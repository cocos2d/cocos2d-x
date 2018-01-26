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

    var Parser = baseParser.extend({

        addSpriteFrame: function(textures, resourcePath){
            if(!textures) return;
            for (var i = 0; i < textures.length; i++) {
                cc.spriteFrameCache.addSpriteFrames(resourcePath + textures[i]);
            }
        },

        pretreatment: function(json, resourcePath){
            this.addSpriteFrame(json["textures"], resourcePath);
        },

        deferred: function(json, resourcePath, node, file){
            if(node){
                var version = json["Version"] || json["version"];
                var versionNum = ccs.uiReader.getVersionInteger(version);
                ccs.actionManager.initWithDictionary(file, json["animation"], node, versionNum);
                node.setContentSize(cc.size(json["designWidth"], json["designHeight"]));
            }
        }

    });
    var parser = new Parser();


    parser.generalAttributes = function(widget, options){
        var ignoreSizeExsit = options["ignoreSize"];
        if(ignoreSizeExsit != null)
            widget.ignoreContentAdaptWithSize(ignoreSizeExsit);

        if (options["sizeType"])
        {
            widget.setSizeType(options["sizeType"]);
        }

        if (options["positionType"])
        {
            widget.setPositionType(options["positionType"]);
        }

        widget.setSizePercent(cc.p(options["sizePercentX"], options["sizePercentY"]));
        widget.setPositionPercent(cc.p(options["positionPercentX"], options["positionPercentY"]));

        /* adapt screen */
        var w = 0, h = 0;
        var adaptScreen = options["adaptScreen"];
        if (adaptScreen) {
            var screenSize = cc.director.getWinSize();
            w = screenSize.width;
            h = screenSize.height;
        } else {
            w = options["width"];
            h = options["height"];
        }
        widget.setContentSize(w, h);

        widget.setTag(options["tag"]);
        widget.setActionTag(options["actiontag"]);
        widget.setTouchEnabled(options["touchAble"]);
        var name = options["name"];
        var widgetName = name ? name : "default";
        widget.setName(widgetName);

        var x = options["x"];
        var y = options["y"];
        widget.setPosition(x, y);

        var sx = options["scaleX"]!=null ? options["scaleX"] : 1;
        widget.setScaleX(sx);

        var sy = options["scaleY"]!=null ? options["scaleY"] : 1;
        widget.setScaleY(sy);

        var rt = options["rotation"] || 0;
        widget.setRotation(rt);

        var vb = options["visible"] || false;
        if(vb != null)
            widget.setVisible(vb);
        widget.setLocalZOrder(options["ZOrder"]);

        var layout = options["layoutParameter"];
        if(layout != null){
            var layoutParameterDic = options["layoutParameter"];
            var paramType = layoutParameterDic["type"];
            var parameter = null;

            switch(paramType){
                case 0:
                    break;
                case 1:
                    parameter = new ccui.LinearLayoutParameter();
                    var gravity = layoutParameterDic["gravity"];
                    parameter.setGravity(gravity);
                    break;
                case 2:
                    parameter = new ccui.RelativeLayoutParameter();
                    var rParameter = parameter;
                    var relativeName = layoutParameterDic["relativeName"];
                    rParameter.setRelativeName(relativeName);
                    var relativeToName = layoutParameterDic["relativeToName"];
                    rParameter.setRelativeToWidgetName(relativeToName);
                    var align = layoutParameterDic["align"];
                    rParameter.setAlign(align);
                    break;
                default:
                    break;
            }
            if(parameter != null){
                var mgl = layoutParameterDic["marginLeft"]||0;
                var mgt = layoutParameterDic["marginTop"]||0;
                var mgr = layoutParameterDic["marginRight"]||0;
                var mgb = layoutParameterDic["marginDown"]||0;
                parameter.setMargin(mgl, mgt, mgr, mgb);
                widget.setLayoutParameter(parameter);
            }
        }
    };

    parser.colorAttributes = function(widget, options){
        var op = options["opacity"];
        if(op != null)
            widget.setOpacity(op);
        var colorR = options["colorR"];
        var colorG = options["colorG"];
        var colorB = options["colorB"];
        widget.setColor(cc.color((colorR == null) ? 255 : colorR, (colorG == null) ? 255 : colorG, (colorB == null) ? 255 : colorB));

        widget.setFlippedX(options["flipX"]);
        widget.setFlippedY(options["flipY"]);
    };

    parser.anchorPointAttributes = function(widget, options){
        var isAnchorPointXExists = options["anchorPointX"];
        var anchorPointXInFile;
        if (isAnchorPointXExists != null)
            anchorPointXInFile = options["anchorPointX"];
        else
            anchorPointXInFile = widget.getAnchorPoint().x;

        var isAnchorPointYExists = options["anchorPointY"];
        var anchorPointYInFile;
        if (isAnchorPointYExists != null)
            anchorPointYInFile = options["anchorPointY"];
        else
            anchorPointYInFile = widget.getAnchorPoint().y;

        if (isAnchorPointXExists != null || isAnchorPointYExists != null)
            widget.setAnchorPoint(cc.p(anchorPointXInFile, anchorPointYInFile));
    };

    parser.parseChild = function(widget, options, resourcePath){
        var children = options["children"];
        for (var i = 0; i < children.length; i++) {
            var child = this.parseNode(children[i], resourcePath);
            if(child){
                if(widget instanceof ccui.PageView)
                    widget.addPage(child);
                else {
                    if(widget instanceof ccui.ListView){
                        widget.pushBackCustomItem(child);
                    } else {
                        if(!(widget instanceof ccui.Layout)) {
                            if(child.getPositionType() === ccui.Widget.POSITION_PERCENT) {
                                var position = child.getPositionPercent();
                                var anchor = widget.getAnchorPoint();
                                child.setPositionPercent(cc.p(position.x + anchor.x, position.y + anchor.y));
                            }
                            var AnchorPointIn = widget.getAnchorPointInPoints();
                            child.setPosition(cc.p(child.getPositionX() + AnchorPointIn.x, child.getPositionY() + AnchorPointIn.y));
                        }
                        widget.addChild(child);
                    }
                }
            }
        }
    };

    var getPath = function(res, type, path, cb){
        if(path){
            if(type === 0)
                cb(res + path, type);
            else
                cb(path, type);
        }
    };

    /**
     * Panel parser (UILayout)
     */
    parser.LayoutAttributes = function(widget, options, resourcePath){
        var w = 0, h = 0;
        var adaptScreen = options["adaptScreen"];
        if (adaptScreen){
            var screenSize = cc.director.getWinSize();
            w = screenSize.width;
            h = screenSize.height;
        }else{
            w = options["width"];
            h = options["height"];
        }
        widget.setSize(cc.size(w, h));

        widget.setClippingEnabled(options["clipAble"]);

        var backGroundScale9Enable = options["backGroundScale9Enable"];
        widget.setBackGroundImageScale9Enabled(backGroundScale9Enable);
        var cr = options["bgColorR"];
        var cg = options["bgColorG"];
        var cb = options["bgColorB"];

        var scr = options["bgStartColorR"];
        var scg = options["bgStartColorG"];
        var scb = options["bgStartColorB"];

        var ecr = options["bgEndColorR"];
        var ecg = options["bgEndColorG"];
        var ecb = options["bgEndColorB"];

        var bgcv1 = options["vectorX"];
        var bgcv2 = options["vectorY"];
        widget.setBackGroundColorVector(cc.p(bgcv1, bgcv2));

        var co = options["bgColorOpacity"];

        var colorType = options["colorType"];
        widget.setBackGroundColorType(colorType/*ui.LayoutBackGroundColorType(colorType)*/);
        widget.setBackGroundColor(cc.color(scr, scg, scb), cc.color(ecr, ecg, ecb));
        widget.setBackGroundColor(cc.color(cr, cg, cb));
        widget.setBackGroundColorOpacity(co);


        var imageFileNameDic = options["backGroundImageData"];
        if(imageFileNameDic){
            getPath(resourcePath, imageFileNameDic["resourceType"], imageFileNameDic["path"], function(path, type){
                widget.setBackGroundImage(path, type);
            });
        }

        if (backGroundScale9Enable){
            var cx = options["capInsetsX"];
            var cy = options["capInsetsY"];
            var cw = options["capInsetsWidth"];
            var ch = options["capInsetsHeight"];
            widget.setBackGroundImageCapInsets(cc.rect(cx, cy, cw, ch));
        }
        if (options["layoutType"])
        {
            widget.setLayoutType(options["layoutType"]);
        }
    };
    /**
     * Button parser (UIButton)
     */
    parser.ButtonAttributes = function(widget, options, resourcePath){
        var button = widget;
        var scale9Enable = options["scale9Enable"];
        button.setScale9Enabled(scale9Enable);

        var normalDic = options["normalData"];
        getPath(resourcePath, normalDic["resourceType"], normalDic["path"], function(path, type){
            button.loadTextureNormal(path, type);
        });
        var pressedDic = options["pressedData"];
        getPath(resourcePath, pressedDic["resourceType"], pressedDic["path"], function(path, type){
            button.loadTexturePressed(path, type);
        });
        var disabledDic = options["disabledData"];
        getPath(resourcePath, disabledDic["resourceType"], disabledDic["path"], function(path, type){
            button.loadTextureDisabled(path, type);
        });
        if (scale9Enable) {
            var cx = options["capInsetsX"];
            var cy = options["capInsetsY"];
            var cw = options["capInsetsWidth"];
            var ch = options["capInsetsHeight"];

            button.setCapInsets(cc.rect(cx, cy, cw, ch));
            var sw = options["scale9Width"];
            var sh = options["scale9Height"];
            if (sw != null && sh != null)
                button.setSize(cc.size(sw, sh));
        }
        var text = options["text"];
        if (text != null)
            button.setTitleText(text);

        var cr = options["textColorR"];
        var cg = options["textColorG"];
        var cb = options["textColorB"];
        var cri = cr!==null?options["textColorR"]:255;
        var cgi = cg!==null?options["textColorG"]:255;
        var cbi = cb!==null?options["textColorB"]:255;

        button.setTitleColor(cc.color(cri,cgi,cbi));
        var fs = options["fontSize"];
        if (fs != null)
            button.setTitleFontSize(options["fontSize"]);
        var fn = options["fontName"];
        if (fn)
            button.setTitleFontName(options["fontName"]);
    };
    /**
     * CheckBox parser (UICheckBox)
     */
    parser.CheckBoxAttributes = function(widget, options, resourcePath){
        //load background image
        var backGroundDic = options["backGroundBoxData"];
        getPath(resourcePath, backGroundDic["resourceType"], backGroundDic["path"], function(path, type){
            widget.loadTextureBackGround(path, type);
        });

        //load background selected image
        var backGroundSelectedDic = options["backGroundBoxSelectedData"];
        getPath(
            resourcePath,
            backGroundSelectedDic["resourceType"] || backGroundDic["resourceType"],
            backGroundSelectedDic["path"] || backGroundDic["path"],
            function(path, type){
            widget.loadTextureBackGroundSelected(path, type);
        });

        //load frontCross image
        var frontCrossDic = options["frontCrossData"];
        getPath(resourcePath, frontCrossDic["resourceType"], frontCrossDic["path"], function(path, type){
            widget.loadTextureFrontCross(path, type);
        });

        //load backGroundBoxDisabledData
        var backGroundDisabledDic = options["backGroundBoxDisabledData"];
        getPath(
            resourcePath,
            backGroundDisabledDic["resourceType"] || frontCrossDic["resourceType"],
            backGroundDisabledDic["path"] || frontCrossDic["path"],
            function(path, type){
            widget.loadTextureBackGroundDisabled(path, type);
        });

        ///load frontCrossDisabledData
        var frontCrossDisabledDic = options["frontCrossDisabledData"];
        getPath(resourcePath, frontCrossDisabledDic["resourceType"], frontCrossDisabledDic["path"], function(path, type){
            widget.loadTextureFrontCrossDisabled(path, type);
        });

        if (options["selectedState"])
            widget.setSelected(options["selectedState"]);
    };
    /**
     * ImageView parser (UIImageView)
     */
    parser.ImageViewAttributes = function(widget, options, resourcePath){
        var imageFileNameDic = options["fileNameData"]
        getPath(resourcePath, imageFileNameDic["resourceType"], imageFileNameDic["path"], function(path, type){
            widget.loadTexture(path, type);
        });

        var scale9EnableExist = options["scale9Enable"];
        var scale9Enable = false;
        if (scale9EnableExist){
            scale9Enable = options["scale9Enable"];
        }
        widget.setScale9Enabled(scale9Enable);

        if (scale9Enable){
            var sw = options["scale9Width"];
            var sh = options["scale9Height"];
            if (sw && sh)
            {
                var swf = options["scale9Width"];
                var shf = options["scale9Height"];
                widget.setSize(cc.size(swf, shf));
            }

            var cx = options["capInsetsX"];
            var cy = options["capInsetsY"];
            var cw = options["capInsetsWidth"];
            var ch = options["capInsetsHeight"];

            widget.setCapInsets(cc.rect(cx, cy, cw, ch));

        }
    };
    /**
     * TextAtlas parser (UITextAtlas)
     */
    parser.TextAtlasAttributes = function(widget, options, resourcePath){
        var sv = options["stringValue"];
        var cmf = options["charMapFileData"];   // || options["charMapFile"];
        var iw = options["itemWidth"];
        var ih = options["itemHeight"];
        var scm = options["startCharMap"];
        if (sv != null && cmf && iw != null && ih != null && scm != null){
            var cmftDic = options["charMapFileData"];
            var cmfType = cmftDic["resourceType"];
            switch (cmfType){
                case 0:
                    var tp_c = resourcePath;
                    var cmfPath = cmftDic["path"];
                    var cmf_tp = tp_c + cmfPath;
                    widget.setProperty(sv, cmf_tp, iw, ih, scm);
                    break;
                case 1:
                    cc.log("Wrong res type of LabelAtlas!");
                    break;
                default:
                    break;
            }
        }
    };
    /**
     * TextBMFont parser (UITextBMFont)
     */
    parser.TextBMFontAttributes = function(widget, options, resourcePath){
        var cmftDic = options["fileNameData"];
        var cmfType = cmftDic["resourceType"];
        switch (cmfType) {
            case 0:
                var tp_c = resourcePath;
                var cmfPath = cmftDic["path"];
                var cmf_tp = tp_c + cmfPath;
                widget.setFntFile(cmf_tp);
                break;
            case 1:
                cc.log("Wrong res type of LabelAtlas!");
                break;
            default:
                break;
        }

        var text = options["text"];
        widget.setString(text);
    };
    /**
     * Text parser (UIText)
     */
    var regTTF = /\.ttf$/;
    parser.TextAttributes = function(widget, options, resourcePath){
        var touchScaleChangeAble = options["touchScaleEnable"];
        widget.setTouchScaleChangeEnabled(touchScaleChangeAble);
        var text = options["text"];
        widget.setString(text);
        var fs = options["fontSize"];
        if (fs != null){
            widget.setFontSize(options["fontSize"]);
        }
        var fn = options["fontName"];
        if (fn != null){
            if(cc.sys.isNative){
                if(regTTF.test(fn)){
                    widget.setFontName(cc.path.join(cc.loader.resPath, resourcePath, fn));
                }else{
                    widget.setFontName(fn);
                }
            }else{
                widget.setFontName(fn.replace(regTTF, ''));
            }
        }
        var aw = options["areaWidth"];
        var ah = options["areaHeight"];
        if (aw != null && ah != null){
            var size = cc.size(options["areaWidth"], options["areaHeight"]);
            widget.setTextAreaSize(size);
        }
        var ha = options["hAlignment"];
        if (ha != null){
            widget.setTextHorizontalAlignment(options["hAlignment"]);
        }
        var va = options["vAlignment"];
        if (va != null){
            widget.setTextVerticalAlignment(options["vAlignment"]);
        }
    };
    /**
     * ListView parser (UIListView)
     */
    parser.ListViewAttributes = function(widget, options, resoutcePath){
        parser.ScrollViewAttributes(widget, options,resoutcePath);
        var direction = options["direction"];
        widget.setDirection(direction);
        var gravity = options["gravity"];
        widget.setGravity(gravity);
        var itemMargin = options["itemMargin"];
        widget.setItemsMargin(itemMargin);
    };
    /**
     * LoadingBar parser (UILoadingBar)
     */
    parser.LoadingBarAttributes = function(widget, options, resourcePath){
        var imageFileNameDic = options["textureData"];
        getPath(resourcePath, imageFileNameDic["resourceType"], imageFileNameDic["path"], function(path, type){
            widget.loadTexture(path, type);
        });

        var scale9Enable = options["scale9Enable"];
        widget.setScale9Enabled(scale9Enable);

        if (scale9Enable){
            var cx = options["capInsetsX"];
            var cy = options["capInsetsY"];
            var cw = options["capInsetsWidth"];
            var ch = options["capInsetsHeight"];

            widget.setCapInsets(cc.rect(cx, cy, cw, ch));

            var width = options["width"];
            var height = options["height"];
            widget.setSize(cc.size(width, height));
        }

        widget.setDirection(options["direction"]);
        widget.setPercent(options["percent"]);
    };
    /**
     * PageView parser (UIPageView)
     */
    parser.PageViewAttributes = parser.LayoutAttributes;
    /**
     * ScrollView parser (UIScrollView)
     */
    parser.ScrollViewAttributes = function(widget, options, resoutcePath){
        parser.LayoutAttributes(widget, options,resoutcePath);
        var innerWidth = options["innerWidth"]!=null ? options["innerWidth"] : 200;
        var innerHeight = options["innerHeight"]!=null ? options["innerHeight"] : 200;
        widget.setInnerContainerSize(cc.size(innerWidth, innerHeight));

        var direction = options["direction"]!=null ? options["direction"] : 1;
        widget.setDirection(direction);
        widget.setBounceEnabled(options["bounceEnable"]);
    };
    /**
     * Slider parser (UISlider)
     */
    parser.SliderAttributes = function(widget, options, resourcePath){

        var slider = widget;

        var barTextureScale9Enable = options["scale9Enable"];
        slider.setScale9Enabled(barTextureScale9Enable);
        var bt = options["barFileName"];
        var barLength = options["length"];

        var imageFileNameDic = options["barFileNameData"];
        var imageFileType = imageFileNameDic["resourceType"];
        var imageFileName = imageFileNameDic["path"];

        if(bt != null){
            if(barTextureScale9Enable){
                getPath(resourcePath, imageFileType, imageFileName, function(path, type){
                    slider.loadBarTexture(path, type);
                });
                slider.setSize(cc.size(barLength, slider.getContentSize().height));
            }
        }else{
            getPath(resourcePath, imageFileType, imageFileName, function(path, type){
                slider.loadBarTexture(path, type);
            });
        }

        var normalDic = options["ballNormalData"];
        getPath(resourcePath, normalDic["resourceType"], normalDic["path"], function(path, type){
            slider.loadSlidBallTextureNormal(path, type);
        });

        var pressedDic = options["ballPressedData"];
        getPath(
            resourcePath,
            pressedDic["resourceType"] || normalDic["resourceType"],
            pressedDic["path"] || normalDic["path"],
            function(path, type){
                slider.loadSlidBallTexturePressed(path, type);
        });

        var disabledDic = options["ballDisabledData"];
        getPath(resourcePath, disabledDic["resourceType"], disabledDic["path"], function(path, type){
            slider.loadSlidBallTextureDisabled(path, type);
        });

        var progressBarDic = options["progressBarData"];
        getPath(resourcePath, progressBarDic["resourceType"], progressBarDic["path"], function(path, type){
            slider.loadProgressBarTexture(path, type);
        });
    };
    /**
     * TextField parser (UITextField)
     */
    parser.TextFieldAttributes = function(widget, options, resourcePath){
        var ph = options["placeHolder"];
        if(ph)
            widget.setPlaceHolder(ph);
        widget.setString(options["text"]||"");
        var fs = options["fontSize1"];
        if(fs)
            widget.setFontSize(fs);
        var fn = options["fontName"];
        if (fn != null){
            if(cc.sys.isNative){
                if(regTTF.test(fn)){
                    widget.setFontName(cc.path.join(cc.loader.resPath, resourcePath, fn));
                }else{
                    widget.setFontName(fn);
                }
            }else{
                widget.setFontName(fn.replace(regTTF, ''));
            }
        }
        var tsw = options["touchSizeWidth"];
        var tsh = options["touchSizeHeight"];
        if(tsw!=null && tsh!=null)
            widget.setTouchSize(tsw, tsh);

        var dw = options["width"];
        var dh = options["height"];
        if(dw > 0 || dh > 0){
            //textField.setSize(cc.size(dw, dh));
        }
        var maxLengthEnable = options["maxLengthEnable"];
        widget.setMaxLengthEnabled(maxLengthEnable);

        if(maxLengthEnable){
            var maxLength = options["maxLength"];
            widget.setMaxLength(maxLength);
        }
        var passwordEnable = options["passwordEnable"];
        widget.setPasswordEnabled(passwordEnable);
        if(passwordEnable)
            widget.setPasswordStyleText(options["passwordStyleText"]);

        var aw = options["areaWidth"];
        var ah = options["areaHeight"];
        if(aw && ah){
            var size = cc.size(aw, ah);
            widget.setTextAreaSize(size);
        }
        var ha = options["hAlignment"];
        if(ha)
            widget.setTextHorizontalAlignment(ha);
        var va = options["vAlignment"];
        if(va)
            widget.setTextVerticalAlignment(va);

        var r = options["colorR"];
        var g = options["colorG"];
        var b = options["colorB"];
        if (r !== undefined && g !== undefined && b !== undefined) {
            widget.setTextColor(cc.color(r, g, b));
        }
    };

    var register = [
        {name: "Panel", object: ccui.Layout, handle: parser.LayoutAttributes},
        {name: "Button", object: ccui.Button, handle: parser.ButtonAttributes},
        {name: "CheckBox", object: ccui.CheckBox, handle: parser.CheckBoxAttributes},
        {name: "ImageView", object: ccui.ImageView, handle: parser.ImageViewAttributes},
        {name: "LabelAtlas", object: ccui.TextAtlas, handle: parser.TextAtlasAttributes},
        {name: "LabelBMFont", object: ccui.TextBMFont, handle: parser.TextBMFontAttributes},
        {name: "Label", object: ccui.Text, handle: parser.TextAttributes},
        {name: "ListView", object: ccui.ListView, handle: parser.ListViewAttributes},
        {name: "LoadingBar", object: ccui.LoadingBar, handle: parser.LoadingBarAttributes},
        {name: "PageView", object: ccui.PageView, handle: parser.PageViewAttributes},
        {name: "ScrollView", object: ccui.ScrollView, handle: parser.ScrollViewAttributes},
        {name: "Slider", object: ccui.Slider, handle: parser.SliderAttributes},
        {name: "TextField", object: ccui.TextField, handle: parser.TextFieldAttributes}
    ];

    register.forEach(function(item){
        parser.registerParser(item.name, function(options, resourcePath){
            var widget = new item.object;
            var uiOptions = options["options"];
            parser.generalAttributes(widget, uiOptions);
            item.handle(widget, uiOptions, resourcePath);
            parser.colorAttributes(widget, uiOptions);
            parser.anchorPointAttributes(widget, uiOptions);
            parser.parseChild.call(this, widget, options, resourcePath);
            return widget;
        });
    });

    load.registerParser("ccui", "*", parser);

})(ccs._load, ccs._parser);
