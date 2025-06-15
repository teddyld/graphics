#shader vertex
#version 450 core

layout(location = 0) in vec4 a_Position;
layout (std140) uniform Matrices
{
    mat4 u_Projection;
    mat4 u_View;
};
uniform mat4 u_Model;

void main()
{
	gl_Position = u_Projection * u_View * u_Model * a_Position;
}

#shader fragment
#version 450 core

layout(location = 0) out vec4 FragColor;

void main()
{
    FragColor = vec4(0.0, 0.0, 1.0, 1.0);
}