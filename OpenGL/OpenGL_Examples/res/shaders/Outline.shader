#shader vertex
#version 330 core

layout(location = 0) in vec4 a_Position;

out vec2 v_TexCoords;

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * a_Position;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 FragColor;

void main()
{
	FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}