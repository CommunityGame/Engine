#ifndef _CAMERA_H_
# define _CAMERA_H_

#include "../AObjectComponent.hpp"
#include "../math/Math.hpp"

class Camera : public AObjectComponent
{
public:
	Camera( Mat4f perspective );

	virtual void		input( Input const & input );
	virtual void		update( double delta );
	virtual void		render( RenderEngine const & renderEngine, Shader const & shader, Camera const & camera ) const;

	// GETTER
	Mat4f const			getPerspectiveMatrix( void ) const;
private:
	Mat4f				_perspective;

	//TODO: remove AObjectComponent heritage and set it own Transform

};

#endif // ! _CAMERA_H_
