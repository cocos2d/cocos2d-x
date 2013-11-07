//
// Created by NiTe Luo on 10/31/13.
//



#ifndef __CCRENDERER_H_
#define __CCRENDERER_H_

#include "CCPlatformMacros.h"
#include "CCEGLView.h"
#include "RenderCommand.h"
#include "CCGLProgram.h"

NS_CC_BEGIN
using namespace std;

class Renderer
{
public:
    static Renderer* getInstance();

    //TODO support multiple viewport
    void addRenderCommand(RenderCommand* commnad);
    void render();

protected:
    Renderer();

protected:
    vector<RenderCommand*> _renderQueue;
    GLProgram* _shaderProgram;
    int _lastMaterialID;
    V3F_C4B_T2F_Quad* _quadBuffer;
};

NS_CC_END

#endif //__CCRENDERER_H_
