#include <iostream>
#include <gmp.h>
#include <stdio.h>
#include <vector>
#include <gmpxx.h>
#include <stdio.h>
#include "Point.hpp"

using namespace std;

class Point;


int main(int argc, const char * argv[]) {
	
	cout << "a";
	
	
	Point p = Point(vector<mpq_class>{0,0}, true);
	Point q = Point(vector<mpq_class>{2,0}, false);
	
	vector<Point> v(6, Point(vector<mpq_class>{0,0}, true));
	
	for(int i = 0; i<6; ++i) v[i] = Point(vector<mpq_class>{1,i+1}, true);
	
	cout << "c";
	
	vector<Point> l(6, Point(vector<mpq_class>{0,0}, true));
	vector<Point> r(6, Point(vector<mpq_class>{0,0}, true));
	
	vector<mpq_class> p1 = p.get_coordinates();
	vector<mpq_class> q1 = q.get_coordinates();
	
	for(int i = 0; i < 6; ++i){
		vector<mpq_class> p2 = v[i].get_coordinates();
		vector<mpq_class> q2 = v[i].get_coordinates();
		
		mpq_class m1 = (p2[1]-p1[1])/(p2[0]-p1[0]);
		mpq_class m2 = (q2[1]-q1[1])/(q2[0]-q1[0]);
		
		m1.canonicalize();
		
		m2.canonicalize();
		
		mpq_class c1 = m1*p1[0];
		mpq_class c2 = m2*q1[0];
		
		c1.canonicalize();
		c2.canonicalize();
		
		c1 = p1[1]-c1;
		c2 = q1[1]-c2;
		
		c1.canonicalize();
		c2.canonicalize();
		
		l[i] = Point(vector<mpq_class>{m1,c1}, true);
		r[i] = Point(vector<mpq_class>{m2,c2}, true);
	}
	
	
	vector<vector<Point>> M(6, vector<Point>(6, Point(vector<mpq_class>{0,0}, true)));
	
	for(int i = 0; i < 6; ++i){
		for(int j = 0; j < 6; ++j){	
			vector<mpq_class> r1 = l[i].get_coordinates();
			vector<mpq_class> r2 = r[j].get_coordinates();
			
			mpq_class x1 = -r2[1]+r1[1];
			mpq_class x2 = r2[0]-r1[0];
			
			x1.canonicalize();
			x2.canonicalize();
			
			mpq_class x = x1/x2;
			x.canonicalize();
			
			mpq_class y = r1[0]*x;
			y.canonicalize();
			
			y = y + r1[1];
			y.canonicalize();
			
			M[i][j] = Point(vector<mpq_class>{x,y}, true);
		}
	}
	
	for(int i = 0; i < 6; ++i){
		for(int j = 0; j < 6; ++j){
			M[i][j].print();
		}
		cout << endl;
	}
	
	return 0;
}
