/*****************************************************
 * Author: Eric Hansson
 * File: Grammar.cpp
 * Date:
 * Purpose:
*******************************************************/
#include "Grammar.hpp"
#include "Token.hpp"
#include <iostream>
#include <iterator>
#include <string>

using namespace std;

string program(std::istream &is){

}

string declaration(std::istream &is){
    string typeVal = type(is);
    string idlistVal = idlist(is);

    int pos = is.tellg();
    
    Token tok;
    tok.get(is);

    if (tok.type()==SEMICOLON) {
        return tok.value(); 
    }
    else {
        is.seekg(pos);
        cerr << "Expected ';', got:" << tok << endl;
        return 0;
    }
}

// works better, but need debugging
string idlist(std::istream &is){
    int pos = is.tellg();

    Token tok;
    tok.get(is);
    
    string idVal = tok.value();
    if (tok.type()==ID) {
        tok.get(is);
        if(tok.type()!=COMMA){
            cerr << "Unexpected token: " << tok << endl;
        }
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

string compound(std::istream &is){
    int pos = is.tellg();

    Token tok;
    tok.get(is);

    if (tok.type()==BEGIN) {
        string stmtlistVal = stmtlist(is);

        tok.get(is);

        if (tok.type()!=END) {
            is.seekg(pos);
            cerr << "Expected 'END', got:" << tok << endl;
        }
        return stmtlistVal;
    }
    else {
        cerr << "Unexpected token: " << tok << endl;
        return 0;
    }
}

string stmtlist(std::istream &is){
    string stmtVal = stmt(is);

    int pos = is.tellg(); 

    Token tok;
    tok.get(is);

    if (tok.type()==SEMICOLON) {
        return stmtVal + tok.value() + stmtlist(is); 
    }
    else {
        is.seekg(pos);
        return stmtVal;
    }

}

string stmt(std::istream &is){
    string compoundVal = compound(is);

    Token tok;
    tok.get(is);

    if (tok.type()==ID) {
        tok.get(is); 

        if (tok.type()==LPAREN) {
            string pval = exprlist(is);

            if (tok.type()!=RPAREN)
                cerr << "Expected ')', got: " << tok << endl;

           return pval;    
        }

        if (tok.type()==ASSIGNOP) { 
            return expr(is);
        }
    }
    if (tok.type()==IF) {  
        string exprVal = expr(is);
        tok.get(is);

        if (tok.type()==THEN) {
            return compound(is); 
        }
        if (tok.type()==ELSE) {
            return compound(is); 
        }
    }

    if (tok.type()==WHILE) {
        tok.get(is);
        if (tok.type()==LPAREN) {
            string exprVal = expr(is);

            if (tok.type()!=RPAREN)
                cerr << "Expected ')', got: " << tok << endl;

           return exprVal;    
        }
        return compoundVal;
    
    }
    else {
        return compoundVal;
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
        string idVal = tok.value();
        tok.get(is);
        
        if (tok.type()==LPAREN) {
            string pval = exprlist(is);
            string lpar = tok.value();

            tok.get(is); 

            if (tok.type()!=RPAREN)
                cerr << "Expected ')', got: " << tok << endl;

           return idVal + lpar + pval + tok.value(); 
        }
        return tok.value();
    }
    
    else if(tok.type()==NUM_REAL){
        return tok.value(); 
    }
    else if(tok.type()==NUM_INT){
        return tok.value(); 
    }
    else if (tok.type()==LPAREN) {
        string exprVal = expr(is);
        string lpar = tok.value();

        tok.get(is);
        if (tok.type()!=RPAREN) {
            cerr << "Expected ')' got: " << tok << endl;
        }
        return lpar + exprVal + tok.value();
    }
    else {
        cerr << "Unexpected token: " << tok << endl;
        return 0;
    }
}
