#include <fstream>
#include <string.h>
#include "LoadObj.h"
#include "colour.h"

#define _DEBUGINDICES 1

#if _DEBUGINDICES
#include <iostream>
#endif // _DEBUGINDICES

// Checks to see if the given character is considered
// whitespace or not
bool iswhitespace( char c )
{
	return ((' ' == c) || ('\n' == c) || ('\r' == c) );
}

void trimwhitespace( char* &str )
{
	// Trim the whitespace from the beginning
	while( (0 != str[0]) && iswhitespace( str[0] )) 
		str = &(str[1]);

	// Trim the whitespace from the end
	int len = strlen( str );
	while( (0 > len) && iswhitespace( str[len-1] )) 
	{
		str[len-1] = 0;
		len--;
	}
}

int LoadVector( char *vecStr, int vectorWidth, float *vectorValues )
{
	// Trim any whitespace for the provided string
	trimwhitespace( vecStr );

	char *tok = strtok( vecStr, " " );
	for( int i = 0; i < vectorWidth; i++ )
	{
		vectorValues[i] = (float)atof( tok );
		tok = strtok( NULL, " " );
	}

	return 3;
}

void ValidateIntBuffer( int **IndexBuffer, int *BuffIndex )
{
	if( (NULL == IndexBuffer) || (NULL == BuffIndex) ) return;
	if( 0 == (((*BuffIndex)+1)%32) )
	{
		(*IndexBuffer) = (int*)realloc( *IndexBuffer, sizeof(int) * (((*BuffIndex)+1)+32) );
	} 
}

void LoadFaceData( char *faceStr, 
							int **VertexIndexBuffer, int *VBuffIndex, 
							int **NormalIndexBuffer, int *NBuffIndex, 
							int **UVIndexBuffer, int *UVBuffIndex )
{
	// Trim any whitespace for the provided string
	trimwhitespace( faceStr );

	char *vertextok[4] = {NULL};
	vertextok[0] = strtok( faceStr, " " );
	vertextok[1] = strtok( NULL, " " );
	vertextok[2] = strtok( NULL, " " );
	// vertextok[4] = strtok( NULL, " " );

	char *indtok = NULL;
	int delimoffset = 0; 
	for( int i = 0; i < 3; i++ )
	{
		// indtok = strtok( vertextok[i], "/" );
		indtok = vertextok[i];
		delimoffset = strcspn( indtok, "/" );
		indtok[ delimoffset ] = 0;
		if( 0 < strlen( indtok ) )
		{
			if( (NULL != VertexIndexBuffer) && (NULL != VBuffIndex) )
			{
				ValidateIntBuffer( VertexIndexBuffer, VBuffIndex );
				(*VertexIndexBuffer)[ (*VBuffIndex)++ ] = atoi( indtok );
			}
		}

		// indtok = strtok( NULL, "/" );
		indtok = &(indtok[delimoffset+1]); 
		delimoffset = strcspn( indtok, "/" );
		indtok[ delimoffset ] = 0;
		if( (NULL != indtok) && (0 < strlen( indtok )) )
		{
			if( (NULL != UVIndexBuffer) && (NULL != VBuffIndex) )
			{
				ValidateIntBuffer( UVIndexBuffer, UVBuffIndex );
				(*UVIndexBuffer)[ (*UVBuffIndex)++ ] = atoi( indtok );
			}
		}

		// indtok = strtok( NULL, "/" );
		indtok = &(indtok[delimoffset+1]); 
		delimoffset = strcspn( indtok, "/" );
		indtok[ delimoffset ] = 0;
		if( (NULL != indtok) && (0 < strlen( indtok )) )
		{
			if( (NULL != NormalIndexBuffer) && (NULL != NBuffIndex) )
			{
				ValidateIntBuffer( NormalIndexBuffer, NBuffIndex );
				(*NormalIndexBuffer)[ (*NBuffIndex)++ ] = atoi( indtok );
			}
		}
	}
}

bool LoadPosition( char *posStr, vector3* VertexPositions )
{
	float Position[3] = { 0.0f, 0.0f, 0.0f };

	if( (NULL != VertexPositions) && LoadVector( posStr, 3, Position ) )
	{
		VertexPositions->X( Position[0] );
		VertexPositions->Y( Position[1] );
		VertexPositions->Z( Position[2] );
		return true;
	}

	return false;
} 

bool LoadNormal( char *normStr, vector3* VertexNormals )
{
	float Normal[3] = { 0.0f, 0.0f, 0.0f };

	if( (NULL != VertexNormals) && LoadVector( normStr, 3, Normal ) )
	{
		VertexNormals->X( Normal[0] );
		VertexNormals->Y( Normal[1] );
		VertexNormals->Z( Normal[2] );
		return true;
	}

	return false;
} 

bool LoadTextureCoordinates( char *texStr, vector2* VertexTexCoords )
{
	float UVs[2] = { 0.0f, 0.0f };

	if( (NULL != VertexTexCoords) && LoadVector( texStr, 2, UVs ) )
	{
		VertexTexCoords->X( UVs[0] );
		VertexTexCoords->Y( UVs[1] );
		return true;
	}
    
	return false;
} 

void LoadMaterial( const std::string &MaterialLibraryName, 
					const std::string &MaterialInstanceName, 
					CMaterial* &Material )
{
	bool DesiredMaterialFound = false;
	std::string Data;
	char LineBuff[1024];
    std::ifstream File( MaterialLibraryName.c_str() );
	
	CMaterial *WorkingMat = Material;
	if( NULL == WorkingMat )
	{
		WorkingMat = Material = new CMaterial();
	}

    while ( !File.eof() )
    {
		getline(File, Data);
		strcpy( LineBuff, Data.c_str() );
		
		if( (0 == strncmp( "newmtl", LineBuff, 6 )) )
		{
			if( DesiredMaterialFound ) return;		// Found the end of the current material
			else if( MaterialInstanceName == std::string( &(LineBuff[7]) ) ) 
			{
				WorkingMat->Name( MaterialInstanceName );
				DesiredMaterialFound = true;
			}
		}
		else if( DesiredMaterialFound && (NULL != WorkingMat) )
		{
			if( ('N' == LineBuff[0]) && ('s' == LineBuff[1]) )
			{
				char Exp[32];
				int NumScanned = sscanf( &(LineBuff[3]), "%s", Exp );
				if( 1 == NumScanned )
				{
					WorkingMat->SpecularExponent( atof( Exp ) );
				}
			}
			else if( ('K' == LineBuff[0]) && ('a' == LineBuff[1]) )
			{
				char RS[32], GS[32], BS[32];
				int NumScanned = sscanf( &(LineBuff[3]), "%s %s %s", RS, GS, BS );
				if( 3 == NumScanned )
				{
					float R = atof( RS );
					float G = atof( GS );
					float B = atof( BS );
					WorkingMat->Ambient( C_RGB( (int)(R * 255.0f), 
												(int)(G * 255.0f), 
												(int)(B * 255.0f) ) );
				}
			}
			else if( ('K' == LineBuff[0]) && ('d' == LineBuff[1]) )
			{
				char RS[32], GS[32], BS[32];
				int NumScanned = sscanf( &(LineBuff[3]), "%s %s %s", RS, GS, BS );
				if( 3 == NumScanned )
				{
					float R = atof( RS );
					float G = atof( GS );
					float B = atof( BS );
					WorkingMat->Diffuse( C_RGB( (int)(R * 255.0f), 
												(int)(G * 255.0f), 
												(int)(B * 255.0f) ) );
				}
			}
			else if( ('K' == LineBuff[0]) && ('s' == LineBuff[1]) )
			{
				char RS[32], GS[32], BS[32];
				int NumScanned = sscanf( &(LineBuff[3]), "%s %s %s", RS, GS, BS );
				if( 3 == NumScanned )
				{
					float R = atof( RS );
					float G = atof( GS );
					float B = atof( BS );
					WorkingMat->Specular( C_RGB( (int)(R * 255.0f), 
												 (int)(G * 255.0f), 
												 (int)(B * 255.0f) ) );
				}
			}
			else if( (0 == strncmp( "map_Kd", LineBuff, 6 )) )
			{
				std::string TextureFile( &(LineBuff[7]) );
				std::cout << "TEXTURE FILE IS: " << TextureFile << std::endl;
				WorkingMat->TextureFileName( TextureFile );
			}
		}
	}
}


bool LoadOBJTriangles( const std::string &FileName, const std::string &FilePath, vector3* &VertexPositions, vector3* &VertexNormals, vector2* &VertexUVs, 
									int &NumVertexPositions, int &NumVertexNormals, int &NumVertexUVs, CMaterial* &Material )
{
	int VIndex = 0;
	int NIndex = 0;
	int UVIndex = 0;

	vector3 *VertexBuffer = (vector3*)malloc( sizeof( vector3 ) * 32 );
	vector3 *NormalBuffer = (vector3*)malloc( sizeof( vector3 ) * 32 );
	vector2 *UVBuffer = (vector2*)malloc( sizeof( vector2 ) * 32 );

	int VBuffIndex = 0;
	int NBuffIndex = 0;
	int UVBuffIndex = 0;

	int *VertexIndexBuffer = (int*)malloc( sizeof( int ) * 32 );
	int *NormalIndexBuffer = (int*)malloc( sizeof( int ) * 32 );
	int *UVIndexBuffer = (int*)malloc( sizeof( int ) * 32 );

	std::string MaterialLibraryName = "";

    std::string Data;
	char LineBuff[1024];
	std::string FileNameNPath = FilePath + FileName;
    std::ifstream File( FileNameNPath.c_str() );
    while ( !File.eof() )
    {
        getline(File, Data);
		strcpy( LineBuff, Data.c_str() );
		if ( 0 == strncmp( "mtllib", LineBuff, 6 ) )
		{
			MaterialLibraryName = FilePath + std::string( &(Data[7]) );
		}
		else if ( 0 == strncmp( "usemtl", LineBuff, 6 ) ) 
		{
			std::string MaterialInstanceName( &(LineBuff[7]) );
			LoadMaterial( MaterialLibraryName, MaterialInstanceName, Material );
		}
        else if ( (Data[0] == 'v') && (Data[1] != 't') && (Data[1] != 'n') )
        {
			VIndex++;
			if( 0 == (VIndex % 32) ) 
			{
				VertexBuffer = (vector3*)realloc( VertexBuffer, sizeof(vector3) * (VIndex+32) );
			}
            LoadPosition( &(LineBuff[1]), &VertexBuffer[VIndex-1] ); 
        }
        else if ( (Data[0] == 'v') && (Data[1] == 'n') )
        {
			NIndex++;
			if( 0 == (NIndex % 32) ) 
			{
				NormalBuffer = (vector3*)realloc( NormalBuffer, sizeof(vector3) * (NIndex+32) );
			}
        	LoadNormal( &(LineBuff[2]), &NormalBuffer[NIndex-1] );
        }
        else if ( (Data[0] == 'v') && (Data[1] == 't') )
        {
			UVIndex++;
			if( 0 == (UVIndex % 32) ) 
			{
				UVBuffer = (vector2*)realloc( UVBuffer, sizeof(vector2) * (UVIndex+32) );
			}
			LoadTextureCoordinates( &(LineBuff[2]), &UVBuffer[UVIndex-1] ); 
        }
        else if ( Data[0] == 'f' )
        {
			LoadFaceData( &(LineBuff[1]), 
							&VertexIndexBuffer, &VBuffIndex, 
							&NormalIndexBuffer, &NBuffIndex, 
							&UVIndexBuffer, &UVBuffIndex );
        }
    }

	// Must have at least vertices
	if( 0 < VBuffIndex )
	{
		NumVertexPositions = VBuffIndex;
		vector3 *PosArr = new vector3[ NumVertexPositions ]; 
		VertexPositions = PosArr;

		VertexNormals = NULL;
		NumVertexNormals = NBuffIndex;		
		if( 0 < NumVertexNormals )
		{
			vector3 *NormArr = new vector3[ NumVertexNormals ];
			VertexNormals = NormArr;
		}

		VertexUVs = NULL;
		NumVertexUVs = UVBuffIndex;
		if( 0 < NumVertexUVs )
		{
			vector2 *UVArr = new vector2[ NumVertexUVs ];
			VertexUVs = UVArr;
		}
	}

	#if _DEBUGINDICES
	for( int i = 0; i < VBuffIndex; i++ )
	{
		std::cout << "vi-" << i << ": " << VertexIndexBuffer[ i ] - 1 << std::endl;
		std::cout << "ni-" << i << ": " << NormalIndexBuffer[ i ] - 1 << std::endl;
		std::cout << "ti-" << i << ": " << UVIndexBuffer[ i ] - 1 << std::endl;
	}
	#endif // _DEBUGINDICES

	for( int i = 0; i < VBuffIndex; i++ )
	{
		// Indices are 1-based instead of 0-based
		// subtract 1 to get the buffer index
		VertexPositions[i] = VertexBuffer[ VertexIndexBuffer[ i ] - 1 ];

		if( 0 < NumVertexNormals )
		{
        	VertexNormals[i] = NormalBuffer[ NormalIndexBuffer[ i ] - 1 ];
		}
        
		if( 0 < NumVertexUVs )
		{
        	VertexUVs[i] = UVBuffer[ UVIndexBuffer[ i ] - 1 ];
		}	
	}
	
	return true;
}

bool LoadOBJPrimitives( const std::string &FileName, const std::string &FilePath, vector3* &VertexPositions, vector3* &VertexNormals, vector2* &VertexUVs, int** Indices, 
									int &NumVertexPositions, int &NumVertexNormals, int &NumVertexUVs, int *NumIndices, CMaterial* &Material )
{
	return true;
}

bool LoadOBJ( const std::string &FileName, const std::string &FilePath, vector3* &VertexPositions, vector3* &VertexNormals, vector2* &VertexUVs, int** Indices, 
							int &NumVertexPositions, int &NumVertexNormals, int &NumVertexUVs, int *NumIndices, CMaterial* &Material )
{
    if( NULL == Indices )
	{
		return LoadOBJTriangles( FileName, FilePath, VertexPositions, VertexNormals, VertexUVs,
						NumVertexPositions, NumVertexNormals, NumVertexUVs, Material );
	}
	else 
	{
		return LoadOBJPrimitives( FileName, FilePath, VertexPositions, VertexNormals, VertexUVs, Indices,
						NumVertexPositions, NumVertexNormals, NumVertexUVs, NumIndices, Material );
	}
	return false;
}
