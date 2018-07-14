#pragma once

#include <boost/test/unit_test.hpp>
#include <boost/version.hpp>

#if BOOST_VERSION < 106400

/*
 * See boost ticket #12778
 * https://svn.boost.org/trac10/ticket/12778
 */
#define nullptr (void*)0x00

#endif
