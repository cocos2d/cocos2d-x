import worker, { MessageEvents } from '@ohos.worker';
import Logger from './Logger';
import { handleEditBoxMsg } from '../components/editbox/EditBoxMsg'
import { handleWebViewMsg } from '../components/webview/WebViewMsg'
import { handleVideoPlayMsg } from '../components/videoplayer/VideoPlayerMsg'
import { handleDialogMsg } from '../components/dialog/DialogMsg'
import { handleJumpManagerMsg } from '../system/appJump/JumpManagerMsg'
import { handleApplicationMsg } from '../system/application/ApplicationManager'
import { BaseWorkerMsgEntity, DialogMsgEntity, EditBoxMsgEntity, JumpMsgEntity, VideoPlayMsgEntity, WebViewMsgEntity } from '../entity/WorkerMsgEntity';

export class WorkerMsgUtils {
    static workPort = worker.workerPort;
    static log : Logger = new Logger(0x0001, 'WorkerMsgUtils')

    static async recvWorkerThreadMessage(event: MessageEvents) {
        let eventData: BaseWorkerMsgEntity = event.data;
        WorkerMsgUtils.log.debug('mainThread receiveMsg, module:%{public}s, function:%{public}s', eventData.module, eventData.function);

        switch (eventData.module) {
            case 'EditBox':
                handleEditBoxMsg(eventData as EditBoxMsgEntity);
                break;
            case "Dialog":
                handleDialogMsg(eventData as DialogMsgEntity);
                break;           
            case 'WebView':
                handleWebViewMsg(eventData as WebViewMsgEntity);
                break;
            case 'VideoPlay':
                handleVideoPlayMsg(eventData as VideoPlayMsgEntity);
                break;
            case 'JumpManager':
                handleJumpManagerMsg(eventData as JumpMsgEntity);
                break;
            case 'ApplicationManager':
                handleApplicationMsg(eventData as BaseWorkerMsgEntity);
                break;
            default:
                WorkerMsgUtils.log.error('%{public}s has not implement yet', eventData.module);
        }
    } 
}
