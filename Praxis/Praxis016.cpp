//
//  Praxis016.cpp
//  ProgrammingPraxis
//
//  Created by Ronnie Chowdhury on 12/03/2016.
//  Copyright © 2016 Ronnie Chowdhury. All rights reserved.
//

#include "stdafx.h"
#include "Praxis.h"
#include <boost/spirit/include/qi.hpp>

using namespace boost;
using namespace boost::spirit;

template<typename It>
struct csv_parser : qi::grammar<It,std::vector<std::string>()>
{
    csv_parser() : csv_parser(start) {
        plain = qi::char_ - '"' - ',';
        quoted = '"' >> *plain >> '"';
        mixed = *(plain|quoted);
        start %= +(mixed) >> *(delim >> mixed);
    }
    
    qi::rule<It> delim;
    qi::rule<It,char> noquote;
    qi::rule<It,std::string()> plain,quoted,mixed;
    qi::rule<It,std::vector<std::string>()> start;
};

void Praxis016() {
    // If we are doing a csv parser, may as well use spirit
    
}