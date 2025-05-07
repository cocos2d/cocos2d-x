import Logger from '../../utils/Logger'
import { BusinessError } from '@ohos.base';
import { GlobalContext,GlobalContextConstants } from "../../common/GlobalContext"

let log: Logger = new Logger(0x0001, "VideoPlayer");
@Observed
export class VideoPlayerInfo {
    // position
    public x: number = 0;
    public y: number = 0;
    // size
    public w: number = 0;
    public h: number = 0;
    // url
    public url: string = ''

    public rawfile?: Resource;
    public isUrl: boolean = false
    // tag
    public viewTag: number = 0

    public isPlay: boolean = false
    public isFullScreen: boolean = false

    // Whether to display
    public visible: boolean = true

    public isLoop: boolean = false

    public objectFit: ImageFit = ImageFit.Auto

    public controller: VideoController = new VideoController()

    constructor(x: number, y: number, w: number, h: number, viewTag: number) {
        this.x = x;
        this.y = y;
        this.w = w;
        this.h = h;
        this.viewTag = viewTag;
    }
}

export enum VideoEvent {
    PLAYING = 0,
    PAUSED,
    STOPPED,
    COMPLETED,
}

export class VideoPlayer {
    static MODULE_NAME: string = 'VideoPlay';

    static setURL(viewTag: number, url: string, isUrl: number) : void {
        let videoPlayInfo:VideoPlayerInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_VIDEO_PLAYER_INDEX_MAP).get(viewTag);
        if(isUrl == 0) {
            videoPlayInfo.isUrl = false;
            videoPlayInfo.rawfile = $rawfile(url);
        } else {
            videoPlayInfo.isUrl = true;
            videoPlayInfo.url = url;
        }
    }

    static setLooping(viewTag: number, isLoop: boolean) : void {
        let videoPlayInfo: VideoPlayerInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_VIDEO_PLAYER_INDEX_MAP).get(viewTag);
        videoPlayInfo.isLoop = isLoop;
    }

    static createVideoPlayer(viewTag: number) : void {
        let newVideoPlayerInfo = new VideoPlayerInfo(0, 0, 0, 0, viewTag);
        GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_VIDEO_PLAYER_ARRAY).push(newVideoPlayerInfo);
        GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_VIDEO_PLAYER_INDEX_MAP).set(viewTag, newVideoPlayerInfo);
    }

    static removeVideoPlayer(viewTag: number) : void {
        let removeIndex = -1;
        GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_VIDEO_PLAYER_ARRAY).forEach((item:VideoPlayerInfo,index:number) => {
            if (item.viewTag == viewTag) {
                removeIndex = index;
            }
        });
        GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_VIDEO_PLAYER_INDEX_MAP).get(viewTag).controller.requestFullscreen(false);
        GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_VIDEO_PLAYER_ARRAY).splice(removeIndex, 1);
        GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_VIDEO_PLAYER_INDEX_MAP).delete(viewTag);
    }

    static setVideoPlayerRect(viewTag: number, x: number, y: number, w: number, h: number) : void {
        let videoPlayInfo:VideoPlayerInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_VIDEO_PLAYER_INDEX_MAP).get(viewTag);
        try {
            videoPlayInfo.x = px2vp(x);
            videoPlayInfo.y = px2vp(y);
            videoPlayInfo.w = px2vp(w);
            videoPlayInfo.h = px2vp(h);
        } catch (error) {
            let e: BusinessError = error as BusinessError;
            log.error('videoPlayerInfo  ErrorCode: %{public}d,  Message: %{public}s', e.code, e.message);
        }
    }

    static play(viewTag: number) : void {
        let videoPlayInfo :VideoPlayerInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_VIDEO_PLAYER_INDEX_MAP).get(viewTag);
        videoPlayInfo.controller.start();
        videoPlayInfo.isPlay = true;
    }
    static pause(viewTag: number) : void {
        let videoPlayInfo:VideoPlayerInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_VIDEO_PLAYER_INDEX_MAP).get(viewTag);
        videoPlayInfo.controller.pause();
        videoPlayInfo.isPlay = false;
    }

    static stop(viewTag: number) : void {
        let videoPlayInfo:VideoPlayerInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_VIDEO_PLAYER_INDEX_MAP).get(viewTag);
        videoPlayInfo.controller.stop();
        videoPlayInfo.isPlay = false;
    }

    static setVisible(viewTag: number, visible: boolean) : void {
        let videoPlayInfo:VideoPlayerInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_VIDEO_PLAYER_INDEX_MAP).get(viewTag);
        if (videoPlayInfo.visible == visible) {
            return;
        }
        videoPlayInfo.visible = visible;
    }

    static requestFullscreen(viewTag: number, isFullScreen: boolean) : void {
        let videoPlayInfo: VideoPlayerInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_VIDEO_PLAYER_INDEX_MAP).get(viewTag);
        videoPlayInfo.controller.requestFullscreen(isFullScreen);
        videoPlayInfo.isFullScreen = isFullScreen;
    }

    static seekTo(viewTag: number, seekTo: number) : void {
        let videoPlayInfo: VideoPlayerInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_VIDEO_PLAYER_INDEX_MAP).get(viewTag);
        videoPlayInfo.controller.setCurrentTime(seekTo, SeekMode.Accurate);
    }

    static setKeepAspectRatioEnabled(viewTag: number, enable: boolean) : void {
        let videoPlayInfo: VideoPlayerInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_VIDEO_PLAYER_INDEX_MAP).get(viewTag);
        videoPlayInfo.objectFit = enable? ImageFit.Cover : ImageFit.Auto;
    }
}
