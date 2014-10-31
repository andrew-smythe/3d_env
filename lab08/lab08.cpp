#include <math.h>
#include <string>

#ifdef WIN32
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#else
#define GL_GLEXT_PROTOTYPES 1
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "GL/glext.h"
//PFNGLCREATESHADERPROC glCreateShader = 0;
#endif

#include <stdlib.h>
#include <vector>

#include <stdio.h>
#include <string.h>
#include "bitmap.h"
#include "LoadObj.h"

#include "ArcBall.h"

#define _DEBUG 0

static CMaterial *modelMaterial = NULL;

static vector3 *modelPositions = NULL;
static int numModelPositions = 0;
static vector3 *modelNormals = NULL;
static int numModelNormals = 0;
static vector2 *modelUVs = NULL;
static int numModelUVs = 0;

static GLuint modelPositionVBO = -1;
static GLuint modelNormalVBO = -1;
static GLuint modelUVVBO = -1;

// Define the globals for arcball controls and user input tracking
static CArcBall gsArcBall;
static vector2 arcballInteractions[2];

#define DEG2RAD(a) (a*3.14159f/180.0f)
#define RAD2DEG(a) (a*180.0f/3.14159f)

#define SCREENWIDTH 512
#define SCREENHEIGHT 512

const float relXScale = 1.0f;
const float relYScale = 1.0f;

#if 1
vector3 GetAtVector( float *matrix44 )
{
	return vector3( -matrix44[8], -matrix44[9], -matrix44[10] );
}

vector3 GetUpVector( float *matrix44 )
{
	return vector3( matrix44[4], matrix44[5], matrix44[6] );
}

vector3 GetRightVector( float *matrix44 )
{
	return vector3( matrix44[0], matrix44[1], matrix44[2] );
}

vector3 GetPositionVector( float *matrix44 )
{
	return vector3( matrix44[12], matrix44[13], matrix44[14] );
}
#else
vector3 GetAtVector( float *matrix44 )
{
	return vector3( -matrix44[2], -matrix44[6], -matrix44[10] );
}

vector3 GetUpVector( float *matrix44 )
{
	return vector3( matrix44[1], matrix44[5], matrix44[9] );
}

vector3 GetRightVector( float *matrix44 )
{
	return vector3( matrix44[0], matrix44[4], matrix44[8] );
}

vector3 GetPositionVector( float *matrix44 )
{
	return vector3( matrix44[3], matrix44[7], matrix44[11] );
}
#endif

void initializeCamera()
{
	gsArcBall.CameraPos( vector3( 0.0f, 0.0f, 3.0f ) );
	gsArcBall.CameraUp( vector3( 0.0f, 1.0f, 0.0f ) );
	gsArcBall.InputScalar( vector2( 5.0f, 5.0f ) );
}

void initializeLights()
{
	GLfloat light_position[] = { 0.0, 5.0, 2.0, 0.0 };
	GLfloat light_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_SMOOTH);

	glLightfv( GL_LIGHT0, GL_POSITION, light_position );
	glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient );
	glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse );
	glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular );

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_DEPTH_TEST);
}

void renderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_PROJECTION);
  	glLoadIdentity();
	gluPerspective( 90.0f, 1.0f, 1.0f, 1000.0f );
 
  	glMatrixMode(GL_MODELVIEW);
  	glLoadIdentity();

	const vector3 &CamPos = gsArcBall.CameraPos(); 
	const vector3 &CamUp = gsArcBall.CameraUp(); 
	const vector3 &SpherePos = gsArcBall.SpherePosition(); 

	gluLookAt( CamPos.X(), CamPos.Y(), CamPos.Z(), // Eye position
				SpherePos.X(), SpherePos.Y(), SpherePos.Z(), // Focus point
				CamUp.X(), CamUp.Y(), CamUp.Z() ); // Up vector

	glPushMatrix();
	{
		if( NULL != modelMaterial ) modelMaterial->Enable();

		glEnable(GL_LIGHTING);
		glPolygonMode( GL_FRONT, GL_FILL );

		if( -1 != modelPositionVBO )
		{
			if( -1 != modelNormalVBO )
			{
				glBindBuffer( GL_ARRAY_BUFFER, modelNormalVBO );
				glNormalPointer( GL_FLOAT, 0, NULL );
				glEnableClientState( GL_NORMAL_ARRAY );
			}

			if( -1 != modelUVVBO )
			{
				glClientActiveTexture( GL_TEXTURE0 );
				glBindBuffer( GL_ARRAY_BUFFER, modelUVVBO );
				glTexCoordPointer( 2, GL_FLOAT, 0, NULL );
				glEnableClientState( GL_TEXTURE_COORD_ARRAY );
			}

			glBindBuffer( GL_ARRAY_BUFFER, modelPositionVBO );
			glVertexPointer( 3, GL_FLOAT, 0, NULL );
			glEnableClientState( GL_VERTEX_ARRAY );
			
			glDrawArrays( GL_TRIANGLES, 0, numModelPositions );

			glDisableClientState( GL_VERTEX_ARRAY );
			glDisableClientState( GL_TEXTURE_COORD_ARRAY );
			glDisableClientState( GL_NORMAL_ARRAY );
		}
		else
		{
			glBegin( GL_TRIANGLES );

			for( int i = 0; i < numModelPositions; i++ )
			{
				glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
				if( numModelUVs == numModelPositions )
				{
					glTexCoord2f( modelUVs[i].X(),  modelUVs[i].Y() );
				}
				if( numModelNormals == numModelPositions )
				{
					glNormal3f( modelNormals[i].X(),  modelNormals[i].Y(),  modelNormals[i].Z() );
				}
				glVertex3f( modelPositions[i].X(),  modelPositions[i].Y(), modelPositions[i].Z() );
			}

			glEnd();
		}

		if( NULL != modelMaterial ) modelMaterial->Disable();
	}

	{
		glDisable(GL_LIGHTING);
		glBegin( GL_LINES );

		glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
		glVertex3f( -1.0f,  0.0f, 0.0f );
		glVertex3f( 1.0f,  0.0f, 0.0f );

		glColor4f( 0.0f, 1.0f, 0.0f, 1.0f );
		glVertex3f( 0.0f, -1.0f, 0.0f );
		glVertex3f( 0.0f, 1.0f, 0.0f );

		glColor4f( 0.0f, 0.0f, 1.0f, 1.0f );
		glVertex3f( 0.0f, 0.0f, -1.0f );
		glVertex3f( 0.0f, 0.0f, 1.0f );

		glEnd();
	}

#if _DEBUG
	if( arcballRotationEnabled )
	{
		glDisable(GL_LIGHTING);

		vector3 CamAt = SpherePos - CamPos; 
		CamAt.Normalize();

		vector3 CamRight = vector3::CrossProduct( CamAt, CamUp );

		vector3 GrabPoint = CamPos + CamAt + CamRight * arcballInteractions[0].X() + CamUp * arcballInteractions[0].Y();
		vector3 MovePoint = CamPos + CamAt + CamRight * arcballInteractions[1].X() + CamUp * arcballInteractions[1].Y();

		glPointSize( 5.0f );
		// Render the interaction points
		glBegin( GL_POINTS );
		glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
		glVertex3f( GrabPoint.X(), GrabPoint.Y(), GrabPoint.Z() );
		glVertex3f( MovePoint.X(), MovePoint.Y(), MovePoint.Z() );
		glEnd();
		glPointSize( 1.0f );

		// Render the rotation axis		
		glBegin( GL_LINES );
		glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
		glVertex3f( GrabPoint.X(), GrabPoint.Y(), GrabPoint.Z() );
		glVertex3f( MovePoint.X(), MovePoint.Y(), MovePoint.Z() );
		glEnd();
		
		// Render the rotation axis		
		glBegin( GL_LINES );

		glColor4f( 1.0f, 1.0f, 0.0f, 1.0f );
		glVertex3f( 0.0f,  0.0f, 0.0f );
		glVertex3f( debugArcballRotationAxis.X(), 
					debugArcballRotationAxis.Y(), 
					debugArcballRotationAxis.Z() );

		glEnd();
	}
#endif // _DEBUG

	glPopMatrix();

	glutSwapBuffers();
}

void LoadModel( const std::string &ImageName )
{
	// Read our .obj file
	bool res = LoadOBJ( "PixarBall.obj", "", modelPositions, modelNormals,  modelUVs, NULL, 
						numModelPositions, numModelNormals, numModelUVs, NULL, modelMaterial );

	return;

	if( (NULL != modelPositions ) && (0 < numModelPositions) )
	{
		glGenBuffers( 1, &modelPositionVBO );
		glBindBuffer( GL_ARRAY_BUFFER, modelPositionVBO );
		glBufferData( GL_ARRAY_BUFFER, 
						sizeof( vector3 ) * numModelPositions, 
						modelPositions, 
						GL_STATIC_DRAW );
	} 

	if( (NULL != modelNormals ) && (0 < numModelNormals) )
	{
		glGenBuffers( 1, &modelNormalVBO );
		glBindBuffer( GL_ARRAY_BUFFER, modelNormalVBO );
		glBufferData( GL_ARRAY_BUFFER, 
						sizeof( vector3 ) * numModelNormals, 
						modelNormals, 
						GL_STATIC_DRAW );
	} 

	if( (NULL != modelUVs ) && (0 < numModelUVs) )
	{
		glGenBuffers( 1, &modelUVVBO );
		glBindBuffer( GL_ARRAY_BUFFER, modelUVVBO );
		glBufferData( GL_ARRAY_BUFFER, 
						sizeof( vector2 ) * numModelUVs, 
						modelUVs, 
						GL_STATIC_DRAW );
	} 
}

// GLUT call back to handle mouse button events
void mouseFunc( int button, int state, int x, int y )
{	
	if( GLUT_LEFT_BUTTON == button )
	{
		// Transform screen-space coordinates into 
		// normalized coordinates with origin at the center
		// of the screen
		float relXPos = (float)(x - SCREENWIDTH/2) / (float)(SCREENWIDTH/2);
		float relYPos = (float)(SCREENHEIGHT/2 -  y) / (float)(SCREENHEIGHT/2);
		
		// Mouse-down sets the interaction mode for the arcball
		if( GLUT_DOWN == state )
		{			
			gsArcBall.Interacting( true );		
			arcballInteractions[0] = vector2( relXPos, relYPos );
			arcballInteractions[1] = arcballInteractions[0];
		}
		// Mouse-up clears the interaction mode for the arcball
		else
		{
			gsArcBall.Interacting( false, true );
		}
	}
}

// GLUT call back to handle mouse movement events
void mouseMotionFunc( int x, int y )
{	
	// Only care about mouse movement if we are in 
	// arcball interacting mode
	if( gsArcBall.Interacting() )
	{
		// Transform screen-space coordinates into 
		// normalized coordinates with origin at the center
		// of the screen
		float relXPos = (float)(x - SCREENWIDTH/2) / (float)(SCREENWIDTH/2);
		float relYPos = (float)(SCREENHEIGHT/2 -  y) / (float)(SCREENHEIGHT/2);

		arcballInteractions[1] = vector2( relXPos, relYPos );
				
		// Update the camera information for the arcball based on
		// latest input values
		gsArcBall.EstimateCamera( arcballInteractions[0], arcballInteractions[1] );

		#if _DEBUGUSERINPUT
		const vector3 &CamPos = gsArcBall.CameraPos(); 
		const vector3 &CamUp = gsArcBall.CameraUp(); 
		const vector3 &SpherePos = gsArcBall.SpherePosition(); 

		std::cout << "CamPos: " << CamPos.X() << ", " << CamPos.Y() << ", " << CamPos.Z() << std::endl;
		std::cout << "CamUp: " << CamUp.X() << ", " << CamUp.Y() << ", " << CamUp.Z() << std::endl;
		#endif // _DEBUGUSERINPUT
	}
}


int main(int argc, char **argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);

	glutInitWindowPosition(100,100);
	glutInitWindowSize( SCREENWIDTH, SCREENHEIGHT );
	glutCreateWindow("Object Loader and Viewer");

	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);

	glutMouseFunc( mouseFunc );
	glutMotionFunc( mouseMotionFunc );
	glutPassiveMotionFunc( mouseMotionFunc );

	// LoadImage("Lena.bmp");
	LoadModel( "Lena.bmp" );

	initializeCamera();
	initializeLights();

	//  GLUT main loop
	glutMainLoop();

	return(0);

}
