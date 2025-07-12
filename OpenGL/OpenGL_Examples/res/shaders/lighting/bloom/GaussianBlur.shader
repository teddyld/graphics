#shader vertex
#version 330 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec2 a_TexCoords;

out vec2 v_TexCoords;

void main()
{
	v_TexCoords = a_TexCoords;
	gl_Position = a_Position;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 FragColor;

in vec2 v_TexCoords;

uniform sampler2D u_Image;
uniform bool u_Horizontal;
const float weight[5] = float[](0.2270270270, 0.1945945946, 0.1216216216, 0.0540540541, 0.0162162162);

void main()
{
	 vec2 tex_offset = 1.0 / textureSize(u_Image, 0); // gets size of single texel
     vec3 result = texture(u_Image, v_TexCoords).rgb * weight[0];
     if (u_Horizontal)
     {
         for (int i = 1; i < 5; ++i)
         {
            result += texture(u_Image, v_TexCoords + vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
            result += texture(u_Image, v_TexCoords - vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
         }
     }
     else
     {
         for (int i = 1; i < 5; ++i)
         {
             result += texture(u_Image, v_TexCoords + vec2(0.0, tex_offset.y * i)).rgb * weight[i];
             result += texture(u_Image, v_TexCoords - vec2(0.0, tex_offset.y * i)).rgb * weight[i];
         }
     }
     FragColor = vec4(result, 1.0);
}