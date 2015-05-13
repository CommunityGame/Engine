#include "Camera.hpp"

Camera::Camera( Mat4f perspective ) :
	_perspective( perspective )
{
	return ;
}

void Camera::input( Input const & input )
{
	return ;
}

void Camera::update( double delta )
{
	return ;
}

void Camera::render( RenderEngine const & renderEngine, Shader const & shader, Camera const & camera ) const
{
	return ;
}
