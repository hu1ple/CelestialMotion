#version 460 core
in vec2 TexCoord;
out vec4 FragColor;
layout (binding = 0) uniform sampler2D samp;
void main()
	{
		FragColor = vec4(texture(samp, TexCoord));
	}