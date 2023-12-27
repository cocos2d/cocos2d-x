import type { ThreadWorkerGlobalScope } from '@ohos.worker';
import { JumpMsgEntity } from '../../entity/WorkerMsgEntity';

export class JumpManager {

    static MODULE_NAME: string = 'JumpManager';

    private static workerPort: ThreadWorkerGlobalScope;

    static init(parentPort: ThreadWorkerGlobalScope) : void {
        JumpManager.workerPort = parentPort;
    }

    static openApp(targetBundleName: string, targetAbilityName: string) : void {
        let jumpMsgEntity: JumpMsgEntity = new JumpMsgEntity(JumpManager.MODULE_NAME, 'openApp');
        jumpMsgEntity.targetBundleName = targetBundleName;
        jumpMsgEntity.targetAbilityName = targetAbilityName;
        JumpManager.workerPort.postMessage(jumpMsgEntity);
    }

    static openAppInAppMarket(appId: string) : void {
        let jumpMsgEntity: JumpMsgEntity = new JumpMsgEntity(JumpManager.MODULE_NAME, 'openAppInAppMarket');
        jumpMsgEntity.appId = appId;
        JumpManager.workerPort.postMessage(jumpMsgEntity);
    }

    static openUrl(url: string) : void {
        let jumpMsgEntity: JumpMsgEntity = new JumpMsgEntity(JumpManager.MODULE_NAME, 'openUrl');
        jumpMsgEntity.url = url;
        JumpManager.workerPort.postMessage(jumpMsgEntity);
    }

    static openImagePicker(pWidth: number, pHeight: number) : void {
        let jumpMsgEntity: JumpMsgEntity = new JumpMsgEntity(JumpManager.MODULE_NAME, 'openImagePicker');
        jumpMsgEntity.pWidth = pWidth;
        jumpMsgEntity.pHeight = pHeight;
        JumpManager.workerPort.postMessage(jumpMsgEntity);
    }
}
