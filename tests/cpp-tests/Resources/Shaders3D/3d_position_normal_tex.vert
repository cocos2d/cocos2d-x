#if (MAX_POINT_LIGHT_NUM > 0)
uniform vec3 u_PointLightSourcePosition[MAX_POINT_LIGHT_NUM];
#endif
#if (MAX_SPOT_LIGHT_NUM > 0)
uniform vec3 u_SpotLightSourcePosition[MAX_SPOT_LIGHT_NUM];
#endif

attribute vec4 a_position;
attribute vec2 a_texCoord;
attribute vec3 a_normal;
varying vec2 TextureCoordOut;

#if MAX_POINT_LIGHT_NUM
varying vec3 v_vertexToPointLightDirection[MAX_POINT_LIGHT_NUM];
#endif
#if MAX_SPOT_LIGHT_NUM
varying vec3 v_vertexToSpotLightDirection[MAX_SPOT_LIGHT_NUM];
#endif
#if ((MAX_DIRECTIONAL_LIGHT_NUM > 0) || (MAX_POINT_LIGHT_NUM > 0) || (MAX_SPOT_LIGHT_NUM > 0))
varying vec3 v_normal;
#endif

void main(void)
{
    vec4 ePosition = CC_MVMatrix * a_position;
#if (MAX_POINT_LIGHT_NUM > 0)
    for (int i = 0; i < MAX_POINT_LIGHT_NUM; ++i)
    {
        v_vertexToPointLightDirection[i] = u_PointLightSourcePosition[i].xyz - ePosition.xyz;
    }
#endif

#if (MAX_SPOT_LIGHT_NUM > 0)
    for (int i = 0; i < MAX_SPOT_LIGHT_NUM; ++i)
    {
        v_vertexToSpotLightDirection[i] = u_SpotLightSourcePosition[i] - ePosition.xyz;
    }
#endif
        
#if ((MAX_DIRECTIONAL_LIGHT_NUM > 0) || (MAX_POINT_LIGHT_NUM > 0) || (MAX_SPOT_LIGHT_NUM > 0))
    v_normal = CC_NormalMatrix * a_normal;
#endif

    TextureCoordOut = a_texCoord;
    TextureCoordOut.y = 1.0 - TextureCoordOut.y;
    gl_Position = CC_PMatrix * ePosition;
}

