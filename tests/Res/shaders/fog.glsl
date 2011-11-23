#define OGL_LINEAR      9729    //0x2601
#define OGL_EXP         2048    //0x0800
#define OGL_EXP2        2049    //0x0801
#if !defined(FOG_MODE)
    #define FOG_MODE -1
#endif
uniform int u_fogMode;
uniform float u_fogDensity;
uniform float u_fogStart;
uniform float u_fogEnd;
float calcFogLinear(float distanceToEye);
float calcFogExp(float distanceToEye);
float calcFogExp2(float distanceToEye);
float calcFogFactor(float distanceToEye)
{
    float fogFactor;
#if FOG_MODE == OGL_LINEAR
    fogFactor = calcFogLinear(distanceToEye);
#elif FOG_MODE == OGL_EXP
    fogFactor = calcFogExp(distanceToEye);
#elif FOG_MODE == OGL_EXP2
    fogFactor = calcFogExp2(distanceToEye);
#elif FOG_MODE == -1
    if (u_fogMode == OGL_LINEAR) {
        fogFactor = calcFogLinear(distanceToEye);
    } else if (u_fogMode == OGL_EXP) {
        fogFactor = calcFogExp(distanceToEye);
    } else {
        fogFactor = calcFogExp2(distanceToEye);
    }
#endif  
    return fogFactor;
}
float calcFogLinear(float distanceToEye)
{
    float f = (u_fogEnd - distanceToEye) / (u_fogEnd - u_fogStart);
    return clamp(f, c_zerof, c_onef);
}
float calcFogExp(float distanceToEye)
{
    float f = exp(-(distanceToEye * u_fogDensity));
    return clamp(f, c_zerof, c_onef);
}
float calcFogExp2(float distanceToEye)
{
    float f = distanceToEye * u_fogDensity;
    f = exp(-(f*f));
    return clamp(f, c_zerof, c_onef);
}
