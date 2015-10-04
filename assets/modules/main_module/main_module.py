from LibModule import Module, GameObject, Input, MeshComponent, Quat, Vec3, Mat4, Transform, Key, Joystick

class TestObject( GameObject ):
	def __init__(self):
		GameObject.__init__(self)
		meshO = GameObject()
		mesh = MeshComponent.loadObj( "./assets/modules/main_module/objs/Feisar_Ship.obj" )
		meshO.addComponent( mesh )
		meshO.getTransform().setScale( Vec3( 0.01, 0.01, 0.01 ) )
		self.addChild( meshO )
		# print("ok TestObject")

	def update(self, delta):
		# print( delta )
		if Input.isKeyPressed( Key.W ):
			self.getTransform().translate( Vec3( 0, 0, 0.2 ) )
		pok = Quat( 1, 1, 1, 1 )
		# pok2 = pok * Vec3( 2, 1, 1 )
		# pok2 /= Quat( 2, 2, 2, 2 )

		if Input.isJoystickPresent( Joystick.J_1 ) :
			j1 = Input.getJoystickDirection( Joystick.J_1, Joystick.RIGHT_STICKER )
			self.getTransform().translate( Vec3( j1.x, 0, j1.y ) )
			# print( j1 )
			pass
			# print( Input.getJoystickName( Joystick.J_1 ) )
		# print( Mat4.initScale( 10 ) )
		# print( Vec3( .023, 1, 2).x )
		# print( pok2.normalized() )
		# print( pok.toMatrix() )
		pass


class main_module( Module ):
	def __init__(self):
		Module.__init__(self)
		# print("ok main_module")

	def init(self, rootObject):
		# print("init")
		o1 = TestObject()
		rootObject.addChild( o1 )

	def update(self, delta):
		pass
