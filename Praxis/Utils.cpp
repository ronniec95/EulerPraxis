#include "stdafx.h"
#include "Utils.h"
#include <streambuf>
#include <fstream>

std::string read_file(const std::string & filename) {
	std::string buf;
	std::fstream f(filename);
	if (f.is_open()) {
		std::copy(std::istream_iterator<char>(f), std::istream_iterator<char>(), std::back_inserter(buf));
	}
	return std::string();
}
