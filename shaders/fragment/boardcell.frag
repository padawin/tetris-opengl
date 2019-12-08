#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
	vec2 coord = vec2(-TexCoord.x, TexCoord.y);
	FragColor = vec4(0.502f, 0.742f, 0.86f, 1.0f) * texture(ourTexture, coord);
}
