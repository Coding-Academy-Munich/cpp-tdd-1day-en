// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#include "shm_040_named_objects.h"
#include "utils.h"
#include <array>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <cstdlib>
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc == 1) {
        print_header("Shared Memory Example 040: Named Objects");
        return shm040::run_parent(argv[0]);
    } else if (argc == 2) {
        return shm040::run_child(argv[1]);
    } else {
        std::cerr << "Invalid number of arguments.\n";
        return 1;
    }
}

namespace shm040 {

namespace bi = boost::interprocess;
using namespace std::string_literals;

struct UserData {
    UserData(int n, double x) : n(n), x(x) { }
    int n;
    double x;
};

std::ostream& operator<<(std::ostream& os, const UserData& user_data) {
    return os << "UserData { n = " << user_data.n << ", x = " << user_data.x << " }";
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
    UserData* user_data {segment.construct<UserData>("UserData")(10, 2.71828)};
    std::cout << "User data instance (parent): " << *user_data << "\n";

    // Create an array of UserData instances in the shared memory segment
    // All instances are initialized with the same values
    // clang-format off
    UserData* user_data_array {
        segment.construct<UserData>("UserData array")[10](42, 3.14159)};
    // clang-format on
    for (int i = 0; i < 2; ++i) {
        std::cout << "User data array[" << i << "]: " << std::string(9, ' ')
                  << user_data_array[i] << "\n";
    }

    std::array<int, 10> ints {90, 91, 92, 93, 94, 95, 96, 97, 98, 99};
    std::array<double, 10> doubles {9.0, 9.1, 9.2, 9.3, 9.4, 9.5, 9.6, 9.7, 9.8, 9.9};

    // Create an array of UserData instances in the shared memory segment using iterators
    // over arrays for the constructor arguments
    // clang-format off
    UserData* user_data_array_it{
		segment.construct_it<UserData>("UserData array_it")[10](
			ints.begin(), doubles.begin())};
    // clang-format on
    for (int i = 0; i < 2; ++i) {
        std::cout << "User data array_it[" << i << "]: " << std::string(6, ' ')
                  << user_data_array_it[i] << "\n";
    }

    // Launch the child process and wait for it to finish
    std::string child_command {build_child_command(program, "child")};
    if (const int error_code {std::system(child_command.c_str())}; error_code != 0) {
        std::cerr << "Child failed with error code " << error_code << ".\n";
        return error_code;
    }

    // Check that data is still available in the parent process
    std::cout << "User data instance (parent): " << *user_data << "\n";
    user_data->n = 10;
    for (int i = 0; i < 2; ++i) {
        std::cout << "User data array[" << i << "]: " << std::string(9, ' ')
                  << user_data_array[i] << "\n";
        user_data_array[i].n = 42;
    }
    for (int i = 0; i < 2; ++i) {
        std::cout << "User data array_it[" << i << "]: " << std::string(6, ' ')
                  << user_data_array_it[i] << "\n";
        user_data_array_it[i].n = 90 + i;
    }

    // Launch the child process and wait for it to finish
    std::string child_command_2 {build_child_command(program, "delete")};
    if (const int error_code {std::system(child_command_2.c_str())}; error_code != 0) {
        std::cerr << "Child failed with error code " << error_code << ".\n";
        return error_code;
    }

    // Ensure that all user data instances are destroyed
    for (const char* name : {"UserData", "UserData array", "UserData array_it"}) {
        if (segment.find<UserData>(name).first) {
            std::cerr << "User data instance \"" << name << "\" still present in parent.\n";
            return 1;
        }
    }
    std::cout << "All user data instances are destroyed.\n";

    return 0;
}

void check_user_data(
    std::string_view name, const std::pair<UserData*, std::size_t>& user_data, int n,
    double x, std::size_t size = 1
);

int run_child(std::string_view arg) {
    std::pair<UserData*, std::size_t> user_data;

    // Open the shared memory segment. This assumes the segment has been created
    bi::managed_shared_memory segment {bi::open_only, "MySharedMemory"};

    // Find the UserData instance in the shared memory segment
    user_data = segment.find<UserData>("UserData");
    check_user_data("UserData", user_data, 10, 2.71828);
    user_data.first->n = 20;

    // Find the array of UserData instances in the shared memory segment
    user_data = segment.find<UserData>("UserData array");
    check_user_data("UserData array", user_data, 42, 3.14159, 10);
    for (int i = 0; i < 10; ++i) {
        user_data.first[i].n = 30 + i;
    }

    // Find the array of UserData instances (created with iterator) in the shared memory
    // segment
    user_data = segment.find<UserData>("UserData array_it");
    check_user_data("UserData array_it", user_data, 90, 9.0, 10);
    for (int i = 0; i < 10; ++i) {
        user_data.first[i].n = 40 + i;
    }

    if (arg == "delete") {
        for (const char* name : {"UserData", "UserData array", "UserData array_it"}) {
            segment.destroy<UserData>(name);
        }
    }
    return 0;
}

void check_user_data(
    std::string_view name, const std::pair<UserData*, std::size_t>& user_data, int n,
    double x, std::size_t size
) {
    if (user_data.first == nullptr) {
        std::cerr << "User data instance \"" << name << "\" not found in child.\n";
        return;
    }
    if (user_data.second != size) {
        std::cerr << "User data instance \"" << name << "\" has wrong size in child.\n";
        return;
    }
    if (user_data.first->n != n || user_data.first->x != x) {
        std::cerr << "User data instance \"" << name << "\" has wrong values in child.\n";
        return;
    }

    std::stringstream ss;
    ss << "User data instance \"" << name << "\" is OK: ";

    std::cout.width(46);
    std::cout << std::left << ss.str() << *user_data.first << "\n";
}

} // namespace shm040
