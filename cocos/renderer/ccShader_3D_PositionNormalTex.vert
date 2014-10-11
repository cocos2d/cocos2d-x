
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

attribute vec4 a_blendWeight;
attribute vec4 a_blendIndex;

attribute vec2 a_texCoord;

attribute vec3 a_normal;

const int SKINNING_JOINT_COUNT = 60;
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

void getPositionAndNormal(out vec4 position, out vec3 normal)
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
    

    vec4 p = vec4(a_position, 1.0);
    position.x = dot(p, matrixPalette1);
    position.y = dot(p, matrixPalette2);
    position.z = dot(p, matrixPalette3);
    position.w = p.w;

\n#if ((MAX_DIRECTIONAL_LIGHT_NUM > 0) || (MAX_POINT_LIGHT_NUM > 0) || (MAX_SPOT_LIGHT_NUM > 0))\n
    vec4 n = vec4(a_normal, 0.0);
    normal.x = dot(n, matrixPalette1);
    normal.y = dot(n, matrixPalette2);
    normal.z = dot(n, matrixPalette3);
\n#endif\n
}

void main()
{
    vec4 position;
    vec3 normal;
    getPositionAndNormal(position, normal);

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