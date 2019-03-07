attribute vec3 a_position;
attribute vec3 a_normal;
attribute vec4 a_blendWeight;
attribute vec4 a_blendIndex;

uniform float OutlineWidth;

const int SKINNING_JOINT_COUNT = 60;
// Uniforms
uniform vec4 u_matrixPalette[SKINNING_JOINT_COUNT * 3];
uniform mat4 u_MVPMatrix;

// Varyings
varying vec2 TextureCoordOut;

vec4 SkinnedVec3(vec4 vec)
{
    float blendWeight = a_blendWeight[0];

    int matrixIndex = int (a_blendIndex[0]) * 3;
    vec4 matrixPalette1 = u_matrixPalette[matrixIndex] * blendWeight;
    vec4 matrixPalette2 = u_matrixPalette[matrixIndex + 1] * blendWeight;
    vec4 matrixPalette3 = u_matrixPalette[matrixIndex + 2] * blendWeight;
    
    
    blendWeight = a_blendWeight[1];
    if (blendWeight > 0.0)
    {
        matrixIndex = int(a_blendIndex[1]) * 3;
        matrixPalette1 += u_matrixPalette[matrixIndex] * blendWeight;
        matrixPalette2 += u_matrixPalette[matrixIndex + 1] * blendWeight;
        matrixPalette3 += u_matrixPalette[matrixIndex + 2] * blendWeight;
    }
    
    
    blendWeight = a_blendWeight[2];
    if (blendWeight > 0.0)
    {
        matrixIndex = int(a_blendIndex[2]) * 3;
        matrixPalette1 += u_matrixPalette[matrixIndex] * blendWeight;
        matrixPalette2 += u_matrixPalette[matrixIndex + 1] * blendWeight;
        matrixPalette3 += u_matrixPalette[matrixIndex + 2] * blendWeight;
    }
    
    
    blendWeight = a_blendWeight[3];
    if (blendWeight > 0.0)
    {
        matrixIndex = int(a_blendIndex[3]) * 3;
        matrixPalette1 += u_matrixPalette[matrixIndex] * blendWeight;
        matrixPalette2 += u_matrixPalette[matrixIndex + 1] * blendWeight;
        matrixPalette3 += u_matrixPalette[matrixIndex + 2] * blendWeight;
    }
    

    vec4 _skinnedPosition;
    vec4 postion = vec;
    _skinnedPosition.x = dot(postion, matrixPalette1);
    _skinnedPosition.y = dot(postion, matrixPalette2);
    _skinnedPosition.z = dot(postion, matrixPalette3);
    _skinnedPosition.w = postion.w;
    
    return _skinnedPosition;
}

void main()
{
    vec4 pos = u_MVPMatrix * SkinnedVec3(vec4(a_position,1.0));
    
    vec4 normalproj = u_MVPMatrix * vec4(SkinnedVec3(vec4(a_normal,0.0)).xyz, 0);
    normalproj = normalize(normalproj);
    pos.xy += normalproj.xy * (OutlineWidth * (pos.z * 0.5 + 0.5));

    gl_Position = pos;
}
