#include "LibModule.hpp"
#include "Module.hpp"
#include "../components/MeshComponent.hpp"
#include "../factories/MeshFactory.hpp"

template <typename T, typename U = T>
struct ArithmeticHelper
{
	static T add( T const &x1, U const &x2 )
	{
		return ( x1 + x2 );
	}

	static T sub( T const &x1, U const &x2 )
	{
		return ( x1 - x2 );
	}

	static T mul( T const &x1, U const &x2 )
	{
		return ( x1 * x2 );
	}

	static T div( T const &x1, U const &x2 )
	{
		return ( x1 / x2 );
	}

	static T normalized( T const &x )
	{
		return ( x.normalized() );
	}
};

struct Mat4Helper
{
	static Mat4f quatToMatrix( Quatf const & self )
	{
		return ( self.toMatrix() );
	}
};

struct TransformHelper
{
	static Transformf	translate( Transformf & self, Vec3f const & vec )
	{
		return ( self.translate( vec ) );
	}

	static void			setScale( Transformf & self, Vec3f const & vec )
	{
		return ( self.setScale( vec ) );
	}
};

struct GameObjectHelper : GameObject
{
	GameObjectHelper( PyObject *p ) : GameObject(),
		_self( p )
	{
		return ;
	}

	GameObjectHelper( PyObject *p, const GameObject& x ) : GameObject( x ),
		_self( p )
	{
		return ;
	}

	virtual void	update( double delta )
	{
		try
		{
			return boost::python::call_method<void>( this->_self, "update", delta );
		}
		catch( const boost::python::error_already_set & e )
		{
			PyErr_Print();
		}

	}

	static void		default_update( GameObject & self, double delta )
	{
		try
		{
			return ( self.GameObject::update( delta ) );
		}
		catch( const boost::python::error_already_set & e )
		{
			PyErr_Print();
		}
	}

private:
	PyObject *	_self;
};

struct ModuleHelper : Module
{
	ModuleHelper( PyObject *p ) : Module(),
		_self( p )
	{
		return ;
	}

	ModuleHelper( PyObject *p, const Module& x ) : Module( x ),
		_self( p )
	{
		return ;
	}

	virtual void	init( shared_ptr<GameObject> const & rootObject )
	{
		return boost::python::call_method<void>( this->_self, "init", rootObject );
	}

	virtual void	update( double delta )
	{
		return boost::python::call_method<void>( this->_self, "update", delta );
	}

	static void		default_update( Module & self, double delta )
	{
		return ( self.Module::update( delta ) );
	}

private:
	PyObject *	_self;
};

BOOST_PYTHON_MODULE(LibModule)
{
	using namespace boost::python;

	class_<Vec2f>( "Vec2", init<float, float>() )
		.def( init<Vec2f>() )
		.add_property( "x", &Vec2f::getX, &Vec2f::setX )
		.add_property( "y", &Vec2f::getY, &Vec2f::setY )
		.def( "norm", &Vec2f::norm )
		.def( "normalized", &ArithmeticHelper<Vec2f>::normalized )
		.def( "__str__", &Vec2f::toString )
		.def( self += self )
		.def( "__add__", &ArithmeticHelper<Vec2f>::add )
		.def( self -= self )
		.def( "__sub__", &ArithmeticHelper<Vec2f>::sub )
		.def( self *= self )
		.def( self *= float() )
		.def( "__mul__", &ArithmeticHelper<Vec2f>::mul )
		.def( "__mul__", &ArithmeticHelper<Vec2f, float>::mul )
		.def( self /= self )
		.def( self /= float() )
		.def( "__truediv__", &ArithmeticHelper<Vec2f>::div )
		.def( "__truediv__", &ArithmeticHelper<Vec2f, float>::div )
	;

	class_<Vec3f>( "Vec3", init<float, float, float>() )
		.def( init<Vec3f>() )
		.add_property( "x", &Vec3f::getX, &Vec3f::setX )
		.add_property( "y", &Vec3f::getY, &Vec3f::setY )
		.add_property( "z", &Vec3f::getZ, &Vec3f::setZ )
		.def( "norm", &Vec3f::norm )
		.def( "normalized", &ArithmeticHelper<Vec3f>::normalized )
		.def( "__str__", &Vec3f::toString )
		.def( self += self )
		.def( "__add__", &ArithmeticHelper<Vec3f>::add )
		.def( self -= self )
		.def( "__sub__", &ArithmeticHelper<Vec3f>::sub )
		.def( self *= self )
		.def( self *= float() )
		.def( "__mul__", &ArithmeticHelper<Vec3f>::mul )
		.def( "__mul__", &ArithmeticHelper<Vec3f, float>::mul )
		.def( self /= self )
		.def( self /= float() )
		.def( "__truediv__", &ArithmeticHelper<Vec3f>::div )
		.def( "__truediv__", &ArithmeticHelper<Vec3f, float>::div )
	;

	class_<Quatf>( "Quat", init<float, float, float, float>() )
		.def( init<Quatf>() )
		.add_property( "r", &Quatf::getR, &Quatf::setR )
		.add_property( "i", &Quatf::getI, &Quatf::setI )
		.add_property( "j", &Quatf::getJ, &Quatf::setJ )
		.add_property( "k", &Quatf::getK, &Quatf::setK )
		.def( "norm", &Quatf::norm )
		.def( "normalized", &ArithmeticHelper<Quatf>::normalized )
		.def( "toMatrix", &Mat4Helper::quatToMatrix )
		.def( "__str__", &Quatf::toString )
		.def( self *= self )
		.def( "__mul__", &ArithmeticHelper<Quatf>::mul )
		.def( "__mul__", &ArithmeticHelper<Quatf, Vec3f>::mul )
		.def( self /= self )
		.def( "__truediv__", &ArithmeticHelper<Quatf>::div )
	;

	Mat<float, 4, 4> &    (Mat4f::*initScale1)(float) = &Mat4f::initScale;
	class_<Mat4f>( "Mat4", no_init )
		.def( "initIdentity", &Mat4f::initIdentity, return_internal_reference<>() ).staticmethod( "initIdentity" )
		.def( "initScale", initScale1, return_internal_reference<>() ).staticmethod( "initScale" )
		.def( "initTranslation", &Mat4f::initTranslation, return_internal_reference<>() ).staticmethod( "initTranslation" )
		.def( "initPerspective", &Mat4f::initPerspective, return_internal_reference<>() ).staticmethod( "initPerspective" )
		.def( "__str__", &Mat4f::toString )
	;

	class_<Transformf>( "Transform", init<>() )
		.def( "translate", &TransformHelper::translate )
		.def( "setScale", &TransformHelper::setScale )
	;

	class_<Input>( "Input", no_init )
		.def( "isKeyPressed", &Input::isKeyPressed ).staticmethod( "isKeyPressed" )
		.def( "isMouseButtonPressed", &Input::isMouseButtonPressed ).staticmethod( "isMouseButtonPressed" )
		.def( "getMousePosition", &Input::getMousePosition ).staticmethod( "getMousePosition" )
		.def( "getScrollOffset", &Input::getScrollOffset ).staticmethod( "getScrollOffset" )
		.def( "isJoystickPresent", &Input::isJoystickPresent ).staticmethod( "isJoystickPresent" )
		.def( "getJoystickName", &Input::getJoystickName ).staticmethod( "getJoystickName" )
		.def( "isJoystickButtonPressed", &Input::isJoystickButtonPressed ).staticmethod( "isJoystickButtonPressed" )
		.def( "getJoystickPressure", &Input::getJoystickPressure ).staticmethod( "getJoystickPressure" )
		.def( "getJoystickDirection", &Input::getJoystickDirection ).staticmethod( "getJoystickDirection" )
	;

	class_<Module, ModuleHelper>( "Module", init<>() )
		.def( "update", &ModuleHelper::update )
		.def( "update", &ModuleHelper::default_update )
		.def( "init", &ModuleHelper::init )
	;

	register_ptr_to_python<shared_ptr<GameObject>>();
	class_<GameObject, GameObjectHelper>( "GameObject", init<>() )
		.def( "update", &GameObjectHelper::update )
		.def( "update", &GameObjectHelper::default_update )
		.def( "addChild", &GameObject::addChild )
		.def( "addComponent", &GameObject::addComponent )
		.def( "getTransform", &GameObject::getTransform, return_internal_reference<>() )
	;

	class_<AObjectComponent>( "AObjectComponent", no_init )
		;

	register_ptr_to_python<shared_ptr<MeshComponent>>();
	class_<MeshComponent, bases<AObjectComponent>>( "MeshComponent", no_init )
		.def( "loadObj", MeshFactory::loadObj );
	;

	enum_<int>( "Mouse" )
		.value( "BUTTON_1", GLFW_MOUSE_BUTTON_1 )
		.value( "BUTTON_2", GLFW_MOUSE_BUTTON_2 )
		.value( "BUTTON_3", GLFW_MOUSE_BUTTON_3 )
		.value( "BUTTON_4", GLFW_MOUSE_BUTTON_4 )
		.value( "BUTTON_5", GLFW_MOUSE_BUTTON_5 )
		.value( "BUTTON_6", GLFW_MOUSE_BUTTON_6 )
		.value( "BUTTON_7", GLFW_MOUSE_BUTTON_7 )
		.value( "BUTTON_8", GLFW_MOUSE_BUTTON_8 )
		.value( "LAST", GLFW_MOUSE_BUTTON_LAST )
		.value( "LEFT", GLFW_MOUSE_BUTTON_LEFT )
		.value( "RIGHT", GLFW_MOUSE_BUTTON_RIGHT )
		.value( "MIDDLE", GLFW_MOUSE_BUTTON_MIDDLE )
	;

	enum_<int>( "Joystick" )
		.value( "J_1", GLFW_JOYSTICK_1 )
		.value( "J_2", GLFW_JOYSTICK_2 )
		.value( "J_3", GLFW_JOYSTICK_3 )
		.value( "J_4", GLFW_JOYSTICK_4 )
		.value( "J_5", GLFW_JOYSTICK_5 )
		.value( "J_6", GLFW_JOYSTICK_6 )
		.value( "J_7", GLFW_JOYSTICK_7 )
		.value( "J_8", GLFW_JOYSTICK_8 )
		.value( "J_9", GLFW_JOYSTICK_9 )
		.value( "J_10", GLFW_JOYSTICK_10 )
		.value( "J_11", GLFW_JOYSTICK_11 )
		.value( "J_12", GLFW_JOYSTICK_12 )
		.value( "J_13", GLFW_JOYSTICK_13 )
		.value( "J_14", GLFW_JOYSTICK_14 )
		.value( "J_15", GLFW_JOYSTICK_15 )
		.value( "J_16", GLFW_JOYSTICK_16 )
		.value( "LAST", GLFW_JOYSTICK_LAST )
		.value( "LEFT_STICKER", LEFT_STICKER )
		.value( "RIGHT_STICKER", RIGHT_STICKER )
		.value( "TRIGGER", TRIGGER )
		.value( "LEFT", LEFT )
		.value( "RIGHT", RIGHT )
		.value( "UP", UP )
		.value( "DOWN", DOWN )
	;

	enum_<int>( "Key" )
		/* The unknown key */
		.value( "UNKNOWN", GLFW_KEY_UNKNOWN )

		/* Printable keys */
		.value( "SPACE", GLFW_KEY_SPACE )
		.value( "APOSTROPHE", GLFW_KEY_APOSTROPHE )        /* ' */
		.value( "COMMA", GLFW_KEY_COMMA )                  /* , */
		.value( "MINUS", GLFW_KEY_MINUS )                  /* - */
		.value( "PERIOD", GLFW_KEY_PERIOD )                /* . */
		.value( "SLASH", GLFW_KEY_SLASH )                  /* / */
		.value( "NUM_0", GLFW_KEY_0 )                      /* 0 */
		.value( "NUM_1", GLFW_KEY_1 )                      /* 1 */
		.value( "NUM_2", GLFW_KEY_2 )                      /* 2 */
		.value( "NUM_3", GLFW_KEY_3 )                      /* 3 */
		.value( "NUM_4", GLFW_KEY_4 )                      /* 4 */
		.value( "NUM_5", GLFW_KEY_5 )                      /* 5 */
		.value( "NUM_6", GLFW_KEY_6 )                      /* 6 */
		.value( "NUM_7", GLFW_KEY_7 )                      /* 7 */
		.value( "NUM_8", GLFW_KEY_8 )                      /* 8 */
		.value( "NUM_9", GLFW_KEY_9 )                      /* 9 */
		.value( "SEMICOLON", GLFW_KEY_SEMICOLON )          /* ; */
		.value( "EQUAL", GLFW_KEY_EQUAL )                  /* = */
		.value( "A", GLFW_KEY_A )                          /* A */
		.value( "B", GLFW_KEY_B )                          /* B */
		.value( "C", GLFW_KEY_C )                          /* C */
		.value( "D", GLFW_KEY_D )                          /* D */
		.value( "E", GLFW_KEY_E )                          /* E */
		.value( "F", GLFW_KEY_F )                          /* F */
		.value( "G", GLFW_KEY_G )                          /* G */
		.value( "H", GLFW_KEY_H )                          /* H */
		.value( "I", GLFW_KEY_I )                          /* I */
		.value( "J", GLFW_KEY_J )                          /* J */
		.value( "K", GLFW_KEY_K )                          /* K */
		.value( "L", GLFW_KEY_L )                          /* L */
		.value( "M", GLFW_KEY_M )                          /* M */
		.value( "N", GLFW_KEY_N )                          /* N */
		.value( "O", GLFW_KEY_O )                          /* O */
		.value( "P", GLFW_KEY_P )                          /* P */
		.value( "Q", GLFW_KEY_Q )                          /* Q */
		.value( "R", GLFW_KEY_R )                          /* R */
		.value( "S", GLFW_KEY_S )                          /* S */
		.value( "T", GLFW_KEY_T )                          /* T */
		.value( "U", GLFW_KEY_U )                          /* U */
		.value( "V", GLFW_KEY_V )                          /* V */
		.value( "W", GLFW_KEY_W )                          /* W */
		.value( "X", GLFW_KEY_X )                          /* X */
		.value( "Y", GLFW_KEY_Y )                          /* Y */
		.value( "Z", GLFW_KEY_Z )                          /* Z */
		.value( "LEFT_BRACKET", GLFW_KEY_LEFT_BRACKET )    /* [ */
		.value( "BACKSLASH", GLFW_KEY_BACKSLASH )          /* \ */
		.value( "RIGHT_BRACKET", GLFW_KEY_RIGHT_BRACKET )  /* ] */
		.value( "GRAVE_ACCENT", GLFW_KEY_GRAVE_ACCENT )    /* ` */
		.value( "WORLD_1", GLFW_KEY_WORLD_1 )              /* non-US #1 */
		.value( "WORLD_2", GLFW_KEY_WORLD_2 )              /* non-US #2 */

		/* Function keys */
		.value( "ESCAPE", GLFW_KEY_ESCAPE )
		.value( "ENTER", GLFW_KEY_ENTER )
		.value( "TAB", GLFW_KEY_TAB )
		.value( "BACKSPACE", GLFW_KEY_BACKSPACE )
		.value( "INSERT", GLFW_KEY_INSERT )
		.value( "DELETE", GLFW_KEY_DELETE )
		.value( "RIGHT", GLFW_KEY_RIGHT )
		.value( "LEFT", GLFW_KEY_LEFT )
		.value( "DOWN", GLFW_KEY_DOWN )
		.value( "UP", GLFW_KEY_UP )
		.value( "PAGE_UP", GLFW_KEY_PAGE_UP )
		.value( "PAGE_DOWN", GLFW_KEY_PAGE_DOWN )
		.value( "HOME", GLFW_KEY_HOME )
		.value( "END", GLFW_KEY_END )
		.value( "CAPS_LOCK", GLFW_KEY_CAPS_LOCK )
		.value( "SCROLL_LOCK", GLFW_KEY_SCROLL_LOCK )
		.value( "NUM_LOCK", GLFW_KEY_NUM_LOCK )
		.value( "PRINT_SCREEN", GLFW_KEY_PRINT_SCREEN )
		.value( "PAUSE", GLFW_KEY_PAUSE )
		.value( "F1", GLFW_KEY_F1 )
		.value( "F2", GLFW_KEY_F2 )
		.value( "F3", GLFW_KEY_F3 )
		.value( "F4", GLFW_KEY_F4 )
		.value( "F5", GLFW_KEY_F5 )
		.value( "F6", GLFW_KEY_F6 )
		.value( "F7", GLFW_KEY_F7 )
		.value( "F8", GLFW_KEY_F8 )
		.value( "F9", GLFW_KEY_F9 )
		.value( "F10", GLFW_KEY_F10 )
		.value( "F11", GLFW_KEY_F11 )
		.value( "F12", GLFW_KEY_F12 )
		.value( "F13", GLFW_KEY_F13 )
		.value( "F14", GLFW_KEY_F14 )
		.value( "F15", GLFW_KEY_F15 )
		.value( "F16", GLFW_KEY_F16 )
		.value( "F17", GLFW_KEY_F17 )
		.value( "F18", GLFW_KEY_F18 )
		.value( "F19", GLFW_KEY_F19 )
		.value( "F20", GLFW_KEY_F20 )
		.value( "F21", GLFW_KEY_F21 )
		.value( "F22", GLFW_KEY_F22 )
		.value( "F23", GLFW_KEY_F23 )
		.value( "F24", GLFW_KEY_F24 )
		.value( "F25", GLFW_KEY_F25 )
		.value( "KP_0", GLFW_KEY_KP_0 )
		.value( "KP_1", GLFW_KEY_KP_1 )
		.value( "KP_2", GLFW_KEY_KP_2 )
		.value( "KP_3", GLFW_KEY_KP_3 )
		.value( "KP_4", GLFW_KEY_KP_4 )
		.value( "KP_5", GLFW_KEY_KP_5 )
		.value( "KP_6", GLFW_KEY_KP_6 )
		.value( "KP_7", GLFW_KEY_KP_7 )
		.value( "KP_8", GLFW_KEY_KP_8 )
		.value( "KP_9", GLFW_KEY_KP_9 )
		.value( "KP_DECIMAL", GLFW_KEY_KP_DECIMAL )
		.value( "KP_DIVIDE", GLFW_KEY_KP_DIVIDE )
		.value( "KP_MULTIPLY", GLFW_KEY_KP_MULTIPLY )
		.value( "KP_SUBTRACT", GLFW_KEY_KP_SUBTRACT )
		.value( "KP_ADD", GLFW_KEY_KP_ADD )
		.value( "KP_ENTER", GLFW_KEY_KP_ENTER )
		.value( "KP_EQUAL", GLFW_KEY_KP_EQUAL )
		.value( "LEFT_SHIFT", GLFW_KEY_LEFT_SHIFT )
		.value( "LEFT_CONTROL", GLFW_KEY_LEFT_CONTROL )
		.value( "LEFT_ALT", GLFW_KEY_LEFT_ALT )
		.value( "LEFT_SUPER", GLFW_KEY_LEFT_SUPER )
		.value( "RIGHT_SHIFT", GLFW_KEY_RIGHT_SHIFT )
		.value( "RIGHT_CONTROL", GLFW_KEY_RIGHT_CONTROL )
		.value( "RIGHT_ALT", GLFW_KEY_RIGHT_ALT )
		.value( "RIGHT_SUPER", GLFW_KEY_RIGHT_SUPER )
		.value( "MENU", GLFW_KEY_MENU )
		.value( "LAST", GLFW_KEY_LAST )
	;
}
