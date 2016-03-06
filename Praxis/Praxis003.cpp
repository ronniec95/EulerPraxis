#include "stdafx.h"
#include "Praxis.h"
#include <boost/multi_array.hpp>

// Check if a row/col/diagonal contains 0 which means they've been struck off
bool has_won(const boost::multi_array<int,2>& card) {
	typedef boost::multi_array_types::index_range range;
	bool win = false;
	// Check for row for 0
	for(auto row : card) {
		win = std::all_of(row.begin(), row.end(), [](auto i) { return i == 0; });
		if (win) break;
	}
	if (win)
		return true;

	// Check col for 0
	win = true;
	for (auto j = 0U; j < card.shape()[1]; j++) {
		auto col = card[boost::indices[range()][j]];
		win = std::all_of(col.begin(), col.end(), [](auto i) { return i == 0; });
		if (win) break;
	}
	if (win)
		return true;

	// Check diagonal of 0
	win = true;
	for (auto j = 0U; j < card.shape()[0]; j++) {
		auto i = card[j][j];
		win = win && (i == 0);
		if (!win)
			break;
	}
	if (win)
		return true;
	// Check opposite diagonal
	win = true;
	for (auto j = 0U; j < card.shape()[0]; j++) {
		auto i = card[j][card.shape()[0] - 1 - j];
		win = win && (i == 0);
		if (!win)
			break;
	}
	return win;
}

void print_card(const boost::multi_array<int, 2>& card) {
	std::copy(card.data(), card.data() + card.num_elements(), std::ostream_iterator<int>(std::cout, ","));
	std::cout << std::endl;
}

void Praxis003() {
	// Bingo
	typedef boost::multi_array_types::index_range range;
	boost::multi_array<int, 2> card(boost::extents[5][5]);

	// Seed using chrono clock
	auto now = std::chrono::high_resolution_clock::now();
	std::mt19937 rng(now.time_since_epoch().count());

	// Generate bingo card
	for (auto j = 0U; j < card.shape()[1]; j++) { 
		// Slice through a column, filling in random numbers between j * 15 + 1 to (j+1) * 15 + 1
		std::uniform_int_distribution<int> gen(j * 15 + 1, (j + 1) * 15 + 1);
		auto col = card[boost::indices[range()][j]];
		for (auto i = col.begin(); i != col.end(); i++)
			*i = gen(rng);
	}
	// Middle cell set to 0
	card[2][2] = 0; // Middle cell
	// Generate a number between 1-75
	long count = 0;
	std::uniform_int_distribution<int> gen(1, 75);
	while (!has_won(card)) {
		auto num = gen(rng);
		auto found = std::find(card.data(), card.data() + card.num_elements(), num);
		if (*found == num)
			*found = 0;
		count++;
	}

	std::cout << "winner after " << count << " rounds";
}
