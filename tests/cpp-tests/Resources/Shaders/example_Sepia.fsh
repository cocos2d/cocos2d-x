
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
precision mediump float;
#endif

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

void main(void)
{
	vec4 c = texture2D(CC_Texture0, v_texCoord);
    vec4 final = c;
    final.r = (c.r * 0.393) + (c.g * 0.769) + (c.b * 0.189);
    final.g = (c.r * 0.349) + (c.g * 0.686) + (c.b * 0.168);
    final.b = (c.r * 0.272) + (c.g * 0.534) + (c.b * 0.131);

	gl_FragColor = final;
}