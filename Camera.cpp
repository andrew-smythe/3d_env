/******************************************************************************
*
* Title: CSCI 405 Assignment #4
*
* Author: Andrew Smythe
*
* Date: April 25th, 2014
*
* File: Camera.cpp
*
* Behaviour: Implementation of class methods for Camera object.
*
******************************************************************************/

#include "Camera.h"
#include <iostream>
using namespace std;

// Constructor method for Camera (instantiates all floating point numbers
// needed for gluPerspective and gluLookAt calls
Camera::Camera(float px, float py, float pz, float f, float a, 
                           float near, float far)
{
    this->yaw = 0.0f;
    this->pitch = 0.0f;
    
    this->posX = px;
    this->posY = py;
    this->posZ = pz;
    
    this->atX = this->posX + 500.0f * cos( this->yaw );
    this->atY = this->posY + 10.0f * sin( this->pitch );
    this->atZ = this->posZ + 500.0f * sin( this->yaw );
    
    this->fovy = f;
    this->aspect = a;
    this->nearClip = near;
    this->farClip = far;
    
    
    // set initial key states
    this->keyState[MOVE_FORWARD] = 0;
    this->keyState[MOVE_BACKWARD] = 0;
    this->keyState[MOVE_LEFT] = 0;
    this->keyState[MOVE_RIGHT] = 0;
    this->keyState[YAW_LEFT] = 0;
    this->keyState[YAW_RIGHT] = 0;
    this->keyState[PITCH_UP] = 0;
    this->keyState[PITCH_DOWN] = 0;
    
    int flipped = 0;
}

// Methods for camera movement
void Camera::moveForward()
{
    // move camera forward
    this->posX = this->posX + 4.5f * cos( this->yaw );
    this->posY = this->posY + 4.5f * sin( this->pitch );
    this->posZ = this->posZ + 4.5f * sin( this->yaw );
    
    // Recalculate at vector
    this->atX = this->posX + 500.0f * cos( this->yaw ) * cos( this->pitch );
    this->atY = this->posY + 500.0f * sin( this->pitch );
    this->atZ = this->posZ + 500.0f * sin( this->yaw ) * cos( this->pitch );
}

void Camera::moveBackward()
{
    // move camera forward
    this->posX = this->posX - 4.5f * cos( this->yaw );
    this->posZ = this->posZ - 4.5f * sin( this->yaw );
    this->posY = this->posY - 4.5f * sin( this->pitch );
    
    // Recalculate at vector
    this->atX = this->posX + 500.0f * cos( this->yaw ) * cos( this->pitch );
    this->atY = this->posY + 500.0f * sin( this->pitch );
    this->atZ = this->posZ + 500.0f * sin( this->yaw ) * cos( this->pitch );
}

void Camera::moveLeft()
{
    // move camera forward
    this->posX = this->posX + 4.5f * cos( this->yaw - PI/2.0f );
    this->posZ = this->posZ + 4.5f * sin( this->yaw - PI/2.0f );
    
    // Recalculate at vector
    this->atX = this->posX + 500.0f * cos( this->yaw ) * cos( this->pitch );
    this->atZ = this->posZ + 500.0f * sin( this->yaw ) * cos( this->pitch );
}

void Camera::moveRight()
{
    // move camera forward
    this->posX = this->posX + 4.5f * cos( this->yaw + PI/2.0f );
    this->posZ = this->posZ + 4.5f * sin( this->yaw + PI/2.0f );
    
    // Recalculate at vector
    this->atX = this->posX + 500.0f * cos( this->yaw ) * cos( this->pitch );
    this->atZ = this->posZ + 500.0f * sin( this->yaw ) * cos( this->pitch );
}

void Camera::yawLeft()
{
    // rotate left
    this->yaw -= 0.04f;

    // Recalculate at vector
    this->atX = this->posX + 500.0f * cos( this->yaw ) * cos( this->pitch );
    this->atZ = this->posZ + 500.0f * sin( this->yaw ) * cos( this->pitch );
}

void Camera::yawRight()
{
    // rotate right
    this->yaw += 0.04f;

    // Recalculate at vector
    this->atX = this->posX + 500.0f * cos( this->yaw ) * cos( this->pitch );
    this->atZ = this->posZ + 500.0f * sin( this->yaw ) * cos( this->pitch );
}

void Camera::pitchUp()
{
    // rotate upwards
    this->pitch += 0.04f;

    // Recalculate at vector
    this->atX = this->posX + 500.0f * cos( this->yaw ) * cos( this->pitch );
                
    this->atY = this->posY + 500.0f * sin( this->pitch );
    if ( this->atY >= this->posY + 480.0f )
    {
        this->atY = this->posY + 480.0f;
        this->pitch = 1.29f;
    }
                
    this->atZ = this->posZ + 500.0f * sin( this->yaw ) * cos( this->pitch );
}

void Camera::pitchDown()
{
    // rotate downwards
    this->pitch -= 0.04f;

    // Recalculate at vector
    this->atX = this->posX + 500.0f * cos( this->yaw ) * cos( this->pitch );
                
    this->atY = this->posY + 500.0f * sin( this->pitch );
    if ( this->atY <= this->posY - 480.0f )
    {
        this->atY = this->posY - 480.0f;
        this->pitch = -1.29f;
    }
    
    this->atZ = this->posZ + 500.0f * sin( this->yaw ) * cos( this->pitch );
}


// Getter methods

float Camera::getPosX()
{
    return (this->posX);
}

float Camera::getPosY()
{
    return (this->posY);
}

float Camera::getPosZ()
{
    return (this->posZ);
}

float Camera::getAtX()
{
    return (this->atX);
}

float Camera::getAtY()
{
    return (this->atY);
}

float Camera::getAtZ()
{
    return (this->atZ);
}

float Camera::getFOV()
{
    return (this->fovy);
}

float Camera::getAspect()
{
    return (this->aspect);
}

float Camera::getNearClip()
{
    return (this->nearClip);
}

float Camera::getFarClip()
{
    return (this->farClip);
}

// Keyboard input functions
void Camera::setKey(int key)
{
    this->keyState[key] = 1;
}

void Camera::releaseKey(int key)
{
    this->keyState[key] = 0;
}

int Camera::getKeyState(int key)
{
    return ( this->keyState[key] );
}

void Camera::setPosX(float x)
{
    this->posX = x;
    
    // Recalculate at vector
    this->atX = this->posX + 500.0f * cos( this->yaw ) * cos( this->pitch );
}

void Camera::setPosY(float y)
{
    this->posY = y;
    
    // Recalculate at vector
    this->atY = this->posY + 500.0f * sin( this->pitch );
}

void Camera::setPosZ(float z)
{
    this->posZ = z;
    
    // Recalculate at vector
    this->atZ = this->posZ + 500.0f * sin( this->yaw ) * cos( this->pitch );
}
