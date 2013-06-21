cocos2d-x
=========

[![Build Status](https://travis-ci.org/cocos2d/cocos2d-x.png?branch=master)](https://travis-ci.org/cocos2d/cocos2d-x)

[cocos2d-x][1] is a multi-platform 2D game framework in C++, branched on
[cocos2d-iphone][2] and licensed under MIT.  The master branch on github uses
OpenGL ES 2.0 rendering, while the old gles11 branch uses OpenGL ES 1.1
rendering. Currently we focus on gles20 developmenet.

Supported Platforms
-------------------

   * iOS:  stable, well tested on iOS 5.x ~ 6.x SDK.
   * Android: stable, well tested on 2.0~4.x, ndk r5 ~ r8. If you use gles20
     branch or cocos2d-x v2.0 above, only android 2.3 and higher are supported
   * Windows Phone 8 and Win8 Metro: stable, it's in another repo
     http://github.com/cocos2d-x/cocos2dx-win8.
   * Bada: cocos2d-x v1.x supports Bada SDK 1.0 & 2.0. Bada support was
     deprecated since cocos2d-x v2.0.
   * BlackBerry: stable, contributed by staffs in RIM, supports Playbook & BB10.
   * Marmalade: stable since cocos2d-x v0.11.0, contributed by Marmalade's staff.
   * Native Client (NaCl): contributed by the Native Client authors.
   * Windows: stable, well tested on WinXP/Vista/Win7. Please upgrde the drive
     of your video card if you meet problems on OpenGL functions
   * Linux: support but not very stable.
   * Emscripten: Alpha-level. Most features implemented. Needs testing.
     Contributed by Zynga staff.
   * Tizen: Experimental. Essential features implemented. Needs more implementing.
     Contributed by Lee, Jae-Hong.

You can visit our continuous integration system http://ci.cocos2d-x.org to
check the stability on edge version.

Supported Programming Languages
-------------------------------

   * C++ is the major programming language of cocos2d-x. Tons of top-chart
     cocos2d-x games were written in C++.
   * Lua binding is also widely used. Glu mobile, Zynga, UCWEB, 4399, Renren
     Games are using lua on cocos2d-x.
   * Javascript binding is our recommendation since 2012 H2. Cocos2d community
     are cooperating on the same Javasciprt API on cocos2d-iphone/-x/-html5.

Documentations
--------------

   * Wiki: [wiki.cocos2d-x.org][3]
   * [Online API References][4]

Contact us
----------

   * Forum: [http://forum.cocos2d-x.org][5]
   * Twitter: [http://www.twitter.com/cocos2dx][6]
   * Weibo: [http://t.sina.com.cn/cocos2dx][7]

[1]: http://www.cocos2d-x.org "cocos2d-x"
[2]: http://www.cocos2d-iphone.org "cocos2d for iPhone"
[3]: http://wiki.cocos2d-x.org "wiki.cocos2d-x.org"
[4]: http://www.cocos2d-x.org/projects/cocos2d-x/wiki/Reference "API References"
[5]: http://forum.cocos2d-x.org "http://forum.cocos2d-x.org"
[6]: http://www.twitter.com/cocos2dx "http://www.twitter.com/cocos2dx"
[7]: http://t.sina.com.cn/cocos2dx "http://t.sina.com.cn/cocos2dx"
