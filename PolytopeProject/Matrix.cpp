//
//  Matrix.cpp
//  PolytopeProject
//
//  Created by Simon Van den Eynde on 10/01/17.
//  Copyright © 2017 Simon Van den Eynde. All rights reserved.
//

#include "Matrix.hpp"

Matrix::Matrix(vector<Point> points){
    for(int i=0; i<points[0].get_coordinates().size(); i++){
        matrix.push_back(vector<mpq_class>());
    }
    
    for(int i=0; i<points.size(); i++){
        vector<mpq_class> coord = points[i].get_coordinates();
        for(int j=0; j<coord.size(); j++){
            matrix[j].push_back(coord[j]);
        }
    }
};

Matrix::Matrix(vector<mpq_class> array){
    for(int i=0; i<array.size(); i++){
        vector<mpq_class> vec = {array[i]};
        matrix.push_back(vec);
    }
}

Matrix::Matrix(vector<vector<mpq_class>> vec): matrix(vec){}

void Matrix::invert(){throw new runtime_error("Not implemented");}

void Matrix::get_kernel(){throw new runtime_error("Not implemented");}

inline mpq_class Matrix::get(int row,int col){ return matrix[row][col];}
mpq_class Matrix::rowDim(){return matrix.size();}
mpq_class Matrix::colDim(){return matrix[0].size();}

//Multiplies this matrix with B and returns the result
Matrix Matrix::multiply(Matrix B){
    if(colDim()!=B.rowDim()){ throw runtime_error("Wrong Matrix Dimension");}
    
    vector<vector<mpq_class>> C;
    
    for(int i=0; i<rowDim(); i++){
        vector<mpq_class> row;
        for(int j=0; j<B.colDim(); j++){
            mpq_class sum=0;
            for(int k=0; k<colDim();k++){
                sum = sum + matrix[i][k]*B.get(k,j);
            }
            sum.canonicalize();
            row.push_back(sum);
        }
        C.push_back(row);
    }
    return Matrix(C);
}

void Matrix::print(){
    cout<<endl;
    for(int i=0; i<matrix.size(); i++){
        for(int j=0; j<matrix[i].size(); j++){
            cout << matrix[i][j].get_d() << " ";
        }
        cout<<endl;
    }
}
