//Реализация иерарxии классов геометрическиx фигур
// и иерарxии классов Visiter, с помощью которой
// выводиться площадь этиx фигур.
//Geometry - базовый класс фигур.
//Triangle, Square, Circle - наследники Geometry.
//GetArea - наследник абстрактного класса Visit.

#include <iostream>
#include <cmath>

//Объявления
struct Square;
struct Triangle;
struct Circle;
struct Point;
struct Visitor;
struct GetArea;
//Длина линии по координатам двух точек
double getLineLen(Point p1, Point p2);

//Класс Visitor посещает фигуры Square, Triangle и Circle
struct Visitor{
    virtual void visit(Square const & s) const = 0;
    virtual void visit(Triangle const & t) const = 0;
    virtual void visit(Circle const & c) const = 0;
};

// Точка по двум координатам
struct Point{
    Point(int x, int y) : x(x), y(y) {}
    ~Point() = default;

    int x;
    int y;
};

struct Geometry{
    Geometry() = default;
    ~Geometry() = default;
    virtual void draw() const = 0;

    virtual void accept(Visitor const &v) const =0;
};

struct Square : Geometry{

    Square(Point p1, Point p2, Point p3, Point p4) : p1(p1), p2(p2), p3(p3), p4(p4) {}
    ~Square() = default;

    virtual void draw () const { std::cout << "drawing a Square..." << std::endl;}

    void accept(Visitor const &v) const {v.visit(*this);}

    Point p1;
    Point p2;
    Point p3;
    Point p4;
};

struct Triangle : Geometry{
    Triangle(Point p1, Point p2, Point p3) : p1(p1), p2(p2), p3(p3) {}
    ~Triangle() = default;

    virtual void draw () const { std::cout << "drawing a Triangle..." << std::endl;}

    void accept(Visitor const &v) const {v.visit(*this);}

    Point p1;
    Point p2;
    Point p3;
};

struct Circle : Geometry{
    Circle(Point p1, int r) : p1(p1), R(r) {}
    ~Circle() = default;

    virtual void draw () const { std::cout << "drawing a Circle..." << std::endl;}

    void accept(Visitor const &v) const {v.visit(*this);}

    Point p1;
    int R;
};

struct GetArea  : Visitor{
    void visit(Square const & s) const {
        std::cout << "Square area= " << getLineLen(s.p1, s.p2)*getLineLen(s.p3, s.p4) << std::endl;
    };
    void visit(Triangle const & t) const {
        // по формуле герона
        double a = getLineLen(t.p1, t.p2);
        double b = getLineLen(t.p1, t.p3);
        double c = getLineLen(t.p2, t.p3);

        double p = (a+b+c)/2;

        std::cout << "Triangle area= " << (double) sqrt(p*(p-a)*(p-b)*(p-c)) << std::endl;

    };
    void visit(Circle const & c) const {

        std::cout << "Circle area= " << 3.14*c.R*c.R << std::endl;
    };
};

double getLineLen(Point p1, Point p2)
{
    double tmpX = p2.x - p1.x;
    double tmpY = p2.y - p1.y;

    return sqrt(tmpX*tmpX + tmpY*tmpY);

}

int main()
{
    Square s = Square(Point (1,1), Point (1,3), Point(3,1), Point(3,3));
    Triangle t = Triangle(Point(5,5), Point(5,9), Point(10,7));
    Circle c = Circle(Point(10,5), 4);

    Geometry *g[] = {&s, &t, &c};

    GetArea a;

    for(int i=0; i<3; i++)
    {
        g[i]->draw();
        g[i]->accept(a);
        std::cout << std::endl;
    }

    return 0;
}
