/*********************************************************
 * Author: Eric Hansson
 * File: Grammar.hpp
 * Date: 
 * Purpose: Implementing grammar for parser
**********************************************************/
#ifndef _GRAMMAR_HPP_
#define _GRAMMAR_HPP_

#include <istream>

void program(std::istream &);

std::string stmt(std::istream &);

std::string exprlist(std::istream &);

std::string idlist(std::istream &);

std::string type(std::istream &);

std::string exprlist(std::istream &);

std::string expr(std::istream &);

std::string simpexpr(std::istream &);

std::string term(std::istream &);

std::string factor(std::istream &);
#endif
