import window from '@ohos.window';
import Logger from '../../utils/Logger'
import { BusinessError } from '@ohos.base';
import { DeviceUtilsMsgEntity } from '../../entity/WorkerMsgEntity';
import { GlobalContext, GlobalContextConstants } from '../../common/GlobalContext';

let log: Logger = new Logger(0x0001, "DeviceUtilsMsg");

export default function handleDeviceUtilsMsg(eventData: DeviceUtilsMsgEntity) {

  switch (eventData.function) {
    case "setWindowPrivacyMode":
      setWindowPrivacyMode(eventData.isPrivacyMode);
      break;
  }
}

function setWindowPrivacyMode(isPrivacyMode: boolean): void {
  try {
    window.getLastWindow(GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_ABILITY_CONTEXT), (err, data:window.Window) => {
      if (err.code) {
        log.error('Failed to getLastWindow : err : %{public}s', JSON.stringify(err));
        return;
      }
     let windowClass:window.Window= data;
      //todo:支持回调，比如设置弹窗根据游戏自己实现
      let promise = windowClass.setWindowPrivacyMode(isPrivacyMode);
      promise.then(() => {
        log.info('setWindowPrivacyMode success ');
      }).catch((err:BusinessError) => {
        log.error('Failed to setWindowPrivacyMode : err : %{public}s', JSON.stringify(err));
      });
    });
  } catch (exception) {
    log.error('Failed to obtain the top window. Cause: ' + JSON.stringify(exception));
  }
}