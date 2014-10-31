#ifndef ANIMATION_H
#define ANIMATION_H

/******************************************************************************
*
* Title: CSCI 405 Assignment #4
*
* Author: Andrew Smythe
*
* Date: April 27th, 2014
*
* File: Animation.h
*
* Behaviour: Class definition for Animation for assignment #4. Will utilize
*            bezier curves to move the camera around.
*
******************************************************************************/

#define MAX_POINTS 50

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "Camera.h"
#include <iostream>
using namespace std;

class Animation
{

    private:
        
        class Vector3
        {
            public:
            
                int x;
                int y;
                int z;
                
                Vector3() {}
                
                Vector3(int x, int y, int z)
                {
                    this->x = x;
                    this->y = y;
                    this->z = z;
                }
        };
        
        Camera* cam;
        Vector3 ctrlPoints[MAX_POINTS];
        int numPoints;
        int currentPoint;
        float time;
        float initialTime;
        bool finished;
        bool started;
        Vector3* initialPoint;
        Vector3* initialControl;
    
    public:
        Animation(Camera* c);
        
        void drawPath();
        void addPoint(float x, float y, float z);
        void init(float x, float y, float z);
        void go();
        bool isFinished();

};

#endif
