#shader vertex
#version 330 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoords;

out vec3 v_Result;
out vec2 v_TexCoords;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

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
	float shininess; // Impacts the scattering/radius of the specular highlight
};

uniform Light u_Light;
uniform Material u_Material;

// Phong lighting model implemented in the vertex shader 
// Gourad shading; efficient, generally less vertices than fragments but not very realistic unless large amounts of vertices are used due to interpolation of lighting values
void main()
{
	// Calculate per-fragment world-space coordinate and normals
	vec3 v_FragPosition = vec3(u_Model * a_Position);
	// Multiplying normal by normal matrix essential for non-uniform scale of object; note: calculating inverse matrices here is expensive, better to calculate on the CPU
	vec3 v_Normal = mat3(transpose(inverse(u_Model))) * a_Normal;

	// Ambient component
	vec3 ambient =  u_Light.ambient * u_Light.diffuse;

	// Diffuse component
	vec3 norm = normalize(v_Normal);
	vec3 lightDir = normalize(u_Light.position - v_FragPosition);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * u_Light.diffuse;

	// Specular component
	vec3 viewDir = normalize(u_ViewPosition - v_FragPosition);
	vec3 reflectDir = reflect(-lightDir, norm); // Negating lightDir to get direction of light source to frag
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess);
	vec3 specular = u_Light.specular * spec * u_Light.diffuse;

	v_Result = ambient + diffuse + specular;
	v_TexCoords = a_TexCoords;

	gl_Position = u_Projection * u_View * u_Model * a_Position;

}

#shader fragment
#version 330 core

layout(location = 0) out vec4 FragColor;

in vec3 v_Result;
in vec2 v_TexCoords;

struct Material
{
	sampler2D diffuse;
	float shininess; // Impacts the scattering/radius of the specular highlight
};

uniform Material u_Material;

void main()
{
	vec3 result = v_Result * vec3(texture(u_Material.diffuse, v_TexCoords));
	FragColor = vec4(result, 1.0);
}