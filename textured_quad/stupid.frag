#version 330 core

uniform sampler2D tex0;
uniform float time;
in vec3 color;
in vec2 texCoord;

out vec4 FragColor;

void main()
{
	FragColor = texture(tex0, texCoord);
	//FragColor = vec4(sin(time*0.83), sin(time*2.21+1), sin(time+2.1415), 1.0);
}