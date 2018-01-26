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
            return json["action"];
        },

        parseNode: function(json, resourcePath, file){
            if(!json)
                return null;
            if(cache[file])
                return cache[file].clone();

            var self = this,
                action = new ccs.ActionTimeline();

            action.setDuration(json["duration"]);
            action.setTimeSpeed(json["speed"] || 1);
            //The process of analysis
            var timelines = json["timelines"];
            timelines.forEach(function(timeline){
                var parser = self.parsers[timeline["frameType"]];
                var frame;
                if(parser)
                    frame = parser.call(self, timeline, resourcePath);
                else
                    cc.log("parser does not exist : %s", timeline["frameType"]);
                if(frame)
                    action.addTimeline(frame);

                if(timeline["frameType"] === "ColorFrame"){
                    action.addTimeline(
                        self.parsers["AlphaFrame"].call(self, timeline, resourcePath)
                    );
                }
            });

            cache[file] = action;
            cache[file].retain();
            return action.clone();
        }

    });

    var parser = new Parser();

    var frameList = [
        {
            name: "PositionFrame",
            handle: function(options){
                var frame = new ccs.PositionFrame();
                var x = options["x"];
                var y = options["y"];
                frame.setPosition(cc.p(x,y));
                return frame;
            }
        },
        {
            name: "VisibleFrame",
            handle: function(options){
                var frame = new ccs.VisibleFrame();
                var visible = options["value"];
                frame.setVisible(visible);
                return frame;
            }
        },
        {
            name: "ScaleFrame",
            handle: function(options){
                var frame = new ccs.ScaleFrame();
                var scalex = options["x"];
                var scaley = options["y"];
                frame.setScaleX(scalex);
                frame.setScaleY(scaley);
                return frame;
            }
        },
        {
            name: "RotationFrame",
            handle: function(options){
                var frame = new ccs.RotationFrame();
                var rotation = options["rotation"];
                frame.setRotation(rotation);
                return frame;
            }
        },
        {
            name: "SkewFrame",
            handle: function(options){
                var frame = new ccs.SkewFrame();
                var skewx = options["x"];
                var skewy = options["y"];
                frame.setSkewX(skewx);
                frame.setSkewY(skewy);
                return frame;
            }
        },
        {
            name: "RotationSkewFrame",
            handle: function(options){
                var frame = new ccs.RotationSkewFrame();
                var skewx = options["x"];
                var skewy = options["y"];
                frame.setSkewX(skewx);
                frame.setSkewY(skewy);
                return frame;
            }
        },
        {
            name: "AnchorFrame",
            handle: function(options){
                var frame = new ccs.AnchorPointFrame();
                var anchorx = options["x"];
                var anchory = options["y"];
                frame.setAnchorPoint(cc.p(anchorx, anchory));
                return frame;
            }
        },
        {
            name: "InnerActionFrame",
            handle: function(options){
                var frame = new ccs.InnerActionFrame();
                var type = options["innerActionType"];
                var startFrame = options["startFrame"];
                frame.setInnerActionType(type);
                frame.setStartFrameIndex(startFrame);
                return frame;
            }
        },
        {
            name: "ColorFrame",
            handle: function(options){
                var frame = new ccs.ColorFrame();
                var red   = options["red"];
                var green = options["green"];
                var blue  = options["blue"];
                frame.setColor(cc.color(red, green, blue));
                var alphaFrame = new ccs.AlphaFrame();
                var alpha = options["alpha"];
                alphaFrame.setAlpha(alpha);
                return frame;
            }
        },
        {
            name: "AlphaFrame",
            handle: function(options){
                var frame = new ccs.AlphaFrame();
                var alpha = options["alpha"];
                frame.setAlpha(alpha);
                return frame;
            }
        },
        {
            name: "TextureFrame",
            handle: function(options){
                var frame = new ccs.TextureFrame();
                var texture = options["value"];
                if(texture != null) {
                    var path = texture;
                    var spriteFrame = cc.spriteFrameCache.getSpriteFrame(path);
                    if(spriteFrame == null){
                        var jsonPath = ccs.csLoader.getJsonPath();
                        path = jsonPath + texture;
                    }
                    frame.setTextureName(path);
                }
                return frame;
            }
        },
        {
            name: "EventFrame",
            handle: function(options){
                var frame = new ccs.EventFrame();
                var evnt = options["value"];
                if(evnt != null)
                    frame.setEvent(evnt);
                return frame;
            }
        },
        {
            name: "ZOrderFrame",
            handle: function(options){
                var frame = new ccs.ZOrderFrame();
                var zorder = options["value"];
                frame.setZOrder(zorder);
                return frame;
            }
        }
    ];

    frameList.forEach(function(item){
        parser.registerParser(item.name, function(options, resourcePath){
            var timeline = new ccs.Timeline();
            timeline.setActionTag(options["actionTag"]);

            var frames = options["frames"];
            if(frames && frames.length){
                frames.forEach(function(frameData){
                    var frame = item.handle(frameData);
                    frame.setFrameIndex(frameData["frameIndex"]);
                    frame.setTween(frameData["tween"]);
                    timeline.addFrame(frame);
                });
            }
            return timeline;
        });
    });

    load.registerParser("action", "0.*", parser);
    load.registerParser("action", "1.*", parser);

})(ccs._load, ccs._parser);
