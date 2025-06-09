#shader vertex
#version 330 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec2 a_TexCoords;

out vec2 v_TexCoords;

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * a_Position;
	v_TexCoords = a_TexCoords;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 FragColor;

in vec2 v_TexCoords;	

uniform sampler2D u_Texture;

void main()
{
	FragColor = texture(u_Texture, v_TexCoords);
};