/**
* Implementation of the parser functions
* Niels Versteeg (s3322637)
* Lana van Sprang (s3272192)
* parser.cc
* 04-10-2023
**/ 

#include "../include/standard.h"
#include "../include/parser.h"
#include "../include/token.h"
#include "../include/tokenId.h"
#include "../include/error.h"
using namespace std;

int parser::getRow(){
    return row;
}// getRow

int parser::getCol(){
    return col;
}// getCol

// Checks what id the given inputChar has in tokenId
void parser::tokenSwitch(const char inputChar, tokenId & id){
    // for all the special characters
    switch(inputChar){
        case '(':
            id = LPAR; 
            break;
        case ')':
            id = RPAR;
            break;
        case '\\':
            id = LAMBDA;
            break;
        case '.': 
            id = DOT;
            break;
        case ' ': 
            id = SPACE;
            break;
        default: 
            id = INVALID;
            break;
    }
    if ((int(inputChar) >= 65 && int(inputChar) <= 90) || 
            (int(inputChar) >=97 && int(inputChar) <= 122) || 
                (int(inputChar) >=48 && int(inputChar) <= 57)){
        id = VAR;
    }
}// tokenSwitch

void parser::expr(tokenList & list){
    lambdaExpr(list);
    expr1(list);
}// expr


void parser::expr1(tokenList & list){
    if (list.peekToken() == EOL){
        return;
    }
    lambdaExpr(list);
    expr1(list);
}// expr1


// Checks if the token at the given index is a parexpr or a lambda expression
void parser::lambdaExpr(tokenList & list){
    if (list.peekToken() == LAMBDA){
        list.consumeToken();
        if (list.peekToken() == VAR){
            list.consumeToken();
            if(list.peekToken() == EOL){
                throw syntaxError("No expression after lambda.");
            }
            lambdaExpr(list);
        }else{
            throw syntaxError("No variable after lambda.");
        }
    }else{
        varExpr(list);
    }
}// fexpr


// Checks if the token at the given index is a paranthesis or a variable
void parser::varExpr(tokenList & list){
    if (list.peekToken() == VAR){
        list.consumeToken();
    }else if ((list.peekToken() == LPAR)){
        list.consumeToken();  
        expr(list);
    }else {
        throw syntaxError("No variable or opening paranthesis.");
    }
}// parexpr


// Tokenizes the given string, and adds them to the given token list
void parser::stringTokenizer(const string input, tokenList & list){
    int lparCounter = 0, rparCounter = 0;
    int size = input.length();
    int i = 0;
    tokenId id = INVALID;
    string tempVar = emptyStr;


    while(input[i] != '\0'){
        if (input[i] == '\n'){
            if (list.isEmpty()){
                break;
            }
            if(!(list.addToken(EOL, "#"))){
                throw tokenError("Failed to add token to the list.");
            }
            list.printList();
            
            if (lparCounter != rparCounter){
                throw tokenError("Not enough beginning/closing parantheses.");
            }
            expr(list);
      
            list.clear();
            lparCounter = 0;
            rparCounter = 0;
            row++;
            col = 0;
        }else {
            tokenSwitch(input[i], id);
            // Checks if the input is a var, which can be of indefinite size
            if (id == VAR){ 
                if (tempVar.empty() && (int(input[i]) >= 48 && int(input[i]) <= 57)){
                    throw tokenError("Variable name starts with a number.");

                }if (i < size){
                    tokenId tempId = INVALID;
                    tokenSwitch(input[i+1], tempId);
                    if (tempId == VAR){
                        tempVar += input[i];
                    }else {
                        tempVar += input[i];
                        if(!list.addToken(id, tempVar)){
                            throw tokenError("Failed to add token to the list.");
                        }
                        tempVar.clear();
                    }
                }
            }else {
                if (id == LPAR){
                    lparCounter++;
                }if (id == RPAR){
                    rparCounter++;
                }
                if(!(list.addToken(id, string(1, input[i])))){
                    throw tokenError("Failed to add token to the list.");
                }
            }
        }
        i++;
        col++;
    }
    if(!(list.addToken(EOL, "#"))){
        throw tokenError("Failed to add token to the list.");
    }
    list.printList();
            
    if (lparCounter != rparCounter){
        throw tokenError("Number of beginning and closing parantheses do not match.");
    }
    expr(list);

}// stringTokenizer

void parser::printExpression(const string input, tokenList & list){
    int length = list.getLength();
    if (!(list.isEmpty())){
        for (int i = 0; i < length; i++){
            cout << input[i] << endl; //?? not done
        }
    }
    else{
        cout << " " << endl;
    }
    
}
