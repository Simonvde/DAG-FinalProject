//
//  Gale_Diagram.cpp
//  PolytopeProject
//
//  Created by Simon Van den Eynde on 10/01/17.
//  Copyright © 2017 Simon Van den Eynde. All rights reserved.
//

#include "Gale_Diagram.hpp"



Gale_Diagram::Gale_Diagram(vector<Point> points): points(points),matrix(Matrix(points)){
};

bool Gale_Diagram::is_neighborly(){
    //Choose 2 points
    for(int i=0; i<points.size()-1; i++){
        for(int j=i+1; j<points.size(); j++){
            
            bool edgeIJPresent=false;
            
            
            //Then choose another 2
            for(int k=0; k<points.size()-3; k++){
                for(int l=k+1; l<points.size()-2; l++){
                    
                    //Remove the columns i,j,k,l by selecting the other columns:
                    vector<int> pointIndices = findMissing(i,j,k,l);
                    //Select points
                    vector<Point> fourPoints;
                    for(int m=0; m<pointIndices.size(); m++) fourPoints.push_back(points[pointIndices[m]]);
                    
                    Matrix m = Matrix(fourPoints);
                    vector<Point> kernel = m.get_kernel();
                    edgeIJPresent = kernel[0].one_sign();
                    
                    if(edgeIJPresent) goto skipLoop;
                    
                }
            }
            
            skipLoop:
            if(!edgeIJPresent){
                return false;
            }
        }
        
    }
    return true;
}

vector<int> Gale_Diagram::findMissing(int i, int j, int k, int l){
    vector<int> pointNums(points.size());
    for(int a=0; a<points.size(); a++) pointNums[a]=a;

    pointNums.erase(pointNums.begin()+j-1);
    pointNums.erase(pointNums.begin()+i-1);
    pointNums.erase(pointNums.begin()+l-1);
    pointNums.erase(pointNums.begin()+k-1);
    
    return pointNums;
}
