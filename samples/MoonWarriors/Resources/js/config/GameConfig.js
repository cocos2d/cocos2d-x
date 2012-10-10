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

//game state
MW.GAME_STATE = {
    HOME:0,
    PLAY:1,
    OVER:2
};

//keys
MW.KEYS = [];

//level
MW.LEVEL = {
    STAGE1:1,
    STAGE2:2,
    STAGE3:3
};

//life
MW.LIFE = 4;

//score
MW.SCORE = 0;

//sound
MW.SOUND = true;

//enemy move type
MW.ENEMY_MOVE_TYPE = {
    ATTACK:0,
    VERTICAL:1,
    HORIZONTAL:2,
    OVERLAP:3
};

//delta x
MW.DELTA_X = -100;

//offset x
MW.OFFSET_X = -24;

//rot
MW.ROT = -5.625;

//bullet type
MW.BULLET_TYPE = {
    PLAYER:1,
    ENEMY:2
};

//weapon type
MW.WEAPON_TYPE = {
    ONE:1
};

//unit tag
MW.UNIT_TAG = {
    ENMEY_BULLET:900,
    PLAYER_BULLET:901,
    ENEMY:1000,
    PLAYER:1000
};

//attack mode
MW.ENEMY_ATTACK_MODE = {
    NORMAL:1,
    TSUIHIKIDAN:2
};

//life up sorce
MW.LIFEUP_SORCE = [50000, 100000, 150000, 200000, 250000, 300000];

//container
MW.CONTAINER = {
    ENEMIES:[],
    ENEMY_BULLETS:[],
    PLAYER_BULLETS:[]
};
