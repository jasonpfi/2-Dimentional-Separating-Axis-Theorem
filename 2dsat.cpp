#include "2dsat.h"

/**
 * A basic Demonstration of the Separating Axis Theorem
 * 
 * Two shapes will be defined by their vertices in the XY coordinate plane
 * If the shapes are found to be intersecting, the program will output "Intersecting"
 * If the two shapes are not intersecting, the program will output "Not Intersecting"
 */

// false if there was an intersection, true if there is space
bool Projection::compareProjections(Projection p)
{
    if (this->getMin() <= p.getMax() || this->getMax() >= p.getMin()) return false;
    else return true;
}

void Shape::output(Shape s)
{
    if (this->compareShapeProjections(s)) std::cout << "Intersecting" << std::endl;
    else std::cout <<"Not Intersecting" << std::endl;
}

bool Shape::compareShapeProjections(Shape s)
{
    for (Vector n1 : this->getLNormals())
    {
        if (this->project(n1).compareProjections(s.project(n1))) return false;
    }

    for (Vector n2 : s.getLNormals())
    {
        if (this->project(n2).compareProjections(s.project(n2))) return false;
    }

    return true;
}

Projection Shape::project(Vector v)
{
    double min = std::numeric_limits<int>::max(), max = -100000;

    for (Point p : this->getPoints())
    {
        double out = v*p;
        if(out < min) min = out;
        else if(out > max) max = out;
    }

    return Projection(min, max);

}

void Shape::printAllPoints()
{
    std::for_each(this->pt.begin(), this->pt.end(), [](Point& element){
        std::cout << "X: " << element.getX() << ", Y: " << element.getY() << std::endl;});   
}

std::vector<Vector> Shape::getLNormals()
{
    std::vector<Vector> normals;
    std::for_each(this->pt.begin(), this->pt.end()-1, [&normals](Point& element){
        normals.push_back(Vector(element.getX() - (*(&element + 1)).getX(),
                                 element.getY() - (*(&element + 1)).getY()).Lnormalize());});
    // Compare first and last element - not done in loop
    normals.push_back(Vector((*(this->pt.begin())).getX() - (*(this->pt.end()-1)).getX(),
                             (*(this->pt.begin())).getY() - (*(this->pt.end()-1)).getY()).Lnormalize());
    return normals;
}

std::vector<Vector> Shape::getRNormals()
{
}

int main()
{
    Shape triangle = Shape({Point(0,0), Point(6,0), Point(3,6)});
    Shape square   = Shape({Point(3,0), Point(9,0), Point(9,6), Point(3,6)});
    Shape tri2     = Shape({Point(10,20), Point(30,40), Point(50,20)});
    Shape squ2     = Shape({Point(3,1), Point(6,4), Point(3,6), Point(1,1)});

    triangle.output(square);
    triangle.output(tri2);
    triangle.output(squ2);
    
}
