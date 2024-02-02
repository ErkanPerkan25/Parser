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
    Token tok;
    tok.get(is);

    if (tok.type()==ID) {
        tok.get(is);
        if (tok.type()==COMMA) {
            idlist(is);
        }
        return true;
    }
    else {
        return false;
    }

}

bool type(std::istream &is){
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
        cerr << "Unexpected token: " << tok << endl;
        return 0;
    }
}
/*
string exprlist(std::istream &);
*/
bool expr(std::istream &is){
    bool simpexprVal = simpexpr(is);

    bool expr2Val = expr2(is,simpexprVal);

    return expr2(is, expr2Val);
}
bool expr2(std::istream &is, bool incomingValue){
    int pos = is.tellg();
    Token tok;
    tok.get(is);

    bool result = incomingValue;

    if (tok.type()==RELOP) {
        result = true;
    }
    else {
        is.seekg(pos);
        return result;
    }
    
    return expr2(is, result);
}



bool simpexpr(std::istream &is){
    bool termVal = term(is);

    bool simpexpr2Val = simpexpr2(is, termVal);

    return simpexpr2(is, simpexpr2Val);

}
bool simpexpr2(std::istream &is, bool incomingValue){
    int pos = is.tellg();
    Token tok;
    tok.get(is);

    bool result = incomingValue;

    if (tok.type()==ADDOP) {  
        result = true;
    }
    else{
        is.seekg(pos);
        return result;
    }

    return simpexpr2(is,result);

}

bool term(std::istream &is){
    bool factorVal = factor(is);

    bool term2Val = term2(is, factorVal);

    return term2Val;
}

bool term2(std::istream &is, bool incomingValue){
    int pos = is.tellg();

    Token tok;
    tok.get(is);

    bool result = incomingValue;

    if(tok.type()==MULOP){
        result = true;
    }
    else {
        is.seekg(pos);
        return result;
    }

    return term2(is, result);
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
