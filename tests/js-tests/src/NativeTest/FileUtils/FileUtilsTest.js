/****************************************************************************
 Copyright (c) 2015 Chukong Technologies Inc.

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
var fileUtilsSceneIdx = -1;

//------------------------------------------------------------------
//
// fileUtilsBase
//
//------------------------------------------------------------------
var fileUtilsBase = BaseTestLayer.extend({
    _title:"",
    _subtitle:"",

    ctor:function() {
        this._super(cc.color(0,0,0,255), cc.color(98,99,117,255));
        var label = new cc.LabelTTF("Back", "Arial", 20);
        var menuItem = new cc.MenuItemLabel(label, this.backtoNativeTest, this);
        var menu = new cc.Menu(menuItem);
        menu.x = 0;
        menu.y = 0;
        menuItem.x = winSize.width - 50;
        menuItem.y = 25;
        this.addChild(menu, 1);
    },
    backtoNativeTest:function(sender) {
        new NativeTestScene().runThisTest();
    },
    onRestartCallback:function (sender) {
        var s = new cc.Scene();
        s.addChild(restartfileUtils());
        director.runScene(s);
    },
    onNextCallback:function (sender) {
        var s = new cc.Scene();
        s.addChild(nextfileUtils());
        director.runScene(s);
    },
    onBackCallback:function (sender) {
        var s = new cc.Scene();
        s.addChild(previousfileUtils());
        director.runScene(s);
    },
    // automation
    numberOfPendingTests:function() {
        return ( (arrayOffileUtils.length-1) - fileUtilsSceneIdx );
    },

    getTestNumber:function() {
        return fileUtilsSceneIdx;
    }

});

var TestWriteData = fileUtilsBase.extend({
    _title:"fileUtils: TestWriteData(Binary) to files",
    ctor:function() {
        this._super();

        var winSize = cc.winSize;

        var writeResult = new cc.LabelTTF("", "Arial", 18);
        this.addChild(writeResult);
        writeResult.setPosition(winSize.width / 2, winSize.height * 3 / 4);

        var readResult = new cc.LabelTTF("", "Arial", 18);
        this.addChild(readResult);
        readResult.setPosition(winSize.width / 2, winSize.height  / 3);

        var writablePath = jsb.fileUtils.getWritablePath();
        writablePath += "cocos/fileUtilTest/";
        var fileName = "writeDataTest.bin";
        var fullPath = writablePath + fileName;

        // writeTest
        var writeData = new Uint8Array(8);
        for(var i = 0; i < writeData.length; i ++) {
            writeData[i] = i;
        }
        jsb.fileUtils.createDirectory(writablePath);
        if (jsb.fileUtils.writeDataToFile(writeData, fullPath))
        {
            log("see the file at %s", fullPath);
            writeResult.setString("write success:\n" + fullPath);
        }
        else
        {
            log("write file failed");
            writeResult.setString("write fail");
        }

        // readTest
        var readData = jsb.fileUtils.getDataFromFile(fullPath);
        if(!readData || typeof readData != typeof writeData) {
            log("read file failed");
            readResult.setString("read failed");
        } else {
            var match = true;
            if(readData.length != writeData.length){
                log("data size not match");
                match = false;
            } else {
                for(var i = 0; i < readData.length; i ++) {
                    if(readData[i] != writeData[i]) {
                        log("data not match");
                        match = false;
                        break;
                    }
                }
            }
            if(!match) {
                readResult.setString("read success, but data not correct");
            } else {
                readResult.setString("read test success");
            }
        }
    },
});

var TestWriteString = fileUtilsBase.extend({
    _title:"fileUtils: TestWriteString to files",
    ctor:function() {
        this._super();

        var winSize = cc.winSize;

        var writeResult = new cc.LabelTTF("", "Arial", 18);
        this.addChild(writeResult);
        writeResult.setPosition(winSize.width / 2, winSize.height * 3 / 4);

        var readResult = new cc.LabelTTF("", "Arial", 18);
        this.addChild(readResult);
        readResult.setPosition(winSize.width / 2, winSize.height  / 3);

        var writablePath = jsb.fileUtils.getWritablePath();
        writablePath += "cocos/fileUtilTest/";
        var fileName = "writeStringTest.txt";

        // writeTest
        var writeDataStr = "the string data will be write into a file";
        var fullPath = writablePath + fileName;
        jsb.fileUtils.createDirectory(writablePath);
        if (jsb.fileUtils.writeStringToFile(writeDataStr, fullPath))
        {
            log("see the plist file at %s", fullPath);
            writeResult.setString("write success:\n" + fullPath);
        }
        else
        {
            log("write plist file failed");
            writeResult.setString("write fail");
        }

        // readTest
        var readDataStr = jsb.fileUtils.getStringFromFile(fullPath);
        readResult.setString("read success:" + readDataStr);

    },
});

var TestWriteValueMap = fileUtilsBase.extend({
    _title:"fileUtils: TestWriteValueMap to files",
    ctor:function() {
        this._super();

        var winSize = cc.winSize;

        var writeResult = new cc.LabelTTF("", "Arial", 18);
        this.addChild(writeResult);
        writeResult.setPosition(winSize.width / 2, winSize.height * 3 / 4);

        var readResult = new cc.LabelTTF("", "Arial", 18);
        this.addChild(readResult);
        readResult.setPosition(winSize.width / 2, winSize.height  / 3);

        var valueMap = {};

        var mapInValueMap = {};
        mapInValueMap["string1"] = "string in dictInMap key 0";
        mapInValueMap["string2"] = "string in dictInMap key 1";
        valueMap["data0"] = mapInValueMap;

        valueMap["data1"] = "string in array";

        var arrayInMap = [];
        arrayInMap[arrayInMap.length] = "string 0 in arrayInMap";
        arrayInMap[arrayInMap.length] = "string 1 in arrayInMap";
        valueMap["data2"] = arrayInMap;

        //add boolean to the plist
        var booleanObject = true;
        valueMap["data3"] = booleanObject;

        //add interger to the plist
        var intObject = 1024;
        valueMap["data4"] = intObject;

        //add float to the plist. js have no float
        var floatObject = 1024.1024;
        valueMap["data5"] = floatObject;

        //add double to the plist
        var doubleObject = 1024.123;
        valueMap["data6"] = doubleObject;


        // end with /
        var writablePath = jsb.fileUtils.getWritablePath();
        writablePath += "cocos/fileUtilTest/";
        var fullPath = writablePath + "testWriteValueMap.plist";
        jsb.fileUtils.createDirectory(writablePath);
        if (jsb.fileUtils.writeValueMapToFile(valueMap, fullPath))
        {
            cc.log("see the plist file at %s", fullPath);
            writeResult.setString("write success:\n" + fullPath);
        }
        else
        {
            cc.log("write plist file failed");
            writeResult.setString("write failed");
        }

        var readValueMap = jsb.fileUtils.getValueMapFromFile(fullPath);
        var readDataStr = "read data:\n";
        // read value map data
        var readMapInMap = readValueMap["data0"];
        readDataStr += "  mapValue:[\"string1\"][" + readMapInMap["string1"] + "]\n";
        readDataStr += "  mapValue:[\"string2\"][" + readMapInMap["string2"] + "]\n";

        // read string data
        readDataStr += "  stringValue:" + readValueMap["data1"] + "\n";

        // read value vector data
        var readVectorInMap = readValueMap["data2"];
        readDataStr += "  vectorValue:[1]" + readVectorInMap[0] + "\n";
        readDataStr += "  vectorValue:[2]" + readVectorInMap[1] + "\n";

        // read bool data
        readDataStr += "  boolValue:" + readValueMap["data3"] + "\n";

        // read int data
        readDataStr += "  intValue:" + readValueMap["data4"] + "\n";

        // read float data
        readDataStr += "  floatValue:" + readValueMap["data5"] + "\n";

        // read double data
        readDataStr += "  doubleValue:" + readValueMap["data6"] + "\n";

        readResult.setString(readDataStr);

    },
});

var TestWriteValueVector = fileUtilsBase.extend({
    _title:"fileUtils: TestWriteValueVector to files",
    ctor:function() {
        this._super();

        var winSize = cc.winSize;

        var writeResult = new cc.LabelTTF("", "Arial", 18);
        this.addChild(writeResult);
        writeResult.setPosition(winSize.width / 2, winSize.height * 3 / 4);

        var readResult = new cc.LabelTTF("", "Arial", 18);
        this.addChild(readResult);
        readResult.setPosition(winSize.width / 2, winSize.height  / 3);

        var array = [];

        var mapInArray = {};
        mapInArray["string1"] = "string in dictInArray key 0";
        mapInArray["string2"] = "string in dictInArray key 1";
        array[array.length] = mapInArray;

        array[array.length] = "string in array";

        var arrayInArray = [];
        arrayInArray[arrayInArray.length] = "string 0 in arrayInArray";
        arrayInArray[arrayInArray.length] = "string 1 in arrayInArray";
        array[array.length] = arrayInArray;

        //add boolean to the plist
        var booleanObject = true;
        array[array.length] = booleanObject;

        //add interger to the plist
        var intObject = 1024;
        array[array.length] = intObject;

        //add float to the plist
        var floatObject = 1024.1024;
        array[array.length] = floatObject;

        //add double to the plist
        var doubleObject = 1024.123;
        array[array.length] = doubleObject;


        // end with /
        var writablePath = jsb.fileUtils.getWritablePath();
        writablePath += "cocos/fileUtilTest/";
        var fullPath = writablePath + "testWriteValueVector.plist";
        jsb.fileUtils.createDirectory(writablePath);
        if (jsb.fileUtils.writeValueVectorToFile(array, fullPath))
        {
            cc.log("see the plist file at %s", fullPath);
            writeResult.setString("write success:\n" + fullPath);
        }
        else
        {
            cc.log("write plist file failed");
            writeResult.setString("write failed");
        }

        var readArray = jsb.fileUtils.getValueVectorFromFile(fullPath);
        var readDataStr = "read data:\n";
        // read value map data
        var readMapInArray = readArray[0];
        readDataStr += "  mapValue:[\"string1\"][" + readMapInArray["string1"] + "]\n";
        readDataStr += "  mapValue:[\"string2\"][" + readMapInArray["string2"] + "]\n";

        // read string data
        readDataStr += "  stringValue:" + readArray[1] + "\n";

        // read value vector data
        var readVectorInArray = readArray[2];
        readDataStr += "  vectorValue:[1]" + readVectorInArray[0] + "\n";
        readDataStr += "  vectorValue:[2]" + readVectorInArray[1] + "\n";

        // read bool data
        readDataStr += "  boolValue:" + readArray[3] + "\n";

        // read int data
        readDataStr += "  intValue:" + readArray[4] + "\n";

        // read float data
        readDataStr += "  floatValue:" + readArray[5] + "\n";

        // read double data
        readDataStr += "  doubleValue:" + readArray[6] + "\n";

        readResult.setString(readDataStr);

    },
});
var arrayOffileUtils = [
    TestWriteData,
    TestWriteString,
    TestWriteValueMap,
    TestWriteValueVector
];

var nextfileUtils = function () {
    fileUtilsSceneIdx++;
    fileUtilsSceneIdx = fileUtilsSceneIdx % arrayOffileUtils.length;

    return new arrayOffileUtils[fileUtilsSceneIdx]();
};
var previousfileUtils = function () {
    fileUtilsSceneIdx--;
    if (fileUtilsSceneIdx < 0)
        fileUtilsSceneIdx += arrayOffileUtils.length;

    return new arrayOffileUtils[fileUtilsSceneIdx]();
};
var restartfileUtils = function () {
    return new arrayOffileUtils[fileUtilsSceneIdx]();
};

var startFileUtilsTest = function()
{
    fileUtilsSceneIdx = 0;
    var s = new cc.Scene();
    s.addChild(restartfileUtils());
    director.runScene(s);
}
