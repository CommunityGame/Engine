#ifndef _CAMERA_CONTROL_H_
# define _CAMERA_CONTROL_H_

#include "basic/InputComponent.hpp"
#include "../Input.hpp"

class CameraControl : public InputComponent
{
public:
	CameraControl( void );
	~CameraControl( void );

	virtual void		input( Input & input, double delta );
	virtual void		update( double delta );
	virtual void		init( CoreEngine & coreEngine ) {};
	// SETTER
	void				setSpeed( float speed );

private:
	float				_speed;
	Vec3f				_motion;
	Quatf				_rotation;
	bool				_mouseLocked;
	Vec2d				_oldMousePos;
};

#endif // ! _CAMERA_CONTROL_H_
