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

string idlist(std::istream &is){
    int pos = is.tellg();

    Token tok;
    tok.get(is);

    if (tok.type()==ID) {
        tok.get(is);
        if (tok.type()==COMMA) {
            return idlist(is);
        }
    }
    else {
        // unget, read one too much
        is.seekg(pos);
        return 0;
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
}

string expr(std::istream &is){
    int pos = is.tellg();

    string simpexprVal = simpexpr(is);

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
    int pos = is.tellg();

    string termVal = term(is);

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
            return tok.value().c_str();
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
        return tok.value().c_str(); 
    }
    else if(tok.type()==NUM_INT){
        return tok.value().c_str(); 
    }
    else {
        cerr << "Unexpected token: " << tok << endl;
        return 0;
    }
}
