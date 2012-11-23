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

var CD_LEVEL_WIDTH = 320;
var CD_SCROLL_FILTER_FACTOR = 0.1;
var CD_DRAGON_TARGET_OFFET = 80;

// Accelerometer
var CD_ACCEL_FILTER_FACTOR = 0.25;

/**
 * Level is the controller object of the game:
 * It receives the following events:
 *  - onUpdate
 *  - Input events like touches, mouse and accelerometer
 */
var Level = function(){
    this.winSize = cc.Director.getInstance().getWinSize();

    // Used for the low-pass filter on the accelerometer
    this.prevX = 0;
};

Level.prototype.onDidLoadFromCCB = function()
{
    // Forward relevant touch events to controller (this)
    this.rootNode.onTouchesBegan = function( touches, event) {
        this.controller.onTouchesBegan(touches, event);
        return true;
    };
    this.rootNode.onTouchesMoved = function( touches, event) {
        this.controller.onTouchesMoved(touches, event);
        return true;
    };
    this.rootNode.onMouseDragged = function( event) {
        this.controller.onMouseDragged(event);
        return true;
    };

    this.rootNode.onAccelerometer = function( event) {
        this.controller.onAccelerometer(event);
    };

    // Schedule callback
    this.rootNode.onUpdate = function(dt) {
        this.controller.onUpdate();
    };
    this.rootNode.schedule(this.rootNode.onUpdate);
};

//
// Events
//
Level.prototype.onTouchesBegan = function(touches, event)
{
	if (gSettingControlType != CD_CONTROLTYPE_TOUCH) return;
	
    var loc = touches[0].getLocation();
    this.dragon.controller.xTarget = loc.x - gLevelOffsetX;
};

Level.prototype.onTouchesMoved = function(touches, event)
{
	if (gSettingControlType != CD_CONTROLTYPE_TOUCH) return;
	
    var loc = touches[0].getLocation();
    this.dragon.controller.xTarget = loc.x - gLevelOffsetX;
};

Level.prototype.onMouseDragged = function(event)
{
	if (gSettingControlType != CD_CONTROLTYPE_TOUCH) return;
	
    var loc = event.getLocation();
    this.dragon.controller.xTarget = loc.x;
};

Level.prototype.onAccelerometer = function(accelEvent)
{
	if (gSettingControlType != CD_CONTROLTYPE_TILT) return;

    // low pass filter for accelerometer. This makes the movement softer
    var accelX = accelEvent.x * CD_ACCEL_FILTER_FACTOR + (1 - CD_ACCEL_FILTER_FACTOR) * this.prevX;
    this.prevX = accelX;

    var newX = this.winSize.width * accelX + this.winSize.width/2;
    this.dragon.controller.xTarget = newX;
    // cc.log('Accel x: '+ accelEvent.x + ' y:' + accelEvent.y + ' z:' + accelEvent.z + ' time:' + accelEvent.timestamp );
};


// Game main loop
Level.prototype.onUpdate = function(dt)
{
    var i=0;
    var gameObject = null;
    var gameObjectController = null;

    // Iterate though all objects in the level layer
    var children = this.rootNode.getChildren();
    for (i = 0; i < children.length; i++)
    {
        // Check if the child has a controller (only the updatable objects will have one)
        gameObject = children[i];
        gameObjectController = gameObject.controller;
        if (gameObjectController)
        {
            // Update all game objects
            gameObjectController.onUpdate();
            
            var gameObjectPos = cc.pMult(gameObject.getPosition(), 1.0/gScaleFactor);
            var dragonPos = cc.pMult(this.dragon.getPosition(), 1.0/gScaleFactor);

            // Check for collisions with dragon
            if (gameObject !== this.dragon)
            {
                if (cc.pDistance(gameObjectPos, dragonPos) < gameObjectController.radius + this.dragon.controller.radius)
                {
                    gameObjectController.handleCollisionWith(this.dragon.controller);
                    this.dragon.controller.handleCollisionWith(gameObjectController);
                }
            }
        }
    }

    // Check for objects to remove
    for (i = children.length-1; i >=0; i--)
    {
        gameObject = children[i];
        gameObjectController = gameObject.controller;
        if (gameObjectController && gameObjectController.isScheduledForRemove)
        {
            this.rootNode.removeChild(gameObject);
        }
    }

    // Adjust position of the layer so dragon is visible
    var yTarget = CD_DRAGON_TARGET_OFFET - this.dragon.getPosition().y;
    var oldLayerPosition = this.rootNode.getPosition();

    var xNew = oldLayerPosition.x;
    var yNew = yTarget * CD_SCROLL_FILTER_FACTOR + oldLayerPosition.y * (1 - CD_SCROLL_FILTER_FACTOR);

    this.rootNode.setPosition(xNew, yNew);
};
