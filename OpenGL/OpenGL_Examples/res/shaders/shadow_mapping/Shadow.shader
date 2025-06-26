#shader vertex
#version 450 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoords;

out VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} vs_out;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;
uniform mat4 u_LightSpaceMatrix;

void main()
{    
    vs_out.FragPos = vec3(u_Model * a_Position);
    vs_out.Normal = transpose(inverse(mat3(u_Model))) * a_Normal;
    vs_out.TexCoords = a_TexCoords;
    vs_out.FragPosLightSpace = u_LightSpaceMatrix * vec4(vs_out.FragPos, 1.0);
    gl_Position = u_Projection * u_View * vec4(vs_out.FragPos, 1.0);
}

#shader fragment
#version 450 core

layout(location = 0) out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} fs_in;

uniform sampler2D u_ShadowMap;

uniform vec3 u_ViewPos;

struct Material
{
	sampler2D diffuse;
	float shininess;
};

struct Light
{
	vec3 position;

	vec3 diffuse;
	vec3 ambient;
	vec3 specular;
};

uniform Light u_Light;
uniform Material u_Material;

float calcShadow(vec4 fragPosLightSpace, vec3 norm, vec3 lightDir)
{
    // Perform perspective divide transforming the range [-w, w] to [-1, -1]
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;

	// Transform NDC to [0, 1] since the depth map is in [0, 1]
	projCoords = projCoords * 0.5 + 0.5; 

	float closestDepth = texture(u_ShadowMap, projCoords.xy).r;
	float currentDepth = projCoords.z;  

	// Bias removes shadow acne when several fragments sample the same discrete depth texel while some are above and below the floor. By itself, this causes peter panning shadow artifact 
	float bias = max(0.05 * (1.0 - dot(norm, lightDir)), 0.005); 

	// Apply percentage-closer filtering to smooth blocky shadows by sampling surrounding texels of the depth map and averaging results
	float shadow = 0.0;
	vec2 texelSize = 1.0 / textureSize(u_ShadowMap, 0);

	for (int x = -1; x <= 1; ++x)
	{
		for (int y = -1; y <= 1; ++y)
		{
			float pcfDepth = texture(u_ShadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
			shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;        
		}    
	}
	shadow /= 9.0;

	
	// Force the shadow to 0.0 for fragments outside the far plane of the light's frustrum
	if (projCoords.z > 1.0)
        shadow = 0.0;

	return shadow;
}

vec3 calcBlinnPhong(Light light, vec3 norm, vec3 viewDir)
{
	// Ambient component
	vec3 ambient = light.ambient * light.diffuse;

	// Diffuse component
	vec3 lightDir = normalize(light.position - fs_in.FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * light.diffuse;

	// Specular component
	vec3 halfwayDir = normalize(lightDir + viewDir);  
	float spec = pow(max(dot(norm, halfwayDir), 0.0), u_Material.shininess);
	vec3 specular = light.specular * spec * light.diffuse;

	// Attenuation
	float distance = length(light.position - fs_in.FragPos);
	float attenuation = 1.0 / distance;
	diffuse *= attenuation;
	specular *= attenuation;
	
	// Shadow component
	float shadow = calcShadow(fs_in.FragPosLightSpace, norm, lightDir);
	vec3 result = ambient + (1.0 - shadow) * (diffuse + specular);

	return result;
}

void main()
{
	vec3 colour = texture(u_Material.diffuse, fs_in.TexCoords).rgb;
	vec3 lighting = vec3(0.0);
	vec3 norm = normalize(fs_in.Normal);
	vec3 viewDir = normalize(u_ViewPos - fs_in.FragPos);

	lighting += calcBlinnPhong(u_Light, norm, viewDir);
	colour *= lighting;
	FragColor = vec4(colour, 1.0);
}