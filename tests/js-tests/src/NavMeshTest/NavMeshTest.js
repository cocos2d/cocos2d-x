var NavMeshTestIdx = -1;

var physicsScene = null;
var START_POS_X = -0.5;
var START_POS_Y = -2.5;
var START_POS_Z = -0.5;

var ARRAY_SIZE_X = 4;
var ARRAY_SIZE_Y = 3;
var ARRAY_SIZE_Z = 4;

var NavMeshTestScene = cc.Scene.extend({

    ctor:function () {
        this._super();

        var label = new cc.LabelTTF("Main Menu", "Arial", 20);
        var menuItem = new cc.MenuItemLabel(label, this.onMainMenuCallback, this);

        var menu = new cc.Menu(menuItem);
        menu.x = 0;
        menu.y = 0;
        menuItem.x = winSize.width - 50;
        menuItem.y = 25;
        this.addChild(menu);

        this.initWithPhysics();
        this.getPhysics3DWorld().setDebugDrawEnable(false);
        physicsScene = this;     
    },
    onMainMenuCallback:function () {
        var scene = new cc.Scene();
        var layer = new TestController();
        scene.addChild(layer);
        director.runScene(scene);
    },
    runThisTest:function (num) {
        director.runScene(this);
    }

});

var NavMeshBaseTestDemo = NavMeshTestScene.extend({
    _title:"NavMesh Test",
    _camera:null,
    _needMoveAgents:null,
    _agents:[],
    _angle:null,
    ctor:function () {
        this._super();

        this._agents = [];
        this._angle = 0.0;

        var size = cc.winSize;
        this._camera = cc.Camera.createPerspective(30.0, size.width / size.height, 1.0, 1000.0);
        this._camera.setPosition3D(cc.math.vec3(0, 50, 100));
        this._camera.lookAt(cc.math.vec3(0, 0, 0), cc.math.vec3(0, 1, 0));
        this._camera.setCameraFlag(cc.CameraFlag.USER1);
        this.addChild(this._camera);

        cc.eventManager.addListener({
            event:cc.EventListener.TOUCH_ALL_AT_ONCE,
            onTouchesBegan:this.onTouchesBegan.bind(this),
            onTouchesMoved:this.onTouchesMoved.bind(this),
            onTouchesEnded:this.onTouchesEnded.bind(this)
        }, this);

        this.initScene();
        this.scheduleUpdate();
    },

    initScene:function () {
        //create mesh
        var trianglesList = jsb.Bundle3D.getTrianglesList("NavMesh/scene.obj");
        var rbDes = jsb.physics3DRigidBodyDes();
        rbDes.mass = 0;
        rbDes.shape = jsb.Physics3DShape.createMesh(trianglesList, trianglesList.length/3);
        var rigidBody = jsb.Physics3DRigidBody.create(rbDes);
        var component = jsb.Physics3DComponent.create(rigidBody);
        var sprite = jsb.Sprite3D.create("NavMesh/scene.obj");
        sprite.addComponent(component);
        sprite.setCameraMask(cc.CameraFlag.USER1);
        this.addChild(sprite);

        physicsScene.setPhysics3DDebugCamera(this._camera);

        var navMesh = jsb.NavMesh.create("NavMesh/all_tiles_tilecache.bin", "NavMesh/geomset.txt");
        navMesh.setDebugDrawEnable(true);
        physicsScene.setNavMesh(navMesh);
        physicsScene.setNavMeshDebugCamera(this._camera);

        var ambientLight = jsb.AmbientLight.create(cc.color(64, 64, 64));
        ambientLight.setCameraMask(cc.CameraFlag.USER1);
        this.addChild(ambientLight);

        var dirLight = jsb.DirectionLight.create(cc.math.vec3(1.2, -1.1, 0.5), cc.color(255, 255, 255));
        dirLight.setCameraMask(cc.CameraFlag.USER1);
        this.addChild(dirLight);
    },
    
    onTouchesBegan:function(touches, event){
        this._needMoveAgents = true;
        return true;
    },

    onTouchesMoved:function(touches, event){
        if(touches.length > 0 && this._camera){
            var touch = touches[0];
            var delta = touch.getDelta();

            this._angle -= cc.degreesToRadians(delta.x);
            this._camera.setPosition3D(cc.math.vec3(100*Math.sin(this._angle), 50, 100*Math.cos(this._angle)));
            this._camera.lookAt(cc.math.vec3(0, 0, 0), cc.math.vec3(0, 1, 0));

            if(delta.x * delta.x + delta.y + delta.y > 16)
                this._needMoveAgents = false;
        }
    },

    onTouchesEnded:function(touches, event){
        if(!this._needMoveAgents)
            return;
        if(touches.length > 0){
            var location = touches[0].getLocationInView();

            var nearP = cc.math.vec3(location.x, location.y, -1);
            var farP = cc.math.vec3(location.x, location.y, 1);
            nearP = this._camera.unproject(nearP);
            farP = this._camera.unproject(farP);
            cc.log("ray cast before");
            var result = physicsScene.getPhysics3DWorld().rayCast(nearP, farP);
            cc.log("ray cast after");
            this.moveAgents(result.hitPosition);
        }
    },

    
    createAgent:function(pos){
        var filePath = "Sprite3DTest/girl.c3b";
        var param = jsb.navMeshAgentParam();
        param.radius = 2.0;
        param.height = 8.0;
        param.maxSpeed = 8.0;
        var agent = jsb.NavMeshAgent.create(param);
        var agentNode = jsb.Sprite3D.create(filePath);
        agent.setOrientationRefAxes(cc.math.vec3(-1.0, 0.0, 1.0));

        var data = jsb.agentUserData();
        agent.setUserData(data);
        agentNode.setScale(0.05);
        agentNode.addComponent(agent);

        var node = new cc.Node();
        node.addChild(agentNode);
        node.setPosition3D(pos);
        node.setCameraMask(cc.CameraFlag.USER1);
        physicsScene.addChild(node);

        var animation = jsb.Animation3D.create(filePath);
        var animate = jsb.Animate3D.create(animation);

        if (animate){
            agentNode.runAction(new cc.RepeatForever(animate));
            animate.setSpeed(0);
        }

        this._agents[this._agents.length] = {"agent":agent, "animate":animate};
    },
    createObstacle:function(pos){
        var obstacle = jsb.NavMeshObstacle.create(2.0, 8.0);
        var obstacleNode = jsb.Sprite3D.create("Sprite3DTest/cylinder.c3b");
        obstacleNode.setPosition3D(cc.math.vec3(pos.x + 0.0, pos.y - 0.5, pos.z + 0.0));
        obstacleNode.setRotation3D(cc.math.vec3(-90.0, 0.0, 0.0));
        obstacleNode.setScale(0.3);
        obstacleNode.addComponent(obstacle);
        obstacleNode.setCameraMask(cc.CameraFlag.USER1);
        this.addChild(obstacleNode);
    },

    jump:function(pV1, pV2, height, t){
        var pOut = cc.math.vec3();
        pOut.x = pV1.x + t * (pV2.x - pV1.x);
        pOut.y = pV1.y + t * (pV2.y - pV1.y);
        pOut.z = pV1.z + t * (pV2.z - pV1.z);
        pOut.y += height * Math.sin(Math.PI * t);
        return pOut;
    },
    moveAgents:function(des){
        var self = this;
        for (var index = 0; index < this._agents.length; index++){
            var callback = function(agent, totalTimeAfterMove){
                var data = agent.getUserData();
                if (agent.isOnOffMeshLink()){
                    agent.setAutoTraverseOffMeshLink(false);
                    agent.setAutoOrientation(false);
                    var linkdata = agent.getCurrentOffMeshLinkData();

                    agent.getOwner().setPosition3D(self.jump(linkdata.startPosition, linkdata.endPosition, 10.0, data.time));
                    var dir = cc.math.vec3(linkdata.endPosition.x - linkdata.startPosition.x, 
                        linkdata.endPosition.y - linkdata.startPosition.y, linkdata.endPosition.z - linkdata.startPosition.z);
                    dir.y = 0.0;
                    dir.normalize();
                    var axes;
                    var refAxes = cc.math.vec3(-1.0, 0.0, 1.0);
                    refAxes.normalize();
                    axes = cc.math.vec3Cross(refAxes, dir);
                    var angle = cc.math.vec3Dot(refAxes, dir);
                    agent.getOwner().setRotationQuat(cc.math.quaternion(axes, Math.acos(angle)));
                    data.time += 0.01;
                    if (1.0 < data.time){
                        agent.completeOffMeshLink();
                        agent.setAutoOrientation(true);
                        data.time = 0.0;
                    }
                }
            };
            this._agents[index]["agent"].move(des, callback);
        }
    },
    update:function(dt) {
        this._super(dt);
        if (!this._agents)
        {
            return;
        }

        for (var index = 0; index < this._agents.length; index++){
            var speed = cc.math.vec3Length( this._agents[index]["agent"].getCurrentVelocity() ) * 0.2
            this._agents[index]["animate"].setSpeed(0.0 < speed ? speed : 0.0)
        }

    },
    //
    // Menu
    //
    onEnter:function () {
        this._super();

        var label = new cc.LabelTTF(this._title, "Arial", 28);
        this.addChild(label, 100, BASE_TEST_TITLE_TAG);
        label.x = winSize.width / 2;
        label.y = winSize.height - 50;

        var label2 = new cc.LabelTTF(this._subtitle, "Thonburi", 16);
        this.addChild(label2, 101, BASE_TEST_SUBTITLE_TAG);
        label2.x = winSize.width / 2;
        label2.y = winSize.height - 80;

        var item1 = new cc.MenuItemImage(s_pathB1, s_pathB2, this.onBackCallback, this);
        var item2 = new cc.MenuItemImage(s_pathR1, s_pathR2, this.onRestartCallback, this);
        var item3 = new cc.MenuItemImage(s_pathF1, s_pathF2, this.onNextCallback, this);

        item1.tag = BASE_TEST_MENUITEM_PREV_TAG;
        item2.tag = BASE_TEST_MENUITEM_RESET_TAG;
        item3.tag = BASE_TEST_MENUITEM_NEXT_TAG;

        var menu = new cc.Menu(item1, item2, item3);

        menu.x = 0;
        menu.y = 0;
        var width = item2.width, height = item2.height;
        item1.x =  winSize.width/2 - width*2;
        item1.y = height/2 ;
        item2.x =  winSize.width/2;
        item2.y = height/2 ;
        item3.x =  winSize.width/2 + width*2;
        item3.y = height/2 ;

        this.addChild(menu, 102, BASE_TEST_MENU_TAG);
    },

    onRestartCallback:function (sender) {
        director.runScene(restartNavMeshTest());
    },

    onNextCallback:function (sender) {
        director.runScene(nextNavMeshTest());
    },

    onBackCallback:function (sender) {
        director.runScene(previousNavMeshTest());
    }
});

var NavMeshBasicTestDemo = NavMeshBaseTestDemo.extend({
    _title:"Navigation Mesh Test",
    _subtitle:"Basic Test",
    ctor:function () {
        this._super();

        var label = new cc.LabelTTF("DebugDraw OFF");
        var menuItem = new cc.MenuItemLabel(label, function(){
            var enabledDebug = physicsScene.getNavMesh().isDebugDrawEnabled();
            physicsScene.getNavMesh().setDebugDrawEnable(!enabledDebug);
            if (enabledDebug){
                label.setString("Debug Draw ON");
            }
            else{
                label.setString("Debug Draw OFF");
            }
        }, this);

        var menu = new cc.Menu(menuItem);
        menu.setPosition(cc.p(0, 0));
        menuItem.setAnchorPoint(cc.p(0, 1));
        menuItem.setPosition(cc.p(cc.visibleRect.left.x, cc.visibleRect.top.y - 50));
        this.addChild(menu);

        
    },
    onEnter:function () {
        this._super();

        var result = physicsScene.getPhysics3DWorld().rayCast(cc.math.vec3(0, 50, 0), cc.math.vec3(0, -50, 0));
        this.createAgent(result.hitPosition);
    }
});

var NavMeshAdvanceTestDemo = NavMeshBaseTestDemo.extend({
    _title:"Navigation Mesh Test",
    _subtitle:"Advance Test",
    ctor:function () {
        this._super();

        var label = new cc.LabelTTF();
        var label2 = new cc.LabelTTF();
        var label3 = new cc.LabelTTF();
        var self = this;
        var menuItem = new cc.MenuItemLabel(new cc.LabelTTF("Create Obstacle"), function(){
            var x = Math.random() * 100 - 50;
            var z = Math.random() * 100 - 50;
            var result = physicsScene.getPhysics3DWorld().rayCast(cc.math.vec3(x, 50, z), cc.math.vec3(x, -50, z));
            self.createObstacle(result.hitPosition);
        }, this);
        var menuItem2 = new cc.MenuItemLabel(new cc.LabelTTF("Create Agent"), function(){
            var x = Math.random() * 100 - 50;
            var z = Math.random() * 100 - 50;
            var result = physicsScene.getPhysics3DWorld().rayCast(cc.math.vec3(x, 50, z), cc.math.vec3(x, -50, z));
            self.createAgent(result.hitPosition);
        }, this);

        var label = new cc.LabelTTF("DebugDraw OFF");
        var menuItem3 = new cc.MenuItemLabel(label, function(){
            var enabledDebug = physicsScene.getNavMesh().isDebugDrawEnabled();
            physicsScene.getNavMesh().setDebugDrawEnable(!enabledDebug);
            if (enabledDebug){
                label.setString("Debug Draw ON");
            }
            else{
                label.setString("Debug Draw OFF");
            }
        }, this);

        var menu = new cc.Menu(menuItem, menuItem2, menuItem3);
        menu.setPosition(cc.p(0, 0));
        menuItem.setAnchorPoint(cc.p(0, 1));
        menuItem.setPosition(cc.p(cc.visibleRect.left.x, cc.visibleRect.top.y - 50));
        menuItem2.setAnchorPoint(cc.p(0, 1));
        menuItem2.setPosition(cc.p(cc.visibleRect.left.x, cc.visibleRect.top.y - 100));
        menuItem3.setAnchorPoint(cc.p(0, 1));
        menuItem3.setPosition(cc.p(cc.visibleRect.left.x, cc.visibleRect.top.y - 150));
        this.addChild(menu);
        
    },
    onEnter:function () {
        this._super();

        var result = physicsScene.getPhysics3DWorld().rayCast(cc.math.vec3(0, 50, 0), cc.math.vec3(0, -50, 0));
        this.createAgent(result.hitPosition);
    }
});



//
// Flow control
//
var arrayOfNavMeshTest = [
    NavMeshBasicTestDemo,
    NavMeshAdvanceTestDemo
];

var nextNavMeshTest = function () {
    NavMeshTestIdx++;
    NavMeshTestIdx = NavMeshTestIdx % arrayOfNavMeshTest.length;

    return new arrayOfNavMeshTest[NavMeshTestIdx ]();
};
var previousNavMeshTest = function () {
    NavMeshTestIdx--;
    if (NavMeshTestIdx < 0)
        NavMeshTestIdx += arrayOfNavMeshTest.length;

    return new arrayOfNavMeshTest[NavMeshTestIdx ]();
};
var restartNavMeshTest = function () {
    return new arrayOfNavMeshTest[NavMeshTestIdx ]();
};