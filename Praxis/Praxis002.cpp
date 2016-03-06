#include "stdafx.h"
#include "Praxis.h"
#include <boost/dynamic_bitset.hpp>

void Praxis002()
{
	// Sieve of eratosthenes
	std::cout << "Enter a number:";
	long n = 0;
	std::cin.clear();
	std::cin >> n;

	// Bool Vector, filled with true. Even numbers can't be prime so halve the bit size
	// Consider odd numbers only - halves the space
	// Start at the square of the number - since numbers below will have been consumed already
	// Stop at the sqrt(N) - anything above that will have been sieved already
	std::vector<bool> bits(static_cast<int>(n / 2.0));
	std::fill(std::begin(bits), std::end(bits), true);
	for (auto i = 1U; i < static_cast<size_t>(sqrt(bits.size())); i++) {
		// Actual value is 2n+1
		const size_t move = 2 * i + 1;
		for (auto j = i + move ; j < bits.size(); j += move) {
			if (bits[j] == true) {
				bits[j].flip();
			}
		}
	}
	// Print the numbers
	for (auto i = 0; i < bits.size(); i++) {
		if (bits[i] == true) {
			std::cout << 2*i+1 << ",";
		}
	}
}
