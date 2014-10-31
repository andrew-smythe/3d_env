#include "material.h"

#include "bitmap.h"

GLuint LoadImage( const std::string &ImageName )
{
	GLuint texHandle = 0;
	CBitmap *Bitmap = new CBitmap( ImageName.c_str() );

	if( NULL != Bitmap )
	{
		glEnable( GL_BLEND );
		glEnable( GL_TEXTURE_2D );
			
		glGenTextures(1, &texHandle);  
		glBindTexture(GL_TEXTURE_2D, texHandle); 

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	 
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

		glEnable( GL_BLEND );
		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	 
		int imageWidth = Bitmap->GetWidth();
		int imageHeight = Bitmap->GetHeight();
		void *imageData = Bitmap->GetBits();

		GLenum errEnum = glGetError();

		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData );

		errEnum = glGetError();
		if( GL_NO_ERROR != errEnum )
		{
			printf( "An error occured: %x\n", errEnum );
		}

		glBindTexture( GL_TEXTURE_2D, 0 ); 
	}

	return texHandle;
}


void 
CMaterial::TextureFileName( const std::string &N ) 
{ 
	if( N != m_TextureFileName )
	{
		m_GLTextureHandle = 0;
		m_TextureFileName = N; 

		m_GLTextureHandle = LoadImage( m_TextureFileName );
	}
};

void 
CMaterial::Enable()
{
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	glBindTexture (GL_TEXTURE_2D, m_GLTextureHandle );

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

void 
CMaterial::Disable()
{
	glBindTexture(GL_TEXTURE_2D, 0); 
}
