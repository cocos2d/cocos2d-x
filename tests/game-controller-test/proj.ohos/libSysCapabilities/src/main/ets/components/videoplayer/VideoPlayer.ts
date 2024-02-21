import { VideoPlayMsgEntity, ViewRect } from '../../entity/WorkerMsgEntity';

export class VideoPlayer {
    static MODULE_NAME: string = 'VideoPlay';

    private static parentPort;

    static init(parentPort) : void {
        VideoPlayer.parentPort = parentPort;
    }

    static setURL(viewTag: number, url: string, isUrl: number) : void {
        let videoPlayMsgEntity: VideoPlayMsgEntity = new VideoPlayMsgEntity(VideoPlayer.MODULE_NAME, 'setURL', viewTag);
        videoPlayMsgEntity.url = url;
        videoPlayMsgEntity.isUrl = isUrl;
        VideoPlayer.parentPort.postMessage(videoPlayMsgEntity);
    }

    static setLooping(viewTag: number, isLoop: boolean) : void {
        let videoPlayMsgEntity: VideoPlayMsgEntity = new VideoPlayMsgEntity(VideoPlayer.MODULE_NAME, 'setLooping', viewTag);
        videoPlayMsgEntity.isLoop = isLoop;
        VideoPlayer.parentPort.postMessage(videoPlayMsgEntity);
    }

    static createVideoPlayer(viewTag: number) : void {
        let videoPlayMsgEntity: VideoPlayMsgEntity = new VideoPlayMsgEntity(VideoPlayer.MODULE_NAME, 'createVideoPlayer', viewTag);
        VideoPlayer.parentPort.postMessage(videoPlayMsgEntity);
    }

    static removeVideoPlayer(viewTag: number) : void {
        let videoPlayMsgEntity: VideoPlayMsgEntity = new VideoPlayMsgEntity(VideoPlayer.MODULE_NAME, 'removeVideoPlayer', viewTag);
        VideoPlayer.parentPort.postMessage(videoPlayMsgEntity);
    }

    static setVideoPlayerRect(viewTag: number, x: number, y: number, w: number, h: number) : void {
        let videoPlayMsgEntity: VideoPlayMsgEntity = new VideoPlayMsgEntity(VideoPlayer.MODULE_NAME, 'setVideoPlayerRect', viewTag);
        let viewRect: ViewRect = new ViewRect(x, y, w, h);
        videoPlayMsgEntity.viewRect = viewRect;
        VideoPlayer.parentPort.postMessage(videoPlayMsgEntity);
    }

    static play(viewTag: number) : void {
        let videoPlayMsgEntity: VideoPlayMsgEntity = new VideoPlayMsgEntity(VideoPlayer.MODULE_NAME, 'play', viewTag);
        VideoPlayer.parentPort.postMessage(videoPlayMsgEntity);
    }
    static pause(viewTag: number) : void {
        let videoPlayMsgEntity: VideoPlayMsgEntity = new VideoPlayMsgEntity(VideoPlayer.MODULE_NAME, 'pause', viewTag);
        VideoPlayer.parentPort.postMessage(videoPlayMsgEntity);
    }

    static stop(viewTag: number) : void {
        let videoPlayMsgEntity: VideoPlayMsgEntity = new VideoPlayMsgEntity(VideoPlayer.MODULE_NAME, 'stop', viewTag);
        VideoPlayer.parentPort.postMessage(videoPlayMsgEntity);
    }

    static setVisible(viewTag: number, visible: boolean) : void {
        let videoPlayMsgEntity: VideoPlayMsgEntity = new VideoPlayMsgEntity(VideoPlayer.MODULE_NAME, 'setVisible', viewTag);
        videoPlayMsgEntity.visible = visible
        VideoPlayer.parentPort.postMessage(videoPlayMsgEntity);
    }

    static requestFullscreen(viewTag: number, isFullScreen: boolean) : void {
        let videoPlayMsgEntity: VideoPlayMsgEntity = new VideoPlayMsgEntity(VideoPlayer.MODULE_NAME, 'requestFullscreen', viewTag);
        videoPlayMsgEntity.isFullScreen = isFullScreen;
        VideoPlayer.parentPort.postMessage(videoPlayMsgEntity);
    }

    static seekTo(viewTag: number, seekTo: number) : void {
        let videoPlayMsgEntity: VideoPlayMsgEntity = new VideoPlayMsgEntity(VideoPlayer.MODULE_NAME, 'seekTo', viewTag);
        videoPlayMsgEntity.seekTo = seekTo;
        VideoPlayer.parentPort.postMessage(videoPlayMsgEntity);
    }

    static setKeepAspectRatioEnabled(viewTag: number, enable: boolean) : void {
        let videoPlayMsgEntity: VideoPlayMsgEntity = new VideoPlayMsgEntity(VideoPlayer.MODULE_NAME, 'setKeepAspectRatioEnabled', viewTag);
        videoPlayMsgEntity.keepAspectRatioEnabled = enable;
        VideoPlayer.parentPort.postMessage(videoPlayMsgEntity);
    }
}
