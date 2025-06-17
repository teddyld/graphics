#shader vertex
#version 450 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec3 a_Normal;

out VS_OUT {
    vec3 normal;
} vs_out;

uniform mat4 u_Model;
uniform mat4 u_View;

void main()
{
    mat3 normalMatrix = mat3(transpose(inverse(u_View * u_Model)));
    vs_out.normal = normalize(vec3(vec4(normalMatrix * a_Normal, 0.0)));
    gl_Position = u_View * u_Model * a_Position; 
}
#shader geometry
#version 450 core

layout (triangles) in;
layout (line_strip, max_vertices = 6) out;

in VS_OUT {
    vec3 normal;
} gs_in[];

const float MAGNITUDE = 0.4;
uniform mat4 u_Projection;

void GenerateLine(int index)
{
    gl_Position = u_Projection * gl_in[index].gl_Position;
    EmitVertex();
    gl_Position = u_Projection * (gl_in[index].gl_Position + vec4(gs_in[index].normal, 0.0) * MAGNITUDE);
    EmitVertex();
    EndPrimitive();
}

void main()
{
    GenerateLine(0); // first vertex normal
    GenerateLine(1); // second vertex normal
    GenerateLine(2); // third vertex normal
}

#shader fragment
#version 450 core

layout(location = 0) out vec4 FragColor;

void main()
{    
    FragColor = vec4(1.0, 1.0, 0.0, 1.0);
}