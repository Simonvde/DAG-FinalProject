//
//  intersectionsTest.hpp
//  PolytopeProject
//
//  Created by Simon Van den Eynde on 14/01/17.
//  Copyright © 2017 Simon Van den Eynde. All rights reserved.
//

#ifndef intersectionsTest_hpp
#define intersectionsTest_hpp

#include <stdio.h>

#include <iostream>
#include <gmp.h>
#include <stdio.h>
#include <vector>
#include <gmpxx.h>
#include <stdio.h>
#include "Point.hpp"
#include "Gale_Diagram.hpp"

using namespace std;

class Point;

typedef vector<mpq_class> V;
typedef vector<V> VV;
typedef vector<Point> VP;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<bool> VB;
typedef vector<VB> VVB;
typedef vector<Gale_Diagram> VGD;



class Intersections{
    int number_diagrams;
    int number_simplicial;
    int number_neighborly;
    VVI all_p_combinations;
    VVB all_s_combinations;
    
    void sign_combinations(VB& v, int n, int ps, int ns);

    void p_combinations(VI& v, VB& b, const Point& p, const Point& q, int n);
    
public:
    void printNeighbourly();
};

#endif /* intersectionsTest_hpp */

