
const char* cc3D_PositionTex_vert = STRINGIFY(

attribute vec4 a_position;
attribute vec2 a_texCoord;

varying vec2 TextureCoordOut;

void main(void)
{
    gl_Position = CC_MVPMatrix * a_position;
    TextureCoordOut = a_texCoord;
    TextureCoordOut.y = 1.0 - TextureCoordOut.y;
}
);

const char* cc3D_SkinPositionTex_vert = STRINGIFY(
attribute vec4 a_position;

attribute vec4 a_blendWeights;
attribute vec4 a_blendIndices;

attribute vec2 a_texCoord;

const int SKINNING_JOINT_COUNT = 30;
// Uniforms
uniform vec4 u_matrixPalette[SKINNING_JOINT_COUNT * 3];

// Varyings
varying vec2 TextureCoordOut;

vec4 _skinnedPosition;
vec4 tmp;

void skinPosition(float blendWeight, int matrixIndex)
{
    tmp.x = dot(a_position, u_matrixPalette[matrixIndex]);
    tmp.y = dot(a_position, u_matrixPalette[matrixIndex + 1]);
    tmp.z = dot(a_position, u_matrixPalette[matrixIndex + 2]);
    tmp.w = a_position.w;
    _skinnedPosition += blendWeight * tmp;
}

vec4 getPosition()
{
    _skinnedPosition = vec4(0.0);
    
    float blendWeight = a_blendWeights[0];
    int matrixIndex = int (a_blendIndices[0]) * 3;
    skinPosition(blendWeight, matrixIndex);
    
    blendWeight = a_blendWeights[1];
    matrixIndex = int(a_blendIndices[1]) * 3;
    skinPosition(blendWeight, matrixIndex);
    
    blendWeight = a_blendWeights[2];
    matrixIndex = int(a_blendIndices[2]) * 3;
    skinPosition(blendWeight, matrixIndex);
    
    blendWeight = a_blendWeights[3];
    matrixIndex = int(a_blendIndices[3]) * 3;
    skinPosition(blendWeight, matrixIndex);
    
    return _skinnedPosition;
}

void main()
{
    vec4 position = getPosition();
    gl_Position = CC_MVPMatrix * position;
    
    TextureCoordOut = a_texCoord;
    TextureCoordOut.y = 1.0 - TextureCoordOut.y;
}

);