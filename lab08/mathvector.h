#ifndef MATHVECTOR_H__
#define MATHVECTOR_H__

//*****************************************************************************
/// vector2, vector3, vector4 class code
/// Implementation of simple encapsulated vector classes and common operators
///
///	Written by Mike Krazanowski
///		for use by students in VIU - CSCI 405 
//*****************************************************************************


#include <stdlib.h>
#include <math.h>

//-----------------------------------------------------------------------------
///  Class for 2 element vectors
//-----------------------------------------------------------------------------
class vector2
{
public:
	
	//-------------------------------------------------------------------------
	///  Default constructor
	//-------------------------------------------------------------------------
	vector2() :
		m_X( 0.0f ), 
		m_Y( 0.0f )
	{
	}

	//-------------------------------------------------------------------------
	///  Explicit constructor
	//-------------------------------------------------------------------------
	vector2( float x, float y ) :
		m_X( x ), 
		m_Y( y )
	{
	}
	
	//-------------------------------------------------------------------------
	///  Copy constructor
	//-------------------------------------------------------------------------
	vector2( const vector2 &other ) :
		m_X( other.m_X ), 
		m_Y( other.m_Y )
	{
	}

	//-------------------------------------------------------------------------
	///  Assignment operator
	//-------------------------------------------------------------------------
	const vector2& operator=( const vector2 &copyFrom )
	{
		if( this != &copyFrom )
		{
			m_X = copyFrom.m_X; 
			m_Y = copyFrom.m_Y;
		}
		return *this;
	}

	//-------------------------------------------------------------------------
	///  Element extraction operator
	//-------------------------------------------------------------------------
	virtual float operator[]( int index )
	{
		switch( index )
		{
			case 0:
				return m_X;
			case 1:
				return m_Y;	
		}

		// assert( "What the ****" );
		return 0.0f;
	}

	//-------------------------------------------------------------------------
	///  Addition operator, 
	//		Modifies contents of vector
	//-------------------------------------------------------------------------
	vector2& operator+=( const vector2 &other )
	{
		if( &other != this )
		{
			m_X += other.m_X;
			m_Y += other.m_Y;
		}
		return *this;
	}

	//-------------------------------------------------------------------------
	///  Subtraction operator, 
	//		Modifies contents of vector
	//-------------------------------------------------------------------------
	vector2& operator-=( const vector2 &other )
	{
		if( &other != this )
		{
			m_X -= other.m_X;
			m_Y -= other.m_Y;
		}
		return *this;
	}

	//-------------------------------------------------------------------------
	///  Multiplication operator, 
	//		Modifies contents of vector
	//-------------------------------------------------------------------------
	vector2& operator*=( float scalar )
	{
		return Scale( scalar );
	}


	//-------------------------------------------------------------------------
	///  Destructor
	//-------------------------------------------------------------------------
	virtual ~vector2()
	{
	}

	//-------------------------------------------------------------------------
	///  Element setters and getters
	//-------------------------------------------------------------------------
	float X() const { return m_X; };
	void X( float x ) { m_X = x; };

	float Y()  const { return m_Y; };
	void Y( float y ) { m_Y = y; };

	//-------------------------------------------------------------------------
	///  Returns the length of the vector
	//-------------------------------------------------------------------------
	float Length() 
	{
		return sqrt( m_X*m_X + m_Y*m_Y );
	}

	//-------------------------------------------------------------------------
	///  Normalizes the vector
	///		Modifies the vector
	//-------------------------------------------------------------------------
	vector2& Normalize() 
	{
		float length = Length();
		m_X /= length;
		m_Y /= length;
		return *this;
	} 

	//-------------------------------------------------------------------------
	///  Scales the vector, 
	//		Modifies contents of vector
	//-------------------------------------------------------------------------
	vector2& Scale( float scalar ) 
	{
		m_X *= scalar;
		m_Y *= scalar;
		return *this;
	} 

	//-------------------------------------------------------------------------
	///  Addition operator, 
	//		Returns a new vector
	//-------------------------------------------------------------------------
	friend vector2 operator+( const vector2 &V1, const vector2 &V2 )
	{
		return vector2( V1.X() + V2.X(),  
						V1.Y() + V2.Y() );
	}

	//-------------------------------------------------------------------------
	///  Subtraction operator, 
	//		Returns a new vector
	//-------------------------------------------------------------------------
	friend vector2 operator-( const vector2 &V1, const vector2 &V2 )
	{
		return vector2( V1.X() - V2.X(),  
						V1.Y() - V2.Y() );
	}

	//-------------------------------------------------------------------------
	///  Multiplication operator  (vector/scalar), 
	//		Returns a new vector
	//-------------------------------------------------------------------------
	friend vector2 operator*( const vector2 &V1, float S )
	{
		return vector2( V1.X() * S,  
						V1.Y() * S );
	}

	//-------------------------------------------------------------------------
	///  Multiplication operator  (vector/scalar), 
	//		Returns a new vector
	//-------------------------------------------------------------------------
	friend vector2 operator*( float S, const vector2 &V1 )
	{
		return vector2( V1.X() * S,  
						V1.Y() * S );
	}

protected:

	float m_X;
	float m_Y;
};

//-----------------------------------------------------------------------------
///  Class for 3 element vectors
///		Extents the vector2 class
//-----------------------------------------------------------------------------
class vector3 : public vector2
{
public:
	
	//-------------------------------------------------------------------------
	///  Default constructor
	//-------------------------------------------------------------------------
	vector3() :
		vector2(), 
		m_Z( 0.0f )
	{
	}

	//-------------------------------------------------------------------------
	///  Explicit constructor
	//-------------------------------------------------------------------------
	vector3( float x, float y, float z ) :
		vector2( x, y ), 
		m_Z( z )
	{
	}
	
	//-------------------------------------------------------------------------
	///  Copy constructor (from a vector2)
	//-------------------------------------------------------------------------
	vector3( const vector2 &other ) :
		vector2( other ), 
		m_Z( 0.0f )
	{
	}

	//-------------------------------------------------------------------------
	///  Copy constructor
	//-------------------------------------------------------------------------
	vector3( const vector3 &other ) :
		vector2( other ), 
		m_Z( other.m_Z )
	{
	}

	//-------------------------------------------------------------------------
	///  Assignment operator
	//-------------------------------------------------------------------------
	const vector3& operator=( const vector3 &copyFrom )
	{
		if( this != &copyFrom )
		{		
			m_X = copyFrom.m_X; 
			m_Y = copyFrom.m_Y;
			m_Z = copyFrom.m_Z;
		}
		return *this;
	}

	//-------------------------------------------------------------------------
	///  Element extraction operator
	//-------------------------------------------------------------------------
	virtual float operator[]( int index )
	{
		switch( index )
		{
			case 0:
				return m_X;
			case 1:
				return m_Y;	
			case 2:
				return m_Z;
		}

		// assert( "What the ****" );
		return 0.0f;
	}

	//-------------------------------------------------------------------------
	///  Addition operator, 
	//		Modifies contents of vector
	//-------------------------------------------------------------------------
	vector3& operator+=( const vector3 &other )
	{
		if( &other != this )
		{
			m_X += other.m_X;
			m_Y += other.m_Y;
			m_Z += other.m_Z;
		}
		return *this;
	}

	//-------------------------------------------------------------------------
	///  Subtraction operator, 
	//		Modifies contents of vector
	//-------------------------------------------------------------------------
	vector3& operator-=( const vector3 &other )
	{
		if( &other != this )
		{
			m_X -= other.m_X;
			m_Y -= other.m_Y;
			m_Z -= other.m_Z;
		}
		return *this;
	}

	//-------------------------------------------------------------------------
	///  Multiplication operator, 
	//		Modifies contents of vector
	//-------------------------------------------------------------------------
	vector3& operator*=( float scalar )
	{
		return Scale( scalar );
	}

	//-------------------------------------------------------------------------
	///  Element setters and getters
	//-------------------------------------------------------------------------
	float Z()  const { return m_Z; };
	void Z( float z ) { m_Z = z; };

	//-------------------------------------------------------------------------
	///  Returns the length of the vector
	//-------------------------------------------------------------------------
	float Length() const
	{
		return sqrt( m_X*m_X + m_Y*m_Y + m_Z*m_Z );
	}

	//-------------------------------------------------------------------------
	///  Normalizes the vector
	///		Modifies the vector
	//-------------------------------------------------------------------------
	vector3& Normalize() 
	{
		float length = Length();
		m_X /= length;
		m_Y /= length;
		m_Z /= length;
		return *this;
	} 

	//-------------------------------------------------------------------------
	///  Scales the vector, 
	//		Modifies contents of vector
	//-------------------------------------------------------------------------
	vector3& Scale( float scalar ) 
	{
		m_X *= scalar;
		m_Y *= scalar;
		m_Z *= scalar;
		return *this;
	} 

	//-------------------------------------------------------------------------
	///  Calculates the dot product of two vectors
	//-------------------------------------------------------------------------
	static float DotProduct( const vector3 &V1, const vector3 &V2 )
	{
		return V1.X() * V2.X() + V1.Y() * V2.Y() + V1.Z() * V2.Z();
	}

	//-------------------------------------------------------------------------
	///  Calclates the relative projection length of A onto B
	//-------------------------------------------------------------------------
	static float ProjectAontoBLength( const vector3 &A, const vector3 &B )
	{
		return (DotProduct( A, B ) / B.Length());
	}

	//-------------------------------------------------------------------------
	///  Calclates the vector projection of A onto B
	//-------------------------------------------------------------------------
	static vector3 ProjectAontoB( const vector3 &A, const vector3 &B )
	{
		return B * ProjectAontoBLength( A, B );
	}

	//-------------------------------------------------------------------------
	///  Calculates the cross product of two vectors
	//-------------------------------------------------------------------------
	static vector3 CrossProduct( const vector3 &V1, const vector3 &V2 )
	{
		return vector3( V1.Y() * V2.Z() - V1.Z()*V2.Y(), 
						V1.Z() * V2.X() - V1.X()*V2.Z(), 
						V1.X() * V2.Y() - V1.Y()*V2.X() );
	}

	//-------------------------------------------------------------------------
	///  Addition operator, 
	//		Returns a new vector
	//-------------------------------------------------------------------------
	friend vector3 operator+( const vector3 &V1, const vector3 &V2 )
	{
		return vector3( V1.X() + V2.X(),  
						V1.Y() + V2.Y(),  
						V1.Z() + V2.Z() );
	}

	//-------------------------------------------------------------------------
	///  Subtraction operator, 
	//		Returns a new vector
	//-------------------------------------------------------------------------
	friend vector3 operator-( const vector3 &V1, const vector3 &V2 )
	{
		return vector3( V1.X() - V2.X(),  
						V1.Y() - V2.Y(),  
						V1.Z() - V2.Z() );
	}

	//-------------------------------------------------------------------------
	///  Multiplication operator  (vector/scalar), 
	//		Returns a new vector
	//-------------------------------------------------------------------------
	friend vector3 operator*( const vector3 &V1, float S )
	{
		return vector3( V1.X() * S,  
						V1.Y() * S,  
						V1.Z() * S );
	}

	//-------------------------------------------------------------------------
	///  Multiplication operator  (vector/scalar), 
	//		Returns a new vector
	//-------------------------------------------------------------------------
	friend vector3 operator*( float S, const vector3 &V1 )
	{
		return vector3( V1.X() * S,  
						V1.Y() * S,  
						V1.Z() * S );
	}

	//-------------------------------------------------------------------------
	///  Component-wise multiplication operator  (vector/vector), 
	//		Returns a new vector
	//-------------------------------------------------------------------------
	friend vector3 operator*( const vector3 &V1, const vector3 &V2 )
	{
		return vector3( V1.X() * V2.X(),  
						V1.Y() * V2.Y(),  
						V1.Z() * V2.Z() );
	}


protected:

	float m_Z;
};

//-----------------------------------------------------------------------------
///  Class for 4 element vectors
///		Extents the vector3 class
//-----------------------------------------------------------------------------
class vector4 : public vector3
{
public:
	
	//-------------------------------------------------------------------------
	///  Default constructor
	//-------------------------------------------------------------------------
	vector4() :
		vector3(), 
		m_W( 0.0f )
	{
	}

	//-------------------------------------------------------------------------
	///  Explicit constructor
	//-------------------------------------------------------------------------
	vector4( float x, float y, float z, float w ) :
		vector3( x, y, z ), 
		m_W( w )
	{
	}
	
	//-------------------------------------------------------------------------
	///  Copy constructor (from a vector3)
	//-------------------------------------------------------------------------
	vector4( const vector3 &other ) :
		vector3( other ), 
		m_W( 0.0f )
	{
	}

	//-------------------------------------------------------------------------
	///  Copy constructor
	//-------------------------------------------------------------------------
	vector4( const vector4 &other ) :
		vector3( other ), 
		m_W( other.m_W )
	{
	}

	//-------------------------------------------------------------------------
	///  Assignment operator
	//-------------------------------------------------------------------------
	const vector4& operator=( const vector4 &copyFrom )
	{
		if( this != &copyFrom )
		{		
			m_X = copyFrom.m_X; 
			m_Y = copyFrom.m_Y;
			m_Z = copyFrom.m_Z;
			m_W = copyFrom.m_W;
		}
		return *this;
	}

	//-------------------------------------------------------------------------
	///  Element extraction operator
	//-------------------------------------------------------------------------
	virtual float operator[]( int index )
	{
		switch( index )
		{
			case 0:
				return m_X;
			case 1:
				return m_Y;	
			case 2:
				return m_Z;
			case 3:
				return m_W;
		}

		// assert( "What the ****" );
		return 0.0f;
	}

	//-------------------------------------------------------------------------
	///  Addition operator, 
	//		Modifies contents of vector
	//-------------------------------------------------------------------------
	vector4& operator+=( const vector4 &other )
	{
		if( &other != this )
		{
			m_X += other.m_X;
			m_Y += other.m_Y;
			m_Z += other.m_Z;
			m_W += other.m_W;
		}
		return *this;
	}

	//-------------------------------------------------------------------------
	///  Subtraction operator, 
	//		Modifies contents of vector
	//-------------------------------------------------------------------------
	vector4& operator-=( const vector4 &other )
	{
		if( &other != this )
		{
			m_X -= other.m_X;
			m_Y -= other.m_Y;
			m_Z -= other.m_Z;
			m_W -= other.m_W;
		}
		return *this;
	}

	//-------------------------------------------------------------------------
	///  Multiplication operator, 
	//		Modifies contents of vector
	//-------------------------------------------------------------------------
	vector4& operator*=( float scalar )
	{
		return Scale( scalar );
	}

	//-------------------------------------------------------------------------
	///  Element setters and getters
	//-------------------------------------------------------------------------
	float W()  const { return m_W; };
	void W( float w ) { m_W = w; };

	//-------------------------------------------------------------------------
	///  Returns the length of the vector
	//-------------------------------------------------------------------------
	float Length() 
	{
		return sqrt( m_X*m_X + m_Y*m_Y + m_Z*m_Z + m_W*m_W );
	}

	//-------------------------------------------------------------------------
	///  Normalizes the vector
	///		Modifies the vector
	//-------------------------------------------------------------------------
	vector4& Normalize() 
	{
		float length = Length();
		m_X /= length;
		m_Y /= length;
		m_Z /= length;
		m_W /= length;
		return *this;
	} 

	//-------------------------------------------------------------------------
	///  Scales the vector, 
	//		Modifies contents of vector
	//-------------------------------------------------------------------------
	vector4& Scale( float scalar ) 
	{
		m_X *= scalar;
		m_Y *= scalar;
		m_Z *= scalar;
		m_W *= scalar;
		return *this;
	} 

	//-------------------------------------------------------------------------
	///  Calculates the dot product of two vectors
	//-------------------------------------------------------------------------
	static float DotProduct( const vector4 &V1, const vector4 &V2 )
	{
		return V1.X() * V2.X() + V1.Y() * V2.Y() + V1.Z() * V2.Z() + V1.W() * V2.W();
	}

	//-------------------------------------------------------------------------
	///  Addition operator, 
	//		Returns a new vector
	//-------------------------------------------------------------------------
	friend vector4 operator+( const vector4 &V1, const vector4 &V2 )
	{
		return vector4( V1.X() + V2.X(),  
						V1.Y() + V2.Y(),  
						V1.Z() + V2.Z(),  
						V1.W() + V2.W() );
	}

	//-------------------------------------------------------------------------
	///  Subtraction operator, 
	//		Returns a new vector
	//-------------------------------------------------------------------------
	friend vector4 operator-( const vector4 &V1, const vector4 &V2 )
	{
		return vector4( V1.X() - V2.X(),  
						V1.Y() - V2.Y(),  
						V1.Z() - V2.Z(),  
						V1.W() - V2.W() );
	}

	//-------------------------------------------------------------------------
	///  Multiplication operator  (vector/scalar), 
	//		Returns a new vector
	//-------------------------------------------------------------------------
	friend vector4 operator*( const vector4 &V1, float S )
	{
		return vector4( V1.X() * S,  
						V1.Y() * S,  
						V1.Z() * S,  
						V1.W() * S );
	}

	//-------------------------------------------------------------------------
	///  Multiplication operator  (vector/scalar), 
	//		Returns a new vector
	//-------------------------------------------------------------------------
	friend vector4 operator*( float S, const vector4 &V1 )
	{
		return vector4( V1.X() * S,  
						V1.Y() * S,  
						V1.Z() * S,  
						V1.W() * S );
	}

protected:

	float m_W;
};


#endif // MATHVECTOR_H__
