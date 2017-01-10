//
//  Gale_Diagram.hpp
//  PolytopeProject
//
//  Created by Simon Van den Eynde on 10/01/17.
//  Copyright © 2017 Simon Van den Eynde. All rights reserved.
//

#ifndef Gale_Diagram_hpp
#define Gale_Diagram_hpp

#include <stdio.h>
#include "Point.hpp"
#include "Matrix.hpp"

class Gale_Diagram{
    vector<Point> points;
    Matrix matrix;
public:
    Gale_Diagram(vector<Point> points);
    
    //Maybe we can generate the points so that we don't have  to do this?
    bool check_simplicial(Gale_Diagram);
    
    bool check_neighborly(Gale_Diagram);
    
    //Checks wether the convex hull of the positive points intersects the convex hull of the negative points.
    bool check_intersect_plus_min(Gale_Diagram);
    
    void print(){
        matrix.print();
    }
};

#endif /* Gale_Diagram_hpp */
