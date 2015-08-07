#ifndef _MODULE_H_
# define _MODULE_H_

#include <string>
#include "../GameObject.hpp"
#include <boost/python.hpp>

class Module
{
public:
	Module( void );

	static Module *	load( std::string const & path, std::string const & name );

	void			addObject( GameObject * object );

	virtual void	init( shared_ptr<GameObject> const & rootObject ) {};
	virtual void	update( double delta ) {};
	virtual void	input( Input const & input ) {};

	// SETTER
	void			setPyModule( boost::python::object PyModule );
	void			setInstance( boost::python::object instance );

	// GETTER
	std::string		getPath( void ) const;
	std::string		getName( void ) const;
	std::string		getVersion( void ) const;
	std::string		getAuthor( void ) const;

private:
	std::string		_path;
	boost::python::object	_PyModule;
	boost::python::object	_instance;

	std::string		_name;
	std::string		_version;
	std::string		_author;

	static const std::string	TAG;
};

#endif // ! _MODULE_H_
