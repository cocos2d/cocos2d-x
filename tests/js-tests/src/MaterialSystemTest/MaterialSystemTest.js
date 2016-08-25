/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011-2012 cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
var MaterialSystemTestIdx = -1;

var MaterialSystemTestDemo = cc.Layer.extend({
    _title:"Material System",
    _subtitle:"",

    ctor:function () {
        this._super();
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
        var s = new MaterialSystemTestScene();
        s.addChild(restartMaterialSystemTest());
        director.runScene(s);
    },

    onNextCallback:function (sender) {
        var s = new MaterialSystemTestScene();
        s.addChild(nextMaterialSystemTest());
        director.runScene(s);
    },

    onBackCallback:function (sender) {
        var s = new MaterialSystemTestScene();
        s.addChild(previousMaterialSystemTest());
        director.runScene(s);
    }
});

var MaterialSystemTestScene = cc.Scene.extend({
    ctor:function () {
        this._super();

        var label = new cc.LabelTTF("Main Menu", "Arial", 20);
        var menuItem = new cc.MenuItemLabel(label, this.onMainMenuCallback, this);

        var menu = new cc.Menu(menuItem);
        menu.x = 0;
        menu.y = 0;
        menuItem.x = winSize.width - 50;
        menuItem.y = 25;
        this.addChild(menu, 99);
    },
    onMainMenuCallback:function () {
        var scene = new cc.Scene();
        var layer = new TestController();
        scene.addChild(layer);
        director.runScene(scene);
    },
    runThisTest:function (num) {
        MaterialSystemTestIdx = (num || num == 0) ? (num - 1) : -1;
        var layer = nextMaterialSystemTest();
        this.addChild(layer);

        director.runScene(this);
    }
});

var Material_2DEffects = MaterialSystemTestDemo.extend({
    _subtitle:"Testing effects on Sprite",

    ctor:function(){
        this._super();
        var properties = cc.Properties.createNonRefCounted("Materials/2d_effects.material#sample");

        var mat1 = cc.Material.createWithProperties(properties);

        var spriteBlur = new cc.Sprite("Images/grossini.png");
        spriteBlur.setNormalizedPosition(cc.p(0.2, 0.5));
        this.addChild(spriteBlur);
        spriteBlur.setGLProgramState(mat1.getTechniqueByName("blur").getPassByIndex(0).getGLProgramState());

        var spriteOutline = new cc.Sprite("Images/grossini.png");
        spriteOutline.setNormalizedPosition(cc.p(0.4, 0.5));
        this.addChild(spriteOutline);
        spriteOutline.setGLProgramState(mat1.getTechniqueByName("outline").getPassByIndex(0).getGLProgramState());

        var spriteNoise = new cc.Sprite("Images/grossini.png");
        spriteNoise.setNormalizedPosition(cc.p(0.6, 0.5));
        this.addChild(spriteNoise);
        spriteNoise.setGLProgramState(mat1.getTechniqueByName("noise").getPassByIndex(0).getGLProgramState());

        var spriteEdgeDetect = new cc.Sprite("Images/grossini.png");
        spriteEdgeDetect.setNormalizedPosition(cc.p(0.8, 0.5));
        this.addChild(spriteEdgeDetect);
        spriteEdgeDetect.setGLProgramState(mat1.getTechniqueByName("edge_detect").getPassByIndex(0).getGLProgramState());
    }
});

var Material_UniformCallback = MaterialSystemTestDemo.extend({
    _subtitle:"Testing uniforms call back",

    ctor:function(){
        this._super();
        var properties = cc.Properties.createNonRefCounted("Materials/auto_binding_test.material#sample");

        var mat1 = cc.Material.createWithProperties(properties);

        var spriteBlur = new cc.Sprite("Images/grossini.png");
        spriteBlur.setNormalizedPosition(cc.p(0.2, 0.5));
        this.addChild(spriteBlur);
        var spriteBlurProgram = mat1.getTechniqueByName("blur").getPassByIndex(0).getGLProgramState();
        spriteBlur.setGLProgramState(spriteBlurProgram);
        spriteBlurProgram.setUniformCallback("blurRadius", function(glprogram, uniform){
            glprogram.setUniformLocationWith1f(uniform.location, Math.random() * 10);
        });


        var spriteOutline = new cc.Sprite("Images/grossini.png");
        spriteOutline.setNormalizedPosition(cc.p(0.4, 0.5));
        this.addChild(spriteOutline);
        var spriteOutlineProgram = mat1.getTechniqueByName("outline").getPassByIndex(0).getGLProgramState();
        spriteOutline.setGLProgramState(spriteOutlineProgram);
        spriteOutlineProgram.setUniformCallback("u_outlineColor", function(glprogram, uniform){
            var r = Math.random();
            var g = Math.random();
            var b = Math.random();
            glprogram.setUniformLocationWith3f(uniform.location, r, g, b);
        });

        var spriteNoise = new cc.Sprite("Images/grossini.png");
        spriteNoise.setNormalizedPosition(cc.p(0.6, 0.5));
        this.addChild(spriteNoise);
        spriteNoise.setGLProgramState(mat1.getTechniqueByName("noise").getPassByIndex(0).getGLProgramState());

        var spriteEdgeDetect = new cc.Sprite("Images/grossini.png");
        spriteEdgeDetect.setNormalizedPosition(cc.p(0.8, 0.5));
        this.addChild(spriteEdgeDetect);
        spriteEdgeDetect.setGLProgramState(mat1.getTechniqueByName("edge_detect").getPassByIndex(0).getGLProgramState());
    }
});


var Material_setTechnique = MaterialSystemTestDemo.extend({
    _subtitle:"Testing setTechnique()",
    _techniqueState:0,
    _sprite:null,

    ctor:function(){
        this._super();

        var sprite = new jsb.Sprite3D("Sprite3DTest/boss1.obj");
        sprite.setScale(6);
        this.addChild(sprite);
        sprite.setNormalizedPosition(cc.p(0.5, 0.5));
        this._sprite = sprite;

        var mat = cc.Material.createWithFilename("Materials/3d_effects.material");
        sprite.setMaterial(mat);

        //lights
        var light1 = new jsb.AmbientLight(cc.color.RED);
        this.addChild(light1);

        var light2 = new jsb.DirectionLight(cc.math.vec3(-1, 1, 0), cc.color.GREEN);
        this.addChild(light2);

        sprite.runAction(cc.rotateBy(5, cc.math.vec3(30, 60, 270)).repeatForever());

        this.schedule(this.changeMaterial, 1);
    },

    changeMaterial:function(dt){
        switch(this._techniqueState){
        case 0:
            this._sprite.getMaterial(0).setTechnique("lit");
            break;
        case 1:
            this._sprite.getMaterial(0).setTechnique("normal");
            break;
        case 2:
            this._sprite.getMaterial(0).setTechnique("outline");
            break;
        default:
            break;
        }

        this._techniqueState++;
        if(this._techniqueState > 2)
            this._techniqueState = 0;
    }
});

var Material_clone = MaterialSystemTestDemo.extend({
    _subtitle:"Testing material->clone()",

    ctor:function(){
        this._super();

        var sprite = new jsb.Sprite3D("Sprite3DTest/boss1.obj");
        sprite.setScale(3);
        this.addChild(sprite);
        sprite.setNormalizedPosition(cc.p(0.25, 0.5));

        var mat = cc.Material.createWithFilename("Materials/3d_effects.material");
        sprite.setMaterial(mat);

        var repeat = cc.rotateBy(5, cc.math.vec3(360, 240, 120)).repeatForever();
        sprite.runAction(repeat);

        // sprite 2... using same material
        var sprite2 = new jsb.Sprite3D("Sprite3DTest/boss1.obj");
        sprite2.setScale(3);
        this.addChild(sprite2);
        sprite2.setNormalizedPosition(cc.p(0.5, 0.5));
        sprite2.setMaterial(mat);
        sprite2.runAction(repeat.clone());

        // sprite 3... using cloned material
        var sprite3 = new jsb.Sprite3D("Sprite3DTest/boss1.obj");
        sprite3.setScale(3);
        this.addChild(sprite3);
        sprite3.setNormalizedPosition(cc.p(0.75, 0.5));
        var mat2 = mat.clone();
        sprite3.setMaterial(mat2);
        sprite3.runAction(repeat.clone());

        mat.setTechnique("outline");
    }
});

var Material_MultipleSprite3D = MaterialSystemTestDemo.extend({
    _subtitle:"Sprites with multiple meshes",

    ctor:function(){
        this._super();

        var names = [
            "Sprite3DTest/ReskinGirl.c3b",
            "Sprite3DTest/ReskinGirl.c3b",
            "Sprite3DTest/ReskinGirl.c3b",
            "Sprite3DTest/ReskinGirl.c3b",
            "Sprite3DTest/ReskinGirl.c3b",
            "Sprite3DTest/ReskinGirl.c3b",
            "Sprite3DTest/ReskinGirl.c3b",
            "Sprite3DTest/ReskinGirl.c3b"
        ];

        var totalNames = names.length;

        var size = cc.winSize;

        for(var i = 0; i < totalNames; ++i){
            var sprite = new jsb.Sprite3D(names[i]);
            this.addChild(sprite);
            sprite.setPosition(cc.p((size.width/(totalNames+1))*(i+1), size.height/4));
            sprite.setScale(3);
        }
    }
});

var Material_Sprite3DTest = MaterialSystemTestDemo.extend({
    _subtitle:"Material System on Sprite3D",

    ctor:function(){
        this._super();

        var sprite = new jsb.Sprite3D("Sprite3DTest/boss1.obj");
        sprite.setScale(8.0);
        sprite.setTexture("Sprite3DTest/boss.png");
        this.addChild(sprite);
        sprite.setNormalizedPosition(cc.p(0.5, 0.5));
    }
});

var Material_parsePerformance = MaterialSystemTestDemo.extend({
    _subtitle:"Testing parsing performance",

    ctor:function(){
        this._super();

        var begin = new Date().getTime();

        for(var i = 0; i < 5000; ++i){
            cc.Material.createWithFilename("Materials/2d_effects.material");
            cc.Material.createWithFilename("Materials/3d_effects.material");
        }

        var end = new Date().getTime();
        var elapsed_secs = (end - begin) / 1000;
        cc.log("Parsing took: "+elapsed_secs +" seconds");
    }
});

//
// Flow control
//
var arrayOfMaterialSystemTest = [
    Material_2DEffects,
    Material_UniformCallback,
    Material_setTechnique,
    Material_clone,
    Material_MultipleSprite3D,
    Material_Sprite3DTest,
    Material_parsePerformance
];

var nextMaterialSystemTest = function () {
    MaterialSystemTestIdx++;
    MaterialSystemTestIdx = MaterialSystemTestIdx % arrayOfMaterialSystemTest.length;

    if(window.sideIndexBar){
        MaterialSystemTestIdx = window.sideIndexBar.changeTest(MaterialSystemTestIdx, 36);
    }

    return new arrayOfMaterialSystemTest[MaterialSystemTestIdx ]();
};
var previousMaterialSystemTest = function () {
    MaterialSystemTestIdx--;
    if (MaterialSystemTestIdx < 0)
        MaterialSystemTestIdx += arrayOfMaterialSystemTest.length;

    if(window.sideIndexBar){
        MaterialSystemTestIdx = window.sideIndexBar.changeTest(MaterialSystemTestIdx, 36);
    }

    return new arrayOfMaterialSystemTest[MaterialSystemTestIdx ]();
};
var restartMaterialSystemTest = function () {
    return new arrayOfMaterialSystemTest[MaterialSystemTestIdx ]();
};
