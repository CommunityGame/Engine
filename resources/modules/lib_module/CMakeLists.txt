PYTHON_ADD_MODULE( LibModule ./srcs/modules/Module.cpp )
target_link_libraries( LibModule ${Boost_LIBRARIES} )