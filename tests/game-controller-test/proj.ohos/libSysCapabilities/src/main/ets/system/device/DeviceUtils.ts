import display from '@ohos.display'
import batteryInfo from "@ohos.batteryInfo";
import i18n from '@ohos.i18n';
import vibrator from '@ohos.vibrator';
import Logger from '../../utils/Logger';
import window from '@ohos.window';
import { GlobalContext, GlobalContextConstants } from '../../common/GlobalContext';

let log = new Logger(0x0001, "DeviceUtils");

export class DeviceUtils {
  static MODULE_NAME: string = 'DeviceUtils';

  private static parentPort;

  static init(parentPort) {
    DeviceUtils.parentPort = parentPort;
  }

  static getDpi(): number {
    return display.getDefaultDisplaySync().densityDPI;
  }

  static getBatterySOC(): number {
    return batteryInfo.batterySOC
  }

  static getSystemLanguage(): string {
    return i18n.System.getSystemLanguage();
  }

  static setWindowPrivacyMode(isPrivacyMode: boolean): void {
    DeviceUtils.parentPort.postMessage({
      'module': DeviceUtils.MODULE_NAME, 'function': 'setWindowPrivacyMode', 'isPrivacyMode': isPrivacyMode
    });
  }

  static startVibration(time: number) {
    try {
      vibrator.startVibration({
        type: 'time',
        duration: time * 1000, // 秒转毫秒
      }, {
        id: 0,
        usage: 'unknown'
      }, (error) => {
        if (error) {
          log.error('vibrate fail, error.code: %{public}d, error.message: %{public}s', error.code, error.message);
          return;
        }
      });
    } catch (err) {
      log.error('error.code: %{public}d, error.message: %{public}s', err.code, err.message);
    }
  }

  static setKeepScreenOn(value: boolean) {
    let windowClass = null;
    try {
      window.getLastWindow(GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_ABILITY_CONTEXT), (err, data) => { //获取窗口实例
        if (err.code) {
          log.error('Failed to obtain last window when setKeepScreenOn. Cause:%{public}s', JSON.stringify(err));
          return;
        }
        windowClass = data;
        // 设置屏幕是否为常亮状态
        let keepScreenOnPromise = windowClass.setWindowKeepScreenOn(value);
        Promise.all([keepScreenOnPromise]).then(() => {
          log.info('Succeeded in setKeepScreenOn, value:%{public}s', value);
        }).catch((err) => {
          log.error('Failed to setKeepScreenOn, cause:%{public}s', JSON.stringify(err));
        });
      });
    } catch (exception) {
      log.error('Failed to get or set the window when setKeepScreenOn, cause:%{public}s', JSON.stringify(exception));
    }
  }
}