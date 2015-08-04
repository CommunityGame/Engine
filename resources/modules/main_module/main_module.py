# import Module
#
# test = Module()
#
# tset.update()

# class Test( Module ):
#
# 	def __init__(self):
# 		print("__init__ Test")

import LibModule

class Test( LibModule.Module ):
	def __init__(self):
		LibModule.Module.__init__(self)
		print("ok")


c1 = Test()
# c2 = LibModule.Module()
# c2.update(0.1)