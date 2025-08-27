// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_SINGLETON_SINGLETON_H
#define COMPLETED_SINGLETON_SINGLETON_H

#include <iomanip>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

namespace singleton
{

constexpr int type_name_width{24};

template <typename T>
void check_singleton(const std::string& type_name, const T& s1, const T& s2)
{
    std::string type_name_colon{type_name + ":"};
    if (&s1 == &s2) {
        std::cout << std::left << std::setw(type_name_width) << type_name_colon
                  << "Works, both variables contain the same instance." << std::endl;
    } else {
        std::cout << std::left << std::setw(type_name_width) << type_name_colon
                  << "Failed, variables contain different instances." << std::endl;
    }
}

class SingletonNonThreadSafe
{
private:
    SingletonNonThreadSafe() = default;

    static SingletonNonThreadSafe* instance_;

public:
    static SingletonNonThreadSafe& instance();

    void some_business_logic()
    {
        // ...
    }
};

class SingletonWithMutex
{
private:
    SingletonWithMutex() {}

    static SingletonWithMutex* instance_;
    static std::mutex mutex_; // <----

public:
    static SingletonWithMutex& instance();

    void some_business_logic()
    {
        // ...
    }
};

class SingletonWithCallOnce
{
private:
    SingletonWithCallOnce() {}

    static SingletonWithCallOnce* instance_;
    static std::once_flag flag_; // <----

public:
    static SingletonWithCallOnce& instance();

    void some_business_logic()
    {
        // ...
    }
};

class Singleton
{
private:
    Singleton() {}

public:
    static Singleton& instance()
    {
        static Singleton instance_{};
        return instance_;
    }

    void some_business_logic()
    {
        // ...
    }
};

} // namespace singleton

#endif // COMPLETED_SINGLETON_SINGLETON_H