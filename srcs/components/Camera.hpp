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

private:
	Mat4f				_perspective;

};

#endif // ! _CAMERA_H_
