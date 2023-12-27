import authentication from '@hms.core.authentication';
import common from '@ohos.app.ability.common';

import iap from '@hms.core.iap';
import hilog from '@ohos.hilog';
import cryptoFramework from '@ohos.security.cryptoFramework';
import util from '@ohos.util';
import { GlobalContext, GlobalContextConstants } from '../common/GlobalContext';

import gamePlayer from '@hms.core.gameservice.gameplayer';

export interface EventData {
  'module': string,
  'function': string,
  'viewTag': string
}

//查询消耗商品
interface InAppPurchaseData {
  purchaseToken: string;
  purchaseState: string;
  productId: string;
  price: string;
  currency: string;
  // 其他的属性参考文档中InAppPurchaseData字段的说明，可按需解析使用
}


class SDKManagerMsg {
  purchaseTokenByQueryConsumProdts: string = "";

  async handlePullSDK(eventData: EventData): Promise<string> {
    let context: common.UIAbilityContext = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_ABILITY_CONTEXT);
    switch (eventData.function) {
    //初始化登录
      case "loginInit":
        return await this.handleLoginInit(context);
    //华为账号授权
      case "authorization":
        return await this.handleAuthorization(context);
    //获取玩家信息
      case "getPlayerInfo":
        return await this.handleGetPlayerInfo(context);
    //上报玩家信息
      case "reportPlayerInfo":
        return await this.handleReportPlayerInfo(context);
    //检查支付环境
      case "checkPayEnv":
        return await this.handleCheckPayEnv(context);
    //查询消耗商品
      case "queryConsumProdts":
        return await this.handleQueryConsumProdts(context);
    //购买
      case "buy":
        return await this.handleBuy(context);
    //消耗
      case "consume":
        return await this.handleConsume(context);
    //查询非消耗型商品
      case "queryNoConsumableGoods":
        return await this.handleQueryNoConsumableGoods(context);
    //非消耗型商品购买
      case "purchaseOfNonConsumableGoods":
        return await this.handlePurchaseOfNonConsumableGoods(context);
    //消耗型商品掉单查询
      case "disposableGoodsOrderQuery":
        return await this.handleDisposableGoodsOrderQuery(context);
    //查询非消耗型商品的购买记录
      case "nonConsumableProductsRecords":
        return await this.handleNonConsumableProductsRecords(context);
    //查询消耗型商品的购买记录
      case "consumableProductsRecords":
        return await this.handleConsumableProductsRecords(context);
      default: {
        return Promise.resolve("");
      }
    }
  }

  //初始化登录
  async handleLoginInit(context: common.UIAbilityContext): Promise<string> {
    try {
      await gamePlayer.init(context as common.UIAbilityContext);
      console.log('init success.');
      return 'init success!';
    } catch (error) {
      // 这里处理异步的参数错误和业务逻辑执行错误。
      hilog.error(0x0001, 'Login Demo', `init failed: Error: ${error}`);
      return `init failed: Error: ${JSON.stringify(error)}`;
    }
  }

  //获取玩家信息
  async handleGetPlayerInfo(context: common.UIAbilityContext): Promise<string> {
    // 获取本地玩家信息promise接口
    try {
      let result = await gamePlayer.getLocalPlayer(context);
      return 'getLocalPlayer success:' + JSON.stringify(result);
    } catch (err) {
      return 'getLocalPlayer failed:' + JSON.stringify(err, null, 4);
    }
  }

  //上报玩家信息
  async handleReportPlayerInfo(context: common.UIAbilityContext): Promise<string> {
    let request: gamePlayer.GSKPlayerRole = {
      roleId: '123',
      roleName: 'Jason',
      serverId: '456',
      serverName: 'Zhangshan',
      gamePlayerId: '789',
      teamPlayerId: '000'
    };
    try {
      await gamePlayer.savePlayerRole(context, request);
      return 'savePlayerRole success.';
    } catch (err) {
      return 'savePlayerRole failed:' + JSON.stringify(err);
    }
  }

  //华为账号授权
  handleAuthorization(context: common.UIAbilityContext): Promise<string> {
    // 调用系统SDK接口
    console.log("enter login");
    // 创建授权请求，并设置参数
    let loginRequest = new authentication.HuaweiIDProvider().createLoginWithHuaweiIDRequest();
    // 当用户未登录华为帐号时，是否强制拉起华为帐号登录界面
    loginRequest.forceLogin = true;
    loginRequest.state = 'nlqtest';
    // 创建登录回调，并处理登录结果
    return new Promise((resolve, reject) => {
      let loginCallback = (err: authentication.AuthenticationResponse, data: authentication.LoginWithHuaweiIDResponse) => {
        if (err) {
          console.log('login fail, error: %{public}s', JSON.stringify(err));
          reject('login fail, error:' + JSON.stringify(err));
          return;
        }
        let loginWithHuaweiIDResponse = data as authentication.LoginWithHuaweiIDResponse;
        let state = loginWithHuaweiIDResponse.state;
        if (loginRequest.state != state) {
          console.log('login fail,The state is different: %{public}s', JSON.stringify(loginWithHuaweiIDResponse));
          reject('login fail,The state is different:' + JSON.stringify(loginWithHuaweiIDResponse));
          return;
        }
        console.log('login success, %{public}s', JSON.stringify(loginWithHuaweiIDResponse));
        let loginWithHuaweiIDCredential = loginWithHuaweiIDResponse.data;
        let authorizationCode = loginWithHuaweiIDCredential?.authorizationCode;
        let idToken = loginWithHuaweiIDCredential?.idToken;
        let openID = loginWithHuaweiIDCredential?.openID;
        let unionID = loginWithHuaweiIDCredential?.unionID;
        console.log('authorizationCode:' + authorizationCode);
        console.log('idToken:' + idToken);
        console.log('openID:' + openID);
        console.log('unionID:' + unionID);
        // result返回子线程
        resolve(JSON.stringify(loginWithHuaweiIDCredential));
      }
      // 执行登录请求
      try {
        let controller = new authentication.AuthenticationController(context);
        controller.executeRequest(loginRequest, loginCallback);
      } catch (e) {
        console.log('login failed: %{public}s', JSON.stringify(e));
        reject('login failed:' + JSON.stringify(e, null, 4));
      }
    });
  }

  //检查支付环境
  async handleCheckPayEnv(context: common.UIAbilityContext): Promise<string> {
    try {
      await iap.queryEnvironmentStatus(context);
     return 'check pay env success!';
    } catch (error) {
      // 这里处理异步的参数错误和业务逻辑执行错误。
      hilog.error(0x0001, "Iap Demo", `Iap queryEnvironmentStatus: Error: ${JSON.stringify(error)}`);
       return `check pay env failed: Error: ${JSON.stringify(error)}`;
    }
  }

  async handleQueryConsumProdts(context: common.UIAbilityContext): Promise<string> {
    const param = {
      productType: iap.ProductType.CONSUMABLE
    } as iap.QueryPurchasesParameter;
    // 调用queryOwnedPurchases接口会获取所有已购但未发货的消耗型商品的购买信息
    try {
      // 获取成功
      let res = await iap.queryOwnedPurchases(context, param);
      if (!res.inAppPurchaseDataList.length) {
        hilog.error(0x0001, "Iap Demo", "inAppPurchaseDataList null");
        return "inAppPurchaseDataList null";
      }
      let inAppPurchaseDataStr = res.inAppPurchaseDataList[0];
      let inAppPurchaseDataSignature = res.inAppSignatureList[0];
      // 使用您应用的IAP公钥验证签名
      await this.checkSign(inAppPurchaseDataSignature, inAppPurchaseDataStr);
      hilog.info(0x0001, "Iap Demo", 'queryOwnedPurchases checkSign true')
      // 如果验签成功，为避免资金损失，必须校验InAppPurchaseData中的productId、price、currency等信息的一致性。
      // 验证一致后，确认每个商品的购买状态。确认商品已支付后，检查此前是否已发过货，未发货则进行发货操作。发货成功后执行消耗操作
      let inAppPurchaseDataObj: InAppPurchaseData = JSON.parse(res.inAppPurchaseDataList[0]);
      this.purchaseTokenByQueryConsumProdts = inAppPurchaseDataObj.purchaseToken;
      let purchaseState = inAppPurchaseDataObj.purchaseState;
      return 'purchaseTokenByQueryConsumProdts：' + this.purchaseTokenByQueryConsumProdts;
    } catch (err) {
      hilog.error(0x0001, "Iap Demo", `Iap queryOwnedPurchases: Error: ${JSON.stringify(err)}`);
      return `Iap queryOwnedPurchases: Error: ${JSON.stringify(err)}`;
    }
  }

  async handleBuy(context: common.UIAbilityContext): Promise<string> {
    //购买
    const purchaseParam: iap.PurchaseParameter = {
      // 通过purchase接口购买的商品必须是您在AppGallery Connect网站配置的商品
      productId: 'consumeProduct001',
      productType: iap.ProductType.CONSUMABLE,
      developerPayload: 'testPurchase'
    }
    try {
      let res = await iap.purchase(context, purchaseParam);
      hilog.info(0x0001, 'Iap Demo', JSON.stringify(res))
      // 支付成功
      let inAppPurchaseData = res.inAppPurchaseData;
      let inAppPurchaseDataSignature = res.signature;
      // 使用您应用的IAP公钥验证签名
      try {
        await this.checkSign(inAppPurchaseDataSignature, inAppPurchaseData);
        hilog.info(0x0001, 'Iap Demo', 'purchase checkSign true')
        // 若验签成功，必须校验InAppPurchaseData中的productId、price、currency等信息的一致性，验证一致后发货
        // 若用户购买商品为消耗型商品，您需要在发货成功后调用consumePurchase接口进行消耗
        let inAppPurchaseDataObj: InAppPurchaseData = JSON.parse(inAppPurchaseData);
        this.purchaseTokenByQueryConsumProdts = inAppPurchaseDataObj.purchaseToken;
        // result返回子线程
        return 'inAppPurchaseData：' + inAppPurchaseData;
      } catch (err) {
        hilog.error(0x0001, 'Iap Demo', 'purchase checkSign false');
        return 'purchase checkSign failed';
      }
    } catch (err) {
      hilog.error(0x0001, 'Iap Demo', 'purchase err:' + JSON.stringify(err))
      return 'purchase failed:' + JSON.stringify(err, null, 4);
    }
  }

  //消耗
  async handleConsume(context: common.UIAbilityContext): Promise<string> {
    const consumeParameter: iap.ConsumePurchaseParameter = {
      purchaseToken: this.purchaseTokenByQueryConsumProdts,
      developerChallenge: 'developerChallenge'
    }
    try {
      const data: iap.ConsumeResult = await iap.consumePurchase(context, consumeParameter);
      // 处理成功逻辑
      hilog.info(0x0001, 'Iap Demo', `Iap consumePurchase: data:` + JSON.stringify(data));
      // result返回子线程
      return 'consumePurchase: data' + JSON.stringify(data);
    } catch (err) {
      hilog.error(0x0001, 'Iap Demo', `Iap consumePurchase: Error: ${err}`);
      return 'consumePurchase failed:' + JSON.stringify(err, null, 4);
    }
  }

  async checkSign(sign: string, content: string): Promise<boolean> {
    const pubkey = 'MIIBojANBgkqhkiG9w0BAQEFAAOCAY8AMIIBigKCAYEAntYzDxlWIkBQRLkP6GgXZenDM/HZW+RoAgYJLqgaClHEP4uf71sXb7HvnM1upbo4Pbyz7bVFFJA5WIEazbVizepQJPDB+OKhJrPqlQAXqATR2Sy8zDP9czJaYst9RieUuwGHsxg+J7+38lG/gp+VzxNvdmor7Ikl4Ev7aIm9avIpaK0gPE4r22K85bkjvbSEeFNAPXhECcapYf9ikyCrbzJ2uTc5cxPeVpYZpzroeqwPOC14cQcb8Cq4TMxqVVrZQkHdf+ci2YfVMX39/C+NHssw204odbRaKrModczWVDSQbxir2fqfgwUlUCb+WrHhixh4jNedKgBNIBgm9yAZp1ZB72BIHnmbF893DdKbslgwvbxLW1BtjeJ2rHMPjOSUrWdoLdIHkvJmYozl/b9yho+rhWLKzwpLHj0rFTC0FiG5aGvpRFfCqjVCZx2K9Col0elmfQ11+c/O9GYOsRG1tSf+wPYul4ZF6UgJBIIZqhSI+x+YVrvo9JjByZuGwBgtAgMBAAE=';
    // use SHA256WithRSA/PSS
    let rsaGenerator = cryptoFramework.createAsyKeyGenerator("RSA3072");
    let base64 = new util.Base64Helper();
    let pkBlob: cryptoFramework.DataBlob = { data: base64.decodeSync(pubkey) };
    try {
      const keyPair = await rsaGenerator.convertKey(pkBlob, null);
      if (keyPair == null) {
        hilog.info(0x0001, 'Iap Demo', 'convertKey fail.');
        throw new Error("");
      }
      let verifyer = cryptoFramework.createVerify("RSA3072|PSS|SHA256|MGF1_SHA256");
      await verifyer.init(keyPair.pubKey);
      let contentBlob: cryptoFramework.DataBlob = { data: (new util.TextEncoder()).encodeInto(content) };
      let signDataBlob: cryptoFramework.DataBlob = { data: base64.decodeSync(sign) };
      return await verifyer.verify(contentBlob, signDataBlob);
    } catch (err) {
      hilog.error(0x0001, 'Iap Demo', 'Verify result is ' + JSON.stringify(err));
      return false;
    }
  }

  async handleQueryNoConsumableGoods(context: common.UIAbilityContext): Promise<string> {
    //查询非消耗型商品
    const nonConsumableQueryParam: iap.QueryProductsParameter = {
      // 查询的商品必须是您在AppGallery Connect网站配置的商品
      productIds: ['noConsumeProduct001'],
      productType: iap.ProductType.NONCONSUMABLE
    }
    try {
      const products = await iap.queryProducts(context, nonConsumableQueryParam);
      // 处理成功逻辑
      hilog.info(0x0001, 'Iap Demo', `Iap queryProducts: data:` + JSON.stringify(products));
      // result返回子线程
      return 'queryProducts: data' + JSON.stringify(products);
    } catch (error) {
      hilog.error(0x0001, 'Iap Demo', `Iap queryProducts: Error: ${error}`);
      return 'queryProducts failed:' + JSON.stringify(error, null, 4);
    }
  }

  async handlePurchaseOfNonConsumableGoods(context: common.UIAbilityContext): Promise<string> {
    //非消耗型商品购买
    const nonConsumablePurchaseParam: iap.PurchaseParameter = {
      // 通过purchase接口购买的商品必须是您在AppGallery Connect网站配置的商品
      productId: 'noConsumeProduct001',
      productType: iap.ProductType.NONCONSUMABLE,
      developerPayload: 'testPurchase'
    }
    try {
      const res = await iap.purchase(context, nonConsumablePurchaseParam);
      hilog.info(0x0001, 'Iap Demo', JSON.stringify(res))
      // 支付成功
      let inAppPurchaseData = res.inAppPurchaseData;
      let inAppPurchaseDataSignature = res.signature;
      try {
        // 使用您应用的IAP公钥验证签名
        await this.checkSign(inAppPurchaseDataSignature, inAppPurchaseData);
        hilog.info(0x0001, 'Iap Demo', 'purchase checkSign true')
        // 若验签成功，必须校验InAppPurchaseData中的productId、price、currency等信息的一致性，验证一致后发货
        // 若用户购买商品为消耗型商品，您需要在发货成功后调用consumePurchase接口进行消耗
        // result返回子线程
        return 'purchase: data' + inAppPurchaseData;
      } catch (err) {
        hilog.error(0x0001, 'Iap Demo', 'purchase checkSign false')
        return 'purchase checkSign failed';
      }
    } catch (err) {
      // 其他返回码请参见错误码章节进行处理
      hilog.error(0x0001, 'Iap Demo', 'purchase err:' + JSON.stringify(err))
      return 'purchase failed:' + JSON.stringify(err, null, 4);
    }
  }

  async handleDisposableGoodsOrderQuery(context: common.UIAbilityContext): Promise<string> {
    //消耗型商品掉单查询
    const disposableParameter: iap.QueryPurchasesParameter = {
      productType: iap.ProductType.CONSUMABLE
    }
    try {
      const res = await iap.queryOwnedPurchases(context, disposableParameter);
      // 获取成功
      if (res.inAppPurchaseDataList.length <= 0) {
        hilog.error(0x0001, 'Iap Demo', 'inAppPurchaseDataList null');
        return 'queryOwnedPurchases inAppPurchaseDataList null';
      }
      let inAppPurchaseDataStr: string = res.inAppPurchaseDataList[0];
      let inAppPurchaseDataSignature: string = res.inAppSignatureList[0];
      try {
        // 使用您应用的IAP公钥验证签名
        await this.checkSign(inAppPurchaseDataSignature, inAppPurchaseDataStr)
        hilog.info(0x0001, 'Iap Demo', 'queryOwnedPurchases checkSign true')
        // 如果验签成功，为避免资金损失，必须校验InAppPurchaseData中的productId、price、currency等信息的一致性。
        // 验证一致后，请检查支付状态。
        let inAppPurchaseDataObj: InAppPurchaseData = JSON.parse(res.inAppPurchaseDataList[0]);
        let purchaseToken = inAppPurchaseDataObj.purchaseToken;
        let purchaseState = inAppPurchaseDataObj.purchaseState;
        // result返回子线程
        return 'queryOwnedPurchases: data' + purchaseToken;
      } catch (err) {
        hilog.error(0x0001, 'Iap Demo', 'queryOwnedPurchases checkSign false')
        return 'queryOwnedPurchases checkSign failed'
      }
    } catch (err) {
      hilog.error(0x0001, 'Iap Demo', `Iap queryOwnedPurchases: Error: ${err}`);
      return 'queryOwnedPurchases failed:' + JSON.stringify(err, null, 4);
    }
  }

  async handleNonConsumableProductsRecords(context: common.UIAbilityContext): Promise<string> {
    //查询非消耗型商品的购买记录
    const recordsParameter1: iap.QueryPurchasesParameter = {
      productType: iap.ProductType.NONCONSUMABLE
    }
    try {
      const data = await iap.queryPurchaseRecords(context, recordsParameter1);
      // 处理成功逻辑
      hilog.info(0x0001, 'Iap Demo', `Iap queryPurchaseRecords: data:` + JSON.stringify(data));
      // result返回子线程
      return 'queryPurchaseRecords: data' + JSON.stringify(data);
    } catch (err) {
      hilog.error(0x0001, 'Iap Demo', `Iap queryPurchaseRecords: Error: ${err}`);
      return 'queryPurchaseRecords failed:' + JSON.stringify(err, null, 4);
    }
  }

  async handleConsumableProductsRecords(context: common.UIAbilityContext): Promise<string> {
    //查询消耗型商品的购买记录
    const recordsParameter: iap.QueryPurchasesParameter = {
      productType: iap.ProductType.CONSUMABLE
    }
    try {
      const data = await iap.queryPurchaseRecords(context, recordsParameter);
      // 处理成功逻辑
      hilog.info(0x0001, 'Iap Demo', `Iap queryPurchaseRecords: data:` + JSON.stringify(data));
      // result返回子线程
      return 'queryPurchaseRecords: data' + JSON.stringify(data);
    } catch (err) {
      hilog.error(0x0001, 'Iap Demo', `Iap queryPurchaseRecords: Error: ${err}`);
      return 'queryPurchaseRecords failed:' + JSON.stringify(err, null, 4);
    }
  }
}

export const sdkManagerMsg = new SDKManagerMsg();
