//
//  main.cpp
//  PolytopeProject
//
//  Created by Simon Van den Eynde on 26/12/16.
//  Copyright © 2016 Simon Van den Eynde. All rights reserved.
//

#include <iostream>
#include <gmp.h>
#include <stdio.h>
#include <vector>
#include <gmpxx.h>
#include "Point.hpp"
#include "Matrix.hpp"
#include "Gale_Diagram.hpp"

using namespace std;

//Test that GMP works
void tests();

class Point;

class Gale_Diagram;

class Matrix;


//Returns an array with all valid (neighborly and simplicial and non-isomorphic) gale diagrams
vector<Gale_Diagram> enumerate_all_gale();

vector<Point> gale_to_polytope(Gale_Diagram);

vector<vector<Point>> enumerate_all_polytope();



void testGMP(){
    mpz_class a, b, c;
    
    a = 1234;
    b = "-5678";
    c = a+b;
    cout<<c.get_d();
}

void testInitialisers(){
    mpq_class q (99);
    
    vector<double> vec1= {1,2,3,4};
    Point point1(vec1,true);
    vector<double> vec2= {4,5,6,7};
    Point point2(vec2,true);
    vector<double> vec3= {5,2,1,9};
    Point point3(vec3,true);
    
    
    vector<Point> vec = {point1,point2,point3};
    Gale_Diagram gd(vec);
    
    gd.print();
}

void tests(){
    //testGMP();
    //testInitialisers();
    
    Point v1(vector<mpq_class>{1,2,1},true);
    Point v2(vector<mpq_class>{2,1,1},false);
    Point v3(vector<mpq_class>{2,-1,1},true);
    Point v4(vector<mpq_class>{1,-2,1},false);
    Point v5(vector<mpq_class>{-1,-2,1},true);
    Point v6(vector<mpq_class>{-2,-1,1},false);
    Point v7(vector<mpq_class>{-2,1,1},true);
    Point v8(vector<mpq_class>{-1,2,1},false);
    
    //Gale_Diagram C47 = Gale_Diagram(vector<Point>{v1,v2,v3,v4,v5,v6,v7,v8});
    
    //C47.print();
    
    //cout << C47.is_neighborly() << endl;
    
    Matrix matrix(vector<Point>{v5,v6,v7,v8});
    matrix.print();
    vector<Point> vec = matrix.get_kernel();
    Matrix(vec).print();
    matrix.testMatrix();
}


int main(int argc, const char * argv[]) {
    tests();
    
    
    
    //example, still has to be implemented:
    //bool simplicial = Gale_Diagram::check_simplicial(gd);
    

    return 0;
}



