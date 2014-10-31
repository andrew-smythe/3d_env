#ifndef _ARCBALL_H__
#define _ARCBALL_H__

//*****************************************************************************
/// ArcBall class code
/// Implementation of arcball camera control, encapsulated and abstracted in
/// a class.  This arcball implementation:
///		Supports an arbitrary arcball sphere origin
///		Supports an arbitrary arcball sphere radius
///		Supports tuning of user inputs for sensitivity
///		Supports an interactive vs non-interactive mode
///		Assumes a constant camera state (for non-interactive mode) with offsets
///			from this constant state to represent interactive mode.
///
///	Written by Mike Krazanowski
///		for use by students in VIU - CSCI 405 
//*****************************************************************************

#include "mathvector.h"

//-----------------------------------------------------------------------------
/// Class CArcBall
/// Class to abstract and control the user interaction for simulating the
///		arcball camera control sceme.
//-----------------------------------------------------------------------------
class CArcBall
{
public:

	//-------------------------------------------------------------------------
	/// \constructor	
	//-------------------------------------------------------------------------
	CArcBall();

	//-------------------------------------------------------------------------
	/// \destructor	
	//-------------------------------------------------------------------------
	virtual ~CArcBall();

	//-------------------------------------------------------------------------
	/// \method Interacting
	/// \returns Whether or not the arcball is in interacting mode or not
	//-------------------------------------------------------------------------
	bool Interacting();
	
	//-------------------------------------------------------------------------
	/// \method Interacting
	/// \params 
	///		I: Allows user to set whether or not the arcball is in interacting 
	///			mode or not
	///		Bind: When I==false, allows user to specify whether or not to use 
	///			the current temporary state as the active reference state.
	//-------------------------------------------------------------------------
	void Interacting( bool I, bool Bind = true );

	//-------------------------------------------------------------------------
	/// \method CameraPos
	/// \returns The world-space coordinate of the camera.
	///	\note If in interacting mode, will return the temporary camera 
	///			coordinate.
	//-------------------------------------------------------------------------
	const vector3& CameraPos();
	
	//-------------------------------------------------------------------------
	/// \method CameraPos
	/// \params
	///		Pos: The world-space coordinate of the camera.
	//-------------------------------------------------------------------------
	void CameraPos( const vector3& Pos );

	//-------------------------------------------------------------------------
	/// \method CameraUp
	/// \returns The world-space up vector of the camera.
	///	\note If in interacting mode, will return the temporary camera up
	///			vector.
	//-------------------------------------------------------------------------
	const vector3& CameraUp();
	//-------------------------------------------------------------------------
	/// \method CameraUp
	/// \params
	///		Up: The world-space up vector of the camera.
	//-------------------------------------------------------------------------
	void CameraUp( const vector3& Up );

	//-------------------------------------------------------------------------
	/// \method CameraAt
	/// \returns The world-space at vector of the camera.
	///	\note If in interacting mode, will return the temporary camera at
	///			vector.
	//-------------------------------------------------------------------------
	vector3 CameraAt();
	
	//-------------------------------------------------------------------------
	/// \method CameraRight
	/// \returns The world-space right vector of the camera.
	///	\note If in interacting mode, will return the temporary camera right
	///			vector.
	//-------------------------------------------------------------------------
	vector3 CameraRight();

	//-------------------------------------------------------------------------
	/// \method SphereRadius
	/// \returns Radius of the arcball sphere.
	//-------------------------------------------------------------------------
	float SphereRadius();
	
	//-------------------------------------------------------------------------
	/// \method SphereRadius
	/// \params 
	//		R: Radius of the arcball sphere.
	//-------------------------------------------------------------------------
	void SphereRadius( float R );

	//-------------------------------------------------------------------------
	/// \method SpherePosition
	/// \returns World-space cooridnate of the arcball.
	//-------------------------------------------------------------------------
	const vector3& SpherePosition();
	
	//-------------------------------------------------------------------------
	/// \method SpherePosition
	/// \params 
	///		Pos: World-space cooridnate of the arcball.
	//-------------------------------------------------------------------------
	void SpherePosition( const vector3& Pos );

	//-------------------------------------------------------------------------
	/// \method InputScalar
	/// \returns A scalar to allow the user to modify the sensitivity of the
	///		use inputs relative to the interaction response.
	//-------------------------------------------------------------------------
	vector2 InputScalar();
	
	//-------------------------------------------------------------------------
	/// \method InputScalar
	/// \params 
	///		IS: A scalar to allow the user to modify the sensitivity of the
	///		use inputs relative to the interaction response.
	//-------------------------------------------------------------------------
	void InputScalar( const vector2 &IS );

	//-------------------------------------------------------------------------
	/// \method BindEstimate
	///		Allows the caller to set the temporary (interacting) camera state
	///			as the currently active reference state.
	/// \params None 
	//-------------------------------------------------------------------------
	void BindEstimate();
	
	//-------------------------------------------------------------------------
	/// \method EstimateCamera
	///		Calculates the temporary (interacting) camera state using the
	///			currently active camera state and the provided delta offsets.
	/// \params 
	///		Origin: Provides the grab point of the sphere in in normalized
	///			camera coordinates.
	///		Offset: Provides the grab point of the sphere in in normalized
	///			camera coordinates.
	//-------------------------------------------------------------------------
	virtual void EstimateCamera( const vector2 &Origin, const vector2 &Offset );

protected:

	vector3 m_CameraPosition;
	vector3 m_CameraUp;

	vector3 m_SpherePosition;
	float m_SphereRadius;

	vector2 m_InputScalar;
	
	vector3 m_InteractingCameraPosition;
	vector3 m_InteractingCameraUp;
	bool m_Interacting;
};

#endif // _ARCBALL_H__