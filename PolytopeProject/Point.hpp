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
#include <vector>
#include <gmpxx.h>

using namespace std;


class Point{
    bool sign;
    vector<mpq_class> coordinates;
public:
    Point(vector<mpq_class> coord,bool sign);
    
    Point(vector<double> coord, bool sign);
    
    bool get_sign();
    vector<mpq_class> get_coordinates();
    
    //Note that we will present a vector with the Point class.
    Point point_to_vector(Point point);
    
    //returns true if all coordinates have the same sign.
    bool one_sign();
    
};


#endif /* Point_hpp */
