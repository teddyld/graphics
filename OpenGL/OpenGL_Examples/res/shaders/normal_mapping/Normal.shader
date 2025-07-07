#shader vertex
#version 330 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoords;
layout(location = 3) in vec3 a_Tangent;
layout(location = 4) in vec3 a_Bitangent;

out VS_OUT {
	vec3 FragPos;
	vec2 TexCoords;
	vec3 TangentLightPos;
	vec3 TangentViewPos;
	vec3 TangentFragPos;
} vs_out;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

uniform vec3 u_ViewPos;
uniform vec3 u_LightPos;

void main()
{
	vs_out.TexCoords = a_TexCoords;
	   
	vec3 T = normalize(vec3(u_Model * vec4(a_Tangent,   0.0)));
	vec3 B = normalize(vec3(u_Model * vec4(a_Bitangent, 0.0)));
	vec3 N = normalize(vec3(u_Model * vec4(a_Normal,    0.0)));
	mat3 TBN = transpose(mat3(T, B, N)); // Transpose: world-space -> tangent-space

	// Transform vectors from world-space to tangent-space saving us having to perform matrix multiplications in the fragment shader
	vs_out.TangentLightPos = TBN * u_LightPos;
	vs_out.TangentViewPos = TBN * u_ViewPos;
	vs_out.TangentFragPos = TBN * vec3(u_Model * a_Position);

	gl_Position = u_Projection * u_View * u_Model * a_Position;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 FragColor;

in VS_OUT {
	vec3 FragPos;
	vec2 TexCoords;
	vec3 TangentLightPos;
	vec3 TangentViewPos;
	vec3 TangentFragPos;
} fs_in;

struct Light
{
	vec3 diffuse;
	vec3 ambient;
	vec3 specular;
};

struct Material
{
	sampler2D diffuse;
	sampler2D normal;

	float shininess;
};

uniform Light u_Light;
uniform Material u_Material;

// Blinn-Phong lighting model
void main()
{
	// Ambient component
	vec3 ambient = u_Light.ambient * u_Light.diffuse;

	// Diffuse component
	// Obtain normal from normal map in range [0,1]
    vec3 normal = texture(u_Material.normal, fs_in.TexCoords).rgb;
    // Transform normal vector to range [-1,1]
    normal = normalize(normal * 2.0 - 1.0);

	vec3 lightDir = normalize(fs_in.TangentLightPos - fs_in.TangentFragPos);
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = diff * u_Light.diffuse;

	// Specular component
	vec3 viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
	vec3 halfwayDir = normalize(lightDir + viewDir);  
	float spec = pow(max(dot(normal, halfwayDir), 0.0), u_Material.shininess);
	vec3 specular = u_Light.specular * spec * u_Light.diffuse;

	vec3 result = (ambient + diffuse + specular) * vec3(texture(u_Material.diffuse, fs_in.TexCoords));
	FragColor = vec4(result, 1.0);
}