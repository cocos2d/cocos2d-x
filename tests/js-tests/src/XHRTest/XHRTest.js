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

var XHRTestScene = TestScene.extend({
    ctor:function () {
        this._super(true);
        var xhrLayer = new XHRTestLayer();
        this.addChild(xhrLayer);
    },
    runThisTest:function () {
        cc.director.runScene(this);
    },
    MainMenuCallback:function (sender) {
        this._super(sender);
    }
});

var XHRTestLayer = cc.Layer.extend({
    ctor:function () {
        this._super();
    },

    onEnter: function() {
        this._super();
        var l = new cc.LabelTTF("Get infos via XHR", "Thonburi", 16);
        this.addChild(l, 1);
        l.x = winSize.width / 2;
        l.y = winSize.height - 60;

        this.sendGetRequest();
        this.sendPostPlainText();
        this.sendPostForms();
    },

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

    sendGetRequest: function() {
        var statusGetLabel = new cc.LabelTTF("Status:", "Thonburi", 12);
        this.addChild(statusGetLabel, 1);

        statusGetLabel.x = 10;
        statusGetLabel.y = winSize.height - 100;
        this.ensureLeftAligned(statusGetLabel);
        statusGetLabel.setString("Status: Send Get Request to httpbin.org");

        var responseLabel = new cc.LabelTTF("", "Thonburi", 16);
        this.addChild(responseLabel, 1);

        this.ensureLeftAligned(responseLabel);
        responseLabel.x = 10;
        responseLabel.y = winSize.height / 2;

        var xhr = cc.loader.getXMLHttpRequest();
        this.streamXHREventsToLabel(xhr, statusGetLabel, responseLabel, "GET", "sendGetRequest");
        // 5 seconds for timeout
        xhr.timeout = 5000;

        //set arguments with <URL>?xxx=xxx&yyy=yyy
        xhr.open("GET", "http://httpbin.org/gzip", true);
        xhr.setRequestHeader("Accept-Encoding","gzip,deflate");

        xhr.send();
    },

    sendPostPlainText: function() {
        var statusPostLabel = new cc.LabelTTF("Status:", "Thonburi", 12);
        this.addChild(statusPostLabel, 1);

        statusPostLabel.x = winSize.width / 10 * 3;
        statusPostLabel.y = winSize.height - 100;
        this.ensureLeftAligned(statusPostLabel);
        statusPostLabel.setString("Status: Send Post Request to httpbin.org with plain text");


        var responseLabel = new cc.LabelTTF("", "Thonburi", 16);
        this.addChild(responseLabel, 1);
        this.ensureLeftAligned(responseLabel);
        responseLabel.x = winSize.width / 10 * 3;
        responseLabel.y = winSize.height / 2;

        var xhr = cc.loader.getXMLHttpRequest();
        this.streamXHREventsToLabel(xhr, statusPostLabel, responseLabel, "POST", "sendPostPlainText");

        xhr.open("POST", "http://httpbin.org/post");

        //set Content-type "text/plain;charset=UTF-8" to post plain text
        xhr.setRequestHeader("Content-Type","text/plain;charset=UTF-8");
        xhr.send("plain text message");
    },

    sendPostForms: function() {
        var statusPostLabel = new cc.LabelTTF("Status:", "Thonburi", 12);
        this.addChild(statusPostLabel, 1);

        statusPostLabel.x = winSize.width / 10 * 7;
        statusPostLabel.y = winSize.height - 100;
        this.ensureLeftAligned(statusPostLabel);
        statusPostLabel.setString("Status: Send Post Request to httpbin.org width form data");

        var responseLabel = new cc.LabelTTF("", "Thonburi", 16);
        this.addChild(responseLabel, 1);

        this.ensureLeftAligned(responseLabel);
        responseLabel.x = winSize.width / 10 * 7;
        responseLabel.y = winSize.height / 2;

        var xhr = cc.loader.getXMLHttpRequest();
        this.streamXHREventsToLabel(xhr, statusPostLabel, responseLabel, "POST", "sendPostForms");

        xhr.open("POST", "http://httpbin.org/post");
        //set Content-Type "application/x-www-form-urlencoded" to post form data
        //mulipart/form-data for upload
        xhr.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
        /**
        form : {
            "a" : "hello",
            "b" : "world"
        }
        **/
        var args = "a=hello&b=world";
        xhr.send(args);
    },

    scrollViewDidScroll:function (view) {
    },
    scrollViewDidZoom:function (view) {
    }
});

var runXHRTest = function () {
    var pScene = new cc.Scene();
    var pLayer = new XHRTestLayer();
    pScene.addChild(pLayer);
    cc.director.runScene(pScene);
};
