//
//  polygons.h
//  hw10
//
//  Created by KEXIN ZHU on 12/3/16.
//  Copyright © 2016 KEXIN ZHU. All rights reserved.
//

#ifndef polygons_h
#define polygons_h
#include <vector>
#include "utilities.h"
#include <string>
using namespace std;

/**
 According to the diagram we draw to write the relationship between different
 polygons.If it is not the polygon's character,constructor failed,throw an integer
 and go to the next polygon
 */
//base case: with two members variable and derived other class.
class Polygon{
public:
    Polygon(const string name,const vector<Point>& points) {
        name_ = name;
        points_ = points;
    }
    string getName(){return  name_;}
    //implmented in cpp
    bool HasAllEqualSides();
    bool HasAllEqualAngles();
    bool HasARightAngle();
    bool HasAnObtuseAngle();
    bool HasAnAcuteAngle();
    bool IsConvex();
    bool IsConcave();
    bool HasTwoEqualSides();//if there are at least two sides equal
    virtual ~Polygon() {}//destructor
protected:
    //for future in the derived class
    vector<Point> points_;
    string name_;
};

        //if it does not have 3 vertex
class Triangle: public Polygon{
public:
    Triangle(const string &name,const vector<Point>& points):
    Polygon(name,points){
        if (points.size() != 3) {
            throw 1;
        }
    }

};

    //if it does not 4 vertex
class Quadrilateral:public Polygon{
public:
    Quadrilateral(const string &name,const vector<Point>& points):
    Polygon(name,points){
        if (points.size() != 4) {
            throw 1;
        }
    }

};


//a triangle which has an obtuse angle
class ObtuseTriangle: virtual public Triangle{
public:
    ObtuseTriangle(const string &name,const vector<Point> &points):
    Triangle(name,points){
        if (!HasAnObtuseAngle()) {
            throw 1;
        }
    }


};


//a triangle which has two equal sides
class IsoscelesTriangle:virtual public Triangle{
public:
    IsoscelesTriangle(const string &name,const vector<Point> &points):
    Triangle(name,points){
        if (!HasTwoEqualSides()) {
            throw 1;
        }
    }
};


//A triangle has a right angle
class RightTriangle: virtual public Triangle{
public:
    RightTriangle(const string &name,const vector<Point> &points):
    Triangle(name,points){
        if (!HasARightAngle()) {
            throw 1;
        }
    }
};



//A triangle has two equal sieds and an obtuse angle
class IsoscelesObtuseTriangle: public ObtuseTriangle,public IsoscelesTriangle{
public:
    IsoscelesObtuseTriangle(const string& name,const vector<Point> &points):
    Triangle(name,points),ObtuseTriangle(name,points), IsoscelesTriangle(name,points){
        if (!(HasTwoEqualSides() && HasAnObtuseAngle())) {
            throw 1;
        }
        
    }
};


//has all equal sides and angles
class EquilateralTriangle: public IsoscelesTriangle{
public:
    EquilateralTriangle(const string &name,const vector<Point> &points):
    Triangle(name,points),IsoscelesTriangle(name,points){
        if (!(HasAllEqualSides()&& HasAllEqualAngles())) {
            throw 1;
        }
    }
};


//has two equal sides and an right angle
class IsoscelesRightTriangle: public RightTriangle, public IsoscelesTriangle{
public:
    IsoscelesRightTriangle(const string &name, const vector<Point> &points):
    Triangle(name,points),RightTriangle(name,points),IsoscelesTriangle(name,points){
        if (!(HasARightAngle() && HasTwoEqualSides())) {
            throw 1;
        }
        
    }
};

//it is concave and its two adjacent sides are equal
class Arrow:public Quadrilateral{
public:
    Arrow(const string& name,const vector<Point> &points):Quadrilateral(name,points){
        if (!IsConcave()) {
            throw 1;
        }
        //compute all the lines distance
        vector<double> lines;
        for (int i = 0; i<points_.size()-1; i++) {
            lines.push_back(DistanceBetween(points_[i], points_[i+1]));
        }
        lines.push_back(DistanceBetween(points_[points_.size()-1],points_[0]));
        if (!((EqualSides(lines[0], lines[1])&&EqualSides(lines[2], lines[3])) ||
              (EqualSides(lines[1], lines[2])&&EqualSides(lines[0], lines[3]))) ) {
            throw 1;
        }

    }
};


//if two of the sides are parallel
class Trapezoid:virtual public Quadrilateral{
public:
    Trapezoid(const string& name,const vector<Point> &points):
    Quadrilateral(name,points){
        //if none of the lines are parallel, fail.
        if (!(Parallel(Vector(points[0], points[1]),
                       Vector(points[2], points[3])) ||
              Parallel(Vector(points[0], points[3]),
                       Vector(points[1], points[2])))){
            throw 1;
        }
    }
};


//it is convex and its two adjacent sides are equal
class Kite:virtual public Quadrilateral{
public:
    Kite(const string& name,const vector<Point> &points):Quadrilateral(name,points){
        //compute all the lines distance
        if (!IsConvex()) {
        throw 1;
    }
        vector<double> lines;
        for (int i = 0; i<points_.size()-1; i++) {
            lines.push_back(DistanceBetween(points_[i], points_[i+1]));
        }
        lines.push_back(DistanceBetween(points_[points_.size()-1],points_[0]));
        if (!((EqualSides(lines[0], lines[1])&&EqualSides(lines[2], lines[3])) ||
              (EqualSides(lines[1], lines[2])&&EqualSides(lines[0], lines[3]))) ) {
            throw 1;
        }

    }
};




//if two angles are the same, since it is already a trapeziod, then just need
//to find same angles
class IsoscelesTrapezoid:virtual public Trapezoid{
public:
    IsoscelesTrapezoid(const string& name,const vector<Point> &points):
    Quadrilateral(name,points),Trapezoid(name,points){
        vector<double> angles;
        for (int i = 0; i<points_.size()-2; i++) {
            angles.push_back(Angle(points_[i],points_[i+1],points_[i+2]));
        }
        angles.push_back(Angle(points_[points_.size()-2], points_[points_.size()-1],
                               points_[0]));
        angles.push_back(Angle(points_[points_.size()-1], points_[0], points_[1]));
        for (int i = 0; i<angles.size(); i++) {
            if (!(EqualAngles(angles[0],angles[1]) ||EqualAngles(angles[1],angles[2]))) {
                throw 1;
            }
        }
    }
};


//2 sets of sides are parallel
class Parallelogram:virtual public Trapezoid{
public:
    Parallelogram(const string& name,const vector<Point>& points):
    Quadrilateral(name,points),Trapezoid(name,points){
        //compute all the lines distance
        vector<double> lines;
        for (int i = 0; i<points_.size()-1; i++) {
            lines.push_back(DistanceBetween(points_[i], points_[i+1]));
        }
        lines.push_back(DistanceBetween(points_[points_.size()-1],points_[0]));
        if (!(EqualSides(lines[0],lines[2])&& EqualSides(lines[1],lines[3]))) {
            throw 1;
        }

    }
};


//has 1  right angles,since it depends on parallelogram, it will have 4 right
//angles
class Rectangle: virtual public Parallelogram, public IsoscelesTrapezoid{
public:
    Rectangle(const string & name,const vector<Point>& points): Quadrilateral
    (name,points),Trapezoid(name,points),
    Parallelogram(name,points),IsoscelesTrapezoid(name,points){
        if (!HasARightAngle()) {
            throw 1;
        }
    }
};


//has all equal sides
class Rhombus: virtual public Parallelogram, public Kite{
public:
    Rhombus(const string & name,const vector<Point>& points):
    Quadrilateral(name,points), Trapezoid(name,points),
    Parallelogram(name,points),Kite(name,points){
        if (!HasAllEqualSides()) {
            throw 1;
        }
    }
};

//has all equal sides and all equal angles
class Square: public Rectangle,public Rhombus{
public:
    Square(const string& name, const vector<Point>& points):
    Quadrilateral(name,points),Trapezoid(name,points),
    Parallelogram(name,points),Rectangle(name,points),Rhombus(name,points){
        //if it does not have equal sides and equal angles
        if (!(HasAllEqualSides() && HasAllEqualAngles())) {
            throw 1;
        }
    }
};


#endif /* polygons_h */
