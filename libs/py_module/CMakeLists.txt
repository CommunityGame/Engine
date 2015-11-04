cmake_minimum_required( VERSION 2.8.4 )
project( LibModule )

PYTHON_ADD_MODULE( LibModule ../../srcs/modules/LibModule.cpp )
target_link_libraries( LibModule ${Boost_LIBRARIES} ${PYTHON_LIBRARIES} ${Module} )
