#ifndef TERRAIN_H
#define TERRAIN_H

/******************************************************************************
*
* Title: CSCI 405 Assignment #4
*
* Author: Andrew Smythe
*
* Date: April 27th, 2014
*
* File: Terrain.h
*
* Behaviour: Class definition for Terrain object -- generates random fractal
*            terrain, stored in a 2D array of Y-axis "height" values.
*
******************************************************************************/

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

class Terrain
{

    private:
        
        class Pair 
        {
            public:
                
                int x;
                int y;
                
                Pair(int x, int y)
                {   
                    this->x = x;
                    this->y = y;
                }
        };

    public:
    
        int sizeX;
        int sizeY;
        
        float** nodes;
        
        Terrain(int x, int y);
        ~Terrain();
        
        void generate();
        
        int getSizeX();
        int getSizeY();
        
        void draw(float factor);

};



#endif
