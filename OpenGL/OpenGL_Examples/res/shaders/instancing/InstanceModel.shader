#shader vertex
#version 330 core

layout(location = 0) in vec4 a_Position;
layout(location = 2) in vec2 a_TexCoords;
layout(location = 3) in mat4 a_InstanceMatrix; // The maximum verrtex attribute is equal to a vec4 so mat4 is actually 4 vec4s at locations 3, 4, 5, and 6

out vec2 v_TexCoords;

uniform mat4 u_Projection;
uniform mat4 u_View;

void main()
{
    v_TexCoords = a_TexCoords;
    gl_Position = u_Projection * u_View * a_InstanceMatrix * a_Position; 
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 FragColor;

in vec2 v_TexCoords;

uniform sampler2D texture_diffuse1;

void main()
{
	FragColor = texture(texture_diffuse1, v_TexCoords);
}