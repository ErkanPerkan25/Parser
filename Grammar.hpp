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

bool type(std::istream &);

bool exprlist(std::istream &);

bool expr(std::istream &);

bool simpexpr(std::istream &);

bool term(std::istream &);

bool factor(std::istream &);
#endif
