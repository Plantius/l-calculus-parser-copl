/**
* Implementation of the standard functions
* Niels Versteeg (s3322637)
* Lana van Sprang (s3272192)
* standard.cc
* 05-10-2023
**/

#include "../include/standard.h"
#include "../include/error.h"
#include <fstream>
#include <sstream>
using namespace std;


// Checks if the given string contains only ASCII-characters
void validInput(const string input){
    for (auto c : input) {
        if (!isascii(c)){
            throw inputError("Contains non-standard ASCII characters");
        }
    }
}// valid_input

