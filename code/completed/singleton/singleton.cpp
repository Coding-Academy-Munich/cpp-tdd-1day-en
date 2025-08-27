// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#include "singleton.h"
#include <chrono>
#include <thread>

namespace singleton
{
SingletonNonThreadSafe* SingletonNonThreadSafe::instance_{};

SingletonNonThreadSafe& SingletonNonThreadSafe::instance()
{
    if (!instance_) {
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 50));
        instance_ = new SingletonNonThreadSafe();
    }
    return *instance_;
}

SingletonWithMutex* SingletonWithMutex::instance_{};
std::mutex SingletonWithMutex::mutex_{};

SingletonWithMutex& SingletonWithMutex::instance()
{
    std::lock_guard<std::mutex> lock{SingletonWithMutex::mutex_}; // <----
    if (!instance_) {
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 50));
        instance_ = new SingletonWithMutex();
    }
    return *instance_;
}

SingletonWithCallOnce* SingletonWithCallOnce::instance_{};
std::once_flag SingletonWithCallOnce::flag_{};

SingletonWithCallOnce& SingletonWithCallOnce::instance()
{
    std::call_once(flag_, []() {
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 50));
        instance_ = new SingletonWithCallOnce();
    });
    return *instance_;
}

} // namespace singleton
