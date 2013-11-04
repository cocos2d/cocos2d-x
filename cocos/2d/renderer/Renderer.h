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

    void setOpenGLView(EGLView *newOpenGLView);
    void addRenderCommand(RenderCommand* commnad);
    void render();

protected:
    Renderer();

protected:
    EGLView* _openGLView;
    vector<RenderCommand*> _renderQueue;
    GLProgram* _shaderProgram;
    int _currentMaterialID;
};

NS_CC_END

#endif //__CCRENDERER_H_
