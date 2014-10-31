#ifndef CAMERA_H
#define CAMERA_H

/******************************************************************************
*
* Title: CSCI 405 Assignment #4
*
* Author: Andrew Smythe
*
* Date: April 25th, 2014
*
* File: Camera.h
*
* Behaviour: Class definition for Camera object.
*
******************************************************************************/

// defines for input keys
#define MOVE_FORWARD 0
#define MOVE_LEFT 1
#define MOVE_RIGHT 2
#define MOVE_BACKWARD 3
#define YAW_LEFT 4
#define YAW_RIGHT 5
#define PITCH_UP 6
#define PITCH_DOWN 7

#define PI 3.14159

#include <cmath>
using namespace std;

class Camera
{
    private:
        float posX;
        float posY;
        float posZ;
        
        float atX;
        float atY;
        float atZ;
        
        float fovy;
        float aspect;
        float nearClip;
        float farClip;
        
        float yaw;
        float pitch;
        
        int keyState[8];
        
        int flipped;
        
    public:
        Camera(float px, float py, float pz, float f, float a, 
               float near, float far);
        
        // apply changes in input state
        void setKey(int key);
        void releaseKey(int key);
        
        // get key input state
        int getKeyState(int key);
        
        // camera movements
        void moveForward();
        void moveBackward();
        void moveLeft();
        void moveRight();
        
        void yawLeft();
        void yawRight();
        
        void pitchUp();
        void pitchDown();
        
        // getter methods
        float getPosX();
        float getPosY();
        float getPosZ();
        
        float getAtX();
        float getAtY();
        float getAtZ();
        
        float getFOV();
        float getAspect();
        float getNearClip();
        float getFarClip();  
        
        // setter methods
        void setPosX(float x);
        void setPosY(float y);
        void setPosZ(float z);
};

#endif
