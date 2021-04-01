set(COCOS_RENDERER_HEADER
    renderer/CCCallbackCommand.h
    renderer/CCCustomCommand.h
    renderer/CCGroupCommand.h
    renderer/CCMaterial.h
    renderer/CCMeshCommand.h
    renderer/CCPass.h
    renderer/CCPipelineDescriptor.h
    renderer/CCQuadCommand.h
    renderer/CCRenderCommand.h
    renderer/CCRenderCommandPool.h
    renderer/CCRenderState.h
    renderer/CCRenderer.h
    renderer/CCTechnique.h
    renderer/CCTexture2D.h
    renderer/CCTextureAtlas.h
    renderer/CCTextureCache.h
    renderer/CCTextureCube.h
    renderer/CCTextureUtils.h
    renderer/CCTrianglesCommand.h
    renderer/ccShaders.h

    renderer/backend/Backend.h
    renderer/backend/Buffer.h
    renderer/backend/CommandBuffer.h
    renderer/backend/DepthStencilState.h
    renderer/backend/Device.h
    renderer/backend/Program.h
    renderer/backend/ProgramCache.h
    renderer/backend/Macros.h
    renderer/backend/RenderPassDescriptor.h
    renderer/backend/RenderPipeline.h
    renderer/backend/RenderPipelineDescriptor.h
    renderer/backend/ShaderModule.h
    renderer/backend/Texture.h
    renderer/backend/Types.h
    renderer/backend/VertexLayout.h
    renderer/backend/ProgramState.h
    renderer/backend/ShaderCache.h
    renderer/backend/DeviceInfo.h
    )

set(COCOS_RENDERER_SRC
    renderer/CCCallbackCommand.cpp
    renderer/CCCustomCommand.cpp
    renderer/CCGroupCommand.cpp
    renderer/CCMaterial.cpp
    renderer/CCMeshCommand.cpp
    renderer/CCPass.cpp
    renderer/CCQuadCommand.cpp
    renderer/CCRenderCommand.cpp
    renderer/CCRenderState.cpp
    renderer/CCRenderer.cpp
    renderer/CCTechnique.cpp
    renderer/CCTexture2D.cpp
    renderer/CCTextureAtlas.cpp
    renderer/CCTextureCache.cpp
    renderer/CCTextureCube.cpp
    renderer/CCTextureUtils.cpp
    renderer/CCTrianglesCommand.cpp
    renderer/ccShaders.cpp

    renderer/backend/CommandBuffer.cpp
    renderer/backend/DepthStencilState.cpp
    renderer/backend/Device.cpp
    renderer/backend/ShaderModule.cpp
    renderer/backend/Texture.cpp
    renderer/backend/Types.cpp
    renderer/backend/VertexLayout.cpp
    renderer/backend/ProgramCache.cpp
    renderer/backend/Program.cpp
    renderer/backend/ProgramState.cpp
    renderer/backend/ShaderCache.cpp
    renderer/backend/RenderPassDescriptor.cpp
    )

if(ANDROID OR WINDOWS OR LINUX) 

list(APPEND COCOS_RENDERER_HEADER
    renderer/backend/opengl/BufferGL.h
    renderer/backend/opengl/CommandBufferGL.h
    renderer/backend/opengl/DepthStencilStateGL.h
    renderer/backend/opengl/DeviceGL.h
    renderer/backend/opengl/ProgramGL.h
    renderer/backend/opengl/RenderPipelineGL.h
    renderer/backend/opengl/ShaderModuleGL.h
    renderer/backend/opengl/TextureGL.h
    renderer/backend/opengl/UtilsGL.h
    renderer/backend/opengl/DeviceInfoGL.h
)

list(APPEND COCOS_RENDERER_SRC
    renderer/backend/opengl/BufferGL.cpp
    renderer/backend/opengl/CommandBufferGL.cpp
    renderer/backend/opengl/DepthStencilStateGL.cpp
    renderer/backend/opengl/DeviceGL.cpp
    renderer/backend/opengl/ProgramGL.cpp
    renderer/backend/opengl/RenderPipelineGL.cpp
    renderer/backend/opengl/ShaderModuleGL.cpp
    renderer/backend/opengl/TextureGL.cpp
    renderer/backend/opengl/UtilsGL.cpp
    renderer/backend/opengl/DeviceInfoGL.cpp
)

else()

list(APPEND COCOS_RENDERER_HEADER
    renderer/backend/metal/BufferMTL.h
    renderer/backend/metal/BufferManager.h
    renderer/backend/metal/CommandBufferMTL.h
    renderer/backend/metal/DepthStencilStateMTL.h
    renderer/backend/metal/DeviceMTL.h
    renderer/backend/metal/RenderPipelineMTL.h
    renderer/backend/metal/ShaderModuleMTL.h
    renderer/backend/metal/TextureMTL.h
    renderer/backend/metal/Utils.h
    renderer/backend/metal/ProgramMTL.h
    renderer/backend/metal/DeviceInfoMTL.h
)

list(APPEND COCOS_RENDERER_SRC
    renderer/backend/metal/BufferMTL.mm
    renderer/backend/metal/BufferManager.mm
    renderer/backend/metal/CommandBufferMTL.mm
    renderer/backend/metal/DepthStencilStateMTL.mm
    renderer/backend/metal/DeviceMTL.mm
    renderer/backend/metal/RenderPipelineMTL.mm
    renderer/backend/metal/ShaderModuleMTL.mm
    renderer/backend/metal/TextureMTL.mm
    renderer/backend/metal/Utils.mm
    renderer/backend/metal/ProgramMTL.mm
    renderer/backend/metal/DeviceInfoMTL.mm
)

endif()