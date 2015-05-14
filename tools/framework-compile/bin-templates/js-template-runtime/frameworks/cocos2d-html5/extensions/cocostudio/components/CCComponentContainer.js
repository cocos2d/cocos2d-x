/****************************************************************************
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

/**
 * The component container for Cocostudio, it has some components.
 * @class
 * @extends cc.Class
 */
cc.ComponentContainer = cc.Class.extend(/** @lends cc.ComponentContainer# */{
    _components:null,
    _owner:null,

    /**
     * Construction of cc.ComponentContainer
     * @param node
     */
    ctor:function(node){
        this._components = null;
        this._owner = node;
    },

    /**
     * Gets component by name.
     * @param name
     * @returns {*}
     */
    getComponent:function(name){
        if(!name)
            throw "cc.ComponentContainer.getComponent(): name should be non-null";
        name = name.trim();
        if(!this._components){
            this._components = {};
        }
        return this._components[name];
    },

    /**
     * Adds a component to container
     * @param {cc.Component} component
     * @returns {boolean}
     */
    add:function(component){
        if(!component)
             throw "cc.ComponentContainer.add(): component should be non-null";
        if(component.getOwner()){
            cc.log("cc.ComponentContainer.add(): Component already added. It can't be added again");
            return false;
        }

        if(this._components == null){
            this._components = {};
            this._owner.scheduleUpdate();
        }
        var oldComponent = this._components[component.getName()];
        if(oldComponent){
            cc.log("cc.ComponentContainer.add(): Component already added. It can't be added again");
            return false;
        }
        component.setOwner(this._owner);
        this._components[component.getName()] = component;
        component.onEnter();
        return true;
    },

    /**
     * Removes component from container by name or component object.
     * @param {String|cc.Component} name component name or component object.
     * @returns {boolean}
     */
    remove:function(name){
        if(!name)
            throw "cc.ComponentContainer.remove(): name should be non-null";
        if(!this._components)
            return false;
        if(name instanceof cc.Component)
            return this._removeByComponent(name);
        else {
            name = name.trim();
            return this._removeByComponent(this._components[name]);
        }
    },

    _removeByComponent:function(component){
        if(!component)
            return false;
        component.onExit();
        component.setOwner(null);
        delete this._components[component.getName()];
        return true;
    },

    /**
     * Removes all components of container.
     */
    removeAll:function(){
        if(!this._components)
            return;
        var locComponents = this._components;
        for(var selKey in locComponents){
            var selComponent = locComponents[selKey];
            selComponent.onExit();
            selComponent.setOwner(null);
            delete locComponents[selKey];
        }
        this._owner.unscheduleUpdate();
        this._components = null;
    },

    _alloc:function(){
        this._components = {};
    },

    /**
     * Visit callback by director. it calls every frame.
     * @param {Number} delta
     */
    visit:function(delta){
        if(!this._components)
            return;

        var locComponents = this._components;
        for(var selKey in locComponents)
             locComponents[selKey].update(delta);
    },

    /**
     * Returns the container whether is empty.
     * @returns {boolean}
     */
    isEmpty: function () {
        if (!this._components)
            return true;
        return this._components.length === 0;
    }
});


