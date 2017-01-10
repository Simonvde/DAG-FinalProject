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
            coord[j].canonicalize();
            matrix[j].push_back(coord[j]);
        }
    }
};

Matrix::Matrix(vector<mpq_class> array){
    for(int i=0; i<array.size(); i++){
        array[i].canonicalize();
        vector<mpq_class> vec = {array[i]};
        matrix.push_back(vec);
    }
}

Matrix::Matrix(vector<vector<mpq_class>> vec): matrix(vec){}

void Matrix::multiplyRow(vector<mpq_class> &row,mpq_class num){
    for(int i=0; i<row.size(); i++){
        mpq_class multiplied = row[i]*num;
        multiplied.canonicalize();
        row[i] = multiplied;
    }
}
void Matrix::subtractRows(const vector<mpq_class> high_row,vector<mpq_class> &low_row, mpq_class scalar){
    for(int i=0; i<high_row.size(); i++){
        mpq_class subtrahend = high_row[i]*scalar;
        subtrahend.canonicalize();
        mpq_class difference = low_row[i]-subtrahend;
        difference.canonicalize();
        low_row[i]=difference;
    }
}

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

void Matrix::pivot(int column_index){
    mpq_class max=abs(matrix[column_index][column_index]);
    int max_row = column_index;
    for(int i=column_index+1; i<rowDim(); i++){
        mpq_class next_num = abs(matrix[0][column_index]);
        if(next_num > max){
            max = next_num;
            max_row=i;
        }
    }
    if(max==0) throw runtime_error("Matrix is singular!");
    
    multiplyRow(matrix[max_row], 1/matrix[max_row][column_index]);
    
    swap(matrix[column_index],matrix[max_row]);
}

//Note: I also calculate the lower triangle (all zeroes), this can be optimised if necessary
void Matrix::rref(){
    for(int k=0; k<min(rowDim(),colDim()); k++){
        //Find pivot
        pivot(k);
        
        //Do for all the rows below the pivot
        for(int i=0; i<rowDim(); i++){
            if(i!=k && matrix[k][k]!=0){
                mpq_class multiplier = matrix[i][k]/matrix[k][k];
                multiplier.canonicalize();
                
                subtractRows(matrix[k], matrix[i], multiplier);
            }
        }
    }
}


void Matrix::testMatrix(){
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

    print();
    mpq_class t = mpq_class(13,17);
    multiplyRow(matrix[0],t);
    print();
    subtractRows(matrix[0],matrix[1],matrix[1][0]/matrix[0][0]);
    print();
    
    Point a1(vector<mpq_class>{mpq_class(1,2),mpq_class(1,3)},true);
    Point a2(vector<mpq_class>{mpq_class(1,3),mpq_class(1,5)},true);
    Point a3(vector<mpq_class>{mpq_class(19,17),mpq_class(13,12)},true);
    Matrix M(vector<Point>{a1,a2,a3});
    
    M.print();
    //M.pivot(0);
    //M.print();
    M.rref();
    M.print();
    
}
