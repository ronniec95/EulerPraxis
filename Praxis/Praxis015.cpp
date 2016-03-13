 //
//  Praxis015.cpp
//  ProgrammingPraxis
//
//  Created by Ronnie Chowdhury on 12/03/2016.
//  Copyright © 2016 Ronnie Chowdhury. All rights reserved.
//
#include "stdafx.h"
#include <stdio.h>
#include "Praxis.h"

int dayofweek(int y, const int m,int d)	/* 1 <= m <= 12,  y > 1752 (in the U.K.) */
{
    return (d+=m<3?y--:y-2,23*m/9+d+4+y/4-y/100+y/400)%7;
}

void Praxis015() {
    for (int y = 2016; y < 2027; y++) {
        for (int m = 1; m < 13; m++) {
            if (dayofweek(y, m, 13) == 5) {
                printf("%4d%02d%02d -> %d\n",y,m,13,dayofweek(y, m, 13));
            }
        }
    }
}
