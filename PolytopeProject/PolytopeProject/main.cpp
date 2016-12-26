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

void testGMP();

int main(int argc, const char * argv[]) {
    testGMP();
    return 0;
}

void testGMP(){
    mpq_t q;
    mpq_init(q);
    mpq_set_si(q,123456,333);
    mpq_canonicalize(q);
    gmp_printf("Rational q with value: %Qd\n",q);
}
