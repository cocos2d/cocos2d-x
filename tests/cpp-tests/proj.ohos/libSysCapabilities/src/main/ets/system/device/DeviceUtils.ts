import display from '@ohos.display'
import i18n from '@ohos.i18n';
import vibrator from '@ohos.vibrator';
import Logger from '../../utils/Logger';
import window from '@ohos.window';
import { GlobalContext, GlobalContextConstants } from '../../common/GlobalContext';
import { Rect } from '@ohos.application.AccessibilityExtensionAbility';

let log = new Logger(0x0001, "DeviceUtils");

export class DeviceUtils {
  static MODULE_NAME: string = 'DeviceUtils';
  static _roundScreen: boolean = false;
  static _hasSoftKeys: boolean = false;
  static _isCutoutEnable: boolean = false;
  static _cutoutLeft: number;
  static _cutoutWidth: number;
  static _cutoutTop: number;
  static _cutoutHeight: number;

  static getDpi(): number {
    return display.getDefaultDisplaySync().densityDPI;
  }

  static getSystemLanguage(): string {
    return i18n.System.getSystemLanguage();
  }

  static startVibration(time: number) {
    try {
      vibrator.startVibration({
        type: 'time',
        duration: time * 1000, // Seconds to milliseconds
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
        // Sets whether the screen is always on.
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

  static isRoundScreen() : boolean {
    return DeviceUtils._roundScreen;
  }

  static hasSoftKeys() : boolean {
    return DeviceUtils._hasSoftKeys;
  }

  static isCutoutEnable() : boolean {
    return DeviceUtils._isCutoutEnable;
  }

  static initScreenInfo() : void {
    let windowClass = null;
    try {
      window.getLastWindow(GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_ABILITY_CONTEXT), (err, data) => {
        if (err.code) {
          log.error('Failed to obtain last window when initScreenInfo. Cause:%{public}s', JSON.stringify(err));
          return;
        }

        windowClass = data;
        let windowProperties: window.WindowProperties = windowClass.getWindowProperties();
        DeviceUtils._roundScreen = windowProperties.isRoundCorner;
        let rect: Rect = windowProperties.windowRect;
        if(rect.top + rect.height < display.getDefaultDisplaySync().height) {
          DeviceUtils._hasSoftKeys = true;
        } else {
          DeviceUtils._hasSoftKeys = false;
        }
      });
    } catch (exception) {
      log.error('Failed to get or set the window when initScreenInfo, cause:%{public}s', JSON.stringify(exception));
    }

    display.getDefaultDisplaySync().getCutoutInfo().then((data) => {
      if(data.boundingRects.length == 0) {
        DeviceUtils._isCutoutEnable = false;
        return;
      }

      DeviceUtils._isCutoutEnable = true;
      DeviceUtils._cutoutLeft = data.boundingRects[0].left;
      DeviceUtils._cutoutTop = data.boundingRects[0].top;
      DeviceUtils._cutoutWidth = data.boundingRects[0].width;
      DeviceUtils._cutoutHeight = data.boundingRects[0].height;
    }).catch((err) => {
      log.error('Failed to obtain all the display objects. Code: ' + JSON.stringify(err));
    });
  }

  static getOrientation() : number {
    let orientation: display.Orientation = display.getDefaultDisplaySync().orientation;

    // If the system enumeration value changes, the processing logic in the C++ code needs to be changed. Therefore, the mapping is performed again.
    if(orientation == display.Orientation.PORTRAIT) {
      return 0;
    }

    if(orientation == display.Orientation.LANDSCAPE) {
      return 1;
    }

    if(orientation == display.Orientation.PORTRAIT_INVERTED) {
      return 2;
    }

    if(orientation == display.Orientation.LANDSCAPE_INVERTED) {
      return 3;
    }

    return 4;
  }

  static getCutoutHeight() : number {
    if(DeviceUtils._cutoutHeight) {
      let height = DeviceUtils._cutoutTop + DeviceUtils._cutoutHeight;
      return height;
    }
    return 0;
  }

  static getCutoutWidth() : number {
    if(!DeviceUtils._cutoutWidth) {
      return 0;
    }

    let disPlayWidth = display.getDefaultDisplaySync().width;
    if(DeviceUtils._cutoutLeft + DeviceUtils._cutoutWidth > disPlayWidth - DeviceUtils._cutoutLeft) {
      return disPlayWidth - DeviceUtils._cutoutLeft;
    }

    return DeviceUtils._cutoutLeft + DeviceUtils._cutoutWidth;
  }
}