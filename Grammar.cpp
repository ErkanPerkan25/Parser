/*****************************************************
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

bool idlist(std::istream &is){
    int pos = is.tellg();

    Token tok;
    tok.get(is);

    if (tok.type()==ID) {
        tok.get(is);
        if (tok.type()==COMMA) {
            return true;
        }
    }
    else {
        // unget, read one too much
        is.seekg(pos);
        return false;
    }

}

bool type(std::istream &is){
    int pos = is.tellg();

    Token tok;
    tok.get(is);

    if(tok.type()==INTEGER){
        return true; 
    }
    else if(tok.type()==FLOAT){
        return true; 
    }
    else if(tok.type()==VOID){
        return  true; 
    }
    else {
        is.seekg(pos);
        cerr << "Unexpected token: " << tok << endl;
        return false;
    }
}

bool exprlist(std::istream &is){
}

bool expr(std::istream &is){
}

bool simpexpr(std::istream &is){
    int pos = is.tellg();

    bool termVal = term(is);

    Token tok;
    tok.get(is);

    if (tok.type()==ADDOP) {
        return true; 
    }
    else {
        is.seekg(pos);
        return termVal;
    }
}

bool term(std::istream &is){
    bool factorVal = factor(is);

    int pos = is.tellg();

    Token tok;
    tok.get(is);

    if (tok.type()==MULOP) {
        return true;
    }
    else {
        is.seekg(pos);
        return factorVal;
    }
}

bool factor(std::istream &is){
    Token tok;    
    tok.get(is);

    if(tok.type()==ID){
        return true;
    }
    /*
    else if(tok.type()== ID && tok.type()==LPAREN){
        string pval = exprlist(is);

        tok.get(is); 

        if (tok.type()!=RPAREN)
            cerr << "Expected ')', got: " << tok << endl;

       return pval; 
    }
    */
    else if(tok.type()==NUM_REAL){
        return true; 
    }
    else if(tok.type()==NUM_INT){
        return true; 
    }
    else {
        cerr << "Unexpected token: " << tok << endl;
        return 0;
    }
}
