#include "stdafx.h"
#include "Praxis.h"
#include <fstream>
#include <ppl.h>
#include <boost\tokenizer.hpp>
#include <boost\algorithm\string.hpp>
#include <boost/range/irange.hpp>
#include "Utils.h"

using namespace boost;

auto find_key_length_vec(const std::vector<int>& crypt) {
	// Take first 2 to n chars
	// Factorise to find key
	// Coincidence index
	std::set<uint64_t> keylengths;
	// Create 2-15 character string
	auto cryptrng = make_iterator_range(crypt.begin(), crypt.begin() + 5);
	for (auto beg = cryptrng.begin(); beg != cryptrng.end(); beg++ ) {
		auto keyrng = make_iterator_range(beg + 2, beg + 20);
		for (auto end = keyrng.begin(); end != keyrng.end();end++) {
			std::vector<int> search_vector(end, crypt.end());
			auto res = search(end,crypt.end(), beg, end);
			auto d = (res != crypt.end() ? std::distance(beg, res) : 0);
			if (d)
				keylengths.insert(d);
			else {
				break;
			}
		}
	}
	// factorise key lengths by first 15 primes
	// See which number has the highest hit rate
	std::vector<int> primes = { 2,3,5,7,11,13,17,19,23,29,31,37,41,43 };
	std::vector<uint64_t> results;
	for (auto i : keylengths) {
		auto res = i;
		for (auto prime : primes) {
			if (res == 1 || res == prime) {
				results.emplace_back(res);
				break;
			}
			while (res % prime == 0) {
				res = res / prime;
				results.emplace_back(res);
			}
		}
	}
	// How many of each, max number is likely to be password length
	// Use a capture to store a temporary map
	uint64_t likelylength = 0;
	range::for_each(results,  [frequency=std::map<uint64_t, int>(),&likelylength]  (auto v) mutable {
		const auto& it = frequency.find(v);
		if (it != frequency.end())
			it->second++;
		else
			frequency.insert(std::make_pair(v, 1));
		likelylength = (std::max_element(frequency.begin(), frequency.end(), [](const auto& lhs, const auto& rhs) { return lhs.second < rhs.second; }))->first;
	});
	return  likelylength;
}

auto analyse_freq(const std::string& buf) {
	std::vector<double> frequency(128, 0);
	// Populate the frequency of characters by directly indexing an array
	// Much more cache friendly than a map
	range::for_each(buf, [&frequency](auto ch) {
		if (ch > 0)
			frequency[ch]++;
	});
	range::for_each(frequency, [sum = accumulate(frequency, 0.0)](auto& i){
		i = i / sum;
	});
	return frequency;
}



void Praxis012() {
	// Read the file
	// Find repeated texts to identify length of password
	// Repeat the xor with the pw against the string.
	auto buf = read_file("Creation.txt");
	// Tokenise to char
	tokenizer<char_separator<char>> tok(buf, char_separator<char>( "\t"," "));
	std::vector<int> crypt;
	range::transform(tok, std::back_inserter(crypt), [](auto i) { return ::atoi(i.data()); });

	// We know the password is <= chars
	// Find a sequence of 2,3,4 numbers, find the distance to the next occurence
	auto n = find_key_length_vec(crypt);

	// Find distribution of characters in english
	auto english_freq = analyse_freq(read_file("Story - Copy.txt"));

	// Frequency analysis
	for (int pos = 0; pos < n; pos++) {
		for (int chr = 65; chr < 123; chr++) {
			auto res = accumulate(crypt | adaptors::strided(n), std::string(), [&chr](auto buf, auto& ch) {
				buf.push_back(static_cast<char>(ch ^ chr));
				return buf;
			});
			auto charfreq = analyse_freq(res);
			// Sum product
			auto sumproduct = accumulate(charfreq | adaptors::indexed(), 0.0, [&charfreq](auto num, auto ch) {
				return ch.index() * (ch.value()*100.0);
			});
		}
	}

	// Compare Nth char frequency analysis with normal english, and see how close it is. 
	// sum(sqrt(distance^2))
	// Decrypt
	std::string plaintext;
	const std::string pw = "Genesis";
	range::transform(crypt | adaptors::indexed(), std::back_inserter(plaintext), [&pw](auto i) {
		return i.value() ^ pw[i.index() % pw.size()];
	});
}