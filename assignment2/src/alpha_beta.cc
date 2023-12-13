/**
* Implementation of the alpha conversion 
  and beta reduction.
* Niels Versteeg (s3322637)
* Lana van Sprang (s3272192)
* alpha_beta.cc
* 15-11-2023
**/ 

#include "../include/standard.h"
#include "../include/error.h"
#include "../include/alpha_beta.h"
#include <fstream>
using std::cout, std::endl;

void alpha_beta::makeAbstract(tokenList &L, tree &T){
    node* start = T.getBegin();
    bool done = true;
    int times = 0;
    needsAlpha(start);

    // while(done){
    //     done = false;
    //     // if(needsBeta(L)){
    //         // done = performReduction(L);
    //         // M.clear();
    //         // N.clear();
    //         times ++;
    //     // }
    //     if (times >= MAX_IT){
    //         done = false;
    //     }
    // }

} // makeAbstract

bool alpha_beta::needsBeta(tokenList &L, tree &T){
    x = "$";
    L.setIndex(0);
    M.setIndex(0);
    N.setIndex(0);
    int i = 0;

    if(T.isEmpty(T.getBegin())){
        return false;
    }

    while(i < L.getLength()){
        if (L.getToken(i)->id == LAMBDA){
            x = L.peekToken();
            i++;
        }
        else if (x != "$" ){
            int j=0;
            while ((L.getToken(i)->id != RPAR) && (i < L.getLength())){
                M.insertToken(L.getToken(i)->id, L.getToken(i)->tokenChar, j);
                i++;
                j++;
            } // while M'

            j = 0;

            if (i < L.getLength()){
                while (i < L.getLength()){
                    N.insertToken(L.getToken(i)->id, L.getToken(i)->tokenChar, j);
                    i++;
                    j++;
                } // while N
                return true;
            }
        }else {
            i++;
        }
    } // while L
    return false;
} // needsBeta

// NOG NIET GOED    
void alpha_beta::needsAlpha(node* &start){
    if (start == nullptr){
        return;
    }
    std::set<std::string> varList, allVar;
    node* temp = start;

    if (temp->tokenChar == "@"){
        if(temp->left->id == LAMBDA){
            temp = temp->left;

            // situation 1:\y (\x y) x
            if(temp->right->id == LAMBDA){
                temp = temp->right;
                findVar(start->right, varList);
                findVar(temp->left, varList);
                if (varList.find(temp->left->tokenChar) != varList.end()){
                    temp->left->tokenChar = chooseVar(allVar);
                    return;
                }
            }
            
            // situation 2: \x (\w w z (\z y))
            // if(start->right->id == LAMBDA && temp->right->tokenChar == "@"){
            //     temp = temp->right;
            //     std::set<std::string> varList;
            //     findVar(temp, varList);
            //     for (auto i : varList){
            //         if(start->right->right->tokenChar == i){
            //             std::set<std::string> allVar;
            //             std::string replace = chooseVar(allVar);
            //             start->right->right->tokenChar = replace;
            //             return;
            //         }
            //     } 
            // }
        }
     }
} // needsAlpha


void alpha_beta::findVar(node* &start, std::set<std::string> &varList) const{
    if (start  == nullptr){
        return;
    }

    if (start->id == VAR){
        varList.insert(start->tokenChar);
    }
    findVar(start->left, varList);
    findVar(start->right, varList);
}// findVar


bool alpha_beta::performReduction(tokenList & L){

    for (int i = 0; i < M.getLength(); i++){
        if (M.getToken(i)->tokenChar == x){
            for (int j = 0; j < N.getLength(); j++){
                M.insertToken(N.getToken(i)->id, N.getToken(i)->tokenChar, i);
            }
            M.deleteToken(i);
        }
    }

    L.clear();
    for (int k = 0; k < M.getLength(); k++){
        L.addToken(M.getToken(k)->id, M.getToken(k)->tokenChar);
    }

    return true;
} // performReduction
