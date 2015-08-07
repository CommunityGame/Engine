#include "MeshBuilder.hpp"

const std::string	MeshBuilder::TAG = "MeshBuilder";
std::map<std::string, shared_ptr<Mesh>>	MeshBuilder::_loadedMesh;

shared_ptr<Mesh> MeshBuilder::loadFromObj( const std::string & file )
{
	std::map<std::string, shared_ptr<Mesh>>::const_iterator it;

	it = MeshBuilder::_loadedMesh.find( file );
	if ( it != MeshBuilder::_loadedMesh.end() )
	{
		Logger::w( TAG, "Reuse an already load mesh :" + file );
		return ( (*it).second );
	}

	bool					flat = true;
	GLuint					i = 0;

	int						lineNb = 0;
	std::vector<Vertexf>	vertexTmp;
	std::vector<Vertexf>	vertex;
	std::vector<GLuint>		indices;

	std::ifstream			inf( file );

	if ( ! inf.is_open() )
	{
		Logger::e( TAG, "Can't open: " + file );
		return ( nullptr );
	}

	while ( inf.good() )
	{
		std::string line;
		std::getline( inf, line );

		lineNb++;
		if ( line.size() <= 1 || line[0] == '#' )
			continue ;

		if ( line[0] == 'v' && line[1] == ' ' )
		{
			Vec3f	v;
			if ( std::sscanf( line.c_str(), "v %f %f %f", &v[0], &v[1], &v[2] ) != 3 )
				Logger::w( TAG, "Missing value line: (" + std::to_string( lineNb ) + ") " + line );
			if ( flat )
				vertexTmp.push_back( Vertexf( v, Colorf( 0.6f, 0.9f, 0.2f, 1 ) ) );
			else
				vertex.push_back( Vertexf( v ) );
		}
		if ( line[0] == 'f' )
		{
			GLuint	index[4];
			int		nbIndex;
			if ( ( nbIndex = std::sscanf( line.c_str(), "f %d %d %d %d", &index[0], &index[1], &index[2], &index[3] ) ) < 3 )
				Logger::w( TAG, "Missing value line: (" + std::to_string( lineNb ) + ") " + line );
			if ( ! flat )
			{
				indices.push_back( index[0] - 1 );
				indices.push_back( index[1] - 1 );
				indices.push_back( index[2] - 1 );
				if ( nbIndex > 3 )
				{
					indices.push_back( index[2] - 1 );
					indices.push_back( index[3] - 1 );
					indices.push_back( index[0] - 1 );
				}
			}
			else
			{
				vertex.push_back( vertexTmp[index[0] - 1] );
				vertex.push_back( vertexTmp[index[1] - 1] );
				vertex.push_back( vertexTmp[index[2] - 1] );
				indices.push_back( i++ );
				indices.push_back( i++ );
				indices.push_back( i++ );
				if ( nbIndex > 3 )
				{
					vertex.push_back( vertexTmp[index[2] - 1] );
					vertex.push_back( vertexTmp[index[3] - 1] );
					vertex.push_back( vertexTmp[index[0] - 1] );
					indices.push_back( i++ );
					indices.push_back( i++ );
					indices.push_back( i++ );
				}
			}
		}
	}
	shared_ptr<Mesh>	res( new Mesh( vertex, indices ) );
	res->calcNormal();
	res->bufferData();

	MeshBuilder::_loadedMesh.insert( std::pair<std::string, shared_ptr<Mesh>>( file, res ) );
	return ( res );
}
