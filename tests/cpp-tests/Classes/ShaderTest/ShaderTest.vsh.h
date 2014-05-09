#define STRINGIFY(A)  #A
static const char* shadertestvsh = R"(

attribute vec4 a_position;
                                             
void main()
{
    gl_Position = CC_MVPMatrix * a_position;
}

)";