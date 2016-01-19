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

/************************************************************
 *
 * Constructors with built in init function
 *
 ************************************************************/

jsb.EventListenerAssetsManager.prototype._ctor = function(assetsManager, callback) {
    callback !== undefined && this.init(assetsManager, callback);
};



cc.ControlButton.prototype._ctor = function(label, backgroundSprite, fontSize, fontName, autoSizeWithLabel ){
    if (autoSizeWithLabel !== undefined && backgroundSprite) {
        this.initWithLabelAndBackgroundSprite(label, backgroundSprite, autoSizeWithLabel);
    }
    else if(fontName !== undefined && fontSize !== undefined) {
        this.initWithTitleAndFontNameAndFontSize(label, fontName, fontSize);
    }
    else if(backgroundSprite !== undefined) {
        this.initWithLabelAndBackgroundSprite(label, backgroundSprite, true);
    }
    else if(label !== undefined) {
        this.initWithBackgroundSprite(label);
    }
    else {
        this.init();
    }
};


cc.ControlColourPicker.prototype._ctor = function(){
    this.init();
};

cc.ControlPotentiometer.prototype._ctor = function(backgroundFile, progressFile, thumbFile){
    if (thumbFile != undefined) {
        // Prepare track for potentiometer
        var backgroundSprite = cc.Sprite.create(backgroundFile);

        // Prepare thumb for potentiometer
        var thumbSprite = cc.Sprite.create(thumbFile);

        // Prepare progress for potentiometer
        var progressTimer = cc.ProgressTimer.create(cc.Sprite.create(progressFile));
        this.initWithTrackSprite_ProgressTimer_ThumbSprite(backgroundSprite, progressTimer, thumbSprite);
    }
};

cc.ControlSlider.prototype._ctor = function(bgFile, progressFile, thumbFile){
    if (thumbFile != undefined) {
        // Prepare background for slider
        bgSprite = cc.Sprite.create(bgFile);

        // Prepare progress for slider
        progressSprite = cc.Sprite.create(progressFile);

        // Prepare thumb (menuItem) for slider
        thumbSprite = cc.Sprite.create(thumbFile);

        this.initWithSprites(bgSprite, progressSprite, thumbSprite);
    }
};

cc.ControlStepper.prototype._ctor = function(minusSprite, plusSprite){
    plusSprite !== undefined && this.initWithMinusSpriteAndPlusSprite(minusSprite, plusSprite);
};

cc.ControlSwitch.prototype._ctor = function(maskSprite, onSprite, offSprite, thumbSprite, onLabel, offLabel){
    offLabel !== undefined && this.initWithMaskSprite(maskSprite, onSprite, offSprite, thumbSprite, onLabel, offLabel);
};

cc.TableView.prototype._ctor = function(dataSouurce, size, container){
    container == undefined ? this._init(dataSouurce, size) : this._init(dataSouurce, size, container);
};

cc.ScrollView.prototype._ctor = function(size, container) {
    size == undefined ? this.init() : (container ? this.initWithViewSize(size, container) : this.initWithViewSize(size));
};


