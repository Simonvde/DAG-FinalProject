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

void testMatrix(){
    Point p1(vector<double>{1,2},true);
    Point p2(vector<double>{3,7},true);
    Point p3(vector<double>{5,1},true);
    
    Matrix A(vector<Point> {p1,p2,p3});
    
    Point q1(vector<double>{1,3,5},true);
    Point q2(vector<double>{2,4,6},true);
    
    Matrix B(vector<Point> {q1,q2});
    
    Matrix D(vector<mpq_class>{mpq_class(19,3102),mpq_class(128,127893)});
    
    A.print();
    B.print();
    Matrix C=A.multiply(B);
    C.print();
    D.print();
    C.multiply(D).print();
}

void tests(){
    //testGMP();
    //testInitialisers();
    testMatrix();
}


int main(int argc, const char * argv[]) {
    tests();
    
    
    
    //example, still has to be implemented:
    //bool simplicial = Gale_Diagram::check_simplicial(gd);
    

    return 0;
}



