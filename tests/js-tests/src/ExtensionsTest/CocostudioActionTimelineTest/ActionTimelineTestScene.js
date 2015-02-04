/****************************************************************************
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

var ActionTimelineTestScene = (function(){

    var ActionTimelineTestSceneEnum = {
        TEST_ANIMATIONELEMENT: 0,
        TEST_CHANGE_PLAY_SECTION: 1,
        TEST_TIMELINE_FRAME_EVENT: 2,
        TEST_TIMELINE_PERFORMACE: 3,

        TEST_ANIMATION_LAYER_COUNT: 4
    };

    var s_nActionIdx = -1;

    var ActionTimelineTestScene = TestScene.extend({

        ctor: function(bPortrait){
            TestScene.prototype.ctor.call(this);
            TestScene.prototype.init.call(this);

            var bg = new cc.Sprite("res/armatures/bg.jpg");
            bg.setPosition(cc.p(400, 225));

            var scaleX = 800 / 500;
            var scaleY = 450 / 500;

            bg.setScaleX(scaleX);
            bg.setScaleY(scaleY);

            this.addChild(bg);

        },

        runThisTest: function(){
            s_nActionIdx = -1;
            this.addChild(NextAnimationTest());
            var self = this;
            cc.loader.load([
                "res/ActionTimeline/boy_1.ExportJson",
                "res/armatures/Cowboy0.plist",
                "res/armatures/Cowboy0.png"
            ], function(){
                cc.director.runScene(self);
            });
        },

        MainMenuCallback: function(pSender){
            this.removeAllChildren();
        }
    });

    var ActionTimelineTestLayer = cc.Layer.extend({

        _restartItem: null,
        _nextItem: null,
        _backItem: null,

        title: function(){
            return "armatures Test Bed";
        },
        subtitle: function(){
            return "";
        },
        restartCallback: function(pSender){
            var s = new ActionTimelineTestScene();
            s.addChild( RestartAnimationTest() );
            cc.director.runScene(s);
        },
        nextCallback: function(pSender){
            var s = new ActionTimelineTestScene();
            s.addChild( NextAnimationTest() );
            cc.director.runScene(s);
        },
        backCallback: function(pSender){
            var s = new ActionTimelineTestScene();
            s.addChild( BackAnimationTest() );
            cc.director.runScene(s);
        },
        onEnter: function(){
            cc.Layer.prototype.onEnter.call(this);
            
            // add title and subtitle
            var title = this.title();
            var label = new cc.LabelTTF(title, "Arial", 18);
            label.setColor(cc.color(0, 0, 0));
            this.addChild(label, 1, 10000);
            label.setPosition( cc.p(cc.winSize.width/2, cc.winSize.height - 80) );

            var strSubtitle = this.subtitle();
            if( ! strSubtitle  )
            {
                var l = new cc.LabelTTF(strSubtitle, "Arial", 18);
                l.setColor(cc.color(0, 0, 0));
                this.addChild(l, 1, 10001);
                l.setPosition(cc.winSize.width/2, cc.winSize.height - 110);
            }

            // add menu
            this._backItem = new cc.MenuItemImage(s_pathB1, s_pathB2, this.backCallback);
            this._restartItem = new cc.MenuItemImage(s_pathR1, s_pathR2, this.restartCallback);
            this._nextItem = new cc.MenuItemImage(s_pathF1, s_pathF2, this.nextCallback);

            var menu = new cc.Menu(this._backItem, this._restartItem, this._nextItem);

            menu.setPosition(cc.p(0, 0));
            this._backItem.setPosition(cc.winSize.width/2 - this._restartItem.getContentSize().width * 2, this._restartItem.getContentSize().height / 2);
            this._restartItem.setPosition(cc.winSize.width/2, this._restartItem.getContentSize().height / 2);
            this._nextItem.setPosition(cc.winSize.width/2 + this._restartItem.getContentSize().width * 2, this._restartItem.getContentSize().height / 2);

            this.addChild(menu, 100);

            //this.setGLProgram(ShaderCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR));

        },
        onExit: function(){
            this.removeAllChildren();
            this._backItem = this._restartItem = this._nextItem = null;
            cc.Layer.prototype.onExit.call(this);

        }
    });

    var TestActionTimeline = ActionTimelineTestLayer.extend({

        onEnter: function(){
            ActionTimelineTestLayer.prototype.onEnter.call(this);

            cc.spriteFrameCache.addSpriteFrames("res/armatures/Cowboy0.plist", "res/armatures/Cowboy0.png");

            var node = ccs.csLoader.createNode("res/ActionTimeline/boy_1.ExportJson");
            var action = ccs.actionTimelineCache.createAction("res/ActionTimeline/boy_1.ExportJson");

            node.runAction(action);
            action.gotoFrameAndPlay(0, 60, true);

            node.setScale(0.2);
            node.setPosition(150,100);

            this.addChild(node);
        },
        title: function(){
            return "Test ActionTimeline";
        }
    });

    var TestChangePlaySection = ActionTimelineTestLayer.extend({

        _action: null,

        onEnter: function(){
            ActionTimelineTestLayer.prototype.onEnter.call(this);

            cc.spriteFrameCache.addSpriteFrames("res/armatures/Cowboy0.plist", "res/armatures/Cowboy0.png");

            var node = ccs.csLoader.createNode("res/ActionTimeline/boy_1.ExportJson");
            this._action = ccs.actionTimelineCache.createAction("res/ActionTimeline/boy_1.ExportJson");

            node.runAction(this._action);
            this._action.gotoFrameAndPlay(70, this._action.getDuration(), true);

            node.setScale(0.2);
            node.setPosition(150,100);

            // add touch event listener
            cc.eventManager.addListener({
                event: cc.EventListener.TOUCH_ONE_BY_ONE,
                onTouchBegan: this.onTouchesEnded
            }, this);

            this.addChild(node);

        },
        title: function(){
            return "Test Change Play Section";
        },
        onTouchesEnded: function(touches, event){
            var target = event.getCurrentTarget();
            if(target._action.getStartFrame() == 0)
                target._action.gotoFrameAndPlay(70, target._action.getDuration(), true);
            else
                target._action.gotoFrameAndPlay(0, 60, true);

            return true;
        }

    });

    var TestTimelineFrameEvent = ActionTimelineTestLayer.extend({
        onEnter: function(){
            ActionTimelineTestLayer.prototype.onEnter.call(this);

            cc.spriteFrameCache.addSpriteFrames("res/armatures/Cowboy0.plist", "res/armatures/Cowboy0.png");

            var node = ccs.csLoader.createNode("res/ActionTimeline/boy_1.ExportJson");
            var action = ccs.actionTimelineCache.createAction("res/ActionTimeline/boy_1.ExportJson");
            node.runAction(action);
            action.gotoFrameAndPlay(0, 60, true);

            node.setScale(0.2);
            node.setPosition(150,100);
            this.addChild(node);

            action.setFrameEventCallFunc(this.onFrameEvent);
        },
        title: function(){
            return "Test Frame Event";
        },
        onFrameEvent: function(frame){
            var evnt = frame;
            if(!evnt)
                return;

            var str = evnt.getEvent();

            if (str == "changeColor"){
                evnt.getNode().setColor(cc.color(0,0,0));
            }else if(str == "endChangeColor"){
                evnt.getNode().setColor(cc.color(255,255,255));
            }
        }
    });

    var TestTimelinePerformance = ActionTimelineTestLayer.extend({
        onEnter: function(){
            ActionTimelineTestLayer.prototype.onEnter.call(this);

            cc.spriteFrameCache.addSpriteFrames("res/armatures/Cowboy0.plist", "res/armatures/Cowboy0.png");

            for (var i = 0; i< 100; i++){
                var node = ccs.csLoader.createNode("res/ActionTimeline/boy_1.ExportJson");
                var action = ccs.actionTimelineCache.createAction("res/ActionTimeline/boy_1.ExportJson");

                node.runAction(action);
                action.gotoFrameAndPlay(70, action.getDuration(), true);

                node.setScale(0.1);
                node.setPosition(i*2,100);
                this.addChild(node);
            }
        },
        title: function(){
            return "Test ActionTimeline performance";
        }
    });

    var CreateAnimationLayer = function(index){
        var pLayer = null;
        switch(index)
        {
            case ActionTimelineTestSceneEnum.TEST_ANIMATIONELEMENT:
                pLayer = new TestActionTimeline();
                break;
            case ActionTimelineTestSceneEnum.TEST_CHANGE_PLAY_SECTION:
                pLayer = new TestChangePlaySection();
                break;
            case ActionTimelineTestSceneEnum.TEST_TIMELINE_FRAME_EVENT:
                pLayer = new TestTimelineFrameEvent();
                break;
            case ActionTimelineTestSceneEnum.TEST_TIMELINE_PERFORMACE:
                pLayer = new TestTimelinePerformance();
                break;
            default:
                break;
        }

        return pLayer;

    };

    var NextAnimationTest = function(){
        ++s_nActionIdx;
        s_nActionIdx = s_nActionIdx % ActionTimelineTestSceneEnum.TEST_ANIMATION_LAYER_COUNT;

        var pLayer = CreateAnimationLayer(s_nActionIdx);
        return pLayer;

    };

    var BackAnimationTest = function(){
        --s_nActionIdx;
        if( s_nActionIdx < 0 )
            s_nActionIdx += ActionTimelineTestSceneEnum.TEST_ANIMATION_LAYER_COUNT;

        var pLayer = CreateAnimationLayer(s_nActionIdx);
        return pLayer;
    };

    var RestartAnimationTest = function(){
        var pLayer = CreateAnimationLayer(s_nActionIdx);
        return pLayer;
    };

    return ActionTimelineTestScene;
})();