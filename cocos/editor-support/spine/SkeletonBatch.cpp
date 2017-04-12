/******************************************************************************
 * Spine Runtimes Software License v2.5
 *
 * Copyright (c) 2013-2016, Esoteric Software
 * All rights reserved.
 *
 * You are granted a perpetual, non-exclusive, non-sublicensable, and
 * non-transferable license to use, install, execute, and perform the Spine
 * Runtimes software and derivative works solely for personal or internal
 * use. Without the written permission of Esoteric Software (see Section 2 of
 * the Spine Software License Agreement), you may not (a) modify, translate,
 * adapt, or develop new applications using the Spine Runtimes or otherwise
 * create derivative works or improvements of the Spine Runtimes or (b) remove,
 * delete, alter, or obscure any trademarks or any copyright, trademark, patent,
 * or other intellectual property or proprietary rights notices on or in the
 * Software, including any copy thereof. Redistributions in binary or source
 * form must include this license and terms.
 *
 * THIS SOFTWARE IS PROVIDED BY ESOTERIC SOFTWARE "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL ESOTERIC SOFTWARE BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES, BUSINESS INTERRUPTION, OR LOSS OF
 * USE, DATA, OR PROFITS) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
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

    void SkeletonBatch::addCommand (cocos2d::Renderer* renderer, float globalZOrder, Texture2D* texture, GLProgramState* glProgramState,
                                    BlendFunc blendFunc, const TrianglesCommand::Triangles& triangles, const Mat4& transform, uint32_t transformFlags
                                    ) {
        if (_command->triangles->verts) {
            free(_command->triangles->verts);
            _command->triangles->verts = NULL;
        }
        
        _command->triangles->verts = (V3F_C4B_T2F *)malloc(sizeof(V3F_C4B_T2F) * triangles.vertCount);
        memcpy(_command->triangles->verts, triangles.verts, sizeof(V3F_C4B_T2F) * triangles.vertCount);
        
        _command->triangles->vertCount = triangles.vertCount;
        _command->triangles->indexCount = triangles.indexCount;
        _command->triangles->indices = triangles.indices;
        
        _command->trianglesCommand->init(globalZOrder, texture, glProgramState, blendFunc, *_command->triangles, transform, transformFlags);
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
        if (triangles->verts) {
            free(triangles->verts);
        }
        delete triangles;
        delete trianglesCommand;
    }

}
