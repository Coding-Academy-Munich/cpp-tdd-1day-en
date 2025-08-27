// Created by Dr. Matthias Hölzl on 17/05/2021.
// Copyright (c) 2021 Dr. Matthias Hölzl. See file LICENSE.md.

// ReSharper disable CppClangTidyBugproneExceptionEscape
// ReSharper disable CppUseAuto
// ReSharper disable CppClangTidyClangDiagnosticUnusedMacros
// ReSharper disable CppClangTidyCppcoreguidelinesMacroUsage

#define SHOW_ANIMAL_INSTANCE_LIFE_CYCLE 1
#define OMIT_VIRTUAL_DESTRUCTOR 1

#include <chrono>
#include <iostream>

#include "cat.hpp"
#include "dog.hpp"

template<typename T>
T create_animal()
{
    return T{};
}

template <typename T>
T create_animal_via_temp_variable()
{
    T dog{};
    return dog;
}

template <typename T>
T create_random_animal()
{
    const auto now{std::chrono::high_resolution_clock::now()};
    const auto time{now.time_since_epoch().count()};
    T animal1{};
    T animal2{};
    if (time % 2 == 0) {
        return animal1;
    }
    {
        return animal2;
    }
}

int main()
{
    {
        std::cout << "\nDog fluffy{} ==========================================\n";
        const Dog fluffy{};
        std::cout << "\nDog dolly{Dog{}} ======================================\n";
        Dog dolly{Dog{}};
        std::cout << "\nDog pepper{fluffy} ====================================\n";
        Dog pepper{fluffy}; // NOLINT(performance-unnecessary-copy-initialization)
        std::cout << "\nDog rex{create_animal<Dog>()} =========================\n";
        Dog rex{create_animal<Dog>()};
        std::cout << "\nDog spot{create_animal_via_temp_variable<Dog>()} ======\n";
        Dog spot{create_animal_via_temp_variable<Dog>()};
        std::cout << "\nDog cooper{create_random_animal<Dog>()} ===============\n";
        Dog cooper{create_random_animal<Dog>()};
        std::cout << "\nDog pebbles{std::move(pepper)} ========================\n";
        Dog pebbles{std::move(pepper)};

        std::cout << "\ndolly = fluffy ========================================\n";
        dolly = fluffy;
        std::cout << "\ndolly = std::move(pebbles) ============================\n";
        dolly = std::move(pebbles);
        std::cout << "\n";
    }
    {
        std::cout << "\nCat milo{} ============================================\n";
        Cat milo{};
        std::cout << "\nCat loki{std::move(milo)} =============================\n";
        Cat loki{std::move(milo)};
        std::cout << "\n";
    }
}
