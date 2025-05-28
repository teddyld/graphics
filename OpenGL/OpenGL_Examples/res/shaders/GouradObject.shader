#shader vertex
#version 330 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec3 a_Normal;

out vec3 v_Result;

uniform mat4 u_Model;
uniform mat4 u_Projection;
uniform mat4 u_View;

uniform vec3 u_ObjectColor;
uniform vec3 u_LightColor;
uniform vec3 u_LightPosition;
uniform vec3 u_ViewPosition;
uniform float u_AmbientStrength;
uniform float u_SpecularStrength;
uniform int u_Shininess;

// Phong lighting model implemented in the vertex shader 
// Gourad shading; efficient, generally less vertices than fragments but not very realistic unless large amounts of vertices are used due to interpolation of lighting values
void main()
{
	// Calculate per-fragment world-space coordinate and normals
	vec3 v_FragPosition = vec3(u_Model * a_Position);
	// Multiplying normal by normal matrix essential for non-uniform scale of object; note: calculating inverse matrices here is expensive, better to calculate on the CPU
	vec3 v_Normal = mat3(transpose(inverse(u_Model))) * a_Normal;

	// Ambient component
	float ambientStrength = u_AmbientStrength;
	vec3 ambient = ambientStrength * u_LightColor;

	// Diffuse component
	vec3 norm = normalize(v_Normal);
	vec3 lightDir = normalize(u_LightPosition - v_FragPosition);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * u_LightColor;

	// Specular component
	float specularStrength = u_SpecularStrength;
	vec3 viewDir = normalize(u_ViewPosition - v_FragPosition);
	vec3 reflectDir = reflect(-lightDir, norm); // Negating lightDir to get direction of light source to frag
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Shininess);
	vec3 specular = specularStrength * spec * u_LightColor;

	v_Result = (ambient + diffuse + specular) * u_ObjectColor;

	gl_Position = u_Projection * u_View * u_Model * a_Position;

}

#shader fragment
#version 330 core

layout(location = 0) out vec4 FragColor;

in vec3 v_Result;

void main()
{
	FragColor = vec4(v_Result, 1.0);
}