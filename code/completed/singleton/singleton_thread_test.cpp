// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#include "singleton.h"
#include <atomic>
#include <chrono>
#include <vector>

using namespace singleton;

template <typename TSingleton>
void test_singleton_implementation(
    const std::string& name, int num_threads = 100, int num_iterations = 10
)
{
    std::cout << "Testing " << name << std::endl;
    bool success{true};
    for (int i = 0; i < num_iterations; ++i) {
        if (!test_singleton_threads<SingletonNonThreadSafe>(num_threads)) {
            success = false;
            break;
        }
    }
    print_result(success);
}

template <typename TSingleton>
bool test_singleton_threads(int num_threads)
{
    std::vector<std::thread> threads;
    std::vector<TSingleton*> singletons(num_threads, nullptr);

    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back([&singletons, i]() {
            TSingleton& instance{TSingleton::instance()};
            singletons[i] = &instance;
        });
    }

    for (auto& thread : threads) {
        thread.join();
    }

    if (singletons[0] == nullptr) {
        std::cerr << "Error: slots[0] is nullptr" << std::endl;
        return false;
    }
    auto num_occurrences{std::count(singletons.begin(), singletons.end(), singletons[0])};
    return num_occurrences == num_threads;
}

void print_result(bool success)
{
    if (!success) {
        std::cout << "Race condition detected! Multiple instances were created."
                  << std::endl;
    } else {
        std::cout << "No race condition detected. Only one instance was created."
                  << std::endl;
    }
}

int main()
{
    test_singleton_implementation<SingletonNonThreadSafe>("SingletonNonThreadSafe");
    test_singleton_implementation<SingletonWithMutex>("SingletonWithMutex");
    test_singleton_implementation<SingletonWithCallOnce>("SingletonWithCallOnce");
    test_singleton_implementation<Singleton>("Singleton");

    return 0;
}
