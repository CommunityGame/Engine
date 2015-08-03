#include "Camera.hpp"

Camera::Camera( float fov, float aspect, float zNear, float zFar ) :
	_fov( fov ),
	_aspect( aspect ),
	_zNear( zNear ),
	_zFar( zFar )
{
	_perspective = Mat4f().initPerspective( fov, aspect, zNear, zFar );
	return ;
}

void Camera::update( double delta )
{
	return ;
}

void		Camera::setFov( float fov )
{
	const float tanHalfFOV = tanf( fov / 2.0f );

	this->_perspective[0] = 1.0f / ( tanHalfFOV * this->_aspect );
	this->_perspective[5] = 1.0f / tanHalfFOV;
	this->_fov = fov;
}

void		Camera::setAspect( float aspect )
{
	const float tanHalfFOV = tanf( this->_fov / 2.0f );

	this->_perspective[0] = 1.0f / ( tanHalfFOV * aspect );
	this->_aspect = aspect;
}

void		Camera::setZNear( float zNear )
{
	const float zRange = zNear - this->_zFar;

	this->_perspective[10] = ( -zNear - this->_zFar ) / zRange;
	this->_perspective[14] = 2.0f * this->_zFar * zNear / zRange;
	this->_zNear = zNear;
}

void		Camera::setZFar( float zFar )
{
	const float zRange = this->_zNear - zFar;

	this->_perspective[10] = ( -this->_zNear - zFar ) / zRange;
	this->_perspective[14] = 2.0f * zFar * this->_zNear / zRange;
	this->_zFar = zFar;
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
	rotationMatrix = this->getTransform().getRotation().toMatrix();
	return ( rotationMatrix * translationMatrix );
}

float		Camera::getFov( void ) const
{
	return ( this->_fov );
}

float		Camera::getAspect( void ) const
{
	return ( this->_aspect );
}

float		Camera::getZNear( void ) const
{
	return ( this->_zNear );
}

float		Camera::getZFar( void ) const
{
	return ( this->_zFar );
}
