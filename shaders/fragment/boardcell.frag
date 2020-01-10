#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform vec4 color;

void main()
{
	vec2 coord = vec2(-TexCoord.x, -TexCoord.y);
	FragColor = texture(ourTexture, coord) * color;
}
