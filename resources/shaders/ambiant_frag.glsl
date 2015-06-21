#version 330 core

in vec4			vertexColor;

uniform vec3	ambiantColor;

out vec4		color;

void main()
{
	color = vec4( ambiantColor, 1 ) * vertexColor;
}
