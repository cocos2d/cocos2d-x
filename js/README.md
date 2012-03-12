# About this branch's work

The idea of this work was to have a working JavaScript VM that would work on most platforms. We intially decided to use JavaScriptCore mainly because it was being used by WebKit and it was already (at some point) working on iOS and Android.

The problem with this was that the license for JavaScriptCore (LGPL) is not compatible with Apple's App Store.

The code here is legacy and while we might updated it from time to time, the new effort will be in another branch, using SpiderMonkey.

JSC is added as a submodule, so if you want to get, just run (from the root of the repo):

    git submodule init; git submodule update
