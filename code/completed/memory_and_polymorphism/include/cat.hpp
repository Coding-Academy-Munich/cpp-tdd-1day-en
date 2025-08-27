// ReSharper disable CppClangTidyCppcoreguidelinesProTypeReinterpretCast
#pragma once

#include <string>

#include "animal.hpp"

using namespace std::string_literals;

class Cat final : public Animal
{
#if SHOW_ANIMAL_INSTANCE_LIFE_CYCLE
public:
    Cat() noexcept
    {
        std::cout << "Creating cat instance " << std::hex
                  << reinterpret_cast<std::uintptr_t>(this)
                  << " via DEFAULT constructor." << std::endl;
    }

    Cat(const Cat& cat) : Animal(cat)
    {
        std::cout << "Creating cat instance " << std::hex
                  << reinterpret_cast<std::uintptr_t>(this) << " via COPY constructor."
                  << std::endl;
    }

    Cat(Cat&& cat) noexcept : Animal(std::move(cat))
    {
        std::cout << "Creating cat instance " << std::hex
                  << reinterpret_cast<std::uintptr_t>(this) << " via MOVE constructor."
                  << std::endl;
    }

    Cat& operator=(const Cat& cat)
    {
        Animal::operator=(cat);
        std::cout << "COPY assigning cat instance " << std::hex
                  << reinterpret_cast<std::uintptr_t>(this) << "." << std::endl;
        return *this;
    }

    Cat& operator=(Cat&& cat) noexcept
    {
        Animal::operator=(std::move(cat));
        std::cout << "MOVE assigning cat instance " << std::hex
                  << reinterpret_cast<std::uintptr_t>(this) << "." << std::endl;
        return *this;
    }

    ~Cat()
    {
        std::cout << "DESTROYING cat instance " << std::hex
                  << reinterpret_cast<std::uintptr_t>(this) << "." << std::endl;
    }
#endif

protected:
    [[nodiscard]] std::string describe_impl() const override
    {
        return "A cat. Go away now."s;
    }

    [[nodiscard]] std::string make_sound_impl() const override { return "[Meow]!"s; }

    [[nodiscard]] std::string provide_detailed_description_impl() const override
    {
        return "A cat. It's hungry. It does not make a sound.\n"s;
    }
};
