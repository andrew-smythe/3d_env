/******************************************************************************
*
* Title: CSCI 405 Assignment #4
*
* Author: Andrew Smythe
*
* Date: April 25th, 2014
*
* File: asn04.cpp
*
* Behaviour: Runs the main OpenGL loop for CSCI 405 assignment #4.
*
******************************************************************************/

// GLOBAL CONSTANTS

#define NUM_TREES 10

#include <math.h>
#include <string>
#include <cstdlib>
#include <iostream>
#include <vector>

#include "Camera.h"
#include "Terrain.h"
#include "Animation.h"
#include "Tree.h"
using namespace std;

// Camera object
Camera* cam;

// Terrain object
Terrain* terrain;

// Animation object
Animation* animation;

// Tree array
Tree* trees[NUM_TREES];

bool playing = false;
bool showPath = false;

// Create the scene world
void initWorld()
{
    // initialize the game
    cam = new Camera( 200.0f, 400.0f, 200.0f, 60.0f, 1.0f, 0.1f, 1500.0f );
    
    // Initialize the terrain
    terrain = new Terrain( 129, 129);
    terrain->generate();
    
    // Initialize animation
    animation = new Animation(cam);
    
    animation->addPoint( 103.6f, 124.4f, 114.1f );
    animation->addPoint( 296.5f, 211.5f, 283.3f );
    animation->addPoint( 652.3f, 150.1f, 636.6f );
    animation->addPoint( 709.3f, 382.7f, 711.7f );
    animation->addPoint( 1120.2f, 193.6f, 1102.4f );
    animation->addPoint( 1346.7f, 321.2f, 1116.5f );
    animation->addPoint( 1554.6f, 196.2f, 951.4f );
    animation->addPoint( 1899.5f, 236.6f, 617.6f );
    animation->addPoint( 2123.1f, 229.4f, 284.3f );
    animation->addPoint( 2285.3f, 279.9f, 320.7f );
    animation->addPoint( 2376.6f, 269.6f, 747.61f );
    animation->addPoint( 2127.8f, 297.2f, 1045.8f );
    animation->addPoint( 1922.1f, 235.5f, 1277.8f );
    animation->addPoint( 1608.7f, 263.9f, 1573.4f );
    animation->addPoint( 1721.6f, 203.6f, 2025.5f );
    animation->addPoint( 1886.7f, 260.2f, 2170.3f );
    animation->addPoint( 1650.4f, 185.6f, 2519.4f );
    animation->addPoint( 1256.5f, 243.9f, 2304.2f );
    animation->addPoint( 845.2f, 191.8f, 2283.1f );
    animation->addPoint( 634.6f, 261.9f, 2043.4f ); 
    animation->addPoint( 200.0f, 200.0f, 200.0f );
    animation->addPoint( 103.6f, 124.4f, 114.1f );
    
    // Create trees
    trees[0] = new Tree( 462.2f, 125.0f, 663.0f );
    trees[1] = new Tree( 1094.2f, 161.9f, 935.2f );
    trees[2] = new Tree( 1069.5f, 170.8f, 1241.3f );
    trees[3] = new Tree( 1718.8f, 182.3f, 919.4f );
    trees[4] = new Tree( 1992.6f, 180.7f, 388.6f );
    trees[5] = new Tree( 2170.7f, 223.7f, 452.0f );
    trees[6] = new Tree( 1646.1f, 161.3f, 1494.5f );
    trees[7] = new Tree( 1705.8f, 164.4f, 2235.4f );
    trees[8] = new Tree( 860.3f, 133.0f, 2132.5f );
    trees[9] = new Tree( 548.4f, 133.9f, 1832.7f );
}

// Call for game state iteration, and reset timer
void timerCall(int t)
{
    if (playing)
    {
        animation->go();
        glutTimerFunc( 33, timerCall, 0 );
	    if (animation->isFinished())
	    {
	        playing = false;
	    }
    }
}

// Handle special key presses (glutKeyboardFunc)
void keyboardPress ( unsigned char key, int x, int y )
{
    if ( key == 'w' || key == 'W' )
        cam->setKey(MOVE_FORWARD);
    
    if ( key == 's' || key == 'S' )
        cam->setKey(MOVE_BACKWARD);
        
    if ( key == 'a' || key == 'A' )
        cam->setKey(MOVE_LEFT);
        
    if ( key == 'd' || key == 'D' )
        cam->setKey(MOVE_RIGHT);
        
    if ( key == 'j' || key == 'J' )
        cam->setKey(YAW_LEFT);
        
    if ( key == 'l' || key == 'L' )
        cam->setKey(YAW_RIGHT);
        
    if ( key == 'i' || key == 'I' )
        cam->setKey(PITCH_DOWN);
        
    if ( key == 'k' || key == 'K' )
        cam->setKey(PITCH_UP);
}

// Handle release of special keys (glutKeyboardUpFunc)
void keyboardUp ( unsigned char key, int x, int y )
{
    if ( key == 'w' || key == 'W' )
        cam->releaseKey(MOVE_FORWARD);
    
    if ( key == 's' || key == 'S' )
        cam->releaseKey(MOVE_BACKWARD);
        
    if ( key == 'a' || key == 'A' )
        cam->releaseKey(MOVE_LEFT);
        
    if ( key == 'd' || key == 'D' )
        cam->releaseKey(MOVE_RIGHT);
        
    if ( key == 'j' || key == 'J' )
        cam->releaseKey(YAW_LEFT);
        
    if ( key == 'l' || key == 'L' )
        cam->releaseKey(YAW_RIGHT);
        
    if ( key == 'i' || key == 'I' )
        cam->releaseKey(PITCH_DOWN);
        
    if ( key == 'k' || key == 'K' )
        cam->releaseKey(PITCH_UP);
        
    if ( key == 'p' || key == 'P' )
    {
        if (!playing)
        {
            animation->init(cam->getPosX(), cam->getPosY(), cam->getPosZ());
            playing = true;
	        // Start animation loop
	        glutTimerFunc( 33, timerCall, 0 );
	    }
	    else
	    {
	        playing = false;
	    }
    }
    if ( key == 'f' || key == 'F' )
    {
        playing = false;
    }
    if ( key == 'z' || key == 'Z' )
    {
        if (showPath)
            showPath = false;
        else
            showPath = true;
    }
}

void renderScene(void) 
{
    glEnable (GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    // Setup player perspective based on current player position
    gluPerspective(cam->getFOV(), cam->getAspect(), cam->getNearClip(),
                   cam->getFarClip() );
 
    glMatrixMode(GL_MODELVIEW);
    
    // Check for camera movement
    if ( cam->getKeyState( MOVE_FORWARD ) && !playing )
    {
        cam->moveForward();
    }
    if ( cam->getKeyState( MOVE_BACKWARD ) && !playing )
    {
        cam->moveBackward();
    }
    if ( cam->getKeyState( MOVE_LEFT ) && !playing )
    {
        cam->moveLeft();
    }
    if ( cam->getKeyState( MOVE_RIGHT ) && !playing )
    {
        cam->moveRight();
    }
    if ( cam->getKeyState( YAW_LEFT ) )
    {
        cam->yawLeft();
    }
    if ( cam->getKeyState( YAW_RIGHT ) )
    {
        cam->yawRight();
    }
    if ( cam->getKeyState( PITCH_UP ) )
    {
        cam->pitchUp();
    }
    if ( cam->getKeyState( PITCH_DOWN ) )
    {
        cam->pitchDown();
    }
    
    // Make a sky box -- an arbitrarily large coloured sphere... maybe
    // one day I'll know exactly where this sphere is and make it a proper size
    // ...for now it's just huge and taking up the whole world
    glPushMatrix();
    glTranslatef( 64.0f, 200.0f, 64.0f );
    glColor3f( 0.6f, 0.6f, 1.0f );
    glutSolidSphere(1500, 40, 40);
    glPopMatrix();
    
    // Aim camera based on current player position
    glPushMatrix();
    gluLookAt( cam->getPosX(), cam->getPosY(), cam->getPosZ(),
               cam->getAtX(), cam->getAtY(), cam->getAtZ(),
               0.0f, 1.0f, 0.0f );
               
    
    // Draw the terrain
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    glColor3f( 0.4f, 0.2f, 0.0f );
    terrain->draw(20.0f);
    
    glFlush();
    
    // Draw some points
    glPointSize(10.0f);
    glColor3f( 1.0f, 0.0f, 0.0f );
    
    if (showPath)
        animation->drawPath();
    glColor3f(0.0,0.6f,0.0);
    glLineWidth(2.0);
    
    for (int i = 0; i < NUM_TREES; i++)
    {
        // DRAW TREES
        trees[i]->draw();
    }
    
	glPopMatrix();
	
    
	glutSwapBuffers(); 

}

int main(int argc, char **argv) 
{
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA|GLUT_MULTISAMPLE);

    glutInitWindowPosition(100,100);
    glutInitWindowSize(512,512);
    glutCreateWindow("CSCI 405 Assignment #4");

    glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);

    // Initialize the scene
    initWorld();

    // Input callbacks
	glutKeyboardFunc(keyboardPress);
	glutKeyboardUpFunc(keyboardUp);
		
    // GLUT main loop
    glutMainLoop();

    return(0);
}
