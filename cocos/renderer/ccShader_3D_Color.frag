
const char* cc3D_Color_frag = STRINGIFY(

\n#ifdef GL_ES\n
varying lowp vec4 DestinationColor;
\n#else\n
varying vec4 DestinationColor;
\n#endif\n
uniform vec4 u_color;
varying vec4 ePosition;
varying vec3 eNormal;

void PointLight(int n, vec4 ePosition, vec3 eNormal, out vec4 intensity)
{
    if (distance(CC_LightSource[n].position, ePosition.xyz) < CC_LightSource[n].range)
    {
        vec4 p = vec4(CC_LightSource[n].position, 1.0);
        p -= ePosition;
        intensity.xyz += CC_LightSource[n].color * max(0.0, dot(normalize(p.xyz), eNormal));	
    }
    intensity.w = 1.0;
}

void DirectionalLight(int n, vec3 eNormal, out vec4 intensity)
{
    intensity.xyz += CC_LightSource[n].color * max(0.0, dot(normalize(-CC_LightSource[n].direction), eNormal));
    intensity.w = 1.0;
}

void SpotLight(int n, vec4 ePosition, vec3 eNormal, out vec4 intensity)
{
    if (distance(CC_LightSource[n].position, ePosition.xyz) < CC_LightSource[n].range)
    {
        vec3 lightDir = CC_LightSource[n].position - ePosition.xyz;
        lightDir = normalize(lightDir);
        float spotDot = dot(lightDir, normalize(-CC_LightSource[n].direction));
        float innerCos = cos(CC_LightSource[n].innerAngle);
        float outerCos = cos(CC_LightSource[n].outerAngle);
        float factor = smoothstep(outerCos, innerCos, spotDot);
        intensity.xyz += CC_LightSource[n].color * max(0.0, dot(lightDir, eNormal)) * factor;	
    }
    intensity.w = 1.0;
}

void main(void)
{
    vec3 normal = normalize(eNormal);
    vec4 intensity = vec4(0.0);
    for (int i = 0; i < CC_EnabledLightNum; ++i)
    {
        if (CC_LightSource[i].type == 0.0f)
            DirectionalLight(i, normal, intensity);
        else
        if (CC_LightSource[i].type == 1.0f)
            PointLight(i, ePosition, normal, intensity);
        else
            SpotLight(i, ePosition, normal, intensity);
    }

    if (intensity.w == 0.0)
        gl_FragColor = u_color;
    else
        gl_FragColor = u_color * (CC_AmbientColor + intensity);
}
);
