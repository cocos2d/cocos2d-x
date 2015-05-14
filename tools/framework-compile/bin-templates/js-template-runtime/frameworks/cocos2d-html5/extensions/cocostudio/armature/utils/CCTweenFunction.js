/****************************************************************************
 Copyright (c) 2011-2012 cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.

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

/**
 * TweenType
 * @type Object
 */
ccs.TweenType = {
    CUSTOM_EASING: -1,
    LINEAR: 0,

    SINE_EASEIN: 1,
    SINE_EASEOUT: 2,
    SINE_EASEINOUT: 3,

    QUAD_EASEIN: 4,
    QUAD_EASEOUT: 5,
    QUAD_EASEINOUT: 6,

    CUBIC_EASEIN: 7,
    CUBIC_EASEOUT: 8,
    CUBIC_EASEINOUT: 9,

    QUART_EASEIN: 10,
    QUART_EASEOUT: 11,
    QUART_EASEINOUT: 12,

    QUINT_EASEIN: 13,
    QUINT_EASEOUT: 14,
    QUINT_EASEINOUT: 15,

    EXPO_EASEIN: 16,
    EXPO_EASEOUT: 17,
    EXPO_EASEINOUT: 18,

    CIRC_EASEIN: 19,
    CIRC_EASEOUT: 20,
    CIRC_EASEINOUT: 21,

    ELASTIC_EASEIN: 22,
    ELASTIC_EASEOUT: 23,
    ELASTIC_EASEINOUT: 24,

    BACK_EASEIN: 25,
    BACK_EASEOUT: 26,
    BACK_EASEINOUT: 27,

    BOUNCE_EASEIN: 28,
    BOUNCE_EASEOUT: 29,
    BOUNCE_EASEINOUT: 30,

    TWEEN_EASING_MAX: 10000
};

ccs.TweenFunction = ccs.TweenFunction || ccs.Class.extend({});

ccs.DOUBLE_PI = ccs.M_PI_X_2 = Math.PI * 2;
ccs.HALF_PI = ccs.M_PI_2 = Math.PI / 2;
ccs.M_PI = Math.PI;

ccs.TweenFunction.tweenTo = function (time, type, easingParam) {
    var delta = 0;

    switch (type) {
        case ccs.TweenType.CUSTOM_EASING:
            delta = this.customEase(time, easingParam);
            break;
        case ccs.TweenType.LINEAR:
            delta = this.linear(time);
            break;
        case ccs.TweenType.SINE_EASEIN:
            delta = this.sineEaseIn(time);
            break;
        case ccs.TweenType.SINE_EASEOUT:
            delta = this.sineEaseOut(time);
            break;
        case ccs.TweenType.SINE_EASEINOUT:
            delta = this.sineEaseInOut(time);
            break;

        case ccs.TweenType.QUAD_EASEIN:
            delta = this.quadEaseIn(time);
            break;
        case ccs.TweenType.QUAD_EASEOUT:
            delta = this.quadEaseOut(time);
            break;
        case ccs.TweenType.QUAD_EASEINOUT:
            delta = this.quadEaseInOut(time);
            break;

        case ccs.TweenType.CUBIC_EASEIN:
            delta = this.cubicEaseIn(time);
            break;
        case ccs.TweenType.CUBIC_EASEOUT:
            delta = this.cubicEaseOut(time);
            break;
        case ccs.TweenType.CUBIC_EASEINOUT:
            delta = this.cubicEaseInOut(time);
            break;

        case ccs.TweenType.QUART_EASEIN:
            delta = this.quartEaseIn(time);
            break;
        case ccs.TweenType.QUART_EASEOUT:
            delta = this.quartEaseOut(time);
            break;
        case ccs.TweenType.QUART_EASEINOUT:
            delta = this.quartEaseInOut(time);
            break;

        case ccs.TweenType.QUINT_EASEIN:
            delta = this.quintEaseIn(time);
            break;
        case ccs.TweenType.QUINT_EASEOUT:
            delta = this.quintEaseOut(time);
            break;
        case ccs.TweenType.QUINT_EASEINOUT:
            delta = this.quintEaseInOut(time);
            break;

        case ccs.TweenType.EXPO_EASEIN:
            delta = this.expoEaseIn(time);
            break;
        case ccs.TweenType.EXPO_EASEOUT:
            delta = this.expoEaseOut(time);
            break;
        case ccs.TweenType.EXPO_EASEINOUT:
            delta = this.expoEaseInOut(time);
            break;

        case ccs.TweenType.CIRC_EASEIN:
            delta = this.circEaseIn(time);
            break;
        case ccs.TweenType.CIRC_EASEOUT:
            delta = this.circEaseOut(time);
            break;
        case ccs.TweenType.CIRC_EASEINOUT:
            delta = this.circEaseInOut(time);
            break;

        case ccs.TweenType.ELASTIC_EASEIN:
            var period = 0.3;
            if(null != easingParam && easingParam.length > 0){
                period = easingParam[0];
            }
            delta = this.elasticEaseIn(time, period);
            break;
        case ccs.TweenType.ELASTIC_EASEOUT:
            var period = 0.3;
            if(null != easingParam && easingParam.length > 0){
                period = easingParam[0];
            }
            delta = this.elasticEaseOut(time, period);
            break;
        case ccs.TweenType.ELASTIC_EASEINOUT:
            var period = 0.3;
            if(null != easingParam && easingParam.length > 0){
                period = easingParam[0];
            }
            delta = this.elasticEaseInOut(time, period);
            break;

        case ccs.TweenType.BACK_EASEIN:
            delta = this.backEaseIn(time);
            break;
        case ccs.TweenType.BACK_EASEOUT:
            delta = this.backEaseOut(time);
            break;
        case ccs.TweenType.BACK_EASEINOUT:
            delta = this.backEaseInOut(time);
            break;

        case ccs.TweenType.BOUNCE_EASEIN:
            delta = this.bounceEaseIn(time);
            break;
        case ccs.TweenType.BOUNCE_EASEOUT:
            delta = this.bounceEaseOut(time);
            break;
        case ccs.TweenType.BOUNCE_EASEINOUT:
            delta = this.bounceEaseInOut(time);
            break;

        default:
            delta = this.sineEaseInOut(time);
            break;
    }

    return delta;
};


// Linear
ccs.TweenFunction.linear = function (time) {
    return time;
};


// Sine Ease
ccs.TweenFunction.sineEaseIn = function (time) {
    return -1 * Math.cos(time * ccs.HALF_PI) + 1;
};
ccs.TweenFunction.sineEaseOut = function (time) {
    return Math.sin(time * ccs.HALF_PI);
};
ccs.TweenFunction.sineEaseInOut = function (time) {
    return -0.5 * (Math.cos(ccs.M_PI * time) - 1);
};


// Quad Ease
ccs.TweenFunction.quadEaseIn = function (time) {
    return time * time;
};
ccs.TweenFunction.quadEaseOut = function (time) {
    return -1 * time * (time - 2);
};
ccs.TweenFunction.quadEaseInOut = function (time) {
    time = time * 2;
    if (time < 1)
        return 0.5 * time * time;
    --time;
    return -0.5 * (time * (time - 2) - 1);
};


// Cubic Ease
ccs.TweenFunction.cubicEaseIn = function (time) {
    return time * time * time;
};
ccs.TweenFunction.cubicEaseOut = function (time) {
    time -= 1;
    return (time * time * time + 1);
};
ccs.TweenFunction.cubicEaseInOut = function (time) {
    time = time * 2;
    if (time < 1)
        return 0.5 * time * time * time;
    time -= 2;
    return 0.5 * (time * time * time + 2);
};


// Quart Ease
ccs.TweenFunction.quartEaseIn = function (time) {
    return time * time * time * time;
};
ccs.TweenFunction.quartEaseOut = function (time) {
    time -= 1;
    return -(time * time * time * time - 1);
};
ccs.TweenFunction.quartEaseInOut = function (time) {
    time = time * 2;
    if (time < 1)
        return 0.5 * time * time * time * time;
    time -= 2;
    return -0.5 * (time * time * time * time - 2);
};


// Quint Ease
ccs.TweenFunction.quintEaseIn = function (time) {
    return time * time * time * time * time;
};
ccs.TweenFunction.quintEaseOut = function (time) {
    time -= 1;
    return (time * time * time * time * time + 1);
};
ccs.TweenFunction.quintEaseInOut = function (time) {
    time = time * 2;
    if (time < 1)
        return 0.5 * time * time * time * time * time;
    time -= 2;
    return 0.5 * (time * time * time * time * time + 2);
};


// Expo Ease
ccs.TweenFunction.expoEaseIn = function (time) {
    return time === 0 ? 0 : Math.pow(2, 10 * (time - 1)) - 0.001;
};
ccs.TweenFunction.expoEaseOut = function (time) {
    return time === 1 ? 1 : (-Math.pow(2, -10 * time) + 1);
};
ccs.TweenFunction.expoEaseInOut = function (time) {
    time /= 0.5;
    if (time < 1) {
        time = 0.5 * Math.pow(2, 10 * (time - 1));
    }
    else {
        time = 0.5 * (-Math.pow(2, -10 * (time - 1)) + 2);
    }

    return time;
};


// Circ Ease
ccs.TweenFunction.circEaseIn = function (time) {
    return -1 * (Math.sqrt(1 - time * time) - 1);
};
ccs.TweenFunction.circEaseOut = function (time) {
    time = time - 1;
    return Math.sqrt(1 - time * time);
};
ccs.TweenFunction.circEaseInOut = function (time) {
    time = time * 2;
    if (time < 1)
        return -0.5 * (Math.sqrt(1 - time * time) - 1);
    time -= 2;
    return 0.5 * (Math.sqrt(1 - time * time) + 1);
};


// Elastic Ease
ccs.TweenFunction.elasticEaseIn = function (time, easingParam) {
    var period = 0.3;

    if (easingParam.length > 0) {
        period = easingParam[0];
    }

    var newT = 0;
    if (time === 0 || time === 1) {
        newT = time;
    }
    else {
        var s = period / 4;
        time = time - 1;
        newT = -Math.pow(2, 10 * time) * Math.sin((time - s) * ccs.DOUBLE_PI / period);
    }

    return newT;
};
ccs.TweenFunction.elasticEaseOut = function (time, easingParam) {
    var period = 0.3;

    if (easingParam.length > 0) {
        period = easingParam[0];
    }

    var newT = 0;
    if (time === 0 || time === 1) {
        newT = time;
    }
    else {
        var s = period / 4;
        newT = Math.pow(2, -10 * time) * Math.sin((time - s) * ccs.DOUBLE_PI / period) + 1;
    }

    return newT;
};
ccs.TweenFunction.elasticEaseInOut = function (time, easingParam) {
    var period = 0.3;

    if (easingParam.length > 0) {
        period = easingParam[0];
    }

    var newT = 0;
    if (time === 0 || time === 1) {
        newT = time;
    }
    else {
        time = time * 2;
        if (!period) {
            period = 0.3 * 1.5;
        }

        var s = period / 4;

        time = time - 1;
        if (time < 0) {
            newT = -0.5 * Math.pow(2, 10 * time) * Math.sin((time - s) * ccs.DOUBLE_PI / period);
        } else {
            newT = Math.pow(2, -10 * time) * Math.sin((time - s) * ccs.DOUBLE_PI / period) * 0.5 + 1;
        }
    }
    return newT;
};


// Back Ease
ccs.TweenFunction.backEaseIn = function (time) {
    var overshoot = 1.70158;
    return time * time * ((overshoot + 1) * time - overshoot);
};
ccs.TweenFunction.backEaseOut = function (time) {
    var overshoot = 1.70158;

    time = time - 1;
    return time * time * ((overshoot + 1) * time + overshoot) + 1;
};
ccs.TweenFunction.backEaseInOut = function (time) {
    var overshoot = 1.70158 * 1.525;

    time = time * 2;
    if (time < 1) {
        return (time * time * ((overshoot + 1) * time - overshoot)) / 2;
    }
    else {
        time = time - 2;
        return (time * time * ((overshoot + 1) * time + overshoot)) / 2 + 1;
    }
};


// Bounce Ease
ccs.bounceTime = function (time) {
    if (time < 1 / 2.75) {
        return 7.5625 * time * time;
    } else if (time < 2 / 2.75) {
        time -= 1.5 / 2.75;
        return 7.5625 * time * time + 0.75;
    } else if (time < 2.5 / 2.75) {
        time -= 2.25 / 2.75;
        return 7.5625 * time * time + 0.9375;
    }

    time -= 2.625 / 2.75;
    return 7.5625 * time * time + 0.984375;
};
ccs.TweenFunction.bounceEaseIn = function (time) {
    return 1 - ccs.bounceTime(1 - time);
};

ccs.TweenFunction.bounceEaseOut = function (time) {
    return ccs.bounceTime(time);
};

ccs.TweenFunction.bounceEaseInOut = function (time) {
    var newT = 0;
    if (time < 0.5) {
        time = time * 2;
        newT = (1 - ccs.bounceTime(1 - time)) * 0.5;
    } else {
        newT = ccs.bounceTime(time * 2 - 1) * 0.5 + 0.5;
    }

    return newT;
};


// Custom Ease
ccs.TweenFunction.customEase = function (time, easingParam) {
    if (easingParam.length > 0) {
        var tt = 1 - time;
        return easingParam[1] * tt * tt * tt + 3 * easingParam[3] * time * tt * tt + 3 * easingParam[5] * time * time * tt + easingParam[7] * time * time * time;
    }
    return time;
};

ccs.TweenFunction.easeIn = function(time, rate){
    return Math.pow(time, rate);
};

ccs.TweenFunction.easeOut = function(time, rate){
    return Math.pow(time, 1 / rate);
};

ccs.TweenFunction.easeInOut = function(time, rate){
    time *= 2;
    if(time < 1){
        return 0.5 * Math.pow(time, rate);
    }else{
        return 1 - 0.5 * Math.pow(2 - time, rate);
    }
};

ccs.TweenFunction.quadraticIn = function(time){
    return Math.pow(time, 2);
};

ccs.TweenFunction.quadraticOut = function(time){
    return -time * (time - 2);
};

ccs.TweenFunction.bezieratFunction = function(a, b, c, d, t){
    return (Math.pow(1-t,3) * a + 3*t*(Math.pow(1-t,2))*b + 3*Math.pow(t,2)*(1-t)*c + Math.pow(t,3)*d );
};