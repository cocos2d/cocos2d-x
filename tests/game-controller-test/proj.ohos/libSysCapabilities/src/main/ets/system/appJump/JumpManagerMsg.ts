import type common from '@ohos.app.ability.common';
import { GlobalContext, GlobalContextConstants } from '../../common/GlobalContext';
import {Result} from "../../entity/Result"
import type { JumpMsgEntity } from '../../entity/WorkerMsgEntity';
import Logger from '../../utils/Logger'
import { openImagePicker } from './ImagePicker'

let log: Logger = new Logger(0x0001, "JumpManagerMsg");

export function handleJumpManagerMsg(eventData: JumpMsgEntity) : void {
    switch (eventData.function) {
        case "openApp":
            openApp(eventData.targetBundleName, eventData.targetAbilityName);
            break;
        case "openAppInAppMarket":
            openAppInAppMarket(eventData.appId); 
            break;
        case "openUrl":
            openUrl(eventData.url);
            break;
        case "openImagePicker":
            openImagePicker(eventData.pWidth, eventData.pHeight);
            break;
        default:
            log.error('%{public}s has not implement yet', eventData.function);
    }
}

function openApp(targetBundleName: string, targetAbilityName: string): void {
    let context: common.UIAbilityContext = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_ABILITY_CONTEXT);
    let wantInfo = {
        'bundleName': targetBundleName,
        'abilityName': targetAbilityName
    }
    context.startAbility(wantInfo).then(() => {
        log.info('%{public}s',  JSON.stringify(Result.success({})));
    }).catch((err) => {
        log.error('openApp : err : %{public}s', JSON.stringify(Result.error(-1, JSON.stringify(err))) ?? '');
    });
}

function openAppInAppMarket(appId: string): void {
    let context: common.UIAbilityContext = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_ABILITY_CONTEXT);
    let wantInfo = {
        action: 'ohos.want.action.appdetail',
        uri: 'store://appgallery.huawei.com',
        type: 'text/text',
        parameters: {
            id: appId // 要拉起的详情页面应用的appId
        }
    }
    context.startAbility(wantInfo).then(() => {
        log.info('%{public}s',  JSON.stringify(Result.success({})));
    }).catch((err) => {
        log.error('openAppInAppMarket : err : %{public}s', JSON.stringify(Result.error(-1, JSON.stringify(err))) ?? '');
    });
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