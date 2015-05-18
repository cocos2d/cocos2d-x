/*
 * Copyright (c) 2014 Chukong Technologies Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

ccui.Widget.prototype.init = ccui.Widget.prototype._init;
ccui.RichText.prototype.init = function(){
    ccui.Widget.prototype.init.call(this);
};
ccui.Slider.prototype.init = function(){
    ccui.Widget.prototype.init.call(this);
    this.setTouchEnabled(true);
};

ccui.Widget.prototype._ctor
    = ccui.RichText.prototype._ctor
    = ccui.Slider.prototype._ctor
    = ccui.Layout.prototype._ctor
    = ccui.ListView.prototype._ctor
    = ccui.PageView.prototype._ctor
    = ccui.ScrollView.prototype._ctor
    = function(){
        this.init();
    }

ccui.Button.prototype._ctor = function (normalImage, selectedImage, disableImage, texType) {
    if(texType !== undefined)
        ccui.Button.prototype.init.call(this, normalImage, selectedImage, disableImage, texType);
    else if(disableImage !== undefined)
        ccui.Button.prototype.init.call(this, normalImage, selectedImage, disableImage);
    else if(selectedImage !== undefined)
        ccui.Button.prototype.init.call(this, normalImage, selectedImage);
    else if(normalImage !== undefined)
        ccui.Button.prototype.init.call(this, normalImage);
    else
        ccui.Widget.prototype.init.call(this);
    
    this.setTouchEnabled(true);
};

ccui.CheckBox.prototype._ctor = function (backGround, backGroundSelected, cross, backGroundDisabled, frontCrossDisabled, texType) {
    if (frontCrossDisabled !== undefined) {
        texType = texType || ccui.Widget.LOCAL_TEXTURE;
        ccui.CheckBox.prototype.init.call(this, backGround, backGroundSelected, cross, backGroundDisabled, frontCrossDisabled, texType);
    }else if(backGroundSelected !== undefined){
        texType = ccui.Widget.LOCAL_TEXTURE;
        cross = backGroundSelected;
        backGroundSelected = backGroundDisabled = frontCrossDisabled = backGround;
        ccui.CheckBox.prototype.init.call(this, backGround, backGroundSelected, cross, backGroundDisabled, frontCrossDisabled, texType);
    }
    else {
        ccui.Widget.prototype.init.call(this);
    }

    this.setSelected(false);
    this.setTouchEnabled(true);
};

ccui.ImageView.prototype._ctor = function(imageFileName, texType){
    if(imageFileName !== undefined){
        texType = texType || ccui.Widget.LOCAL_TEXTURE;
        ccui.ImageView.prototype._init.call(this, imageFileName, texType);
    }
    else
        ccui.Widget.prototype.init.call(this);
}

ccui.LoadingBar.prototype._ctor = function(textureName, percentage){
    ccui.Widget.prototype.init.call(this);

    if(textureName !== undefined)
        this.loadTexture(textureName);
    if(percentage !== undefined)
        this.setPercent(percentage);
};

ccui.TextAtlas.prototype._ctor = function(stringValue, charMapFile, itemWidth, itemHeight, startCharMap){
    ccui.Widget.prototype.init.call(this);
    startCharMap !== undefined && this.setProperty(stringValue, charMapFile, itemWidth, itemHeight, startCharMap);
};

ccui.Text.prototype._ctor = function(textContent, fontName, fontSize){
    if(fontSize !== undefined)
        ccui.Text.prototype.init.call(this, textContent, fontName, fontSize);
    else
        ccui.Widget.prototype.init.call(this);
};

ccui.TextBMFont.prototype._ctor = function(text, filename){
    ccui.Widget.prototype.init.call(this);

    if(filename !== undefined){
        this.setFntFile(filename);
        this.setString(text);
    }
};

ccui.TextField.prototype._ctor = function(placeholder, fontName, fontSize){
    ccui.Widget.prototype.init.call(this);
    this.setTouchEnabled(true);

    if (placeholder !== undefined)
        this.setPlaceHolder(placeholder);
    if (fontName !== undefined)
        this.setFontName(fontName);
    if (fontSize !== undefined)
        this.setFontSize(fontSize);
};

ccui.RichElementText.prototype._ctor = function(tag, color, opacity, text, fontName, fontSize){
    fontSize !== undefined && this.init(tag, color, opacity, text, fontName, fontSize);
};

ccui.RichElementImage.prototype._ctor = function(tag, color, opacity, filePath){
    filePath !== undefined && this.init(tag, color, opacity, filePath);
};

ccui.RichElementCustomNode.prototype._ctor = function(tag, color, opacity, customNode){
    customNode !== undefined && this.init(tag, color, opacity, customNode);
};

cc.Scale9Sprite.prototype._ctor = function(file, rect, capInsets){
    rect = rect || cc.rect(0, 0, 0, 0);
    capInsets = capInsets || cc.rect(0, 0, 0, 0);
    if(file != undefined){
        if(file instanceof cc.SpriteFrame)
            this.initWithSpriteFrame(file, rect);
        else{
            var frame = cc.spriteFrameCache.getSpriteFrame(file);
            if(frame != null)
                this.initWithSpriteFrame(frame, rect);
            else
                this.initWithFile(file, rect, capInsets);
        }
    }else{
        this.init();
    }
};

cc.EditBox.prototype._ctor = function(size, normal9SpriteBg, press9SpriteBg, disabled9SpriteBg){
    normal9SpriteBg && this.initWithSizeAndBackgroundSprite(size, normal9SpriteBg);
};
