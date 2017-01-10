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

using namespace std;

//Test that GMP works
void testGMP();

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



class Point{
    bool sign;
    vector<mpq_class> coordinates;
public:
    Point(vector<mpq_class> coord,bool sign):sign(sign),coordinates(coord){}
    
    Point(vector<double> coord, bool sign):sign(sign){
        for(double dob : coord){
            mpq_class q(dob);
            coordinates.push_back(q);
        }
    }
    
    bool get_sign(){return sign;}
    vector<mpq_class> get_coordinates(){return coordinates;}
    
    //Note that a vector can be represented with the point-class
    Point point_to_vector(Point point);

};


class Matrix{
private:
    vector<vector<mpq_class>> matrix;

    void Gauss(Matrix matrix);

public:
    Matrix(vector<Point> points){
        for(int i=0; i<points[0].get_coordinates().size(); i++){
            matrix.push_back(*new vector<mpq_class>());
        }
        
        for(int i=0; i<points.size(); i++){
            vector<mpq_class> coord = points[i].get_coordinates();
            for(int j=0; j<coord.size(); j++){
                matrix[j].push_back(coord[j]);
            }
        }
    };
    Matrix(vector<mpq_class> array);
    
    void invert();
    
    void get_kernel();
    
    //Multiplies this matrix with B
    void multiply(Matrix B);
    
    void print(){
        cout<<endl;
        for(int i=0; i<matrix.size(); i++){
            for(int j=0; j<matrix[i].size(); j++){
                cout << matrix[i][j].get_d() << " ";
            }
            cout<<endl;
        }
    }
};


class Gale_Diagram{
    vector<Point> points;
    Matrix matrix;
public:
    Gale_Diagram(vector<Point> points): points(points),matrix(Matrix(points)){
    };
    
    //Maybe we can generate the points so that we don't have  to do this?
    bool check_simplicial(Gale_Diagram);
    
    bool check_neighborly(Gale_Diagram);
    
    //Checks wether the convex hull of the positive points intersects the convex hull of the negative points.
    bool check_intersect_plus_min(Gale_Diagram);
    
    void print(){
        matrix.print();
    }
};





int main(int argc, const char * argv[]) {
    testGMP();
    
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
    
    //example, still has to be implemented:
    //bool simplicial = Gale_Diagram::check_simplicial(gd);
    

    return 0;
}



