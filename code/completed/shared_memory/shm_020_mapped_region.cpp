// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#include "shm_020_mapped_region.h"
#include "utils.h"
#include <boost/interprocess/managed_shared_memory.hpp>
#include <cstdlib>
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc == 1) {
        print_header("Shared Memory Example 020: Mapped Region");
        return shm020::run_parent(argv[0]);
    } else if (argc == 2) {
        return shm020::run_child(argv[1]);
    } else {
        std::cerr << "Invalid number of arguments.\n";
        return 1;
    }
}

namespace shm020 {

namespace bi = boost::interprocess;
using namespace std::string_literals;

constexpr std::size_t shared_memory_length_in_bytes {65536};
constexpr std::size_t char_allocation_size = 1024;
static_assert(char_allocation_size % 4 == 0);

int run_parent(std::string_view program) {
    // Remove shared memory on construction and destruction using a modified
    // form of RAII
    struct shm_remove {
        shm_remove() { bi::shared_memory_object::remove("MySharedMemory"); }
        ~shm_remove() { bi::shared_memory_object::remove("MySharedMemory"); }
    } remover;

    // Create a shared memory object (unmanaged)
    bi::shared_memory_object shared_memory {
        bi::create_only, "MySharedMemory", bi::read_write
    };

    // Set the size of the shared memory object
    shared_memory.truncate(shared_memory_length_in_bytes);

    // Map the shared memory object into the address space of the current process
    bi::mapped_region region {shared_memory, bi::read_write};
    std::cout << "Mapped region size: " << region.get_size() << " bytes\n";

    // Get a pointer to the beginning of the shared memory region
    void* raw_data {region.get_address()};

    // Treat the shared memory as an array of characters
    char* char_data {static_cast<char*>(raw_data)};

    // Fill part of the memory with the pattern "ABCD"
    for (int i {0}; i < char_allocation_size; i += 4) {
        char_data[i] = 'A';
        char_data[i + 1] = 'B';
        char_data[i + 2] = 'C';
        char_data[i + 3] = 'D';
    }

    // Launch the child process and wait for it to finish
    std::string child_command {build_child_command(program, "child")};
    if (const int error_code {std::system(child_command.c_str())}; error_code != 0) {
        std::cerr << "Child failed with error code " << error_code << ".\n";
        return error_code;
    }

    return 0;
}

int run_child(std::string_view arg) {
    // Open the existing shared memory object
    bi::shared_memory_object shared_memory {bi::open_only, "MySharedMemory", bi::read_only};

    // Map the shared memory object into the address space of the current process
    bi::mapped_region region {shared_memory, bi::read_only};

    // Access char_data in the shared memory region
    char* char_data {static_cast<char*>(region.get_address())};

    // Output the char contents of the shared memory region
    std::cout << "Char data: ";
    for (int i {0}; i < 40; ++i) {
        std::cout << char_data[i];
    }
    std::cout << "...\n";

    // Check that the memory contains the expected pattern
    for (int i {0}; i < char_allocation_size; i += 4) {
        if (char_data[i] != 'A' || char_data[i + 1] != 'B' || char_data[i + 2] != 'C'
            || char_data[i + 3] != 'D') {
            std::cerr << "Memory corrupted at position " << i << ".\n";
            return 1;
        }
    }

    std::cout << "Memory verified.\n";
    return 0;
}
} // namespace shm020
