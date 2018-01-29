/****************************************************************************
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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

(function(load, baseParser){

    var Parser = baseParser.extend({

        getNodeJson: function(json){
            return json;
        },

        parseNode: function(json, resourcePath){
            var parser = this.parsers[this.getClass(json)];
            var node = null;
            if(parser)
                node = parser.call(this, json, resourcePath);
            else
                cc.log("Can't find the parser : %s", this.getClass(json));

            return node;
        },

        deferred: function(json, resourcePath, node, file){
            ccs.triggerManager.parse(json["Triggers"]||[]);
            if(ccs.sceneReader)
                ccs.sceneReader._node = node;
        },

        setPropertyFromJsonDict: function(node, json){
            var x = (cc.isUndefined(json["x"]))?0:json["x"];
            var y = (cc.isUndefined(json["y"]))?0:json["y"];
            node.setPosition(x, y);

            var bVisible = Boolean((cc.isUndefined(json["visible"]))?1:json["visible"]);
            node.setVisible(bVisible);

            var nTag = (cc.isUndefined(json["objecttag"]))?-1:json["objecttag"];
            node.setTag(nTag);

            var nZorder = (cc.isUndefined(json["zorder"]))?0:json["zorder"];
            node.setLocalZOrder(nZorder);

            var fScaleX = (cc.isUndefined(json["scalex"]))?1:json["scalex"];
            var fScaleY = (cc.isUndefined(json["scaley"]))?1:json["scaley"];
            node.setScaleX(fScaleX);
            node.setScaleY(fScaleY);

            var fRotationZ = (cc.isUndefined(json["rotation"]))?0:json["rotation"];
            node.setRotation(fRotationZ);

            var sName = json["name"] || "";
            node.setName(sName);
        }

    });

    var parser = new Parser();

    parser.parseChild = function(node, objects, resourcePath){
        for (var i = 0; i < objects.length; i++) {
            var child,
                options = objects[i];
            if(options)
                child = this.parseNode(options, resourcePath);
            if(child)
                node.addChild(child);
        }
    };

    var componentsParser = {
        "CCSprite": function(node, component, resourcePath){
            var child = new cc.Sprite();
            loadTexture(component["fileData"], resourcePath, function(path, type){
                if(type === 0)
                    child.setTexture(path);
                else if(type === 1){
                    var spriteFrame = cc.spriteFrameCache.getSpriteFrame(path);
                    child.setSpriteFrame(spriteFrame);
                }
            });
            var render = new ccs.ComRender(child, "CCSprite");
            node.addComponent(render);
            return render;
        },
        "CCTMXTiledMap": function(node, component, resourcePath){
            var child = null;
            loadTexture(component["fileData"], resourcePath, function(path, type){
                if(type === 0)
                    child = new cc.TMXTiledMap(path);
            });
            var render = new ccs.ComRender(child, "CCTMXTiledMap");
            node.addComponent(render);
            return render;
        },
        "CCParticleSystemQuad": function(node, component, resourcePath){
            var child = null;
            loadTexture(component["fileData"], resourcePath, function(path, type){
                if(type === 0)
                    child = new cc.ParticleSystem(path);
                else
                    cc.log("unknown resourcetype on CCParticleSystemQuad!");
                child.setPosition(0, 0);
            });
            var render = new ccs.ComRender(child, "CCParticleSystemQuad");
            node.addComponent(render);
            return render;
        },
        "CCArmature": function(node, component, resourcePath){
            var child = null;
            loadTexture(component["fileData"], resourcePath, function(path, type){
                if(type === 0){
                    var jsonDict = cc.loader.getRes(path);
                    if (!jsonDict) cc.log("Please load the resource [%s] first!", path);
                    var armature_data = jsonDict["armature_data"];
                    var subData = armature_data[0];
                    var name = subData["name"];
                    ccs.armatureDataManager.addArmatureFileInfo(path);
                    child = new ccs.Armature(name);
                }
            });
            if(child){
                var render = new ccs.ComRender(child, "CCArmature");
                node.addComponent(render);
                var actionName = component["selectedactionname"];
                if (actionName && child.getAnimation())
                    child.getAnimation().play(actionName);

                return render;
            }

        },
        "CCComAudio": function(node, component, resourcePath){
            var audio = null;
            loadTexture(component["fileData"], resourcePath, function(path, type){
                if(type === 0){
                    audio = new ccs.ComAudio();
                    audio.preloadEffect(path);
                    var name = component["name"];
                    if(name)
                        audio.setName(name);
                    node.addComponent(audio);
                }
            });
        },
        "CCComAttribute": function(node, component, resourcePath){
            var attribute = null;
            loadTexture(component["fileData"], resourcePath, function(path, type){
                if(type === 0){
                    attribute = new ccs.ComAttribute();
                    if (path !== "")
                        attribute.parse(path);
                    node.addComponent(attribute);
                }else
                    cc.log("unknown resourcetype on CCComAttribute!");
            });
            return attribute;
        },
        "CCBackgroundAudio": function(node, component, resourcePath){
            var audio = null;
            loadTexture(component["fileData"], resourcePath, function(path, type){
                if(type === 0){
                    audio = new ccs.ComAudio();
                    audio.preloadBackgroundMusic(path);
                    audio.setFile(path);var bLoop = Boolean(component["loop"] || 0);
                    audio.setLoop(bLoop);
                    var name = component["name"];
                    if(name)
                        audio.setName(name);
                    node.addComponent(audio);
                    audio.playBackgroundMusic(path, bLoop);
                }
            });
        },
        "GUIComponent": function(node, component, resourcePath){
            var widget = null;
            loadTexture(component["fileData"], resourcePath, function(path, type){
                widget = ccs._load(path, "ccui");
            });
            var render = new ccs.ComRender(widget, "GUIComponent");
            node.addComponent(render);
            return render;
        },
        "CCScene": function(){}
    };
    var loadedPlist = {};
    var loadTexture = function(json, resourcePath, cb){
        if(json != null){
            var path = json["path"];
            var type = json["resourceType"];
            var plist = json["plist"];
            if(!path)
                return;
            if(plist){
                if(cc.loader.getRes(resourcePath + plist)){
                    loadedPlist[resourcePath + plist] = true;
                    cc.spriteFrameCache.addSpriteFrames(resourcePath + plist);
                }else{
                    if(!loadedPlist[resourcePath + plist])
                        cc.log("%s need to be preloaded", resourcePath + plist);
                }
            }
            if(type !== 0)
                cb(path, type);
            else
                cb(resourcePath + path, type);
        }
    };

    parser.parseComponents = function(node, json, resourcePath){
        if(!node || !json)
            return;
        json.forEach(function(component){
            var parser = componentsParser[component["classname"]];
            var render = null;
            if(parser)
                render = parser(node, component, resourcePath);
            else
                cc.log("Can't find the component parser : %s", component["classname"]);
            var name = component["name"];
            if(render && name){
                render.setName(name);
            }
        });
    };

    parser.registerParser("CCNode", function(options, resourcePath){
        var node = new cc.Node();
        this.setPropertyFromJsonDict(node, options);
        this.parseChild.call(this, node, options["gameobjects"], resourcePath);
        this.parseComponents(node, options["components"], resourcePath);
        var size = options["CanvasSize"];
        if (size)
            node.setContentSize(cc.size(size["_width"], size["_height"]));

        return node;
    });

    load.registerParser("scene", "*", parser);


})(ccs._load, ccs._parser);
