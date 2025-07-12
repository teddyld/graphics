#shader vertex
#version 330 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoords;

out VS_OUT 
{
	vec3 FragPos;
	vec3 Normal;
	vec2 TexCoords;
} vs_out;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
	vs_out.FragPos = vec3(u_Model * a_Position);
	vs_out.Normal = mat3(transpose(inverse(u_Model))) * a_Normal;
	vs_out.TexCoords = a_TexCoords;
	gl_Position = u_Projection * u_View * u_Model * a_Position;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 FragColor;
layout(location = 1) out vec4 BrightColor;  

in VS_OUT 
{
	vec3 FragPos;
	vec3 Normal;
	vec2 TexCoords;
} fs_in;

struct Light
{
	vec3 position;
	vec3 color;
};

uniform Light u_Lights[4];
uniform sampler2D u_Texture;

void main()
{
	vec3 color = texture(u_Texture, fs_in.TexCoords).rgb;
    vec3 normal = normalize(fs_in.Normal);

    vec3 ambient = 0.05 * color;
    vec3 lighting = vec3(0.0);
    
    for (int i = 0; i < 4; i++)
    {
        vec3 lightDir = normalize(u_Lights[i].position - fs_in.FragPos);
        float diff = max(dot(lightDir, normal), 0.0);
        vec3 diffuse = u_Lights[i].color * diff * color;      
        vec3 result = diffuse;        
        // attenuation (use quadratic as we have gamma correction)
        float distance = length(fs_in.FragPos - u_Lights[i].position);
        result *= 1.0 / (distance * distance);
        lighting += result;
    }
    vec3 result = ambient + lighting;
    FragColor = vec4(result, 1.0);

    // check whether fragment output is higher than threshold, if so output as brightness color
    float brightness = dot(result, vec3(0.2126, 0.7152, 0.0722));
    if (brightness > 1.0)
        BrightColor = vec4(result, 1.0);
    else
        BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
}