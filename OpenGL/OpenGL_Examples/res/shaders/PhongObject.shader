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

uniform vec3 u_LightColor;
uniform vec3 u_LightPosition;
uniform vec3 u_ViewPosition;
uniform float u_AmbientStrength;
uniform float u_SpecularStrength;
uniform int u_Shininess;
uniform sampler2D u_Texture;

// Phong lighting model
void main()
{
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

	vec3 result = (ambient + diffuse + specular) * vec3(texture(u_Texture, v_TexCoords));
	FragColor = vec4(result, 1.0);
}