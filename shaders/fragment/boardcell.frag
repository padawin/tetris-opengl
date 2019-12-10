#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Color;

uniform sampler2D ourTexture;

void main()
{
	vec2 coord = vec2(-TexCoord.x, -TexCoord.y);
	FragColor = texture(ourTexture, coord) * vec4(Color, 1.0);
}
