#version 330 core

struct			light
{
	vec3		position;
	vec3		ambient;
	vec3		diffuse;
	vec3		specular;
	float		shininess;
};

struct			material
{
	vec4		ambiant;
};

in vec3			vertexPos;
in vec3			vertexNormal;
in vec4			vertexColor;
in mat4			normalMatrix;

out vec4		color;

uniform	int		numLights;
uniform	vec3	eyePos;
uniform	light	lights[64];

void main()
{
	vec4 sceneColor = vec4( 0, 0, 0, 1 );
	vec4 matAmbient = vertexColor;
	vec4 matDiffuse = vertexColor;
	vec4 matSpecular = vertexColor;
	float matShininess = 1;

//	vec3 N = normalize( ( normalMatrix * vec4 (vertexNormal, 1 ) ).xyz );
	vec3 N = vertexNormal;

	vec4 final_color = vec4( 0, 0, 0, 1 );

	for ( int i = 0; i < numLights; i++ )
	{
//	vec3 diffuse;
//    vec3 spec;
//    vec3 ambient;
//
//       vec3 L = normalize(lights[i].position.xyz - vertexPos);
//       vec3 E = normalize(eyePos-vertexPos);
//       vec3 R = normalize(reflect(-L,N));
//
//       	ambient = lights[i].ambient;
//
//      	diffuse = clamp( lights[i].diffuse * max(dot(N,L), 0.0)  , 0.0, 1.0 ) ;
//       	spec = clamp ( lights[i].specular * pow(max(dot(R,E),0.0),0.3*20) , 0.0, 1.0 );
//
//		final_color += vec4( ambient + diffuse + spec , 1 );
		final_color += sceneColor * matAmbient + vec4( lights[i].ambient, 1 ) * matAmbient;

		vec3 L = normalize( lights[i].position - vertexPos );

		float lambertTerm = dot( N, L );

		if ( lambertTerm > 0.0 )
		{
			final_color += clamp( vec4( lights[i].diffuse, 1 ) * matDiffuse * lambertTerm, 0.0, 1.0 );

			vec3 E = normalize( eyePos - vertexPos );
			vec3 R = reflect( -L, N );
			float specular = pow( max( dot( R, E ), 0.0 ), matShininess * lights[i].shininess );
			final_color += vec4( lights[i].specular, 1 ) * matSpecular * specular;
		}
	}
	color = final_color;
}
