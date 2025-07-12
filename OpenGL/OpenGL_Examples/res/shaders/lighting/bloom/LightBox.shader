#shader vertex
#version 330 core

layout(location = 0) in vec4 a_Position;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
    gl_Position = u_Projection * u_View * u_Model * a_Position;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 FragColor;
layout(location = 1) out vec4 BrightColor;

uniform vec3 u_LightColor;

void main()
{           
    FragColor = vec4(u_LightColor, 1.0);
    float brightness = dot(FragColor.rgb, vec3(0.2126, 0.7152, 0.0722));
    if (brightness > 1.0)
        BrightColor = vec4(FragColor.rgb, 1.0);
	else
		BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
}