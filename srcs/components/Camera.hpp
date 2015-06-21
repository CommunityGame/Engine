#ifndef _CAMERA_H_
# define _CAMERA_H_

#include "../AObjectComponent.hpp"
#include "../math/Math.hpp"

class Camera : public AObjectComponent
{
public:
	Camera( float fov, float aspect, float zNear, float zFar );

	virtual void		input( Input & input, double delta );
	virtual void		update( double delta );
	virtual void		render( RenderEngine const & renderEngine, Shader const & shader, Camera const & camera ) const;
	virtual void		init( CoreEngine & coreEngine ) {};

	// GETTER
	float				getFov( void ) const;
	float				getAspect( void ) const;
	float				getZNear( void ) const;
	float				getZFar( void ) const;
	Mat4f const			getPerspectiveMatrix( void ) const;

	void				setFov( float fov );
	void				setAspect( float aspect );
	void				setZNear( float zNear );
	void				setZFar( float zFar );

	Mat<float, 4, 4> const	getTransformedViewMatrix( void ) const;

private:
	float				_fov;
	float				_aspect;
	float				_zNear;
	float				_zFar;
	Mat4f				_perspective;

	//TODO: remove AObjectComponent heritage and set it own Transform

};

#endif // ! _CAMERA_H_
