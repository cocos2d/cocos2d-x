precision mediump float;
precision mediump int;
#define MAX_DIRECTIONAL_LIGHT_NUM 1
#define MAX_POINT_LIGHT_NUM 1
#define MAX_SPOT_LIGHT_NUM 1

#if (MAX_DIRECTIONAL_LIGHT_NUM > 0)
uniform vec3 u_DirLightSourceDirection[MAX_DIRECTIONAL_LIGHT_NUM];
#endif
#if (MAX_POINT_LIGHT_NUM > 0)
uniform vec3 u_PointLightSourcePosition[MAX_POINT_LIGHT_NUM];
#endif
#if (MAX_SPOT_LIGHT_NUM > 0)
uniform vec3 u_SpotLightSourcePosition[MAX_SPOT_LIGHT_NUM];
uniform vec3 u_SpotLightSourceDirection[MAX_SPOT_LIGHT_NUM];
#endif

uniform vec3 u_CameraPosition;

attribute vec3 a_position;
attribute vec2 a_texCoord;
attribute vec3 a_normal;
attribute vec3 a_tangent;
attribute vec3 a_binormal;
varying vec2 TextureCoordOut;

#if MAX_DIRECTIONAL_LIGHT_NUM
varying vec3 v_dirLightDirection[MAX_DIRECTIONAL_LIGHT_NUM];
varying vec3 v_dirLightReflectDirection[MAX_DIRECTIONAL_LIGHT_NUM];
#endif
#if MAX_POINT_LIGHT_NUM
varying vec3 v_vertexToPointLightDirection[MAX_POINT_LIGHT_NUM];
#endif
#if MAX_SPOT_LIGHT_NUM
varying vec3 v_vertexToSpotLightDirection[MAX_SPOT_LIGHT_NUM];
varying vec3 v_spotLightDirection[MAX_SPOT_LIGHT_NUM];
#endif

void getPositionAndNormal(out vec4 position, out vec3 normal, out vec3 tangent, out vec3 binormal)
{
    position = vec4(a_position, 1.0);
    normal = a_normal;
    tangent = a_tangent;
    binormal = a_binormal;
}
void main()
{
    vec4 position;
    vec3 normal;
    vec3 tangent;
    vec3 binormal;
    getPositionAndNormal(position, normal, tangent, binormal);
    vec4 ePosition = CC_MVMatrix * position;

#if ((MAX_DIRECTIONAL_LIGHT_NUM > 0) || (MAX_POINT_LIGHT_NUM > 0) || (MAX_SPOT_LIGHT_NUM > 0))
    vec3 eTangent = normalize(CC_NormalMatrix * tangent);
    vec3 eBinormal = normalize(CC_NormalMatrix * binormal);
    vec3 eNormal = normalize(CC_NormalMatrix * normal);
#endif

#if (MAX_DIRECTIONAL_LIGHT_NUM > 0)
    vec3 cameraDirection = normalize(ePosition.xyz - u_CameraPosition);
    for (int i = 0; i < MAX_DIRECTIONAL_LIGHT_NUM; ++i)
    {
        vec3 reflectDirection = normalize(u_DirLightSourceDirection[i] + cameraDirection);
        v_dirLightDirection[i].x = dot(eTangent, u_DirLightSourceDirection[i]);
        v_dirLightDirection[i].y = dot(eBinormal, u_DirLightSourceDirection[i]);
        v_dirLightDirection[i].z = dot(eNormal, u_DirLightSourceDirection[i]);
        v_dirLightReflectDirection[i].x = dot(eTangent, reflectDirection);
        v_dirLightReflectDirection[i].y = dot(eBinormal, reflectDirection);
        v_dirLightReflectDirection[i].z = dot(eNormal, reflectDirection);
    }
#endif

#if (MAX_POINT_LIGHT_NUM > 0)
    for (int i = 0; i < MAX_POINT_LIGHT_NUM; ++i)
    {
        vec3 pointLightDir = u_PointLightSourcePosition[i].xyz - ePosition.xyz;
        v_vertexToPointLightDirection[i].x = dot(eTangent, pointLightDir);
        v_vertexToPointLightDirection[i].y = dot(eBinormal, pointLightDir);
        v_vertexToPointLightDirection[i].z = dot(eNormal, pointLightDir);
    }
#endif

#if (MAX_SPOT_LIGHT_NUM > 0)
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
#endif

    TextureCoordOut = a_texCoord;
    TextureCoordOut.y = 1.0 - TextureCoordOut.y;
    gl_Position = CC_PMatrix * ePosition;
}
