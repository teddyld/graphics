#shader vertex
#version 330 core

layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec3 a_Color;
layout(location = 2) in vec2 a_Offset; // Using an instanced array

out vec3 f_Color;

void main()
{
	vec2 pos = a_Position * (gl_InstanceID / 100.0);
	f_Color = a_Color;
	gl_Position = vec4(pos + a_Offset, 0.0, 1.0);
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 FragColor;

in vec3 f_Color;

void main()
{
	FragColor = vec4(f_Color, 1.0);
}