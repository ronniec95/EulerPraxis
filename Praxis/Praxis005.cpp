#include "stdafx.h"
#include "Praxis.h"
#include <math.h>

using namespace boost;


void Praxis005() {
	// http://www.exploringbinary.com/powers-of-two-in-the-josephus-problem/
	// Break the problem into a power of 2 problem and a k remainder problem
	// winner = 2(n - 2^m) + 1;
	auto n = 41;
	auto k = 3;
	int a = 1;
	for (int i = 1; i <= n; i++) {
		a = (a + k - 1) % i + 1;
	}
	std::cout << a << std::endl;
}