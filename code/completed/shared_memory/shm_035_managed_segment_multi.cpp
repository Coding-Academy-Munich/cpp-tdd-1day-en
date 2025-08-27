// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#include "shm_035_managed_segment_multi.h"
#include "utils.h"
#include <boost/interprocess/managed_shared_memory.hpp>
#include <cstdlib>
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc == 1) {
        print_header("Shared Memory Example 035: Segment Multi");
        return shm035::run_parent(argv[0]);
    } else if (argc == 3) {
        return shm035::run_child(argv[1], argv[2]);
    } else {
        std::cerr << "Invalid number of arguments.\n";
        return 1;
    }
}

namespace shm035 {

namespace bi = boost::interprocess;
using namespace std::string_literals;

constexpr std::size_t char_allocation_size = 1024;
static_assert(char_allocation_size % 4 == 0);

constexpr std::size_t num_double_allocations {1024};

int run_parent(std::string_view program) {
    // Remove shared memory on construction and destruction using a modified
    // form of RAII
    struct shm_remove {
        shm_remove() { bi::shared_memory_object::remove("MySharedMemory"); }
        ~shm_remove() { bi::shared_memory_object::remove("MySharedMemory"); }
    } remover;

    // Create a managed shared memory segment
    bi::managed_shared_memory segment(bi::create_only, "MySharedMemory", 65536);
    std::cout << "Free memory in segment:                 " << segment.get_free_memory()
              << " bytes\n";

    // Allocate 1024 bytes of raw memory for chars
    void* raw_char_data {segment.allocate(char_allocation_size)};
    std::cout << "Free memory after char allocation:      " << segment.get_free_memory()
              << " bytes\n";

    // Treat the allocated char memory as an array of characters
    auto* char_data = static_cast<char*>(raw_char_data);

    // Fill the allocated memory with the pattern "ABCD"
    for (int i {0}; i < char_allocation_size; i += 4) {
        char_data[i] = 'A';
        char_data[i + 1] = 'B';
        char_data[i + 2] = 'C';
        char_data[i + 3] = 'D';
    }

    // Allocate 1024 * sizeof(double) bytes of raw memory for doubles
    void* raw_double_data {segment.allocate(num_double_allocations * sizeof(double))};
    std::cout << "Free memory after double allocation:    " << segment.get_free_memory()
              << " bytes\n";

    // Treat the allocated double memory as an array of doubles
    auto* double_data = static_cast<double*>(raw_double_data);

    // Fill the allocated double memory with the pattern 0, 1, 2, ...
    for (int i {0}; i < num_double_allocations; ++i) {
        double_data[i] = static_cast<double>(i);
    }

    // Create a char_handle to the allocated char memory
    bi::managed_shared_memory::handle_t char_handle {
        segment.get_handle_from_address(raw_char_data)
    };

    // Create a double_handle to the allocated double memory
    bi::managed_shared_memory::handle_t double_handle {
        segment.get_handle_from_address(raw_double_data)
    };

    // Launch the child process and wait for it to finish
    std::string child_command {build_child_command(
        program, std::to_string(char_handle), std::to_string(double_handle)
    )};

    if (const int error_code {std::system(child_command.c_str())}; error_code != 0) {
        std::cerr << "Child failed with error code " << error_code << ".\n";
        return error_code;
    }

    // Check that the char memory has been deallocated
    std::cout << "Free memory after child process:        " << segment.get_free_memory()
              << " bytes\n";

    // Deallocate the double memory (for all processes)
    segment.deallocate(raw_double_data);
    std::cout << "Free memory after deallocating doubles: " << segment.get_free_memory()
              << " bytes\n";

    if (segment.all_memory_deallocated()) {
        std::cout << "All memory deallocated.\n";
    } else {
        std::cout << "Memory not deallocated!\n";
    }
    return 0;
}

int run_child(std::string_view char_handle_str, std::string_view double_handle_str) {
    // Open the shared memory segment. This assumes the segment has been created
    bi::managed_shared_memory segment {bi::open_only, "MySharedMemory"};

    // Create handles to the allocated memory
    bi::managed_shared_memory::handle_t char_handle {};
    bi::managed_shared_memory::handle_t double_handle {};

    // Read the handles from the arguments
    std::stringstream ss;
    ss << char_handle_str;
    ss >> char_handle;
    ss.clear();
    ss << double_handle_str;
    ss >> double_handle;

    // Get a pointer to the allocated memory from the char_handle
    void* raw_char_data = segment.get_address_from_handle(char_handle);
    void* raw_double_data = segment.get_address_from_handle(double_handle);

    // Access the data in the segment as characters
    auto* char_data = static_cast<char*>(raw_char_data);
    auto* double_data = static_cast<double*>(raw_double_data);

    // Output the char contents of the shared memory region
    std::cout << "Char data: ";
    for (int i {0}; i < 40; ++i) {
        std::cout << char_data[i];
    }
    std::cout << "...\n";

    // Check that the memory contains the expected pattern for chars
    for (int i {0}; i < char_allocation_size; i += 4) {
        if (char_data[i] != 'A' || char_data[i + 1] != 'B' || char_data[i + 2] != 'C'
            || char_data[i + 3] != 'D') {
            std::cerr << "Char memory corrupted at position " << i << ".\n";
            return 1;
        }
    }

    // Output the first few doubles in the shared memory region
    std::cout << "Double data: ";
    for (int i {0}; i < 10; ++i) {
        std::cout << double_data[i] << ", ";
    }
    std::cout << "...\n";

    // Check that the memory contains the expected pattern for doubles
    for (int i {0}; i < num_double_allocations; ++i) {
        if (double_data[i] != static_cast<double>(i)) {
            std::cerr << "Double memory corrupted at position " << i << ".\n";
            return 1;
        }
    }

    std::cout << "Memory verified.\n";

    // Deallocate the memory (for all processes)
    segment.deallocate(raw_char_data);
    return 0;
}
} // namespace shm035
