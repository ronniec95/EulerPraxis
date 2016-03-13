//
//  Euler003.cpp
//  ProgrammingPraxis
//
//  Created by Ronnie Chowdhury on 03/03/2016.
//  Copyright © 2016 Ronnie Chowdhury. All rights reserved.
//

#include "stdafx.h"
#include "Euler.h"
#include <iterator>
#include <vector>
#include <math.h>
#include <boost/range/irange.hpp>
#include <iostream>

using namespace boost;

std::vector<bool> find_primes(const long number) {
    // Only need to test up to sqrt(num), and we can skip even numbers
    std::vector<bool> primeset(::sqrt(number) / 2);
    // Starting from 3 cross out any primes higher than it
    for(auto i : irange(3,static_cast<int>(sqrt(number)))) {
        for(auto b = (i / 2) - 1; b < primeset.size() ; b +=i ) {
            if (primeset[b] == true)
                primeset[b].flip();
        }
    }
    return primeset;
}


void Euler003() {
    long long number = 600851475143;
    auto res = find_primes(number);
	for (auto i = res.begin(); i != res.end(); ++i) {
        std::cout << (std::distance(res.begin(),i)) * 2 + 1 << std::endl;
    };
}