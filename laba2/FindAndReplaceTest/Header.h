#pragma once


#include <stdio.h>
#include <tchar.h>

#include "boost/test/unit_test.hpp"

#define BOOST_TEST_INCLUDED

#pragma warning (disable:4702) // To disable 4702 warning in boost
#include <boost/test/unit_test.hpp>
#include <boost/algorithm/string/replace.hpp>
#define BOOST_TEST_MODULE

// TODO: reference additional headers your program requires here