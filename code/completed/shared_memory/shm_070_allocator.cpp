// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#include "shm_070_allocator.h"
#include "utils.h"
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <cstdlib>
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc == 1) {
        print_header("Shared Memory Example 070: Allocator");
        return shm070::run_parent(argv[0]);
    } else if (argc == 2) {
        return shm070::run_child(argv[1]);
    } else {
        std::cerr << "Invalid number of arguments.\n";
        return 1;
    }
}

namespace shm070 {

namespace bi = boost::interprocess;
using namespace std::string_literals;

using SharedMemoryAllocator
    = bi::allocator<int, bi::managed_shared_memory::segment_manager>;

template <typename T>
using SharedMemoryVector = bi::vector<T, SharedMemoryAllocator>;

void print_vector(std::string prefix, const SharedMemoryVector<int>* shared_vector);

int run_parent(std::string_view program) {
    // Remove shared memory on construction and destruction using a modified
    // form of RAII
    struct shm_remove {
        shm_remove() { bi::shared_memory_object::remove("MySharedMemory"); }
        ~shm_remove() { bi::shared_memory_object::remove("MySharedMemory"); }
    } remover;

    // Create a managed shared memory segment
    bi::managed_shared_memory segment(bi::create_only, "MySharedMemory", 65536);

    // Initialize the STL-compatible allocator for segment
    SharedMemoryAllocator allocator {segment.get_segment_manager()};

    // Create a vector of ints in shared memory
    SharedMemoryVector<int>* shared_vector
        = {segment.construct<SharedMemoryVector<int>>("SharedVector")(allocator)};

    // Fill the vector with some data
    for (int i = 0; i < 10; ++i) {
        shared_vector->push_back(i);
    }
    print_vector("Parent", shared_vector);

    // Launch the child process and wait for it to finish
    std::string child_command {build_child_command(program, "child")};
    if (const int error_code {std::system(child_command.c_str())}; error_code != 0) {
        std::cerr << "Child failed with error code " << error_code << ".\n";
        return error_code;
    }
    print_vector("Parent", shared_vector);

    // Launch the child process and wait for it to finish
    std::string child_command_2 {build_child_command(program, "delete")};
    if (const int error_code {std::system(child_command_2.c_str())}; error_code != 0) {
        std::cerr << "Child failed with error code " << error_code << ".\n";
        return error_code;
    }

    // Check that the child has destroyed the vector
    if (segment.find<SharedMemoryVector<int>>("SharedVector").first) {
        std::cerr << "Child failed to destroy the vector.\n";
        return 1;
    }
    return 0;
}

int run_child(std::string_view arg) {

    // Open the shared memory segment. This assumes the segment has been created
    bi::managed_shared_memory segment {bi::open_only, "MySharedMemory"};

    auto shared_vector_res = segment.find<SharedMemoryVector<int>>("SharedVector");
    if (!shared_vector_res.first) {
        std::cerr << "Failed to find shared vector in shared memory.\n";
        return 1;
    }

    SharedMemoryVector<int>* shared_vector {shared_vector_res.first};
    print_vector("Child", shared_vector);

    std::reverse(shared_vector->begin(), shared_vector->end());
    print_vector("Reversed", shared_vector);

    if (arg == "delete") {
        // Destroy the vector
        segment.destroy<SharedMemoryVector<int>>("SharedVector");
    }

    return 0;
}

constexpr int desired_prefix_length {10};

void print_vector(std::string prefix, const SharedMemoryVector<int>* shared_vector) {
    prefix.append(":");
    if (prefix.length() < desired_prefix_length) {
        prefix.append(desired_prefix_length - prefix.length(), ' ');
    }

    if (!shared_vector) {
        std::cout << prefix << "nullptr\n";
        return;
    }

    std::cout << prefix << "[ ";
    for (const auto& value : *shared_vector) {
        std::cout << value << " ";
    }
    std::cout << "]\n";
}

} // namespace shm070
