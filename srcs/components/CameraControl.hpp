#ifndef _CAMERA_CONTROL_H_
# define _CAMERA_CONTROL_H_

#include "../AObjectComponent.hpp"

class CameraControl : public AObjectComponent
{
public:
	CameraControl( void );
	~CameraControl( void );

	virtual void		input( Input & input );
	virtual void		update( double delta );
	virtual void		render( RenderEngine const & renderEngine, Shader const & shader, Camera const & camera ) const {};

	// SETTER
	void				setSpeed( float speed );

private:
	float				_speed;
	Vec3f				_motion;
	Quatf				_rotation;
	bool				_mouseLocked;
	Vec2d				_windowCenter;
};

#endif // ! _CAMERA_CONTROL_H_
