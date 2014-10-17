#pragma once

#include "pch.h"

namespace cpp_tests
{
    class HelloTriangleRenderer
    {
    public:
        HelloTriangleRenderer();
        ~HelloTriangleRenderer();
        void Draw(GLsizei width, GLsizei height);

    private:
        GLuint mProgram;
    };
}