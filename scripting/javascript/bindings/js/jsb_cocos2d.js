//
// cocos2d constants
//

var cc = cc || {};
var window = window || this;
/**
 * Device type
 * @constant
 * @type {Object}
 */
cc.TARGET_PLATFORM = {
    WINDOWS:0,
    LINUX:1,
    MACOS:2,
    ANDROID:3,
    IPHONE:4,
    IPAD:5,
    BLACKBERRY:6,
    NACL:7,
    EMSCRIPTEN:8,
    MOBILE_BROWSER:100,
    PC_BROWSER:101
};

cc.LANGUAGE_ENGLISH    = 0;
cc.LANGUAGE_CHINESE    = 1;
cc.LANGUAGE_FRENCH     = 2;
cc.LANGUAGE_ITALIAN    = 3;
cc.LANGUAGE_GERMAN     = 4;
cc.LANGUAGE_SPANISH    = 5;
cc.LANGUAGE_RUSSIAN    = 6;
cc.LANGUAGE_KOREAN     = 7;
cc.LANGUAGE_JAPANESE   = 8;
cc.LANGUAGE_HUNGARIAN  = 9;
cc.LANGUAGE_PORTUGUESE = 10;
cc.LANGUAGE_ARABIC     = 11;

cc.DIRECTOR_PROJECTION_2D = 0;
cc.DIRECTOR_PROJECTION_3D = 1;

cc.TEXTURE_PIXELFORMAT_RGBA8888 = 0;
cc.TEXTURE_PIXELFORMAT_RGB888 = 1;
cc.TEXTURE_PIXELFORMAT_RGB565 = 2;
cc.TEXTURE_PIXELFORMAT_A8 = 3;
cc.TEXTURE_PIXELFORMAT_I8 = 4;
cc.TEXTURE_PIXELFORMAT_AI88 = 5;
cc.TEXTURE_PIXELFORMAT_RGBA4444 = 6;
cc.TEXTURE_PIXELFORMAT_RGB5A1 = 7;
cc.TEXTURE_PIXELFORMAT_PVRTC4 = 8;
cc.TEXTURE_PIXELFORMAT_PVRTC4 = 9;
cc.TEXTURE_PIXELFORMAT_DEFAULT = cc.TEXTURE_PIXELFORMAT_RGBA8888;

cc.TEXT_ALIGNMENT_LEFT  = 0;
cc.TEXT_ALIGNMENT_CENTER = 1;
cc.TEXT_ALIGNMENT_RIGHT = 2;

cc.VERTICAL_TEXT_ALIGNMENT_TOP = 0;
cc.VERTICAL_TEXT_ALIGNMENT_CENTER = 1;
cc.VERTICAL_TEXT_ALIGNMENT_BOTTOM = 2;

cc.IMAGE_FORMAT_JPEG = 0;
cc.IMAGE_FORMAT_PNG = 0;

cc.PROGRESS_TIMER_TYPE_RADIAL = 0;
cc.PROGRESS_TIMER_TYPE_BAR = 1;

cc.PARTICLE_TYPE_FREE = 0;
cc.PARTICLE_TYPE_RELATIVE = 1;
cc.PARTICLE_TYPE_GROUPED = 2;
cc.PARTICLE_DURATION_INFINITY = -1;
cc.PARTICLE_MODE_GRAVITY = 0;
cc.PARTICLE_MODE_RADIUS = 1;
cc.PARTICLE_START_SIZE_EQUAL_TO_END_SIZE = -1;
cc.PARTICLE_START_RADIUS_EQUAL_TO_END_RADIUS = -1;

cc.TOUCH_ALL_AT_ONCE = 0;
cc.TOUCH_ONE_BY_ONE = 1;

cc.TMX_TILE_HORIZONTAL_FLAG = 0x80000000;
cc.TMX_TILE_VERTICAL_FLAG = 0x40000000;
cc.TMX_TILE_DIAGONAL_FLAG = 0x20000000;

cc.TRANSITION_ORIENTATION_LEFT_OVER = 0;
cc.TRANSITION_ORIENTATION_RIGHT_OVER = 1;
cc.TRANSITION_ORIENTATION_UP_OVER = 0;
cc.TRANSITION_ORIENTATION_DOWN_OVER = 1;

cc.RED = {r:255, g:0, b:0};
cc.GREEN = {r:0, g:255, b:0};
cc.BLUE = {r:0, g:0, b:255};
cc.BLACK = {r:0, g:0, b:0};
cc.WHITE = {r:255, g:255, b:255};
cc.YELLOW = {r:255, g:255, b:0};

cc.POINT_ZERO = {x:0, y:0};

// XXX: This definition is different than cocos2d-html5
// cc.REPEAT_FOREVER = - 1;
// We can't assign -1 to cc.REPEAT_FOREVER, since it will be a very big double value after
// converting it to double by JS_ValueToNumber on android.
// Then cast it to unsigned int, the value will be 0. The schedule will not be able to work.
// I don't know why this occurs only on android.
// So instead of passing -1 to it, I assign it with max value of unsigned int in c++.
cc.REPEAT_FOREVER = 0xffffffff;

cc.MENU_STATE_WAITING = 0;
cc.MENU_STATE_TRACKING_TOUCH = 1;
cc.MENU_HANDLER_PRIORITY = -128;
cc.DEFAULT_PADDING = 5;

// reusable objects
cc._reuse_p = [ {x:0, y:0}, {x:0,y:0}, {x:0,y:0}, {x:0,y:0} ];
cc._reuse_p_index = 0;
cc._reuse_size = {width:0, height:0};
cc._reuse_rect = {x:0, y:0, width:0, height:0};
cc._reuse_color3b = {r:255, g:255, b:255 };
cc._reuse_color4b = {r:255, g:255, b:255, a:255 };
cc.log = cc._cocosplayerLog || cc.log || log;

//
// Color 3B
//
cc.c3b = function( r, g, b )
{
    switch (arguments.length) {
        case 0:
            return {r:0, g:0, b:0 };
        case 1:
            if (r && r instanceof cc.c3b) {
            	  return {r:r.r, g:r.g, b:r.b };
            } else {
                return {r:0, g:0, b:0 };
            }
        case 3:
            return {r:r, g:g, b:b };
        default:
            throw "unknown argument type";
            break;
    }
};

cc.integerToColor3B = function (intValue) {
    intValue = intValue || 0;

    var offset = 0xff;
    var retColor = {r:0, g:0, b:0 };
    retColor.r = intValue & (offset);
    retColor.g = (intValue >> 8) & offset;
    retColor.b = (intValue >> 16) & offset;
    return retColor;
};

cc._c3b = function( r, g, b )
{
    cc._reuse_color3b.r = r;
    cc._reuse_color3b.g = g;
    cc._reuse_color3b.b = b;
    return cc._reuse_color3b;
};

cc.c3BEqual = function(color1, color2){
    return color1.r === color2.r && color1.g === color2.g && color1.b === color2.b;
};

cc.white = function () {
    return cc.c3b(255, 255, 255);
};

cc.yellow = function () {
    return cc.c3b(255, 255, 0);
};

cc.blue = function () {
    return cc.c3b(0, 0, 255);
};

cc.green = function () {
    return cc.c3b(0, 255, 0);
};

cc.red = function () {
    return cc.c3b(255, 0, 0);
};

cc.magenta = function () {
    return cc.c3b(255, 0, 255);
};

cc.black = function () {
    return cc.c3b(0, 0, 0);
};

cc.orange = function () {
    return cc.c3b(255, 127, 0);
};

cc.gray = function () {
    return cc.c3b(166, 166, 166);
};

//
// Color 4B
//
cc.c4b = function (r, g, b, a) {
    return {r:r, g:g, b:b, a:a };
};

cc._c4b = function( r, g, b, a )
{
    cc._reuse_color4b.r = r;
    cc._reuse_color4b.g = g;
    cc._reuse_color4b.b = b;
    cc._reuse_color4b.a = a;
    return cc._reuse_color4b;
};
// compatibility
cc.c4 = cc.c4b;
cc._c4 = cc._c4b;

cc.c4f = function (r, g, b, a) {
    return {r:r, g:g, b:b, a:a };
};

cc.c4FFromccc3B = function (c) {
    return cc.c4f(c.r / 255.0, c.g / 255.0, c.b / 255.0, 1.0);
};

cc.c4FFromccc4B = function (c) {
    return cc.c4f(c.r / 255.0, c.g / 255.0, c.b / 255.0, c.a / 255.0);
};

cc.c4BFromccc4F = function (c) {
    return cc.c4f(0 | (c.r * 255), 0 | (c.g * 255), 0 | (c.b * 255), 0 | (c.a * 255));
};

cc.c4FEqual = function (a, b) {
    return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a;
};

/**
 * convert Color3B to a string of color for style.
 * e.g.  Color3B(255,6,255)  to : "#ff06ff"
 * @param clr
 * @return {String}
 */
cc.convertColor3BtoHexString = function (clr) {
    var hR = clr.r.toString(16);
    var hG = clr.g.toString(16);
    var hB = clr.b.toString(16);
    var stClr = "#" + (clr.r < 16 ? ("0" + hR) : hR) + (clr.g < 16 ? ("0" + hG) : hG) + (clr.b < 16 ? ("0" + hB) : hB);
    return stClr;
};

//
// Point
//
cc.p = function( x, y )
{
    return {x:x, y:y};
};
cc._p = function( x, y )
{
    if( cc._reuse_p_index == cc._reuse_p.length )
        cc._reuse_p_index = 0;

    var p = cc._reuse_p[ cc._reuse_p_index];
    cc._reuse_p_index++;
    p.x = x;
    p.y = y;
    return p;
};

cc.pointEqualToPoint = function (point1, point2) {
    return ((point1.x == point2.x) && (point1.y == point2.y));
};

cc.PointZero = function () {
    return cc.p(0, 0);
};

//
// Grid
//
cc._g = function( x, y )
{
    cc._reuse_grid.x = x;
    cc._reuse_grid.y = y;
    return cc._reuse_grid;
};

//
// Size
//
cc.size = function(w,h)
{
    return {width:w, height:h};
};
cc._size = function(w,h)
{
    cc._reuse_size.width = w;
    cc._reuse_size.height = h;
    return cc._reuse_size;
};
cc.sizeEqualToSize = function (size1, size2)
{
    return ((size1.width == size2.width) && (size1.height == size2.height));
};
cc.SizeZero = function () {
    return cc.size(0, 0);
};

//
// Rect
//
cc.rect = function(x,y,w,h)
{
    return {x:x, y:y, width:w, height:h};
};
cc._rect = function(x,y,w,h)
{
    cc._reuse_rect.x = x;
    cc._reuse_rect.y = y;
    cc._reuse_rect.width = w;
    cc._reuse_rect.height = h;
    return cc._reuse_rect;
};
cc.rectEqualToRect = function (rect1, rect2) {
    return ( rect1.x==rect2.x && rect1.y==rect2.y && rect1.width==rect2.width && rect1.height==rect2.height);
};

cc.rectContainsRect = function (rect1, rect2) {
    if ((rect1.x >= rect2.x) || (rect1.y >= rect2.y) ||
        ( rect1.x + rect1.width <= rect2.x + rect2.width) ||
        ( rect1.y + rect1.height <= rect2.y + rect2.height))
        return false;
    return true;
};

cc.rectGetMaxX = function (rect) {
    return (rect.x + rect.width);
};

cc.rectGetMidX = function (rect) {
    return (rect.x + rect.width / 2.0);
};

cc.rectGetMinX = function (rect) {
    return rect.x;
};

cc.rectGetMaxY = function (rect) {
    return(rect.y + rect.height);
};

cc.rectGetMidY = function (rect) {
    return rect.y + rect.height / 2.0;
};

cc.rectGetMinY = function (rect) {
    return rect.y;
};

cc.rectContainsPoint = function (rect, point) {
    var ret = false;
    if (point.x >= rect.x && point.x <= rect.x + rect.width &&
        point.y >= rect.y && point.y <= rect.y + rect.height) {
        ret = true;
    }
    return ret;
};

cc.rectIntersectsRect = function( rectA, rectB )
{
    var bool = ! (  rectA.x > rectB.x + rectB.width ||
                    rectA.x + rectA.width < rectB.x ||
                    rectA.y > rectB.y +rectB.height ||
                    rectA.y + rectA.height < rectB.y );

    return bool;
};

cc.rectUnion = function (rectA, rectB) {
    var rect = cc.rect(0, 0, 0, 0);
    rect.x = Math.min(rectA.x, rectB.x);
    rect.y = Math.min(rectA.y, rectB.y);
    rect.width = Math.max(rectA.x + rectA.width, rectB.x + rectB.width) - rect.x;
    rect.height = Math.max(rectA.y + rectA.height, rectB.y + rectB.height) - rect.y;
    return rect;
};

cc.rectIntersection = function (rectA, rectB) {
    var intersection = cc.rect(
        Math.max(rectA.x, rectB.x),
        Math.max(rectA.y, rectB.y),
        0, 0);

    intersection.width = Math.min(rectA.x+rectA.width, rectB.x+rectB.width) - intersection.x;
    intersection.height = Math.min(rectA.y+rectA.height, rectB.y+rectB.height) - intersection.y;
    return intersection;
};

cc.RectZero = function () {
    return cc.rect(0, 0, 0, 0);
};

cc.VisibleRect = {
    _topLeft:cc.p(0,0),
    _topRight:cc.p(0,0),
    _top:cc.p(0,0),
    _bottomLeft:cc.p(0,0),
    _bottomRight:cc.p(0,0),
    _bottom:cc.p(0,0),
    _center:cc.p(0,0),
    _left:cc.p(0,0),
    _right:cc.p(0,0),
    _width:0,
    _height:0,
    init:function(size){
        this._width = size.width;
        this._height = size.height;

        var w = this._width;
        var h = this._height;

        //top
        this._topLeft.y = h;
        this._topRight.x = w;
        this._topRight.y = h;
        this._top.x = w/2;
        this._top.y = h;

        //bottom
        this._bottomRight.x = w;
        this._bottom.x = w/2;

        //center
        this._center.x = w/2;
        this._center.y = h/2;

        //left
        this._left.y = h/2;

        //right
        this._right.x = w;
        this._right.y = h/2;
    },
    getWidth:function(){
        return this._width;
    },
    getHeight:function(){
        return this._height;
    },
    topLeft:function(){
        return this._topLeft;
    },
    topRight:function(){
        return this._topRight;
    },
    top:function(){
        return this._top;
    },
    bottomLeft:function(){
        return this._bottomLeft;
    },
    bottomRight:function(){
        return this._bottomRight;
    },
    bottom:function(){
        return this._bottom;
    },
    center:function(){
        return this._center;
    },
    left:function(){
        return this._left;
    },
    right:function(){
        return this._right;
    }
};

//
// Array: for cocos2d-html5 compatibility
//

/**
 * Returns index of first occurence of object, -1 if value not found.
 * @function
 * @param {Array} arr Source Array
 * @param {*} findObj find object
 * @return {Number} index of first occurence of value
 */
cc.ArrayGetIndexOfObject = function (arr, findObj) {
    for (var i = 0; i < arr.length; i++) {
        if (arr[i] == findObj)
            return i;
    }
    return -1;
};

/**
 * Returns a Boolean value that indicates whether value is present in the array.
 * @function
 * @param {Array} arr
 * @param {*} findObj
 * @return {Boolean}
 */
cc.ArrayContainsObject = function (arr, findObj) {
    return cc.ArrayGetIndexOfObject(arr, findObj) != -1;
};

cc.ArrayRemoveObject = function (arr, delObj) {
    for (var i = 0; i < arr.length; i++) {
        if (arr[i] == delObj) {
            arr.splice(i, 1);
        }
    }
};

//
// Helpers
//
cc.dump = function(obj)
{
    for( var i in obj )
        cc.log( i + " = " + obj[i] );
};

// dump config info, but only in debug mode
var sys = sys || undefined;
cc.dumpConfig = function()
{
    if (sys) {
        cc.dump(sys);
        cc.dump(sys.capabilities);
    }
};

//
// Bindings Overrides
//
// MenuItemToggle
cc.MenuItemToggle.create = function( /* var args */) {

    var n = arguments.length;

    if (typeof arguments[n-2] === 'function' || typeof arguments[n-1] === 'function') {
        var args = Array.prototype.slice.call(arguments);
        var obj = null;
        if( typeof arguments[n-2] === 'function' )
            obj = args.pop();

        var func = args.pop();

        // create it with arguments,
        var item = cc.MenuItemToggle._create.apply(this, args);

        // then set the callback
        if( obj !== null )
            item.setCallback(func, obj);
        else
            item.setCallback(func);
        return item;
    } else {
        return cc.MenuItemToggle._create.apply(this, arguments);
    }
};

// LabelAtlas
cc.LabelAtlas.create = function( a,b,c,d,e ) {

    var n = arguments.length;

    if ( n == 5) {
        return cc.LabelAtlas._create(a,b,c,d,e.charCodeAt(0));
    } else {
        return cc.LabelAtlas._create.apply(this, arguments);
    }
};

cc.LayerMultiplex.create = cc.LayerMultiplex.createWithArray;


/**
 * Associates a base class with a native superclass
 * @function
 * @param {object} jsobj subclass
 * @param {object} klass superclass
 */
cc.associateWithNative = function( jsobj, superclass_or_instance ) {};

//
// JSB supports 2 official ways to create subclasses
//
// 1) Google "subclasses" borrowed from closure library
// This is the recommended way to do it
//
cc.inherits = function (childCtor, parentCtor) {
	/** @constructor */
	function tempCtor() {};
	tempCtor.prototype = parentCtor.prototype;
	childCtor.superClass_ = parentCtor.prototype;
	childCtor.prototype = new tempCtor();
	childCtor.prototype.constructor = childCtor;

    // Copy "static" method, but doesn't generate subclasses.
//	for( var i in parentCtor ) {
//		childCtor[ i ] = parentCtor[ i ];
//	}
};
cc.base = function(me, opt_methodName, var_args) {
	var caller = arguments.callee.caller;
	if (caller.superClass_) {
		// This is a constructor. Call the superclass constructor.
		ret =  caller.superClass_.constructor.apply( me, Array.prototype.slice.call(arguments, 1));
		return ret;
	}

	var args = Array.prototype.slice.call(arguments, 2);
	var foundCaller = false;
	for (var ctor = me.constructor;
        ctor; ctor = ctor.superClass_ && ctor.superClass_.constructor) {
		if (ctor.prototype[opt_methodName] === caller) {
			foundCaller = true;
		} else if (foundCaller) {
			return ctor.prototype[opt_methodName].apply(me, args);
		}
	}

	// If we did not find the caller in the prototype chain,
	// then one of two things happened:
	// 1) The caller is an instance method.
	// 2) This method was not called by the right caller.
	if (me[opt_methodName] === caller) {
		return me.constructor.prototype[opt_methodName].apply(me, args);
	} else {
		throw Error(
					'cc.base called from a method of one name ' +
					'to a method of a different name');
	}
};


//
// 2) Using "extend" subclassing
// Simple JavaScript Inheritance By John Resig http://ejohn.org/
//
cc.Class = function(){};
cc.Class.extend = function (prop) {
    var _super = this.prototype;

    // Instantiate a base class (but only create the instance,
    // don't run the init constructor)
    initializing = true;
    var prototype = new this();
    initializing = false;
    fnTest = /xyz/.test(function(){xyz;}) ? /\b_super\b/ : /.*/;

    // Copy the properties over onto the new prototype
    for (var name in prop) {
        // Check if we're overwriting an existing function
        prototype[name] = typeof prop[name] == "function" &&
            typeof _super[name] == "function" && fnTest.test(prop[name]) ?
            (function (name, fn) {
                return function () {
                    var tmp = this._super;

                    // Add a new ._super() method that is the same method
                    // but on the super-class
                    this._super = _super[name];

                    // The method only need to be bound temporarily, so we
                    // remove it when we're done executing
                    var ret = fn.apply(this, arguments);
                    this._super = tmp;

                    return ret;
                };
            })(name, prop[name]) :
            prop[name];
    }

    // The dummy class constructor
    function Class() {
        // All construction is actually done in the init method
        if (!initializing && this.ctor)
            this.ctor.apply(this, arguments);
    }

    // Populate our constructed prototype object
    Class.prototype = prototype;

    // Enforce the constructor to be what we expect
    Class.prototype.constructor = Class;

    // And make this class extendable
    Class.extend = arguments.callee;

    return Class;
};

cc.Node.extend = cc.Class.extend;
cc.Layer.extend = cc.Class.extend;
cc.LayerGradient.extend = cc.Class.extend;
cc.LayerColor.extend = cc.Class.extend;
cc.Sprite.extend = cc.Class.extend;
cc.MenuItemFont.extend = cc.Class.extend;
cc.Scene.extend = cc.Class.extend;
cc.DrawNode.extend = cc.Class.extend;

// Cocos2d-html5 supports multi scene resources preloading.
// This is a compatible function for JSB.
cc.Loader = cc.Class.extend({
                            initWith:function (resources, selector, target) {
                            if (selector) {
                            this._selector = selector;
                            this._target = target;
                            }
                            this._selector.call(this._target);
                            }
                            });

cc.Loader.preload = function (resources, selector, target) {
    if (!this._instance) {
        this._instance = new cc.Loader();
    }
    this._instance.initWith(resources, selector, target);
    return this._instance;
};

cc.LoaderScene = cc.Loader;

var ConfigType = {
    NONE: 0,
    COCOSTUDIO: 1
};

var __onParseConfig = function(type, str) {
    if (type === ConfigType.COCOSTUDIO) {
        ccs.TriggerMng.getInstance().parse(JSON.parse(str));
    }
};

cc.VisibleRect = {
    _topLeft:cc.p(0,0),
    _topRight:cc.p(0,0),
    _top:cc.p(0,0),
    _bottomLeft:cc.p(0,0),
    _bottomRight:cc.p(0,0),
    _bottom:cc.p(0,0),
    _center:cc.p(0,0),
    _left:cc.p(0,0),
    _right:cc.p(0,0),
    _width:0,
    _height:0,
    _isInitialized: false,
    init:function(){
        var director = cc.Director.getInstance();
        var origin = director.getVisibleOrigin();
        var size = director.getVisibleSize();

        this._width = size.width;
        this._height = size.height;

        var x = origin.x;
        var y = origin.y;
        var w = this._width;
        var h = this._height;

        var left = origin.x;
        var right = origin.x + size.width;
        var middle = origin.x + size.width/2;

        //top
        this._top.y = this._topLeft.y = this._topRight.y = y + h;
        this._topLeft.x = left;
        this._top.x = middle;
        this._topRight.x = right;

        //bottom

        this._bottom.y = this._bottomRight.y = this._bottomLeft.y = y;
        this._bottomLeft.x = left
        this._bottom.x = middle;
        this._bottomRight.x = right;

        //center
        this._right.y = this._left.y = this._center.y = y + h/2;
        this._center.x = middle;
        
        //left
        this._left.x = left;

        //right
        this._right.x = right;
    },

    lazyInit: function(){
        if (!this._isInitialized) {
            this.init();
            this._isInitialized = true;
        }
    },
    getWidth:function(){
        this.lazyInit();
        return this._width;
    },
    getHeight:function(){
        this.lazyInit();
        return this._height;
    },
    topLeft:function(){
        this.lazyInit();        
        return this._topLeft;
    },
    topRight:function(){
        this.lazyInit();        
        return this._topRight;
    },
    top:function(){
        this.lazyInit();        
        return this._top;
    },
    bottomLeft:function(){
        this.lazyInit();        
        return this._bottomLeft;
    },
    bottomRight:function(){
        this.lazyInit();        
        return this._bottomRight;
    },
    bottom:function(){
        this.lazyInit();        
        return this._bottom;
    },
    center:function(){
        this.lazyInit();        
        return this._center;
    },
    left:function(){
        this.lazyInit();        
        return this._left;
    },
    right:function(){
        this.lazyInit();        
        return this._right;
    }
};

var _windowTimeIntervalId = 0;
var _windowTimeFunHash = {};
var WindowTimeFun = cc.Class.extend({
    _code: null,
    _intervalId: 0,
    ctor: function (code) {
        this._intervalId = _windowTimeIntervalId++;
        this._code = code;
    },
    fun: function () {
        if (!this._code) return;
        var code = this._code;
        if (typeof code == "string") {
            Function(code)();
        }
        else if (typeof code == "function") {
            code();
        }
    }
});

/**
 * overwrite window's setTimeout
 @param {String|Function} code
 @param {number} delay
 @return {number}
 */
var setTimeout = function (code, delay) {
    var target = new WindowTimeFun(code);
    cc.Director.getInstance().getScheduler().scheduleCallbackForTarget(target, target.fun, delay / 1000, 0, 0, false);
    _windowTimeFunHash[target._intervalId] = target;
    return target._intervalId;
};

/**
 * overwrite window's setInterval
 @param {String|Function} code
 @param {number} delay
 @return {number}
 */
var setInterval = function (code, delay) {
    var target = new WindowTimeFun(code);
    cc.Director.getInstance().getScheduler().scheduleCallbackForTarget(target, target.fun, delay / 1000, cc.REPEAT_FOREVER, 0, false);
    _windowTimeFunHash[target._intervalId] = target;
    return target._intervalId;
};

/**
 * overwrite window's clearInterval
 @param {number} intervalId
 */
var clearInterval = function (intervalId) {
    var target = _windowTimeFunHash[intervalId];
    if (target) {
        cc.Director.getInstance().getScheduler().unscheduleCallbackForTarget(target, target.fun);
        delete _windowTimeFunHash[intervalId];
    }
};
var clearTimeout = clearInterval;