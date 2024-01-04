#include <iostream>
#include <cmath>

class Figure {
public:
    Figure() {}

    virtual double getArea() const = 0;
    virtual double getPerimeter() const = 0;
};

class Triangle : public Figure {
private:
    double side1, side2, side3;

public:
    Triangle(double s1, double s2, double s3) : side1(s1), side2(s2), side3(s3) {}

    double getSide1() const { return side1; }
    double getSide2() const { return side2; }
    double getSide3() const { return side3; }

    void setSide1(double s) { side1 = s; }
    void setSide2(double s) { side2 = s; }
    void setSide3(double s) { side3 = s; }

    double getArea() const override {
        double s = (side1 + side2 + side3) / 2.0;
        return sqrt(s * (s - side1) * (s - side2) * (s - side3));
    }

    double getPerimeter() const override {
        return side1 + side2 + side3;
    }
};

class Rectangle : public Figure {
private:
    double length, width;

public:
    Rectangle(double l, double w) : length(l), width(w) {}

    double getLength() const { return length; }
    double getWidth() const { return width; }

    void setLength(double l) { length = l; }
    void setWidth(double w) { width = w; }

    double getArea() const override {
        return length * width;
    }

    double getPerimeter() const override {
        return 2 * (length + width);
    }
};

class Circle : public Figure {
private:
    double radius;

public:
    Circle(double r) : radius(r) {}

    double getRadius() const { return radius; }

    void setRadius(double r) { radius = r; }

    double getArea() const override {
        return 3.141592653589793 * radius * radius;
    }

    double getPerimeter() const override {
        return 2 * 3.141592653589793 * radius;
    }
};

int main() {
    // Example usage:
    Triangle triangle(3.0, 4.0, 5.0);
    Rectangle rectangle(4.0, 5.0);
    Circle circle(2.5);

    std::cout << "Triangle Area: " << triangle.getArea() << ", Perimeter: " << triangle.getPerimeter() << std::endl;
    std::cout << "Rectangle Area: " << rectangle.getArea() << ", Perimeter: " << rectangle.getPerimeter() << std::endl;
    std::cout << "Circle Area: " << circle.getArea() << ", Circumference: " << circle.getPerimeter() << std::endl;

    return 0;
}
