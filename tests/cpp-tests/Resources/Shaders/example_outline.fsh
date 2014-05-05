/*
  Created by guanghui on 4/8/14.
http://www.idevgames.com/forums/thread-3010.html
*/

varying vec2 v_texCoord;
varying vec4 v_fragmentColor;

uniform sampler2D CC_Texture0;

uniform vec3 u_outlineColor;
uniform float u_threshold;
uniform float u_radius;

void main()
{
    float radius = u_radius;
    vec4 accum = vec4(0.0);
    vec4 normal = vec4(0.0);
    
    normal = texture2D(CC_Texture0, vec2(v_texCoord.x, v_texCoord.y));
    
    accum += texture2D(CC_Texture0, vec2(v_texCoord.x - radius, v_texCoord.y - radius));
    accum += texture2D(CC_Texture0, vec2(v_texCoord.x + radius, v_texCoord.y - radius));
    accum += texture2D(CC_Texture0, vec2(v_texCoord.x + radius, v_texCoord.y + radius));
    accum += texture2D(CC_Texture0, vec2(v_texCoord.x - radius, v_texCoord.y + radius));
    
    accum *= u_threshold;
    
    accum.r = u_outlineColor.x;
    accum.g = u_outlineColor.y;
    accum.b = u_outlineColor.z;
    
    normal = (accum * (1.0 - normal.a)) + (normal * normal.a);
    
    gl_FragColor = v_fragmentColor * normal;
}

