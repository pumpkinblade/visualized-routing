#version 330 core
out vec4 fragColor;

in vec2 texCoords;

uniform sampler2D tex;
uniform vec3 color;

void main()
{
	fragColor = vec4(1.0f, 1.0f, 1.0f, texture(tex, texCoords).r) * vec4(color, 1.0f);
}