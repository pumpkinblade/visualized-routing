#version 330 core
out vec4 fragColor;

uniform vec3 color;

void main()
{
	fragColor = vec4(color[0], color[1], color[2], 1.0f);
}