import Logger from '../utils/Logger';
import data_preferences from '@ohos.data.preferences';
import { BusinessError } from '@ohos.base';
import common from '@ohos.app.ability.common';
import { GlobalContext, GlobalContextConstants } from '../common/GlobalContext';

let log: Logger = new Logger(0x0001, "Preferences");
let preferences: data_preferences.Preferences | null = null;
const PREFS_NAME: string = "Cocos2dxPreferences";

export default class Preferences {

  // 通过 preferencesName 获取Preferences实例
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
  通过 preferencesName 从缓存中移出指定的Preferences实例，若Preferences实例有对应的持久化文件，则同时删除其持久化文件。使用Promise异步回调。
  调用该接口后，不建议再使用旧的Preferences实例进行数据操作，否则会出现数据一致性问题，应将Preferences实例置为null，系统将会统一回收。
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
  通过 preferencesName 从缓存中移出指定的Preferences实例，使用Promise异步回调。
  应用首次调用getPreferences接口获取某个Preferences实例后，该实例会被会被缓存起来，后续再次getPreferences时不会再次从持久化文件中读取，
  直接从缓存中获取Preferences实例。调用此接口移出缓存中的实例之后，再次getPreferences将会重新读取持久化文件，生成新的Preferences实例。
  调用该接口后，不建议再使用旧的Preferences实例进行数据操作，否则会出现数据一致性问题，应将Preferences实例置为null，系统将会统一回收。
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

  // 从缓存的Preferences实例中获取键对应的值，如果值为null或者非默认值类型，返回默认数据defValue
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

  // 将数据写入缓存的Preferences实例中，可通过flush将Preferences实例持久化
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

  // 从缓存的Preferences实例中获取所有键值数据。
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

  // 检查缓存的Preferences实例中是否包含名为给定Key的存储键值对
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

  // 从缓存的Preferences实例中删除名为给定Key的存储键值对，可通过flush将Preferences实例持久化
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

  // 将缓存的Preferences实例中的数据异步存储到用户首选项的持久化文件中，使用Promise异步回调。
  static flush(): void {
    if (preferences === null) {
      Preferences.getPreferences();
    }
    preferences.flush().then(()=>{
      log.info("Succeeded in flushing.");
    });
  }

  // 清除缓存的Preferences实例中的所有数据，可通过flush将Preferences实例持久化，使用Promise异步回调。
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


  // 订阅数据变更，订阅的Key的值发生变更后，在执行flush方法后，触发callback回调。
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

  // 取消订阅数据变更。
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

// 由于ArkTS中无Object.keys，且无法使用for..in...
// 若报ArkTS问题，请将此方法单独抽离至一个ts文件中并暴露，在需要用到的ets文件中引入使用
function getObjKeys(obj: Object): string[] {
  let keys = Object.keys(obj);
  return keys;
}