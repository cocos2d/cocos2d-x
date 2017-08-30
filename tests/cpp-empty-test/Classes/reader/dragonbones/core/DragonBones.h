#ifndef DRAGONBONES_H
#define DRAGONBONES_H

#include <cmath>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <unordered_map>
#include <tuple>
#include <functional>
#include <sstream>
#include <assert.h>

// dragonBones assert
#ifndef DRAGONBONES_ASSERT
#define DRAGONBONES_ASSERT(cond, msg) do { \
        assert(cond); \
    } while (0)
#endif

// namespace dragonBones {}
#define DRAGONBONES_NAMESPACE_BEGIN namespace dragonBones {
#define DRAGONBONES_NAMESPACE_END }

// using dragonBones namespace
#define DRAGONBONES_USING_NAME_SPACE using namespace dragonBones

/**
 * A macro to disallow the copy constructor and operator= functions
 * This should be used in the private: declarations for a class
 */
#define DRAGONBONES_DISALLOW_COPY_AND_ASSIGN(CLASS)\
    CLASS(const CLASS&);\
    void operator=(const CLASS&)\

DRAGONBONES_NAMESPACE_BEGIN

enum class TextureFormat
{
    DEFAULT, 
    RGBA8888, 
    BGRA8888, 
    RGBA4444, 
    RGB888, 
    RGB565, 
    RGBA5551
};

enum class DisplayType 
{
    Image = 0, 
    Armature = 1, 
    Mesh = 2
};

enum class ArmatureType 
{
    Armature = 0,
    MovieClip = 1,
    Stage = 2
};

enum class ExtensionType {
    FFD = 0,
    AdjustColor = 10,
    BevelFilter = 11,
    BlurFilter = 12,
    DropShadowFilter = 13,
    GlowFilter = 14,
    GradientBevelFilter = 15,
    GradientGlowFilter = 16
};

enum class EventType {
    Frame = 0,
    Sound = 1
};

enum class ActionType {
    Play = 0,
    Stop = 1,
    GotoAndPlay = 2,
    GotoAndStop = 3,
    FadeIn = 4,
    FadeOut = 5
};

enum class BlendMode 
{
    Normal = 0,
    Add = 1,
    Alpha = 2,
    Darken = 3,
    Difference = 4,
    Erase = 5,
    HardLight = 6,
    Invert = 7,
    Layer = 8,
    Lighten = 9,
    Multiply = 10,
    Overlay = 11,
    Screen = 12,
    Subtract = 13
};

const float PI = 3.14159265358979323846f;
const float PI_D = PI * 2.0f;
const float PI_H = PI * 0.5f;
const float PI_Q = PI * 0.25f;
const float ANGLE_TO_RADIAN = PI / 180.f;
const float RADIAN_TO_ANGLE = 180.f / PI;
const float SECOND_TO_MILLISECOND = 1000.f;
const float NO_TWEEN = 100.f;
// VERSION 4.7.2

template <class T>
std::string to_string(const T& value)
{
    std::ostringstream stream;
    stream << value;
    return stream.str();
}

template<class T>
inline T* mapFind(const std::map<std::string, T*>& map, const std::string& key)
{
    const auto iterator = map.find(key);
    return (iterator != map.end()) ? iterator->second : nullptr;
}

template<class T>
inline int indexOf(const std::vector<T>& vector, const T& value)
{
    for (std::size_t i = 0, l = vector.size(); i < l; ++i)
    {
        if (vector[i] == value)
        {
            return (int) i;
        }
    }
    
    return -1;
}

DRAGONBONES_NAMESPACE_END

#endif // DRAGONBONES_H
