
// boot code needed for cocos2d + JS bindings.
// Not needed by cocos2d-html5

require("jsb.js");

var appFiles = [
    'src/resource.js',
    'src/app.js'
];

cc.dumpConfig();

for( var i=0; i < appFiles.length; i++) {
    require( appFiles[i] );
}

var director = cc.Director.getInstance();
director.setDisplayStats(true);

// set FPS. the default value is 1.0/60 if you don't call this
director.setAnimationInterval(1.0 / 60);

// create a scene. it's an autorelease object
var myScene = new MyScene();

// run
if (director.getRunningScene())
{
	director.replaceScene(myScene);
}
else
{
	director.runWithScene(myScene);
}
