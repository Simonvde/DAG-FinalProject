//
//  Point.hpp
//  PolytopeProject
//
//  Created by Simon Van den Eynde on 10/01/17.
//  Copyright © 2017 Simon Van den Eynde. All rights reserved.
//

#ifndef Point_hpp
#define Point_hpp

#include <stdio.h>
#include "iostream"
#include <vector>
#include <gmpxx.h>

using namespace std;


class Point{
    bool sign;
    vector<mpq_class> coordinates;
public:
    Point(vector<mpq_class> coord,bool sign);
    
    Point(vector<double> coord, bool sign);
    
    bool get_sign() const;
    vector<mpq_class> get_coordinates() const;
    
    //Note that we will present a vector with the Point class.
    Point point_to_vector(Point point);
    
    //returns true if all coordinates have the same sign.
    bool one_sign() const;
    
    //Substract the coordinates of point b from this point and return a new point
    Point minus (const Point &b) const;
    
    void print() const;
    
};


#endif /* Point_hpp */
