#include "stdafx.h"
#include "Praxis.h"
#include <boost\multiprecision\gmp.hpp>

using namespace boost;
namespace mp = boost::multiprecision;

mp::mpf_float series(int i, const double numerator, const double denominator) {
	return numerator / (8.0 * i + denominator);
}

void Praxis008() {
	// Had a look at the spigot algorithm here  http://www.cs.ox.ac.uk/people/jeremy.gibbons/publications/spigot.pdf
	// Also the	http://beej.us/blog/data/pi-chudnovsky-gmp/ calculates pi in one shot and is fast
	// The original algo by pouffle is give in bpp
	int n = 20.0;
	mp::mpf_float sum = 0.0;
	const mp::mpf_float con = 16.0;
	do 	{
		mp::mpf_float factor;
		mpf_pow_ui(factor.backend().data(), con.backend().data(), n);
		factor = 1.0 / factor;
		sum += factor * (series(n, 4, 1) - series(n, 2, 4) - series(n, 1, 5) - series(n, 1, 6));
	} while (n-- > 0);
	std::cout << sum.str(100) << std::endl;
}

