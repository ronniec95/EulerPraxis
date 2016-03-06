//
//  Praxis001.cpp
//  ProgrammingPraxis
//
//  Created by Ronnie Chowdhury on 23/02/2016.
//  Copyright © 2016 Ronnie Chowdhury. All rights reserved.
//
#include "stdafx.h"
#include "Praxis.h"
#include <iomanip>
#include <boost/convert.hpp>
#include <boost/convert/lexical_cast.hpp>


struct boost::cnv::by_default : public boost::cnv::lexical_cast {};

void Praxis001() {
    // Operators
    std::map<char,std::function<double(double,double)>> op;
    op.insert({'+',[](double a,double b) { return a+b; }});
    op.insert({'-',[](double a,double b) { return a-b; }});
    op.insert({'*',[](double a,double b) { return a*b; }});
    op.insert({'/',[](double a,double b) { return a/b; }});
  //  while(true)
    {
        // Read tokens until newline
        std::vector<std::string> tokens;
		std::cin.clear();
        std::copy(std::istream_iterator<std::string>(std::cin),
                  std::istream_iterator<std::string>(),std::back_inserter(tokens));

        // Push things on the stack
        std::stack<double> st;
        std::for_each(std::begin(tokens), std::end(tokens), [&op,&st](const std::string& i){
            auto it = op.find(*i.data());
            if(it == op.end()) {
                st.push(boost::convert<double>(i).value_or(0));
            } else {
                // Pop values and put the result on stack
                auto a = st.top(); st.pop();
                auto b = st.top(); st.pop();
                auto val = it->second(a,b);
                st.push(val);
            }
        });
        
        // Pop final value and print
        if(!st.empty())
            std::cout << std::setprecision(3) << st.top() << std::endl;
	}
}