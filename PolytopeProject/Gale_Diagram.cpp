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
                

                    edgeIJPresent = isSimplex(i, j, k, l);
                    
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


//Does NOT check for degeneracies
//returns -1 if x lies on the right of the oriented line ab, otherwise +1;
int Gale_Diagram::orientation(Point x, Point a, Point b){
    Matrix M = Matrix(vector<Point>{b.minus(a),x.minus(a)});
    return sgn(M.determinant());
}
//Checks if onePoint lies in the triangle defined by threePoints
bool Gale_Diagram::in_triangle(vector<Point> onePoint, vector<Point> triangle){
    Point x=onePoint[0];
    Point a=triangle[0];
    Point b=triangle[1];
    Point c=triangle[2];
    int o1 = orientation(x,a,b);
    int o2 = orientation(x,b,c);
    int o3 = orientation(x, c,a);
    return o1==o2 && o2 == o3;
}
// returns whether both linesegments (vectors of size 2) intersect.
bool Gale_Diagram::intersectingLineSegments(vector<Point> lineSegment1, vector<Point> lineSegment2){
    Point a=lineSegment1[0];
    Point b=lineSegment1[1];
    Point c=lineSegment2[0];
    Point d=lineSegment2[1];
    int o1 = orientation(a, c, d);
    int o2 = orientation(b,c,d);
    int o3 = orientation(c,a,b);
    int o4 = orientation(d,a,b);
    return o1!=o2 && o3!=o4;
}
bool Gale_Diagram::check_intersecting(vector<Point> points){
    if(points.size()!=4) throw runtime_error("Wrong Size in check_intersecting, Gale_diagram");
    
    vector<Point> positives;
    vector<Point> negatives;
    for(Point p : points){
        if(p.get_sign()) positives.push_back(p);
        else negatives.push_back(p);
    }
    int s = positives.size();
    if(s==0 || s==4) return false;
    if(s==1) return in_triangle(positives, negatives);
    if(s==2) return intersectingLineSegments(positives, negatives);
    return in_triangle(negatives, positives);
    return true;
}

void Gale_Diagram::test(){
    Point a(vector<double>{0,0},true);
    Point b(vector<double>{0,1},true);
    Point c(vector<double>{1,0},true);
    Point d(vector<double>{0,-1},true);
    Point e(vector<double>{-1,0},true);
    Point f(vector<double>{1,1},true);
    
    cout << (orientation(b,a,c)==1) << (orientation(d,a,c)==-1) << (orientation(c,a,b)==-1);
    cout << (orientation(e,a,b)==1) << endl;
    
    vector<Point> zero{a};
    vector<Point> triangle{b,f,c};
    vector<Point> triangle2{f,d,e};

    cout << "triangle results " << (in_triangle(zero, triangle)==false) << (in_triangle(zero, triangle2)==true) << endl;
    
}


bool Gale_Diagram::isSimplex(int i, int j , int k, int l){
    //Remove the columns i,j,k,l by selecting the other columns:
    vector<int> pointIndices = findMissing(i,j,k,l);
    //Select points
    vector<Point> fourPoints;
    for(int m=0; m<pointIndices.size(); m++) fourPoints.push_back(points[pointIndices[m]]);
    
    return check_intersecting(fourPoints);
}

void Gale_Diagram::makeVertexFacetStructure(){
    int s = points.size();
    
    for(int i=0; i<s-3; i++){
        for(int j=i+1; j<s-2; j++){
            for(int k=j+1; k<s-1; k++){
                for(int l=k+1; l<s; l++){
                    cout << i << " " << j << " " << k << " " << l << endl;

                    
                    
                    if(isSimplex(i, j, k, l)){
                        //add edge to graph
                    };
                }
            }
        }
    }
    
    //return graph
}

bool Gale_Diagram::isSimplicial(){
    int s = points.size();
    for(int i=0; i<s-3; i++){
        for(int j=i+1; j<s-2; j++){
            //If ij is a vertical line
            if(points[i].get_coordinates()[0]==points[j].get_coordinates()[0]){
                for(int k=j+1; k<s-1; k++){
                    if(points[k].get_coordinates()[0]==points[i].get_coordinates()[0]) return false;
                }
                continue;
            }
            
            //check if k is on line ij
            Point slopeCoordinates = points[i].minus(points[j]);
            mpq_class slope = slopeCoordinates.get_coordinates()[1]/slopeCoordinates.get_coordinates()[0];
            slope.canonicalize();
            
            mpq_class aSlope = slope*points[i].get_coordinates()[0];
            aSlope.canonicalize();
            aSlope -= points[i].get_coordinates()[1];
            aSlope.canonicalize();
            
            for(int k=j+1; k<s-1; k++){
                mpq_class rightHandSide = slope*points[k].get_coordinates()[0];
                rightHandSide.canonicalize();
                
                rightHandSide-=aSlope;
                rightHandSide.canonicalize();
                
                if(points[k].get_coordinates()[1] == rightHandSide){
                    return false;
                }
            }
        }
    }
    return true;
}
