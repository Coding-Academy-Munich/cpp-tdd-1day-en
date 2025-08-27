// ReSharper disable CppClangTidyCppcoreguidelinesAvoidCArrays
#pragma once
#ifndef POINTERS_ARRAY_DANGERS_HPP
#define POINTERS_ARRAY_DANGERS_HPP
#include <span>

namespace pointers {
class Shape;

// This signature is a lie...
void bad_clear_buffer(char buffer[10]);
void problematic_clear_buffer(char (&buffer)[10]);
void dangerous_clear_buffer(char* buffer, int size);
void stl_style_clear_buffer(char* buffer_start, char* buffer_end);
void clear_buffer_span_fixed(std::span<char, 10> buffer);
void clear_buffer_span(std::span<char> buffer);

void show_bad_array_signatures();
void show_bad_array_access();

void draw_many_shapes(const Shape* shapes, int num_shapes);

} // namespace pointers

#endif // POINTERS_ARRAY_DANGERS_HPP
