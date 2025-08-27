// ReSharper disable CppClangTidyCppcoreguidelinesProTypeReinterpretCast
#pragma once

#include <string>

#include "animal.hpp"

using namespace std::string_literals; // NOLINT(clang-diagnostic-header-hygiene)

class Dog final : public Animal
{
#if SHOW_ANIMAL_INSTANCE_LIFE_CYCLE
public:
    Dog() noexcept
    {
        std::cout << "Creating dog instance " << std::hex
                  << reinterpret_cast<std::uintptr_t>(this)
                  << " via DEFAULT constructor." << std::endl;
    }

    Dog(const Dog& dog)
    {
        std::cout << "Creating dog instance " << std::hex
                  << reinterpret_cast<std::uintptr_t>(this) << " via COPY constructor."
                  << std::endl;
    }

    Dog(Dog&& dog) noexcept
    {
        std::cout << "Creating dog instance " << std::hex
                  << reinterpret_cast<std::uintptr_t>(this) << " via MOVE constructor."
                  << std::endl;
    }

    Dog& operator=(const Dog& dog)
    {
        Animal::operator=(dog);
        std::cout << "COPY assigning dog instance " << std::hex
                  << reinterpret_cast<std::uintptr_t>(this) << "." << std::endl;
        return *this;
    }

    Dog& operator=(Dog&& dog) noexcept
    {
        Animal::operator=(dog);
        std::cout << "MOVE assigning dog instance " << std::hex
                  << reinterpret_cast<std::uintptr_t>(this) << "." << std::endl;
        return *this;
    }

    ~Dog()
    {
        std::cout << "DESTROYING dog instance " << std::hex
                  << reinterpret_cast<std::uintptr_t>(this) << "." << std::endl;
    }
#endif

protected:
    [[nodiscard]] std::string describe_impl() const override
    {
        return "A dog. What is there to say?"s;
    }

    [[nodiscard]] std::string make_sound_impl() const override { return "[Woof]!"s; }
};
