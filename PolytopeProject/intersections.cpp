#include <iostream>
#include <gmp.h>
#include <stdio.h>
#include <vector>
#include <gmpxx.h>
#include <stdio.h>
#include "Point.hpp"
#include "Gale_Diagram.hpp"

using namespace std;

class Point;

typedef vector<mpq_class> V;
typedef vector<V> VV;
typedef vector<Point> VP;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<bool> VB;
typedef vector<VB> VVB;
typedef vector<Gale_Diagram> VGD;

int number_diagrams;
int number_simplicial;
int number_neighborly;
VVI all_p_combinations;
VVB all_s_combinations;

void sign_combinations(VB& v, int n, int ps, int ns){
	if(n>0){
		if(ps>0){
			v[n-1] = true;
			sign_combinations(v, n-1, ps-1, ns);
		}
		if(ns>0){
			v[n-1] = false;
			sign_combinations(v, n-1, ps, ns-1);
		}
	}
	else{
		
		/*if(gd.isSimplicial()){
			++number_simplicial;
			if(gd.is_neighborly()){
				++number_neighborly;
			}
		}*/
		
		all_s_combinations.push_back(VB(v));
		
	}
	
}

void p_combinations(VI& v, VB& b, const Point& p, const Point& q, int n){
	if(n>0){
		for(int i = 0; i < 6; ++i){
			if(b[i]){
				v[n-1] = i;
				b[i]=false;
				p_combinations(v, b, p, q, n-1);
				b[i]=true;
			}
		}
	}
	else all_p_combinations.push_back(VI(v));
}


int main(int argc, const char * argv[]) {
	
	Point p = Point(V{0,0}, true);
	Point q = Point(V{2,0}, false);
	
	VP v(6, Point(V{0,0}, true));
	
	for(int i = 0; i<6; ++i) v[i] = Point(V{1,i+1}, true);
	
	VP l(6, Point(V{0,0}, true));
	VP r(6, Point(V{0,0}, true));
	
	V p1 = p.get_coordinates();
	V q1 = q.get_coordinates();
	
	for(int i = 0; i < 6; ++i){
		V p2 = v[i].get_coordinates();
		V q2 = v[i].get_coordinates();
		
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
		
		l[i] = Point(V{m1,c1}, true);
		r[i] = Point(V{m2,c2}, true);
	}
	
	
	vector<VV> M(6, VV(6, V{0,0}));
	
	for(int i = 0; i < 6; ++i){
		for(int j = 0; j < 6; ++j){	
			V r1 = l[i].get_coordinates();
			V r2 = r[j].get_coordinates();
			
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
			
			M[i][j] = V{x,y};
		}
	}
	
	number_diagrams = 0;
	number_neighborly = 0;
	number_simplicial = 0;
	
	VI vi(6,0);
	VB b(6,true);
	VB vs(8, false);
	
	p_combinations(vi, b, p, q, 6);
	sign_combinations(vs, 7, 5, 4);
	
	/*
	VP vp(8, Point(V{0,0}, false));
	vp[6] = p;
	vp[7] = q;
	
	for(int i = 0; i < all_p_combinations.size(); ++i){
		for(int j = 0; j < all_s_combinations.size(); ++j){
			//if(i == 0 and j == 0){
				VI p_combination = all_p_combinations[i];
				VB s_combination = all_s_combinations[j];
				for(int k = 0; k < 6; ++k) vp[k] = Point(M[k][p_combination[k]],s_combination[k]);
				vp[6].set_sign(s_combination[6]);
				vp[7].set_sign(s_combination[7]);
				
				++number_diagrams;
				
				Gale_Diagram gd(vp);
				
				if(gd.isSimplicial()){
					++number_simplicial;
					if(gd.is_neighborly()){
						cout << i << " " << j << endl;
						++number_neighborly;
					}
				}
			//}
		}
	}
	
	cout << "totals: " << endl;
	cout << number_diagrams << " " << number_simplicial << " " << number_neighborly << endl;
	*/
	
	int i, j;
	
	VGD vgd;
	
	while(cin >> i >> j){
		
		VP vp(8, Point(V{0,0}, false));
		
		for (int k=0; k < all_p_combinations[i].size(); ++k) vp[k] = Point(M[k][all_p_combinations[i][k]], all_s_combinations[j][k]);
		vp[6] = Point(V{0,0}, all_s_combinations[j][6]);
		vp[7] = Point(V{2,0}, all_s_combinations[j][7]);
		
		Gale_Diagram gd(vp);
		
		gd.print();
		
		vgd.push_back(gd);		
		
	}
	
	for (int i = 0; i < vgd.size(); ++i){
		vgd[i].print();
	}
	
	return 0;
}
