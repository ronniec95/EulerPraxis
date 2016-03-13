// Praxis.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Praxis.h"

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <boost\log\trivial.hpp>

BOOST_AUTO_TEST_CASE(TestPraxis) {
	Praxis004();
}

