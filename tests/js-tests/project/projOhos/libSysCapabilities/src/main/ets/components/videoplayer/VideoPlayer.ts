import { VideoPlayMsgEntity, ViewRect } from '../../entity/WorkerMsgEntity';

export class VideoPlayer {
    static MODULE_NAME: string = 'VideoPlay';

    private static workerPort;

    static init(workerPort) : void {
        VideoPlayer.workerPort = workerPort;
    }

    static setURL(viewTag: number, url: string, isUrl: number) : void {
        let videoPlayMsgEntity: VideoPlayMsgEntity = new VideoPlayMsgEntity(VideoPlayer.MODULE_NAME, 'setURL', viewTag);
        videoPlayMsgEntity.url = url;
        videoPlayMsgEntity.isUrl = isUrl;
        VideoPlayer.workerPort.postMessage(videoPlayMsgEntity);
    }

    static setLooping(viewTag: number, isLoop: boolean) : void {
        let videoPlayMsgEntity: VideoPlayMsgEntity = new VideoPlayMsgEntity(VideoPlayer.MODULE_NAME, 'setLooping', viewTag);
        videoPlayMsgEntity.isLoop = isLoop;
        VideoPlayer.workerPort.postMessage(videoPlayMsgEntity);
    }

    static createVideoPlayer(viewTag: number) : void {
        let videoPlayMsgEntity: VideoPlayMsgEntity = new VideoPlayMsgEntity(VideoPlayer.MODULE_NAME, 'createVideoPlayer', viewTag);
        VideoPlayer.workerPort.postMessage(videoPlayMsgEntity);
    }

    static removeVideoPlayer(viewTag: number) : void {
        let videoPlayMsgEntity: VideoPlayMsgEntity = new VideoPlayMsgEntity(VideoPlayer.MODULE_NAME, 'removeVideoPlayer', viewTag);
        VideoPlayer.workerPort.postMessage(videoPlayMsgEntity);
    }

    static setVideoPlayerRect(viewTag: number, x: number, y: number, w: number, h: number) : void {
        let videoPlayMsgEntity: VideoPlayMsgEntity = new VideoPlayMsgEntity(VideoPlayer.MODULE_NAME, 'setVideoPlayerRect', viewTag);
        let viewRect: ViewRect = new ViewRect(x, y, w, h);
        videoPlayMsgEntity.viewRect = viewRect;
        VideoPlayer.workerPort.postMessage(videoPlayMsgEntity);
    }

    static play(viewTag: number) : void {
        let videoPlayMsgEntity: VideoPlayMsgEntity = new VideoPlayMsgEntity(VideoPlayer.MODULE_NAME, 'play', viewTag);
        VideoPlayer.workerPort.postMessage(videoPlayMsgEntity);
    }
    static pause(viewTag: number) : void {
        let videoPlayMsgEntity: VideoPlayMsgEntity = new VideoPlayMsgEntity(VideoPlayer.MODULE_NAME, 'pause', viewTag);
        VideoPlayer.workerPort.postMessage(videoPlayMsgEntity);
    }

    static stop(viewTag: number) : void {
        let videoPlayMsgEntity: VideoPlayMsgEntity = new VideoPlayMsgEntity(VideoPlayer.MODULE_NAME, 'stop', viewTag);
        VideoPlayer.workerPort.postMessage(videoPlayMsgEntity);
    }

    static setVisible(viewTag: number, visible: boolean) : void {
        let videoPlayMsgEntity: VideoPlayMsgEntity = new VideoPlayMsgEntity(VideoPlayer.MODULE_NAME, 'setVisible', viewTag);
        videoPlayMsgEntity.visible = visible
        VideoPlayer.workerPort.postMessage(videoPlayMsgEntity);
    }

    static requestFullscreen(viewTag: number, isFullScreen: boolean) : void {
        let videoPlayMsgEntity: VideoPlayMsgEntity = new VideoPlayMsgEntity(VideoPlayer.MODULE_NAME, 'requestFullscreen', viewTag);
        videoPlayMsgEntity.isFullScreen = isFullScreen;
        VideoPlayer.workerPort.postMessage(videoPlayMsgEntity);
    }

    static seekTo(viewTag: number, seekTo: number) : void {
        let videoPlayMsgEntity: VideoPlayMsgEntity = new VideoPlayMsgEntity(VideoPlayer.MODULE_NAME, 'seekTo', viewTag);
        videoPlayMsgEntity.seekTo = seekTo;
        VideoPlayer.workerPort.postMessage(videoPlayMsgEntity);
    }

    static setKeepAspectRatioEnabled(viewTag: number, enable: boolean) : void {
        let videoPlayMsgEntity: VideoPlayMsgEntity = new VideoPlayMsgEntity(VideoPlayer.MODULE_NAME, 'setKeepAspectRatioEnabled', viewTag);
        videoPlayMsgEntity.keepAspectRatioEnabled = enable;
        VideoPlayer.workerPort.postMessage(videoPlayMsgEntity);
    }
}
