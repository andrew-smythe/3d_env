#ifndef CMATERIAL_H__
#define CMATERIAL_H__

#include <stdlib.h>
#include <math.h>
#include "mathvector.h"
#include "colour.h"

#include <string>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

class CMaterial
{
public:

	CMaterial() :
		m_AmbientRGB( 10, 10, 10 ), 
		m_DiffuseRGB( 0, 0, 0 ), 
		m_SpecularRGB( 0, 0, 0 ), 
		m_SpecularExponent( 1.0f ), 

		m_GLTextureHandle( 0 )
	{
	}

	CMaterial( const CMaterial &Other ) :
		m_MaterialName( Other.m_MaterialName ),
		m_AmbientRGB( Other.m_AmbientRGB ),
		m_DiffuseRGB( Other.m_DiffuseRGB ),
		m_SpecularRGB( Other.m_SpecularRGB ), 
		m_SpecularExponent( Other.m_SpecularExponent ),
 
		m_TextureFileName( Other.m_TextureFileName ), 
		m_GLTextureHandle( Other.m_GLTextureHandle )
	{
	}

	CMaterial( const C_RGB &AmbientRGB, 
			const C_RGB &DiffuseRGB, 
			const C_RGB &SpecularRGB, 
			float SpecularExponent, 
			float Reflectivity ) :
		m_AmbientRGB( AmbientRGB ),
		m_DiffuseRGB( DiffuseRGB ),
		m_SpecularRGB( SpecularRGB ),
		m_SpecularExponent( SpecularExponent ),

		m_GLTextureHandle( 0 )
		
	{
	}

	virtual ~CMaterial()
	{
	}

	CMaterial* Copy() const 
	{
		return new CMaterial( *this );
	}

	const CMaterial& operator=( const CMaterial &Other ) 
	{
		if( &Other != this )
		{
			m_MaterialName = Other.m_MaterialName;			
			m_AmbientRGB = Other.m_AmbientRGB;
			m_DiffuseRGB = Other.m_DiffuseRGB;
			m_SpecularRGB = Other.m_SpecularRGB; 
			m_SpecularExponent = Other.m_SpecularExponent; 
			
			m_TextureFileName = Other.m_TextureFileName;
			m_GLTextureHandle = Other.m_GLTextureHandle;
		}
		
		return *this;
	}

	const std::string& Name() const { return m_MaterialName; }
	void Name( const std::string &N ) { m_MaterialName = N; };

	const C_RGB& Ambient() const { return m_AmbientRGB; }
	void Ambient( const C_RGB &Amb ) { m_AmbientRGB = Amb; };

	const C_RGB& Diffuse() const { return m_DiffuseRGB; }
	void Diffuse( const C_RGB &Diff ) { m_DiffuseRGB = Diff; };

	const C_RGB& Specular() const { return m_SpecularRGB; }
	void Specular( const C_RGB &Spec ) { m_SpecularRGB = Spec; };

	float SpecularExponent() const { return m_SpecularExponent; }
	void SpecularExponent( float Exp ) { m_SpecularExponent = Exp; };

	const std::string& TextureFileName() const { return m_TextureFileName; }
	void TextureFileName( const std::string &N );

	GLuint GLTextureHandle() const { return m_GLTextureHandle; }

	void Enable();
	void Disable();

protected:

	std::string m_MaterialName;

	C_RGB 		m_AmbientRGB; 
	C_RGB 		m_DiffuseRGB; 
	C_RGB 		m_SpecularRGB;
	float 		m_SpecularExponent; 

	std::string m_TextureFileName;
	GLuint		m_GLTextureHandle;	
};

#endif // CMATERIAL_H__
