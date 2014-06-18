// http://www.cocos2d-iphone.org

#ifdef GL_ES
precision lowp float;
#endif

varying vec2 v_texCoord;

vec4 colors[10];

void main(void)
{
	colors[0] = vec4(1,0,0,1);
	colors[1] = vec4(0,1,0,1);
	colors[2] = vec4(0,0,1,1);
	colors[3] = vec4(0,1,1,1);
	colors[4] = vec4(1,0,1,1);
	colors[5] = vec4(1,1,0,1);
	colors[6] = vec4(1,1,1,1);
	colors[7] = vec4(1,0.5,0,1);
	colors[8] = vec4(1,0.5,0.5,1);
	colors[9] = vec4(0.5,0.5,1,1);
	
	// inline to prevent "float" loss and keep using lowp
	int y = int( mod(gl_FragCoord.y / 3.0, 10.0 ) );
	gl_FragColor = colors[y] * texture2D(CC_Texture0, v_texCoord);
}