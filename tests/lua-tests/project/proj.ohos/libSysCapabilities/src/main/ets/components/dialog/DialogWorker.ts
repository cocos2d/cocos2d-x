import type { ThreadWorkerGlobalScope } from '@ohos.worker';
import { DialogMsgEntity } from '../../entity/WorkerMsgEntity';

export class Dialog {
    static MODULE_NAME : string = 'Dialog';
    static workerPort;

    static init(workerPort: ThreadWorkerGlobalScope) : void {
        Dialog.workerPort = workerPort;
    }

    static showDialog(message: string, title: string) : void {
        let dialogMsgEntity: DialogMsgEntity = new DialogMsgEntity(Dialog.MODULE_NAME, 'showDialog');
        dialogMsgEntity.title = title;
        dialogMsgEntity.message = message;
        Dialog.workerPort.postMessage(dialogMsgEntity);
    }

    static showTextInputDialog(message: string) : void {
        let dialogMsgEntity: DialogMsgEntity = new DialogMsgEntity(Dialog.MODULE_NAME, 'showTextInputDialog');
        dialogMsgEntity.message = message;
        Dialog.workerPort.postMessage(dialogMsgEntity);
    }

    static hideTextInputDialog() : void {
        let dialogMsgEntity: DialogMsgEntity = new DialogMsgEntity(Dialog.MODULE_NAME, 'hideTextInputDialog');
        Dialog.workerPort.postMessage(dialogMsgEntity);
    }
}
