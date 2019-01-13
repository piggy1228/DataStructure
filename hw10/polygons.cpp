//
//  polygons.cpp
//  hw10
//
//  Created by KEXIN ZHU on 12/3/16.
//  Copyright © 2016 KEXIN ZHU. All rights reserved.
//

#include "polygons.h"

/**
 first using all the points to compute all the sides length and store them in 
 the vectors, then compare all the sides in the vectors,if find there is
 two sides does not equal, return false.
 */
bool Polygon::HasAllEqualSides(){
    //compute all the lines distance
    vector<double> lines;
    for (int i = 0; i<points_.size()-1; i++) {
        lines.push_back(DistanceBetween(points_[i], points_[i+1]));
    }
    lines.push_back(DistanceBetween(points_[points_.size()-1],points_[0]));
    //compare them,if two sides are different,constructor fail
    for (int i = 0; i<lines.size()-1; i++) {
        if (!EqualSides(lines[i],lines[i+1])) {
            return false;
        }
    }
    return true;
}

/**
 first using all the points to compute all the angles and store them in
 the vectors, then compare all the angles in the vectors,if find there is
 two angles does not equal, return false.
 */
bool Polygon::HasAllEqualAngles(){
    //compute all the angles
    vector<double> angles;
    for (int i = 0; i<points_.size()-2; i++) {
        angles.push_back(Angle(points_[i],points_[i+1],points_[i+2]));
    }
    angles.push_back(Angle(points_[points_.size()-2], points_[points_.size()-1],
                           points_[0]));
    angles.push_back(Angle(points_[points_.size()-1], points_[0], points_[1]));
    //compare the angles, if two angles are different, constructor fail
    for (int i = 0; i<angles.size()-1; i++) {
        if (!EqualAngles(angles[i], angles[i+1])) {
            return  false;
        }
    }
    return true;
}


bool Polygon::HasARightAngle(){
    //compute all the angles
    vector<double> angles;
    for (int i = 0; i<points_.size()-2; i++) {
        angles.push_back(Angle(points_[i],points_[i+1],points_[i+2]));
    }
    angles.push_back(Angle(points_[points_.size()-2], points_[points_.size()-1],
                           points_[0]));
    angles.push_back(Angle(points_[points_.size()-1], points_[0], points_[1]));
    //if in all angles, there is right angle
    for (int i = 0; i<angles.size(); i++) {
        if (RightAngle(angles[i])) {
            return true;
        }
    }
    return false;
}


bool Polygon::HasAnObtuseAngle(){
    //compute all the angles,and store them in the vector
    vector<double> angles;
    for (int i = 0; i<points_.size()-2; i++) {
        angles.push_back(Angle(points_[i],points_[i+1],points_[i+2]));
    }
    angles.push_back(Angle(points_[points_.size()-2], points_[points_.size()-1],
                           points_[0]));
    angles.push_back(Angle(points_[points_.size()-1], points_[0], points_[1]));
    //in all the angles, there is obtuse angle
    for (int i = 0; i<angles.size(); i++) {
        if (ObtuseAngle(angles[i])) {
            return true;
        }
    }
    return false;
}

bool Polygon::HasAnAcuteAngle(){
    //compute all the angles
    vector<double> angles;
    for (int i = 0; i<points_.size()-2; i++) {
        angles.push_back(Angle(points_[i],points_[i+1],points_[i+2]));
    }
    angles.push_back(Angle(points_[points_.size()-2], points_[points_.size()-1],
                           points_[0]));
    angles.push_back(Angle(points_[points_.size()-1], points_[0], points_[1]));
    //in all the angle, there is acute angle
    for (int i = 0; i<angles.size(); i++) {
        if (AcuteAngle(angles[i])) {
            return true;
        }
    }
    return false;
}

bool Polygon::HasTwoEqualSides(){
    //compute all the lines distance
    vector<double> lines;
    for (int i = 0; i<points_.size()-1; i++) {
        lines.push_back(DistanceBetween(points_[i], points_[i+1]));
    }
    //deal with the last line in the vector
    lines.push_back(DistanceBetween(points_[points_.size()-1],points_[0]));
    //if find equal sides, return true
    for (int i = 0; i<lines.size(); i++) {
        for (int j = 0; j<lines.size(); j++) {
            if (i == j) {
                continue;
            }
            if (EqualSides(lines[i], lines[j])) {
                return true;
            }
        }
    }

    return false;
}



//all angles should be smaller than 180 degree
bool Polygon::IsConvex(){
    //compute all the angles
    vector<double> angles;
    for (int i = 0; i<points_.size()-2; i++) {
        angles.push_back(Angle(points_[i],points_[i+1],points_[i+2]));
    }
    //deal with last two angles in the vector. Since it may exceed the size in
    //for loop
    angles.push_back(Angle(points_[points_.size()-2], points_[points_.size()-1],
                           points_[0]));
    angles.push_back(Angle(points_[points_.size()-1], points_[0], points_[1]));
    //if one angle is reflex angle, throw it
    for (int i = 0; i<angles.size(); i++) {
        if (ReflexAngle(angles[i])) {
            return false;
        }
    }
    return true;
}


//if there is one reflex angle, it is concave
bool Polygon::IsConcave(){
    //compute all the angles and store them in the vector
    vector<double> angles;
    for (int i = 0; i<points_.size()-2; i++) {
        angles.push_back(Angle(points_[i],points_[i+1],points_[i+2]));
    }
    angles.push_back(Angle(points_[points_.size()-2], points_[points_.size()-1],
                           points_[0]));
    angles.push_back(Angle(points_[points_.size()-1], points_[0], points_[1]));
    //if there is reflex angle in all angles
    for (int i = 0; i<angles.size(); i++) {
        if (ReflexAngle(angles[i])) {
            return true;
        }
    }
    return false;
}



