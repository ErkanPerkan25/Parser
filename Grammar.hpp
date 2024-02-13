/*********************************************************
 * Author: Eric Hansson
 * File: Grammar.hpp
 * Date: 2/13/2024 
 * Purpose: Implementing grammar for parser
**********************************************************/
#ifndef _GRAMMAR_HPP_
#define _GRAMMAR_HPP_

#include <istream>

// Grammar for program
std::string program(std::istream &);

// Grammar for declaration
std::string declaration(std::istream &);

// Grammar for idlist
std::string idlist(std::istream &);

// Grammar for type
std::string type(std::istream &);

// Grammar for compound
std::string compound(std::istream &);

// Grammar for stmtlist
std::string stmtlist(std::istream &);

// Grammar for stmt
std::string stmt(std::istream &);

// Grammar for exprlist
std::string exprlist(std::istream &);

// Grammar for expr
std::string expr(std::istream &);

// Grammar for simpexpr
std::string simpexpr(std::istream &);

// Grammar for term
std::string term(std::istream &);

// Grammar for factor
std::string factor(std::istream &);

#endif
