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

// works better, but need debugging
string idlist(std::istream &is){
    int pos = is.tellg();

    Token tok;
    tok.get(is);
    
    string idVal = tok.value();

    if (tok.type()==ID) {
        tok.get(is);
        if(tok.type()!=COMMA) 
           cerr << "Unexpected token: " << tok << endl;

        return idVal + tok.value() + idlist(is);
    }
    else {
        // unget, read one too much
        is.seekg(pos);
        return idVal;
    }

}

string type(std::istream &is){
    int pos = is.tellg();

    Token tok;
    tok.get(is);

    if(tok.type()==INTEGER){
        return tok.value(); 
    }
    else if(tok.type()==FLOAT){
        return tok.value(); 
    }
    else if(tok.type()==VOID){
        return  tok.value(); 
    }
    else {
        is.seekg(pos);
        cerr << "Unexpected token: " << tok << endl;
        return 0;
    }
}

string exprlist(std::istream &is){
    string exprVal = expr(is);
    
    int pos = is.tellg();

    Token tok;
    tok.get(is);

    if (tok.type()==COMMA) {
        return exprVal + tok.value() + exprlist(is); 
    }
    else {
        is.seekg(pos);
        return exprVal;
    }
}

// need to look at this
string expr(std::istream &is){
    string simpexprVal = simpexpr(is);

    int pos = is.tellg();

    Token tok;
    tok.get(is);

    if (tok.type()==RELOP) {
        return simpexprVal + tok.value() + simpexpr(is);
    }
    else {
        is.seekg(pos);
        return simpexprVal;
    }
}

string simpexpr(std::istream &is){
    string termVal = term(is);

    int pos = is.tellg();

        Token tok;
    tok.get(is);

    if (tok.type()==ADDOP) {
        return termVal + tok.value() + simpexpr(is); 
    }
    else {
        // unget the token
        is.seekg(pos);
        return termVal;
    }
}

string term(std::istream &is){
    string result = factor(is);

    int pos = is.tellg();

    Token tok;
    tok.get(is);

    if (tok.type()==MULOP) {
        return result + tok.value() + term(is);
    }
    else {
        is.seekg(pos);
        return result;
    }
}

string factor(std::istream &is){
    Token tok;    
    tok.get(is);

    if(tok.type()==ID){
            return tok.value();
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
        return tok.value(); 
    }
    else if(tok.type()==NUM_INT){
        return tok.value(); 
    }
    else {
        cerr << "Unexpected token: " << tok << endl;
        return 0;
    }
}
