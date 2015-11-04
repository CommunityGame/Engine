#version 330 core

in vec4			vertexColor;

uniform vec3	ambientColor;

out vec4		color;

void main()
{
	color = vec4( ambientColor, 1 ) * vertexColor;
}
