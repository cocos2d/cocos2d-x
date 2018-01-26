/*global ccui */

/*
 * Copyright (c) 2013-2017 Chukong Technologies Inc.
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

// Deprecated functions

var cc = cc || {};

(function() {
    var logW = function(oldName, newName) {
        cc.log("\n********** \n"+oldName +" was deprecated, please use "+ newName +" instead.\n**********");
    };

    ccui.Text.prototype.setText = function(text) {
        logW("ccui.Text.setText", "ccui.Text.setString");
        this.setString(text);
    };

    ccui.Text.prototype.getStringValue = function() {
        logW("ccui.Text.getStringValue", "ccui.Text.getString");
        return this.getString();
    };

    ccui.PageView.prototype.getCurPageIndex = function() {
        logW("ccui.PageView.getCurPageIndex", "ccui.PageView.getCurrentPageIndex");
        return this.getCurrentPageIndex();
    };

    ccui.PageView.prototype.addWidgetToPage = function(widget, pageIndx) {
        logW("ccui.PageView.addWidgetToPage", "ccui.PageView.insertPage");
        return this.insertPage(widget, pageIndx);
    };

    ccui.PageView.prototype.setCurPageIndex = function(index) {
        logW("ccui.PageView.setCurPageIndex", "ccui.PageView.setCurrentPageIndex");
        return this.setCurrentPageIndex(index);
    };

    ccui.PageView.prototype.getPages = function() {
        logW("ccui.PageView.getPages", "ccui.PageView.getItems");
        return this.getItems();
    };

    ccui.PageView.prototype.getPage = function(index) {
        logW("ccui.PageView.getPage", "ccui.PageView.getItem");
        return this.getItem(index);
    };

    ccui.PageView.prototype.setCustomScrollThreshold = function() {
        cc.log("Since v3.9, this method has no effect.");
    };

    ccui.PageView.prototype.getCustomScrollThreshold = function() {
        cc.log("Since v3.9, this method has no effect.");
    };

    ccui.PageView.prototype.setUsingCustomScrollThreshold = function() {
        cc.log("Since v3.9, this method has no effect.");
    };

    ccui.PageView.prototype.isUsingCustomScrollThreshold = function() {
        cc.log("Since v3.9, this method has no effect.");
    };

    ccui.ListView.prototype.requestRefreshView = function() {
        logW("ccui.ListView.requestRefreshView", "ccui.ListView.forceDoLayout");
        this.forceDoLayout();
    };

    ccui.ListView.prototype.refreshView = function() {
        logW("ccui.ListView.refreshView", "ccui.ListView.forceDoLayout");
        this.forceDoLayout();
    };

})();
