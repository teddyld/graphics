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
	sampler2D emission;
	float shininess;
};

struct Light 
{
	vec4 direction;
	vec3 position;
	float innerCutOff;
	float outerCutOff;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

uniform Material u_Material;
uniform Light u_Light;

uniform vec3 u_ViewPosition;

// Ambient component
vec3 phongAmbient()
{
	return u_Light.ambient * vec3(texture(u_Material.diffuse, v_TexCoords));
}

// Diffuse component
vec3 phongDiffuse(vec3 lightDir, vec3 norm)
{
	float diff = max(dot(norm, lightDir), 0.0);
	return u_Light.diffuse * diff * vec3(texture(u_Material.diffuse, v_TexCoords));
}

// Specular component
vec3 phongSpecular(vec3 lightDir, vec3 norm)
{
	vec3 viewDir = normalize(u_ViewPosition - v_FragPosition);
	vec3 reflectDir = reflect(-lightDir, norm); // Negating lightDir to get direction of light source to frag
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess);
	return u_Light.specular * spec * vec3(texture(u_Material.specular, v_TexCoords));
}

void main()
{
	float attenuation = 1.0;
	vec3 norm = normalize(v_Normal);
	vec3 lightDir = vec3(1.0);

	// Directional light
	if (u_Light.direction.w == 0.0)
		lightDir = normalize(-u_Light.direction.xyz);
	// Positional/Spot light
	else
	{
		lightDir = normalize(u_Light.position - v_FragPosition);
		float distance = length(u_Light.position - v_FragPosition);
		attenuation = 1.0 / (u_Light.constant + u_Light.linear * distance + u_Light.quadratic * (distance * distance));
	}

	vec3 ambient = phongAmbient() * attenuation;
	vec3 diffuse = phongDiffuse(lightDir, norm) * attenuation;
	vec3 specular = phongSpecular(lightDir, norm) * attenuation;	

	// Point light
	if (u_Light.direction.w == 2.0)	
	{
		float theta = dot(lightDir, normalize(-u_Light.direction.xyz)); // Angle between the vector from the fragment to the light source and the direction the spotlight is aiming at. Note this is cosine values cos(0deg) = 1, cos(90deg) = 0
		float epsilon = u_Light.innerCutOff - u_Light.outerCutOff;
		float intensity = clamp((theta - u_Light.outerCutOff) / epsilon, 0.0, 1.0); // Interpolate light intensity between inner and outer cutoff regions to smooth the spotlight edge

		diffuse *= intensity;
		specular *= intensity;
		FragColor = vec4(ambient + diffuse + specular, 1.0);
	}
	else
	{
		FragColor = vec4(ambient + diffuse + specular, 1.0);
	}

}