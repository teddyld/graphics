#shader vertex
#version 450 core

layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec2 a_TexCoord;

out vec2 v_TexCoord;

uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * vec4(a_Position, 0.0, 1.0); 
    v_TexCoord = a_TexCoord;
}  

#shader fragment
#version 450 core

layout(location = 0) out vec4 FragColor;
  
in vec2 v_TexCoord;

uniform sampler2D u_Texture;

const float offset = 1.0 / 300.0;

// Apply post-processing effects to screen-space texture
void main()
{ 
    // Normal
    FragColor = texture(u_Texture, v_TexCoord);

    // Inversion
    //FragColor = vec4(vec3(1.0 - texture(u_Texture, v_TexCoord)), 1.0); 

    // Grayscale
    //FragColor = texture(u_Texture, v_TexCoord);
    //float average = (FragColor.r + FragColor.g + FragColor.b) / 3;
    //FragColor = vec4(average, average, average, 1.0);

    // Kernel effects
    /*
    vec2 offsets[9] = vec2[](
        vec2(-offset,  offset), // top-left
        vec2( 0.0f,    offset), // top-center
        vec2( offset,  offset), // top-right
        vec2(-offset,  0.0f),   // center-left
        vec2( 0.0f,    0.0f),   // center-center
        vec2( offset,  0.0f),   // center-right
        vec2(-offset, -offset), // bottom-left
        vec2( 0.0f,   -offset), // bottom-center
        vec2( offset, -offset)  // bottom-right    
    );

    float kernel[9] = float[](
        1, 1, 1,
        1, -8, 1,
        1, 1, 1
    );
    
    vec3 sampleTex[9];
    for(int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(u_Texture, v_TexCoord.st + offsets[i]));
    }
    vec3 col = vec3(0.0);
    for (int i = 0; i < 9; i++)
        col += sampleTex[i] * kernel[i];
    
    FragColor = vec4(col, 1.0);
    */
}