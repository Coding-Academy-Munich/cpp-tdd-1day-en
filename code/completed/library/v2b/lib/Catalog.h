// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_LIBRARY_V2B_LIB_CATALOG_H
#define COMPLETED_LIBRARY_V2B_LIB_CATALOG_H

#include <functional>
#include <memory>
#include <vector>

namespace library::v2b {

template <typename T>
class Catalog {
public:
    using ValueType = T;
    using PointerType = std::unique_ptr<ValueType>;
    using ContainerType = std::vector<PointerType>;

    Catalog() = default;
    explicit Catalog(ContainerType values);

    [[nodiscard]] size_t Size() const { return values.size(); }

    [[nodiscard]] const ContainerType& GetValues() const { return values; }
    [[nodiscard]] ContainerType& GetValues() { return values; }

    void Add(PointerType value) { values.push_back(std::move(value)); }

    void Remove(const ValueType& value)
    {
        const auto& iterator = std::ranges::find_if(
            values, [&value](const auto& v) { return *v == value; });
        if (iterator != values.end()) {
            values.erase(iterator);
        }
    }

    [[nodiscard]] ValueType* Find(
        const std::function<bool(const ValueType&)>& predicate)
    {
        for (const auto& value : values) {
            if (predicate(*value)) {
                return value.get();
            }
        }
        return nullptr;
    }

private:
    ContainerType values;
};

template <typename T>
Catalog<T>::Catalog(Catalog::ContainerType values)
    : values(std::move(values))
{
}

} // namespace library::v2b

#endif // COMPLETED_LIBRARY_V2B_LIB_CATALOG_H
