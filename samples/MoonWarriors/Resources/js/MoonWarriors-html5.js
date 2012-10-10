/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 
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

// boot code needed for cocos2d-html5
// Not needed by cocos2d + JS bindings

var MW = MW || {};

(function () {
    var d = document;
    var c = {
        menuType:'canvas', //whether to use canvas mode menu or dom menu
        COCOS2D_DEBUG:2, //0 to turn debug off, 1 for basic debug, and 2 for full debug
        showFPS:true,
        frameRate:60,
        tag:'gameCanvas', //the dom element to run cocos2d on
        engineDir:'libs/cocos2d/',
        appFiles:[
            'MoonWarriors/src/Resource.js',
            'MoonWarriors/src/config/GameConfig.js',
            'MoonWarriors/src/config/EnemyType.js',
            'MoonWarriors/src/config/Level.js',
            'MoonWarriors/src/Effect.js',
            'MoonWarriors/src/Bullet.js',
            'MoonWarriors/src/Enemy.js',
            'MoonWarriors/src/Explosion.js',
            'MoonWarriors/src/Ship.js',
            'MoonWarriors/src/LevelManager.js',
            'MoonWarriors/src/GameController.js',
            'MoonWarriors/src/GameControlMenu.js',
            'MoonWarriors/src/GameLayer.js',
            'MoonWarriors/src/GameOver.js',
            'MoonWarriors/src/AboutLayer.js',
            'MoonWarriors/src/SettingsLayer.js',
            'MoonWarriors/src/SysMenu.js'
        ]
    };
    window.addEventListener('DOMContentLoaded', function () {
        //first load engine file if specified
        var s = d.createElement('script');
        s.src = c.engineDir + 'platform/jsloader.js';
        d.body.appendChild(s);
        s.c = c;
        s.id = 'cocos2d-html5';
        //else if single file specified, load singlefile
    });
})();
