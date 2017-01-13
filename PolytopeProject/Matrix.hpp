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
    
    void multiplyRow(vector<mpq_class> &row,mpq_class num);
    
    //Subtract high_row*scalar from low_row.
    void subtractRows(const vector<mpq_class> high_row,vector<mpq_class> &low_row, mpq_class scalar);
    
    /*Given the current column/row (its the same) we are looking for, find the maximum element in the column and swap that row with the current row.
    Returns a point with the value of the pivot and as sign if rows were changed*/
    Point pivot(int column_index);
    
    /*Brings the matrix in reduced row echelon form.
     Returns the determinant if the matrix was square.*/
    mpq_class rref();
public:
    Matrix(vector<Point> points);
    
    //Make a n*1 matrix.
    Matrix(vector<mpq_class> array);
    
    Matrix(vector<vector<mpq_class> > vec);
    
    void invert();
    
    vector<Point> get_kernel();
    
    inline mpq_class get(int row,int col);
    int rowDim();
    int colDim();
    
    //Multiplies this matrix with B and returns the result
    Matrix multiply(Matrix B);
    
    void print();
    
    void testMatrix();
    
    mpq_class determinant();
};


#endif /* Matrix_hpp */
