#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
	FragColor = vec4(0.915f, 0.866f, 0.209f, 1.0f) * texture(ourTexture, TexCoord);
}
