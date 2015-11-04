#ifndef _ASSET_HPP_
# define _ASSET_HPP_

# include <string>
# include <boost/shared_ptr.hpp>
# include "IAsset.hpp"

using namespace boost;

template <typename T, typename = typename std::enable_if<std::is_base_of<IAsset, T>::value, T>::type>
class Asset
{
public:
	Asset( void ) :
		_uidName( "" ),
		_id( -1 )
	{
		return ;
	}

	Asset( shared_ptr<T> ptr, std::string const & uidName ) :
		_ptr( ptr ),
		_uidName( uidName ),
		_id( Asset::_identifier++ )
	{
		return ;
	}

	Asset<T> &		operator=( Asset<T> const & rhs )
	{
		if ( this != &rhs )
		{
			this->_id = rhs.getUid();
			this->_uidName = rhs.getUidName();
			this->_ptr = rhs.getPtr();
		}
		return ( *this );
	}

	shared_ptr<T>	operator->( void ) const
	{
		return ( this->_ptr );
	}

	int				getUid( void ) const
	{
		return ( this->_id );
	}

	std::string		getUidName( void ) const
	{
		return ( this->_uidName );
	}

	shared_ptr<T>	getPtr( void ) const
	{
		return ( this->_ptr );
	}

private:
	int				_id;
	std::string		_uidName;
	shared_ptr<T>	_ptr;

	static int		_identifier;
};

template <typename T, typename U>
int		Asset<T, U>::_identifier = 0;

#endif // ! _ASSET_HPP_
