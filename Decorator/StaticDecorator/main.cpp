#include <iostream>

using namespace std;

struct Shape {
    virtual string str() const=0;
};

struct Circle : Shape {
    float radius;
    Circle() {}
    Circle(float radius) : radius(radius) {}
    void resize(float factor) {
        radius *= factor;
    }
    string str() const override {
        ostringstream oss;
        oss << "A circle of radius " << radius;
        return oss.str();
    }
};

struct Square : Circle {
    float side;
    Square() {}
    Square(float side) : side(side){}
    string str() const override {
        ostringstream oss;
        oss << "A square with side " << side;
        return oss.str();
    }
};

struct ColoredShape : Shape {
    Shape& shape;
    string color;
    ColoredShape(Shape& shape, const string &color)
        : shape(shape), color(color) {}
    string str() const override {
        ostringstream oss;
        oss << shape.str() << " has the color " << color;
        return oss.str();
    }
};

struct TransparentShape : Shape {
    Shape& shape;
    uint8_t transparency;
    TransparentShape(Shape & shape, uint8_t transparency)
        : shape(shape), transparency(transparency) {}
    string str() const override {
        ostringstream oss;
        oss << shape.str() << " has " << static_cast<float>(transparency)/255.f*100.f << "% transparency";

        return oss.str();
    }
};

// Static Decorator
// mixin inheritance
// perfect forwarding
template <typename T>
concept IsAShape = std::is_base_of<Shape, T>::value;
template <IsAShape T> struct ColoredShape2 : T {
    string color;
    ColoredShape2() {}
    template <typename...Args>
    ColoredShape2(const string &color, Args ...args)
        : T(std::forward<Args>(srgs)...), color{color} {}
    string str() const override {
        stringstream oss;
        oss << T::str() << " has the color " << color;
        return oss.str();
    }
}

int main()
{
    Square square{5};
    ColoredShape red_square{square, "red"};
    cout << square.str() << endl << red_square.str() << endl;
    TransparentShape my_square{red_square, 51};
    cout << my_square.str() << endl;

    ColoredShape2<Circle> green_circle{"green", 5};
    cout << green_circle() << endl;


    return 0;
}
