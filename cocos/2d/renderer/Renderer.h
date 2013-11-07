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

#define NUM_QUADS_PER_ALLOC 20

NS_CC_BEGIN
using namespace std;

class Renderer
{
public:
    static Renderer* getInstance();

    //TODO support multiple viewport
    void addRenderCommand(RenderCommand* command);
    void render();

protected:
    Renderer();
    ~Renderer();

    void batchQuads(QuadCommand* cmd);
    void drawQuads();

protected:
    vector<RenderCommand*> _renderQueue;
    int _lastMaterialID;
    V3F_C4B_T2F_Quad* _quadBuffer;
    int _numQuadsAlloc;
    int _numQuads;
};

NS_CC_END

#endif //__CCRENDERER_H_
