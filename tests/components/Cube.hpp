#ifndef _CUBE_H_
# define _CUBE_H_

#include "../../srcs/GameObject.hpp"
#include "../../srcs/components/Mesh.hpp"

class Cube : public GameObject
{
public:
	Cube( float size );

private:
	static shared_ptr<Mesh>	_cube;
};

#endif // ! _CUBE_H_
