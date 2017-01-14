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
#include<iostream>
#include<fstream>
#include <vector>
#include <gmpxx.h>
#include "Point.hpp"
#include "Matrix.hpp"
#include "Gale_Diagram.hpp"
//#include <polymake.h>
#include "igraph.h"
//#include "intersectionsTest.hpp"

using namespace std;


//Returns an array with all valid (neighborly and simplicial and non-isomorphic) gale diagrams
vector<vector<Gale_Diagram>> isomorphismClasses(vector<Gale_Diagram> neighborlyGaleDiagrams) {
    vector<bool> sorted(neighborlyGaleDiagrams.size(),false);
    
    vector<vector<Gale_Diagram>> isomorphismClasses;
    
    for(int i=0; i<neighborlyGaleDiagrams.size(); i++){
        if(sorted[i]) continue;
        
        Gale_Diagram galeI = neighborlyGaleDiagrams[i];
        vector<Gale_Diagram> isomorphismClass;
        isomorphismClass.push_back(galeI);
        sorted[i]=true;
        
        for(int j=i+1; j<neighborlyGaleDiagrams.size(); j++){
            if(sorted[j]) continue;
            
            if(galeI.isIsomorphic(neighborlyGaleDiagrams[j])){
                isomorphismClass.push_back(neighborlyGaleDiagrams[j]);
                sorted[j]=true;
            }
        }
        isomorphismClasses.push_back(isomorphismClass);
    }
    return isomorphismClasses;
}

void enumerateAllPolytopes(vector<Gale_Diagram> neighborlyGaleDiagrams){
    vector<vector<Gale_Diagram>> isoClasses = isomorphismClasses(neighborlyGaleDiagrams);
    for(int i=0; i < isoClasses.size(); i++){
        Matrix polyMatrix = isoClasses[i][0].galeToPolytope();
        
        //Write vertex-facet lattice
        isoClasses[i][0].writeGraph("Polytopes"+to_string(i));
        
        //Print
        Matrix pointPM = polyMatrix.transpose();
        vector<vector<mpq_class>> pPM = pointPM.getMatrix();
        
        cout << endl << "Points of polytope " + to_string(i+1) + " " << endl;
        for(int i=0; i<pPM.size(); i++){
            cout << i << " ";
            Point(pPM[i],true).print();
        }
        cout << endl;
        
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
    
    Point v9(vector<mpq_class>{1,mpq_class(21,10)},true);
    
    Gale_Diagram C48 = Gale_Diagram(vector<Point>{v1,v2,v3,v4,v5,v6,v7,v8});
    Gale_Diagram C482 = Gale_Diagram(vector<Point>{v9,v2,v3,v4,v5,v6,v7,v8});
    
    Point n1(vector<mpq_class>{1,mpq_class(1,2)},true);
    vector<mpq_class> coord{-1,mpq_class(1,2)};
    Point n8(coord,false);
    Gale_Diagram N48 = Gale_Diagram(vector<Point>{n1,v2,v3,v4,v5,v6,v7,n8});
    cout << "Simpel" <<C48.isSimplicial() << " " << C482.isSimplicial() << " " << C482.isSimplicial() << endl;
    
    igraph_t graph = C48.makeVertexFacetStructure();
    igraph_t graph2 = C482.makeVertexFacetStructure();
    igraph_t graph3 = N48.makeVertexFacetStructure();
    
    /*writeGraph(graph,"CyclicPolytopeGraph.txt");
    writeGraph(graph2,"CyclicPolytopeGraph2.txt");
    writeGraph(graph3,"CyclicPolytopeGraph3.txt");*/
    igraph_bool_t result = false;
    igraph_isomorphic(&graph, &graph2, &result);
    
    cout << "isomorphism test " <<result << endl;
    
    
    vector<Gale_Diagram> gales{C48,C482,N48};
    //vector<vector<Gale_Diagram>> isoC = isomorphismClasses(gales);
    enumerateAllPolytopes(gales);
    
    
    igraph_destroy(&graph);
    igraph_destroy(&graph2);
    igraph_destroy(&graph3);

    /*for(int a = 0; a<1000; a++){
        int s=8;
    for(int i=0; i<s-1; i++){
        for(int j=i+1; j<s; j++){
            for(int k=0; k<s-3; k++){
                for(int l=k+1; l<s-2; l++){
                    C48.findMissing(i, j, k, l);
                }
            }
        }
    }
        cout<<"a"<<a<<endl;
    }*/
    /*for(int i=0; i<10000; i++){
        C48.is_neighborly();
        cout << i << endl;
    }*/
    
    cout<<"Gale_Diagram test"<<endl;
    C48.test();
    
    C48.print();
    
    cout << "C48 test " << (C48.is_neighborly()) << " end test"<< endl;
    
    Matrix matrix(vector<Point>{v5,v6,v7,v8});
    matrix.print();
    //vector<Point> vec = matrix.get_kernel();
    //Matrix(vec).print();
    matrix.testMatrix();
    
    cout<<"StartTest" << endl;
    N48.galeToPolytope();
    cout << "EndTest" << endl;
}


int main(int argc, const char * argv[]) {
    tests();
    
    //Intersections inters;
    //inters.printNeighbourly();
    
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
