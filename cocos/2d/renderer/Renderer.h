//
// Created by NiTe Luo on 10/31/13.
//



#ifndef __CCRENDERER_H_
#define __CCRENDERER_H_

#include "CCPlatformMacros.h"
#include "CCEGLView.h"
#include "RenderCommand.h"
#include "CCGLProgram.h"
#include "QuadCommand.h"

#define VBO_SIZE 64

NS_CC_BEGIN
using namespace std;

class Renderer : public Object
{
public:
    static Renderer* getInstance();
    static void destroyInstance();

    //TODO support multiple viewport
    void addRenderCommand(RenderCommand* command);
    void render();

protected:
    Renderer();
    ~Renderer();

    bool init();
    void setupIndices();
    void setupVBOAndVAO();

    void batchQuads(QuadCommand* cmd);
    void drawQuads();

protected:
    vector<RenderCommand*> _renderQueue;
    int _lastMaterialID;


    V3F_C4B_T2F_Quad*_quads;
    GLushort* _indices;
    GLuint _VAOname;
    GLuint _buffersVBO[2]; //0: vertex  1: indices

    int _numQuads;
};

NS_CC_END

#endif //__CCRENDERER_H_
