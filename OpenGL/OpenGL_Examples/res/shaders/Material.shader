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
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Material u_Material;
uniform Light u_Light;

uniform vec3 u_ViewPosition;
uniform float u_Time;

// Phong lighting model
void main()
{
	// Ambient component
	vec3 ambient = u_Light.ambient * vec3(texture(u_Material.diffuse, v_TexCoords));

	// Diffuse component
	vec3 norm = normalize(v_Normal);
	vec3 lightDir = normalize(u_Light.position - v_FragPosition);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = u_Light.diffuse * diff * vec3(texture(u_Material.diffuse, v_TexCoords));

	// Specular component
	vec3 viewDir = normalize(u_ViewPosition - v_FragPosition);
	vec3 reflectDir = reflect(-lightDir, norm); // Negating lightDir to get direction of light source to frag
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess);
	vec3 specular = u_Light.specular * spec * vec3(texture(u_Material.specular, v_TexCoords));

	// Emission component
	vec3 emission = vec3(0.0);
	// Restrict emmisive texture to non-specular wood component
	if (vec3(texture(u_Material.specular, v_TexCoords)).r == 0.0)
	{
		// Scale by time in the y-direction
		emission = vec3(texture(u_Material.emission, fract(v_TexCoords + vec2(0.0, u_Time))));
	}

	FragColor = vec4(ambient + diffuse + specular + emission, 1.0);
}