//
// code.cpp
// Revl
//
// Created by Oliver Dain on 02/15/2018
// Copyright © 2018 Revl. All rights reserved.
//

#include <ctime>
#include "code.h"
#include <iostream>
#include <algorithm>

using std::vector;

using momentVec = std::vector<Moment>;

VectorOfPermutation GetVectors(const Moment& startingMoment, const momentVec& myCamera, const momentVec& otherCamera, int k, int c){
    //Create Temp and Return Val Holders
    VectorOfPermutation temp;
    VectorOfPermutation returnVec;
    //Base Case - Return A singular vector with a singular object
    if (c == k-1){
        momentVec tempVec;
        tempVec.push_back(startingMoment);
        returnVec.push_back(tempVec);
    }
    else{
        for (int i = 0; i < otherCamera.size(); ++i){
            //For Each Moment in the Other Camera, Get Possible Permutations
            temp = GetVectors(otherCamera[i], otherCamera, myCamera, k, c+1);
            
            for (auto it = temp.begin(); it != temp.end(); ++it){
                //If There Is Already An Instance of This Moment In This Vector
                if (std::find((*it).begin(), (*it).end(), startingMoment) != (*it).end()) {
                    //Remove the Vector - It is Invalid
                    it = temp.erase(it);
                    --it;
                }
                else {
                    //Insert the current Moment at the beginning of the vector
                    (*it).insert((*it).begin(), startingMoment);
                }
            }
            //Move temp vectors into finalReturn
            returnVec.insert(returnVec.end(), std::make_move_iterator(temp.begin()), std::make_move_iterator(temp.end()));
        }
    }
    return returnVec;
}

// Implement your solution here. Feel free to add helper methods, classes, etc.
PtrToVectorOfPermutation AllPossibleEdits(
    const vector<Moment>& camera_one_moments,
    const vector<Moment>& camera_two_moments,
    int k) {
    clock_t begin = clock();
    std::cout << begin << std::endl;
    PtrToVectorOfPermutation finalAnswer = std::make_unique<VectorOfPermutation>();
    int size1 = camera_one_moments.size();
    int size2 = camera_two_moments.size();
    //Base Case
    if (size1 + size2 < k){
        //No Valid permutations, leave the vector empty
    }
    //The Vectors' lengths must be valid
    else {
        //If There are More Empty Spaces after filling with camera 2 than
        //  there are moments in camera 1, then there's no point in continuing
        if (k - size2 <= size1){
            //For Each Moment
            for (auto& s: camera_two_moments){
                //Get the vectors that start with s
                VectorOfPermutation temp = GetVectors(s, camera_two_moments, camera_one_moments, k, 0);
                //Move those vectors into Final Answer
                finalAnswer->insert(finalAnswer->end(), std::make_move_iterator(temp.begin()), std::make_move_iterator(temp.end()));
            }
            
        }
        //Same Deal, see above comment
        if (k - size1 <= size2){
            //Camera One Can Go First
            for (auto& s: camera_one_moments){
                //Get every vector that starts with S
                VectorOfPermutation temp = GetVectors(s, camera_one_moments, camera_two_moments, k, 0);
                //Move Those Vectors into Final Answer
                finalAnswer->insert(finalAnswer->end(), std::make_move_iterator(temp.begin()), std::make_move_iterator(temp.end()));
            }
            
        }
        else {
            //No Valid Permutations, leave the vector empty
        }
    }
    return finalAnswer;
}
