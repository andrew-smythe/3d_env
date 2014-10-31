/******************************************************************************
*
* Title: CSCI 405 Assignment #4
*
* Author: Andrew Smythe
*
* Date: April 27th, 2014
*
* File: Terrain.cpp
*
* Behaviour: Implementation of Terrain class methods.
*
******************************************************************************/

#include "Terrain.h"

// public constructor -- build array of terrain nodes of size X by Y.
Terrain::Terrain(int x, int y)
{
    this->sizeX = x;
    this->sizeY = y;
    
    // create array of terrain nodes
    this->nodes = new float*[this->sizeY];
    
    // construct each row
    for (int i = 0; i < this->sizeY; i++)
    {
        this->nodes[i] = new float[this->sizeX];
    }
    
    // initialize each node at height 0.0f
    for (int i = 0; i < this->sizeY; i++)
    {
        for (int j = 0; j < this->sizeX; j++)
        {
            this->nodes[i][j] = 0.0f;
        }
    }
}

// destructor class
Terrain::~Terrain()
{
    delete[] this->nodes;
}

// Draw the terrain with a left position of X,Y
// factor -- length/width of each quad represented by four vertices
void Terrain::draw(float factor)
{

    
    for (int i = 0; i < this->sizeY-1; i++)
    {
        glBegin( GL_QUAD_STRIP );
        for (int j = 0; j < this->sizeX; j++)
        {
            glColor3f( 0.2f+0.15f*(float)(this->nodes[i][j]/350), 0.8f-0.5f*(float)(this->nodes[i][j]/150), 0.0f );
            glVertex3f( (float) i*factor, this->nodes[i][j], (float) j*factor);
            glVertex3f( (float) (i+1)*factor, this->nodes[i+1][j], (float) j*factor );            
        }
        glEnd();
    }
    
    
    
    /*glPointSize( 5.0f );    
    
    glBegin( GL_POINTS );
    
    for (int i = 0; i < this->sizeY-1; i++)
    {
        for (int j = 0; j < this->sizeX; j++)
        {
            glVertex3f( (float) (i)*factor, this->nodes[i][j], (float) j*factor );
            glVertex3f( (float) (i+1)*factor, this->nodes[i+1][j], (float) j*factor );     
        }
    }
    
    
    glEnd();*/
}

// Generate the fractal terrain heights -- based on square/diamond algorithm
void Terrain::generate()
{
    ifstream is;
    is.open("terrain.data", ios::in);
    if (!is.is_open())
    {
        // Make a queue for pushing vertices -- needed for the algorithm
        queue<Pair*> squareQ;
        
        // initialize the first corner vertices, push into queue
        this->nodes[0][0] = 50.0f;
        this->nodes[0][this->sizeX-1] = 150.0f;
        this->nodes[this->sizeY-1][0] = 193.0f;
        this->nodes[this->sizeY-1][this->sizeX-1] = 142.0f;
        
        // push the first square onto the square queue
        squareQ.push(new Pair(0, 0));
        squareQ.push(new Pair(this->sizeX-1, 0));
        squareQ.push(new Pair(0, this->sizeY-1));
        squareQ.push(new Pair(this->sizeX-1, this->sizeY-1));
        
        // start the algorithm
        while (squareQ.size() > 0)
        {
            // get the four corners of the next square from the queue
            Pair* topLeftCorner = squareQ.front();
            squareQ.pop();
            
            Pair* topRightCorner = squareQ.front();
            squareQ.pop();
            
            Pair* bottomLeftCorner = squareQ.front();
            squareQ.pop();
            
            Pair* bottomRightCorner = squareQ.front();
            squareQ.pop();
            
            // DIAMOND STEP -- Get the midpoint
            int x = (bottomRightCorner->x + topLeftCorner->x) / 2;
            int y = (bottomRightCorner->y + topLeftCorner->y) / 2;
            Pair* midPoint = new Pair(x, y);
            
            // Calculate the value of the midpoint
            srand(time(NULL));
            
            float avg = (float) ( this->nodes[topLeftCorner->x][topLeftCorner->y] +
                                this->nodes[topRightCorner->x][topRightCorner->y] +
                                this->nodes[bottomLeftCorner->x][bottomLeftCorner->y] +
                                this->nodes[bottomRightCorner->x][bottomRightCorner->y] ) 
                                / 4;
                                
            float random = rand() % 50 + 75;
            random = (float) random / 100;
            //usleep(10);
                                   
            float newValue = avg * random;
            this->nodes[x][y] = newValue;
            
            // SQUARE STEP -- find each side point, and then add 4 new squares
            //                to the queue
            
            // Get distance from midpoint
            int distX = x - topLeftCorner->x;
            int distY = y - topRightCorner->y;
            int baseX, baseY;
            
            if (distX > 0 && distY > 0)
            {
                            
                // assign values to each "side point"
                for (int i = 0; i < 4; i++)
                {
                    random = rand() % 40 + 80;
                    if (i == 0)
                    {
                        avg = (float) ( this->nodes[topLeftCorner->x][topLeftCorner->y] +
                                        this->nodes[topRightCorner->x][topRightCorner->y] )
                                      / 2;
                        random = (float) random / 100;
                        this->nodes[topLeftCorner->x+distX][topLeftCorner->y] = avg * random;
                    }
                    else if (i == 1)
                    {
                        avg = (float) ( this->nodes[topRightCorner->x][topRightCorner->y] +
                                        this->nodes[bottomRightCorner->x][bottomRightCorner->y] )
                                      / 2;
                        random = (float) random / 100;
                        this->nodes[topRightCorner->x][topRightCorner->y+distY] = avg * random;
                    }
                    else if (i == 2)
                    {
                        avg = (float) ( this->nodes[bottomRightCorner->x][bottomRightCorner->y] +
                                        this->nodes[bottomLeftCorner->x][bottomLeftCorner->y] )
                                      / 2;
                        random = (float) random / 100;
                        this->nodes[bottomLeftCorner->x+distX][bottomLeftCorner->y] = avg * random;
                    }
                    else if (i == 3)
                    {
                        avg = (float) ( this->nodes[topLeftCorner->x][topLeftCorner->y] +
                                        this->nodes[bottomLeftCorner->x][bottomLeftCorner->y] )
                                      / 2;
                        random = (float) random / 100;
                        this->nodes[topLeftCorner->x][topLeftCorner->y+distY] = avg * random;
                    }
                }
                    
                // Add each resulting square to queue
                /*cout << "PUSHING TO QUEUE" << endl;
                cout << "---------------------------" << endl;
                cout << "TOP LEFT: " << topLeftCorner->x << ", " << topLeftCorner->y << endl;
                cout << "TOP RIGHT: " << topRightCorner->x << ", " << topRightCorner->y << endl;
                cout << "BOTTOM LEFT: " << bottomLeftCorner->x << ", " << bottomLeftCorner->y << endl;
                cout << "BOTTOM RIGHT: " << bottomRightCorner->x << ", " << bottomRightCorner->y << endl;
                cout << "MID X: " << x << endl;
                cout << "MID Y: " << y << endl;
                cout << "DISTX: " << distX << endl;
                cout << "DISTY: " << distY << endl;
                cout << "---------------------------" << endl;*/
                for (int i = 0; i < 4; i++)
                {
                    if (i == 0)
                    {
                        baseX = 0;
                        baseY = 0;
                    }
                    else if (i == 1)
                    {
                        baseX = distX;
                        baseY = 0;
                    }
                    else if (i == 2)
                    {
                        baseX = 0;
                        baseY = distY;
                    }
                    else if (i == 3)
                    {
                        baseX = distX;
                        baseY = distY;
                    }
                    //cout << baseX+topLeftCorner->x << ", " << baseY+topLeftCorner->y << endl;
                    squareQ.push(new Pair(baseX+topLeftCorner->x, baseY+topLeftCorner->y));
                        
                    //cout << baseX+topLeftCorner->x+distX << ", " << baseY+topLeftCorner->y << endl;
                    squareQ.push(new Pair(baseX+topLeftCorner->x+distX, baseY+topLeftCorner->y));
                        
                    //cout << baseX+topLeftCorner->x << ", " << baseY+topLeftCorner->y+distY << endl;
                    squareQ.push(new Pair(baseX+topLeftCorner->x, baseY+topLeftCorner->y+distY));
                    
                    //cout << baseX+topLeftCorner->x+distX << ", " << baseY+topLeftCorner->y+distY << endl;
                    squareQ.push(new Pair(baseX+topLeftCorner->x+distX, baseY+topLeftCorner->y+distY));
                }   
            } 
        }
        // Open file for terrain output
        ofstream os;
        os.open("terrain.data", ios::out);
        
        for (int i = 0; i < this->sizeY; i++)
        {
            for (int j = 0; j < this->sizeX; j++)
            {
                os << this->nodes[i][j] << " ";
            }
            os << endl;
        }
        
        os.close();
    }
    else
    {
        // load terrain from file
        for (int i = 0; i < this->sizeY; i++)
        {
            for (int j = 0; j < this->sizeX; j++)
            {
                is >> this->nodes[i][j];
            }
        }
    }
}


// Getters/Setters
int Terrain::getSizeX()
{
    return( this->sizeX );
}

int Terrain::getSizeY()
{
    return( this->sizeY );
}
