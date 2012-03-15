// http://www.cocos2d-iphone.org

#ifdef GL_ES
precision lowp float;
#endif

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
uniform sampler2D u_texture;

void main()
{
	gl_FragColor = vec4( v_fragmentColor.rgb,										// RGB from uniform
						v_fragmentColor.a * texture2D(u_texture, v_texCoord).a		// A from texture & uniform
						);
}
