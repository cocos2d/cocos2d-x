
// JS Bindings constants
require("jsb_constants.js");

// Resources definitions
require("tests_resources-jsb.js");

// Load main file
require("tests-main.js");

// Load tests files

cc.log = cc.log || log;
cc.config =  cc.config || {};
cc.config.deviceType = 'mobile';

var tests_files = [
		'ActionsTest.js',
		'EaseActionsTest.js',
		'LabelTest.js',
		'LayerTest.js',
		'MenuTest.js',
		'SpriteTest.js',
        'ParticleTest.js'
	];
for( var i=0; i < tests_files.length; i++) {
	cc.log(" Loading: " + tests_files[i] );
	require( tests_files[i] );
}

// cc.AudioEngine.getInstance().init("mp3,ogg");

var scene = cc.Scene.create();
var layer = new TestController();
scene.addChild(layer);
director.runWithScene( scene );
