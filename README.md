# TestJS

Simple iOS (and soon Android) example of cocos2d-x game running javascript bindings

*NOTE* This is a WIP and the bindings are not yet complete! What's working:

CCPoint CCSize CCRect CCDirector CCNode CCSprite CCScene CCSpriteFrameCache
CCSpriteFrame CCAction CCAnimate CCAnimation CCRepeatForever CCLayer CCTouch
CCSet CCMoveBy CCMoveTo CCRotateTo CCRotateBy CCRenderTexture

This is just a proof of concept and there are plans around this in order to make a more js-friendly API, right now
the bindings were created automatically and the final idea is not to use them as they are but to create a higher
level wrapper.

You can follow the progress of the js-bindings in the current [development fork](https://github.com/funkaster/cocos2d-x/tree/js-bindings).

For a sneak peak, you can take a look at what's in the JS directory.

## How to Build

### iOS

Just open the xcode project and run. It's using the latest spidermonkey and js-bindings for cocos2d-x

### Android

Instructions to be added here
