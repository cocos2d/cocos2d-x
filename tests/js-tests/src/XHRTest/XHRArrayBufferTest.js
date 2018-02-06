/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011-2012 cocos2d-x.org
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

var XHRArrayBufferTestScene = TestScene.extend({
    ctor:function () {
        this._super(true);
        var xhrLayer = new XHRArrayBufferTestLayer();
        this.addChild(xhrLayer);
    },
    runThisTest:function () {
        cc.director.runScene(this);
    },
    MainMenuCallback:function (sender) {
        this._super(sender);
    }
});

var XHRArrayBufferTestLayer = cc.Layer.extend({
    ctor:function () {
        this._super();
    },

    onEnter: function() {
        this._super();
        var l = new cc.LabelTTF("Get infos via XHR", "Thonburi", 16);
        this.addChild(l, 1);
        l.x = winSize.width / 2;
        l.y = winSize.height - 60;

        this.sendPostArrayBuffer();
    },

    //some utils functions
    ensureLeftAligned: function(label) {
        label.anchorX = 0;
        label.anchorY = 1;
        label.textAlign = cc.TEXT_ALIGNMENT_LEFT;
    },

    streamXHREventsToLabel: function( xhr, label, textbox, method, title ) {
        // Simple events
        ['loadstart', 'abort', 'error', 'load', 'loadend', 'timeout'].forEach(function (eventname) {
            xhr["on" + eventname] = function () {
                label.string += "\nEvent : " + eventname;
            };
        });
        
        // Special event
        xhr.onreadystatechange = function () {
            if (xhr.readyState == 4 && (xhr.status >= 200 && xhr.status <= 207)) {
                var httpStatus = xhr.statusText;
                var response = xhr.responseText.substring(0, 100) + "...";
                cc.log("title:" + title + ", response:\n" + xhr.responseText);
                textbox.string = method + " Response (100 chars):\n";
                textbox.string += response;
                label.string += "\nStatus: Got " + method + " response! " + httpStatus;
            }
        };
    },
                                              
    sendPostArrayBuffer: function() {
        var statusPostLabel = new cc.LabelTTF("Status:", "Thonburi", 12);
        this.addChild(statusPostLabel, 1);

        statusPostLabel.x = 10;
        statusPostLabel.y = winSize.height - 100;
        this.ensureLeftAligned(statusPostLabel);
        statusPostLabel.setString("Status: Send Post Request to httpbin.org with ArrayBuffer");


        var responseLabel = new cc.LabelTTF("", "Thonburi", 16);
        this.addChild(responseLabel, 1);
        this.ensureLeftAligned(responseLabel);
        responseLabel.x = 10;
        responseLabel.y = winSize.height / 2;
        
        var xhr = cc.loader.getXMLHttpRequest();
        this.streamXHREventsToLabel(xhr, statusPostLabel, responseLabel, "POST", "sendPostArrayBuffer");

        xhr.open("POST", "http://httpbin.org/post");
        //set Content-type "text/plain" to post ArrayBuffer or ArrayBufferView
        xhr.setRequestHeader("Content-Type","text/plain");
        // Uint8Array is an ArrayBufferView
        xhr.send(new Uint8Array([1,2,3,4,5]));
    },

    scrollViewDidScroll:function (view) {
    },
    scrollViewDidZoom:function (view) {
    }
});

var runXHRArrayBufferTest = function () {
    var pScene = new cc.Scene();
    var pLayer = new XHRArrayBufferTestLayer();
    pScene.addChild(pLayer);
    cc.director.runScene(pScene);
};
