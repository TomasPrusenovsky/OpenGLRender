#version 460 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 aCol;
layout (location = 2) in vec3 aNorm;

uniform mat4 u_proj;
uniform mat4 u_view;
uniform mat4 u_model;

out vec3 o_Color;

// Outputs the normal for the Fragment Shader
out vec3 Normal;
// Outputs the current position for the Fragment Shader
out vec3 crntPos;

void main()
{
	o_Color = aCol;
	crntPos = (u_view * u_model * vec4(pos, 1.0)).xyz;
	Normal =  (u_model * vec4(aNorm, 1.0)).xyz;

	gl_Position = u_proj * u_view * u_model * vec4(pos, 1.0);
}