#ifndef _SCALABLE_VECTOR_GRAPHICS_HPP_
# define _SCALABLE_VECTOR_GRAPHICS_HPP_

#include <vector>
#include "SVGPath.hpp"
#include "../../components/basic/RenderComponent.hpp"

class ScalableVectorGraphics : public RenderComponent
{
public:
	ScalableVectorGraphics( std::string const & file );

	void				parseNode( rapidxml::xml_node<> * node, SVGAttributes g = SVGAttributes::NO_ATTRIBUTES );

	virtual void		render( RenderEngine const & renderEngine, GameObject const & parent, Shader const & shader, Camera const & camera ) const;

	// SETTER
	static void			setStrokePaint( VGPaint paint );
	static void			setFillPaint( VGPaint paint );

	// GETTER
	static VGPaint		getStrokePaint( void );
	static VGPaint		getFillPaint( void );

private:
	std::vector<shared_ptr<SVGPath>>	_paths;

	static VGPaint						_strokePaint;
	static VGPaint						_fillPaint;
};

#endif // ! _SCALABLE_VECTOR_GRAPHICS_HPP_
