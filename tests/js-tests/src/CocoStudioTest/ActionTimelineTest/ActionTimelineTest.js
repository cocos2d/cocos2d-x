/****************************************************************************
 Copyright (c) 2013-2016 Chukong Technologies Inc.

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

var runActionTimeLineTest;

(function(){

    runActionTimeLineTest = function(){
        var scene = new cc.Scene();
        scene.addChild(new layer);
        cc.director.runScene(scene);
    };

    var layer = cc.Layer.extend({

        ctor: function(){
            cc.Layer.prototype.ctor.call(this);

            var json = ccs.load("ActionTimeline/DemoPlayer_skeleton.json");

            var node = json.node, action = json.action;

            node.x = 200;
            node.y = 160;
            node.setScale(0.2);
            this.addChild(node);
            node.setDebugDrawEnabled(true);
            if (action) {
                node.runAction(action);
                action.gotoFrameAndPlay(0, 40, true);
            }

            this.createMenu(node, action);
        },

        createMenu: function(node, action){
            var menus = [];

            action.addAnimationInfo(new ccs.AnimationInfo("stand", 0, 40));
            action.addAnimationInfo(new ccs.AnimationInfo("walk", 41, 81));

            var items = [
                {
                    title: "debug",
                    callback: function(){
                        node.setDebugDrawEnabled(!node.isDebugDrawEnabled());
                    }
                },{
                    title: "change animation",
                    callback: function(){
                        if(action.getStartFrame() == 0)
                            action.gotoFrameAndPlay(41, 81, true);
                        else
                            action.gotoFrameAndPlay(0, 40, true);
                    }
                },/*{
                    title: "set Frame callback",
                    callback: function(evnt){
                        action.setFrameEventCallFunc(function(){
                            if("" == "changeColor"){
                                evnt.getNode().setColor(cc.color(0,0,0));
                            }else{
                                evnt.getNode().setColor(cc.color(255,255,255));
                            }
                        }, this);
                    }
                },*/{
                    title: "AnimationList: walk",
                    callback: function(){
                        action.play("walk", true);
                    }
                },{
                    title: "AnimationList: stand",
                    callback: function(){
                        action.play("stand", true);
                    }
                },{
                    title: "change skin",
                    callback: function(){
                        if (weapSkinToAdd.isVisible())
                            weaponHandeBone.displaySkin("3", true);
                        else
                            weaponHandeBone.displaySkin(weapSkinToAdd, true);
                    }
                }

            ];

            var weaponHandeBone = node.getBoneNode("Layer20");
            var weapSkinToAdd = new cc.Sprite("ActionTimeline/testAnimationResource/girl_arms.png");
            weapSkinToAdd.setName("Knife");
            weapSkinToAdd.setPosition(cc.p(135, 23));
            weapSkinToAdd.setScale(3.0);
            weapSkinToAdd.setRotation(86);
            weaponHandeBone.addSkin(weapSkinToAdd, false);


            items.forEach(function(item, index){
                var menuItem = new cc.MenuItemFont(item.title, item.callback, this);
                menuItem.setPosition((index / 7 | 0) * 100, 120 - index % 7 * 30);
                menus.push(menuItem);
            });
            var menuItem = new cc.MenuItemFont("Back", function(){
                var scene = new CocoStudioTestScene();
                scene.runThisTest();
            }, this);
            menuItem.setPosition(325, -175);
            menus.push(menuItem);

            var menu = new cc.Menu(menus);
            this.addChild(menu);
        }


    });

})();