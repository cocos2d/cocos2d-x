import { LoginSDK } from '../sdk/SDKManager'
import { PaySDK } from '../sdk/SDKManager'

export class SDKNapiHelper {

    static registerFunctions(registerFunc : Function) {
        SDKNapiHelper.registerLoginSDK(registerFunc);
        SDKNapiHelper.registerPaySDK(registerFunc);
    }

    private static registerLoginSDK(registerFunc : Function) {
      registerFunc('LoginSDK.authorization', LoginSDK.authorization);
      registerFunc('LoginSDK.loginInit', LoginSDK.loginInit);
      registerFunc('LoginSDK.getPlayerInfo', LoginSDK.getPlayerInfo);
      registerFunc('LoginSDK.reportPlayerInfo', LoginSDK.reportPlayerInfo);
    }
    private static registerPaySDK(registerFunc : Function) {
      registerFunc('PaySDK.checkPayEnv', PaySDK.checkPayEnv);
      registerFunc('PaySDK.queryConsumProdts', PaySDK.queryConsumProdts);
      registerFunc('PaySDK.buy', PaySDK.buy);
      registerFunc('PaySDK.consume', PaySDK.consume);
      registerFunc('PaySDK.queryNoConsumableGoods', PaySDK.queryNoConsumableGoods);
      registerFunc('PaySDK.purchaseOfNonConsumableGoods', PaySDK.purchaseOfNonConsumableGoods);
      registerFunc('PaySDK.disposableGoodsOrderQuery', PaySDK.disposableGoodsOrderQuery);
      registerFunc('PaySDK.nonConsumableProductsRecords', PaySDK.nonConsumableProductsRecords);
      registerFunc('PaySDK.consumableProductsRecords', PaySDK.consumableProductsRecords);
    }
}