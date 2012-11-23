/* http://www.cocosbuilder.com
 * http://www.cocos2d-iphone.org
 *
 * Copyright (c) 2012 Zynga, Inc.
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
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

//
// Controller for the GameScene Object
// This object loads the main Scene
//

var GameScene = function(){};
var sharedGameScene;
var gLevelOffsetX = 0;

GameScene.prototype.onDidLoadFromCCB = function()
{
    sharedGameScene = this;

    this.score = 0;

    var level = cc.Reader.load("Level.ccbi");
    
    // Center the level on Screen
    gLevelOffsetX = (gWinSize.width-CD_LEVEL_WIDTH*gScaleFactor)/2;
    
    level.setPosition(cc.p(gLevelOffsetX,0));

    this.rootNode.addChild(level);
};

GameScene.prototype.setScore = function(score)
{
    this.score = score;
    this.scoreLabel.setString(""+score);
};

GameScene.prototype.getScore = function()
{
    return this.score;
};

GameScene.prototype.handleGameOver = function()
{
    var scene = cc.Reader.loadAsScene("MainMenuScene.ccbi");
    cc.Director.getInstance().replaceScene(scene);
};

GameScene.prototype.handleLevelComplete = function()
{
    var scene = cc.Reader.loadAsScene("MainMenuScene.ccbi");
    cc.Director.getInstance().replaceScene(scene);
};
