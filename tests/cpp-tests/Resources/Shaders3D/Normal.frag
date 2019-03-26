#ifdef GL_ES
precision mediump float;
#endif

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
uniform sampler2D u_normalMap;
uniform float u_kBump;
uniform vec4  u_lightPosInLocalSpace;
uniform vec2  u_contentSize;
uniform vec3  u_diffuseL;

uniform sampler2D u_texture;

void main(void)
{
    vec4 texColor=texture2D(u_texture, v_texCoord);
    vec3 normal=texture2D(u_normalMap, v_texCoord).rgb;
	normal=normal*2.0-1.0;
	normal.y=-normal.y;
	if(u_kBump!=1.0)
	{
        //if the vertex.z mult kBump, then the normal.z should div kBump and re-normalize
        normal=vec3(normal.x,normal.y,normal.z/u_kBump);
        normal=normalize(normal);
    }
	vec4 curPixelPosInLocalSpace=vec4(v_texCoord.x*u_contentSize.x,(1.0-v_texCoord.y)*u_contentSize.y,0.0,1.0);
	vec4 lightDir=normalize(curPixelPosInLocalSpace-u_lightPosInLocalSpace);
	vec3 posToLight=-lightDir.xyz;
	float normDotPosToLight=max(0.0,dot(normal,posToLight));
	vec4 diffuse=vec4(normDotPosToLight*u_diffuseL,1.0);
	vec4 ambient=vec4(0.5,0.5,0.5,1);
	gl_FragColor=texColor*vec4(vec3(diffuse+ambient),diffuse.a);
}