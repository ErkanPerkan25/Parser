/******************************************************
 * Author: Eric Hansson
 * File: Grammar.cpp
 * Date:
 * Purpose:
*******************************************************/
#include "Grammar.hpp"
#include "Token.hpp"

using namespace std;

void program(std::istream &){

}

string exprlist(std::istream &);

void expr(std::istream &);
void expr2(std::istream &);

void simpexpr(std::istream &);
void simpexpr2(std::istream &);

void term(std::istream &);
void term2(std::istream &);

string factor(std::istream &is){
    Token tok;    
    tok.get(is);

    if(tok.type()==ID){
        return tok.value();
    }
    else if(tok.type()== ID && tok.type()==LPAREN){
        string pval = exprlist(is);

        tok.get(is); 

        if (tok.type()!=RPAREN)
            cerr << "Expected ')', got: " << tok << endl;
       return pval; 
    }
    else if(tok.type()==NUM_REAL){
        //return tok.value(); 
    }
    else if(tok.type()==NUM_INT){
    
    }
    
    else {
        cerr << "Unexpected token: " << tok << endl;
        return 0;
    }
}
