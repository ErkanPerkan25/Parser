/****************************************************
 * Author: Eric Hansson
 * File: main.cpp
 * Date:
 * Prupose:
*****************************************************/
#include <iostream>
#include <fstream>

#include "Token.hpp"
#include "Grammar.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    // check to make sure an input file was specified. 
    if (argc!=2)
    {
      cerr << "USAGE: " << argv[0] << " <file>" << endl;
      return -1;
    }

    // open input file
    ifstream ifile(argv[1]);

    // if open was not successful, let user know. 
    if (!ifile)
    {
      cerr << "ERROR: Could not open file:\"" << argv[1] << "\"" <<endl;
      return -1;
    }

    //if(program(ifile)){
    //  cout << "# successful code ======================================" << endl;
    //}
    //else{
    //  cout << "# UNsuccessful code ====================================" << endl;
    //}
    
    //cout << idlist(ifile) << endl;
    cout << expr(ifile) << endl;

  return 0;
}
