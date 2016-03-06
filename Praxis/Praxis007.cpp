#include "stdafx.h"
#include "Praxis.h"
#include <boost/range/algorithm.hpp>

using namespace boost;

void Praxis007() {
	std::string floors = "bfcms";
	bool solved = false;
	do {
		auto c = find(floors, 'c');
		auto f = find(floors, 'f');
		auto m = find(floors, 'm');
		auto s = find(floors, 's');
		auto b = find(floors, 'b');
		auto baker = [](auto& floors) { return 'b' != floors[4]; };
		auto cooper = [&](auto& floors) { return 'c' != floors[4] && abs(std::distance(f, c)) > 1; };
		auto fletcher = [&](auto& floors) { return 'f' != floors[0] && 'f' != floors[4] && abs(std::distance(f, c)) > 1; };
		auto miller = [&](auto& floors) { return std::distance(c, m) > 0; };
		auto smith = [&](auto& floors) { return abs(std::distance(s, f)) > 1; };
		std::array<std::function<bool(std::string&)>, 5> conditions({ baker,cooper,fletcher,miller,smith });
		solved = std::all_of(conditions.begin(), conditions.end(), [&floors](const auto& f) { return f(floors); });
		std::next_permutation(floors.begin(), floors.end());
	} while (!solved);
	std::cout << "Final: " << floors << std::endl;
}
