// cocos2d Helper

cc.c3 = cc.c3 || function (r, g, b) {
	return {r: r, g: g, b: b};
};

cc.c4 = cc.c4 || function (r, g, b, o) {
	return {r: r, g: g, b: b, a: o};
};

cc.c4f = cc.c4f || function (r, g, b, o) {
	return {r: r, g: g, b: b, a: o};
};

cc.p = cc.p || function( x, y )
{
    return {x:x, y:y};
};

cc.g = cc.g || cc.p;
cc.log = cc.log || log;

//
// cocos2d constants
//
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

cc.RED = cc.c3(255,0,0);
cc.GREEN = cc.c3(0,255,0);
cc.BLUE = cc.c3(0,0,255);
cc.BLACK = cc.c3(0,0,0);
cc.WHITE = cc.c3(255,255,255);

cc.POINT_ZERO = {x:0, y:0};

cc._reuse_p0 = {x:0, y:0};
cc._reuse_p1 = {x:0, y:0};
cc._reuse_p_index = 0;
cc._reuse_color3b = cc.c3(255, 255, 255 );
cc._reuse_color4b = cc.c4(255, 255, 255, 255 );
cc._reuse_grid = cc.g(0,0);

// dump config info, but only in debug mode
cc.dumpConfig = function()
{
    if( cc.config.debug ) {
        for(var i in cc.config)
            cc.log( i + " = " + cc.config[i] );
    }
};

//
// Point
//
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

cc._to_p = function( point )
{
    return point;
};

cc._from_p = function( size )
{
    return size;
};

//
// Grid 
//
cc._g = function( x, y )
{
    cc._reuse_grid.x = x;
    cc._reuse_grid.y = y;
    return cc._reuse_grid;
}

//
// Color
//
cc._c3 = function( r, g, b )
{
    cc._reuse_color3b[0] = r;
    cc._reuse_color3b[1] = g;
    cc._reuse_color3b[2] = b;
    return cc._reuse_color3b;
}

cc._c4 = function( r, g, b, a )
{
    cc._reuse_color4b[0] = r;
    cc._reuse_color4b[1] = g;
    cc._reuse_color4b[2] = b;
    cc._reuse_color4b[3] = a;
    return cc._reuse_color4b;
}

//
// Size
//
cc.size = function(w,h)
{
    return {width:w, height:h};
}

cc._to_size = function( size )
{
    return size;
}

cc._from_size = function( size )
{
    return size;
}

//
// Rect
//
cc.rect = function(x,y,w,h)
{
    return {x:x, y:y, width:w, height:h};
}

cc._to_rect = function( rect )
{
    return rect;
}

cc._from_rect = function( rect )
{
    return rect;
}

// XXX Should be done in native
cc.rectIntersectsRect = function( rectA, rectB )
{
    var bool = ! (  rectA.x > rectB.x + rectB.width ||
                    rectA.x + rectA.width < rectB.x ||
                    rectA.y > rectB.y +rectB.height ||
                    rectA.y + rectA.height < rectB.y );

    return bool;
}

// point functions
cc.pAdd = cc.pAdd || function (p1, p2) {
    return {x: p1.x + p2.x, y: p1.y + p2.y};
};

cc.pSub = cc.pSub || function (p1, p2) {
    return {x: p1.x - p2.x, y: p1.y - p2.y};
}

cc.pMult = cc.pMult || function (p1, s) {
    return {x: p1.x * s, y: p1.y * s};
};

//
// Array: for cocos2d-hmtl5 compatibility
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

cc.Layer.extend = cc.Class.extend;
cc.LayerGradient.extend = cc.Class.extend;
cc.Sprite.extend = cc.Class.extend;
cc.MenuItemFont.extend = cc.Class.extend;

//
// Chipmunk helpers
//
var cp = cp || {};

cp.v = cc.p;
cp._v = cc._p;
cp.vzero  = cp.v(0,0);

//
// OpenGL Helpers
//
var gl = gl || {};
gl.NEAREST                      = 0x2600;
gl.LINEAR                       = 0x2601;
gl.REPEAT                       = 0x2901;
gl.CLAMP_TO_EDGE                = 0x812F;
gl.CLAMP_TO_BORDER              = 0x812D;
gl.LINEAR_MIPMAP_NEAREST        = 0x2701;
gl.NEAREST_MIPMAP_NEAREST       = 0x2700;
gl.ZERO                         = 0;
gl.ONE                          = 1;
gl.SRC_COLOR                    = 0x0300;
gl.ONE_MINUS_SRC_COLOR          = 0x0301;
gl.SRC_ALPHA                    = 0x0302;
gl.ONE_MINUS_SRC_ALPHA          = 0x0303;
gl.DST_ALPHA                    = 0x0304;
gl.ONE_MINUS_DST_ALPHA          = 0x0305;
gl.DST_COLOR                    = 0x0306;
gl.ONE_MINUS_DST_COLOR          = 0x0307;
gl.SRC_ALPHA_SATURATE           = 0x0308;

