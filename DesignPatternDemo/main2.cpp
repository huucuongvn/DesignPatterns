#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>
using namespace std;
using namespace boost;

class Rectangle{
protected:
    int width,height;
public:
    Rectangle(int width, int height)
        :width(width), height(height){};
    int getWidth() const {
        return width;
    }
    virtual void setWidth(int width) {
        Rectangle::width=width;
    }
    int getHeight() const {
        return height;
    }
    virtual void setHeight(int height) {
        Rectangle::height=height;
    }
    int area() const {
        return (width*height);
    }

};

void process(Rectangle &r) {
    int w=r.getWidth();
    r.setHeight(10);
    cout << "expected area = " << (w*10) << " ,got " << r.area() << endl;
}

class Square : public Rectangle {
public:
    Square(int size): Rectangle(size,size) {}
    void setWidth(int width) override {
        this->width = this->height = width;
    }
    void setHeight(int height) {
        this->width = this->height = height;
    }
};

struct RectangleFactory{
    static Rectangle creat_rectangle(int w, int h);
    static Rectangle creat_square(int size);
};

int main()
{
    Rectangle r{3,4};
    process(r);
    Square sq{5};
    process(sq);
    return 0;
}
