try {
  
    cc.p = cc.p || function( x, y ) {
        return {x:x, y:y};
    };
    
    cc.c4b = cc.c4 || function (r, g, b, o) {
        return {r: r, g: g, b: b, a: o};
    };

    director = cc.Director.getInstance();
    winSize = director.getWinSize();

    var scene = new cc.Scene();
    var layer = new cc.LayerGradient();
    
    layer.init(cc.c4b(0, 0, 0, 255), cc.c4b(0, 128, 255, 255));

    var lab = "Houston we have liftoff!";
    var label = cc.LabelTTF.create(lab, "Arial", 28);
    layer.addChild(label, 1);
    label.setPosition( cc.p(winSize.width / 2, winSize.height / 2));


    scene.addChild(layer);

    director.runWithScene(scene);

} catch(e) {log(e);}