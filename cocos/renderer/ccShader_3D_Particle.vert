
const char* cc3D_Particle_vert = R"(
                                              
attribute vec4 a_position;
attribute vec4 a_color;
attribute vec2 a_texCoord;

varying vec2 TextureCoordOut;
varying vec4 ColorOut;
void main()
{
    ColorOut = a_color;
    TextureCoordOut = a_texCoord;
    TextureCoordOut.y = 1.0 - TextureCoordOut.y;
    gl_Position = CC_PMatrix * a_position;
}

)";