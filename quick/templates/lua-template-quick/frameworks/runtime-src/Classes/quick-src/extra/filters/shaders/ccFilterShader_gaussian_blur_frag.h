"uniform float u_resolution;\n\
uniform float u_radius;\n\
uniform vec2 u_direction;\n\
\n\
varying vec4 v_fragmentColor;\n\
varying vec2 v_texCoord;\n\
\n\
void main() {\n\
	//this will be our RGBA sum\n\
	vec4 sum = vec4(0.0);\n\
	\n\
	//our original texcoord for this fragment\n\
	vec2 tc = v_texCoord;\n\
	\n\
	//the amount to blur, i.e. how far off center to sample from \n\
	//1.0 -> blur by one pixel\n\
	//2.0 -> blur by two pixels, etc.\n\
	float blur = u_radius/u_resolution; \n\
    \n\
    //the u_direction of our blur\n\
    //(1.0, 0.0) -> x-axis blur\n\
    //(0.0, 1.0) -> y-axis blur\n\
	float hstep = u_direction.x;\n\
	float vstep = u_direction.y;\n\
	\n\
	\n\
    //apply blurring, using a 9-tap filter with predefined gaussian weights\n\
    \n\
	sum += texture2D(CC_Texture0, vec2(tc.x - 4.0*blur*hstep, tc.y - 4.0*blur*vstep)) * 0.0162162162;\n\
	sum += texture2D(CC_Texture0, vec2(tc.x - 3.0*blur*hstep, tc.y - 3.0*blur*vstep)) * 0.0540540541;\n\
	sum += texture2D(CC_Texture0, vec2(tc.x - 2.0*blur*hstep, tc.y - 2.0*blur*vstep)) * 0.1216216216;\n\
	sum += texture2D(CC_Texture0, vec2(tc.x - 1.0*blur*hstep, tc.y - 1.0*blur*vstep)) * 0.1945945946;\n\
	\n\
	sum += texture2D(CC_Texture0, vec2(tc.x, tc.y)) * 0.2270270270;\n\
	\n\
	sum += texture2D(CC_Texture0, vec2(tc.x + 1.0*blur*hstep, tc.y + 1.0*blur*vstep)) * 0.1945945946;\n\
	sum += texture2D(CC_Texture0, vec2(tc.x + 2.0*blur*hstep, tc.y + 2.0*blur*vstep)) * 0.1216216216;\n\
	sum += texture2D(CC_Texture0, vec2(tc.x + 3.0*blur*hstep, tc.y + 3.0*blur*vstep)) * 0.0540540541;\n\
	sum += texture2D(CC_Texture0, vec2(tc.x + 4.0*blur*hstep, tc.y + 4.0*blur*vstep)) * 0.0162162162;\n\
\n\
	//discard alpha for our simple demo, multiply by vertex color and return\n\
	gl_FragColor = v_fragmentColor * vec4(sum.rgb, 1.0);\n\
}";
