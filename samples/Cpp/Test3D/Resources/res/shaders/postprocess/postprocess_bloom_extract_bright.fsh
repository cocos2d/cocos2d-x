#ifdef OPENGL_ES
precision mediump float;
#endif

// Uniforms
uniform sampler2D u_texture;
uniform float u_bloomThreshold;

// Inputs
varying vec2 v_texCoord;

void main()
{
    vec4 color = texture2D(u_texture, v_texCoord);
    
   //float gray = dot(color.rgb, vec3(0.299, 0.587, 0.25));
   
   //float coef = smoothstep(u_bloomThreshold, 1.0, gray);
    
    color = (color - u_bloomThreshold) / (1.0 - u_bloomThreshold);
   
   gl_FragColor = clamp(color, 0.0, 1.0);
}