<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Cocos2d-x 3.13.1 Release Notes](#cocos2d-x-3131-release-notes)
- [Misc Information](#misc-information)
- [v3.13.1](#v3131)
  - [Bug fixed](#bug-fixed)
  - [Cocos command modification](#cocos-command-modification)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Cocos2d-x 3.13.1 Release Notes #

# Misc Information

* [Full Changelog](https://github.com/cocos2d/cocos2d-x/blob/v3/CHANGELOG)

# v3.13.1

## Bug fixed

* Label color broken
* application will crash in debug mode if don't specify a design resolution
* may crash if coming from background by clicking application icon on Android
* AudioEngine can not play audio if the audio lies outside APK on Android
* AudioEngine::stop() will trigger `finish` callback on Android
* application will crash if using SimpleAudioEngine or new AudioEngine to play audio on Android 2.3.x
* object.setString() has not effect if passing a number on JSB

## Cocos command modifications

Prior to `v3.13` the __cocos__ command would find an Android API level __>=__ a specified
Android API level inorder to build source codes on Android. For example, if the contents of
__APP_ROOT/proj.android/project.properties__ is:

```
target=android-13 // the default android api level
android.library.reference.1=../../../cocos/platform/android/java
```

then the __cocos__ command will find __android-13__ in `ANDROID_SDK_ROOT/platforms`. If __android-13__
is not found then it will try to find __android-14__. If __android-14__ is not found, then it will find
__android-15__ and so on until it finds one.

This algorithm has a problem. If you only download __Android 21__, then your application will be built with
__Android 21__ even though the default API level is 13. If your application runs on a device with a lower Android OS,
such as Android 4.0, then your application may crash. Building with a higher API level does not ensure that your
application will run on devices with a lower Android OS.

Starting in `v3.13.1`, the __cocos__ command will stop if it can not find a specific API level. The default
is __android-13__. If you want to build with a higher level Android SDK, you should explicitely specify it.
Example:

```sh
cocos compile -p android --ap android-19
```

Keep in mind that, after running this command, the contents of `APP_ROOT/proj.android/project.properties` will
be changed, __android-19__ will now be the default API level.

There is a map between Android API level and Android OS version that you can [refer to](https://developer.android.com/guide/topics/manifest/uses-sdk-element.html) for detailed information.

There is also more detailed information in our [GitHub repo](https://github.com/cocos2d/cocos2d-x/milestone/33) about this issue.
