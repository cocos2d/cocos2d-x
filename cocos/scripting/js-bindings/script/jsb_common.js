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

cc.KEY = {
    none:0,

    // android
    back:6,
    menu:18,

    // desktop
    backspace:8,
    tab:9,

    enter:13,

    shift:16, //should use shiftkey instead
    ctrl:17, //should use ctrlkey
    alt:18, //should use altkey
    pause:19,
    capslock:20,

    escape:27,
    space:32,
    pageup:33,
    pagedown:34,
    end:35,
    home:36,
    left:37,
    up:38,
    right:39,
    down:40,
    select:41,

    insert:45,
    Delete:46,
    0:48,
    1:49,
    2:50,
    3:51,
    4:52,
    5:53,
    6:54,
    7:55,
    8:56,
    9:57,
    a:65,
    b:66,
    c:67,
    d:68,
    e:69,
    f:70,
    g:71,
    h:72,
    i:73,
    j:74,
    k:75,
    l:76,
    m:77,
    n:78,
    o:79,
    p:80,
    q:81,
    r:82,
    s:83,
    t:84,
    u:85,
    v:86,
    w:87,
    x:88,
    y:89,
    z:90,

    num0:96,
    num1:97,
    num2:98,
    num3:99,
    num4:100,
    num5:101,
    num6:102,
    num7:103,
    num8:104,
    num9:105,
    '*':106,
    '+':107,
    '-':109,
    'numdel':110,
    '/':111,
    f1:112, //f1-f12 don't work on ie
    f2:113,
    f3:114,
    f4:115,
    f5:116,
    f6:117,
    f7:118,
    f8:119,
    f9:120,
    f10:121,
    f11:122,
    f12:123,

    numlock:144,
    scrolllock:145,

    ';':186,
    semicolon:186,
    equal:187,
    '=':187,
    ',':188,
    comma:188,
    dash:189,
    '.':190,
    period:190,
    forwardslash:191,
    grave:192,
    '[':219,
    openbracket:219,
    backslash:220,
    ']':221,
    closebracket:221,
    quote:222,

    // gamepad control
    dpadLeft:1000,
    dpadRight:1001,
    dpadUp:1003,
    dpadDown:1004,
    dpadCenter:1005
};

var jsbKeyArr = [
    cc.KEY["none"],//0
    cc.KEY["pause"],//1
    cc.KEY["scrolllock"],//2
    cc.KEY["none"],//3
    cc.KEY["none"],//4
    cc.KEY["none"],//5
    cc.KEY["back"],//6
    cc.KEY["backspace"],//7
    cc.KEY["tab"],//8
    cc.KEY["none"],//9
    cc.KEY["none"],//10
    cc.KEY["capslock"],//11
    cc.KEY["shift"],//12//should use shiftkey instead
    cc.KEY["shift"],//13
    cc.KEY["ctrl"],//14//should use ctrlkey
    cc.KEY["ctrl"],//15
    cc.KEY["alt"],//16//should use altkey
    cc.KEY["alt"],//17
    cc.KEY["menu"],//18
    cc.KEY["none"],//19
    cc.KEY["insert"],//20
    cc.KEY["home"],//21
    cc.KEY["pageup"],//22
    cc.KEY["Delete"],//23
    cc.KEY["end"],//24
    cc.KEY["pagedown"],//25
    cc.KEY["left"],//26
    cc.KEY["right"],//27
    cc.KEY["up"],//28
    cc.KEY["down"],//29
    cc.KEY["numlock"],//30
    cc.KEY["+"],//31
    cc.KEY["-"],//32
    cc.KEY["*"],//33
    cc.KEY["none"],//34
    cc.KEY["enter"],//35
    cc.KEY["home"],//36
    cc.KEY["up"],//37
    cc.KEY["pageup"],//38
    cc.KEY["left"],//39
    cc.KEY["num5"],//40
    cc.KEY["right"],//41
    cc.KEY["end"],//42
    cc.KEY["down"],//43
    cc.KEY["pagedown"],//44
    cc.KEY["insert"],//45
    cc.KEY["Delete"],//46
    cc.KEY["f1"],//47
    cc.KEY["f2"],//48
    cc.KEY["f3"],//49
    cc.KEY["f4"],//50
    cc.KEY["f5"],//51
    cc.KEY["f6"],//52
    cc.KEY["f7"],//53
    cc.KEY["f8"],//54
    cc.KEY["f9"],//55
    cc.KEY["f10"],//56
    cc.KEY["f11"],//57
    cc.KEY["f12"],//58
    cc.KEY["space"],//59
    cc.KEY["none"],//60
    cc.KEY["quote"],//61
    cc.KEY["none"],//62
    cc.KEY["none"],//63
    cc.KEY["none"],//64
    cc.KEY["none"],//65
    cc.KEY["none"],//66
    cc.KEY["quote"],//67
    cc.KEY["none"],//68
    cc.KEY["none"],//69
    cc.KEY["none"],//70
    cc.KEY["none"],//71
    cc.KEY["comma"],//72
    cc.KEY["-"],//73
    cc.KEY["period"],//74
    cc.KEY["forwardslash"],//75//word keyboard
    cc.KEY["num0"],//76
    cc.KEY["num1"],//77
    cc.KEY["num2"],//78
    cc.KEY["num3"],//79
    cc.KEY["num4"],//80
    cc.KEY["num5"],//81
    cc.KEY["num6"],//82
    cc.KEY["num7"],//83
    cc.KEY["num8"],//84
    cc.KEY["num9"],//85
    cc.KEY["none"],//86
    cc.KEY["semicolon"],//87
    cc.KEY["none"],//88
    cc.KEY["equal"],//89
    cc.KEY["none"],//90
    cc.KEY["none"],//91
    cc.KEY["none"],//92
    cc.KEY["a"],//93
    cc.KEY["b"],//94
    cc.KEY["c"],//95
    cc.KEY["d"],//96
    cc.KEY["e"],//97
    cc.KEY["f"],//98
    cc.KEY["g"],//99
    cc.KEY["h"],//100
    cc.KEY["i"],//101
    cc.KEY["j"],//102
    cc.KEY["k"],//103
    cc.KEY["l"],//104
    cc.KEY["m"],//105
    cc.KEY["n"],//106
    cc.KEY["o"],//107
    cc.KEY["p"],//108
    cc.KEY["q"],//109
    cc.KEY["r"],//110
    cc.KEY["s"],//111
    cc.KEY["t"],//112
    cc.KEY["u"],//113
    cc.KEY["v"],//114
    cc.KEY["w"],//115
    cc.KEY["x"],//116
    cc.KEY["y"],//117
    cc.KEY["z"],//118
    cc.KEY["openbracket"],//119
    cc.KEY["backslash"],//120
    cc.KEY["closebracket"],//121
    cc.KEY["none"],//122
    cc.KEY["grave"],//123
    cc.KEY["a"],//124
    cc.KEY["b"],//125
    cc.KEY["c"],//126
    cc.KEY["d"],//127
    cc.KEY["e"],//128
    cc.KEY["f"],//129
    cc.KEY["g"],//130
    cc.KEY["h"],//131
    cc.KEY["i"],//132
    cc.KEY["j"],//133
    cc.KEY["k"],//134
    cc.KEY["l"],//135
    cc.KEY["m"],//136
    cc.KEY["n"],//137
    cc.KEY["o"],//138
    cc.KEY["p"],//139
    cc.KEY["q"],//140
    cc.KEY["r"],//141
    cc.KEY["s"],//142
    cc.KEY["t"],//143
    cc.KEY["u"],//144
    cc.KEY["v"],//145
    cc.KEY["w"],//146
    cc.KEY["x"],//147
    cc.KEY["y"],//148
    cc.KEY["z"],//149
    cc.KEY["none"],//150
    cc.KEY["none"],//151
    cc.KEY["none"],//152
    cc.KEY["none"],//153
    cc.KEY["none"],//154
    cc.KEY["none"],//155
    cc.KEY["none"],//156
    cc.KEY["none"],//157
    cc.KEY["none"],//158
    cc.KEY["dpadLeft"],//159
    cc.KEY["dpadRight"],//160
    cc.KEY["dpadUp"],//161
    cc.KEY["dpadDown"],//162
    cc.KEY["dpadCenter"],//163
    cc.KEY["enter"],//164
    cc.KEY["none"]//165
    // html5 more key, these key can not trigge
    //'numdel'
    //select
    //dash
];

if (cc.sys.os != cc.sys.OS_ANDROID)
{
    jsbKeyArr[6] = cc.KEY["escape"];//6
}

var parseKeyCode = function (keycode)
{
    var keyIndex = jsbKeyArr.indexOf(keycode);
    var jsbKeyCode = keyIndex == -1 ? cc.KEY.none : keyIndex;
    return jsbKeyCode;
}
