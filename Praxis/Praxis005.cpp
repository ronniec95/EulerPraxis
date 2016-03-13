#include "stdafx.h"
#include "Praxis.h"
#include <boost\circular_buffer.hpp>

using namespace boost;

void Praxis005() {
	auto n = 41;
	auto m = 3;
	//Buffer filled with n people, all alive = '1'
	circular_buffer<int> people(n,1);
	auto kill_pos = 0;
	people[kill_pos] = 0;
	while (range::count_if(people, [](auto i) { return i == 1; }) > 0) {
		kill_pos += m;
		if (kill_pos > (n - 1)) {
			kill_pos = kill_pos % (n - 1);
		}
		people[kill_pos] = 0;
	}
}