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

// Blinn-Phong lighting model
void main()
{
	// Ambient component
	vec3 ambient = u_Light.ambient * u_Light.diffuse;

	// Diffuse component
	vec3 norm = normalize(v_Normal);
	vec3 lightDir = normalize(u_Light.position - v_FragPosition);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * u_Light.diffuse;

	// Specular component (uses angle between normal and halfway vector instead of view and reflection vector)
	// Note: since the angle between the halfway vector and surface normal is often shorter, we need to set the specular shininess exponent higher to get similar results as Phong shading by 2-4 times
	vec3 viewDir = normalize(u_ViewPosition - v_FragPosition);
	vec3 halfwayDir = normalize(lightDir + viewDir);  
	float spec = pow(max(dot(norm, halfwayDir), 0.0), u_Material.shininess);
	vec3 specular = u_Light.specular * spec * u_Light.diffuse;

	vec3 result = (ambient + diffuse + specular) * vec3(texture(u_Material.diffuse, v_TexCoords));
	FragColor = vec4(result, 1.0);
}