#include "Program.h"

CC_BACKEND_BEGIN

Program::Program(const std::string& vs, const std::string& fs)
: _vertexShader(vs)
, _fragmentShader(fs)
{
}

CC_BACKEND_END
