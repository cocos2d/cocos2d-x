import Logger from '../utils/Logger'

let log: Logger = new Logger(0x0001, "SDKManager");

export class LoginSDK {
  static MODULE_NAME: string = 'LoginSDK';
  private static parentPort;

  static init(parentPort) {
    LoginSDK.parentPort = parentPort;
  }

  static authorization(): string {
    LoginSDK.parentPort.postMessage({
      'module': LoginSDK.MODULE_NAME, 'function': 'authorization', 'viewTag': "1111"
    });
    return "";
  }
  static loginInit(): string {
    LoginSDK.parentPort.postMessage({
      'module': LoginSDK.MODULE_NAME, 'function': 'loginInit', 'viewTag': "1111"
    });
    return "";
  }
  static getPlayerInfo(): string {
    LoginSDK.parentPort.postMessage({
      'module': LoginSDK.MODULE_NAME, 'function': 'getPlayerInfo', 'viewTag': "1111"
    });
    return "";
  }
  static reportPlayerInfo(): string {
    LoginSDK.parentPort.postMessage({
      'module': LoginSDK.MODULE_NAME, 'function': 'reportPlayerInfo', 'viewTag': "1111"
    });
    return "";
  }
}
export class PaySDK {
  static MODULE_NAME: string = 'PaySDK';
  private static parentPort;

  static init(parentPort) {
    PaySDK.parentPort = parentPort;
  }

  static checkPayEnv(): string {
    PaySDK.parentPort.postMessage({
      'module': PaySDK.MODULE_NAME, 'function': 'checkPayEnv', 'viewTag': "1111"
    });
    return "";
  }
  static queryConsumProdts(): string {
    PaySDK.parentPort.postMessage({
      'module': PaySDK.MODULE_NAME, 'function': 'queryConsumProdts', 'viewTag': "1111"
    });
    return "";
  }
  static buy(): string {
    PaySDK.parentPort.postMessage({
      'module': PaySDK.MODULE_NAME, 'function': 'buy', 'viewTag': "1111"
    });
    return "";
  }
  static consume(): string {
    PaySDK.parentPort.postMessage({
      'module': PaySDK.MODULE_NAME, 'function': 'consume', 'viewTag': "1111"
    });
    return "";
  }
  static queryNoConsumableGoods(): string {
    PaySDK.parentPort.postMessage({
      'module': PaySDK.MODULE_NAME, 'function': 'queryNoConsumableGoods', 'viewTag': "1111"
    });
    return "";
  }
  static purchaseOfNonConsumableGoods(): string {
    PaySDK.parentPort.postMessage({
      'module': PaySDK.MODULE_NAME, 'function': 'purchaseOfNonConsumableGoods', 'viewTag': "1111"
    });
    return "";
  }
  static disposableGoodsOrderQuery(): string {
    PaySDK.parentPort.postMessage({
      'module': PaySDK.MODULE_NAME, 'function': 'disposableGoodsOrderQuery', 'viewTag': "1111"
    });
    return "";
  }
  static nonConsumableProductsRecords(): string {
    PaySDK.parentPort.postMessage({
      'module': PaySDK.MODULE_NAME, 'function': 'nonConsumableProductsRecords', 'viewTag': "1111"
    });
    return "";
  }
  static consumableProductsRecords(): string {
    PaySDK.parentPort.postMessage({
      'module': PaySDK.MODULE_NAME, 'function': 'consumableProductsRecords', 'viewTag': "1111"
    });
    return "";
  }
}