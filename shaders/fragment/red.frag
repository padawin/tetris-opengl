#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform float currentTime;

void main()
{
	float red = sin(currentTime) / 2.0f + 0.5f;
    FragColor = vec4(red, 0.0f, 0.0f, 1.0f);
}
