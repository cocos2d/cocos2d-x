const GLchar * FilterShader_celshading_frag = STRINGIFY(

\n#ifdef GL_ES\n
precision mediump float;
\n#endif\n

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

uniform vec2 resolution;

\n#define FILTER_SIZE 3\n
\n#define COLOR_LEVELS 7.0\n
\n#define EDGE_FILTER_SIZE 3\n
\n#define EDGE_THRESHOLD 0.05\n

vec4 edgeFilter(in int px, in int py)
{
	vec4 color = vec4(0.0);
	
	for (int y = -EDGE_FILTER_SIZE; y <= EDGE_FILTER_SIZE; ++y)
	{
		for (int x = -EDGE_FILTER_SIZE; x <= EDGE_FILTER_SIZE; ++x)
		{
			color += texture2D(CC_Texture0, v_texCoord + vec2(px + x, py + y) / resolution.xy);
		}
	}

	color /= float((2 * EDGE_FILTER_SIZE + 1) * (2 * EDGE_FILTER_SIZE + 1));
	
	return color;
}

void main(void)
{	
	// Shade
	vec4 color = vec4(0.0);
	
	for (int y = -FILTER_SIZE; y <= FILTER_SIZE; ++y)
	{
		for (int x = -FILTER_SIZE; x <= FILTER_SIZE; ++x)
		{
			color += texture2D(CC_Texture0, v_texCoord + vec2(x, y) / resolution.xy);
		}
	}

	color /= float((2 * FILTER_SIZE + 1) * (2 * FILTER_SIZE + 1));
	
	for (int c = 0; c < 3; ++c)
	{
		color[c] = floor(COLOR_LEVELS * color[c]) / COLOR_LEVELS;
	}
	
	// Highlight edges
	vec4 sum = abs(edgeFilter(0, 1) - edgeFilter(0, -1));
	sum += abs(edgeFilter(1, 0) - edgeFilter(-1, 0));
	sum /= 2.0;	

	if (length(sum) > EDGE_THRESHOLD)
	{
		color.rgb = vec3(0.0);	
	}
	
	gl_FragColor = color;
}

);
