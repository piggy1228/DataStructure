//
//  main.cpp
//  lab4
//
//  Created by KEXIN ZHU on 9/20/16.
//  Copyright © 2016 KEXIN ZHU. All rights reserved.
//
#include "Rectangle.h"
#include <iostream>
#include <vector>
#include "Point2D.h"
#include <algorithm>

using namespace std;
int main(int argc, const char * argv[]) {
    Point2D p1(1, 2);
    Point2D p2(5, 7);
    Point2D pt(10,20);
   // pt.x();
    //pt.y();
    pt.set(12, 12);
    Rectangle r(p1, p2);
    cout<<"lower left corner ("<<r.lower_left_corner().x()<<" , "<<r.lower_left_corner().y()<<")"<<endl;
    cout<<"upper right corner("<<r.upper_right_corner().x()<<" , "<<r.upper_right_corner().y()<<")"<<endl;
    Point2D p3(2,4);
    Point2D p4(10,20);
    Point2D p5(2,6);
    Point2D p6(4,80);
    Point2D p7(1,1);
    Point2D p8(30,30);
    Rectangle r0(p7,p8);
    r0.add_point(p5);
    r0.add_point(p6);
    r0.add_point(p1);
    r0.add_point(p3);
    cout<<"if point is within "<<r.is_point_within(p3)<<endl;
    cout<<"if point is within "<<r.is_point_within(p4)<<endl;
    cout<<"can add the point "<<r.add_point(p5)<<endl;
    cout<<"can add the point "<<r.add_point(p6)<<endl;
    vector<Point2D> point_in_both;

    point_in_both = points_in_both(r, r0);
    for (int i=0; i<point_in_both.size(); i++) {
        cout<<"point in both are "<<"x: "<<point_in_both[i].x()<<" and y: "<<point_in_both[i].y()<<endl;
    }
    print_rectangle(r);
    return 0;
}
