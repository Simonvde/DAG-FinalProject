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
    
    vector<int> findMissing(int i, int j, int k,int l);
    
    //Does NOT check for degeneracies
    //returns -1 if x lies on the right of the oriented line ab, otherwise +1;
    int orientation(Point x, Point a, Point b);
    
    //Checks if onePoint lies in the triangle defined by threePoints
    bool in_triangle(vector<Point> onePoint, vector<Point> triangle);
    
    // returns whether both linesegments (vectors of size 2) intersect.
    bool intersectingLineSegments(vector<Point> lineSegment1, vector<Point> lineSegment2);
    
    bool check_intersecting(vector<Point> points);
    
    bool isSimplex(int i, int j, int k, int l);
public:
    Gale_Diagram(vector<Point> points);
    
    bool is_neighborly();
    
    //Checks wether the convex hull of the positive points intersects the convex hull of the negative points.
    bool is_intersect_plus_min();
    
    bool is_isomorphic(const Gale_Diagram&);
    
    void print(){
        matrix.print();
    }
    
    //Make the facet-graph.
    void makeVertexFacetStructure();
    
    bool isSimplicial();
    
    void test();
};

#endif /* Gale_Diagram_hpp */
