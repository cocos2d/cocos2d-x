/****************************************************************************
 Copyright (c) 2018-2019 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
 

const char* CC3D_colorNormalTexture_frag = R"(

#if (MAX_DIRECTIONAL_LIGHT_NUM > 0)
uniform vec3 u_DirLightSourceColor[MAX_DIRECTIONAL_LIGHT_NUM];
uniform vec3 u_DirLightSourceDirection[MAX_DIRECTIONAL_LIGHT_NUM];
#endif
#if (MAX_POINT_LIGHT_NUM > 0)
uniform vec3 u_PointLightSourceColor[MAX_POINT_LIGHT_NUM];
uniform float u_PointLightSourceRangeInverse[MAX_POINT_LIGHT_NUM];
#endif
#if (MAX_SPOT_LIGHT_NUM > 0)
uniform vec3 u_SpotLightSourceColor[MAX_SPOT_LIGHT_NUM];
uniform vec3 u_SpotLightSourceDirection[MAX_SPOT_LIGHT_NUM];
uniform float u_SpotLightSourceInnerAngleCos[MAX_SPOT_LIGHT_NUM];
uniform float u_SpotLightSourceOuterAngleCos[MAX_SPOT_LIGHT_NUM];
uniform float u_SpotLightSourceRangeInverse[MAX_SPOT_LIGHT_NUM];
#endif
uniform vec3 u_AmbientLightSourceColor;

#ifdef GL_ES
varying mediump vec2 TextureCoordOut;

#ifdef USE_NORMAL_MAPPING
#if MAX_DIRECTIONAL_LIGHT_NUM
varying mediump vec3 v_dirLightDirection[MAX_DIRECTIONAL_LIGHT_NUM];
#endif
#endif
#if MAX_POINT_LIGHT_NUM
varying mediump vec3 v_vertexToPointLightDirection[MAX_POINT_LIGHT_NUM];
#endif
#if MAX_SPOT_LIGHT_NUM
varying mediump vec3 v_vertexToSpotLightDirection[MAX_SPOT_LIGHT_NUM];
#ifdef USE_NORMAL_MAPPING
varying mediump vec3 v_spotLightDirection[MAX_SPOT_LIGHT_NUM];
#endif
#endif

#ifndef USE_NORMAL_MAPPING
#if ((MAX_DIRECTIONAL_LIGHT_NUM > 0) || (MAX_POINT_LIGHT_NUM > 0) || (MAX_SPOT_LIGHT_NUM > 0))
varying mediump vec3 v_normal;
#endif
#endif

#else

varying vec2 TextureCoordOut;

#ifdef USE_NORMAL_MAPPING
#if MAX_DIRECTIONAL_LIGHT_NUM
varying vec3 v_dirLightDirection[MAX_DIRECTIONAL_LIGHT_NUM];
#endif
#endif
#if MAX_POINT_LIGHT_NUM
varying vec3 v_vertexToPointLightDirection[MAX_POINT_LIGHT_NUM];
#endif
#if MAX_SPOT_LIGHT_NUM
varying vec3 v_vertexToSpotLightDirection[MAX_SPOT_LIGHT_NUM];
#ifdef USE_NORMAL_MAPPING
varying vec3 v_spotLightDirection[MAX_SPOT_LIGHT_NUM];
#endif
#endif

#ifndef USE_NORMAL_MAPPING
#if ((MAX_DIRECTIONAL_LIGHT_NUM > 0) || (MAX_POINT_LIGHT_NUM > 0) || (MAX_SPOT_LIGHT_NUM > 0))
varying vec3 v_normal;
#endif
#endif

#endif

uniform vec4 u_color;
#ifdef USE_NORMAL_MAPPING
uniform sampler2D u_normalTex;
#endif

uniform sampler2D u_texture;

vec3 computeLighting(vec3 normalVector, vec3 lightDirection, vec3 lightColor, float attenuation)
{
    float diffuse = max(dot(normalVector, lightDirection), 0.0);
    vec3 diffuseColor = lightColor  * diffuse * attenuation;

    return diffuseColor;
}

void main(void)
{

#ifdef USE_NORMAL_MAPPING
    #if ((MAX_DIRECTIONAL_LIGHT_NUM > 0) || (MAX_POINT_LIGHT_NUM > 0) || (MAX_SPOT_LIGHT_NUM > 0))
        vec3 normal  = normalize(2.0 * texture2D(u_normalTex, TextureCoordOut).xyz - 1.0);
    #endif
#else
    #if ((MAX_DIRECTIONAL_LIGHT_NUM > 0) || (MAX_POINT_LIGHT_NUM > 0) || (MAX_SPOT_LIGHT_NUM > 0))
        vec3 normal  = normalize(v_normal);
    #endif
#endif

    vec4 combinedColor = vec4(u_AmbientLightSourceColor, 1.0);

    // Directional light contribution
#if (MAX_DIRECTIONAL_LIGHT_NUM > 0)
    for (int i = 0; i < MAX_DIRECTIONAL_LIGHT_NUM; ++i)
    {
#ifdef USE_NORMAL_MAPPING
        vec3 lightDirection = normalize(v_dirLightDirection[i] * 2.0);
#else
        vec3 lightDirection = normalize(u_DirLightSourceDirection[i] * 2.0);
#endif
        combinedColor.xyz += computeLighting(normal, -lightDirection, u_DirLightSourceColor[i], 1.0);
    }
#endif

    // Point light contribution
#if (MAX_POINT_LIGHT_NUM > 0)
    for (int i = 0; i < MAX_POINT_LIGHT_NUM; ++i)
    {
        vec3 ldir = v_vertexToPointLightDirection[i] * u_PointLightSourceRangeInverse[i];
        float attenuation = clamp(1.0 - dot(ldir, ldir), 0.0, 1.0);
        combinedColor.xyz += computeLighting(normal, normalize(v_vertexToPointLightDirection[i]), u_PointLightSourceColor[i], attenuation);
    }
#endif

    // Spot light contribution
#if (MAX_SPOT_LIGHT_NUM > 0)
    for (int i = 0; i < MAX_SPOT_LIGHT_NUM; ++i)
    {
        // Compute range attenuation
        vec3 ldir = v_vertexToSpotLightDirection[i] * u_SpotLightSourceRangeInverse[i];
        float attenuation = clamp(1.0 - dot(ldir, ldir), 0.0, 1.0);
        vec3 vertexToSpotLightDirection = normalize(v_vertexToSpotLightDirection[i]);

#ifdef USE_NORMAL_MAPPING
        vec3 spotLightDirection = normalize(v_spotLightDirection[i] * 2.0);
#else
        vec3 spotLightDirection = normalize(u_SpotLightSourceDirection[i] * 2.0);
#endif

        // "-lightDirection" is used because light direction points in opposite direction to spot direction.
        float spotCurrentAngleCos = dot(spotLightDirection, -vertexToSpotLightDirection);

        // Apply spot attenuation
        attenuation *= smoothstep(u_SpotLightSourceOuterAngleCos[i], u_SpotLightSourceInnerAngleCos[i], spotCurrentAngleCos);
        attenuation = clamp(attenuation, 0.0, 1.0);
        combinedColor.xyz += computeLighting(normal, vertexToSpotLightDirection, u_SpotLightSourceColor[i], attenuation);
    }
#endif

#if ((MAX_DIRECTIONAL_LIGHT_NUM > 0) || (MAX_POINT_LIGHT_NUM > 0) || (MAX_SPOT_LIGHT_NUM > 0))
    gl_FragColor = texture2D(u_texture, TextureCoordOut) * u_color * combinedColor;
#else
    gl_FragColor = texture2D(u_texture, TextureCoordOut) * u_color;
#endif

}
)";
