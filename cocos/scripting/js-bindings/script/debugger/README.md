Remote Debugging By Using FireFox
=================================

Requirement
-----------

* Firefox: From v24

How To Use
----------

### Prepare ###

Please refer to https://developer.mozilla.org/en-US/docs/Tools/Remote_Debugging .

### Enable Debugger Support For Your JSB Project ###

```
bool AppDelegate::applicationDidFinishLaunching()
{
    ...
    
    ScriptingCore* sc = ScriptingCore::getInstance();
    sc->addRegisterCallback(register_all_cocos2dx);
    sc->addRegisterCallback(register_all_cocos2dx_extension);
    sc->addRegisterCallback(register_cocos2dx_js_extensions);
    sc->addRegisterCallback(jsb_register_chipmunk);
    sc->addRegisterCallback(register_all_cocos2dx_extension_manual);
    sc->addRegisterCallback(register_CCBuilderReader);
    sc->addRegisterCallback(jsb_register_system);
    sc->addRegisterCallback(JSB_register_opengl);
    
    sc->start();
    
#if defined(COCOS2D_DEBUG) && (COCOS2D_DEBUG > 0)
    sc->enableDebugger();   // Enable debugger here
#endif

   ...
}
```

Run your game.

### Open Firefox And Follow The Step As Follows ###


![pic 1](https://lh5.googleusercontent.com/-HoxLGBdV2J0/UlZ7ZoFUjyI/AAAAAAAAADM/68GDaCQ1vP0/s0-I/Firefox-Remote-Debug01.jpg)
![pic 2](https://lh6.googleusercontent.com/-7FDIHAYsKAY/UlZ7Yf8W-pI/AAAAAAAAAFQ/joG0AymnuBk/s0-I/Firefox-Remote-Debug02.jpg)
![pic 3](https://lh4.googleusercontent.com/-idvnMRGcGy8/UlZ7Wj6DDuI/AAAAAAAAAC0/L9IVyHLNqeQ/s0-I/Firefox-Remote-Debug04.jpg)
![pic 4](https://lh6.googleusercontent.com/-YuZj7JGAtFE/UlZ9DDGDczI/AAAAAAAAAEQ/D2qIedjP5FU/s0-I/Firefox-Remote-Debug04.png.png)
![pic 5](https://lh3.googleusercontent.com/-cdIcNa3jT5c/UlZ9uapf3OI/AAAAAAAAAEg/MGq3vLHsauw/s0-I/Firefox-Remote-Debug05.png)
![pic 6](https://lh5.googleusercontent.com/-T79-o5ylJKI/UlZ_JJQe3MI/AAAAAAAAAE8/F63fSVxlJKs/s0-I/Firefox-Remote-Debug06.png)

