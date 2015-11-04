
struct			Light
{
	vec3		position;
	float		shininess;
	vec3		ambient;
	float		radius;
	vec3		diffuse;
	float		cutoff;
	vec3		specular;
};

struct			Material
{
	vec4		ambiant;
};