#version 460 core

out vec4 FragColor;
in vec3 o_Color;
// Outputs the normal for the Fragment Shader
in vec3 Normal;
// Outputs the current position for the Fragment Shader
in vec3 crntPos;

uniform vec3 u_lightPos;

void main()
{
	// ambient lighting
	float ambient = 0.20f;
	vec3 lightPos = u_lightPos;
	vec4 lightCol = vec4(1.0);

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - crntPos);
	float diffuse = max(dot(normal, lightDirection), 0.0);


	FragColor = vec4(o_Color, 1.0) * lightCol * diffuse;
}