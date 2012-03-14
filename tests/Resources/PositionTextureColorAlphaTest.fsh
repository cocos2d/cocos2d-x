// http://www.cocos2d-iphone.org

#ifdef GL_ES
precision lowp float;
#endif

uniform		float u_alpha_value;

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
uniform sampler2D u_texture;

void main()
{
	vec4 texColor = texture2D(u_texture, v_texCoord);

	//
	// mimic: glAlphaFunc(GL_GREATER)
	// pass if ( incoming_pixel >= u_alpha_value ) => fail if incoming_pixel < u_alpha_value
	//
	if ( texColor.a <= u_alpha_value )
	{
		discard;
	}

	gl_FragColor = texColor * v_fragmentColor;
}