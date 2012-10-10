/**
 *  Cocos2d-html5 show case : Moon Warriors
 *
 * @Licensed:
 * This showcase is licensed under GPL.
 *
 *  @Authors:
 *  Programmer: Shengxiang Chen (陈升想), Dingping Lv (吕定平), Ricardo Quesada
 *  Effects animation: Hao Wu (吴昊)
 *  Quality Assurance: Sean Lin (林顺)
 *
 *  @Links:
 *  http://www.cocos2d-x.org
 *  http://bbs.html5china.com
 *
 */


MW.GameController = cc.Class.extend({
    _curScene:null,
    _gameState:MW.GAME_STATE.HOME,
    _isNewGame:true,
    _curLevel:MW.LEVEL.STAGE1,
    _selectLevel:MW.LEVEL.STAGE1,
    init:function () {
        return true;
    },
    setCurScene:function (s) {
        if (this._curScene != s) {
            if (this._curScene !== null) {
                this._curScene.onExit();
            }
            this._curScene = s;
            if (this._curScene) {
                this._curScene.onEnter();
                cc.Director.getInstance().replaceScene(s);
            }
        }
    },
    getCurScene:function () {
        return this._curScene;
    },
    runGame:function () {

    },
    newGame:function () {

    },
    option:function () {

    },
    about:function () {

    }
});

MW.GameController.getInstance = function () {
    cc.Assert(this._sharedGame, "Havn't call setSharedGame");
    if (!this._sharedGame) {
        this._sharedGame = new MW.GameController();
        if (this._sharedGame.init()) {
            return this._sharedGame;
        }
    } else {
        return this._sharedGame;
    }
    return null;
};

MW.GameController._sharedGame = null;