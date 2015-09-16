attribute vec3 a_position;

attribute vec4 a_blendWeight;
attribute vec4 a_blendIndex;

attribute vec2 a_texCoord;

const int SKINNING_JOINT_COUNT = 8;
// Uniforms
uniform vec4 u_matrixPalette[SKINNING_JOINT_COUNT * 3];

// Varyings
varying vec2 TextureCoordOut;

struct SSkinningTransform {
    vec4 row_one;
    vec4 row_two;
    vec4 row_three;
};

SSkinningTransform GenerateSkinningTransform() {
    SSkinningTransform skinning_transform;
    lowp float blendWeight = a_blendWeight[0];

    int matrixIndex = int (a_blendIndex[0]) * 3;
    skinning_transform.row_one = u_matrixPalette[matrixIndex] * blendWeight;
    skinning_transform.row_two = u_matrixPalette[matrixIndex + 1] * blendWeight;
    skinning_transform.row_three = u_matrixPalette[matrixIndex + 2] * blendWeight;

    blendWeight = a_blendWeight[1];
    if (blendWeight > 0.0) {
        matrixIndex = int(a_blendIndex[1]) * 3;
        skinning_transform.row_one += u_matrixPalette[matrixIndex] * blendWeight;
        skinning_transform.row_two += u_matrixPalette[matrixIndex + 1] * blendWeight;
        skinning_transform.row_three += u_matrixPalette[matrixIndex + 2] * blendWeight;
        blendWeight = a_blendWeight[2];
        
        if (blendWeight > 0.0) {
            matrixIndex = int(a_blendIndex[2]) * 3;
            skinning_transform.row_one += u_matrixPalette[matrixIndex] * blendWeight;
            skinning_transform.row_two += u_matrixPalette[matrixIndex + 1] * blendWeight;
            skinning_transform.row_three += u_matrixPalette[matrixIndex + 2] * blendWeight;
            blendWeight = a_blendWeight[3];
            
            if (blendWeight > 0.0) {
                matrixIndex = int(a_blendIndex[3]) * 3;
                skinning_transform.row_one += u_matrixPalette[matrixIndex] * blendWeight;
                skinning_transform.row_two += u_matrixPalette[matrixIndex + 1] * blendWeight;
                skinning_transform.row_three += u_matrixPalette[matrixIndex + 2] * blendWeight;
            }
        }
    }
    return skinning_transform;
}

vec3 SkinnedVector(vec3 input_vector, SSkinningTransform skinning_transform) {
    vec3 skinned_vector;
    skinned_vector.x = dot(vec4(input_vector, 1.0), skinning_transform.row_one);
    skinned_vector.y = dot(vec4(input_vector, 1.0), skinning_transform.row_two);
    skinned_vector.z = dot(vec4(input_vector, 1.0), skinning_transform.row_three);
    return skinned_vector;
}

void main()
{
    SSkinningTransform skinning_transform = GenerateSkinningTransform();
    gl_Position = CC_MVPMatrix * vec4(SkinnedVector(a_position, skinning_transform), 1.0);
    
    TextureCoordOut = a_texCoord;
    TextureCoordOut.y = 1.0 - TextureCoordOut.y;
}
