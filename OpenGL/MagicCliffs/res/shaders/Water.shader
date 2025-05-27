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

layout(location = 0) out vec4 FragColor;

in vec2 v_TexCoord;

uniform float u_Strength;
uniform vec2 u_Offset; 
uniform sampler2D u_Texture;
uniform sampler2D u_Normal;

void main()
{
	// Reflect the texture coordinates on the y-axis
	vec2 reflectionUV = vec2(v_TexCoord.x, 1.0 - v_TexCoord.y);

	// Apply normal texture and offset by u_Offset; fract() to keep the normal in view
	vec4 waterColor = texture(u_Normal, fract(reflectionUV + u_Offset));
	
	// Apply reflected texture modified by normal UV, adjusted by u_Strength
	waterColor = texture(u_Texture, reflectionUV + (waterColor.rg * u_Strength));

	FragColor = waterColor;
};