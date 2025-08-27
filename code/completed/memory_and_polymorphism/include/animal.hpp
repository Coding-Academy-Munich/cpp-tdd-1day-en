// ReSharper disable CppClangTidyCppcoreguidelinesProTypeReinterpretCast
#pragma once
#include <cstdint>
#include <iostream>
#include <string>

using namespace std::string_literals; // NOLINT(clang-diagnostic-header-hygiene)

class Animal
{
public:
#if SHOW_ANIMAL_INSTANCE_LIFE_CYCLE
    Animal() noexcept
    {
        std::cout << "Creating animal instance " << std::hex
                  << reinterpret_cast<std::uintptr_t>(this)
                  << " via DEFAULT constructor." << std::endl;
    }

    Animal(const Animal& animal)
    {
        std::cout << "Creating animal instance " << std::hex
                  << reinterpret_cast<std::uintptr_t>(this) << " via COPY constructor."
                  << std::endl;
    }

    Animal(Animal&& animal) noexcept
    {
        std::cout << "Creating animal instance " << std::hex
                  << reinterpret_cast<std::uintptr_t>(this) << " via MOVE constructor."
                  << std::endl;
    }

    Animal& operator=(const Animal& animal)
    {
        std::cout << "COPY assigning animal instance " << std::hex
                  << reinterpret_cast<std::uintptr_t>(this) << "." << std::endl;
        return *this;
    }

    Animal& operator=(Animal&& animal) noexcept
    {
        std::cout << "MOVE assigning animal instance " << std::hex
                  << reinterpret_cast<std::uintptr_t>(this) << "." << std::endl;
        return *this;
    }
#endif

#if OMIT_VIRTUAL_DESTRUCTOR
#if SHOW_ANIMAL_INSTANCE_LIFE_CYCLE
    ~Animal()
    {
        std::cout << "DESTROYING animal instance " << std::hex
                  << reinterpret_cast<std::uintptr_t>(this) << "." << std::endl;
    }
#else
    ~Animal() = default;
#endif
#else
#if SHOW_ANIMAL_INSTANCE_LIFE_CYCLE
    virtual ~Animal()
    {
        std::cout << "DESTROYING animal instance " << std::hex
                  << reinterpret_cast<std::uintptr_t>(this) << "." << std::endl;
    }
#else
    virtual ~Animal() = default;
#endif
#endif

    // Use Non-virtual interface pattern
    // (special case of template method).
    [[nodiscard]] std::string describe() const { return describe_impl(); }

    [[nodiscard]] std::string make_sound() const { return make_sound_impl(); }

    [[nodiscard]] std::string provide_detailed_description() const
    {
        return provide_detailed_description_impl();
    }

protected:
    [[nodiscard]] virtual std::string describe_impl() const = 0;
    [[nodiscard]] virtual std::string make_sound_impl() const = 0;

    [[nodiscard]] virtual std::string provide_detailed_description_impl() const
    {
        return "Animal: "s + describe_impl() + " It goes "s + make_sound_impl() + "\n"s;
    }
};
