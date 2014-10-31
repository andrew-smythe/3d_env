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
* Behaviour: Implementation of Tree class methods.
*
******************************************************************************/

#include "Tree.h"

// Public constructor -- takes in vertex for base of tree
Tree::Tree(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->numRotations = NUM_ROTATIONS;
    this->scale = (float) TREE_SCALE;
    this->angle = (float) TREE_ANGLE;
}

// Draw method -- draws the tree to the screen
void Tree::draw()
{
    // Place at the correct vertex
    glPushMatrix();
    glTranslatef( this->x, this->y, this->z );
    
    // Draw the correct number of rotations
    for (int i = 0; i < this->numRotations; i++)
    {
        // Rotate the tree
        glPushMatrix();
        glRotatef(i*(180/this->numRotations), 0.0f, 1.0f, 0.0f);
        
        glBegin(GL_LINES);
        glLineWidth(15.0f);
            
        // start the recursive call
        renderCall(0, -10, 0, 50, 1.5, 8);
            
        glEnd();
        glPopMatrix();
    }
    
    glPopMatrix();
}

// callRender method -- recursive method to draw the tree
void Tree::renderCall(float x, float y, float z, float length, float angle, 
                      int count)
{
   if(count > 0)
   {
      
      // draw next tree vertex
      glVertex3f( x, y, z );
      
      float newX = x + length*cos(angle);
      float newY = y + length*sin(angle);
      float newZ = z;
      
      // draw next tree vertex
      glVertex3f( newX, newY, newZ);

      float newLength = length * this->scale;
      float newAngle = angle + this->angle;
   
      this->renderCall(newX, newY, newZ, newLength, newAngle, count-1);
      newAngle = angle - this->angle;
      this->renderCall(newX, newY, newZ, newLength, newAngle, count-1);
   }
}
