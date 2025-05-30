#shader vertex
#version 330 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoords;

out vec3 v_FragPosition;
out vec3 v_Normal;
out vec2 v_TexCoords;

uniform mat4 u_Model;
uniform mat4 u_Projection;
uniform mat4 u_View;

void main()
{
	// Calculate per-fragment world-space coordinate and normals
	v_FragPosition = vec3(u_Model * a_Position);
	// Multiplying normal by normal matrix essential for non-uniform scale of object; note: calculating inverse matrices here is expensive, better to calculate on the CPU
	v_Normal = mat3(transpose(inverse(u_Model))) * a_Normal;

	v_TexCoords = a_TexCoords;
	gl_Position = u_Projection * u_View * u_Model * a_Position;

}

#shader fragment
#version 330 core

layout(location = 0) out vec4 FragColor;

in vec3 v_FragPosition;
in vec3 v_Normal;
in vec2 v_TexCoords;

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct DirLight
{
	vec3 direction;
	
	Light properties;
};

struct PointLight
{
	vec3 position;

	Light properties;

	float constant;
	float linear;
	float quadratic;
};

struct SpotLight
{
	vec3 position;
	vec3 direction;

	float innerCutOff;
	float outerCutOff;

	Light properties;

	float constant;
	float linear;
	float quadratic;
};

uniform Material u_Material;
uniform vec3 u_ViewPosition;

uniform DirLight u_DirLight;

#define NR_POINT_LIGHTS 4
uniform PointLight u_PointLights[NR_POINT_LIGHTS];

uniform SpotLight u_SpotLight;

// Ambient component
vec3 phongAmbient(Light properties)
{
	return properties.ambient * vec3(texture(u_Material.diffuse, v_TexCoords));
}

// Diffuse component
vec3 phongDiffuse(Light properties, vec3 lightDir, vec3 normal)
{
	float diff = max(dot(normal, lightDir), 0.0);
	return properties.diffuse * diff * vec3(texture(u_Material.diffuse, v_TexCoords));
}

// Specular component
vec3 phongSpecular(Light properties, vec3 lightDir, vec3 normal, vec3 viewDir)
{
	vec3 reflectDir = reflect(-lightDir, normal); // Negating lightDir to get direction of light source to frag
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess);
	return properties.specular * spec * vec3(texture(u_Material.specular, v_TexCoords));
}

vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);
	return phongAmbient(light.properties) + phongDiffuse(light.properties, lightDir, normal) + phongSpecular(light.properties, lightDir, normal, viewDir);
}

vec3 calcPointLight(PointLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - v_FragPosition);

	float distance = length(light.position - v_FragPosition);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	vec3 ambient = phongAmbient(light.properties) * attenuation;
	vec3 diffuse = phongDiffuse(light.properties, lightDir, normal) * attenuation;
	vec3 specular = phongSpecular(light.properties, lightDir, normal, viewDir) * attenuation;

	return ambient + diffuse + specular;
}

vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - v_FragPosition);

	float distance = length(light.position - v_FragPosition);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	float theta = dot(lightDir, normalize(-light.direction)); // Angle between the vector from the fragment to the light source and the direction the spotlight is aiming at. Note this is cosine values cos(0deg) = 1, cos(90deg) = 0
	float epsilon = light.innerCutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0); // Interpolate light intensity between inner and outer cutoff regions to smooth the spotlight edge

	vec3 ambient = phongAmbient(light.properties) * attenuation * intensity;
	vec3 diffuse = phongDiffuse(light.properties, lightDir, normal) * attenuation * intensity;
	vec3 specular = phongSpecular(light.properties, lightDir, normal, viewDir) * attenuation * intensity;
	
	return ambient + diffuse + specular;
}


void main()
{
	vec3 viewDir = normalize(u_ViewPosition - v_FragPosition);
	vec3 normal = normalize(v_Normal);

	vec3 output = vec3(0.0);

	output += calcDirLight(u_DirLight, normal, viewDir);

	for (int i = 0; i < NR_POINT_LIGHTS; i++)
		output += calcPointLight(u_PointLights[i], normal, viewDir);

	output += calcSpotLight(u_SpotLight, normal, viewDir);

	FragColor = vec4(output, 1.0);
}