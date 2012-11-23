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
// controller for the Dragon Object (the Hero)
//

// Constants
var CD_START_SPEED = 8;
var CD_COIN_SPEED = 8;
var CD_START_TARGET = 160;

var CD_TARGET_FILTER_FACTOR = 0.05;
var CD_SLOW_DOWN_FACTOR = 0.995;
var CD_GRAVITY_SPEED = 0.1;
var CD_GAMEOVER_SPEED = -10;
var CD_DELTA_TO_ROTATION_FACTOR = 5;

var Dragon = function()
{
    this.xTarget = CD_START_TARGET*gScaleFactor;
    this.ySpeed = CD_START_SPEED;
    this.radius = 25;
};

Dragon.prototype.onUpdate = function()
{
    // Calculate the new position
    var oldPosition = cc.pMult(this.rootNode.getPosition(), 1.0/gScaleFactor);

    var xNew = (this.xTarget/gScaleFactor) * CD_TARGET_FILTER_FACTOR + oldPosition.x * (1-CD_TARGET_FILTER_FACTOR);
    var yNew = oldPosition.y + this.ySpeed;
    this.rootNode.setPosition(xNew*gScaleFactor, yNew*gScaleFactor);

    // Update the vertical speed
    this.ySpeed = (this.ySpeed - CD_GRAVITY_SPEED) * CD_SLOW_DOWN_FACTOR;

    // Tilt the dragon
    var xDelta = xNew - oldPosition.x;
    this.rootNode.setRotation(xDelta * CD_DELTA_TO_ROTATION_FACTOR);

    // Check for game over
    if (this.ySpeed < CD_GAMEOVER_SPEED)
    {
        sharedGameScene.handleGameOver();
    }
};

Dragon.prototype.handleCollisionWith = function(gameObjectController)
{
    if (gameObjectController.controllerName == "Coin")
    {
        // Took a coin
        this.ySpeed = CD_COIN_SPEED;
        sharedGameScene.setScore(sharedGameScene.score+1);
    }
    else if (gameObjectController.controllerName == "Bomb")
    {
        // Hit a bomb
        if (this.ySpeed > 0) this.ySpeed = 0;

        this.rootNode.animationManager.runAnimationsForSequenceNamed("Hit");
    }
};
