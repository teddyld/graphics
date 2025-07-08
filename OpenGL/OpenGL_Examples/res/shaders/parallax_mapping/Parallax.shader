#shader vertex
#version 330 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoords;
layout(location = 3) in vec3 a_Tangent;
layout(location = 4) in vec3 a_Bitangent;

out VS_OUT {
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
	mat3 TBN = transpose(mat3(T, B, N));

	vs_out.TangentLightPos = TBN * u_LightPos;
	vs_out.TangentViewPos = TBN * u_ViewPos;
	vs_out.TangentFragPos = TBN * vec3(u_Model * a_Position);

	gl_Position = u_Projection * u_View * u_Model * a_Position;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 FragColor;

in VS_OUT {
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
	sampler2D depth;

	float shininess;
};

uniform Light u_Light;
uniform Material u_Material;
uniform float u_HeightScale;

vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir)
{ 
    float height =  texture(u_Material.depth, texCoords).r;    
	// Dividing by viewDir.z: when viewDir is parallel to the surface, z is close to 0.0, returning a larger P vector compared to when the viewDir is perpendicular to the surface
	// The size of P offsets the texture coordinates at a larger scale when looking at the surface from an angle, providing more realism at angles
    vec2 p = viewDir.xy / viewDir.z * (height * u_HeightScale); 
    return texCoords - p;    
} 

void main()
{
	// Offset texture coordinates with parallax mapping
	vec3 viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
    vec2 texCoords = ParallaxMapping(fs_in.TexCoords, viewDir);
	// Discard border artifacts due to oversampling outside the range [0, 1]
	if (texCoords.x > 1.0 || texCoords.y > 1.0 || texCoords.x < 0.0 || texCoords.y < 0.0)
		discard;

	vec3 materialDiffuse = texture(u_Material.diffuse, texCoords).rgb;
    vec3 normal = texture(u_Material.normal, texCoords).rgb;
    normal = normalize(normal * 2.0 - 1.0);

	// Ambient component
	vec3 ambient = u_Light.ambient * u_Light.diffuse;

	// Diffuse component
	vec3 lightDir = normalize(fs_in.TangentLightPos - fs_in.TangentFragPos);
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = diff * u_Light.diffuse;

	// Specular component
	vec3 halfwayDir = normalize(lightDir + viewDir);  
	float spec = pow(max(dot(normal, halfwayDir), 0.0), u_Material.shininess);
	vec3 specular = u_Light.specular * spec * u_Light.diffuse;

	vec3 result = (ambient + diffuse + specular) * materialDiffuse;
	FragColor = vec4(result, 1.0);
}