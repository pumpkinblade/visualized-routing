#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 instancedColor;
layout (location = 2) in mat4 instancedModel;

out vec3 color;

uniform mat4 projection;

void main()
{
	gl_Position = projection * instancedModel * vec4(aPos, 0.0f, 1.0f);
	color = instancedColor;
}