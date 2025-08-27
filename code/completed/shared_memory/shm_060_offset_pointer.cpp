// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#include "shm_060_offset_pointer.h"
#include "utils.h"
#include <boost/interprocess/managed_shared_memory.hpp>
#include <cstdlib>
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc == 1) {
        print_header("Shared Memory Example 060: Offset Pointer");
        return shm060::run_parent(argv[0]);
    } else if (argc == 2) {
        return shm060::run_child(argv[1]);
    } else {
        std::cerr << "Invalid number of arguments.\n";
        return 1;
    }
}

namespace shm060 {

namespace bi = boost::interprocess;
using namespace std::string_literals;

// UserData can *only* be used in shared memory
struct UserData {
    UserData() : self {this} { }
    bi::offset_ptr<const UserData> self;
};

std::ostream& operator<<(std::ostream& os, const UserData& user_data) {
    return os << std::hex << "UserData { self = 0x" << &*user_data.self << " } @ 0x"
              << &user_data << std::dec << ", user_data.self "
              << (user_data.self == &user_data ? "==" : "!=") << " &user_data";
}

int run_parent(std::string_view program) {
    // Remove shared memory on construction and destruction using a modified
    // form of RAII
    struct shm_remove {
        shm_remove() { bi::shared_memory_object::remove("MySharedMemory"); }
        ~shm_remove() { bi::shared_memory_object::remove("MySharedMemory"); }
    } remover;

    // Create a managed shared memory segment
    bi::managed_shared_memory segment(bi::create_only, "MySharedMemory", 65536);

    // Create a single UserData instance in the shared memory segment
    UserData* user_data = {segment.construct<UserData>("UserData")()};
    std::cout << "Parent: " << *user_data << "\n";

    // Launch the child process and wait for it to finish
    std::string child_command {build_child_command(program, "child")};
    if (const int error_code {std::system(child_command.c_str())}; error_code != 0) {
        std::cerr << "Child failed with error code " << error_code << ".\n";
        return error_code;
    }
    return 0;
}

int run_child(std::string_view arg) {

    // Open the shared memory segment. This assumes the segment has been created
    bi::managed_shared_memory segment {bi::open_only, "MySharedMemory"};

    // Find the UserData instance in the shared memory segment
    auto user_data_res = segment.find<UserData>("UserData");

    // Output the user data instance, if it exists
    if (!user_data_res.first) {
        std::cerr << "Failed to find user data in shared memory.\n";
        return 1;
    } else {
        UserData* user_data {user_data_res.first};
        std::cout << "Child:  " << *user_data << "\n";
    }

    return 0;
}

} // namespace shm060
