// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Animal {
public:
    explicit Animal(const std::string& name) // NOLINT(*-pass-by-value)
        : name {name}
    {
    }
    Animal(const Animal&) = delete;
    Animal& operator=(const Animal&) = delete;
    Animal(Animal&&) = delete;
    Animal& operator=(Animal&&) = delete;
    virtual ~Animal() = default;

    virtual void print_food_requirements() const
    {
        std::cout << name << " needs the following food: " << std::endl;
    }

protected:
    std::string name;
};

// %% tags=["subslide"]
class Elephant : public Animal {
public:
    Elephant()
        : Animal {"Elephant"}
    {
    }

    void print_food_requirements() const override
    {
        Animal::print_food_requirements();
        std::cout << "  hay" << std::endl;
        std::cout << "  fruit" << std::endl;
        std::cout << "  vegetables" << std::endl;
    }
};

class Zebra : public Animal {
public:
    Zebra()
        : Animal {"Zebra"}
    {
    }

    void print_food_requirements() const override
    {
        Animal::print_food_requirements();
        std::cout << "  hay" << std::endl;
        std::cout << "  grass" << std::endl;
    }
};

class Lion : public Animal {
public:
    Lion()
        : Animal {"Lion"}
    {
    }

    void print_food_requirements() const override
    {
        Animal::print_food_requirements();
        std::cout << "  meat" << std::endl;
    }
};

using Animals = std::vector<std::unique_ptr<Animal>>;

Animals make_animals()
{
    std::vector<std::unique_ptr<Animal>> res {};
    res.push_back(std::make_unique<Elephant>());
    res.push_back(std::make_unique<Zebra>());
    res.push_back(std::make_unique<Lion>());
    return res;
}

int main()
{
    auto animals = make_animals();

    for (const auto& animal : animals) {
        animal->print_food_requirements();
    };
}
