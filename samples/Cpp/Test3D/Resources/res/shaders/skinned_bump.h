#ifdef SKINNING_JOINT_COUNT
attribute vec4 a_blendWeights;
attribute vec4 a_blendIndices;

// 32 4x3 matrices as an array of floats
uniform vec4 u_matrixPalette[SKINNING_JOINT_COUNT * 3];

// Common vectors.
vec4 _skinnedPosition;
vec3 _skinnedNormal;

void skinPosition(float blendWeight, int matrixIndex)
{
    vec4 tmp;

    tmp.x = dot(a_position, u_matrixPalette[matrixIndex]);
    tmp.y = dot(a_position, u_matrixPalette[matrixIndex + 1]);
    tmp.z = dot(a_position, u_matrixPalette[matrixIndex + 2]);
    tmp.w = a_position.w;

    _skinnedPosition += blendWeight * tmp;
}

vec4 getPosition()
{
    _skinnedPosition = vec4(0.0);

    // Transform position to view space using 
    // matrix palette with four matrices used to transform a vertex.

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

void skinTangentSpaceVector(vec3 vector, float blendWeight, int matrixIndex)
{
    vec3 tmp;

    tmp.x = dot(vector, u_matrixPalette[matrixIndex].xyz);
    tmp.y = dot(vector, u_matrixPalette[matrixIndex + 1].xyz);
    tmp.z = dot(vector, u_matrixPalette[matrixIndex + 2].xyz);

    _skinnedNormal += blendWeight * tmp;
}

vec3 getTangentSpaceVector(vec3 vector)
{
    _skinnedNormal = vec3(0.0);

    // Transform normal to view space using 
    // matrix palette with four matrices used to transform a vertex.

    float blendWeight = a_blendWeights[0];
    int matrixIndex = int (a_blendIndices[0]) * 3;
    skinTangentSpaceVector(vector, blendWeight, matrixIndex);

    blendWeight = a_blendWeights[1];
    matrixIndex = int(a_blendIndices[1]) * 3;
    skinTangentSpaceVector(vector, blendWeight, matrixIndex);

    blendWeight = a_blendWeights[2];
    matrixIndex = int(a_blendIndices[2]) * 3;
    skinTangentSpaceVector(vector, blendWeight, matrixIndex);

    blendWeight = a_blendWeights[3];
    matrixIndex = int(a_blendIndices[3]) * 3;
    skinTangentSpaceVector(vector, blendWeight, matrixIndex);

    return _skinnedNormal;
}

vec3 getNormal()
{
    return getTangentSpaceVector(a_normal);
}

vec3 getTangent()
{
    return getTangentSpaceVector(a_tangent);
}

vec3 getBinormal()
{
    return getTangentSpaceVector(a_binormal);
}
#else
vec4 getPosition()
{
    return a_position;
}

vec3 getNormal()
{
    return a_normal;
}
vec3 getTangent()
{
    return a_tangent;
}

vec3 getBinormal()
{
    return a_binormal;
}
#endif