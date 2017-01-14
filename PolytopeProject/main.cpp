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
//#include <polymake.h>
#include "igraph.h"

using namespace std;


//Returns an array with all valid (neighborly and simplicial and non-isomorphic) gale diagrams
//NOT TESTED, NOT SURE IT WORKS. Petar = intersections, in main() we should define Petar as well
void enumerate_all_gale(Matrix Petar, int i, vector<Gale_Diagram> &AllGale) {
	vector<bool> used(6, false);
	vector<Point> GaleDiagram;
	//vector<Gale_Diagram> AllGale();
	GaleDiagram[0]=Point(vector<double>{0,0},true);
	GaleDiagram[1]=Point(vector<double>{2,0},true);
	if(i==6){
		AllGale.push_back(GaleDiagram);
		return;
	}
	for(int j = 0; j < 6; ++j){
		if(not used[j]) {
            //GaleDiagram[i+2] = Petar.get(i,j);
			used[j] = true;
			//enumerate_all_gale(Petar,i+1);
			used[j] = false;
		}
	}
}
	


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

void tests(){
    //testGMP();
    //testInitialisers();
    
    Point v1(vector<mpq_class>{1,2},true);
    Point v2(vector<mpq_class>{2,1},false);
    Point v3(vector<mpq_class>{2,-1},true);
    Point v4(vector<mpq_class>{1,-2},false);
    Point v5(vector<mpq_class>{-1,-2},true);
    Point v6(vector<mpq_class>{-2,-1},false);
    Point v7(vector<mpq_class>{-2,1},true);
    Point v8(vector<mpq_class>{-1,2},false);
    
    Point v9(vector<mpq_class>{1,mpq_class(100,49)},false);
    
    Gale_Diagram C48 = Gale_Diagram(vector<Point>{v1,v2,v3,v4,v5,v6,v7,v8});
    Gale_Diagram C482 = Gale_Diagram(vector<Point>{v9,v2,v3,v4,v5,v6,v7,v8});
    cout << C48.isSimplicial() << " " << C482.isSimplicial() << endl;
    
    /*igraph_t graph = C48.makeVertexFacetStructure();
    igraph_t graph2 = C48.makeVertexFacetStructure();
    igraph_bool_t result;
    igraph_isomorphic(&graph, &graph2, &result);
    
    cout << "isomorphism test " <<result << endl;
    
    igraph_destroy(&graph);
    igraph_destroy(&graph2);*/

    
    for(int i=0; i<10000; i++){
        C48.is_neighborly();
        cout << i << endl;
    }
    
    cout<<"Gale_Diagram test"<<endl;
    C48.test();
    
    C48.print();
    
    cout << "C48 test " << (C48.is_neighborly()) << " end test"<< endl;
    
    Matrix matrix(vector<Point>{v5,v6,v7,v8});
    matrix.print();
    vector<Point> vec = matrix.get_kernel();
    Matrix(vec).print();
    matrix.testMatrix();
}


int main(int argc, const char * argv[]) {
    tests();
    
    //vector<Gale_Diagram> AllGale();
    //enumerate_all_gale(Petar,0,AllGale);
    
    
    //example, still has to be implemented:
    //bool simplicial = Gale_Diagram::check_simplicial(gd);
    

    return 0;
}

/*int main(void) {
    igraph_real_t avg_path;
    igraph_t graph;
    igraph_vector_t dimvector;
    igraph_vector_t edges;
    int i;
    
    igraph_vector_init(&dimvector, 2);
    VECTOR(dimvector)[0]=30;
    VECTOR(dimvector)[1]=30;
    igraph_lattice(&graph, &dimvector, 0, IGRAPH_UNDIRECTED, 0, 1);
    
    igraph_rng_seed(igraph_rng_default(), 42);
    igraph_vector_init(&edges, 20);
    for (i=0; i<igraph_vector_size(&edges); i++) {
        VECTOR(edges)[i] = rand() % (int)igraph_vcount(&graph);
    }
    
    igraph_average_path_length(&graph, &avg_path, IGRAPH_UNDIRECTED, 1);
    printf("Average path length (lattice):            %f\n", (double) avg_path);
    
    igraph_add_edges(&graph, &edges, 0);
    igraph_average_path_length(&graph, &avg_path, IGRAPH_UNDIRECTED, 1);
    printf("Average path length (randomized lattice): %f\n", (double) avg_path);
    
    igraph_vector_destroy(&dimvector);
    igraph_vector_destroy(&edges);
    igraph_destroy(&graph);
    
    return 0;
}*/
