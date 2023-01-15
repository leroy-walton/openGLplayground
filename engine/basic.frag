#version 330 core

out vec4 FragColor;

in vec3 color;
in vec2 texCoord;
in vec3 normal;
in vec3 crntPos;

uniform sampler2D tex0;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

void main()
{
	float ambient = 0.16f;
	// // diffuse lighting
	vec3 nnormal = normalize(normal);
	vec3 lightDirection = normalize(lightPos - crntPos);
	float diffuse = max(dot(nnormal, lightDirection), 0.0f);

	// // specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, nnormal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
	float specular = specAmount * specularLight;

	// outputs final color
	FragColor = texture(tex0, texCoord) * lightColor * (diffuse + ambient + specular);
}

