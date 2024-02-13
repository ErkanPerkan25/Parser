/****************************************************
 * Author: Eric Hansson
 * File: main.cpp
 * Date: 2/13/2024
 * Prupose: To read in a file, and if there is no invalid
 * program, print out the beautfied code of it
*****************************************************/
#include <cstdio>
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

    if (ifile.is_open()) {
        cout << "Successful code ===========================================" << endl;
        cout << program(ifile) << endl;
    } 
    else {
        cout << "UNsucessful code ==========================================" << endl;
    }

  return 0;
}
