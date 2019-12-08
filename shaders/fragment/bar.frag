#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
	FragColor = vec4(0.176f, 0.477f, 0.875f, 1.0f) * texture(ourTexture, TexCoord);
}
