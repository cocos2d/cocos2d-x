
const char* cc3D_PositionNormalTex_vert = STRINGIFY(

\n#if (MAX_POINT_LIGHT_NUM > 0)\n
uniform vec3 u_PointLightSourcePosition[MAX_POINT_LIGHT_NUM];
\n#endif\n
\n#if (MAX_SPOT_LIGHT_NUM > 0)\n
uniform vec3 u_SpotLightSourcePosition[MAX_SPOT_LIGHT_NUM];
\n#endif\n

attribute vec4 a_position;
attribute vec2 a_texCoord;
attribute vec3 a_normal;
varying vec2 TextureCoordOut;

\n#if MAX_POINT_LIGHT_NUM\n
varying vec3 v_vertexToPointLightDirection[MAX_POINT_LIGHT_NUM];
\n#endif\n
\n#if MAX_SPOT_LIGHT_NUM\n
varying vec3 v_vertexToSpotLightDirection[MAX_SPOT_LIGHT_NUM];
\n#endif\n
\n#if ((MAX_DIRECTIONAL_LIGHT_NUM > 0) || (MAX_POINT_LIGHT_NUM > 0) || (MAX_SPOT_LIGHT_NUM > 0))\n
varying vec3 v_normal;
\n#endif\n

void main(void)
{
    vec4 ePosition = CC_MVMatrix * a_position;
\n#if (MAX_POINT_LIGHT_NUM > 0)\n
    for (int i = 0; i < MAX_POINT_LIGHT_NUM; ++i)
    {
        v_vertexToPointLightDirection[i] = u_PointLightSourcePosition[i].xyz - ePosition.xyz;
    }
\n#endif\n

\n#if (MAX_SPOT_LIGHT_NUM > 0)\n
    for (int i = 0; i < MAX_SPOT_LIGHT_NUM; ++i)
    {
        v_vertexToSpotLightDirection[i] = u_SpotLightSourcePosition[i] - ePosition.xyz;
    }
\n#endif\n
        
\n#if ((MAX_DIRECTIONAL_LIGHT_NUM > 0) || (MAX_POINT_LIGHT_NUM > 0) || (MAX_SPOT_LIGHT_NUM > 0))\n
    v_normal = CC_NormalMatrix * a_normal;
\n#endif\n

    TextureCoordOut = a_texCoord;
    TextureCoordOut.y = 1.0 - TextureCoordOut.y;
    gl_Position = CC_PMatrix * ePosition;
}
);

const char* cc3D_SkinPositionNormalTex_vert = STRINGIFY(

\n#if (MAX_POINT_LIGHT_NUM > 0)\n
uniform vec3 u_PointLightSourcePosition[MAX_POINT_LIGHT_NUM];
\n#endif\n
\n#if (MAX_SPOT_LIGHT_NUM > 0)\n
uniform vec3 u_SpotLightSourcePosition[MAX_SPOT_LIGHT_NUM];
\n#endif\n

attribute vec3 a_position;

attribute lowp vec4 a_blendWeight;
attribute vec4 a_blendIndex;

attribute vec2 a_texCoord;

attribute vec3 a_normal;

const int SKINNING_JOINT_COUNT = 8;
// Uniforms
uniform vec4 u_matrixPalette[SKINNING_JOINT_COUNT * 3];

// Varyings
varying vec2 TextureCoordOut;

\n#if MAX_POINT_LIGHT_NUM\n
varying vec3 v_vertexToPointLightDirection[MAX_POINT_LIGHT_NUM];
\n#endif\n
\n#if MAX_SPOT_LIGHT_NUM\n
varying vec3 v_vertexToSpotLightDirection[MAX_SPOT_LIGHT_NUM];
\n#endif\n
varying vec3 v_normal;

struct SSkinningTransform {
    vec4 row_one;
    vec4 row_two;
    vec4 row_three;
};

SSkinningTransform GenerateSkinningTransform() {
    SSkinningTransform skinning_transform;
    lowp float blendWeight = a_blendWeight[0];

    int matrixIndex = int (a_blendIndex[0]) * 3;
    skinning_transform.row_one = u_matrixPalette[matrixIndex] * blendWeight;
    skinning_transform.row_two = u_matrixPalette[matrixIndex + 1] * blendWeight;
    skinning_transform.row_three = u_matrixPalette[matrixIndex + 2] * blendWeight;

    blendWeight = a_blendWeight[1];
    if (blendWeight > 0.0) {
        matrixIndex = int(a_blendIndex[1]) * 3;
        skinning_transform.row_one += u_matrixPalette[matrixIndex] * blendWeight;
        skinning_transform.row_two += u_matrixPalette[matrixIndex + 1] * blendWeight;
        skinning_transform.row_three += u_matrixPalette[matrixIndex + 2] * blendWeight;
        blendWeight = a_blendWeight[2];
        
        if (blendWeight > 0.0) {
            matrixIndex = int(a_blendIndex[2]) * 3;
            skinning_transform.row_one += u_matrixPalette[matrixIndex] * blendWeight;
            skinning_transform.row_two += u_matrixPalette[matrixIndex + 1] * blendWeight;
            skinning_transform.row_three += u_matrixPalette[matrixIndex + 2] * blendWeight;
            blendWeight = a_blendWeight[3];
            
            if (blendWeight > 0.0) {
                matrixIndex = int(a_blendIndex[3]) * 3;
                skinning_transform.row_one += u_matrixPalette[matrixIndex] * blendWeight;
                skinning_transform.row_two += u_matrixPalette[matrixIndex + 1] * blendWeight;
                skinning_transform.row_three += u_matrixPalette[matrixIndex + 2] * blendWeight;
            }
        }
    }
    return skinning_transform;
}

vec3 SkinnedVector(vec3 input_vector, SSkinningTransform skinning_transform) {
    vec3 skinned_vector;
    skinned_vector.x = dot(vec4(input_vector, 1.0), skinning_transform.row_one);
    skinned_vector.y = dot(vec4(input_vector, 1.0), skinning_transform.row_two);
    skinned_vector.z = dot(vec4(input_vector, 1.0), skinning_transform.row_three);
    return skinned_vector;
}

void main()
{
    SSkinningTransform skinning_transform = GenerateSkinningTransform();
    vec4 position = vec4(SkinnedVector(a_position, skinning_transform), 1.0);
\n#if ((MAX_DIRECTIONAL_LIGHT_NUM > 0) || (MAX_POINT_LIGHT_NUM > 0) || (MAX_SPOT_LIGHT_NUM > 0))\n
    vec3 normal = SkinnedVector(a_normal, skinning_transform);
\n#endif\n

    vec4 ePosition = CC_MVMatrix * position;
\n#if (MAX_POINT_LIGHT_NUM > 0)\n
    for (int i = 0; i < MAX_POINT_LIGHT_NUM; ++i)
    {
        v_vertexToPointLightDirection[i] = u_PointLightSourcePosition[i].xyz- ePosition.xyz;
    }
\n#endif\n

\n#if (MAX_SPOT_LIGHT_NUM > 0)\n
    for (int i = 0; i < MAX_SPOT_LIGHT_NUM; ++i)
    {
        v_vertexToSpotLightDirection[i] = u_SpotLightSourcePosition[i] - ePosition.xyz;
    }
\n#endif\n

\n#if ((MAX_DIRECTIONAL_LIGHT_NUM > 0) || (MAX_POINT_LIGHT_NUM > 0) || (MAX_SPOT_LIGHT_NUM > 0))\n
    v_normal = CC_NormalMatrix * normal;
\n#endif\n

    TextureCoordOut = a_texCoord;
    TextureCoordOut.y = 1.0 - TextureCoordOut.y;
    gl_Position = CC_PMatrix * ePosition;
}

);