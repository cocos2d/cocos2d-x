import web_webview from '@ohos.web.webview'
import Logger from '../../utils/Logger';
import { GlobalContext, GlobalContextConstants } from '../../common/GlobalContext';
import { BusinessError } from '@ohos.base';

let log: Logger = new Logger(0x0001, "WebView");
export class WebViewInfo {
    public uniqueId: number = 0;
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

function copyWebViewInfo(viewInfo: WebViewInfo): WebViewInfo {
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

function waitUtilControllerAttached(): Promise<number> {
    return new Promise((resolve, reject) => {
        resolve(1);
    })
}

export class WebView {
    static MODULE_NAME: string = 'WebView';

    static createWebView(viewTag: number) : void {
        let view = new WebViewInfo(0, 0, 0, 0, viewTag);
        GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY).push(view);
        GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_INDEX_MAP)
            .set(viewTag, GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY)
                .length - 1);
    }

    static removeWebView(viewTag: number) : void {
        if (GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY).length > 0) {
            let index:number = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_INDEX_MAP).get(viewTag);
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
            tempInfoMap.delete(viewTag);
        }
    }

    static setJavascriptInterfaceScheme(viewTag: number, jsInterfaceScheme: string) : void {
        let index:number = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_INDEX_MAP).get(viewTag);
        let webViewInfo: WebViewInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY)[index];
        webViewInfo.jsInterfaceScheme = jsInterfaceScheme;
    }

    static loadData(viewTag: number, data: string, mimeType: string, encoding: string, baseURL: string) : void {
        let index:number = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_INDEX_MAP).get(viewTag);
        let webViewInfo: WebViewInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY)[index];
        waitUtilControllerAttached().then(() => {
            webViewInfo.controller.loadData(data, mimeType, encoding, baseURL)
        });
    }

    static loadURL(viewTag: number, url: string) : void {
        let index:number = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_INDEX_MAP).get(viewTag);
        GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY)[index].url = url;
        GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY)[index].isUrl = true;
        let webViewInfo: WebViewInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY)[index];
        waitUtilControllerAttached().then(() => {
            webViewInfo.controller.loadUrl(url);
        })
    }

    static loadFile(viewTag: number, filePath: string) : void {
        let index:number = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_INDEX_MAP).get(viewTag);
        GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY)[index].url = filePath;
        GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY)[index].isUrl = false;
        let webViewInfo: WebViewInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY)[index];
        waitUtilControllerAttached().then(() => {
            webViewInfo.controller.loadUrl($rawfile(filePath));
        })
    }

    static stopLoading(viewTag: number) : void {
        let index:number = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_INDEX_MAP).get(viewTag);
        GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY)[index].controller.stop();
    }

    static reload(viewTag: number) : void {
        let index:number = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_INDEX_MAP).get(viewTag);
        let webViewInfo: WebViewInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY)[index];
        waitUtilControllerAttached().then(() => {
            webViewInfo.controller.refresh();
        })
    }

    static canGoBack(viewTag: number) : void {
        let index:number = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_INDEX_MAP).get(viewTag);
        let result: number = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY)[index]
            .controller
            .accessBackward();
        // todo The value needs to be sent back to the worker thread.
    }

    static canGoForward(viewTag: number) : void {
        let index:number = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_INDEX_MAP).get(viewTag);
        let result: number = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY)[index]
            .controller
            .accessForward();
        // todo The value needs to be sent back to the worker thread.
    }

    static goBack(viewTag: number) : void {
        let index:number = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_INDEX_MAP).get(viewTag);
        let webViewInfo: WebViewInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY)[index];
        waitUtilControllerAttached().then(() => {
            webViewInfo.controller.backward();
        })
    }

    static goForward(viewTag: number) : void {
        let index:number = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_INDEX_MAP).get(viewTag);
        let webViewInfo: WebViewInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY)[index];
        waitUtilControllerAttached().then(() => {
            webViewInfo.controller.forward();
        })
    }

    static setWebViewRect(viewTag: number, x: number, y: number, w: number, h: number) : void {
        let index:number = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_INDEX_MAP).get(viewTag);
        let tmpWebInfo: WebViewInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY)[index];
        tmpWebInfo.x = px2vp(x);
        tmpWebInfo.y = px2vp(y);
        tmpWebInfo.w = px2vp(w);
        tmpWebInfo.h = px2vp(h);
        let newViewInfo: WebViewInfo = copyWebViewInfo(tmpWebInfo);
        let tempInfoArray: WebViewInfo[] = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY);
        tempInfoArray[index] = newViewInfo;
    }

    static setVisible(viewTag: number, visible: boolean) : void {
        let index:number = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_INDEX_MAP).get(viewTag);
        if (GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY)[index]
            .visible == visible) {
            return;
        }
        let tmpWebInfo: WebViewInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY)[index];
        tmpWebInfo.visible = visible;
        let newViewInfo: WebViewInfo = copyWebViewInfo(tmpWebInfo);
        let tempInfoArray: WebViewInfo[] = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY);
        tempInfoArray[index] = newViewInfo;
    }

    static setOpacityWebView(viewTag: number, opacity: number) : void {
        let index:number = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_INDEX_MAP).get(viewTag);
        if (GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY)[index]
            .opacity == opacity) {
            return;
        }
        let tmpWebInfo: WebViewInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY)[index];
        tmpWebInfo.opacity = opacity;
        let newViewInfo: WebViewInfo = copyWebViewInfo(tmpWebInfo);
        let tempInfoArray: WebViewInfo[] = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY);
        tempInfoArray[index] = newViewInfo;
    }

    static setBackgroundTransparent(viewTag: number) : void {
        let index:number = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_INDEX_MAP).get(viewTag);
        if (GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY)[index]
            .backgroundColor == Color.Transparent) {
            return;
        }
        GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY)[index]
            .backgroundColor = Color.Transparent;
        let newViewInfo: WebViewInfo = copyWebViewInfo(GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY)[index]);
        let tempInfoArray: WebViewInfo[] = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY);
        tempInfoArray[index] = newViewInfo;
    }

    static evaluateJS(viewTag: number, js: string) : void {
        let index:number = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_INDEX_MAP).get(viewTag);
        GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY)[index]
            .controller
            .runJavaScript(js, (error: BusinessError, result: string) => {
                if (error) {
                    log.warn("webView run JavaScript error:%{public}s", JSON.stringify(error));
                    return;
                }
                if (result) {
                    GlobalContext.storeGlobalThis(GlobalContextConstants.COCOS2DX_WEB_RESULT, result)
                    log.debug("webView run JavaScript result is %{public}s:", result);
                }
            })
    }

    static setScalesPageToFit(viewTag: number, scalesPageToFit: boolean) : void {
        let index:number = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_INDEX_MAP).get(viewTag);
        if (GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY)[index]
            .zoomAccess == scalesPageToFit) {
            return;
        }
        let tmpWebInfo: WebViewInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY)[index];
        tmpWebInfo.zoomAccess == scalesPageToFit
        let newViewInfo: WebViewInfo = copyWebViewInfo(tmpWebInfo);
        let tempInfoArray: WebViewInfo[] = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY);
        tempInfoArray[index] = newViewInfo;
    }
}