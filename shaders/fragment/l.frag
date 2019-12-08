#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
	FragColor = vec4(0.1f, 0.66f, 0.71f, 1.0f) * texture(ourTexture, TexCoord);
}
