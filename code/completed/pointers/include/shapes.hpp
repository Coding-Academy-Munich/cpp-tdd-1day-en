#pragma once
#ifndef POINTERS_SHAPES_HPP
#define POINTERS_SHAPES_HPP

namespace pointers {

class Shape // NOLINT(cppcoreguidelines-special-member-functions)
{
public:
    virtual ~Shape() = default;
    virtual void draw() const = 0;
};

class Circle final : public Shape
{
public:
    Circle()
        : Circle{0.0, 0.0}
    {}

    Circle(double x, double y)
        : x_{x}
        , y_{y}
    {}

    void draw() const override;

    [[nodiscard]] double x() const { return x_; }
    [[nodiscard]] double y() const { return y_; }

private:
    double x_;
    double y_;
};

} // namespace pointers

#endif