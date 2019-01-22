// http://www.cocos2d-iphone.org

uniform mat4 CC_PMatrix;
uniform mat4 CC_MultiViewPMatrix[4];
uniform mat4 CC_MVMatrix;
uniform mat4 CC_MVPMatrix;
uniform mat4 CC_MultiViewMVPMatrix[4];
uniform mat3 CC_NormalMatrix;
uniform vec4 CC_Time;
uniform vec4 CC_SinTime;
uniform vec4 CC_CosTime;
uniform vec4 CC_Random01;
uniform sampler2D CC_Texture0;
uniform sampler2D CC_Texture1;
uniform sampler2D CC_Texture2;
uniform sampler2D CC_Texture3;
//CC INCLUDES END\n\n

#ifdef GL_ES
precision lowp float;
#endif

varying vec2 v_texCoord;

uniform sampler2D u_texture;

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
	gl_FragColor = colors[y] * texture2D(u_texture, v_texCoord);
}