#shader vertex
#version 450 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec2 a_TexCoord;

out vec4 v_Color;
out vec2 v_TexCoord;

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * a_Position;
	v_TexCoord = a_TexCoord;
};

#shader fragment
#version 450 core

layout(location = 0) out vec4 o_Color;

in vec2 v_TexCoord;

uniform sampler2D u_Texture;

void main()
{
	o_Color = texture(u_Texture, v_TexCoord);
};