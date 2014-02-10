// Uniforms
uniform mat4 u_worldViewProjectionMatrix;       // Matrix to transform a position to clip space.
uniform mat4 u_worldMatrix;  
uniform mat4 u_inverseTransposeWorldMatrix;  
uniform vec3 u_cameraWorldPosition;

//fog parameter
uniform vec4 u_fogparam; // .x, .y, .z, .w stand for fog density, fog start, fog end, fog type. fog type 0, no fog, fog type 1 linear fog, fog type 2 exp fog, fog type 3 exp2 fog

// Inputs
attribute vec4 a_position;                      // Vertex Position (x, y, z, w).
attribute vec2 a_texCoord;                      // Vertex Texture Coordinate (u, v).
attribute vec3 a_normal;

//#ifdef FOG
varying float v_fogFactor;              //fog factor

//#endif

#ifdef NORMALMAP
#define TANGENT
#define PIXELLIGHT
#endif

#ifdef MAXPOINTLIGHT
#define PIXELLIGHT
#endif

#ifdef TANGENT
attribute vec3 a_tangent;
attribute vec3 a_binormal;
#define NORMAL_ENABLE
#endif

#ifdef SPECULAR
#define PIXELLIGHT
#endif

// Outputs
varying vec2 v_texCoord;                        // Texture coordinate (u, v).

// Only support ONE directional light
#ifdef MAXDIRLIGHT

#define NORMAL_ENABLE

struct DirectionLight
{
    vec3 dir;
    vec3 color;
};

uniform DirectionLight u_dirlight[1];

#ifdef OPENGL_ES
uniform lowp int u_ndirlight;
#else
uniform int u_ndirlight;
#endif

#endif  // MAXDIRLIGHT

#ifdef PIXELLIGHT
varying vec3 v_normal;
varying vec3 v_lightDir;
varying vec3 v_cameraDir;
#endif

varying vec4 v_lightColor; //.a : n dot l




#ifdef MAXANIMLIGHT
uniform vec3 u_animLightAxisU;
uniform vec3 u_animLightAxisV;
uniform vec3 u_animLightPos;
uniform vec4 u_animLightTexOffset;
uniform vec4 u_animLightTexRotScale1;
uniform vec4 u_animLightTexRotScale2;

varying vec2 v_texCoordLight;
varying vec2 v_texCoordLight2;
#endif

#ifdef SHADOWMAP

uniform mat4 u_shadowMatrix;  
varying vec4 v_texCoordShadow;

#endif

#ifdef MAXPOINTLIGHT
struct PointLight
{
    vec3 position;
    vec3 color;
    float rangeInverse;
};

#ifdef OPENGL_ES
uniform lowp int u_npointlight;
#else
uniform int u_npointlight;
#endif
uniform PointLight u_pointlight[MAXPOINTLIGHT];
//uniform mat4 u_worldViewMatrix;
varying vec4 v_vertexToPointLightDirection[MAXPOINTLIGHT];
#endif

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

void skinNormal(vec3 normal, float blendWeight, int matrixIndex)
{
    vec3 tmp;

    tmp.x = dot(normal, u_matrixPalette[matrixIndex].xyz);
    tmp.y = dot(normal, u_matrixPalette[matrixIndex + 1].xyz);
    tmp.z = dot(normal, u_matrixPalette[matrixIndex + 2].xyz);

    _skinnedNormal += blendWeight * tmp;
}

vec3 getNormalVector(vec3 v)
{
    _skinnedNormal = vec3(0.0);

    // Transform normal to view space using 
    // matrix palette with four matrices used to transform a vertex.

    float blendWeight = a_blendWeights[0];
    int matrixIndex = int (a_blendIndices[0]) * 3;
    skinNormal(v, blendWeight, matrixIndex);

    blendWeight = a_blendWeights[1];
    matrixIndex = int(a_blendIndices[1]) * 3;
    skinNormal(v, blendWeight, matrixIndex);

    blendWeight = a_blendWeights[2];
    matrixIndex = int(a_blendIndices[2]) * 3;
    skinNormal(v, blendWeight, matrixIndex);

    blendWeight = a_blendWeights[3];
    matrixIndex = int(a_blendIndices[3]) * 3;
    skinNormal(v, blendWeight, matrixIndex);

    return _skinnedNormal;
}

vec3 getNormal()
{
	return getNormalVector(a_normal);
}

#ifdef TANGENT
vec3 getTangent()
{
    return getNormalVector(a_tangent);
}

vec3 getBinormal()
{
    return getNormalVector(a_binormal);
}
#endif

#else

vec4 getPosition()
{
    return a_position;    
}

vec3 getNormal()
{
    return a_normal;    
}

#ifdef TANGENT
vec3 getTangent()
{
    return a_tangent;
}

vec3 getBinormal()
{
    return a_binormal;
}
#endif

#endif

#ifdef MAXPOINTLIGHT
void applyPointLight(vec4 position)
{
    vec4 positionWorldSpace = u_worldMatrix * position;
    
    for (int i = 0; i < u_npointlight; i++) {
        //vec3 lightDirection = u_pointlight[i].position - positionWorldViewSpace.xyz;
        vec3 lightDirection = u_pointlight[i].position - positionWorldSpace.xyz;
        vec4 vertexToPointLightDirection;
        vertexToPointLightDirection.xyz = -lightDirection;
        
        // Attenuation
        vertexToPointLightDirection.w = 1.0 - dot(lightDirection * u_pointlight[i].rangeInverse, lightDirection * u_pointlight[i].rangeInverse);
        
        //vertexToPointLightDirection.w = max(0.0, vertexToPointLightDirection.w);
        // Output light direction.
        v_vertexToPointLightDirection[i] =  vertexToPointLightDirection;
    }
    
}
#endif

void main()
{
    vec4 position = getPosition();

    // Transform position to clip space.
    gl_Position = u_worldViewProjectionMatrix * position;

	vec4 worldPos = (u_worldMatrix * position);

    // Pass on texture coordinate to fragment shader.
    v_texCoord = a_texCoord;

	vec3 normal = getNormal();
	vec3 worldNormal = (u_inverseTransposeWorldMatrix * vec4(normal, 0.0)).xyz;
	worldNormal = normalize(worldNormal);
#ifdef NORMAL_ENABLE
	
	
#ifdef TANGENT
	vec3 tangent = getTangent();
	vec3 worldTangent = (u_inverseTransposeWorldMatrix * vec4(tangent, 0.0)).xyz;
	worldTangent = normalize(worldTangent);

	vec3 binormal = getBinormal();
	vec3 worldBinormal = (u_inverseTransposeWorldMatrix * vec4(binormal, 0.0)).xyz;
	worldBinormal = normalize(worldBinormal);

	mat3 matTangent = mat3(worldTangent.x, worldBinormal.x, worldNormal.x,
                           worldTangent.y, worldBinormal.y, worldNormal.y,
                           worldTangent.z, worldBinormal.z, worldNormal.z);
#endif

#endif
	
#ifdef MAXDIRLIGHT
#ifdef PIXELLIGHT
	
	v_normal = worldNormal;
	v_cameraDir = normalize(u_cameraWorldPosition - worldPos.xyz);
	if (u_ndirlight > 0)
	{
		v_lightDir = -u_dirlight[0].dir;
	}
	else
	{
		v_lightDir = vec3(0, 0, 0);
	}
	
#ifdef TANGENT
	v_cameraDir = matTangent * v_cameraDir;
	v_lightDir = matTangent * v_lightDir;
#endif

#endif
	if (u_ndirlight > 0)
	{
		v_lightColor = vec4(u_dirlight[0].color, -dot(worldNormal, u_dirlight[0].dir));
	}
	else
	{
		v_lightColor = vec4(1.0, 1.0, 1.0, 1.0);
	}
#endif

#ifdef MAXPOINTLIGHT
#ifdef PIXELLIGHT
	
	v_normal = worldNormal;
	v_cameraDir = normalize(u_cameraWorldPosition - worldPos.xyz);
	
	
#ifdef TANGENT
	v_cameraDir = matTangent * v_cameraDir;
#endif

#endif
#endif
	
#ifdef SHADOWMAP
	v_texCoordShadow = u_shadowMatrix * worldPos;
#endif
	
#ifdef MAXANIMLIGHT
	// compute light texture coordinate
	vec3 posToLight = worldPos.xyz - u_animLightPos;
	vec2 texCoordLight = vec2(dot(u_animLightAxisU, posToLight), dot(u_animLightAxisV, posToLight));
	v_texCoordLight = texCoordLight;
	v_texCoordLight2 = texCoordLight;
	v_texCoordLight = vec2(dot(u_animLightTexRotScale1.xy, v_texCoordLight), dot(u_animLightTexRotScale1.zw, v_texCoordLight)) + u_animLightTexOffset.xy;
	v_texCoordLight2 = vec2(dot(u_animLightTexRotScale2.xy, v_texCoordLight2), dot(u_animLightTexRotScale2.zw, v_texCoordLight2)) + u_animLightTexOffset.zw;	
#endif
	
	#ifdef MAXPOINTLIGHT
    if (u_npointlight > 0)
        applyPointLight(position);
  #endif
  
  if (u_fogparam.w == 0.0)// no fog
 			return;
  if (u_fogparam.w == 1.0)// linear fog
  {
  	 	 float z = gl_Position.z;//(u_worldViewMatrix * position).z;
       v_fogFactor = (u_fogparam.z - z) / (u_fogparam.z - u_fogparam.y);
       v_fogFactor = clamp(v_fogFactor, 0.0, 1.0); 
  }
  else if (u_fogparam.w == 2.0) // exp fog
  {
   		 float z = gl_Position.z;//(u_worldViewMatrix * position).z;
       const float LOG2 = 1.442695;
       v_fogFactor = exp2( -u_fogparam.x * 
				   z * 
				   LOG2 );
       v_fogFactor = clamp(v_fogFactor, 0.0, 1.0); 
  }
  else if (u_fogparam.w == 3.0) // exp2 fog
  {
       float z = gl_Position.z;//(u_worldViewMatrix * position).z;
       const float LOG2 = 1.442695;
       v_fogFactor = exp2( -u_fogparam.x * 
				   u_fogparam.x * 
				   z * 
				   z * 
				   LOG2 );
       v_fogFactor = clamp(v_fogFactor, 0.0, 1.0); 
  }
  
}
