import web_webview from '@ohos.web.webview'
import Logger from '../../utils/Logger';
import { GlobalContext, GlobalContextConstants } from '../../common/GlobalContext';
import { WebViewMsgEntity } from '../../entity/WorkerMsgEntity';
import { BusinessError } from '@ohos.base';

let log: Logger = new Logger(0x0001, "WebViewMsg");

export class WebViewInfo {
  public uniqueId : number = 0;
  // position
  public x: number = 0;
  public y: number = 0;
  // size
  public w: number = 0;
  public h: number = 0;
  // url
  public url: string = '';
  public isUrl: boolean = true;

  public viewTag: number = 0
  public zoomAccess: boolean = true
  public visible: boolean = true
  public opacity: number = 1
  public backgroundColor: number = 0xffffff;
  public jsInterfaceScheme: string = "";
  public controller: web_webview.WebviewController = new web_webview.WebviewController()

  constructor(x: number, y: number, w: number, h: number, viewTag: number) {
    this.x = x;
    this.y = y;
    this.w = w;
    this.h = h;
    this.viewTag = viewTag
    this.uniqueId = viewTag;
  }
}

function copyWebViewInfo(viewInfo: WebViewInfo) : WebViewInfo {
  let newViewInfo: WebViewInfo = new WebViewInfo(viewInfo.x, viewInfo.y, viewInfo.w, viewInfo.h, viewInfo.viewTag);
  newViewInfo.url = viewInfo.url;
  newViewInfo.isUrl = viewInfo.isUrl;
  newViewInfo.zoomAccess = viewInfo.zoomAccess;
  newViewInfo.visible = viewInfo.visible;
  newViewInfo.controller = viewInfo.controller;
  newViewInfo.opacity = viewInfo.opacity;
  newViewInfo.backgroundColor = viewInfo.backgroundColor;
  newViewInfo.jsInterfaceScheme = viewInfo.jsInterfaceScheme;
  newViewInfo.uniqueId = 100000 - viewInfo.uniqueId; // support 50000 webView exist at the same time
  return newViewInfo;
}

function waitUtilControllerAttached() : Promise<number> {
  return new Promise((resolve, reject) => {
      resolve(1);
  })
}

export function handleWebViewMsg(eventData: WebViewMsgEntity) {
  let index: number;
  switch (eventData.function) {
    case "createWebView": {
      let view = new WebViewInfo(0, 0, 0, 0, eventData.viewTag);
      GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY).push(view);
      GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_INDEX_MAP)
        .set(eventData.viewTag, GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY)
          .length - 1);
      break;
    }
    case "removeWebView": {
      if (GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY).length > 0) {
        index = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_INDEX_MAP).get(eventData.viewTag);
        GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY).splice(index, 1);
        // Do not assume the invoking time of removeWebView. After an element is deleted, the following elements need to be advanced by one bit.
        GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_INDEX_MAP)
          .forEach((value: number, key: number, map: Map<number, number>) => {
            if (value > index) {
              GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_INDEX_MAP).set(key, value - 1);
            }
          })

        // Delete the subscript mapping of the removed webView.
        let tempInfoMap: Map<number, number> = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_INDEX_MAP);
        tempInfoMap.delete(eventData.viewTag);
      }
      break;
    }
    case "setJavascriptInterfaceScheme": {
      index = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_INDEX_MAP).get(eventData.viewTag);
      let webViewInfo: WebViewInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY)[index];
      webViewInfo.jsInterfaceScheme = eventData.jsInterfaceScheme;
      break;
    }
    case "loadData": {
      index = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_INDEX_MAP).get(eventData.viewTag);
      let webViewInfo: WebViewInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY)[index];
      waitUtilControllerAttached().then(() => {
        webViewInfo.controller.loadData(eventData.data, eventData.mimeType, eventData.encoding, eventData.baseURL)
      });
      break;
    }
    case "loadURL": {
      index = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_INDEX_MAP).get(eventData.viewTag);
      GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY)[index].url = eventData.url;
      GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY)[index].isUrl = true;
      let webViewInfo: WebViewInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY)[index];
      waitUtilControllerAttached().then(() => {
        webViewInfo.controller.loadUrl(eventData.url);
      })
      break;
    }
    case "loadFile": {
      index = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_INDEX_MAP).get(eventData.viewTag);
      GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY)[index].url = eventData.filePath;
      GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY)[index].isUrl = false;
      let webViewInfo: WebViewInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY)[index];
      waitUtilControllerAttached().then(() => {
        webViewInfo.controller.loadUrl($rawfile(eventData.filePath));
      })
      break;
    }
    case "stopLoading":
      index = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_INDEX_MAP).get(eventData.viewTag);
      GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY)[index].controller.stop();
      break;
    case "reload": {
      index = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_INDEX_MAP).get(eventData.viewTag);
      let webViewInfo: WebViewInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY)[index];
      waitUtilControllerAttached().then(() => {
        webViewInfo.controller.refresh();
      })
      break;
    }
    case "canGoBack":
      index = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_INDEX_MAP).get(eventData.viewTag);
      let result: number = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY)[index]
        .controller
        .accessBackward();
    // todo The value needs to be sent back to the worker thread.
      break;
    case "canGoForward":
      index = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_INDEX_MAP).get(eventData.viewTag);
      result = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY)[index]
        .controller
        .accessForward();
    // todo The value needs to be sent back to the worker thread.
      break;
    case "goBack": {
      index = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_INDEX_MAP).get(eventData.viewTag);
      let webViewInfo: WebViewInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY)[index];
      waitUtilControllerAttached().then(() => {
        webViewInfo.controller.backward();
      })
      break;
    }
    case "goForward": {
      index = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_INDEX_MAP).get(eventData.viewTag);
      let webViewInfo: WebViewInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY)[index];
      waitUtilControllerAttached().then(() => {
        webViewInfo.controller.forward();
      })
      break;
    }
    case "setWebViewRect": {
      index = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_INDEX_MAP).get(eventData.viewTag);
      let tmpWebInfo :WebViewInfo= GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY)[index];
      tmpWebInfo.x = px2vp(eventData.viewRect.x);
      tmpWebInfo.y = px2vp(eventData.viewRect.y);
      tmpWebInfo.w = px2vp(eventData.viewRect.w);
      tmpWebInfo.h = px2vp(eventData.viewRect.h);
      let newViewInfo:WebViewInfo = copyWebViewInfo(tmpWebInfo);
      let tempInfoArray :WebViewInfo[]= GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY);
      tempInfoArray[index] = newViewInfo;
      break;
    }
    case "setVisible": {
      index = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_INDEX_MAP).get(eventData.viewTag);
      if (GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY)[index]
        .visible == eventData.visible) {
        return;
      }
      let tmpWebInfo:WebViewInfo= GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY)[index];
      tmpWebInfo.visible = eventData.visible;
      let newViewInfo:WebViewInfo = copyWebViewInfo(tmpWebInfo);
      let tempInfoArray :WebViewInfo[]= GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY);
      tempInfoArray[index] = newViewInfo;
      break;
    }
    case "setOpacityWebView": {
      index = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_INDEX_MAP).get(eventData.viewTag);
      if (GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY)[index]
        .opacity == eventData.opacity) {
        return;
      }
      let tmpWebInfo :WebViewInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY)[index];
      tmpWebInfo.opacity = eventData.opacity;
      let newViewInfo :WebViewInfo= copyWebViewInfo(tmpWebInfo);
      let tempInfoArray :WebViewInfo[]= GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY);
      tempInfoArray[index] = newViewInfo;
      break;
    }
    case "setBackgroundTransparent": {
      index = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_INDEX_MAP).get(eventData.viewTag);
      if (GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY)[index]
        .backgroundColor == Color.Transparent) {
        return;
      }
      GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY)[index]
        .backgroundColor = Color.Transparent;
      let newViewInfo :WebViewInfo= copyWebViewInfo(GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY)[index]);
      let tempInfoArray :WebViewInfo[]= GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY);
      tempInfoArray[index] = newViewInfo;
      break;
    }
    case "evaluateJS": {
      index = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_INDEX_MAP).get(eventData.viewTag);
      GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY)[index]
        .controller
        .runJavaScript(eventData.js, (error:BusinessError, result:string) => {
          if (error) {
            log.warn("webView run JavaScript error:%{public}s", JSON.stringify(error));
            return;
          }
          if (result) {
            GlobalContext.storeGlobalThis(GlobalContextConstants.COCOS2DX_WEB_RESULT,result)
            log.debug("webView run JavaScript result is %{public}s:", result);
          }
        })
      break;
    }
    case "setScalesPageToFit": {
      index = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_INDEX_MAP).get(eventData.viewTag);
      if (GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY)[index]
        .zoomAccess == eventData.scalesPageToFit) {
        return;
      }
      let tmpWebInfo:WebViewInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY)[index];
      tmpWebInfo.zoomAccess == eventData.scalesPageToFit
      let newViewInfo:WebViewInfo = copyWebViewInfo(tmpWebInfo);
      let tempInfoArray:WebViewInfo[] = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY);
      tempInfoArray[index] = newViewInfo;
    }
      break;
  }
}