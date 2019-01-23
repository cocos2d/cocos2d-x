#include "ShaderModuleMTL.h"
#include "DeviceMTL.h"

#include "glsl_optimizer.h"

CC_BACKEND_BEGIN

ShaderModuleMTL::ShaderModuleMTL(id<MTLDevice> mtlDevice, ShaderStage stage, const std::string& source)
: ShaderModule(stage)
{
    // Convert GLSL shader to metal shader
    //TODO: don't crreate/destroy ctx every time.
    glslopt_ctx* ctx = glslopt_initialize(kGlslTargetMetal);
    glslopt_shader_type shaderType = stage == ShaderStage::VERTEX ? kGlslOptShaderVertex : kGlslOptShaderFragment;
    glslopt_shader* glslShader = glslopt_optimize(ctx, shaderType, source.c_str(), 0);
    if (!glslShader)
    {
        NSLog(@"Can not translate GLSL shader to metal shader:");
        NSLog(@"%s", source.c_str());
        return;
    }
    
    const char* metalShader = glslopt_get_raw_output(glslShader);
    if (!metalShader)
    {
        NSLog(@"Can not get metal shader:");
        NSLog(@"%s", source.c_str());
        glslopt_cleanup(ctx);
        return;
    }
    
//    NSLog(@"%s", metalShader);
    
    parseUniform(mtlDevice, glslShader);
    parseTexture(mtlDevice, glslShader);
    
    NSString* shader = [NSString stringWithUTF8String:metalShader];
    NSError* error;
    id<MTLLibrary> library = [mtlDevice newLibraryWithSource:shader
                                                     options:nil
                                                       error:&error];
    if (!library)
    {
        NSLog(@"Can not compile metal shader: %@", error);
        NSLog(@"%s", metalShader);
        glslopt_shader_delete(glslShader);
        glslopt_cleanup(ctx);
        return;
    }
    
    if (ShaderStage::VERTEX == stage)
        _mtlFunction = [library newFunctionWithName:@"xlatMtlMain1"];
    else
        _mtlFunction = [library newFunctionWithName:@"xlatMtlMain2"];
    if (!_mtlFunction)
    {
        NSLog(@"metal shader is ---------------");
        NSLog(@"%s", metalShader);
        assert(false);
    }
    
    glslopt_shader_delete(glslShader);
    glslopt_cleanup(ctx);
}

ShaderModuleMTL::~ShaderModuleMTL()
{
    [_mtlFunction release];
}

void ShaderModuleMTL::parseUniform(id<MTLDevice> mtlDevice, glslopt_shader* shader)
{
    const int uniformCount = glslopt_shader_get_uniform_count(shader);
    const int uniformSize = glslopt_shader_get_uniform_total_size(shader);
    if (uniformSize > 0)
    {
        std::shared_ptr<uint8_t> sp(new uint8_t[uniformSize], [](uint8_t *p) { delete[] p; });
        _uniformBuffer = sp;
    }
    
    for (int i = 0; i < uniformCount; ++i)
    {
        int nextLocation = -1;
        const char* parName;
        glslopt_basic_type parType;
        glslopt_precision parPrec;
        int parVecSize, parMatSize, parArrSize, location;
        if( i+1 < uniformCount)
        {
            glslopt_shader_get_uniform_desc(shader, i+1, &parName, &parType, &parPrec, &parVecSize, &parMatSize, &parArrSize, &location);
            nextLocation = location;
        }
        else
        {
            nextLocation = uniformSize;
        }
        
        glslopt_shader_get_uniform_desc(shader, i, &parName, &parType, &parPrec, &parVecSize, &parMatSize, &parArrSize, &location);
        
        parArrSize = (parArrSize > 0) ? parArrSize : 1;
        UniformInfo uniform;
        uniform.count = parArrSize;
        uniform.location = location;
        uniform.isArray = parArrSize;
        uniform.bufferSize = nextLocation - location;
        _uniformInfos[parName] = uniform;
        
        _maxLocation = _maxLocation < location ? (location + 1) : _maxLocation;
    }
}

void ShaderModuleMTL::parseTexture(id<MTLDevice> mtlDevice, glslopt_shader* shader)
{
    const int textureCount = glslopt_shader_get_texture_count(shader);
    for (int i = 0; i < textureCount; ++i)
    {
        const char* parName;
        glslopt_basic_type parType;
        glslopt_precision parPrec;
        int parVecSize, parMatSize, parArrSize, location;
        glslopt_shader_get_texture_desc(shader, i, &parName, &parType, &parPrec, &parVecSize, &parMatSize, &parArrSize, &location);
        
        UniformInfo uniform;
        uniform.count = parArrSize;
        uniform.location = location;
        uniform.isArray = parArrSize > 0;
        _uniformInfos[parName] = uniform;
    }
}

CC_BACKEND_END
