//
// CocosBuilder definitions
//

cc.BuilderReader = cc.BuilderReader || {};
cc.BuilderReader._resourcePath = "";

var _ccbGlobalContext = this;

cc.BuilderReader.setResourcePath = function (rootPath) {
    cc.BuilderReader._resourcePath = rootPath;
};

cc.BuilderReader.load = function(file, owner, parentSize)
{
    // Load the node graph using the correct function
    var reader = cc._Reader.create();
    reader.setCCBRootPath(cc.BuilderReader._resourcePath);
    
    var node;

    if (owner && parentSize)
    {
        node = reader.load(file, owner, parentSize);
    }
    else if (owner)
    {
        node = reader.load(file,owner);
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

            callbackNode.setCallback(owner[callbackName], owner);
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

    // Attach animation managers to nodes and assign root node callbacks and member variables
    for (var i = 0; i < nodesWithAnimationManagers.length; i++)
    {
        var innerNode = nodesWithAnimationManagers[i];
        var animationManager = animationManagersForNodes[i];

        innerNode.animationManager = animationManager;

        var documentControllerName = animationManager.getDocumentControllerName();
        if (!documentControllerName) continue;

        // Create a document controller
        var controller = new _ccbGlobalContext[documentControllerName]();
        controller.controllerName = documentControllerName;

        innerNode.controller = controller;
        controller.rootNode = innerNode;

        // Callbacks
        var documentCallbackNames = animationManager.getDocumentCallbackNames();
        var documentCallbackNodes = animationManager.getDocumentCallbackNodes();

        for (var j = 0; j < documentCallbackNames.length; j++)
        {
            var callbackName = documentCallbackNames[j];
            var callbackNode = documentCallbackNodes[j];

            callbackNode.setCallback(controller[callbackName], controller);
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
