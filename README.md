# TestJS

Simple iOS (and soon Android) example of cocos2d-x game running javascript bindings

*NOTE* This is a WIP and the bindings are not yet complete! What's working:

	CCPoint CCSize CCRect CCDirector CCNode CCSprite CCScene CCSpriteFrameCache
	CCSpriteFrame CCAction CCAnimate CCAnimation CCRepeatForever CCLayer CCTouch
	CCSet CCMoveBy CCMoveTo CCRotateTo CCRotateBy CCRenderTexture CCMenu CCMenuItem
	CCMenuItemLabel CCMenuItemSprite CCMenuItemImage CCLabelTTF CCSequence

This is just a proof of concept and there are plans around this in order to make a more js-friendly API, right now
the bindings were created automatically and the final idea is not to use them as they are but to create a higher
level wrapper.

You can follow the progress of the js-bindings in the current [development fork](https://github.com/funkaster/cocos2d-x/tree/js-bindings).

For a sneak peak, you can take a look at what's in the JS directory.

## How to Build

### Before hitting the "Build" button

In debug mode, (when there's a `#define DEBUG` somewhere), the javascript code will be read from somewhere else and not from the JS directory
in the app bundle. To make sure this works, modify the absolute path in ScriptingCore:

```c++
void ScriptingCore::runScript(const char *path)
{
#ifdef DEBUG
	std::string dpath("/Users/rabarca/Desktop/testjs/testjs/");
	dpath += path;
	const char *realPath = dpath.c_str();
#else
	const char *realPath = CCFileUtils::fullPathFromRelativePath(path);
#endif
	unsigned char *content = NULL;
	size_t contentSize = CCFileUtils::ccLoadFileIntoMemory(realPath, &content);
	if (content && contentSize) {
		JSBool ok;
		jsval rval;
		ok = JS_EvaluateScript(this->cx, this->global, (char *)content, contentSize, path, 1, &rval);
		if (JSVAL_IS_NULL(rval) || rval == JSVAL_FALSE) {
			CCLog("error evaluating script:\n%s", content);
		}
		free(content);
	}
}
```

Basically, the dpath string should point to wherever the JS directory is located. This affects every script
run through the `runScript` function from `ScriptingCore`. If you don't want that behaviour, then just set
the dpath string to `""`. It also allows for the "reload script" button to work on the demo:

![screenshot 1](http://dl.dropbox.com/u/29043245/testjs1.png)

If you set the dpath string to `""` (empty string) then the reload button will try to reload the script from
inside the bundle.

In the test scenes the buttons represent:

* top left: will reload the current script
* left arrow: previous test scene in the script
* center button: will reload the current scene
* right arrow: next test scene in the script

The current test script can be changed in the AppDelegate (or by modifying the source and then hitting reload script):

```c++
# AppDelegate.cpp
bool AppDelegate::applicationDidFinishLaunching()
{
...
	// run the main script
	ScriptingCore::getInstance().runScript("JS/1to1/test_actions.js");
//	ScriptingCore::getInstance().runScript("JS/1to1/test_layer.js");

	return true;
}
```

Change the script name there and relaunch the simulator.

### iOS

Just open the xcode project and run. It's using the latest spidermonkey and js-bindings for cocos2d-x

### Android

Instructions to be added here
