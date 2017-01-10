//
//  Matrix.hpp
//  PolytopeProject
//
//  Created by Simon Van den Eynde on 10/01/17.
//  Copyright © 2017 Simon Van den Eynde. All rights reserved.
//

#ifndef Matrix_hpp
#define Matrix_hpp

#include <stdio.h>
#include "Point.hpp"
#include "iostream"
#include <vector>
#include <gmpxx.h>

using namespace std;

class Matrix{
private:
    vector<vector<mpq_class>> matrix;
    
    void Gauss(Matrix matrix);
    
public:
    Matrix(vector<Point> points);
    
    //Make a n*1 matrix.
    Matrix(vector<mpq_class> array);
    
    Matrix(vector<vector<mpq_class>> vec);
    
    void invert();
    
    void get_kernel();
    
    inline mpq_class get(int row,int col);
    mpq_class rowDim();
    mpq_class colDim();
    
    //Multiplies this matrix with B and returns the result
    Matrix multiply(Matrix B);
    
    void print();
    
};


#endif /* Matrix_hpp */
