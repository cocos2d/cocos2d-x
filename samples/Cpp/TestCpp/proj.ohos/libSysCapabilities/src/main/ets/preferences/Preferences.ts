import Logger from '../utils/Logger';
import data_preferences from '@ohos.data.preferences';
import { BusinessError } from '@ohos.base';
import common from '@ohos.app.ability.common';
import { GlobalContext, GlobalContextConstants } from '../common/GlobalContext';

let log: Logger = new Logger(0x0001, "Preferences");
let preferences: data_preferences.Preferences | null = null;
const PREFS_NAME: string = "Cocos2dxPreferences";

export default class Preferences {

  // Get Preferences instance through preferencesName
  static getPreferences(): data_preferences.Preferences {
    let context: common.UIAbilityContext = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_ABILITY_CONTEXT);
    try {
      preferences = data_preferences.getPreferencesSync(context, {name: PREFS_NAME});
      log.info("Succeeded in getting preferences.");
    } catch (err) {
      let code = (err as BusinessError).code;
      let message = (err as BusinessError).message;
      log.error("Failed to get preferences. code =" + code + ", message =" + message);
    }
    return preferences;
  }

  /*
   * Retrieve the specified Preferences instance from the cache using preferencesName, and if the Preferences instance has a corresponding persistent file, delete its persistent file at the same time. Use Promise asynchronous callbacks.
   * After calling this interface, it is not recommended to use the old Preferences instance for data operations, otherwise data consistency issues may occur. The Preferences instance should be set to null, and the system will uniformly recycle it.
  */
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

  /*
   * Retrieve the specified Preferences instance from the cache using preferencesName and use Promise asynchronous callback.
   * After the application first calls the getPreferences interface to obtain a Preferences instance, the instance will be cached and will not be read from the persistent file again when getPreferences is retrieved later,
   * Retrieve the Preferences instance directly from the cache. After calling this interface to remove the instance from the cache, getPreferences will re read the persistent file and generate a new Preferences instance.
   * After calling this interface, it is not recommended to use the old Preferences instance for data operations, otherwise data consistency issues may occur. The Preferences instance should be set to null, and the system will uniformly recycle it.
  */
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

  // Retrieve the value corresponding to the key from the cached Preferences instance. If the value is null or of a non default type, return the default data defValue
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

  // Write data to the cached Preferences instance, which can be persisted through flushing
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

  // Retrieve all key value data from the cached Preferences instance.
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

  // Check if the cached Preferences instance contains a stored key value pair named the given Key
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

  // Deleting the stored key value pair named the given Key from the cached Preferences instance can be persisted by flushing the Preferences instance
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

  // Asynchronous storage of data from cached Preferences instances to persistent files of user preferences, using Promise asynchronous callbacks.
  static flush(): void {
    if (preferences === null) {
      Preferences.getPreferences();
    }
    preferences.flush().then(()=>{
      log.info("Succeeded in flushing.");
    });
  }

  // Clearing all data from cached Preferences instances can be achieved by persistently flushing the Preferences instance and using Promise asynchronous callbacks.
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


  // After the subscription data changes and the value of the subscription key changes, a callback is triggered after executing the flush method.
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

  // Unsubscribe from data changes.
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

// Due to the absence of Object. keys in ArkTS and the inability to use for in...
//If ArkTS issues are reported, please separate this method into a TS file and expose it, and introduce it into the ETS file that needs to be used
function getObjKeys(obj: Object): string[] {
  let keys = Object.keys(obj);
  return keys;
}
