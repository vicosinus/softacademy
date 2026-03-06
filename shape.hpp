#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <cstddef>
#include <stdexcept>
#include <cmath>

namespace softacademy {
    class Shape {
    public:
        virtual ~Shape() = default;
        virtual double area() const = 0;
        virtual double perimeter() const = 0;
    };

    class Circle final : public Shape {
    public:
        explicit Circle(double radius) 
        : m_radius(radius) {}

        double radius() const noexcept {
            return m_radius;
        }

        double area() const override {
            return 3.14 * m_radius * m_radius;
        }
        double perimeter() const override {
            return 2 * 3.14 * m_radius;
        }
    private:
        double m_radius;
    };

    class Rectangle final : public Shape {
    public:
        Rectangle(double width, double height) 
        :m_width(width) 
        ,m_height(height) {}

        double width() const noexcept {
            return m_width;
        }

        double height() const noexcept {
            return m_height;
        }

        double area() const override {
            return m_width * m_height;
        }

        double perimeter() const override {
            return 2 * (m_width + m_height);
        }
    private:
        double m_width;
        double m_height;
    };

    class Triangle final : public Shape {
    public:
        Triangle(double a, double b, double c)
        : m_a(a)
        , m_b(b)
        , m_c(c) {
            if (!valid_triangle(m_a, m_b, m_c)) {
                throw std::invalid_argument("triangle doesnt exist");
            }
        }

        double a() const noexcept {
            return m_a;
        }

        double b() const noexcept {
            return m_b;
        }

        double c() const noexcept {
            return m_c;
        }

        double area() const override {
            double p = (m_a + m_b + m_c) / 2;
            return std::sqrt(p * (p - m_a) * (p - m_b) * (p - m_c));
        }

        double perimeter() const override {
            return m_a + m_b + m_c;
        }
    private:
        double m_a;
        double m_b;
        double m_c;
    private:
        bool valid_triangle(double a, double b, double c) const noexcept {
            if (a + b <= c || a + c <= b || b + c <= a) {
                return false;
            }
            return true;
        }
    };
}

#endif 