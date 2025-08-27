// ReSharper disable CppClangTidyClangDiagnosticUnusedMacros
// ReSharper disable CppClangTidyCppcoreguidelinesMacroUsage

#define SHOW_ANIMAL_INSTANCE_LIFE_CYCLE 1
#define SHOW_RAII_OPERATIONS 1
#define OMIT_VIRTUAL_DESTRUCTOR 0

#include "animal.hpp"
#include "cat.hpp"
#include "dog.hpp"
#include "raii.hpp"

using raii::SimpleRaiiContainer;

int main()
{
    try {
        SimpleRaiiContainer<Dog> dog_container{};
        std::cout << dog_container.get()->describe() << "\n";
        // throw std::runtime_error("Error!");
    }
    catch (const std::runtime_error&) {
        std::printf("An exception was thrown.\n");
    }
    try {
        SimpleRaiiContainer<Cat> cat_container{};
        std::cout << cat_container.get()->describe() << "\n";

        auto another_cat_container{std::move(cat_container)};
        std::cout << another_cat_container.get()->describe() << "\n";

        SimpleRaiiContainer<Cat> yet_another_cat_container{};
        // yet_another_cat_container = another_cat_container;
        yet_another_cat_container = std::move(another_cat_container);
        std::cout << yet_another_cat_container.get()->describe() << "\n";
    }
    catch (const std::runtime_error&) {
        std::printf("An exception was thrown.\n");
    }
}