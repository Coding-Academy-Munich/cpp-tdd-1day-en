// ReSharper disable CppClangTidyCppcoreguidelinesAvoidCArrays
// ReSharper disable CppClangTidyCppcoreguidelinesProBoundsArrayToPointerDecay
// ReSharper disable CppClangTidyCppcoreguidelinesProBoundsPointerArithmetic
#include "array_dangers.hpp"

#include <gsl/gsl>
#include <iostream>
#include <span>

#include "shapes.hpp"
#include "utils.hpp"

namespace pointers {

namespace {
auto constexpr show_explanation = true;
}

void bad_clear_buffer(char buffer[10])
{
    for (gsl::index i{0}; i < 10; ++i) {
        buffer[i] = '\0';
    }
}

void problematic_clear_buffer(char (&buffer)[10])
{
    for (auto& c : buffer) {
        c = '\0';
    }
}

void dangerous_clear_buffer(char* buffer, int size)
{
    for (gsl::index i{0}; i < size; ++i) {
        buffer[i] = '\0';
    }
}

void stl_style_clear_buffer(char* buffer_start, char* buffer_end)
{
    for (auto it{buffer_start}; it != buffer_end; ++it) {
        *it = '\0';
    }
}

void clear_buffer_span_fixed(std::span<char, 10> buffer)
{
    for (auto& c : buffer) {
        c = '\0';
    }
}

void clear_buffer_span(std::span<char> buffer)
{
    for (auto& c : buffer) {
        c = '\0';
    }
}

void show_buffer(std::string_view prefix, std::span<char> buffer)
{
    std::cout << prefix << " buffer[";
    for (const char c : buffer) {
        if (c == '\0') {
            std::cout << "\\0";
        }
        else {
            std::cout << c;
        }
    }
    std::cout << "]\n";
}

void show_calls_to_bad_clear_buffer()
{
    char buffer[10]{"123456789"};
    show_buffer("Before call to bad_clear_buffer():        ", buffer);
    bad_clear_buffer(buffer);
    show_buffer("After call to bad_clear_buffer():         ", buffer);

    // ReSharper disable once StringLiteralTypo
    char large_buffer[16]{"123456789abcdef"};
    show_buffer("Before call to bad_clear_buffer():        ", large_buffer);
    bad_clear_buffer(large_buffer);
    show_buffer("After call to bad_clear_buffer():         ", large_buffer);

    // Will the compiler catch this?
    char i{};
    [[maybe_unused]] char* pi{&i};
    // bad_clear_buffer(pi);
    // (Answer: no, but it will hopefully crash at runtime.)
}

void show_calls_to_problematic_clear_buffer()
{
    char buffer[10]{"123456789"};
    show_buffer("Before call to problematic_clear_buffer():", buffer);
    problematic_clear_buffer(buffer);
    show_buffer("After call to problematic_clear_buffer(): ", buffer);

    // ReSharper disable once StringLiteralTypo
    [[maybe_unused]] char large_buffer[16]{"123456789abcdef"};
    // Compiler error
    // problematic_clear_buffer(large_buffer);
}

void show_calls_to_dangerous_clear_buffer()
{
    char buffer[10]{"123456789"};
    show_buffer("Before call to dangerous_clear_buffer():  ", buffer);
    dangerous_clear_buffer(buffer, 10);
    show_buffer("After call to dangerous_clear_buffer():   ", buffer);

    // ReSharper disable once StringLiteralTypo
    [[maybe_unused]] char large_buffer[16]{"123456789abcdef"};
    // Compiler error
    show_buffer("Before call to dangerous_clear_buffer():  ", large_buffer);
    dangerous_clear_buffer(large_buffer, 16);
    show_buffer("After call to dangerous_clear_buffer():   ", large_buffer);
}

void show_calls_to_stl_style_clear_buffer()
{
    char buffer[10]{"123456789"};
    show_buffer("Before call to stl_style_clear_buffer():  ", buffer);
    stl_style_clear_buffer(std::begin(buffer), std::end(buffer));
    show_buffer("After call to stl_style_clear_buffer():   ", buffer);

    // ReSharper disable once StringLiteralTypo
    char large_buffer[16]{"123456789abcdef"};
    show_buffer("Before call to stl_style_clear_buffer():  ", large_buffer);
    stl_style_clear_buffer(std::begin(large_buffer), std::end(large_buffer));
    show_buffer("After call to stl_style_clear_buffer():   ", large_buffer);
}

void show_calls_to_clear_buffer_span_fixed()
{
    char buffer[10]{"123456789"};
    show_buffer("Before call to clear_buffer_span_fixed(): ", buffer);
    clear_buffer_span_fixed(buffer);
    show_buffer("After call to clear_buffer_span_fixed():  ", buffer);

    // ReSharper disable once StringLiteralTypo
    [[maybe_unused]] char large_buffer[16]{"123456789abcdef"};
    // Compiler error
    // clear_buffer_span(large_buffer);
}

void show_calls_to_clear_buffer_span()
{
    char buffer[10]{"123456789"};
    show_buffer("Before call to clear_buffer_span():       ", buffer);
    clear_buffer_span(buffer);
    show_buffer("After call to clear_buffer_span():        ", buffer);

    // ReSharper disable once StringLiteralTypo
    char large_buffer[16]{"123456789abcdef"};
    show_buffer("Before call to clear_buffer_span():       ", large_buffer);
    clear_buffer_span(large_buffer);
    show_buffer("After call to clear_buffer_span():        ", large_buffer);
}

void show_bad_array_signatures()
{
    show_calls_to_bad_clear_buffer();
    std::cout << std::string(72, '-') << "\n";
    show_calls_to_problematic_clear_buffer();
    std::cout << std::string(72, '-') << "\n";
    show_calls_to_dangerous_clear_buffer();
    std::cout << std::string(72, '-') << "\n";
    show_calls_to_stl_style_clear_buffer();
    std::cout << std::string(72, '-') << "\n";
    show_calls_to_clear_buffer_span_fixed();
    std::cout << std::string(72, '-') << "\n";
    show_calls_to_clear_buffer_span();
}

void show_bad_array_access()
{
    const Circle circles[5]{{1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0}, {7.0, 8.0}, {9.0, 0.0}};
    const Circle* pc = circles;
    const Shape* ps = circles;

    std::cout << "Drawing circles via circles[].\n\n";
    std::cout << "circles[0]: ";
    circles[0].draw();
    std::cout << "circles[3]: ";
    circles[3].draw();

    std::cout << "\nDrawing circles via pc.\n\n";
    std::cout << "&pc[0]: ";
    (&pc[0])->draw();
    std::cout << "&pc[3]: ";
    (&pc[3])->draw();

    std::cout << "\nDrawing circles via ps.\n\n";
    std::cout << "&ps[0]: ";
    (&ps[0])->draw();
    std::cout << "&ps[3]: ";
    (&ps[3])->draw();

    if constexpr (show_explanation) {
        std::cout << "\nExplanation:\n\n";
        std::cout << "Address of circles:    " << address_of(circles) << "\n";
        std::cout << "Address of pc:         " << address_of(pc) << "\n";
        std::cout << "Address of ps:         " << address_of(ps) << "\n\n";

        std::cout << "Address of circles[1]: " << address_of(circles + 1) << "\n";
        std::cout << "Address of pc[1]:      " << address_of(pc + 1) << "\n";
        std::cout << "Address of ps[1]:      " << address_of(ps + 1) << "\n\n";

        std::cout << "Address of circles[3]: " << address_of(circles + 3) << "\n";
        std::cout << "Address of pc[3]:      " << address_of(pc + 3) << "\n";
        std::cout << "Address of ps[3]:      " << address_of(ps + 3) << "\n\n";

        std::cout << "Size of Circle:        " << sizeof(Circle) << "\n";
        std::cout << "Size of Shape:         " << sizeof(Shape) << "\n\n";
    }
}

void draw_many_shapes(const Shape* shapes, int num_shapes)
{
    for (gsl::index i{0}; i < num_shapes; ++i) {
        shapes[i].draw();
    }
}


} // namespace pointers
