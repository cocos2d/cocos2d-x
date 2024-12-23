import type common from '@ohos.app.ability.common';
import { GlobalContext, GlobalContextConstants } from '../../common/GlobalContext';
import {Result} from "../../entity/Result"
import type { JumpMsgEntity } from '../../entity/WorkerMsgEntity';
import Logger from '../../utils/Logger'

let log: Logger = new Logger(0x0001, "JumpManagerMsg");

export function handleJumpManagerMsg(eventData: JumpMsgEntity) : void {
    switch (eventData.function) {
        case "openUrl":
            openUrl(eventData.url);
            break;
        default:
            log.error('%{public}s has not implement yet', eventData.function);
    }
}

function openUrl(url: string): void {
    let context: common.UIAbilityContext = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_ABILITY_CONTEXT);
    let wantInfo = {
        'action': 'ohos.want.action.viewData',
        'entities': ['entity.system.browsable'],
        'uri': url
    }
    context.startAbility(wantInfo).then(() => {
        log.info('%{public}s',  JSON.stringify(Result.success({})));
    }).catch((err) => {
        log.error('openUrl : err : %{public}s', JSON.stringify(Result.error(-1, JSON.stringify(err))) ?? '');
    });
}