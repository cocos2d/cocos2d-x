import type { ThreadWorkerGlobalScope } from '@ohos.worker';
import { JumpMsgEntity } from '../../entity/WorkerMsgEntity';

export class JumpManager {

    static MODULE_NAME: string = 'JumpManager';

    private static workerPort: ThreadWorkerGlobalScope;

    static init(workerPort: ThreadWorkerGlobalScope) : void {
        JumpManager.workerPort = workerPort;
    }

    static openUrl(url: string) : void {
        let jumpMsgEntity: JumpMsgEntity = new JumpMsgEntity(JumpManager.MODULE_NAME, 'openUrl');
        jumpMsgEntity.url = url;
        JumpManager.workerPort.postMessage(jumpMsgEntity);
    }
}
