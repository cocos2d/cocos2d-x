/*
 * Copyright (c) 2013-2014 Chukong Technologies Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

//
// CocosBuilder definitions
//

cc.BuilderReader = cc.BuilderReader || {};
cc.BuilderReader._resourcePath = "";

cc.BuilderReader._controllerClassCache = {};
cc.BuilderReader.registerController = function(controllerName, controller){
    cc.BuilderReader._controllerClassCache[controllerName] = cc.Class.extend(controller);
};

cc.BuilderReader.setResourcePath = function (rootPath) {
    cc.BuilderReader._resourcePath = rootPath;
};

cc.BuilderReader.load = function(file, owner, parentSize)
{
    // Load the node graph using the correct function
    var reader = cc._Reader.create();
    reader.setCCBRootPath(cc.BuilderReader._resourcePath);
    
    var node;

    if (parentSize)
    {
        node = reader.load(file, null, parentSize);
    }
    else
    {
        node = reader.load(file);
    }

    // Assign owner callbacks & member variables
    if (owner)
    {
        // Callbacks
        var ownerCallbackNames = reader.getOwnerCallbackNames();
        var ownerCallbackNodes = reader.getOwnerCallbackNodes();

        for (var i = 0; i < ownerCallbackNames.length; i++)
        {
            var callbackName = ownerCallbackNames[i];
            var callbackNode = ownerCallbackNodes[i];

            if (owner[callbackName] === undefined)
            {
                cc.log("Warning: " + "owner." + callbackName + " is undefined.");
            }
            else
            {
                if(callbackNode instanceof cc.ControlButton)
                {
                    var ownerCallbackControlEvents = reader.getOwnerCallbackControlEvents();
                    callbackNode.addTargetWithActionForControlEvents(owner, owner[callbackName], ownerCallbackControlEvents[i]);
                }
                else
                {
                    callbackNode.setCallback(owner[callbackName], owner);
                }
            }
        }

        // Variables
        var ownerOutletNames = reader.getOwnerOutletNames();
        var ownerOutletNodes = reader.getOwnerOutletNodes();

        for (var i = 0; i < ownerOutletNames.length; i++)
        {
            var outletName = ownerOutletNames[i];
            var outletNode = ownerOutletNodes[i];

            owner[outletName] = outletNode;
        }
    }

    var nodesWithAnimationManagers = reader.getNodesWithAnimationManagers();
    var animationManagersForNodes = reader.getAnimationManagersForNodes();

    var controllerClassCache = cc.BuilderReader._controllerClassCache;
    // Attach animation managers to nodes and assign root node callbacks and member variables
    for (var i = 0; i < nodesWithAnimationManagers.length; i++)
    {
        var innerNode = nodesWithAnimationManagers[i];
        var animationManager = animationManagersForNodes[i];

        innerNode.animationManager = animationManager;

        var controllerName = animationManager.getDocumentControllerName();
        if (!controllerName) continue;

        // Create a controller
        var controllerClass = controllerClassCache[controllerName];
        if(!controllerClass) throw "Can not find controller : " + controllerName;
        var controller = new controllerClass();
        controller.controllerName = controllerName;

        innerNode.controller = controller;
        controller.rootNode = innerNode;

        // Callbacks
        var documentCallbackNames = animationManager.getDocumentCallbackNames();
        var documentCallbackNodes = animationManager.getDocumentCallbackNodes();

        for (var j = 0; j < documentCallbackNames.length; j++)
        {
            var callbackName = documentCallbackNames[j];
            var callbackNode = documentCallbackNodes[j];

            if (controller[callbackName] === undefined)
            {
                cc.log("Warning: " + controllerName + "." + callbackName + " is undefined.");
            }
            else
            {
                if(callbackNode instanceof cc.ControlButton)
                {
                    var documentCallbackControlEvents = animationManager.getDocumentCallbackControlEvents();
                    callbackNode.addTargetWithActionForControlEvents(controller, controller[callbackName], documentCallbackControlEvents[j]); 
                }
                else
                {
                    callbackNode.setCallback(controller[callbackName], controller);
                }
            }
        }


        // Variables
        var documentOutletNames = animationManager.getDocumentOutletNames();
        var documentOutletNodes = animationManager.getDocumentOutletNodes();

        for (var j = 0; j < documentOutletNames.length; j++)
        {
            var outletName = documentOutletNames[j];
            var outletNode = documentOutletNodes[j];

            controller[outletName] = outletNode;
        }

        if (typeof(controller.onDidLoadFromCCB) == "function")
        {
            controller.onDidLoadFromCCB();
        }

        // Setup timeline callbacks
        var keyframeCallbacks = animationManager.getKeyframeCallbacks();
        for (var j = 0; j < keyframeCallbacks.length; j++)
        {
            var callbackSplit = keyframeCallbacks[j].split(":");
            var callbackType = callbackSplit[0];
            var callbackName = callbackSplit[1];
            
            if (callbackType == 1) // Document callback
            {
                var callfunc = cc.CallFunc.create(controller[callbackName], controller);
                animationManager.setCallFunc(callfunc, keyframeCallbacks[j]);
            }
            else if (callbackType == 2 && owner) // Owner callback
            {
                var callfunc = cc.CallFunc.create(owner[callbackName], owner);
                animationManager.setCallFunc(callfunc, keyframeCallbacks[j]);
            }
        }
        
        // Start animation
        var autoPlaySeqId = animationManager.getAutoPlaySequenceId();
        if (autoPlaySeqId != -1)
        {
            animationManager.runAnimationsForSequenceIdTweenDuration(autoPlaySeqId, 0);
        }
    }

    return node;
};

cc.BuilderReader.loadAsScene = function(file, owner, parentSize)
{
    var node = cc.BuilderReader.load(file, owner, parentSize);
    var scene = cc.Scene.create();
    scene.addChild( node );

    return scene;
};
