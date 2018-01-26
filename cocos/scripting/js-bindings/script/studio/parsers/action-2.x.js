/****************************************************************************
 Copyright (c) 2013-2017 Chukong Technologies Inc.

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

    var cache = {};

    var Parser = baseParser.extend({

        getNodeJson: function(json){
            return json["Content"]["Content"]["Animation"];
        },

        parseNode: function(json, resourcePath, file){
            if(!json)
                return null;
            if(cache[file])
                return cache[file].clone();

            var self = this,
                action = new ccs.ActionTimeline();

            action.setDuration(json["Duration"]);
            action.setTimeSpeed(json["Speed"] || 1);

            //The process of analysis
            var timelines = json["Timelines"];
            timelines.forEach(function(timeline){
                var parser = self.parsers[timeline["Property"]];
                var frame;
                if(parser)
                    frame = parser.call(self, timeline, resourcePath);
                else
                    cc.log("parser does not exist : %s", timeline["Property"]);
                if(frame)
                    action.addTimeline(frame);
            });

            cache[file] = action;
            cache[file].retain();
            return action.clone();
        },

        deferred: function(json, resourcePath, action, file){
            var animationlist = json["Content"]["Content"]["AnimationList"];
            var length = animationlist ? animationlist.length : 0;
            for (var i = 0; i < length; i++){
                var animationdata = animationlist[i];
                var info = { name: null, startIndex: null, endIndex: null };
                info.name = animationdata["Name"];
                info.startIndex = animationdata["StartIndex"];
                info.endIndex = animationdata["EndIndex"];
                action.addAnimationInfo(info);
            }
        }

    });
    var parser = new Parser();

    var frameList = [
        {
            name: "Position",
            handle: function(options){
                var frame = new ccs.PositionFrame();
                var x = options["X"];
                var y = options["Y"];
                frame.setPosition(cc.p(x,y));
                return frame;
            }
        },
        {
            name: "VisibleForFrame",
            handle: function(options){
                var frame = new ccs.VisibleFrame();
                var visible = options["Value"];
                frame.setVisible(visible);
                return frame;
            }
        },
        {
            name: "Scale",
            handle: function(options){
                var frame = new ccs.ScaleFrame();
                var scalex = options["X"];
                var scaley = options["Y"];
                frame.setScaleX(scalex);
                frame.setScaleY(scaley);
                return frame;
            }
        },
        {
            name: "Rotation",
            handle: function(options){
                var frame = new ccs.RotationFrame();
                var rotation = options["Rotation"] || options["Value"] || 0;
                frame.setRotation(rotation);
                return frame;
            }
        },
        {
            name: "Skew",
            handle: function(options){
                var frame = new ccs.SkewFrame();
                var skewx = options["X"];
                var skewy = options["Y"];
                frame.setSkewX(skewx);
                frame.setSkewY(skewy);
                return frame;
            }
        },
        {
            name: "RotationSkew",
            handle: function(options){
                var frame = new ccs.RotationSkewFrame();
                var skewx = options["X"];
                var skewy = options["Y"];
                frame.setSkewX(skewx);
                frame.setSkewY(skewy);
                return frame;
            }
        },
        {
            name: "Anchor",
            handle: function(options){
                var frame = new ccs.AnchorPointFrame();
                var anchorx = options["X"];
                var anchory = options["Y"];
                frame.setAnchorPoint(cc.p(anchorx, anchory));
                return frame;
            }
        },{
            name: "AnchorPoint",
            handle: function(options){
                var frame = new ccs.AnchorPointFrame();
                var anchorx = options["X"];
                var anchory = options["Y"];
                frame.setAnchorPoint(cc.p(anchorx, anchory));
                return frame;
            }
        },{
            name: "InnerAction",
            handle: function(options){
                var frame = new ccs.InnerActionFrame();
                var type = options["InnerActionType"];
                var startFrame = options["StartFrame"];
                frame.setInnerActionType(type);
                frame.setStartFrameIndex(startFrame);
                return frame;
            }
        },
        {
            name: "CColor",
            handle: function(options){
                var frame = new ccs.ColorFrame();
                var color = options["Color"];
                if(!color) color = {};
                color["R"] = color["R"] === undefined ? 255 : color["R"];
                color["G"] = color["G"] === undefined ? 255 : color["G"];
                color["B"] = color["B"] === undefined ? 255 : color["B"];
                frame.setColor(cc.color(color["R"], color["G"], color["B"]));
                return frame;
            }
        },
        {
            name: "Alpha",
            handle: function(options){
                var frame = new ccs.AlphaFrame();
                var alpha = options["Value"];
                frame.setAlpha(alpha);
                return frame;
            }
        },
        {
            name: "FileData",
            handle: function(options, resourcePath){
                var frame, texture, plist, path, spriteFrame;
                frame = new ccs.TextureFrame();
                texture = options["TextureFile"];
                if(texture != null) {
                    plist = texture["Plist"];
                    path = texture["Path"];
                    spriteFrame = cc.spriteFrameCache.getSpriteFrame(path);
                    if(!spriteFrame && plist){
                        if(cc.loader.getRes(resourcePath + plist)){
                            cc.spriteFrameCache.addSpriteFrames(resourcePath + plist);
                            spriteFrame = cc.spriteFrameCache.getSpriteFrame(path);
                        }else{
                            cc.log("%s need to be preloaded", resourcePath + plist);
                        }
                    }
                    if(spriteFrame == null){
                        path = resourcePath + path;
                    }
                    frame.setTextureName(path);
                }
                return frame;
            }
        },
        {
            name: "FrameEvent",
            handle: function(options){
                var frame = new ccs.EventFrame();
                var evnt = options["Value"];
                if(evnt != null)
                    frame.setEvent(evnt);
                return frame;
            }
        },
        {
            name: "ZOrder",
            handle: function(options){
                var frame = new ccs.ZOrderFrame();
                var zorder = options["Value"];
                frame.setZOrder(zorder);
                return frame;
            }
        },
        {
            name: "ActionValue",
            handle: function (options) {

                var frame = new ccs.InnerActionFrame();
                var innerActionType = options["InnerActionType"];

                var currentAnimationFrame = options["CurrentAniamtionName"];

                var singleFrameIndex = options["SingleFrameIndex"];

                var frameIndex = options["FrameIndex"];
                if(frameIndex !== undefined)
                    frame.setFrameIndex(frameIndex);

                frame.setInnerActionType(ccs.InnerActionType[innerActionType]);
                frame.setSingleFrameIndex(singleFrameIndex);

                frame.setEnterWithName(true);
                if (currentAnimationFrame)
                     frame.setAnimationName(currentAnimationFrame);

                return frame;
            }
        },
        {
            name: "BlendFunc",
            handle: function(options){
                var frame = new ccs.BlendFuncFrame();
                var blendFunc = options["BlendFunc"];
                if(blendFunc && blendFunc["Src"] !== undefined && blendFunc["Dst"] !== undefined)
                    frame.setBlendFunc(new cc.BlendFunc(blendFunc["Src"], blendFunc["Dst"]));
                return frame;
            }
        }
    ];

    var loadEasingDataWithFlatBuffers = function(frame, options){
        var type = options["Type"];
        frame.setTweenType(type);
        var points = options["Points"];
        var result = [];
        if(points){
            points.forEach(function(p){
                result.push(p["X"]);
                result.push(p["Y"]);
            });
            frame.setEasingParams(result);
        }
    };

    frameList.forEach(function(item){
        parser.registerParser(item.name, function(options, resourcePath){
            var timeline = new ccs.Timeline();
            timeline.setActionTag(options["ActionTag"]);

            var frames = options["Frames"];
            if(frames && frames.length){
                frames.forEach(function(frameData){
                    var frame = item.handle(frameData, resourcePath);
                    frame.setFrameIndex(frameData["FrameIndex"]);
                    var tween = frameData["Tween"] != null ? frameData["Tween"] : true;
                    frame.setTween(tween);
                    //https://github.com/cocos2d/cocos2d-x/pull/11388/files
                    var easingData = frameData["EasingData"];
                    if(easingData)
                        loadEasingDataWithFlatBuffers(frame, easingData);
                    timeline.addFrame(frame);
                });
            }
            return timeline;
        });
    });

    load.registerParser("action", "*", parser);

})(ccs._load, ccs._parser);
