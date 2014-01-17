#ifdef OPENGL_ES
precision mediump float;
#endif

// Uniforms
uniform sampler2D u_texture;


#define SAMPLE_COUNT 9
uniform vec2 u_sampleOff[SAMPLE_COUNT]; // sample offset
uniform float u_sampleWeight[SAMPLE_COUNT]; //sample weight
uniform vec2 u_delta;

// Inputs
varying vec2 v_texCoord;

void main()
{
    vec4 sum = vec4(0.0);
    
    sum += texture2D(u_texture, v_texCoord - 4.0 * u_delta) * 0.05;
    sum += texture2D(u_texture, v_texCoord - 3.0 * u_delta) * 0.09;
    sum += texture2D(u_texture, v_texCoord - 2.0 * u_delta) * 0.12;
    sum += texture2D(u_texture, v_texCoord - u_delta) * 0.15;
    sum += texture2D(u_texture, v_texCoord) * 0.16;
    sum += texture2D(u_texture, v_texCoord + u_delta) * 0.15;
    sum += texture2D(u_texture, v_texCoord + 2.0 * u_delta) * 0.12;
    sum += texture2D(u_texture, v_texCoord + 3.0 * u_delta) * 0.09;
    sum += texture2D(u_texture, v_texCoord + 4.0 * u_delta) * 0.05;
    
    //sum = texture2D(u_texture, v_texCoord);
    
    gl_FragColor = sum;
}