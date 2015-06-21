#version 330 core

layout( location = 0 ) in vec3	positon;
layout( location = 1 ) in vec3	normal;
layout( location = 2 ) in vec4	color;

out vec3		vertexPos;
out vec3		vertexNormal;
out vec4		vertexColor;

uniform mat4	model;
uniform mat4	view;
uniform mat4	projection;

void main()
{
	gl_Position = projection * view * model * vec4( positon, 1 );
	vertexPos = vec3( model * vec4( positon, 1 ) );
	vertexNormal = normal;
	vertexColor = color;
}
