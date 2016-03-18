#include "stdafx.h"
#include "Praxis.h"
#include <fstream>
#include <strstream>
#include <queue>
#include <algorithm>
#include <boost\tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/device/mapped_file.hpp>
using namespace boost;



auto build_word_list(const std::string& word, const std::string& target, const std::vector<std::string>& words) {
	// Build a map with 1 letter changed
	auto cmp = [&target](const auto& lhs, const auto &rhs) {
		int lhsvalue = 0, rhsvalue = 0;
#pragma loop(ivdep)
		for (int c = 0; c < lhs.size(); c++) {
			lhsvalue += abs(lhs[c] - target[c]);
		}
#pragma loop(ivdep)
		for (int c = 0; c < rhs.size(); c++) {
			rhsvalue += abs(rhs[c] - target[c]);
		}
		return lhsvalue < rhsvalue;
	};
	std::set<std::string, decltype(cmp)> alternatives(cmp);
	for (int i = 0; i < word.size(); ++i) {
		for (auto w : words) {
			auto add = true;
#pragma loop(ivdep)
			for (int ch = 0; ch < word.size(); ++ch) {
				if (ch == i)
					continue;
				if (w[ch] != word[ch]) {
					add = false;
					break;
				}
			}
			if (add)
				alternatives.emplace(w);
		}
	}
	return std::vector<std::string>(alternatives.begin(), alternatives.end());
}

auto solve(const std::string& start, const std::string& end, 
		   const std::vector<std::string>& words) {
	// DFS or BFS iterative approach
	std::queue<std::string> queue;
	std::vector<bool> visited(words.size(), false);
	auto found = std::find(words.begin(), words.end(), start);
	visited[std::distance(words.begin(), found)] = true;
	queue.emplace(start);
	
	// Keep a track of parents. Fastest data structure to use for only a few K elements
	std::vector<std::pair<std::string, std::string>> parents;

	while (!queue.empty()) {
		auto current = queue.front();
		if (current == end) {
			break;
		}
		queue.pop();

		// Add children to graph
		auto children = build_word_list(current, end, words);
		for (auto w : children) {
			found = std::find(words.begin(), words.end(), w);
			auto pos = std::distance(words.begin(), found);
			if (*(visited.begin() + pos) == false) {
				visited[pos] = true;
				queue.emplace(w);
				parents.emplace_back(std::make_pair(w, current));
			}
		}
	}
	std::vector<std::string> path;
	path.emplace_back(end);
	auto tail = end;
	//while (tail != start) {
	//	auto found = std::find_if(parents.begin(), parents.end(), [&tail](auto pair) {
	//		return pair.first == tail;
	//	});
	//	if (found != parents.end()) {
	//		path.emplace_back(found->second);
	//		tail = found->second;
	//	}
	//}
	return path;
}

// This is largely shortest path algorith with a breath first search, but with each path
// being a valid word
void Praxis016(const std::string& start, const std::string& end) {
	// First see the size of words, and only load up word list which
	// matches size to reduce search/mem requirements
	const auto sz = start.size();
	iostreams::stream<iostreams::mapped_file> file("words.txt");
	std::vector<std::string> words;
	words.reserve(6000);
	char buf[50];
	while (file.getline(buf, 50)) {
		if (strlen(buf) == sz) {
			words.push_back(buf);
		}
	}
	auto result = solve(boost::to_lower_copy(start), boost::to_lower_copy(end), words);
	boost::copy(result, std::ostream_iterator<std::string>(std::cout, "\n"));
}