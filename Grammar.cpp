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

string factor(std::istream &is){
    Token tok;    
    tok.get(is);

    if(tok.type()==ID){
        return tok.value();
    }

    else {
        cerr << "Unexpected token: " << tok << endl;
        return 0;
    }
}
