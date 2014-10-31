#include "ArcBall.h"

#define CHEATMETHOD 0

CArcBall::CArcBall() :
	m_CameraPosition( 0.0f, 0.0f, 1.0f ),
	m_CameraUp( 0.0f, 1.0f, 0.0f ),
	m_InteractingCameraPosition( 0.0f, 0.0f, 1.0f ),
	m_InteractingCameraUp( 0.0f, 1.0f, 0.0f ),
	m_SpherePosition( 0.0f, 0.0f, 0.0f ), 
	m_SphereRadius( 2.0f ),
	m_InputScalar( 1.0f, 1.0f ), 
	m_Interacting( false )
{

}

CArcBall::~CArcBall()
{
}

bool 
CArcBall::Interacting()
{
	return m_Interacting;
}

void 
CArcBall::Interacting( bool I, bool Bind ) 
{
	if( !m_Interacting && I )
	{
		m_Interacting = I;

		// If setting the mode to interacting, default the 
		// temporary camera state to the active state
		m_InteractingCameraPosition = m_CameraPosition;
		m_InteractingCameraUp = m_CameraUp;
	}
	else if( m_Interacting && !I )
	{
		m_Interacting = I;
		if( Bind )
		{
			BindEstimate();
		}
	}
}

const vector3& 
CArcBall::CameraPos()
{
	if( m_Interacting )
	{
		return m_InteractingCameraPosition;
	}

	return m_CameraPosition;
}

void 
CArcBall::CameraPos( const vector3& Pos )
{
	m_CameraPosition = Pos;

	// If setting position explicitly, update the sphere radius
	vector3 delta = m_SpherePosition - m_CameraPosition;
	m_SphereRadius = delta.Length();
}

const vector3& 
CArcBall::CameraUp()
{
	if( m_Interacting )
	{
		return m_InteractingCameraUp;
	}

	return m_CameraUp;
}

void 
CArcBall::CameraUp( const vector3& Up )
{
	m_CameraUp = Up;
}


vector3 
CArcBall::CameraAt()
{
	vector3 &CamPos = m_CameraPosition;
	if( m_Interacting )
	{
		CamPos = m_InteractingCameraPosition;
	}

	vector3 delta = m_SpherePosition - CamPos; 
	delta.Normalize();
	return delta;
}
	
vector3 
CArcBall::CameraRight()
{
	vector3 &CamPos = m_CameraPosition;
	if( m_Interacting )
	{
		CamPos = m_InteractingCameraPosition;
	}

	vector3 at = m_SpherePosition - CamPos; 
	vector3 right = vector3::CrossProduct( at, m_CameraUp );
	right.Normalize();
	return right;
}

float 
CArcBall::SphereRadius()
{
	return m_SphereRadius;
}

void 
CArcBall::SphereRadius( float R )
{
	m_SphereRadius = R;

	// If setting radius explicitly, update the camera position
	vector3 delta = m_SpherePosition - m_CameraPosition;
	delta.Normalize();
	m_CameraPosition = m_SpherePosition - delta * m_SphereRadius;
}

const vector3& 
CArcBall::SpherePosition()
{
	return m_SpherePosition;
}

void 
CArcBall::SpherePosition( const vector3& Pos )
{
	m_SpherePosition = Pos;
}

vector2 
CArcBall::InputScalar()
{
	return m_InputScalar;
}
	
void 
CArcBall::InputScalar( const vector2 &IS )
{
	m_InputScalar = IS;
}

void 
CArcBall::BindEstimate()
{
	m_CameraPosition = m_InteractingCameraPosition;
	m_CameraUp = m_InteractingCameraUp;
}

#if CHEATMETHOD

void 
CArcBall::EstimateCamera( const vector2 &Origin, const vector2& Offset )
{
	if( !m_Interacting ) return;

	vector2 Delta = -1.0f * (Offset - Origin);
	
	m_CameraUp.Normalize();

	vector3 CameraAt = m_SpherePosition - m_CameraPosition;
	CameraAt.Normalize();

	vector3 CameraRight = vector3::CrossProduct( CameraAt, m_CameraUp );

	m_InteractingCameraPosition = m_CameraPosition + 
							CameraRight * (Delta.X()*m_InputScalar.X()) + 
							m_CameraUp * (Delta.Y()*m_InputScalar.Y());

	vector3 InteractingCameraAt = m_SpherePosition - m_InteractingCameraPosition;
	InteractingCameraAt.Normalize();
	m_InteractingCameraPosition = m_SpherePosition - InteractingCameraAt * m_SphereRadius;

	vector3 InteractingCameraRight = vector3::CrossProduct( InteractingCameraAt, m_CameraUp );
	m_InteractingCameraUp = vector3::CrossProduct( InteractingCameraRight, InteractingCameraAt );
}

#else // CHEATMETHOD

void RotateVectors( const vector3 &rotationAxis, float rotationAngle, 
				vector3 *vectorList, int numVectorsInList )
{
	float CT = cosf( rotationAngle );
	float OCT = (1.0f - CT);
	float ST = sinf( rotationAngle );
	float Ax = rotationAxis.X();
	float Ay = rotationAxis.Y();
	float Az = rotationAxis.Z();
	#if 0
	float RotationMatrix[4][4] = { 
			{CT + Ax*Ax*OCT,  Ax*Ay*OCT-Az*ST, Ax*Az*OCT+Ay*ST,  0.0f},
			{Ay*Ax*OCT+Az*ST, CT+Ay*Ay*OCT,    Ay*Az*OCT-Ax*ST,  0.0f},
			{Az*Ax*OCT-Ay*ST, Az*Ay*OCT+Ax*ST, CT+Az*Az*OCT,     0.0f}, 
			{0.0f,                  0.0f,                  0.0f,                   1.0f} };
	#else
	float RotationMatrix[4][4] = { 
			{CT + Ax*Ax*OCT,  Ay*Ax*OCT+Az*ST,  Az*Ax*OCT-Ay*ST,  0.0f},
			{Ax*Ay*OCT-Az*ST, CT+Ay*Ay*OCT,     Az*Ay*OCT+Ax*ST,  0.0f},
			{Ax*Az*OCT+Ay*ST, Ay*Az*OCT-Ax*ST,  CT+Az*Az*OCT,     0.0f}, 
			{0.0f,                  0.0f,                  0.0f,                   1.0f} };

	#endif
	for( int i = 0; i < numVectorsInList; i++ )
	{
		vector3 &rotVec = vectorList[i];
		vector3 origVec = rotVec;

		rotVec.X( RotationMatrix[0][0]*origVec.X() + 
				  RotationMatrix[0][1]*origVec.Y() +  
				  RotationMatrix[0][2]*origVec.Z() );

		rotVec.Y( RotationMatrix[1][0]*origVec.X() + 
				  RotationMatrix[1][1]*origVec.Y() +  
				  RotationMatrix[1][2]*origVec.Z() );

		rotVec.Z( RotationMatrix[2][0]*origVec.X() + 
				  RotationMatrix[2][1]*origVec.Y() +  
				  RotationMatrix[2][2]*origVec.Z() );
	}
}

void 
CArcBall::EstimateCamera( const vector2 &Origin, const vector2& Offset )
{
	if( !m_Interacting ) return;

	m_CameraUp.Normalize();

	vector3 CameraAt = m_SpherePosition - m_CameraPosition;
	CameraAt.Normalize();

	vector3 CameraRight = vector3::CrossProduct( CameraAt, m_CameraUp );

	// Estimate the world-space coordinate of the grab point
	vector3 OriginSpherePos = m_CameraPosition + 
							CameraRight * (Origin.X()*m_InputScalar.X()) + 
							m_CameraUp * (Origin.Y()*m_InputScalar.Y());
	vector3 OriginVector = OriginSpherePos - m_SpherePosition;
	OriginVector.Normalize();
		
	// Estimate the world-space coordinate of the grab-move point
	vector3 OffsetSpherePos = m_CameraPosition + 
							CameraRight * (Offset.X()*m_InputScalar.X()) + 
							m_CameraUp * (Offset.Y()*m_InputScalar.Y());
	vector3 OffsetVector = OffsetSpherePos - m_SpherePosition;
	OffsetVector.Normalize();

	// Calculate the rotation axis as the vector orthogonal to both the grab 
	// and offset vector.
	vector3 RotationAxis = vector3::CrossProduct( OriginVector, OffsetVector );
		
	// Dividing by the vector lengths is not necessary since the vectors have
	// been normalized
	float RotationAxisLength = RotationAxis.Length();
	if( 0.001f > fabs( RotationAxisLength ) )
	{
		// If movement isn't significant enough, use original camera state
		m_InteractingCameraPosition = m_CameraPosition;
		m_InteractingCameraUp = m_CameraUp;
	}
	else
	{
		// Calculate the angle from the identity sin(theta) = ||AxB||/||A||||B||
		float RotationAngle = asinf( RotationAxisLength );
		// Normalize the rotation vector
		RotationAxis *= (1.0f/RotationAxisLength);

		// Transform the camera vectors using the rotation axis and angle
		vector3 CamVecList[4] = { (m_CameraPosition-m_SpherePosition),
								   CameraAt,
								   m_CameraUp,
								   CameraRight }; 
		RotateVectors( RotationAxis, RotationAngle, CamVecList, 4 );

		// Ensure the arcball sphere property is maintained and that the
		// camera state is still valid (orthonormalized)
		m_InteractingCameraPosition = m_SpherePosition+CamVecList[0];

		vector3 InteractingCameraAt = m_SpherePosition - m_InteractingCameraPosition;
		InteractingCameraAt.Normalize();
		m_InteractingCameraPosition = m_SpherePosition - InteractingCameraAt * m_SphereRadius;
		
		vector3 InteractingCameraRight = vector3::CrossProduct( CamVecList[1], CamVecList[2] );
		m_InteractingCameraUp = vector3::CrossProduct( InteractingCameraRight, CamVecList[1] );
	}
}

#endif // CHEATMETHOD