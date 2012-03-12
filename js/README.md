# About this branch's work

The idea of this work was to have a working JavaScript VM that would work on most platforms. We intially decided to use JavaScriptCore mainly because it was being used by WebKit and it was already (at some point) working on iOS and Android.

The problem with this was that the license for JavaScriptCore (LGPL) is not compatible with Apple's App Store.

The code here is legacy and while we might updated it from time to time, the new effort will be in another branch, using SpiderMonkey.

JSC is added as a submodule, so if you want to get, just run (from the root of the repo):

    git submodule init; git submodule update

# How to test this

1. Compile JSC for iOS (open the xcode project and select the iOS target). Make sure you're targeting the simulator (otherwise build a universal version)
2. Create a new cocos2d-x project
3. Add the bindings to the project
4. Link against the .a file produced by the JSC project
5. Add a JS folder reference to your project, and add some of the examples in there
6. Make sure your app delegate has some code like this:

<pre>
# define MAIN_SCRIPT "JS/main.js"
#include "ScriptingCore.h"
...
bool AppDelegate::applicationDidFinishLaunching()
{
  ...
  ScriptingCore::getInstance().runScript(MAIN_SCRIPT);
  ...
}
</pre>

That should work. If you have problems, make sure you're linking the right version (target) of the static library.