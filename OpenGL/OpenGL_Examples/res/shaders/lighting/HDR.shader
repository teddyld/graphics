#shader vertex
#version 330 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec2 a_TexCoords;

out vec2 v_TexCoords;

void main()
{
	v_TexCoords = a_TexCoords;
	gl_Position = a_Position;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 FragColor;

in vec2 v_TexCoords;

uniform sampler2D u_HDRBuffer;
uniform bool u_HDR;
uniform float u_Exposure;

void main()
{
	const float gamma = 2.2;
	vec3 hdrColor = texture(u_HDRBuffer, v_TexCoords).rgb;

	vec3 result = vec3(1.0);
	if (u_HDR)
	{
		// Exposure tone mapping + gamma correction
		result = vec3(1.0) - exp(-hdrColor * u_Exposure);
		result = pow(result, vec3(1.0 / gamma));
	}
	else
	{
		result = pow(hdrColor, vec3(1.0 / gamma));
	}
	FragColor = vec4(result, 1.0);
}