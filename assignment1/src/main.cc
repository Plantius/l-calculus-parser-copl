/**
* Implementation of the main function
* Niels Versteeg (s3322637)
* Lana van Sprang (s3272192)
* main.cc
* 15-09-2023
**/ 

#include "../include/standard.h"
#include "../include/parser.h"
#include "../include/token.h"
using namespace std;

enum test { lpar, rpar, lambda, var};

int main(){
    tokenList* t = new tokenList;
    t->addToken(0, '#');
    t->addToken(0, '#');
    t->addToken(0, '#');
    t->addToken(0, '#');
    t->addToken(0, '#');
    t->addToken(0, '#');
    t->addToken(0, '#');
    t->addToken(0, '#');
    delete t;

    // string input = ""; 
    // getInput(input);

    // if(validInput(input)){
    //     stringTokenizer(input);
    //     printCout(input);
    // }
    
    return 0;
}// main