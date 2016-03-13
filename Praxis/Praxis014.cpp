//
//  Praxis014.cpp
//  ProgrammingPraxis
//
//  Created by Ronnie Chowdhury on 12/03/2016.
//  Copyright © 2016 Ronnie Chowdhury. All rights reserved.
//

#include "stdafx.h"
#include "Praxis.h"
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/bind.hpp>
#include <fstream>
#include <streambuf>
#include <boost/program_options.hpp>
#include <boost/algorithm/string.hpp>
#include <string>
using namespace boost;
using namespace boost::spirit;

namespace po = boost::program_options;

void Praxis014(const std::string& cmd) {
    // Program options for parsing cmd line
    po::options_description desc("Praxis options");
    desc.add_options()
        ("file",po::value<std::string>())
        ("n",po::value<int>());
    std::vector<std::string> args;
    boost::split(args, cmd, boost::is_any_of(" "));
    po::variables_map vm;
    po::store(po::command_line_parser(args).options(desc).run(),vm);
    po::notify(vm);

    // Read the file
    std::ifstream f(vm["file"].as<std::string>());
    std::string foo((std::istreambuf_iterator<char>(f)),std::istreambuf_iterator<char>());
    // Boost spirit for extracting words (could use regex...)
    std::vector<std::pair<std::string,int>> result;
    auto ok = qi::phrase_parse(foo.begin(),foo.end(),
                               *qi::lexeme[+qi::alpha][([&result](auto i) {
        std::string match(i.begin(),i.end());
        const auto& found = std::find_if(result.begin(),result.end(),[&match](auto p) { return p.first == match; });
        if (found != result.end()) {
            found->second++;
        } else {
            result.push_back(std::make_pair(match,1));
        }
    })],~qi::alpha);
    if(ok) {
        // Only need to pop the first few elements of the heap rather than sorting the whole collection
        // Is this faster? Depends on cache and number of words
        std::make_heap(result.begin(),result.end(),[](const auto& lhs,const auto& rhs) { return lhs.second < rhs.second;});
        for(auto i = result.begin(); i < result.begin()+vm["n"].as<int>(); i++) {
            std::cout <<  i->first << " " << i->second << std::endl;
        }
    }
}