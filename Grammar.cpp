/*****************************************************
 * Author: Eric Hansson
 * File: Grammar.cpp
 * Date:
 * Purpose:
*******************************************************/
#include "Grammar.hpp"
#include "Token.hpp"
#include <iostream>
#include <string>

using namespace std;


string program(std::istream &is){
    return declaration(is) + program(is);
}

string declaration(std::istream &is){
    string typeVal = type(is);
    string idlistVal = idlist(is);

    int pos = is.tellg();
    
    Token tok;
    tok.get(is);

    if (tok.type()!=SEMICOLON) {
        is.seekg(pos);
        cerr << "Expected ';', got:" << tok << endl;
        return 0;
    }
    else if (tok.type()==SEMICOLON) {
        return typeVal + " " + idlistVal + tok.value() + "\n"; 
    }
    else {
        is.seekg(pos);
        cerr << "Expected ';', got:" << tok << endl;
        return 0;
    }
}

string idlist(std::istream &is){
    Token tok;
    tok.get(is);
    
    string idVal = tok.value();
    if (tok.type()==ID) {
        int pos = is.tellg();

        tok.get(is);

        if(tok.type()!=COMMA){
            is.seekg(pos);
            return idVal;
        }
        else if (tok.type()==COMMA) {
            return idVal + tok.value() + " " + idlist(is);
        }
        else {
            is.seekg(pos);
            return idVal;
        }
    }
    else {
        cerr << "Unexpected token: " << tok << endl;
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

string compound(std::istream &is){
    int pos = is.tellg();

    Token tok;
    tok.get(is);

    if (tok.type()==BEGIN) {
        string beginVal = "  " + tok.value() + "\n";
        string stmtlistVal = "    " + stmtlist(is) + "\n";

        tok.get(is);

        if (tok.type()!=END) {
            is.seekg(pos);
            cerr << "Unexpected token: " << tok << endl;
            return 0;
        }
        else if(tok.type()==END) {
            return beginVal + stmtlistVal + "  " + tok.value();
        }
        else {
            is.seekg(pos);
            cerr << "Unexpected token: " << tok << endl;
            return 0;
        }
    }
    else {
        is.seekg(pos);
        cerr << "Unexpected token: " << tok << endl;
        return 0;
    }
}

string stmtlist(std::istream &is){
    string stmtVal = stmt(is);

    int pos = is.tellg(); 

    Token tok;
    tok.get(is);
    if (tok.type()!=SEMICOLON){
        is.seekg(pos);
        return stmtVal;
    }
    else if (tok.type()==SEMICOLON) {
        return stmtVal + tok.value() + "\n" + stmtlist(is); 
    }
    else {
        is.seekg(pos);
        return stmtVal;
    }
}

string stmt(std::istream &is){

    Token tok;
    tok.get(is);
    
    string idVal;
    if(tok.type()==ID){
        int pos = is.tellg();
        idVal = tok.value();
        
        tok.get(is);

        if (tok.type()!=LPAREN && tok.type()!=ASSIGNOP) {
            is.seekg(pos);
            return idVal; 
        }
        else if (tok.type()==LPAREN) {
            string pval = exprlist(is);
            
            tok.get(is);

            if (tok.type()!=RPAREN){
                cerr << "Expected ')', got: " << tok << endl;
            }
           return idVal + "(" + pval + ")"; 
        }
        else if (tok.type()==ASSIGNOP) { 
            return idVal + " = " + expr(is);
        }
        else {
            is.seekg(pos);
            return idVal;
        }
    }
     
    if (tok.type()==IF) {  
        string exprVal = expr(is);
        string ifVal = tok.value();

        int pos = is.tellg();

        tok.get(is);

        if (tok.type()==THEN) {
            string compVal = compound(is);
            tok.get(is);
            if (tok.type()==ELSE) {
                return ifVal + " " + exprVal + " then" + "\n" + compVal +"\n else \n" + compound(is); 
            }
            else {
                is.seekg(pos);
                cerr << "Unexpected token: " << tok << endl;
                return 0;
            }
        }
        else {
            is.seekg(pos);
            cerr << "Unexpected token: " << tok << endl;
            return 0;
        }
    }

    if (tok.type()==WHILE) {
        int pos = is.tellg();

        tok.get(is);

        if (tok.type()!=LPAREN) {
            is.seekg(pos);
            return 0; 
        }

        else if (tok.type()==LPAREN) {
            string exprVal = expr(is);
            
            tok.get(is);

            if (tok.type()!=RPAREN){
                cerr << "Expected ')', got: " << tok << endl;
            }

           return "while ( " + exprVal + " ) \n" + compound(is); 
        }
        else {
            is.seekg(pos);
            return 0;
        }
    }
    else {
        return compound(is);
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
    
    string idVal;
    if(tok.type()==ID){
        int pos = is.tellg();

        idVal = tok.value();
        
        tok.get(is);
        if (tok.type()!=LPAREN) {
            is.seekg(pos);
            return idVal; 
        }

        else if (tok.type()==LPAREN) {
            string pval = exprlist(is);
            
            tok.get(is);

            if (tok.type()!=RPAREN){
                cerr << "Expected ')', got: " << tok << endl;
            }

           return idVal + "(" + pval + ")"; 
        }
        else {
            is.seekg(pos);
            return idVal;
        }
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
