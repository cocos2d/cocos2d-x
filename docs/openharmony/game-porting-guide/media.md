# 媒体

## 音频
2dx鸿蒙化，当前全部使用的OPENSL ES 相关接口，而不是系统TS层媒体组件。

2dx上已鸿蒙化的版本，音频模块代码是完整的体系，正常不需要改动，直接移植即可。2.2.6 版本音频模块代码在CocosDenshion/ohos中。2.x版本的2dx游戏，直接对应CocosDenshion/include/SimpleAudioEngine.h 中的相关接口；3.17.2 版本音频模块代码在cocos/audio/ohos 中，3.x版本的2dx游戏，可以参考3.17.2 ,对接 audio/include/SimpleAudioEngine.h 中的相关接口。

如用户要自行使用OPENSL ES接口，请参考鸿蒙官方[demo代码](https://gitee.com/openharmony/multimedia_audio_framework/blob/OpenHarmony-3.2-Release/frameworks/native/opensles/test/example/audio_opensles_player_test.cpp)

注意点：大部分用户之前如果自行调用OPENSL接口，一般会自己创建buffer，再调用enqueue接口播放。在鸿蒙上，其架构设计期望用户调用其GetBuffer接口获取的buffer。这个接口中有一个清理过期缓存的流程，如果用户在enqueue之前没有调用这个接口，播放的音频会出现很多杂音。解决方法可以参考当前2dx中的PcmAudioService.cpp。里面在调用opensl的enqueue接口前，专门调用了一下GetBuffer接口。
