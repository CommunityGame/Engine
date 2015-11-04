#version 330 core
#include structs.glsl

in vec3			vertexPos;
in vec3			vertexNormal;
in vec4			vertexColor;
in mat4			normalMatrix;

out vec4		color;

uniform	vec3	C_eyePos;
uniform int		C_numLights;
uniform	Light	C_lights[64];

const float		C_screenGamma = 1;

vec4	gammaCorrection( vec4 color )
{
	return ( pow( color, vec4( 1.0 / C_screenGamma ) ) );
}

vec4	attenuationCorrection( Light light, vec4 color )
{
	float d = length( light.position - vertexPos ) - light.radius;
	float denom = d / light.radius + 1;
	float attenuation = 1 / ( denom * denom );
	// scale and bias attenuation such that:
	//   attenuation == 0 at extent of max influence
	//   attenuation == 1 when d == 0
	attenuation = ( attenuation - light.cutoff ) / ( 1 - light.cutoff );
	attenuation = max( attenuation, 0 );

	color.x *= attenuation;
	color.y *= attenuation;
	color.z *= attenuation;
	return ( color );
}

vec4	lightColor( Light light, vec3 vertexNormal )
{
	vec3 lightDir = normalize( light.position - vertexPos );

	float lambertian = max( dot( lightDir, vertexNormal ), 0.0 );
	float specular = 0.0;

	if ( lambertian > 0.0 )
	{
		vec3 viewDir = normalize( C_eyePos - vertexPos );

		// this is blinn phong
		vec3 halfDir = normalize( lightDir + viewDir );
		float specAngle = max( dot( halfDir, vertexNormal ), 0.0 );
		specular = pow( specAngle, 1 / light.shininess );
	}
	vec4 colorLinear = vec4( light.ambient, 1 );
//	colorLinear += lambertian * vec4( light.diffuse, 1 );
	colorLinear += specular * vec4( light.specular, 1 );

	// apply gamma correction (assume ambientColor, diffuseColor and specColor
	// have been linearized, i.e. have no gamma correction in them)
	vec4 colorGammaCorrected = gammaCorrection( colorLinear );

	vec4 attenuationCorrected = attenuationCorrection( light, colorGammaCorrected );

	return ( attenuationCorrected );
}

void	main()
{
	vec4 sceneColor = vec4( 0, 0, 0, 1 );
	vec4 matAmbient = vertexColor;
	vec4 matDiffuse = vertexColor;
	vec4 matSpecular = vertexColor;
	float matShininess = 1;

	vec3 normal = normalize( vertexNormal );

	color = vec4( 0, 0, 0, 0 );
	for ( int i = 0; i < C_numLights; i++ )
	{
		color += lightColor( C_lights[i], normal );
	}
}
