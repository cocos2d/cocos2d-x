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

ccs._load = (function(){

    /**
     * load file
     * @param {String} file
     * @param {String} [type=] - ccui|node|action
     * @param {String} [path=] - Resource search path
     * @returns {*}
     */
    var load = function(file, type, path){

        var json = cc.loader.getRes(file);

        if(!json)
            return cc.log("%s does not exist", file);
        var ext = extname(file).toLocaleLowerCase();
        if(ext !== "json" && ext !== "exportjson")
            return cc.log("%s load error, must be json file", file);

        var parse;
        if(!type){
            if(json["widgetTree"])
                parse = parser["ccui"];
            else if(json["nodeTree"])
                parse = parser["timeline"];
            else if(json["Content"] && json["Content"]["Content"])
                parse = parser["timeline"];
            else if(json["gameobjects"])
                parse = parser["scene"];
        }else{
            parse = parser[type];
        }

        if(!parse){
            cc.log("Can't find the parser : %s", file);
            return new cc.Node();
        }
        var version = json["version"] || json["Version"];
        if(!version && json["armature_data"]){
            cc.warn("%s is armature. please use:", file);
            cc.warn("    ccs.armatureDataManager.addArmatureFileInfoAsync(%s);", file);
            cc.warn("    var armature = new ccs.Armature('name');");
            return new cc.Node();
        }
        var currentParser = getParser(parse, version);
        if(!currentParser){
            cc.log("Can't find the parser : %s", file);
            return new cc.Node();
        }

        return currentParser.parse(file, json, path) || null;
    };

    var parser = {
        "ccui": {},
        "timeline": {},
        "action": {},
        "scene": {}
    };

    load.registerParser = function(name, version, target){
        if(!name || !version || !target)
            return cc.log("register parser error");
        if(!parser[name])
            parser[name] = {};
        parser[name][version] = target;
    };

    load.getParser = function(name, version){
        if(name && version)
            return parser[name] ? parser[name][version] : undefined;
        if(name)
            return parser[name];
        return parser;
    };

    //Gets the file extension
    var extname = function(fileName){
        var arr = fileName.match(extnameReg);
        return ( arr && arr[1] ) ? arr[1] : null;
    };
    var extnameReg = /\.([^\.]+)$/;


    var parserReg = /([^\.](\.\*)?)*$/;
    var getParser = function(parser, version){
        if(parser[version])
            return parser[version];
        else if(version === "*")
            return null;
        else
            return getParser(parser, version.replace(parserReg, "*"));
    };

    return load;

})();

ccs._parser = cc.Class.extend({

    ctor: function(){
        this.parsers = {};
    },

    _dirnameReg: /\S*\//,
    _dirname: function(path){
        var arr = path.match(this._dirnameReg);
        return (arr && arr[0]) ? arr[0] : "";
    },

    getClass: function(json){
        return json["classname"];
    },

    getNodeJson: function(json){
        return json["widgetTree"];
    },

    parse: function(file, json, resourcePath){
        resourcePath = resourcePath || this._dirname(file);
        this.pretreatment(json, resourcePath);
        var node = this.parseNode(this.getNodeJson(json), resourcePath, file);
        node && this.deferred(json, resourcePath, node, file);
        return node;
    },

    pretreatment: function(json, resourcePath, file){},

    deferred: function(json, resourcePath, node, file){},

    parseNode: function(json, resourcePath){
        var parser = this.parsers[this.getClass(json)];
        var widget = null;
        if(parser)
            widget = parser.call(this, json, resourcePath);
        else
            cc.log("Can't find the parser : %s", this.getClass(json));

        return widget;
    },

    registerParser: function(widget, parse){
        this.parsers[widget] = parse;
    }
});

/**
 * Analysis of studio JSON file
 * The incoming file name, parse out the corresponding object
 * Temporary support file list:
 *   ui 1.*
 *   node 1.* - 2.*
 *   action 1.* - 2.*
 *   scene 0.* - 1.*
 * @param {String} file
 * @param {String} [path=] Resource path
 * @returns {{node: cc.Node, action: cc.Action}}
 */
ccs.load = function(file, path){
    var object = {
        node: null,
        action: null
    };

    object.node = ccs._load(file, null, path);
    object.action = ccs._load(file, "action", path);
    if(object.action && object.action.tag === -1 && object.node)
        object.action.tag = object.node.tag;
    return object;
};

/**
 * Analysis of studio JSON file and layout ui widgets by visible size.
 * The incoming file name, parse out the corresponding object
 * Temporary support file list:
 *   ui 1.*
 *   node 1.* - 2.*
 *   action 1.* - 2.*
 *   scene 0.* - 1.*
 * @param {String} file
 * @param {String} [path=] Resource path
 * @returns {{node: cc.Node, action: cc.Action}}
 */
ccs.loadWithVisibleSize = function(file, path){
    var object = ccs.load(file, path);
    var size = cc.director.getVisibleSize();
    if(object.node && size){
        object.node.setContentSize(size.width, size.height);
        ccui.helper.doLayout(object.node);
    }
    return object;
};

//Forward compatible interface

ccs.actionTimelineCache = {


    //@deprecated This function will be deprecated sooner or later please use ccs.load
    /**
     * Create Timeline Action
     * @param file
     * @returns {*}
     */
    createAction: function(file){
        return ccs._load(file, "action");
    }
};

ccs.csLoader = {

    //@deprecated This function will be deprecated sooner or later please use ccs.load
    /**
     * Create Timeline Node
     * @param file
     * @returns {*}
     */
    createNode: function(file){
        return ccs._load(file);
    }
};