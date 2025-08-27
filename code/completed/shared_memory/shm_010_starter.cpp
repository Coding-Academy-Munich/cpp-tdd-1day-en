// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#include "shm_010_starter.h"
#include "utils.h"
#include <boost/interprocess/detail/os_thread_functions.hpp>
#include <cstdlib>
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc == 1) {
        print_header("Shared Memory Example 010: Starter");
        return shm010::run_parent(argv[0]);
    } else if (argc == 2) {
        return shm010::run_child(argv[1]);
    } else {
        std::cerr << "Invalid number of arguments.\n";
        return 1;
    }
}

namespace shm010 {

namespace bii = boost::interprocess::ipcdetail;
using namespace std::string_literals;

int run_parent(std::string_view program) {
    std::cout << "Hello from main process (id = " << bii::get_current_process_id()
              << ").\n";

    std::string child_command {build_child_command(program, "child")};
    if (0 != std::system(child_command.c_str())) {
        std::cerr << "Failed to start first child process or error in child process.\n";
        return 1;
    }

    std::string child_command_2 {build_child_command(program, "child_2")};
    if (0 != std::system(child_command_2.c_str())) {
        std::cerr << "Failed to start second child process or error in child process.\n";
        return 1;
    }

    std::cout << "Goodbye from main process.\n";
    return 0;
}

int run_child(std::string_view arg) {
    std::cout << "Hello from child process (id = " << bii::get_current_process_id()
              << ", arg = " << arg << ").\n";
    return 0;
}
} // namespace shm010
