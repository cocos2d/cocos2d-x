/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011      Zynga Inc.

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

var CurrentLanguageTest = cc.Layer.extend({
    ctor:function () {
        this._super();

        var s = cc.Director.getInstance().getWinSize();
        var label = cc.LabelTTF.create("Current language Test", "Arial", 28);
        this.addChild(label, 0);
        label.setPosition(cc.p(s.width / 2, s.height - 50));

        var labelLanguage = cc.LabelTTF.create("", "Arial", 20);
        labelLanguage.setPosition(cc.p(s.width / 2, s.height / 2));

        var currentLanguageType = cc.Application.getCurrentLanguage();
        switch (currentLanguageType) {
            case cc.LANGUAGE_ENGLISH:
                labelLanguage.setString("current language is English");
                break;
            case cc.LANGUAGE_CHINESE:
                labelLanguage.setString("current language is Chinese");
                break;
            case cc.LANGUAGE_FRENCH:
                labelLanguage.setString("current language is French");
                break;
            case cc.LANGUAGE_GERMAN:
                labelLanguage.setString("current language is German");
                break;
            case cc.LANGUAGE_ITALIAN:
                labelLanguage.setString("current language is Italian");
                break;
            case cc.LANGUAGE_RUSSIAN:
                labelLanguage.setString("current language is Russian");
                break;
            case cc.LANGUAGE_SPANISH:
                labelLanguage.setString("current language is Spanish");
                break;
        }

        this.addChild(labelLanguage);
    }
});

var CurrentLanguageTestScene = TestScene.extend({
    runThisTest:function () {
        var layer = new CurrentLanguageTest();
        this.addChild(layer);

        cc.Director.getInstance().replaceScene(this);
    }
});
