/******************************************************************************
*
* Title: CSCI 405 Assignment #4
*
* Author: Andrew Smythe
*
* Date: April 27th, 2014
*
* File: Animation.cpp
*
* Behaviour: Implementation of Animation class.
*
******************************************************************************/

#include "Animation.h"

// Public constructor method
Animation::Animation(Camera* c)
{
    this->cam = c;
    this->numPoints = 0;
    this->started = false;
    this->initialPoint = NULL;
    this->initialControl = NULL;
}

// Draws the path the camera will follow: implmented as quadratic bezier curves
void Animation::drawPath()
{

            glBegin(GL_LINE_STRIP);
        
            // iterate through ctrl points -- there must be at least 3
            if (this->numPoints > 2) 
            {
                // start a curve at each even numbered point (odd points
                // are control points)
                for (int i = 0; i < this->numPoints; i += 2) 
                {
                
                    if ( (i+2) < this->numPoints ) 
                    {
                        // iterate through parametric bezier function
                        for (float t = 0.0; t < 1.0; t += 0.02) 
                        {
                        
                            // Create points for the bezier curve
                            float x = this->ctrlPoints[i].x*pow((1-t), 2) + 
                                      2*this->ctrlPoints[i+1].x*(1-t)*t + 
                                      this->ctrlPoints[i+2].x*pow(t, 2);
                                      
                            float y = this->ctrlPoints[i].y*pow((1-t), 2) + 
                                      2*this->ctrlPoints[i+1].y*(1-t)*t + 
                                      this->ctrlPoints[i+2].y*pow(t, 2);
                                      
                            float z = this->ctrlPoints[i].z*pow((1-t), 2) + 
                                      2*this->ctrlPoints[i+1].z*(1-t)*t + 
                                      this->ctrlPoints[i+2].z*pow(t, 2);
                            
	                        glVertex3f( x, y, z );
                        
                        }       
                    } 
                    
                }
            }
            glEnd();

}

// Add a control point to the list
void Animation::addPoint(float x, float y, float z)
{
    if (this->numPoints < MAX_POINTS)
    {
        this->ctrlPoints[this->numPoints] = Vector3(x,y,z);
        this->numPoints++;
    }
}

// Initialize animation
void Animation::init(float x, float y, float z)
{
    if (!this->started)
    {
        if (this->numPoints > 0)
        {
            this->cam->setPosX(this->ctrlPoints[0].x);
            this->cam->setPosY(this->ctrlPoints[0].y);
            this->cam->setPosZ(this->ctrlPoints[0].z);
        }
        this->currentPoint = 0;
        this->started = true;
        this->finished = false;
    }
    
    this->initialPoint = new Vector3(x,y,z);
    this->initialControl = new Vector3( (x + this->ctrlPoints[this->currentPoint].x) / 2, 
                                    (y + this->ctrlPoints[this->currentPoint].y) / 2, 
                                    (z + this->ctrlPoints[this->currentPoint].z) / 2 );
    this->time = 0.0f;
    this->initialTime = 0.0f;
}

// Execute animation
void Animation::go()
{
    if (this->initialPoint != NULL && this->initialControl != NULL)
    {
        // get from the user's position to the first bezier node
        float x = this->initialPoint->x*pow((1-this->initialTime), 2) + 
                  2*this->initialControl->x*(1-this->initialTime)*this->initialTime + 
                  this->ctrlPoints[this->currentPoint].x*pow(this->initialTime, 2);
                                      
        float y = this->initialPoint->y*pow((1-this->initialTime), 2) + 
                  2*this->initialControl->y*(1-this->initialTime)*this->initialTime + 
                  this->ctrlPoints[this->currentPoint].y*pow(this->initialTime, 2);
                                     
        float z = this->initialPoint->z*pow((1-this->initialTime), 2) + 
                  2*this->initialControl->y*(1-this->initialTime)*this->initialTime + 
                  this->ctrlPoints[this->currentPoint].z*pow(this->initialTime, 2);
                      
        // set camera position
        this->cam->setPosX(x);
        this->cam->setPosY(y);
        this->cam->setPosZ(z);
                     
        // iterate t
        this->initialTime += 0.015;
        if (this->initialTime > 1.0f)
        {
            this->time = 0.0f;
            delete this->initialPoint;
            delete this->initialControl;
            this->initialPoint = NULL;
            this->initialControl = NULL;
        }
    }
    else
    {
        if (this->currentPoint < this->numPoints-2)
        {
            // calculate next bezier position
            float x = this->ctrlPoints[this->currentPoint].x*pow((1-this->time), 2) + 
                      2*this->ctrlPoints[this->currentPoint+1].x*(1-this->time)*this->time + 
                      this->ctrlPoints[this->currentPoint+2].x*pow(this->time, 2);
                                          
            float y = this->ctrlPoints[this->currentPoint].y*pow((1-this->time), 2) + 
                      2*this->ctrlPoints[this->currentPoint+1].y*(1-this->time)*this->time + 
                      this->ctrlPoints[this->currentPoint+2].y*pow(this->time, 2);
                                         
            float z = this->ctrlPoints[this->currentPoint].z*pow((1-this->time), 2) + 
                      2*this->ctrlPoints[this->currentPoint+1].z*(1-this->time)*this->time + 
                      this->ctrlPoints[this->currentPoint+2].z*pow(this->time, 2);
                      
            // set camera position
            this->cam->setPosX(x);
            this->cam->setPosY(y);
            this->cam->setPosZ(z);
                      
            // iterate t
            this->time += 0.015;
            if (this->time > 1.0f)
            {
                this->time = 0.0f;
                // iterate the current point
                this->currentPoint += 2;
            }
        }
        else
        {
            this->currentPoint = 0;
            this->started = false;
        }
    }
}

// Returns if animation is finished or not
bool Animation::isFinished()
{
    return (this->finished);
}
