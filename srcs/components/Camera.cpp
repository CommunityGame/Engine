#include "Camera.hpp"

Camera::Camera( Mat4f perspective ) :
	_perspective( perspective )
{
	return ;
}

void Camera::input( Input & input )
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

// GETTER
Mat4f const	Camera::getPerspectiveMatrix( void ) const
{
	return ( this->_perspective );
}

Mat<float, 4, 4> const Camera::getTransformedViewMatrix( void ) const
{
	Mat<float, 4, 4>	translationMatrix;
	Mat<float, 4, 4>	rotationMatrix;

	translationMatrix.initTranslation( this->getTransform().getPosition() * -1 );
	rotationMatrix = this->getTransform().getRotation().conjugated().toMatrix();
	return ( rotationMatrix * translationMatrix );
}
