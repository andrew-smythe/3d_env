#ifndef CCOLOUR_H__
#define CCOLOUR_H__

#include <stdlib.h>
#include <math.h>
#include "mathvector.h"

#ifdef max
#undef max
#endif 
#define max(a,b)(a>b?a:b)

#ifdef min
#undef min
#endif 
#define min(a,b)(a>b?b:a)

#define clamp(a,mn,mx) (min(mx, max(mn, a))) 

class C_RGB
{
public:

	C_RGB() :
		m_Red( 0 ), m_Green( 0 ), m_Blue( 0 )
	{		
	}

	C_RGB( unsigned char R, unsigned char G, unsigned char B ) :
		m_Red( R ), m_Green( G ), m_Blue( B )
	{
	}

	C_RGB( int R, int G, int B )
	{
		m_Red = clamp(R, 0, 255); 
		m_Green = clamp(G, 0, 255);
		m_Blue = clamp(B, 0, 255);  
	}

	C_RGB( const C_RGB &C ) :
		m_Red( C.m_Red ), m_Green( C.m_Green ), m_Blue( C.m_Blue )
	{  
	}

	unsigned char Red() const { return m_Red; };
	void Red( unsigned char R ) { m_Red = R; };

	unsigned char Green() const { return m_Green; };
	void Green( unsigned char G ) { m_Green = G; };

	unsigned char Blue() const { return m_Blue; };
	void Blue( unsigned char B ) { m_Blue = B; };

	const C_RGB& operator+=( const C_RGB &Other )
	{
		if( &Other != this )
		{
			m_Red = clamp(m_Red + Other.m_Red, 0, 255); 
			m_Green = clamp(m_Green + Other.m_Green, 0, 255);
			m_Blue = clamp(m_Blue + Other.m_Blue, 0, 255); 
		}
		return *this;
	}

	const C_RGB& operator*=( float S )
	{
		m_Red =		(unsigned char)clamp(((float)m_Red)*S, 0.0f, 255.0f); 
		m_Green =	(unsigned char)clamp(((float)m_Green)*S, 0.0f, 255.0f);
		m_Blue =	(unsigned char)clamp(((float)m_Blue)*S, 0.0f, 255.0f);
		
		return *this;
	}

	friend C_RGB operator+( const C_RGB &C1, const C_RGB &C2 )
	{
		unsigned char R = clamp(C1.m_Red   + C2.m_Red, 0, 255); 
		unsigned char G = clamp(C1.m_Green + C2.m_Green, 0, 255);
		unsigned char B = clamp(C1.m_Blue  + C2.m_Blue, 0, 255); 
		
		return C_RGB( R, G, B );
	}

	friend C_RGB operator*( const C_RGB &C, float S )
	{
		unsigned char R = (unsigned char)clamp(((float)C.m_Red)*S, 0.0f, 255.0f); 
		unsigned char G = (unsigned char)clamp(((float)C.m_Green)*S, 0.0f, 255.0f);
		unsigned char B = (unsigned char)clamp(((float)C.m_Blue)*S, 0.0f, 255.0f);
	
		return C_RGB( R, G, B );
	}

	friend C_RGB operator*( const C_RGB &C1, const C_RGB &C2 )
	{
		unsigned char R = (unsigned char)clamp(((float)C1.m_Red*(float)C2.m_Red/255.0f), 0.0f, 255.0f); 
		unsigned char G = (unsigned char)clamp(((float)C1.m_Green*(float)C2.m_Green/255.0f), 0.0f, 255.0f);
		unsigned char B = (unsigned char)clamp(((float)C1.m_Blue*(float)C2.m_Blue/255.0f), 0.0f, 255.0f);
	
		return C_RGB( R, G, B );
	}

protected:

	unsigned char m_Red;
	unsigned char m_Green;
	unsigned char m_Blue;
};

#endif // CCOLOUR_H__
