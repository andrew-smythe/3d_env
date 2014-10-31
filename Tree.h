#ifndef TREE_H
#define TREE_H

/******************************************************************************
*
* Title: CSCI 405 Assignment #4
*
* Author: Andrew Smythe
*
* Date: April 29th, 2014
*
* File: Animation.h
*
* Behaviour: Class definition for Tree objects for assignment #4.
*
******************************************************************************/

#define NUM_ROTATIONS 8
#define TREE_SCALE 0.9
#define TREE_ANGLE 25.0

#include "Animation.h"

class Tree
{
    private:
    
        float x;
        float y;
        float z;
        
        int numRotations;
        float scale;
        float angle;
        
        void renderCall(float x, float y, float z, float length, float angle, 
                   int count);
        
    public:
    
        Tree(float x, float y, float z);
        
        void draw();    
    
};

#endif
