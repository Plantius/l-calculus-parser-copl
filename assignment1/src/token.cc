/**
* Implementation of the token functions
* Niels Versteeg (s3322637)
* Lana van Sprang (s3272192)
* token.cc
* 04-10-2023
**/ 

#include "../include/standard.h"
#include "../include/token.h"
#include "../include/tokenId.h"
using namespace std;

// Default constructor
token::token(){
    next = nullptr;
    prev = nullptr;
    id = INVALID;
    tokenChar = "$";
}// default constructor


// Default constructor
token::token(const tokenId idToken, token* nextToken, token* prevToken, const std::string c){
    next = nextToken;
    prev = prevToken;
    id = idToken;
    tokenChar = c;
}// default constructor


// Default constructor
tokenList::tokenList(){
    begin = nullptr;
    end = nullptr;
    length = 0;
    index = 0;
}// default constructor


// Deletes the list of tokens
tokenList::~tokenList(){
    clear();
}// destructor

void tokenList::clear(){
    token* temp = begin;

    while (temp != nullptr){
        temp = temp->next;
        delete begin;
        begin = temp;
        length--;
    }
    begin = nullptr;
    end = nullptr;
    index = 0;
}


// Checks if the tokenList is empty
bool tokenList::isEmpty(){
    if (begin != nullptr){
        return false;
    }
    return true;
}// isEmpty


// Returns the length of the list
int tokenList::getLength(){
    return length;
}// getLength


// Returns the current index
int tokenList::getIndex(){
    return index;
}// getIndex


// Returns the token type of the token at the given index
int tokenList::peekToken(){
    token* nextToken = getToken(index);
    if (nextToken != nullptr){
        while(nextToken->next != nullptr && (nextToken->id == SPACE || nextToken->id == RPAR)){
            nextToken = nextToken->next;
            index++;
        }
        
        if(nextToken != nullptr){
            if (nextToken->id == INVALID){
                throw string("Invalid token: token id is invalid");
            }
            return nextToken->id;
        }
    }
    return INVALID;
}// peekToken


// Consumes the current token
void tokenList::consumeToken(){
    if (index < length-1){
        index++;
    }
}// consumeToken


// Returns the token-object at the given list index
// If the index is greater then half of the list length, the
// walk is started from the end of the list, instead of the beginning
token* tokenList::getToken(const int index){
    token* temp = nullptr;

    if (index < 0 || index >= length){
        printError("Invalid token: index out of bounds");
        return temp;
    }

    if (index < int(length/2)){
        temp = begin;
        for(int i = 0; i < index; i++){
            if (temp != nullptr){
                temp = temp->next;
            }else {
                printError("Invalid token: index out of bounds");
                return temp;
            }   
        }
    }else {
        temp = end;
        for(int i = getLength()-1; i > index; i--){
            if (temp != nullptr){
                temp = temp->prev;
            }else {
                printError("Invalid token: index out of bounds");
                return temp;
            }
        }
    }
    return temp;
}// getToken


// Adds a token-object at the back of the tokenList
bool tokenList::addToken(const tokenId id, const string tokenChar){
    if(isEmpty()){
        token* newToken = new token(id, nullptr, nullptr, tokenChar);
        if (newToken == nullptr){
            printError("Memory allocation failed");
            return false;
        }
        begin = newToken;
        end = newToken;
        length++;

        return true;
    }else {
        token* temp = end;
        token* newToken = new token(id, nullptr, end, tokenChar);
        if (newToken == nullptr){
            printError("Memory allocation failed");
            return false;
        }
        temp->next = newToken;
        end = newToken;
        length++;

        return true;
    }

    return false;
}// addToken


// Prints the contents of tokenList to stdout
void tokenList::printList(){
    token* temp = begin;

    while(temp != nullptr){
        cout << temp->id << ":" << temp->tokenChar << " ";
        temp = temp->next;
    }cout << endl;
}// printList
