//
// cocos2d constants
//
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

cc.RED = {r:255, g:0, b:0};
cc.GREEN = {r:0, g:255, b:0};
cc.BLUE = {r:0, g:0, b:255};
cc.BLACK = {r:0, g:0, b:0};
cc.WHITE = {r:255, g:255, b:255};

cc.POINT_ZERO = {x:0, y:0};

cc._reuse_p0 = {x:0, y:0};
cc._reuse_p1 = {x:0, y:0};
cc._reuse_p_index = 0;
cc._reuse_color3b = {r:255, g:255, b:255 };
cc._reuse_color4b = {r:255, g:255, b:255, a:255 };
cc._reuse_grid = cc.g(0,0);

//
// Color 3B
//
cc.c3b = function( r, g, b )
{
    return {r:r, g:g, b:b };
};
cc._c3b = function( r, g, b )
{
    cc._reuse_color3b.r = r;
    cc._reuse_color3b.g = g;
    cc._reuse_color3b.b = b;
    return cc._reuse_color3b;
};
// compatibility
cc.c3 = cc.c3b;
cc._c3 = cc._c3b;

//
// Color 4B
//
cc.c4b = function( r, g, b, a )
{
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



//
// Color 4F
//
cc.c4f = function( r, g, b, a )
{
    return {r:r, g:g, b:b, a:a };
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
    if( cc._reuse_p_index === 0 ) {
        cc._reuse_p0.x = x;
        cc._reuse_p0.y = y;
        cc._reuse_p_index = 1;
        return cc._reuse_p0;
    } else {
        cc._reuse_p1.x = x;
        cc._reuse_p1.y = y;
        cc._reuse_p_index = 0;
        return cc._reuse_p1;
    }
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

//
// Rect
//
cc.rect = function(x,y,w,h)
{
    return {x:x, y:y, width:w, height:h};
};


// dump config info, but only in debug mode
cc.dumpConfig = function()
{
    if( cc.config.debug ) {
        for( var i in cc.config )
            cc.log( i + " = " + cc.config[i] );
    }
};

//
// MenuItemToggle
//
cc.MenuItemToggle.create = function( /* var args */) {

    var n = arguments.length;

    if (typeof arguments[n-1] === 'function') {
        var args = Array.prototype.slice.call(arguments);
        var func = args.pop();
        var obj = args.pop();
    
        // create it with arguments,
        var item = cc.MenuItemToggle._create.apply(this, args);

        // then set the callback
        item.setCallback(obj, func);
        return item;
    } else {
        return cc.MenuItemToggle._create.apply(this, arguments);
    }
};

/**
 * Associates a base class with a native superclass
 * @function
 * @param {object} jsobj subclass
 * @param {object} klass superclass
 */
cc.associateWithNative = function( jsobj, superclass ) {
    var native = new superclass();
    __associateObjWithNative( jsobj, native );
};


// XXX Should be done in native
cc.rectIntersectsRect = function( rectA, rectB )
{
    var bool = ! (  rectA.x > rectB.x + rectB.width ||
                    rectA.x + rectA.width < rectB.x ||
                    rectA.y > rectB.y +rectB.height ||
                    rectA.y + rectA.height < rectB.y );

    return bool;
};

//
// Array: for cocos2d-html5 compatibility
//
cc.ArrayRemoveObject = function (arr, delObj) {
    for (var i = 0; i < arr.length; i++) {
        if (arr[i] == delObj) {
            arr.splice(i, 1);
        }
    }
};


//
// Google "subclasses"
// borrowed from closure library
//
var goog = goog || {}; // Check to see if already defined in current scope
goog.inherits = function (childCtor, parentCtor) {
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
goog.base = function(me, opt_methodName, var_args) {
	var caller = arguments.callee.caller;
	if (caller.superClass_) {
		// This is a constructor. Call the superclass constructor.
		ret =  caller.superClass_.constructor.apply( me, Array.prototype.slice.call(arguments, 1));

		// XXX: SpiderMonkey bindings extensions
//		__associateObjWithNative( me, ret );
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
					'goog.base called from a method of one name ' +
					'to a method of a different name');
	}
};


//
// Simple subclass
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
