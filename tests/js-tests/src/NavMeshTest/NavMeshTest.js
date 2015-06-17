var NavMeshTestIdx = -1;

var physicsScene = null;

const START_POS_X = -0.5;
const START_POS_Y = -2.5;
const START_POS_Z = -0.5;

const ARRAY_SIZE_X = 4;
const ARRAY_SIZE_Y = 3;
const ARRAY_SIZE_Z = 4;

var NavMeshBaseTestDemo = cc.Layer.extend({
    _title:"NavMesh Test",
    _camera:null,
    _needMoveAgents:null,
    _agents:null
    ctor:function () {
        this._super();

        var size = cc.winSize;
        this._camera = cc.Camera.createPerspective(30.0, size.width / size.height, 1.0, 1000.0);
        this._camera.setPosition3D(cc.math.cc.math.vec3(0, 50, 100));
        this._camera.lookAt(cc.math.cc.math.vec3(0, 0, 0), cc.math.cc.math.vec3(0, 1, 0));
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
        var rbDes = cc.physics3DRigidBodyDes();
        rbDes.mass = 0;
        rbDes.shape = cc.Physics3DShape.createMesh(trianglesList[0], trianglesList.length/3);
        var rigidBody = cc.Physics3DRigidBody.create(rbDes);
        var component = cc.Physics3DComponent.create(rigidBody);
        var sprite = cc.PhysicsSprite3D.create("NavMesh/scene.obj");
        sprite.addComponent(component);
        sprite.setCameraMask(cc.CameraFlag.USER1);
        this.addChild(sprite);

        physicsScene.setPhysics3DDebugCamera(this._camera);

        var navMesh = jsb.NavMesh.create("NavMesh/all_tiles_tilecache.bin", "NavMesh/geomset.txt");
        navMesh.setDebugDrawEnable(true);
        setNavMesh(navMesh);
        setNavMeshDebugCamera(this._camera);

        var ambientLight = jsb.AmbientLight.create(cc.color(64, 64, 64));
        ambientLight.setCameraMask(cc.CameraFlag.USER1);
        this.addChild(ambientLight);

        var dirLight = jsb.DirectionLight.create(cc.math.cc.math.vec3(1.2f, -1.1f, 0.5f), cc.color(255, 255, 255));
        dirLight.setCameraMask(cc.CameraFlag.USER1);
        this.addChild(dirLight);
    },
    onMainMenuCallback:function () {
        var scene = new cc.Scene();
        var layer = new TestController();
        scene.addChild(layer);
        director.runScene(scene);
    },
    runThisTest:function (num) {
        NavMeshTestIdx = (num || num == 0) ? (num - 1) : -1;
        var layer = nextNavMeshTest();
        this.addChild(layer);

        director.runScene(this);
    },
    onTouchesBegan:function(touches, event){
        this._needMoveAgents = true;
    },

    onTouchesMoved:function(touches, event){
        if(touches.length > 0 && this._camera){
            var touch = touches[0];
            var delta = touch.getDelta();

            this._angle -= cc.degreesToRadians(delta.x);
            this._camera.setPosition3D(cc.math.cc.math.vec3(100*Math.sin(this._angle), 50, 100*Math.cos(this._angle)));
            this._camera.lookAt(cc.math.cc.math.vec3(0, 0, 0), cc.math.cc.math.vec3(0, 1, 0));

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

            var dir = cc.math.vec3Sub(farP, nearP);

            var result = {};
            this.getPhysics3DWorld().rayCast(nearp, farp, result);
            this.moveAgents(result.hitPosition);
        }
    }

    
    createAgent:function(pos){
        var filePath = "Sprite3DTest/girl.c3b";
        var param = {};
        param.radius = 2.0;
        param.height = 8.0;
        param.maxSpeed = 8.0;
        var agent = jsb.NavMeshAgent.create(filePath);
        var agentNode = jsb.Sprite3D.create(filePath);
        agent.setOrientationRefAxes(cc.math.cc.math.vec3(-1.0f, 0.0f, 1.0f));

        var data = {time:0};
        agent.setUserData(data);
        agentNode.setScale(0.05);
        agentNode.addComponent(agent);

        var node = new cc.Node();
        node.addChild(agentNode);
        node.setPosition3D(pos);
        node.setCameraMask(cc.CameraFlag.USER1);
        this.addChild(node);

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

    jump:function(pV1, pV2, eight, t){
        var pOut;
        pOut.x = pV1.x + t * (pV2.x - pV1.x);
        pOut.y = pV1.y + t * (pV2.y - pV1.y);
        pOut.z = pV1.z + t * (pV2.z - pV1.z);
        pOut.y += height * cc.math.sinf(cc.math.M_PI * t);
        return pOut;
    },
    moveAgents:function(des){
        for (var index = 0; index < this._agents.length; index++){
            var callback = function(agent, totalTimeAfterMove){
                var data = agent.getUserData();
                if (agent.isOnOffMeshLink()){
                    agent.setAutoTraverseOffMeshLink(false);
                    agent.setAutoOrientation(false);
                    var linkdata = agent.getCurrentOffMeshLinkData();

                    agent.getOwner().setPosition3D(jump(linkdata.startPosition, linkdata.endPosition, 10.0, data.time));
                    var dir = cc.math.vec3(linkdata.endPosition.x - linkdata.startPosition.x, 
                        linkdata.endPosition.y - linkdata.startPosition.y, linkdata.endPosition.z - linkdata.startPosition.z);
                    dir.y = 0.0;
                    dir.normalize();
                    var axes;
                    var refAxes = cc.math.vec3(-1.0, 0.0, 1.0);
                    refAxes.normalize();
                    cc.math.vec3.cross(refAxes, dir, &axes);
                    float angle = cc.math.vec3.dot(refAxes, dir);
                    agent.getOwner().setRotationQuat(Quaternion(axes, acosf(angle)));
                    data.time += 0.01;
                    if (1.0 < data.time){
                        agent.completeOffMeshLink();
                        agent.setAutoOrientation(true);
                        data.time = 0.0f;
                    }
                }
            };
            this._agents[index]["agent"].move(des, callback);
        }
    },
    update:function(dt) {
        if (!this._agents)
        {
            return;
        }

        for (var index = 0; index < this._agents.length; index++){
            var speed = this._agents[index]["agent"].getCurrentVelocity().length * 0.2
            this._agents[index]["animate"].setSpeed(speed)
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
        var s = new NavMeshTestScene();
        s.addChild(restartNavMeshTest());
        director.runScene(s);
    },

    onNextCallback:function (sender) {
        var s = new NavMeshTestScene();
        s.addChild(nextNavMeshTest());
        director.runScene(s);
    },

    onBackCallback:function (sender) {
        var s = new NavMeshTestScene();
        s.addChild(previousNavMeshTest());
        director.runScene(s);
    }
});

var NavMeshBaseTestDemo = NavMeshBaseTestDemo.extend({
    _title:"Navigation Mesh Test",
    _subtitle:"Basic Test",
    ctor:function () {
        this._super();

        var label = new cc.LabelTTF("DebugDraw OFF");
        var menuItem = new cc.MenuItemLabel(label, function(){
            if(physicsScene.getPhysics3DWorld().isDebugDrawEnabled()){
                physicsScene.getPhysics3DWorld().setDebugDrawEnable(false);
                label.setString("DebugDraw OFF");
            }else{
                physicsScene.getPhysics3DWorld().setDebugDrawEnable(true);
                label.setString("DebugDraw ON");
            }
        }, this);

        var menu = new cc.Menu(menuItem);
        menu.setPosition(cc.p(0, 0));
        menuItem.setAnchorPoint(cc.p(0, 1));
        menuItem.setPosition(cc.p(cc.visibleRect.left.x, cc.visibleRect.top.y - 50));
        this.addChild(menu);

        var result = {};
        this.getPhysics3DWorld().rayCast(cc.math.vec3(0, 50, 0), cc.math.vec3(0, -50, 0), result);
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
        var menuItem = new cc.MenuItemFont("Create Obstacle", function(){
            if(physicsScene.getPhysics3DWorld().isDebugDrawEnabled()){
                physicsScene.getPhysics3DWorld().setDebugDrawEnable(false);
                label.setString("DebugDraw OFF");
            }else{
                physicsScene.getPhysics3DWorld().setDebugDrawEnable(true);
                label.setString("DebugDraw ON");
            }
        }, this);
        var menuItem2 = new cc.MenuItemFont("Create Agent", function(){
            
        }, this);
        var menuItem3 = new cc.MenuItemFont("DebugDraw OFF", function(){
            
        }, this);

        var menu = new cc.Menu(menuItem, menuItem2, menuItem3);
        menu.setPosition(cc.p(0, 0));
        menuItem.setAnchorPoint(cc.p(0, 1));
        menuItem.setPosition(cc.p(cc.visibleRect.left.x, cc.visibleRect.top.y - 50));
        this.addChild(menu);
        
        var result = {};
        this.getPhysics3DWorld().rayCast(cc.math.vec3(0, 50, 0), cc.math.vec3(0, -50, 0), result);
        this.createAgent(result.hitPosition);
    }
});

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
    }

});

//
// Flow control
//
var arrayOfNavMeshTest = [
    NavMeshBaseTestDemo,
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