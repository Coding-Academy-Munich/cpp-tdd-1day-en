// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#include "shm_030_managed_segment.h"
#include "utils.h"
#include <boost/interprocess/managed_shared_memory.hpp>
#include <cstdlib>
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc == 1) {
        print_header("Shared Memory Example 030: Segment");
        return shm030::run_parent(argv[0]);
    } else if (argc == 2) {
        return shm030::run_child(argv[1]);
    } else {
        std::cerr << "Invalid number of arguments.\n";
        return 1;
    }
}

namespace shm030 {

namespace bi = boost::interprocess;
using namespace std::string_literals;

constexpr std::size_t allocation_size = 1024;
static_assert(allocation_size % 4 == 0);

int run_parent(std::string_view program) {
    // Remove shared memory on construction and destruction using a modified
    // form of RAII
    struct shm_remove {
        shm_remove() { bi::shared_memory_object::remove("MySharedMemory"); }
        ~shm_remove() { bi::shared_memory_object::remove("MySharedMemory"); }
    } remover;

    // Create a managed shared memory segment
    bi::managed_shared_memory segment(bi::create_only, "MySharedMemory", 65536);
    bi::managed_shared_memory::size_type free_memory {segment.get_free_memory()};
    std::cout << "Free memory in segment:          " << free_memory << " bytes\n";

    // Allocate 1024 bytes of raw memory
    void* raw_data {segment.allocate(allocation_size)};

    // Print some statistics about the allocation
    std::cout << "Free memory after allocation:    " << segment.get_free_memory()
              << " bytes\n";
    std::cout << "Allocated memory:                "
              << free_memory - segment.get_free_memory() << " bytes\n";

    // Treat the allocated memory as an array of characters
    char* char_data = static_cast<char*>(raw_data);

    // Fill the allocated memory with the pattern "ABCD"
    for (int i {0}; i < allocation_size; i += 4) {
        char_data[i] = 'A';
        char_data[i + 1] = 'B';
        char_data[i + 2] = 'C';
        char_data[i + 3] = 'D';
    }

    // Create a handle to the allocated memory that we can pass to another process
    // This can address the memory in the shared memory segment across processes
    bi::managed_shared_memory::handle_t handle {segment.get_handle_from_address(raw_data)};
    std::cout << "Handle: " << handle << "\n";

    // Launch the child process and wait for it to finish
    std::string child_command {build_child_command(program, std::to_string(handle))};
    if (const int error_code {std::system(child_command.c_str())}; error_code != 0) {
        std::cerr << "Child failed with error code " << error_code << ".\n";
        return error_code;
    }

    // Check that the memory has been deallocated
    std::cout << "Free memory after child process: " << segment.get_free_memory()
              << " bytes\n";
    if (segment.all_memory_deallocated()) {
        std::cout << "All memory deallocated.\n";
    } else {
        std::cout << "Memory not deallocated!\n";
    }
    return 0;
}

int run_child(std::string_view arg) {
    // Open the shared memory segment. This assumes the segment has been created
    bi::managed_shared_memory segment {bi::open_only, "MySharedMemory"};

    // Create a handle to the allocated memory
    bi::managed_shared_memory::handle_t handle {};

    // Read the handle from the argument
    std::stringstream ss;
    ss << arg;
    ss >> handle;

    // Get a pointer to the allocated memory from the handle
    void* raw_data = segment.get_address_from_handle(handle);

    // Access the data in the segment as characters
    char* char_data = static_cast<char*>(raw_data);

    // Output the char contents of the shared memory region
    std::cout << "Char data: ";
    for (int i {0}; i < 40; ++i) {
        std::cout << char_data[i];
    }
    std::cout << "...\n";

    // Verify that the memory contains the expected pattern
    for (int i = 0; i < allocation_size; i += 4) {
        if (char_data[i] != 'A' || char_data[i + 1] != 'B' || char_data[i + 2] != 'C'
            || char_data[i + 3] != 'D') {
            std::cerr << "Memory corrupted.\n";
            return 1;
        }
    }
    std::cout << "Memory verified.\n";

    // Deallocate the memory (for all processes)
    segment.deallocate(raw_data);
    return 0;
}
} // namespace shm030
