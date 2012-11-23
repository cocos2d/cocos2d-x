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

var CD_CONTROLTYPE_TOUCH = 0;
var CD_CONTROLTYPE_TILT = 1;

// Setup global variables
var gSettingMusicEnabled = true;
var gSettingControlType;

var gWinSize = cc.Director.getInstance().getWinSize();

var gScaleFactor;
if (gWinSize.width <= 320) gScaleFactor = 1;
else gScaleFactor = 2;

// Start playing looped background music
cc.AudioEngine.getInstance().setEffectsVolume(0.2);
cc.AudioEngine.getInstance().playMusic("Music.mp3");

//
// MainMenuScene class
//

var MainMenuScene = function(){};

MainMenuScene.prototype.updateSettingsDisplay = function()
{
	// Music on/off
	this.sprtMusicOff.setVisible(!gSettingMusicEnabled);
	
	// Controls
	if (gSettingControlType == CD_CONTROLTYPE_TOUCH)
	{
		this.sprtControlTouch.setVisible(true);
		this.sprtControlTilt.setVisible(false);
	}
	else
	{
		this.sprtControlTouch.setVisible(false);
		this.sprtControlTilt.setVisible(true);
	}
};

MainMenuScene.prototype.onDidLoadFromCCB = function()
{
	this.updateSettingsDisplay();
};

MainMenuScene.prototype.onPressedPlay = function()
{
    var scene = cc.Reader.loadAsScene("GameScene.ccbi");
    cc.Director.getInstance().replaceScene(scene);
};

MainMenuScene.prototype.onPressedMusic = function()
{
	gSettingMusicEnabled = !gSettingMusicEnabled;
	
	if (gSettingMusicEnabled)
	{
    	cc.AudioEngine.getInstance().playMusic("Music.mp3");
    }
    else
    {
    	cc.AudioEngine.getInstance().stopMusic();
    }
	
	this.updateSettingsDisplay();
};

MainMenuScene.prototype.onPressedControl = function()
{
	if (gSettingControlType == CD_CONTROLTYPE_TOUCH)
	{
		gSettingControlType = CD_CONTROLTYPE_TILT;
	}
	else
	{
		gSettingControlType = CD_CONTROLTYPE_TOUCH;
	}
	this.updateSettingsDisplay();
};
