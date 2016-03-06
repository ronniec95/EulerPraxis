#include "stdafx.h"
#include "Praxis.h"

#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>
#include <boost/range/irange.hpp>

using namespace boost;

typedef std::pair<std::set<std::string>::const_iterator,std::set<std::string>::const_iterator> paircmpiter;
typedef std::vector < std::pair<std::set<std::string>::const_iterator, int>> chainlist;
// Comparison
auto paircmp = [](const paircmpiter& lhs, const paircmpiter& rhs) { return (*lhs.first + *lhs.second) < (*rhs.first + *rhs.second); };

auto choose_word(
	std::set<std::string>::const_iterator& word1,
	std::set<std::string>::const_iterator& word2,
	const std::map <paircmpiter, chainlist, decltype(paircmp)>& markov) {
	auto nextwordchoice = markov.find(std::make_pair(word1,word2));
	auto choices = nextwordchoice->second;
	std::set<std::string>::const_iterator word3;
	// Single word choice
	if (choices.size() == 1) {
		word3 = choices.begin()->first;
	}
	else {
		// Sum of options
		auto sum = 0U;
		range::for_each(choices, [&sum](auto i) {return sum += i.second; });
		auto choice = rand() % sum;
		if (sum == choices.size()) {
			word3 = (choices.begin() + choice)->first;
		}
		else {
			auto choice_sum = 0U;
			for (auto i : choices) {
				choice_sum += i.second;
				if (choice_sum >= choice) {
					word3 = i.first;
					break;
				}
			}
		}
	}
	word1 = word2;
	word2 = word3;
	return word3;
}

void Praxis011() {
	typedef double freq;
	std::string story;
	std::fstream file("Story.txt");
	if (file.is_open()) {
		// Fastest way to read in a file
		const size_t sz = 512 * 1024;
		char buf[sz];
		story.reserve(sz);
		while (file) {
			file.read(buf, sz);
			story.append(buf);
		}
	}
	// Split into strings (as iterators) and just store unique words
	std::set<std::string> words;
	split(words, story, is_any_of(" "));

	// Markov chain is 2 words pointing to a vector of alternative follow-on words with a frequency counter
	std::map <paircmpiter, chainlist, decltype(paircmp)> markov(paircmp);
	// Iterate over the story again splitting on a space
	tokenizer<char_separator<char>> tokens(story, char_separator<char>(" "));
	auto token = tokens.begin();
	auto token2 = token++;
	auto token3 = token++;
	for(; token3 != tokens.end(); token++, token2++, token3++) {
		auto word1 = words.find(*token);
		auto word2 = words.find(*token2);
		auto word3 = words.find(*token3);
		auto key = std::make_pair(word1, word2);
		auto chain = markov.find(key);
		if (chain == markov.end()) {
			markov.insert(std::make_pair(key, chainlist({ std::make_pair(word3,1) })));
		}
		else {
			auto& word = boost::find_if(chain->second, [&word3](auto& val) { return val.first == word3;  });
			if (word != chain->second.end()) {
				word->second++;
			}
			else {
				chain->second.emplace_back(std::make_pair(word3, 1));
			}
		}
	}

	// Now just sort the wordlists which have 2 or more options
	for_each(markov | adaptors::filtered([](auto i) { return i.second.size() > 1; }), [](auto& m) {
		sort(m.second,[](const auto& lhs, const auto& rhs) { return lhs.second < rhs.second; });
	});
	// Choose a random point in the markov chain to start
	auto markoviter = markov.begin();
	for (auto i = 0U; i <= rand() % markov.size(); i++, markoviter++); // Do nothing
	auto start = markoviter->first;
	auto word1 = start.first, word2 = start.second;
	std::cout << *word1 << " " << *word2 << " ";
	for_each(irange(0, 500),[&word1,&word2,&markov](auto) { 
		std::cout << *choose_word(word1, word2, markov) << " ";
	});
}