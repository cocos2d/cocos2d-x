// A constant buffer that stores the three basic column-major matrices for composing geometry.
cbuffer ModelViewProjectionConstantBuffer : register(b0)
{
	matrix model;
	matrix view;
	matrix projection;
};

// Per-vertex data used as input to the vertex shader.
struct VertexShaderInput
{
	float3 pos : POSITION;
	float3 color : COLOR0;
};

// Per-pixel color data passed through the pixel shader.
struct PixelShaderInput
{
	float4 pos : SV_POSITION;
	float3 color : COLOR0;
};

// Simple shader to do vertex processing on the GPU.
PixelShaderInput main(VertexShaderInput input)
{
	PixelShaderInput output;
	float4 pos = float4(input.pos, 1.0f);

		// Transform the vertex position into projected space.
		pos = mul(pos, model);
	pos = mul(pos, view);
	pos = mul(pos, projection);
	output.pos = pos;

	// Pass the color through without modification.
	output.color = input.color;

	return output;
}

/*
const char* cc3D_PositionTex_vert = STRINGIFY(

attribute vec4 a_position;
attribute vec2 a_texCoord;

varying vec2 TextureCoordOut;

void main(void)
{
    gl_Position = CC_MVPMatrix * a_position;
    TextureCoordOut = a_texCoord;
    TextureCoordOut.y = 1.0 - TextureCoordOut.y;
}
);

const char* cc3D_SkinPositionTex_vert = STRINGIFY(
attribute vec4 a_position;

attribute vec4 a_blendWeight;
attribute vec4 a_blendIndex;

attribute vec2 a_texCoord;

const int SKINNING_JOINT_COUNT = 60;
// Uniforms
uniform vec4 u_matrixPalette[SKINNING_JOINT_COUNT * 3];

// Varyings
varying vec2 TextureCoordOut;

vec4 _skinnedPosition;

vec4 getPosition()
{
    vec4 matrixPalette1 = vec4(0.0);
    vec4 matrixPalette2 = vec4(0.0);
    vec4 matrixPalette3 = vec4(0.0);
    
    float blendWeight = a_blendWeight[0];
    int matrixIndex = int (a_blendIndex[0]) * 3;
    matrixPalette1 += u_matrixPalette[matrixIndex] * blendWeight;
    matrixPalette2 += u_matrixPalette[matrixIndex + 1] * blendWeight;
    matrixPalette3 += u_matrixPalette[matrixIndex + 2] * blendWeight;
    
    blendWeight = a_blendWeight[1];
    matrixIndex = int(a_blendIndex[1]) * 3;
    matrixPalette1 += u_matrixPalette[matrixIndex] * blendWeight;
    matrixPalette2 += u_matrixPalette[matrixIndex + 1] * blendWeight;
    matrixPalette3 += u_matrixPalette[matrixIndex + 2] * blendWeight;
    
    blendWeight = a_blendWeight[2];
    matrixIndex = int(a_blendIndex[2]) * 3;
    matrixPalette1 += u_matrixPalette[matrixIndex] * blendWeight;
    matrixPalette2 += u_matrixPalette[matrixIndex + 1] * blendWeight;
    matrixPalette3 += u_matrixPalette[matrixIndex + 2] * blendWeight;
    
    blendWeight = a_blendWeight[3];
    matrixIndex = int(a_blendIndex[3]) * 3;
    matrixPalette1 += u_matrixPalette[matrixIndex] * blendWeight;
    matrixPalette2 += u_matrixPalette[matrixIndex + 1] * blendWeight;
    matrixPalette3 += u_matrixPalette[matrixIndex + 2] * blendWeight;

    _skinnedPosition.x = dot(a_position, matrixPalette1);
    _skinnedPosition.y = dot(a_position, matrixPalette2);
    _skinnedPosition.z = dot(a_position, matrixPalette3);
    _skinnedPosition.w = a_position.w;
    
    return _skinnedPosition;
}

void main()
{
    vec4 position = getPosition();
    gl_Position = CC_MVPMatrix * position;
    
    TextureCoordOut = a_texCoord;
    TextureCoordOut.y = 1.0 - TextureCoordOut.y;
}

);
*/