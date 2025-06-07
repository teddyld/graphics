#shader vertex
#version 450 core

layout(location = 0) in vec4 a_Position;

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * a_Position;
};

#shader fragment
#version 450 core

layout(location = 0) out vec4 o_FragColor;

in vec4 gl_FragCoord;

uniform ivec2 u_Resolution;
uniform float u_Time;

vec3 palette(float t)
{
	vec3 a = vec3(0.5, 0.5, 0.5);
	vec3 b = vec3(0.5, 0.5, 0.5);
	vec3 c = vec3(1.0, 1.0, 1.0);
	vec3 d = vec3(0.263, 0.416, 0.557);

	return a + b * cos(6.28318 * (c * t + d));
}

void main()
{
	// Center coordinate (0, 0) to the canvas and change corner coordinates to clip space
	vec2 uv = gl_FragCoord.xy / u_Resolution.xy * 2.0 - 1.0;

	// Adjust shader to aspect ratio
	uv.x *= u_Resolution.x / u_Resolution.y;
	vec2 uv0 = uv;
	vec3 finalColor = vec3(0.0);

	for (float i = 0.0; i < 4.0; i++)
	{
		// Spatial repetition using fract; scaling and centering each partition
		uv = fract(uv * 1.5) - 0.5;

		float d = length(uv) * exp(-length(uv0));

		vec3 col = palette(length(uv0) + i * 0.4 + u_Time * 0.4);

		// Create infinite loop of rings that terminate at the center
		d = sin(d * 8.0 + u_Time) / 8.0;
		d = abs(d);

		// Change contrast with pow
		d = pow(0.01 / d, 2.0);

		finalColor += col * d;
	}
	

	o_FragColor = vec4(finalColor, 1.0);
};