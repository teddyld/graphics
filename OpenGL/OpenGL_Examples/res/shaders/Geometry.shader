#shader vertex
#version 450 core

layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec3 a_Color;

out VS_OUT {
    vec3 color;
} vs_out;

void main()
{
    vs_out.color = a_Color;
	gl_Position = vec4(a_Position, 0.0, 1.0);
}

#shader geometry
#version 450 core

/*
-- Internally GLSL gives us approximately this built-in variable
-- gl_in is declared as an array because most render primitives contain more than 1 vertex; the geometry shader receives all vertices of a primitive as input
in gl_Vertex
-- EmitVertex()    Adds vector currently set to gl_Positiuon to the output primitive
-- EndPrimitive()  Combines all emitted vertices for the primitive into specified output render primitive
{
    vec4  gl_Position;
    float gl_PointSize;
    float gl_ClipDistance[];
} gl_in[];  
*/

/*
The type of primitive input received from the vertex shader
    points: when drawing GL_POINTS primitives (1).
    lines: when drawing GL_LINES or GL_LINE_STRIP (2).
    lines_adjacency: GL_LINES_ADJACENCY or GL_LINE_STRIP_ADJACENCY (4).
    triangles: GL_TRIANGLES, GL_TRIANGLE_STRIP or GL_TRIANGLE_FAN (3).
    triangles_adjacency : GL_TRIANGLES_ADJACENCY or GL_TRIANGLE_STRIP_ADJACENCY (6).
The number within the parenthesis represents the minimal number of vertices a single primitive contains
*/
layout (points) in; 

/*
The type of primitive type that the geometry shader will output one of: points, line_strip, or triangle_strip
max_vertices is the maximum number of vertices the shader will output (OpenGL will not draw the extra vertices)
*/
layout (triangle_strip, max_vertices = 5) out;

// Note: also represented as an array of data
in VS_OUT {
    vec3 color;
} gs_in[];
out vec3 f_Color;

void build_house(vec4 position)
{    
    f_Color = gs_in[0].color; // Each vertex will emit the last stored value in f_Color at that vertices' output value
    gl_Position = position + vec4(-0.2, -0.2, 0.0, 0.0);    // 1:bottom-left
    EmitVertex();   
    gl_Position = position + vec4( 0.2, -0.2, 0.0, 0.0);    // 2:bottom-right
    EmitVertex();
    gl_Position = position + vec4(-0.2,  0.2, 0.0, 0.0);    // 3:top-left
    EmitVertex();
    gl_Position = position + vec4( 0.2,  0.2, 0.0, 0.0);    // 4:top-right
    EmitVertex();
    f_Color = vec3(1.0, 1.0, 1.0); // Set the top vertex to white
    gl_Position = position + vec4( 0.0,  0.4, 0.0, 0.0);    // 5:top
    EmitVertex();
    EndPrimitive();
}

void main() {    
    build_house(gl_in[0].gl_Position);
}  

#shader fragment
#version 450 core

layout(location = 0) out vec4 FragColor;

in vec2 v_TexCoords;

uniform sampler2D texture_diffuse1;

void main()
{    
    FragColor = texture(texture_diffuse1, v_TexCoords);
}