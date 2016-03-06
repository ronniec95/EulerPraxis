// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO: reference additional headers your program requires here
#define BOOST_TEST_MAIN
#define BOOST_ALL_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <boost\log\trivial.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/numeric.hpp>
#include <boost/iterator_adaptors.hpp>
#include <vector>
#include <set>
#include <map>
#include <functional>
#include <numeric>
#include <string>
#include <iostream>
#include <fstream>
#include <stack>
#include <chrono>
#include <array>
#include <random>