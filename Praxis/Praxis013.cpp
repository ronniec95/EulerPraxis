//
//  Praxis13.cpp
//  ProgrammingPraxis
//
//  Created by Ronnie Chowdhury on 10/03/2016.
//  Copyright © 2016 Ronnie Chowdhury. All rights reserved.
//
/*=============================================================================
 Copyright (c) 2001-2010 Joel de Guzman
 
 Distributed under the Boost Software License, Version 1.0. (See accompanying
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/
///////////////////////////////////////////////////////////////////////////////
//
//  A Roman Numerals Parser (demonstrating the symbol table). This is
//  discussed in the "Symbols" chapter in the Spirit User's Guide.
//
//  [ JDG August 22, 2002 ] spirit1
//  [ JDG March 13, 2007 ]  spirit2
//
///////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

#include <iostream>
#include <string>

using namespace boost;
using namespace boost::spirit;

    // symbol tables
    struct hundreds_ : qi::symbols<char,unsigned> {
        hundreds_() {
            add("C",100)("CC",200)("CCC",300)("CD",400)("D",500)("DC",600)("DCC",700)("DCCC",800)("CM",900);
        };
    } hundreds;
    struct tens_ : qi::symbols<char,unsigned> {
        tens_() {
            add("X",10)("XX",20)("XXX",30)("XL",40)("L",50)("LX", 60)("LXX",70)("LXXX",80)("XC",90);
        }
    } tens;
    struct ones_ : qi::symbols<char,unsigned> {
        ones_() {
            add("I",1)("II", 2)("III", 3)("IV", 4)("V", 5)("VI", 6)("VII",7)("VIII",8)("IX",9);
        }
    } ones;

    // grammar
    template<typename It>
    struct roman : qi::grammar<It,unsigned()> {
        roman() : roman::base_type(start) {
            using namespace qi;
            // Allow for both subtractive and additive versions of roman numerals
            start = qi::eps [_val=0] >>
            (
             +lit('M')[_val+=1000]
             || *hundreds [_val+=_1]
             || *tens [_val+=_1]
             || *ones [_val+=_1]
             );
        }
        qi::rule<It,unsigned()> start;
    };


void Praxis013()
{
    roman<std::string::const_iterator> roman_parser;
    const std::string str = "XXXX";
    unsigned result = 0;
    auto iter = str.begin();
    bool r = spirit::qi::parse(iter, str.end(), roman_parser, result);
    if (r && iter == str.end()) {
        std::cout << result << std::endl;
    } else {
        std::string rest(iter,str.end());
        std::cout << "Failed " << rest << std::endl;
    }
}

