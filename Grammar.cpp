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

string idlist(std::istream &is){
    Token tok;
    tok.get(is);
    if(tok.type()==ID){
    }
}

string idlist2(std::istream &is){

}

string type(std::istream &is){
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
        cerr << "Unexpected token: " << tok << endl;
        return 0;
    }
}

string exprlist(std::istream &);

void expr(std::istream &);
void expr2(std::istream &);

void simpexpr(std::istream &);
void simpexpr2(std::istream &);

string term(std::istream &is){
    string factorVal = factor(is);

    string term2Val = term2(is, factorVal);

    return term2Val;
}
string term2(std::istream &is, string incomingValue){
    int pos = is.tellg();

    Token mul;
    mul.get(is);

    string result = incomingValue;
    
    if(mul.type()==MULOP){
        string termVal = incomingValue; 
        result += termVal;
    }
    else{
        is.seekg(pos);
        return incomingValue;
    }

    return term2(is,result);

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
