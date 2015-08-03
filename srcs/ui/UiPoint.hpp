#ifndef _UI_POINT_H_
# define _UI_POINT_H_

#include "../math/Math.hpp"

class UiPoint
{
public:
	UiPoint( Vec2f pos, Colorf color );

private:
	Vec2f		_pos;
	Colorf		_color;
};

#endif // ! _UI_POINT_H_
