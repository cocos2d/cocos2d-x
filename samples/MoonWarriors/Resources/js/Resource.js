var dirImg = "";
var dirMusic = "";
var musicSuffix = ".mp3";
if( cc.config.deviceType == 'browser') {
    dirImg = "res/";
    dirMusic = "res/Music/";
    musicSuffix = "";
}
else if( cc.config.engine == 'cocos2d-x') {
    dirImg = "res/";
    dirMusic = "res/Music/";
    musicSuffix = ".mp3";
}

//image
var s_bg01 = dirImg + "bg01.jpg";
var s_loading = dirImg + "loading.png";
var s_ship01 = dirImg + "ship01.png";
var s_menu = dirImg + "menu.png";
var s_logo = dirImg + "logo.png";
var s_cocos2dhtml5 = dirImg + "cocos2d-html5.png";
var s_gameOver = dirImg + "gameOver.png";
var s_menuTitle = dirImg + "menuTitle.png";
var s_Enemy = dirImg + "Enemy.png";
var s_flare = dirImg + "flare.jpg";
var s_bullet = dirImg + "bullet.png";
var s_explosion = dirImg + "explosion.png";
var s_explode1 = dirImg + "explode1.jpg";
var s_explode2= dirImg + "explode2.jpg";
var s_explode3 = dirImg + "explode3.jpg";
var s_hit = dirImg + "hit.jpg";
var s_arial14 = dirImg + "arial-14.png";
var s_arial14_fnt = dirImg + "arial-14.fnt";

//music
var s_bgMusic = dirMusic + "bgMusic" + musicSuffix;
var s_mainMainMusic = dirMusic + "mainMainMusic" + musicSuffix;

//effect
var s_buttonEffect = dirMusic + "buttonEffet" + musicSuffix;
var s_explodeEffect = dirMusic + "explodeEffect" + musicSuffix;
var s_fireEffect = dirMusic + "fireEffect" + musicSuffix;
var s_shipDestroyEffect = dirMusic + "shipDestroyEffect" + musicSuffix;

//tmx
var s_level01 = dirImg + "level01.tmx";

//plist
var s_Enemy_plist = dirImg + "Enemy.plist";
var s_explosion_plist = dirImg + "explosion.plist";
var s_bullet_plist = dirImg + "bullet.plist";

var g_ressources = [
    //image
    {type:"image", src:s_bg01},
    {type:"image", src:s_loading},
    {type:"image", src:s_ship01},
    {type:"image", src:s_menu},
    {type:"image", src:s_logo},
    {type:"image", src:s_cocos2dhtml5},
    {type:"image", src:s_gameOver},
    {type:"image", src:s_menuTitle},
    {type:"image", src:s_Enemy},
    {type:"image", src:s_flare},
    {type:"image", src:s_bullet},
    {type:"image", src:s_explosion},
    {type:"image", src:s_explode1},
    {type:"image", src:s_explode2},
    {type:"image", src:s_explode3},
    {type:"image", src:s_hit},
    {type:"image", src:s_arial14},

    //tmx
    {type:"tmx", src:s_level01},

    //plist
    {type:"plist", src:s_Enemy_plist},
    {type:"plist", src:s_explosion_plist},
    {type:"plist", src:s_bullet_plist},

    //music
    {type:"bgm", src:s_bgMusic},
    {type:"bgm", src:s_mainMainMusic},

    //effect
    {type:"effect", src:s_buttonEffect},
    {type:"effect", src:s_explodeEffect},
    {type:"effect", src:s_fireEffect},
    {type:"effect", src:s_shipDestroyEffect},

    // FNT
    {type:"fnt", src:s_arial14_fnt}

];
