#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 texCoords;

uniform mat4 projection;

void main()
{
	gl_Position = projection * vec4(aPos, 0.0f, 1.0f);
	texCoords = aTexCoords;
}