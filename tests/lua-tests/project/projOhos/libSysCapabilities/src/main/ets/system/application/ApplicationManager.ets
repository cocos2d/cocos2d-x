import bundleManager from '@ohos.bundle.bundleManager';
import type { ThreadWorkerGlobalScope } from '@ohos.worker';
import { BaseWorkerMsgEntity } from '../../entity/WorkerMsgEntity';
import { common } from '@kit.AbilityKit';
import { BusinessError } from '@kit.BasicServicesKit';
import { GlobalContext, GlobalContextConstants } from '../../common/GlobalContext';

export class ApplicationManager {
    static MODULE_NAME: string = 'ApplicationManager';

    private static workerPort: ThreadWorkerGlobalScope;

    static init(workerPort: ThreadWorkerGlobalScope): void {
        ApplicationManager.workerPort = workerPort;
    }

    static exit(): void {
        let workerMsg: BaseWorkerMsgEntity = new BaseWorkerMsgEntity(ApplicationManager.MODULE_NAME, 'exit');
        ApplicationManager.workerPort.postMessage(workerMsg);
    }

    static getVersionName(): string {
        let bundleFlags = bundleManager.BundleFlag.GET_BUNDLE_INFO_DEFAULT;
        return bundleManager.getBundleInfoForSelfSync(bundleFlags).versionName;
    }
}

export function handleApplicationMsg(eventData: BaseWorkerMsgEntity): void {
    switch (eventData.function) {
        case "exit":
            terminateSelf();
            break;
        default:
            console.error('%{public}s has not implement yet', eventData.function);
    }
}

function terminateSelf(): void {
    try {
        let context: common.UIAbilityContext =
            GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_ABILITY_CONTEXT);
        context.terminateSelf((err: BusinessError) => {
            if (err.code) {
                console.error(`terminateSelf failed, code is ${err.code}, message is ${err.message}`);
                return;
            }
            console.info('terminateSelf succeed');
        });
    } catch (err) {
        let code = (err as BusinessError).code;
        let message = (err as BusinessError).message;
        console.error(`terminateSelf failed, code is ${code}, message is ${message}`);
    }
}

