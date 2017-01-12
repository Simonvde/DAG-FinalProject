//
//  Point.cpp
//  PolytopeProject
//
//  Created by Simon Van den Eynde on 10/01/17.
//  Copyright © 2017 Simon Van den Eynde. All rights reserved.
//

#include "Point.hpp"


Point::Point(vector<mpq_class> coord,bool sign):sign(sign),coordinates(coord){}

Point::Point(vector<double> coord, bool sign):sign(sign){
    for(double dob : coord){
        mpq_class q(dob);
        coordinates.push_back(q);
    }
}

bool Point::get_sign(){
    return sign;
}

vector<mpq_class> Point::get_coordinates(){return coordinates;}

bool Point::one_sign(){
    int tempsgn = sgn(coordinates[0]);
    for(int i=1; i<coordinates.size(); i++){
        if(tempsgn == sgn(coordinates[i])){
        } else return false;
    }
    return true;
}

Point point_to_vector(Point point){
    throw runtime_error("Still has to be implemented!!!");
}
