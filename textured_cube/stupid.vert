#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;

out vec3 color;
out vec2 texCoord;

uniform mat4 proj;
uniform mat4 model;
uniform float time;

void main()
{
	vec4 newPos = vec4(aPos.x , aPos.y , aPos.z , 1.0);
	gl_Position = proj * model * newPos;
	color = aColor;
	texCoord = aTex;
}