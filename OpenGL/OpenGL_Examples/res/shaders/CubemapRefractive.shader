#shader vertex
#version 330 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec3 a_Normal;

out vec4 v_Position;
out vec3 v_Normal;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
    v_Position = u_Model * a_Position;
    v_Normal = mat3(transpose(inverse(u_Model))) * a_Normal;

	gl_Position = u_Projection * u_View * u_Model * a_Position;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 FragColor;

in vec4 v_Position;
in vec3 v_Normal;

uniform vec3 u_CameraPos;
uniform samplerCube u_Skybox;
uniform float u_RefractiveIndex;

void main()
{
    // Note: This is single sided refraction
    vec3 I = normalize(vec3(v_Position) - u_CameraPos); // View direction vector
    vec3 R = refract(I, normalize(v_Normal), u_RefractiveIndex); // Refraction vector
    FragColor = texture(u_Skybox, R);
}