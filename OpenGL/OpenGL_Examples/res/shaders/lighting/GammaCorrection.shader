#shader vertex
#version 450 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoords;

out vec3 v_FragPosition;
out vec3 v_Normal;
out vec2 v_TexCoords;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
	v_FragPosition = vec3(u_Model * a_Position);
	v_Normal = mat3(transpose(inverse(u_Model))) * a_Normal;
	v_TexCoords = a_TexCoords;
	gl_Position = u_Projection * u_View * u_Model * a_Position;
}

#shader fragment
#version 450 core

layout(location = 0) out vec4 FragColor;

in vec3 v_FragPosition;
in vec3 v_Normal;
in vec2 v_TexCoords;

uniform vec3 u_ViewPosition;

struct Light
{
	vec3 position;

	vec3 diffuse;
	vec3 ambient;
	vec3 specular;
};

struct Material
{
	sampler2D diffuse;
	float shininess;
};

#define NR_LIGHTS 4
uniform Light u_Lights[NR_LIGHTS];
uniform Material u_Material;

uniform float u_Gamma;
uniform bool u_GammaCorrection;
uniform bool u_Attenuation;

vec3 calcBlinnPhong(Light light, vec3 norm, vec3 viewDir)
{
	// Ambient component
	vec3 ambient = light.ambient * light.diffuse;

	// Diffuse component
	vec3 lightDir = normalize(light.position - v_FragPosition);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * light.diffuse;

	// Specular component
	vec3 halfwayDir = normalize(lightDir + viewDir);  
	float spec = pow(max(dot(norm, halfwayDir), 0.0), u_Material.shininess);
	vec3 specular = light.specular * spec * light.diffuse;

	if (u_Attenuation)
	{
		float distance = length(light.position - v_FragPosition);
		float attenuation = 1.0 / (u_GammaCorrection ? distance * distance : distance);
		diffuse *= attenuation;
		specular *= attenuation;
	}

	return ambient + diffuse + specular;
}

void main()
{
	vec3 color = texture(u_Material.diffuse, v_TexCoords).rgb;
	vec3 lighting = vec3(0.0);
	vec3 norm = normalize(v_Normal);
	vec3 viewDir = normalize(u_ViewPosition - v_FragPosition);

	for (int i = 0; i < NR_LIGHTS; i++)
		lighting += calcBlinnPhong(u_Lights[i], norm, viewDir);

	color *= lighting;

	if (u_GammaCorrection)
		FragColor = vec4(pow(color, vec3(1.0 / u_Gamma)), 1.0);
	else
		FragColor = vec4(color, 1.0);
}