//
//  Praxis004.cpp
//  ProgrammingPraxis
//
//  Created by Ronnie Chowdhury on 25/02/2016.
//  Copyright © 2016 Ronnie Chowdhury. All rights reserved.
//

#include "stdafx.h"
#include "Praxis.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <boost/range/adaptor/indexed.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/irange.hpp>
#include <boost/convert.hpp>
#include <boost/convert/lexical_cast.hpp>
#include <boost/container/map.hpp>
#include <boost/container/static_vector.hpp>
#include <numeric>
#include "Praxis004.h"

using namespace boost;

// Create a table of peers for each cell (row,col and block)
container::multimap<int, container::static_vector<int, 27>> assign_peers(const std::vector<int>& rawboard) {
    container::multimap<int, container::static_vector<int, 27>> peers;
    for (auto i = 0U; i < rawboard.size(); i++) {
        container::static_vector<int, 27> peer_indices;
        const int row = i / 9;
        const int col = i % 9;
        for(auto n = 0; n < 9;n++){
            const int row_idx = row * 9 + n;
            if (i != row_idx)
                peer_indices.emplace_back(row_idx);
        }
        for(auto n = 0; n < 9;n++){
            const int col_idx = n * 9 + col;
            if(i != col_idx)
                peer_indices.emplace_back(col_idx);
        }
        const int blockV = row / 3;
        const int blockH = col / 3;
        for(auto j = blockH * 3; j < (blockH + 1) * 3; j++) {
            for(auto k = blockV * 3; k < (blockV + 1) * 3; k++) {
                const int cell_idx = j + k * 9;
                if(i != cell_idx)
                    peer_indices.emplace_back(cell_idx);
            }
        }
        peers.insert(std::make_pair(static_cast<int>(i), peer_indices));
    }
    return peers;
}

void display(const container::static_vector<int, 9>& v) {
	std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout));
	std::cout << std::endl;
}

void display(const container::multimap<int, container::static_vector<int,9>>& valuemap) {
	for (int i = 0; i < 81; i++) {
		auto v = valuemap.find(i);
		auto cell_values = v->second;
		std::for_each(cell_values.begin(), cell_values.end(), [](int v) {
			if (v == 0)
				std::cout << " ";
			else
				std::cout << v;
		});
		std::cout << "|";
		if ((i+1) % 9 == 0)
			std::cout << std::endl;
	}
	std::cout << std::endl;
    std::cout << "-------------" << std::endl;
}


// Each cell has 9 possible values
container::multimap<int, container::static_vector<int,9>> assign_values(const std::vector<int>& rawboard) {
    container::multimap<int, container::static_vector<int,9>> assignees;
	for(auto i : irange(0,81)) {
		container::static_vector<int, 9> numbers({1,2,3,4,5,6,7,8,9});
		assignees.insert(std::make_pair(static_cast<int>(i), numbers));
	}
    return assignees;
}
// fwd declaration
bool assign_element(container::multimap<int, container::static_vector<int, 9>>& cells,const container::multimap<int, container::static_vector<int, 27>>& peermap,const int cell,const int d);
bool eliminate(
	container::multimap<int, container::static_vector<int, 9>>& cells,
	const container::multimap<int, container::static_vector<int, 27>>& peermap,
	const int s,
	const int d) {
	auto cell_values_iter = cells.find(s);
	auto& cell_values = cell_values_iter->second;
	auto find_cell = std::find(cell_values.begin(), cell_values.end(), d);

	// If d not in cells[s] return true
	if (find_cell == cell_values.end())
		return true;
	cell_values[d - 1] = 0;
	auto remaining = std::count_if(cell_values.begin(), cell_values.end(), std::bind2nd(std::not_equal_to<int>(), 0));
	if (remaining == 0) {
		cell_values[d - 1] = d;
		return false;
	}
	else if (remaining == 1) {
		auto peers_iter = peermap.find(s);
		auto peers = peers_iter->second;
		auto d2 = find_if(cell_values, std::bind1st(std::not_equal_to<int>(), 0));
		if (!std::all_of(peers.begin(), peers.end(), [&](auto n) { return eliminate(cells, peermap, n, *d2); }))
			return false;
	}
	return true;
}

void display_peers(const int &s, boost::container::container_detail::iterator_from_iiterator<boost::intrusive::tree_iterator<boost::intrusive::bhtraits<boost::container::container_detail::tree_node<std::pair<const int, boost::container::static_vector<int, 27Ui64>>, void *, boost::container::red_black_tree, true>, boost::intrusive::rbtree_node_traits<void *, true>, boost::intrusive::normal_link, boost::intrusive::dft_tag, 3U>, false>, true> &peers, boost::container::multimap<int, boost::container::static_vector<int, 9Ui64>> & cells, const boost::container::multimap<int, boost::container::static_vector<int, 27Ui64>> & peermap) {
	std::cout << "Peers of " << s << "->[";
	boost::copy(peers->second, std::ostream_iterator<int>(std::cout, ","));
	auto values = boost::accumulate(peers->second, std::set<int>(), [&cells, &peermap](auto& values, auto p) {
		auto cell_values_in_peer = cells.find(p);
		boost::copy(cell_values_in_peer->second, std::inserter(values, values.begin()));
		return values;
	});
	std::cout << "] contain [";
	boost::copy(values, std::ostream_iterator<int>(std::cout, ","));
	std::cout << "]" << std::endl;
}

bool assign_element(
	container::multimap<int, container::static_vector<int,9>>& cells,
    const container::multimap<int,container::static_vector<int, 27>>& peermap,
    const int cell,
    const int d) {
    auto cell_values_iter = cells.find(cell);
    auto& cell_values = cell_values_iter->second;
	// Find other values except d
	auto others = cell_values | adaptors::transformed([&](auto i) { return i == d ? 0 : i; });
	if (std::all_of(others.begin(), others.end(), std::bind1st(std::equal_to<int>(), 0))) {
		return false;
	}
	bool elim = std::all_of(others.begin(), others.end(), [&](auto n) { 
		return n == 0 ? true : eliminate(cells, peermap, cell, n); }); 
	return elim;
}

void Praxis004()
{
    // Read file
    std::fstream reader;
    reader.open("Sodoku.txt");
    
    if(reader.is_open()) {
        std::string line;
        // Parse a line
        std::vector<int> rawboard;
        while (std::getline(reader,line)){
            std::transform(line.begin(), line.end(), std::back_inserter(rawboard),
				[](const char i) { return i == '.' ? 0 : lexical_cast<int>(i); });
        }
        // Each cell starts off with 9 values (1-9) but it's peers remove valid numbers
        auto peermap = assign_peers(rawboard);
        auto valuemap = assign_values(rawboard);
		for (int v = 0; v < rawboard.size(); v++) {
			if (rawboard[v]) {
				assign_element(valuemap, peermap, v, rawboard[v]);
				display(valuemap);
			}
        }
	}
}