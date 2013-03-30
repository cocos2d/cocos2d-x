//
// sys properties
//

var sys = sys || {};

Object.defineProperties(sys,
{
	"capabilities" : {
		get : function(){
			var capabilities = {"opengl":true};
			if( sys.platform == 'mobile' ) {
				capabilities["accelerometer"] = true;
				capabilities["touches"] = true;
			} else {
				// desktop
				capabilities["keyboard"] = true;
				capabilities["mouse"] = true;
			}
			return capabilities;
        },
		enumerable : true,
		configurable : true
	},
	"os" : {
		get : function(){
            return __getOS();
        },
		enumerable : true,
		configurable : true
	},
	"platform" : {
		get : function(){
            return __getPlatform();
        },
		enumerable : true,
		configurable : true
	},
	"version" : {
		get : function(){
            return __getVersion();
        },
		enumerable : true,
		configurable : true
	}

});

// Forces the garbage collector
sys.garbageCollect = function() {
	__jsc__.garbageCollect();
};

// Dumps rooted objects
sys.dumpRoot = function() {
	__jsc__.dumpRoot();
};

// restarts the JS VM
sys.restartVM = function() {
	__restartVM();
};