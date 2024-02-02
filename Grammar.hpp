/*********************************************************
 * Author: Eric Hansson
 * File: Grammar.hpp
 * Date: 
 * Purpose: Implementing grammar 
**********************************************************/
#ifndef _GRAMMAR_HPP_
#define _GRAMMAR_HPP_

#include <istream>

void program(std::istream &);

bool exprlist(std::istream &);

bool idlist(std::istream &);
bool idlist2(std::istream &, std::string incomingValue);

bool type(std::istream &);

bool expr(std::istream &);
bool expr2(std::istream &, bool incomingValue);

bool simpexpr(std::istream &);
bool simpexpr2(std::istream &, bool incomingValue);

bool term(std::istream &);
bool term2(std::istream &, bool incomingValue);

bool factor(std::istream &);
#endif
