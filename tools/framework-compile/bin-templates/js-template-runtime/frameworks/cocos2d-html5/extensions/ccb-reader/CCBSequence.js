/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011-2012 cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.

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

cc.BuilderSequence = cc.Class.extend({
    _duration:0,
    _name:"",
    _sequenceId:0,
    _chainedSequenceId:0,
    _callbackChannel:null,
    _soundChannel:null,

    ctor:function(){
        this._name = "";
    },

    getDuration:function(){
        return this._duration;
    },
    setDuration:function(duration){
        this._duration = duration;
    },

    getName:function(){
        return this._name;
    },
    setName:function(name){
        this._name = name;
    },

    getSequenceId:function(){
        return this._sequenceId;
    },
    setSequenceId:function(sequenceId){
        this._sequenceId = sequenceId;
    },

    getChainedSequenceId:function(){
        return this._chainedSequenceId;
    },
    setChainedSequenceId:function(chainedSequenceId){
        this._chainedSequenceId = chainedSequenceId;
    },

    getCallbackChannel:function() {
        return this._callbackChannel;
    },
    setCallbackChannel:function(channel) {
        this._callbackChannel = channel;
    },

    getSoundChannel:function() {
        return this._soundChannel;
    },
    setSoundChannel:function(channel) {
        this._soundChannel = channel;
    }
});

cc.BuilderSequenceProperty = cc.Class.extend({
    _name : null,
    _type:0,
    _keyFrames:null,

    ctor:function(){
        this.init();
    },

    init:function(){
        this._keyFrames = [];
        this._name = "";
    },

    getName:function(){
        return this._name;
    },

    setName :function(name){
        this._name = name;
    },

    getType:function(){
        return this._type;
    },
    setType :function(type){
        this._type = type;
    },

    getKeyframes:function(){
        return this._keyFrames;
    }
});