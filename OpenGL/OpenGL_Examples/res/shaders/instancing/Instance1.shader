#shader vertex
#version 450 core

layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec3 a_Color;

out vec3 f_Color;

uniform vec2 offsets[100]; // May hit the uniform limit if we are rendering more than 100 instances

void main()
{
	f_Color = a_Color;
	vec2 offset = offsets[gl_InstanceID];
	gl_Position = vec4(a_Position + offset, 0.0, 1.0);
}

#shader fragment
#version 450 core

layout(location = 0) out vec4 FragColor;

in vec3 f_Color;

void main()
{
	FragColor = vec4(f_Color, 1.0);
}