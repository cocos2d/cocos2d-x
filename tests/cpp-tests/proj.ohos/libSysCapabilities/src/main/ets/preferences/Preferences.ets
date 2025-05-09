import Logger from '../utils/Logger';
import data_preferences from '@ohos.data.preferences';
import { BusinessError } from '@ohos.base';
import common from '@ohos.app.ability.common';
import { GlobalContext, GlobalContextConstants } from '../common/GlobalContext';

let log: Logger = new Logger(0x0001, "Preferences");
let preferences: data_preferences.Preferences;
const PREFS_NAME: string = "Cocos2dxPreferences";

export default class Preferences {

  static getPreferences(): void {
    let context: common.UIAbilityContext = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_ABILITY_CONTEXT);
    try {
      preferences = data_preferences.getPreferencesSync(context, {name: PREFS_NAME});
      log.info("Succeeded in getting preferences.");
    } catch (err) {
      let code = (err as BusinessError).code;
      let message = (err as BusinessError).message;
      log.error("Failed to get preferences. code =" + code + ", message =" + message);
    }
  }

  static deletePreferences(): void {
    let context: common.UIAbilityContext = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_ABILITY_CONTEXT);
    try {
      data_preferences.deletePreferences(context, PREFS_NAME).then(() => {
        log.info("Succeeded in deleting preferences.");
      });
    } catch (err) {
      let code = (err as BusinessError).code;
      let message = (err as BusinessError).message;
      log.error("Failed to delete preferences. code =" + code + ", message =" + message);
    }
  }

  static removePreferencesFromCache(): void {
    let context: common.UIAbilityContext = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_ABILITY_CONTEXT);
    try {
      data_preferences.removePreferencesFromCacheSync(context, PREFS_NAME);
      log.info("Succeeded in removing preferences.");
    } catch (err) {
      let code = (err as BusinessError).code;
      let message = (err as BusinessError).message;
      log.error("Failed to remove preferences. code =" + code + ", message =" + message);
    }
  }

  static get(key: string, defValue: data_preferences.ValueType): data_preferences.ValueType {
    if (preferences === null) {
      Preferences.getPreferences();
    }
    try {
      let data = preferences.getSync(key, defValue);
      log.info("Succeeded in getting value of 'startup'. Data: " + data);
      return data;
    } catch (err) {
      let code = (err as BusinessError).code;
      let message = (err as BusinessError).message;
      log.error("Failed to get value of 'startup'. code =" + code + ", message =" + message);
      return defValue;
    }
  }

  static put(key: string, value: data_preferences.ValueType): void {
    if (preferences === null) {
      Preferences.getPreferences();
    }
    try {
      preferences.putSync(key, value);
      log.info("Succeeded in put the key.");
      Preferences.flush();
    } catch (err) {
      let code = (err as BusinessError).code;
      let message = (err as BusinessError).message;
      log.error("Failed to put. code =" + code + ", message =" + message);
    }
  }

  static getAll(): string | undefined {
    if (preferences === null) {
      Preferences.getPreferences();
    }
    try {
      let object = preferences.getAllSync();
      let allKeys = getObjKeys(object);
      log.info('getAll keys = ' + allKeys);
      log.info("getAll object = " + JSON.stringify(object));
      return JSON.stringify(object);
    } catch (err) {
      let code = (err as BusinessError).code;
      let message = (err as BusinessError).message;
      log.error("Failed to getAll. code =" + code + ", message =" + message);
      return undefined;
    }
  }

  static has(key: string): boolean {
    if (preferences === null) {
      Preferences.getPreferences();
    }
    try {
      let val = preferences.hasSync(key);
      if (val) {
        log.info("The key 'startup' is contained.");
        return true;
      } else {
        log.info("The key 'startup' dose not contain.");
        return false;
      }
    } catch (err) {
      let code = (err as BusinessError).code;
      let message = (err as BusinessError).message;
      log.error("Failed to has. code =" + code + ", message =" + message);
      return false;
    }
  }

  static delete(key: string): void {
    if (preferences === null) {
      Preferences.getPreferences();
    }
    try {
      preferences.deleteSync(key);
      log.info("Succeeded in deleting the key.");
      Preferences.flush();
    } catch (err) {
      let code = (err as BusinessError).code;
      let message = (err as BusinessError).message;
      log.error("Failed to delete. code =" + code + ", message =" + message);
    }
  }

  static flush(): void {
    if (preferences === null) {
      Preferences.getPreferences();
    }
    preferences.flush().then(()=>{
      log.info("Succeeded in flushing.");
    });
  }

  static clear(): void {
    if (preferences === null) {
      Preferences.getPreferences();
    }
    try {
      preferences.clearSync();
      log.info("Succeeded in clearing.");
    } catch (err) {
      let code = (err as BusinessError).code;
      let message = (err as BusinessError).message;
      log.error("Failed to clear. code =" + code + ", message =" + message);
    }
  }


  static onChange(cb: Function): void {
    if (preferences === null) {
      Preferences.getPreferences();
    }
    try {
      preferences.on('change', (key: string) => {
        log.info("The key " + key + " changed.");
        cb(key);
      });
    } catch (err) {
      let code = (err as BusinessError).code;
      let message = (err as BusinessError).message;
      log.error("Failed to flush. code =" + code + ", message =" + message);
    }
  }

  static offChange(cb: Function): void {
    if (preferences === null) {
      Preferences.getPreferences();
    }
    try {
      preferences.off('change', (key: string) => {
        log.info("The key " + key + " changed.");
        cb(key);
      });
    } catch (err) {
      let code = (err as BusinessError).code;
      let message = (err as BusinessError).message;
      log.error("Failed to flush. code =" + code + ", message =" + message);
    }
  }
}

function getObjKeys(obj: Object): string[] {
  let keys = Object.keys(obj);
  return keys;
}
