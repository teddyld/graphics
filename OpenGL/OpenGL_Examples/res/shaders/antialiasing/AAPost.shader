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

uniform sampler2D u_ScreenTexture;

void main()
{
    vec3 col = texture(u_ScreenTexture, v_TexCoords).rgb;
    float grayscale = 0.2126 * col.r + 0.7152 * col.g + 0.0722 * col.b;
    FragColor = vec4(vec3(grayscale), 1.0);
}