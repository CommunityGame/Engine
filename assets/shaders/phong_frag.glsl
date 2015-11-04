#version 330 core
//TODO: #inlude <> ""
#include structs.glsl

in vec3			vertexPos;
in vec3			vertexNormal;
in vec4			vertexColor;
in mat4			normalMatrix;

out vec4		color;

uniform	int		numLights;
uniform	vec3	eyePos;
uniform	Light	lights[64];

const float screenGamma = 1;

void main()
{
	vec4 sceneColor = vec4( 0, 0, 0, 1 );
	vec4 matAmbient = vertexColor;
	vec4 matDiffuse = vertexColor;
	vec4 matSpecular = vertexColor;
	float matShininess = 1;

	vec4 finalColor = vec4( 0, 0, 0, 0 );
	for ( int i = 0; i < numLights; i++ )
	{
		Light l = lights[i];

		vec3 normal = normalize(vertexNormal);
		vec3 lightDir = normalize(l.position - vertexPos);

		float lambertian = max(dot(lightDir,normal), 0.0) * l.shininess;
		float specular = 0.0;

		if(lambertian > 0.0)
		{
			vec3 viewDir = normalize(eyePos-vertexPos);

			// this is blinn phong
			vec3 halfDir = normalize(lightDir + viewDir);
			float specAngle = max(dot(halfDir, normal), 0.0);
			specular = pow(specAngle, 1 / l.shininess);
		}
		vec3 colorLinear = l.ambient * l.shininess + lambertian * l.diffuse + specular * l.specular;
		// apply gamma correction (assume ambientColor, diffuseColor and specColor
		// have been linearized, i.e. have no gamma correction in them)
		vec3 colorGammaCorrected = pow(colorLinear, vec3(1.0/screenGamma));

		float d = length( l.position - vertexPos ) - l.radius;
		float denom = d / l.radius + 1;
		float attenuation = 1 / (denom*denom);
		// scale and bias attenuation such that:
		//   attenuation == 0 at extent of max influence
		//   attenuation == 1 when d == 0
		attenuation = (attenuation - l.cutoff) / (1 - l.cutoff);
		attenuation = max(attenuation, 0);

		// use the gamma corrected color in the fragment
		finalColor += vec4(colorGammaCorrected, 1.0) * attenuation;
	}
	color = finalColor;
}
