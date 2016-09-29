/******************************************************************************
 * Spine Runtimes Software License
 * Version 2.3
 *
 * Copyright (c) 2013-2015, Esoteric Software
 * All rights reserved.
 *
 * You are granted a perpetual, non-exclusive, non-sublicensable and
 * non-transferable license to use, install, execute and perform the Spine
 * Runtimes Software (the "Software") and derivative works solely for personal
 * or internal use. Without the written permission of Esoteric Software (see
 * Section 2 of the Spine Software License Agreement), you may not (a) modify,
 * translate, adapt or otherwise create derivative works, improvements of the
 * Software or develop new applications using the Software or (b) remove,
 * delete, alter or obscure any trademarks or any copyright, trademark, patent
 * or other intellectual property or proprietary rights notices on or in the
 * Software, including any copy thereof. Redistributions in binary or source
 * form must include this license and terms.
 *
 * THIS SOFTWARE IS PROVIDED BY ESOTERIC SOFTWARE "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL ESOTERIC SOFTWARE BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

#include <spine/SkeletonBatch.h>
#include <spine/extension.h>
#include <algorithm>

USING_NS_CC;
#define EVENT_AFTER_DRAW_RESET_POSITION "director_after_draw"
using std::max;

namespace spine {
    
    static SkeletonBatch* instance = nullptr;
    
    SkeletonBatch* SkeletonBatch::getInstance () {
        if (!instance) instance = new SkeletonBatch();
        return instance;
    }
    
    void SkeletonBatch::destroyInstance () {
        if (instance) {
            delete instance;
            instance = nullptr;
        }
    }
    
    SkeletonBatch::SkeletonBatch ()
    {
        _firstCommand = new Command();
        _command = _firstCommand;
        
        Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_AFTER_DRAW_RESET_POSITION, [this](EventCustom* eventCustom){
            this->update(0);
        });;
    }
    
    SkeletonBatch::~SkeletonBatch () {
        Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_AFTER_DRAW_RESET_POSITION);
        
        Command* command = _firstCommand;
        while (command) {
            Command* next = command->next;
            delete command;
            command = next;
        }
    }
    
    void SkeletonBatch::update (float delta) {
        _command = _firstCommand;
    }
    
    void SkeletonBatch::addCommand (cocos2d::Renderer* renderer, float globalZOrder, GLuint textureID, GLProgramState* glProgramState,
                                    BlendFunc blendFunc, const TrianglesCommand::Triangles& triangles, const Mat4& transform, uint32_t transformFlags
                                    ) {
        _command->triangles->verts = triangles.verts;
        
        _command->triangles->vertCount = triangles.vertCount;
        _command->triangles->indexCount = triangles.indexCount;
        _command->triangles->indices = triangles.indices;
        
        _command->trianglesCommand->init(globalZOrder, textureID, glProgramState, blendFunc, *_command->triangles, transform);
        renderer->addCommand(_command->trianglesCommand);
        
        if (!_command->next) _command->next = new Command();
        _command = _command->next;
    }
    
    SkeletonBatch::Command::Command () :
    next(nullptr)
    {
        trianglesCommand = new TrianglesCommand();
        triangles = new TrianglesCommand::Triangles();
    }
    
    SkeletonBatch::Command::~Command () {
        delete triangles;
        delete trianglesCommand;
    }
    
}