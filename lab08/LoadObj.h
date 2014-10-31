#ifndef OBJLOADER_H__
#define OBJLOADER_H__

#ifdef WIN32
#include <windows.h>
#endif 

#include <stdlib.h>
#include <string>

#ifdef WIN32
#include "GL/gl.h"
#include "GL/glext.h"
#include "GL/glu.h"
#include "GL/glut.h"
#else
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include "mathvector.h"
#include "material.h"

bool LoadOBJ( const std::string &FileName, const std::string &FilePath, 
				vector3* &VertexPositions, vector3* &VertexNormals, vector2* &VertexUVs, int** Indices, 
				int &NumVertexPositions, int &NumVertexNormals, int &NumVertexUVs, int *NumIndices, CMaterial* &Material );

#endif // OBJLOADER_H__
