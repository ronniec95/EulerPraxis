//
//  Euler002.cpp
//  ProgrammingPraxis
//
//  Created by Ronnie Chowdhury on 02/03/2016.
//  Copyright © 2016 Ronnie Chowdhury. All rights reserved.
//

#include "stdafx.h"
#include "Euler.h"
#include <math.h>
#include <boost/math/special_functions/pow.hpp>

using namespace boost;

void Euler002() {
    const double golden_ratio = 1.618034;
    const double sqrt5 = ::sqrt(5.0);
    long fib = 0;
    long sum = 0;
    int i = 6;
    while ( sum < 4000000) {
        fib = static_cast<int>((::pow(golden_ratio, i) - ::pow(1.0 - golden_ratio, i)) / sqrt5);
        std::cout << fib << std::endl;
        sum += fib;
        i += 3;
    }
    std::cout << sum << std::endl;
}