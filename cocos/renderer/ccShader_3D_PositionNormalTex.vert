
const char* cc3D_PositionNormalTex_vert = STRINGIFY(

\n#ifdef USE_NORMAL_MAPPING\n
\n#if (MAX_DIRECTIONAL_LIGHT_NUM > 0)\n
uniform vec3 u_DirLightSourceDirection[MAX_DIRECTIONAL_LIGHT_NUM];
\n#endif\n
\n#endif\n
\n#if (MAX_POINT_LIGHT_NUM > 0)\n
uniform vec3 u_PointLightSourcePosition[MAX_POINT_LIGHT_NUM];
\n#endif\n
\n#if (MAX_SPOT_LIGHT_NUM > 0)\n
uniform vec3 u_SpotLightSourcePosition[MAX_SPOT_LIGHT_NUM];
\n#ifdef USE_NORMAL_MAPPING\n
uniform vec3 u_SpotLightSourceDirection[MAX_SPOT_LIGHT_NUM]; 
\n#endif\n
\n#endif\n

attribute vec4 a_position;
attribute vec2 a_texCoord;
attribute vec3 a_normal;
\n#ifdef USE_NORMAL_MAPPING\n
attribute vec3 a_tangent;
attribute vec3 a_binormal;
\n#endif\n
varying vec2 TextureCoordOut;

\n#ifdef USE_NORMAL_MAPPING\n
\n#if MAX_DIRECTIONAL_LIGHT_NUM\n
varying vec3 v_dirLightDirection[MAX_DIRECTIONAL_LIGHT_NUM];
\n#endif\n
\n#endif\n
\n#if MAX_POINT_LIGHT_NUM\n
varying vec3 v_vertexToPointLightDirection[MAX_POINT_LIGHT_NUM];
\n#endif\n
\n#if MAX_SPOT_LIGHT_NUM\n
varying vec3 v_vertexToSpotLightDirection[MAX_SPOT_LIGHT_NUM];
\n#ifdef USE_NORMAL_MAPPING\n
varying vec3 v_spotLightDirection[MAX_SPOT_LIGHT_NUM];
\n#endif\n
\n#endif\n

\n#ifndef USE_NORMAL_MAPPING\n
\n#if ((MAX_DIRECTIONAL_LIGHT_NUM > 0) || (MAX_POINT_LIGHT_NUM > 0) || (MAX_SPOT_LIGHT_NUM > 0))\n
varying vec3 v_normal;
\n#endif\n
\n#endif\n

void main(void)
{
    vec4 ePosition = CC_MVMatrix * a_position;
\n#ifdef USE_NORMAL_MAPPING\n
    \n#if ((MAX_DIRECTIONAL_LIGHT_NUM > 0) || (MAX_POINT_LIGHT_NUM > 0) || (MAX_SPOT_LIGHT_NUM > 0))\n
        vec3 eTangent = normalize(CC_NormalMatrix * a_tangent);
        vec3 eBinormal = normalize(CC_NormalMatrix * a_binormal);
        vec3 eNormal = normalize(CC_NormalMatrix * a_normal);
    \n#endif\n
    \n#if (MAX_DIRECTIONAL_LIGHT_NUM > 0)\n
        for (int i = 0; i < MAX_DIRECTIONAL_LIGHT_NUM; ++i)
        {
            v_dirLightDirection[i].x = dot(eTangent, u_DirLightSourceDirection[i]);
            v_dirLightDirection[i].y = dot(eBinormal, u_DirLightSourceDirection[i]);
            v_dirLightDirection[i].z = dot(eNormal, u_DirLightSourceDirection[i]);
        }
    \n#endif\n

    \n#if (MAX_POINT_LIGHT_NUM > 0)\n
        for (int i = 0; i < MAX_POINT_LIGHT_NUM; ++i)
        {
            vec3 pointLightDir = u_PointLightSourcePosition[i].xyz - ePosition.xyz;
            v_vertexToPointLightDirection[i].x = dot(eTangent, pointLightDir);
            v_vertexToPointLightDirection[i].y = dot(eBinormal, pointLightDir);
            v_vertexToPointLightDirection[i].z = dot(eNormal, pointLightDir);
        }
    \n#endif\n

    \n#if (MAX_SPOT_LIGHT_NUM > 0)\n
        for (int i = 0; i < MAX_SPOT_LIGHT_NUM; ++i)
        {
            vec3 spotLightDir = u_SpotLightSourcePosition[i] - ePosition.xyz;
            v_vertexToSpotLightDirection[i].x = dot(eTangent, spotLightDir);
            v_vertexToSpotLightDirection[i].y = dot(eBinormal, spotLightDir);
            v_vertexToSpotLightDirection[i].z = dot(eNormal, spotLightDir);

            v_spotLightDirection[i].x = dot(eTangent, u_SpotLightSourceDirection[i]);
            v_spotLightDirection[i].y = dot(eBinormal, u_SpotLightSourceDirection[i]);
            v_spotLightDirection[i].z = dot(eNormal, u_SpotLightSourceDirection[i]);
        }
    \n#endif\n
\n#else\n
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
\n#endif\n

    TextureCoordOut = a_texCoord;
    TextureCoordOut.y = 1.0 - TextureCoordOut.y;
    gl_Position = CC_PMatrix * ePosition;
}
);

const char* cc3D_SkinPositionNormalTex_vert = STRINGIFY(

\n#ifdef USE_NORMAL_MAPPING\n
\n#if (MAX_DIRECTIONAL_LIGHT_NUM > 0)\n
uniform vec3 u_DirLightSourceDirection[MAX_DIRECTIONAL_LIGHT_NUM];
\n#endif\n
\n#endif\n
\n#if (MAX_POINT_LIGHT_NUM > 0)\n
uniform vec3 u_PointLightSourcePosition[MAX_POINT_LIGHT_NUM];
\n#endif\n
\n#if (MAX_SPOT_LIGHT_NUM > 0)\n
uniform vec3 u_SpotLightSourcePosition[MAX_SPOT_LIGHT_NUM];
\n#ifdef USE_NORMAL_MAPPING\n
uniform vec3 u_SpotLightSourceDirection[MAX_SPOT_LIGHT_NUM]; 
\n#endif\n
\n#endif\n

attribute vec3 a_position;

attribute vec4 a_blendWeight;
attribute vec4 a_blendIndex;

attribute vec2 a_texCoord;

attribute vec3 a_normal;
\n#ifdef USE_NORMAL_MAPPING\n
attribute vec3 a_tangent;
attribute vec3 a_binormal;
\n#endif\n

const int SKINNING_JOINT_COUNT = 60;
// Uniforms
uniform vec4 u_matrixPalette[SKINNING_JOINT_COUNT * 3];

// Varyings
varying vec2 TextureCoordOut;

\n#ifdef USE_NORMAL_MAPPING\n
\n#if MAX_DIRECTIONAL_LIGHT_NUM\n
varying vec3 v_dirLightDirection[MAX_DIRECTIONAL_LIGHT_NUM];
\n#endif\n
\n#endif\n
\n#if MAX_POINT_LIGHT_NUM\n
varying vec3 v_vertexToPointLightDirection[MAX_POINT_LIGHT_NUM];
\n#endif\n
\n#if MAX_SPOT_LIGHT_NUM\n
varying vec3 v_vertexToSpotLightDirection[MAX_SPOT_LIGHT_NUM];
\n#ifdef USE_NORMAL_MAPPING\n
varying vec3 v_spotLightDirection[MAX_SPOT_LIGHT_NUM];
\n#endif\n
\n#endif\n

\n#ifndef USE_NORMAL_MAPPING\n
\n#if ((MAX_DIRECTIONAL_LIGHT_NUM > 0) || (MAX_POINT_LIGHT_NUM > 0) || (MAX_SPOT_LIGHT_NUM > 0))\n
varying vec3 v_normal;
\n#endif\n
\n#endif\n

void getPositionAndNormal(out vec4 position, out vec3 normal, out vec3 tangent, out vec3 binormal)
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
        
        blendWeight = a_blendWeight[2];
        if (blendWeight > 0.0)
        {
            matrixIndex = int(a_blendIndex[2]) * 3;
            matrixPalette1 += u_matrixPalette[matrixIndex] * blendWeight;
            matrixPalette2 += u_matrixPalette[matrixIndex + 1] * blendWeight;
            matrixPalette3 += u_matrixPalette[matrixIndex + 2] * blendWeight;
            
            blendWeight = a_blendWeight[3];
            if (blendWeight > 0.0)
            {
                matrixIndex = int(a_blendIndex[3]) * 3;
                matrixPalette1 += u_matrixPalette[matrixIndex] * blendWeight;
                matrixPalette2 += u_matrixPalette[matrixIndex + 1] * blendWeight;
                matrixPalette3 += u_matrixPalette[matrixIndex + 2] * blendWeight;
            }
        }
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
\n#ifdef USE_NORMAL_MAPPING\n
    vec4 t = vec4(a_tangent, 0.0);
    tangent.x = dot(t, matrixPalette1);
    tangent.y = dot(t, matrixPalette2);
    tangent.z = dot(t, matrixPalette3);
    vec4 b = vec4(a_binormal, 0.0);
    binormal.x = dot(b, matrixPalette1);
    binormal.y = dot(b, matrixPalette2);
    binormal.z = dot(b, matrixPalette3);
\n#endif\n
\n#endif\n
}

void main()
{
    vec4 position;
    vec3 normal;
    vec3 tangent;
    vec3 binormal;
    getPositionAndNormal(position, normal, tangent, binormal);
    vec4 ePosition = CC_MVMatrix * position;

\n#ifdef USE_NORMAL_MAPPING\n
    \n#if ((MAX_DIRECTIONAL_LIGHT_NUM > 0) || (MAX_POINT_LIGHT_NUM > 0) || (MAX_SPOT_LIGHT_NUM > 0))\n
        vec3 eTangent = normalize(CC_NormalMatrix * tangent);
        vec3 eBinormal = normalize(CC_NormalMatrix * binormal);
        vec3 eNormal = normalize(CC_NormalMatrix * normal);
    \n#endif\n

    \n#if (MAX_DIRECTIONAL_LIGHT_NUM > 0)\n
        for (int i = 0; i < MAX_DIRECTIONAL_LIGHT_NUM; ++i)
        {
            v_dirLightDirection[i].x = dot(eTangent, u_DirLightSourceDirection[i]);
            v_dirLightDirection[i].y = dot(eBinormal, u_DirLightSourceDirection[i]);
            v_dirLightDirection[i].z = dot(eNormal, u_DirLightSourceDirection[i]);
        }
    \n#endif\n

    \n#if (MAX_POINT_LIGHT_NUM > 0)\n
        for (int i = 0; i < MAX_POINT_LIGHT_NUM; ++i)
        {
            vec3 pointLightDir = u_PointLightSourcePosition[i].xyz - ePosition.xyz;
            v_vertexToPointLightDirection[i].x = dot(eTangent, pointLightDir);
            v_vertexToPointLightDirection[i].y = dot(eBinormal, pointLightDir);
            v_vertexToPointLightDirection[i].z = dot(eNormal, pointLightDir);
        }
    \n#endif\n

    \n#if (MAX_SPOT_LIGHT_NUM > 0)\n
        for (int i = 0; i < MAX_SPOT_LIGHT_NUM; ++i)
        {
            vec3 spotLightDir = u_SpotLightSourcePosition[i] - ePosition.xyz;
            v_vertexToSpotLightDirection[i].x = dot(eTangent, spotLightDir);
            v_vertexToSpotLightDirection[i].y = dot(eBinormal, spotLightDir);
            v_vertexToSpotLightDirection[i].z = dot(eNormal, spotLightDir);

            v_spotLightDirection[i].x = dot(eTangent, u_SpotLightSourceDirection[i]);
            v_spotLightDirection[i].y = dot(eBinormal, u_SpotLightSourceDirection[i]);
            v_spotLightDirection[i].z = dot(eNormal, u_SpotLightSourceDirection[i]);
        }
    \n#endif\n
\n#else\n
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
\n#endif\n

    TextureCoordOut = a_texCoord;
    TextureCoordOut.y = 1.0 - TextureCoordOut.y;
    gl_Position = CC_PMatrix * ePosition;
}

);