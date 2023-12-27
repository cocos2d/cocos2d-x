import Logger from '../../utils/Logger'
import { BusinessError } from '@ohos.base';
import { GlobalContext,GlobalContextConstants } from "../../common/GlobalContext"
import { VideoPlayMsgEntity } from '../../entity/WorkerMsgEntity';

let log: Logger = new Logger(0x0001, "VideoPlayerMsg");

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

export function handleVideoPlayMsg(eventData: VideoPlayMsgEntity) {

    switch (eventData.function) {
        case "createVideoPlayer": {
            let newVideoPlayerInfo = new VideoPlayerInfo(0, 0, 0, 0, eventData.viewTag);
            GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_VIDEO_PLAYER_ARRAY).push(newVideoPlayerInfo);
            GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_VIDEO_PLAYER_INDEX_MAP).set(eventData.viewTag, newVideoPlayerInfo);
            break;
        }
        case "removeVideoPlayer": {
            let removeIndex = -1;
              GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_VIDEO_PLAYER_ARRAY).forEach((item:VideoPlayerInfo,index:number) => {
                if (item.viewTag == eventData.viewTag) {
                    removeIndex = index;
                }
            });
           GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_VIDEO_PLAYER_INDEX_MAP).get(eventData.viewTag).controller.requestFullscreen(false); //4.x已修复
              GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_VIDEO_PLAYER_ARRAY).splice(removeIndex, 1);
           GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_VIDEO_PLAYER_INDEX_MAP).delete(eventData.viewTag);
            break;
        }
        case "play": {
            let videoPlayInfo :VideoPlayerInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_VIDEO_PLAYER_INDEX_MAP).get(eventData.viewTag);
            videoPlayInfo.controller.start();
            videoPlayInfo.isPlay = true;
            break;
        }
        case "pause": {
            let videoPlayInfo:VideoPlayerInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_VIDEO_PLAYER_INDEX_MAP).get(eventData.viewTag);
            videoPlayInfo.controller.pause();
            videoPlayInfo.isPlay = false;
            break;
        }
        case "stop": {
            let videoPlayInfo:VideoPlayerInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_VIDEO_PLAYER_INDEX_MAP).get(eventData.viewTag);
            videoPlayInfo.controller.stop();
            videoPlayInfo.isPlay = false;
            break;
        }
        case "setURL": {
            let videoPlayInfo:VideoPlayerInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_VIDEO_PLAYER_INDEX_MAP).get(eventData.viewTag);
            if(eventData.isUrl == 0) {
                videoPlayInfo.isUrl = false;
                videoPlayInfo.rawfile = $rawfile(eventData.url);
            } else {
                videoPlayInfo.isUrl = true;
                videoPlayInfo.url = eventData.url;
            }
            break;
        }
        case "setLooping": {
            let videoPlayInfo: VideoPlayerInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_VIDEO_PLAYER_INDEX_MAP).get(eventData.viewTag);
            videoPlayInfo.isLoop = eventData.isLoop;
            break;
        }
        case "setVideoPlayerRect": {
            let videoPlayInfo:VideoPlayerInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_VIDEO_PLAYER_INDEX_MAP).get(eventData.viewTag);
            try {
                videoPlayInfo.x = px2vp(eventData.viewRect.x);
                videoPlayInfo.y = px2vp(eventData.viewRect.y);
                videoPlayInfo.w = px2vp(eventData.viewRect.w);
                videoPlayInfo.h = px2vp(eventData.viewRect.h);
            } catch (error) {
                let e: BusinessError = error as BusinessError;
                log.error('videoPlayerInfo  ErrorCode: %{public}d,  Message: %{public}s', e.code, e.message);
            }
            break;
        }
        case "setVisible": {
            let videoPlayInfo:VideoPlayerInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_VIDEO_PLAYER_INDEX_MAP).get(eventData.viewTag);
            if (videoPlayInfo.visible == eventData.visible) {
                return;
            }
            videoPlayInfo.visible = eventData.visible;
            break;
        }
        case "requestFullscreen": {
            let videoPlayInfo: VideoPlayerInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_VIDEO_PLAYER_INDEX_MAP).get(eventData.viewTag);
            videoPlayInfo.controller.requestFullscreen(eventData.isFullScreen);
            videoPlayInfo.isFullScreen = eventData.isFullScreen;
            break;
        }
        case "seekTo": {
            let videoPlayInfo: VideoPlayerInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_VIDEO_PLAYER_INDEX_MAP).get(eventData.viewTag);
            videoPlayInfo.controller.setCurrentTime(eventData.seekTo, SeekMode.Accurate);
            break;
        }
        case "setKeepAspectRatioEnabled": {
            let videoPlayInfo: VideoPlayerInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_VIDEO_PLAYER_INDEX_MAP).get(eventData.viewTag);
            videoPlayInfo.objectFit = eventData.keepAspectRatioEnabled? ImageFit.Cover : ImageFit.Auto;
            break;
        }
    }
}