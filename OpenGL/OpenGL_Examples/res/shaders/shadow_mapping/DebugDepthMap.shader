#shader vertex
#version 450 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec2 a_TexCoords;

out vec2 v_TexCoords;

void main()
{
    v_TexCoords = a_TexCoords;
    gl_Position = a_Position;
}

#shader fragment
#version 450 core

layout(location = 0) out vec4 FragColor;

in vec2 v_TexCoords;

uniform sampler2D u_DepthMap;
uniform float u_Near;
uniform float u_Far;

// Required when using a perspective projection matrix
float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // Back to NDC 
    return (2.0 * u_Near * u_Far) / (u_Far + u_Near - z * (u_Far - u_Near));	
}

void main()
{             
    float depthValue = texture(u_DepthMap, v_TexCoords).r;
    //FragColor = vec4(vec3(LinearizeDepth(depthValue) / u_Far), 1.0); // perspective
    FragColor = vec4(vec3(depthValue), 1.0); // orthographic
}