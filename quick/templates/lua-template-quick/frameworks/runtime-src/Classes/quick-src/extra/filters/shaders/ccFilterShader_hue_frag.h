"#ifdef GL_ES\n\
precision mediump float;\n\
#endif\n\
varying vec2 v_texCoord;\n\
\n\
uniform float u_hueAdjust;\n\
const vec4  kRGBToYPrime = vec4 (0.299, 0.587, 0.114, 0.0);\n\
const vec4  kRGBToI     = vec4 (0.595716, -0.274453, -0.321263, 0.0);\n\
const vec4  kRGBToQ     = vec4 (0.211456, -0.522591, 0.31135, 0.0);\n\
\n\
const vec4  kYIQToR   = vec4 (1.0, 0.9563, 0.6210, 0.0);\n\
const vec4  kYIQToG   = vec4 (1.0, -0.2721, -0.6474, 0.0);\n\
const vec4  kYIQToB   = vec4 (1.0, -1.1070, 1.7046, 0.0);\n\
\n\
void main ()\n\
{\n\
    // Sample the input pixel\n\
    vec4 color   = texture2D(CC_Texture0, v_texCoord);\n\
    \n\
    // Convert to YIQ\n\
    float   YPrime  = dot (color, kRGBToYPrime);\n\
    float   I      = dot (color, kRGBToI);\n\
    float   Q      = dot (color, kRGBToQ);\n\
    \n\
    // Calculate the hue and chroma\n\
    float   hue     = atan (Q, I);\n\
    float   chroma  = sqrt (I * I + Q * Q);\n\
    \n\
    // Make the user's adjustments\n\
    hue += (-u_hueAdjust); //why negative rotation?\n\
    \n\
    // Convert back to YIQ\n\
    Q = chroma * sin (hue);\n\
    I = chroma * cos (hue);\n\
    \n\
    // Convert back to RGB\n\
    vec4    yIQ   = vec4 (YPrime, I, Q, 0.0);\n\
    color.r = dot (yIQ, kYIQToR);\n\
    color.g = dot (yIQ, kYIQToG);\n\
    color.b = dot (yIQ, kYIQToB);\n\
    \n\
    // Save the result\n\
    gl_FragColor = color;\n\
}";

