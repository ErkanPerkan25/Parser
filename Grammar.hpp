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

std::string exprlist(std::istream &);

void expr(std::istream &);
void expr2(std::istream &);

void simpexpr(std::istream &);
void simpexpr2(std::istream &);

void term(std::istream &);
void term2(std::istream &);

std::string factor(std::istream &);
#endif
