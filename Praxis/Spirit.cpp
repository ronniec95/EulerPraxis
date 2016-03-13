//
//  Praxis014.cpp
//  ProgrammingPraxis
//
//  Created by Ronnie Chowdhury on 12/03/2016.
//  Copyright © 2016 Ronnie Chowdhury. All rights reserved.
//

#include <stdio.h>

#include "Praxis001.hpp"
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/sequence.hpp>
#include <iostream>
#include <string>

using namespace boost;
using namespace boost::spirit;

struct employee {
    int age;
    std::string name;
    std::string location;
    double salary;
};

BOOST_FUSION_ADAPT_STRUCT(
                          employee,
                          (int, age),
                          (std::string,name)
                          (std::string,location)
                          (double, salary))

template<typename It>
struct employee_parser : qi::grammar<It,employee(),ascii::space_type> {
    employee_parser() : employee_parser::base_type(start) {
        quoted_string %= qi::lexeme['"' >> +(qi::char_ - '"') >> '"'];
        start %=
        qi::lit("employee") >> '{'
        >> qi::int_ >> ','
        >> quoted_string >> ','
        >> quoted_string >> ','
        >> qi::double_ >> '}';
    }
    
    qi::rule<It,std::string(),ascii::space_type> quoted_string;
    qi::rule<It,employee(),ascii::space_type> start;
};

void SpiritTest() {
    std::string words = "I am a car";
    fusion::vector<int,char,std::string> stuff (1,'c',"hello");
    int i = fusion::at_c<0>(stuff);
    
    //fusion::for_each(stuff,[](auto xml){
    //    std::cout << '<' << typeid(xml).name() << '>'
    //    << xml
    //    << "</" << typeid(xml).name() << '>';
    //});
    
    const std::string employee_str = "employee {23,\"Ronnie,\"London\",34.0}";
    employee_parser<std::string::const_iterator> emp;
    auto iter = employee_str.begin();
    employee res;
    bool r = qi::phrase_parse(iter,employee_str.end(),emp,ascii::space,res);
    
    if(r && iter == employee_str.end()) {
        std::cout << fusion::as_vector(res) << std::endl;
    } else {
        std::cout << "Failed " << std::string(iter,employee_str.end()) << std::endl;
    }
}