// Uniforms
uniform mat4 u_worldViewProjectionMatrix;           // Matrix to transform a position to clip space.
uniform mat4 u_inverseTransposeWorldViewMatrix;     // Matrix to transform a normal to view space.
uniform mat4 u_worldViewMatrix;                     // Matrix to tranform a position to view space.
uniform vec3 u_cameraViewPosition;                      // Position of the camera in view space.



// Inputs
attribute vec4 a_position;                          // Vertex Position (x, y, z, w)
attribute vec3 a_normal;                            // Vertex Normal (x, y, z)
attribute vec2 a_texCoord;                          // Vertex Texture Coordinate (u, v)

// Outputs
varying vec3 v_normalVector;                        // NormalVector in view space.
varying vec2 v_texCoord;                            // Texture coordinate (u, v).
varying vec3 v_cameraDirection;                     // Camera direction

//refect coordinate
varying vec3 v_reflectCoord;

#ifdef SKINNING_JOINT_COUNT
attribute vec4 a_blendWeights;
attribute vec4 a_blendIndices;

// 32 4x3 matrices as an array of floats
uniform vec4 u_matrixPalette[SKINNING_JOINT_COUNT * 3];

// Common vectors.
vec4 _skinnedPosition;
vec3 _skinnedNormal;
#endif

#ifdef MAXDIRLIGHT
struct DirectionLight
{
    vec3 dir;
    vec3 color;
};
#endif

#ifdef MAXPOINTLIGHT
struct PointLight
{
    vec3 position;
    vec3 color;
    float rangeInverse;
};
#endif

#ifdef MAXSPOTLIGHT
struct SpotLight
{
    vec3 position;
    vec3 color;
    float rangeInverse;
    vec3 dir;
    float innerAngleCos;
    float outerAngleCos;
};
#endif

#ifdef MAXDIRLIGHT
uniform DirectionLight u_dirlight[MAXDIRLIGHT];
#endif
#ifdef MAXPOINTLIGHT
uniform PointLight u_pointlight[MAXPOINTLIGHT];
#endif
#ifdef MAXSPOTLIGHT
uniform SpotLight u_spotlight[MAXSPOTLIGHT];
#endif

//uniform vec3 u_nlight; // light number, u_nlight.x directional light, u_nlight.y point light, u_nlight.z spot light
#ifdef OPENGL_ES
uniform lowp int u_ndirlight;
uniform lowp int u_npointlight;
uniform lowp int u_nspotlight;
#else
uniform int u_ndirlight;
uniform int u_npointlight;
uniform int u_nspotlight;
#endif

#ifdef MAXPOINTLIGHT
varying vec4 v_vertexToPointLightDirection[MAXPOINTLIGHT];
varying vec4 v_positionWorldViewSpace;
#endif
#ifdef MAXSPOTLIGHT
varying vec3 v_vertexToSpotLightDirection[MAXSPOTLIGHT];              // Light direction w.r.t current vertex.
varying float v_spotLightAttenuation[MAXSPOTLIGHT];                   // Attenuation of spot light.
#endif

#ifdef SKINNING_JOINT_COUNT
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

void skinNormal(float blendWeight, int matrixIndex)
{
    vec3 tmp;

    tmp.x = dot(a_normal, u_matrixPalette[matrixIndex].xyz);
    tmp.y = dot(a_normal, u_matrixPalette[matrixIndex + 1].xyz);
    tmp.z = dot(a_normal, u_matrixPalette[matrixIndex + 2].xyz);

    _skinnedNormal += blendWeight * tmp;
}

vec3 getNormal()
{
    _skinnedNormal = vec3(0.0);

    // Transform normal to view space using 
    // matrix palette with four matrices used to transform a vertex.

    float blendWeight = a_blendWeights[0];
    int matrixIndex = int (a_blendIndices[0]) * 3;
    skinNormal(blendWeight, matrixIndex);

    blendWeight = a_blendWeights[1];
    matrixIndex = int(a_blendIndices[1]) * 3;
    skinNormal(blendWeight, matrixIndex);

    blendWeight = a_blendWeights[2];
    matrixIndex = int(a_blendIndices[2]) * 3;
    skinNormal(blendWeight, matrixIndex);

    blendWeight = a_blendWeights[3];
    matrixIndex = int(a_blendIndices[3]) * 3;
    skinNormal(blendWeight, matrixIndex);

    return _skinnedNormal;
}
#endif


#ifdef MAXPOINTLIGHT
void applyPointLight(vec4 position)
{
    vec4 positionWorldViewSpace = u_worldViewMatrix * position;
    v_positionWorldViewSpace = positionWorldViewSpace;//
    
    for (int i = 0; i < u_npointlight; i++) {
        vec3 lightDirection = u_pointlight[i].position - positionWorldViewSpace.xyz;
        vec4 vertexToPointLightDirection;
        vertexToPointLightDirection.xyz = lightDirection;
        
        // Attenuation
        vertexToPointLightDirection.w = 1.0 - dot(lightDirection * u_pointlight[i].rangeInverse, lightDirection * u_pointlight[i].rangeInverse);
        
        // Output light direction.
        v_vertexToPointLightDirection[i] =  vertexToPointLightDirection;
    }
    
}
#endif

#ifdef MAXSPOTLIGHT
void applySpotLight(vec4 position)
{
    // World space position.
    vec4 positionWorldViewSpace = u_worldViewMatrix * position;
    
    for (int i = 0; i < u_nspotlight; i++) {
        // Compute the light direction with light position and the vertex position.
        vec3 lightDirection = u_spotlight[i].position - positionWorldViewSpace.xyz;
        
        // Attenuation
        v_spotLightAttenuation[i] = 1.0 - dot(lightDirection * u_spotlight[i].rangeInverse, lightDirection * u_spotlight[i].rangeInverse);
        
        // Compute the light direction with light position and the vertex position.
        v_vertexToSpotLightDirection[i] = lightDirection;
    }

}
#endif

#ifdef MAXDIRLIGHT
void applyDirLight(vec4 position)
{ 
}
#endif

void main()
{
#ifdef SKINNING_JOINT_COUNT
    vec4 position = getPosition();
    vec3 normal = getNormal();
#else
    vec4 position = a_position;
    vec3 normal = a_normal;
#endif

    // Transform position to clip space.
    gl_Position = u_worldViewProjectionMatrix * position;

    // Transform normal to view space.
    mat3 normalMatrix = mat3(u_inverseTransposeWorldViewMatrix[0].xyz,
                             u_inverseTransposeWorldViewMatrix[1].xyz,
                             u_inverseTransposeWorldViewMatrix[2].xyz);
    v_normalVector = normalMatrix * normal;

    // Compute the camera direction.
    vec4 positionWorldViewSpace = u_worldViewMatrix * position;
    
    v_cameraDirection = u_cameraViewPosition - positionWorldViewSpace.xyz;

    // Apply light.
    #ifdef MAXDIRLIGHT
    if (u_ndirlight > 0)
        applyDirLight(position);
    #endif
    
    #ifdef MAXPOINTLIGHT
    if (u_npointlight > 0)
        applyPointLight(position);
    #endif
    
    #ifdef MAXSPOTLIGHT
    if (u_nspotlight > 0)
        applySpotLight(position);
    #endif

	// Pass on the texture coordinates to Fragment shader.
    v_texCoord = a_texCoord;
    
    //compute reflect
    vec3 vEyeVertex = normalize(positionWorldViewSpace.xyz / positionWorldViewSpace.w);
    vec4 vReflectCoord = vec4(reflect(vEyeVertex, v_normalVector), 1.0);
    
    v_reflectCoord = normalize(vReflectCoord.xyz);
}
