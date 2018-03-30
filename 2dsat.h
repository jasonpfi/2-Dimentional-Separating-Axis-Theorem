#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>
#include <algorithm>

/**
 * Header file for the Separating Axis Theorem in 2 Dimentions
 * 
 */

class Vector
{
protected:

    double x, y;

public:

    Vector() : x(0), y(0) {};
    Vector(double x, double y): x(x), y(y) {};

    double operator*(Vector& v)
    {
        return this->getX() * v.getX() + this->getY() * v.getY();
    }

    double getX() {return x;}
    double getY() {return y;}

    void setX(double x) {this->x = x;}
    void setY(double y) {this->y = y;}

    void printVector() {std::cout << x << ", " << y << "\n" << std::endl;}

    Vector Lnormalize() {double i = x; this->setX(-y/sqrt(i*i + y*y)); this->setY(i/sqrt(i*i + y*y)); return *this;};
    Vector Rnormalize() {x = y; y = -x;};
};

class Point : public Vector
{
    /**
     * A point is a Vector from the Normal
     */

public:

    Point() : Vector() {}
    Point(int x, int y) : Vector(x, y) {}
    ~Point() {}

};

// x is min, y is max
class Projection : public Vector
{

public:

    Projection() : Vector() {};
    Projection(double min, double max) : Vector(min, max) {};

    double getMax() {return y;}
    double getMin() {return x;}

    bool compareProjections(Projection p);
    double getOverlap(Projection p);
};

// Minimum Translation Vector
class MVT 
{
    double overlap;
    Vector axis;
public:

    MVT() : overlap(0), axis(Vector()) {};
    MVT(double o, Vector a) : overlap(o), axis(Vector(a)) {};

    double returnOverlap() {return overlap;};
    Vector returnAxis() {return axis;};
};

class Shape 
{
    std::vector<Point> pt;
    std::string type;

public:

    Shape() {}
    Shape(std::vector<Point> pt) : pt(pt) {}
    ~Shape() {}

    std::vector<Point> getPoints() {return pt;}
    Point getPoint(int index) {return pt[index];}
    void addPoint(Point p) {pt.push_back(p);}

    std::string getType() {return type;}
    std::vector<Vector> getLNormals();
    std::vector<Vector> getRNormals();

    Projection project(Vector v);
    MVT compareShapeProjections(Shape s);

    void printAllPoints();
    void output(Shape s);

};


