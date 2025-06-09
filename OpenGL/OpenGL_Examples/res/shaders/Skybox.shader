#shader vertex
#version 330 core

layout(location = 0) in vec4 a_Position;

out vec3 v_TexCoords;

uniform mat4 u_MVP;

void main()
{
    v_TexCoords = vec3(a_Position); // Use local positions as texture coordinates. A cube centered at the origin (0, 0, 0) has each of its position vectors also a direction vector from the origin
	gl_Position = (u_MVP * a_Position).xyww; // Set z == w == 1.0, skybox should always have maximum depth value so that it fails if an object is in front of it
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 FragColor;

in vec3 v_TexCoords;

uniform samplerCube u_Skybox;

void main()
{             
    FragColor = texture(u_Skybox, v_TexCoords);
}