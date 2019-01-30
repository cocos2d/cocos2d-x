
#pragma once

#include "base/ccMacros.h"
#include "math/CCMath.h"

#include <unordered_map>
#include <vector>

NS_CC_BEGIN

namespace shaderinfos
{
    enum class VertexKey :int {

        /**Index 0 will be used as Position.*/
        VERTEX_ATTRIB_POSITION = 0,
        /**Index 1 will be used as Color.*/
        VERTEX_ATTRIB_COLOR = 1,
        /**Index 2 will be used as Tex coord unit 0.*/
        VERTEX_ATTRIB_TEX_COORD = 2,
        /**Index 3 will be used as Tex coord unit 1.*/
        VERTEX_ATTRIB_TEX_COORD1 = 3,
        /**Index 4 will be used as Tex coord unit 2.*/
        VERTEX_ATTRIB_TEX_COORD2 = 4,
        /**Index 5 will be used as Tex coord unit 3.*/
        VERTEX_ATTRIB_TEX_COORD3 = 5,
        /**Index 6 will be used as Normal.*/
        VERTEX_ATTRIB_NORMAL = 6,
        /**Index 7 will be used as Blend weight for hardware skin.*/
        VERTEX_ATTRIB_BLEND_WEIGHT = 7,
        /**Index 8 will be used as Blend index.*/
        VERTEX_ATTRIB_BLEND_INDEX = 8,
        /**Index 9 will be used as tangent.*/
        VERTEX_ATTRIB_TANGENT = 9,
        /**Index 10 will be used as Binormal.*/
        VERTEX_ATTRIB_BINORMAL = 10,
        VERTEX_ATTRIB_MAX = 11,

        // backward compatibility
        VERTEX_ATTRIB_TEX_COORDS = VERTEX_ATTRIB_TEX_COORD,

        VERTEX_ATTRIB_ERROR = -1
    };

    /**Preallocated uniform handle.*/
    enum class Uniformkey
    {
        /**Ambient color.*/
        UNIFORM_AMBIENT_COLOR,
        /**Projection matrix.*/
        UNIFORM_P_MATRIX,
        /**MultiView Projection matrix.*/
        UNIFORM_MULTIVIEW_P_MATRIX,
        /**Model view matrix.*/
        UNIFORM_MV_MATRIX,
        /**Model view projection matrix.*/
        UNIFORM_MVP_MATRIX,
        /**MultiView Model view projection matrix.*/
        UNIFORM_MULTIVIEW_MVP_MATRIX,
        /**Normal matrix.*/
        UNIFORM_NORMAL_MATRIX,
        /**Time.*/
        UNIFORM_TIME,
        /**sin(Time).*/
        UNIFORM_SIN_TIME,
        /**cos(Time).*/
        UNIFORM_COS_TIME,
        /**Random number.*/
        UNIFORM_RANDOM01,
        /** @{
        * Sampler 0-3, used for texture.
        */
        UNIFORM_SAMPLER0,
        UNIFORM_SAMPLER1,
        UNIFORM_SAMPLER2,
        UNIFORM_SAMPLER3,
        /**@}*/
        UNIFORM_MAX,
    };

    namespace shader {

        extern const char* SHADER_NAME_ETC1AS_POSITION_TEXTURE_COLOR;
        extern const char* SHADER_NAME_ETC1AS_POSITION_TEXTURE_COLOR_NO_MVP;

        extern const char* SHADER_NAME_ETC1AS_POSITION_TEXTURE_GRAY;
        extern const char* SHADER_NAME_ETC1AS_POSITION_TEXTURE_GRAY_NO_MVP;

        /**Built in shader for 2d. Support Position, Texture and Color vertex attribute.*/
        extern const char* SHADER_NAME_POSITION_TEXTURE_COLOR;
        /**Built in shader for 2d. Support Position, Texture and Color vertex attribute, but without multiply vertex by MVP matrix.*/
        extern const char* SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP;
        /**Built in shader for 2d. Support Position, Texture vertex attribute, but include alpha test.*/
        extern const char* SHADER_NAME_POSITION_TEXTURE_ALPHA_TEST;
        /**Built in shader for 2d. Support Position, Texture and Color vertex attribute, include alpha test and without multiply vertex by MVP matrix.*/
        extern const char* SHADER_NAME_POSITION_TEXTURE_ALPHA_TEST_NO_MV;
        /**Built in shader for 2d. Support Position, Color vertex attribute.*/
        extern const char* SHADER_NAME_POSITION_COLOR;
        /**Built in shader for 2d. Support Position, Color, Texture vertex attribute. texture coordinate will used as point size.*/
        extern const char* SHADER_NAME_POSITION_COLOR_TEXASPOINTSIZE;
        /**Built in shader for 2d. Support Position, Color vertex attribute, without multiply vertex by MVP matrix.*/
        extern const char* SHADER_NAME_POSITION_COLOR_NO_MVP;
        /**Built in shader for 2d. Support Position, Texture vertex attribute.*/
        extern const char* SHADER_NAME_POSITION_TEXTURE;
        /**Built in shader for 2d. Support Position, Texture vertex attribute. with a specified uniform as color*/
        extern const char* SHADER_NAME_POSITION_TEXTURE_U_COLOR;
        /**Built in shader for 2d. Support Position, Texture and Color vertex attribute. but alpha will be the multiplication of color attribute and texture.*/
        extern const char* SHADER_NAME_POSITION_TEXTURE_A8_COLOR;
        /**Built in shader for 2d. Support Position, with color specified by a uniform.*/
        extern const char* SHADER_NAME_POSITION_U_COLOR;
        /**Built in shader for draw a sector with 90 degrees with center at bottom left point.*/
        extern const char* SHADER_NAME_POSITION_LENGTH_TEXTURE_COLOR;

        /**Built in shader for ui effects */
        extern const char* SHADER_NAME_POSITION_GRAYSCALE;
        /** @{
        Built in shader for label and label with effects.
        */
        extern const char* SHADER_NAME_LABEL_NORMAL;
        extern const char* SHADER_NAME_LABEL_OUTLINE;
        extern const char* SHADER_NAME_LABEL_DISTANCEFIELD_NORMAL;
        extern const char* SHADER_NAME_LABEL_DISTANCEFIELD_GLOW;

        /**Built in shader used for 3D, support Position vertex attribute, with color specified by a uniform.*/
        extern const char* SHADER_3D_POSITION;
        /**Built in shader used for 3D, support Position and Texture vertex attribute, with color specified by a uniform.*/
        extern const char* SHADER_3D_POSITION_TEXTURE;
        /**
        Built in shader used for 3D, support Position (Skeletal animation by hardware skin) and Texture vertex attribute,
        with color specified by a uniform.
        */
        extern const char* SHADER_3D_SKINPOSITION_TEXTURE;
        /**
        Built in shader used for 3D, support Position and Normal vertex attribute, used in lighting. with color specified by a uniform.
        */
        extern const char* SHADER_3D_POSITION_NORMAL;
        /**
        Built in shader used for 3D, support Position, Normal, Texture vertex attribute, used in lighting. with color specified by a uniform.
        */
        extern const char* SHADER_3D_POSITION_NORMAL_TEXTURE;
        /**
        Built in shader used for 3D, support Position(skeletal animation by hardware skin), Normal, Texture vertex attribute,
        used in lighting. with color specified by a uniform.
        */
        extern const char* SHADER_3D_SKINPOSITION_NORMAL_TEXTURE;
        /**
        Built in shader used for 3D, support Position, Bumped Normal, Texture vertex attribute, used in lighting. with color specified by a uniform.
        */
        extern const char* SHADER_3D_POSITION_BUMPEDNORMAL_TEXTURE;
        /**
        Built in shader used for 3D, support Position(skeletal animation by hardware skin), Bumped Normal, Texture vertex attribute,
        used in lighting. with color specified by a uniform.
        */
        extern const char* SHADER_3D_SKINPOSITION_BUMPEDNORMAL_TEXTURE;
        /**
        Built in shader for particles, support Position and Texture, with a color specified by a uniform.
        */
        extern const char* SHADER_3D_PARTICLE_TEXTURE;
        /**
        Built in shader for particles, support Position, with a color specified by a uniform.
        */
        extern const char* SHADER_3D_PARTICLE_COLOR;

        /**
        Built in shader for skybox
        */
        extern const char* SHADER_3D_SKYBOX;

        /**
        Built in shader for terrain
        */
        extern const char* SHADER_3D_TERRAIN;

        /**
        Built in shader for LayerRadialGradient
        */
        extern const char* SHADER_LAYER_RADIAL_GRADIENT;

        /**
        Built in shader for camera clear
        */
        extern const char* SHADER_CAMERA_CLEAR;
        /**
        end of built shader types.
        @}
        */
    }

    namespace uniform {
        /**
        @name Built uniform names
        @{
        */
        /**Ambient Color uniform.*/
        extern const char* UNIFORM_NAME_AMBIENT_COLOR;
        /**Projection Matrix uniform.*/
        extern const char* UNIFORM_NAME_P_MATRIX;
        /**MultiView Projection Matrix uniform.*/
        extern const char* UNIFORM_NAME_MULTIVIEW_P_MATRIX;
        /**Model view matrix uniform.*/
        extern const char* UNIFORM_NAME_MV_MATRIX;
        /**Model view projection uniform.*/
        extern const char* UNIFORM_NAME_MVP_MATRIX;
        /**MultiView Model view projection uniform.*/
        extern const char* UNIFORM_NAME_MULTIVIEW_MVP_MATRIX;
        /**Normal matrix uniform.*/
        extern const char* UNIFORM_NAME_NORMAL_MATRIX;
        /**Time uniform.*/
        extern const char* UNIFORM_NAME_TIME;
        /**Sin time uniform.*/
        extern const char* UNIFORM_NAME_SIN_TIME;
        /**Cos time uniform.*/
        extern const char* UNIFORM_NAME_COS_TIME;
        /**Random number uniform.*/
        extern const char* UNIFORM_NAME_RANDOM01;
        /**
        @{ Sampler uniform 0-3, used for textures.
        */
        extern const char* UNIFORM_NAME_SAMPLER0;
        extern const char* UNIFORM_NAME_SAMPLER1;
        extern const char* UNIFORM_NAME_SAMPLER2;
        extern const char* UNIFORM_NAME_SAMPLER3;
        /**
        @}
        */
        /**Alpha test value uniform.*/
        extern const char* UNIFORM_NAME_ALPHA_TEST_VALUE;
        /**
        end of Built uniform names
        @}
        */
    }

    namespace attribute {
        /**
        @name Built Attribute names
        @{
        */
        /**Attribute color.*/
        extern const char* ATTRIBUTE_NAME_COLOR;
        /**Attribute position.*/
        extern const char* ATTRIBUTE_NAME_POSITION;
        /**@{ Attribute Texcoord 0-3.*/
        extern const char* ATTRIBUTE_NAME_TEX_COORD;
        extern const char* ATTRIBUTE_NAME_TEX_COORD1;
        extern const char* ATTRIBUTE_NAME_TEX_COORD2;
        extern const char* ATTRIBUTE_NAME_TEX_COORD3;
        /**@}*/
        /**Attribute normal.*/
        extern const char* ATTRIBUTE_NAME_NORMAL;
        /**Attribute blend weight.*/
        extern const char* ATTRIBUTE_NAME_BLEND_WEIGHT;
        /**Attribute blend index.*/
        extern const char* ATTRIBUTE_NAME_BLEND_INDEX;
        /**Attribute blend tangent.*/
        extern const char* ATTRIBUTE_NAME_TANGENT;
        /**Attribute blend binormal.*/
        extern const char* ATTRIBUTE_NAME_BINORMAL;
        /**
        end of Built Attribute names
        @}
        */
    }

    const std::vector<std::pair<const char *, VertexKey>>& getPredefinedAttributes();
    const std::string getAttributeName(const VertexKey &key);
};

NS_CC_END