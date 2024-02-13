/*****************************************************
 * Author: Eric Hansson
 * File: Grammar.cpp
 * Date: 2/13/2024
 * Purpose: Implementation of grammar for parsing code
 * and beautifing it.
*******************************************************/
#include "Grammar.hpp"
#include "Token.hpp"
#include <iostream>
#include <string>

using namespace std;

// Grammar for the program 
string program(std::istream &is){
    int pos = is.tellg();

    // Read token
    Token tok;
    tok.get(is);
    
    // Checks if there is any declarion 
    if (tok.type()==INTEGER) {
        is.seekg(pos);
        string val = declaration(is);
        return val + program(is); 
    }
    else if (tok.type()==VOID) {
        is.seekg(pos);
        string val = declaration(is);
        return val + program(is); 
    }
    else if (tok.type()==FLOAT) {
        is.seekg(pos);
        string val = declaration(is);
        return val + program(is); 
    }
    else if (tok.type()==BEGIN) {
        is.seekg(pos);
        return "\n" + compound(is); 
    }
    else {
        is.seekg(pos);
        return compound(is);
    }

}

// Grammar of decloration
string declaration(std::istream &is){
    // Gets type and idlist
    string typeVal = type(is);
    string idlistVal = idlist(is);

    int pos = is.tellg();
   
    // Reads next token
    Token tok;
    tok.get(is);

    // If not SEMICOLON, unget and give error
    if (tok.type()!=SEMICOLON) {
        is.seekg(pos);
        cerr << "Expected ';', got:" << tok << endl;
        return "error";
    }
    // SEMICOLON, return a decloration
    else if (tok.type()==SEMICOLON) {
        return typeVal + " " + idlistVal + tok.value() + "\n"; 
    }
    // Otherwise unget token, give error
    else {
        is.seekg(pos);
        cerr << "Expected ';', got:" << tok << endl;
        return "error";
    }
}

// Grammar for idlist
string idlist(std::istream &is){
    // read token
    Token tok;
    tok.get(is);
    
    string idVal;
    // token is ID, check for more ID's
    if (tok.type()==ID) {
        int pos = is.tellg();
        idVal = tok.value();
        
        // gets next token
        tok.get(is);
        
        // if not COMMA, return just ID
        if(tok.type()!=COMMA){
            is.seekg(pos);
            return idVal;
        }
        // if COMMA, return ID and get list
        else if (tok.type()==COMMA) {
            return idVal + tok.value() + " " + idlist(is);
        }
        // otherwise unget token, return ID
        else {
            is.seekg(pos);
            return idVal;
        }
    }
    else {
        cerr << "Unexpected token: " << tok << endl;
        return "error";
    }

}

// Grammar for type
string type(std::istream &is){
    int pos = is.tellg();

    // Read token
    Token tok;
    tok.get(is);

    // if INTEGER, VOID, or FLOAT, return the value of the token
    if(tok.type()==INTEGER){
        return tok.value(); 
    }
    else if(tok.type()==FLOAT){
        return tok.value(); 
    }
    else if(tok.type()==VOID){
        return  tok.value(); 
    }
    // otherwise unget token, and give error
    else {
        is.seekg(pos);
        cerr << "Unexpected token: " << tok << endl;
        return "error type";
    }
}

// Grammar for compound
string compound(std::istream &is){
    int pos = is.tellg();

    // Read token
    Token tok;
    tok.get(is);

    // is it begin, then
    if (tok.type()==BEGIN) {
        // get the value of token and stmtlist
        string beginVal = tok.value();
        string stmtlistVal = "  "+stmtlist(is);

        // read new token
        tok.get(is);

        // if not END, give error
        if (tok.type()!=END) {
            is.seekg(pos);
            cerr << "Unexpected token: " << tok << endl;
            return "error end";
        }
        // if END, return compund with the list of statements
        else if(tok.type()==END) {
            return beginVal +"\n" +stmtlistVal+ "  \n  "  + tok.value() ;
        }
        // otherwise unget token, and give error
        else {
            is.seekg(pos);
            cerr << "Unexpected token: " << tok << endl;
            return "error";
        }
    }
    else {
        is.seekg(pos);
        cerr << "Unexpected token: " << tok << endl;
        return "error";
    }
}

// Grammar for stmtlist
string stmtlist(std::istream &is){
    string stmtVal = stmt(is);

    int pos = is.tellg(); 

    // Read token
    Token tok;
    tok.get(is);
    // if not SEMICOLON, unget and return statement
    if (tok.type()!=SEMICOLON){
        is.seekg(pos);
        return stmtVal;
    }
    // if SEMICOLON, return statment and call it self to have list of statements
    else if (tok.type()==SEMICOLON) {
        return "  " + stmtVal + ";\n  " + stmtlist(is)+"  ";
    }
    // otherwise unget token, return just the statement
    else {
        is.seekg(pos);
        return stmtVal +"\n";
    }
}

// Grammar for stmt
string stmt(std::istream &is){

    // Read token
    Token tok;
    tok.get(is);
    
    string idVal;
    // if ID, then ...
    if(tok.type()==ID){
        int pos = is.tellg();
        // Store value of token
        idVal = tok.value();
        
        // read new token
        tok.get(is);
        
        // if not LPAREN and ASSIGNOP, return ID value
        if (tok.type()!=LPAREN && tok.type()!=ASSIGNOP) {
            is.seekg(pos);
            return idVal; 
        }
        // if LPAREN, get exprlist
        else if (tok.type()==LPAREN) {
            string pval = exprlist(is);
            
            // read new token
            tok.get(is);

            // if not RPAREN, give error
            if (tok.type()!=RPAREN){
                cerr << "Expected ')', got: " << tok << endl;
            }
            // otherwise return id and exprlist
            return idVal + " ( " + pval + " ) "; 
        }
        // if ASSIGNOP, then return id and exprassion
        else if (tok.type()==ASSIGNOP) { 
            return "  " + idVal + " = " + expr(is);
        }
        // otherwise unget token, and return id
        else {
            is.seekg(pos);
            return idVal;
        }
    }
    
    // if IF, then ...
    if (tok.type()==IF) {  
        // store expression
        string exprVal = expr(is);

        int pos = is.tellg();

        // read new token
        tok.get(is);

        // if THEN, ...
        if (tok.type()==THEN) {
            // Store compound
            string compVal = compound(is);
            // read new token
            tok.get(is);
            // if else, return if statement
            if (tok.type()==ELSE) {
                return "if " + exprVal + " then \n  " + compVal +"\n else \n  " + compound(is); 
            }
            // otherwise unget token, give error
            else {
                is.seekg(pos);
                cerr << "Unexpected token: " << tok << endl;
                return 0;
            }
        }
        // otherwise unget token, give error
        else {
            is.seekg(pos);
            cerr << "Unexpected token: " << tok << endl;
            return "error";
        }
    }

    // if WHILE, then ...
    if (tok.type()==WHILE) {
        int pos = is.tellg();

        // read new token
        tok.get(is);

        // if not LPAREN, unget token return compound
        if (tok.type()!=LPAREN) {
            is.seekg(pos);
            return compound(is); 
        }
        // if LPAREN, then ...
        else if (tok.type()==LPAREN) {
            // store expression
            string exprVal = expr(is);
           
            // read new token
            tok.get(is);
        
            // if not RPAREN, then give error
            if (tok.type()!=RPAREN){
                cerr << "Expected ')', got: " << tok << endl;
            }
            // otherwise return the while statement and compound
            return "while ( " + exprVal + " ) " + "\n    " +compound(is);
        }
        // otherwise unget token, give error
        else {
            is.seekg(pos);
            return 0;
        }
    }
    // otherwise return compound
    else {
        return compound(is);
    }
}

// Grammar for exprlist
string exprlist(std::istream &is){
    // store expression
    string exprVal = expr(is);
    
    int pos = is.tellg();

    // Read token
    Token tok;
    tok.get(is);

    // if COMMA, return list of expression
    if (tok.type()==COMMA) {
        return exprVal + tok.value() + " " + exprlist(is); 
    }
    // otherwise unget token, return expression
    else {
        is.seekg(pos);
        return exprVal;
    }
}

// Grammar for expr
string expr(std::istream &is){
    // store simple expression
    string simpexprVal = simpexpr(is);

    int pos = is.tellg();

    // Read token
    Token tok;
    tok.get(is);
   
    // if not RELOP, unget token and return simple expression
    if (tok.type()!=RELOP) {
        is.seekg(pos);
        return simpexprVal;
    }
    // if RELOP, then return expression
    if (tok.type()==RELOP) {
        return simpexprVal + " " + tok.value() + " " + simpexpr(is);
    }
    // otherwise unget token, and return simple expression
    else {
        is.seekg(pos);
        return simpexprVal;
    }
}

// Grammar for simpexpr
string simpexpr(std::istream &is){
    // store term
    string termVal = term(is);

    int pos = is.tellg();

    // Read token
    Token tok;
    tok.get(is);

    // if ADDOP, then return term and operator with simple expression
    if (tok.type()==ADDOP) {
        return termVal +" "+ tok.value() +" "+ simpexpr(is); 
    }
    else {
        // unget the token, return term
        is.seekg(pos);
        return termVal;
    }
}

// Grammar for term
string term(std::istream &is){
    // store factor
    string result = factor(is);

    int pos = is.tellg();

    // Read token
    Token tok;
    tok.get(is);

    // if MULOP, then return factor as term
    if (tok.type()==MULOP) {
        return result +" "+ tok.value() +" "+ term(is);
    }
    // otherwise unget token, and return factor
    else {
        is.seekg(pos);
        return result;
    }
}

string factor(std::istream &is){
    // Read token
    Token tok;    
    tok.get(is);
    
    string idVal;
    // if ID, then ...
    if(tok.type()==ID){
        int pos = is.tellg();

        // store token value
        idVal = tok.value();
       
        // read new token
        tok.get(is);
        // if not LPAREN, unget token and return just id
        if (tok.type()!=LPAREN) {
            is.seekg(pos);
            return idVal; 
        }
        // if LPAREN, return expressions
        else if (tok.type()==LPAREN) {
            // store list of expressions
            string pval = exprlist(is);
           
            // read next token
            tok.get(is);
            
            // if not RPAREN, give error
            if (tok.type()!=RPAREN){
                cerr << "Expected ')', got: " << tok << endl;
            }
            // Otherwise return id and list of expressions in parantheses 
            return idVal + "( " + pval + " )"; 
        }
        // Otherwise unget token, and return id
        else {
            is.seekg(pos);
            return idVal;
        }
    }
    // if NUM_REAL, return value
    else if(tok.type()==NUM_REAL){
        return tok.value(); 
    }
    // if NUM_INT, return value
    else if(tok.type()==NUM_INT){
        return tok.value(); 
    }
    // if LPAREN, then...
    else if (tok.type()==LPAREN) {
        // store expression
        string exprVal = expr(is);
        
        // read new token
        tok.get(is);
        // if not RPAREN, give error
        if (tok.type()!=RPAREN) {
            cerr << "Expected ')' got: " << tok << endl;
        }
        // otherwise return exppression inside parantheses
        return "( "+ exprVal +" "+ tok.value();
    }
    // otherwise unget token, return error
    else {
        cerr << "Unexpected token: " << tok << endl;
        return 0;
    }
}
