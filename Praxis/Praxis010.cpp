#include "stdafx.h"
#include "Praxis.h"

void Praxis010() {
	auto year = 2011;
	auto a = year % 4;
	auto b = year % 7;
	auto c = year % 19;
	auto d = (19 * c + 15) % 30;
	auto e = (2 * a + 4 * b - d + 34) % 7;
	auto month = static_cast<int>(floor((d + e + 114) / 31));
	auto day = ((d + e + 114) % 31) + 1 + 13; // +13 only till 2099
	std::cout << day << "/" << month << "/" << year << std::endl;
}
