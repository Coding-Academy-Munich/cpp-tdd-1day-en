// ReSharper disable CppClangTidyCppcoreguidelinesProTypeReinterpretCast
#pragma once
#ifndef POINTERS_UTILS_HPP
#define POINTERS_UTILS_HPP

#include <cstdint>
#include <sstream>

template <typename T> std::string address_of(T* obj)
{
    std::stringstream os {};
    os << "0x" << std::hex << reinterpret_cast<std::uintptr_t>(obj);
    return os.str();
}

#endif