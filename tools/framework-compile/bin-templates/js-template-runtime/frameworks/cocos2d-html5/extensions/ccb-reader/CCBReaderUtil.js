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

cc.NodeLoaderListener = cc.Class.extend({
    onNodeLoaded:function(node,nodeLoader){}
});

cc.BuilderSelectorResolver = cc.Class.extend({
    onResolveCCBCCMenuItemSelector:function(target, selectorName){},
    onResolveCCBCCCallFuncSelector:function(target, selectorName){},
    onResolveCCBCCControlSelector:function(target,selectorName){}
});

cc.BuilderScriptOwnerProtocol = cc.Class.extend({
    createNew:function(){}
});

cc.BuilderMemberVariableAssigner = cc.Class.extend({
    /**
     * The callback function of assigning member variable.          <br/>
     * @note The member variable must be CCNode or its subclass.
     * @param {Object} target The custom class
     * @param {string} memberVariableName The name of the member variable.
     * @param {cc.Node} node The member variable.
     * @return {Boolean} Whether the assignment was successful.
     */
    onAssignCCBMemberVariable:function(target,memberVariableName, node){ return false;},

    /**
     * The callback function of assigning custom properties.
     * @note The member variable must be Integer, Float, Boolean or String.
     * @param {Object} target The custom class.
     * @param {string} memberVariableName The name of the member variable.
     * @param {*} value The value of the property.
     * @return {Boolean} Whether the assignment was successful.
     */
    onAssignCCBCustomProperty:function(target, memberVariableName, value){ return false; }
});
