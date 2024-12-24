import { WorkerManager } from '../workers/WorkerManager'
import {
  VideoPlayerInfo,
  VideoEvent
} from '@ohos/libSysCapabilities/src/main/ets/components/videoplayer/VideoPlayerMsg';
import worker from '@ohos.worker';

@Component
export struct CocosVideoPlayer {
  @ObjectLink videoPlayerInfo: VideoPlayerInfo;
  cocosWorker: worker.ThreadWorker = WorkerManager.getInstance().getWorker();

  build() {
    Column() {
      Video({
        src: this.videoPlayerInfo.isUrl ? this.videoPlayerInfo.url : this.videoPlayerInfo.rawfile,
        controller: this.videoPlayerInfo.controller
      })
        .width(this.videoPlayerInfo.w)
        .height(this.videoPlayerInfo.h)
        .visibility(this.videoPlayerInfo.visible ? Visibility.Visible : Visibility.None)
        .controls(false)
        .loop(this.videoPlayerInfo.isLoop)
        .objectFit(this.videoPlayerInfo.objectFit)
        .onPrepared(() => {
          if (this.videoPlayerInfo.isPlay) {
            this.videoPlayerInfo.controller.start()
          }
          this.videoPlayerInfo.controller.requestFullscreen(this.videoPlayerInfo.isFullScreen)
        })
        .onStart(() => {
          this.cocosWorker.postMessage({
            type: "onVideoCallBack",
            viewTag: this.videoPlayerInfo.viewTag,
            event: VideoEvent.PLAYING
          });
        })
        .onPause(() => {
          this.cocosWorker.postMessage({
            type: "onVideoCallBack",
            viewTag: this.videoPlayerInfo.viewTag,
            event: VideoEvent.PAUSED
          });
        })
        .onFinish(() => {
          this.cocosWorker.postMessage({
            type: "onVideoCallBack",
            viewTag: this.videoPlayerInfo.viewTag,
            event: VideoEvent.COMPLETED
          });
        })
    }
  }
}
