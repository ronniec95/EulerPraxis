//
//  Euler001.cpp
//  ProgrammingPraxis
//
//  Created by Ronnie Chowdhury on 01/03/2016.
//  Copyright © 2016 Ronnie Chowdhury. All rights reserved.
//

#include "stdafx.h"
#include "Euler.h"

void Euler001() {
    auto n5 = (995 - 5) / 5 + 1;
    auto sum5 = 5 * (n5 * (n5 + 1))/ 2;
    auto n3 = (999 - 3) / 3 + 1;
    auto sum3 = 3 * (n3 * (n3 + 1)) / 2;

    auto n15 = (1000 - 15) / 15 + 1;
    auto sum15 = 15 * (n15 * (n15 + 1)) / 2;

    auto result = sum5 + sum3 - sum15;
}