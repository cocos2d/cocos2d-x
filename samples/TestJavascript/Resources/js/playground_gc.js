
director = cc.Director.getInstance();

cc.log("**** 1 ****");
__jsc__.dumpRoot();
__jsc__.garbageCollect();

scene = cc.Scene.create();
layer = cc.LayerGradient.create( cc.c4b(0, 0, 0, 255), cc.c4b(0, 128, 255, 255) );

layer.onEnter = function() {
    cc.log("On Enter!!");

    cc.log("**** 2 ****");
    __jsc__.dumpRoot();
 //   __jsc__.garbageCollect();
};

scene.addChild( layer );
director.runWithScene( scene );

cc.log("**** 5 ****");
__jsc__.dumpRoot();
__jsc__.garbageCollect();

