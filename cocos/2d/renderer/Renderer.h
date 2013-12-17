//
// Created by NiTe Luo on 10/31/13.
//



#ifndef __CC_RENDERER_H_
#define __CC_RENDERER_H_

#include "CCPlatformMacros.h"
#include "RenderCommand.h"
#include "CCGLProgram.h"
#include "CCGL.h"
#include <vector>
#include <stack>

#define VBO_SIZE 10500
#define DEFAULT_RENDER_QUEUE 0

NS_CC_BEGIN

typedef std::vector<RenderCommand*> RenderQueue;

struct RenderStackElement
{
    int renderQueueID;
    size_t currentIndex;
};

class Renderer : public Object
{
public:
    static Renderer* getInstance();
    static void destroyInstance();
    
    //TODO manage GLView inside Render itself
    void initGLView();
    
    //TODO support multiple viewport
    void addCommand(RenderCommand* command);
    void addCommand(RenderCommand* command, int renderQueue);
    void pushGroup(int renderQueueID);
    void popGroup();
    
    int createRenderQueue();
    void render();

protected:
    Renderer();
    ~Renderer();

    bool init();
    
    void setupIndices();
    //Setup VBO or VAO based on OpenGL extensions
    void setupBuffer();
    void setupVBOAndVAO();
    void setupVBO();
    void mapBuffers();

    void drawBatchedQuads();
    //Draw the previews queued quads and flush previous context
    void flush();

    void onBackToForeground(Object* obj);

protected:
    std::stack<int> _commandGroupStack;
    
    std::stack<RenderStackElement> _renderStack;
    std::vector<RenderQueue> _renderGroups;

    int _lastMaterialID;

    size_t _firstCommand;
    size_t _lastCommand;

    V3F_C4B_T2F_Quad _quads[VBO_SIZE];
    GLushort _indices[6 * VBO_SIZE];
    GLuint _quadVAO;
    GLuint _buffersVBO[2]; //0: vertex  1: indices

    int _numQuads;
    
    bool _glViewAssigned;
};

NS_CC_END

#endif //__CC_RENDERER_H_
