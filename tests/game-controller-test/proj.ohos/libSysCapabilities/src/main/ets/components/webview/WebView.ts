import { ViewRect, WebViewMsgEntity } from '../../entity/WorkerMsgEntity';

export class WebView {
    static MODULE_NAME: string = 'WebView';

    private static parentPort;

    static init(parentPort) : void {
        WebView.parentPort = parentPort;
    }

    static createWebView(viewTag: number) : void {
        let webViewMsgEntity: WebViewMsgEntity = new WebViewMsgEntity(WebView.MODULE_NAME, 'createWebView', viewTag);
        WebView.parentPort.postMessage(webViewMsgEntity);
    }

    static removeWebView(viewTag: number) : void {
        let webViewMsgEntity: WebViewMsgEntity = new WebViewMsgEntity(WebView.MODULE_NAME, 'removeWebView', viewTag);
        WebView.parentPort.postMessage(webViewMsgEntity);
    }

    static loadData(viewTag: number, data: string, mimeType: string, encoding: string, baseURL: string) : void {
        let webViewMsgEntity: WebViewMsgEntity = new WebViewMsgEntity(WebView.MODULE_NAME, 'loadData', viewTag);
        webViewMsgEntity.data = data;
        webViewMsgEntity.mimeType = mimeType;
        webViewMsgEntity.encoding = encoding;
        webViewMsgEntity.baseURL = baseURL;
        WebView.parentPort.postMessage(webViewMsgEntity);
    }

    static loadURL(viewTag: number, url: string) : void {
        let webViewMsgEntity: WebViewMsgEntity = new WebViewMsgEntity(WebView.MODULE_NAME, 'loadURL', viewTag);
        webViewMsgEntity.url = url;
        WebView.parentPort.postMessage(webViewMsgEntity);
    }

    static loadFile(viewTag: number, filePath: string) : void {
        let webViewMsgEntity: WebViewMsgEntity = new WebViewMsgEntity(WebView.MODULE_NAME, 'loadFile', viewTag);
        webViewMsgEntity.filePath = filePath;
        WebView.parentPort.postMessage(webViewMsgEntity);
    }

    static stopLoading(viewTag: number) : void {
        let webViewMsgEntity: WebViewMsgEntity = new WebViewMsgEntity(WebView.MODULE_NAME, 'stopLoading', viewTag);
        WebView.parentPort.postMessage(webViewMsgEntity);
    }

    static reload(viewTag: number) : void {
        let webViewMsgEntity: WebViewMsgEntity = new WebViewMsgEntity(WebView.MODULE_NAME, 'reload', viewTag);
        WebView.parentPort.postMessage(webViewMsgEntity);
    }

    static canGoBack(viewTag: number) : void {
        let webViewMsgEntity: WebViewMsgEntity = new WebViewMsgEntity(WebView.MODULE_NAME, 'canGoBack', viewTag);
        WebView.parentPort.postMessage(webViewMsgEntity);
    }

    static canGoForward(viewTag: number) : void {
        let webViewMsgEntity: WebViewMsgEntity = new WebViewMsgEntity(WebView.MODULE_NAME, 'canGoForward', viewTag);
        WebView.parentPort.postMessage(webViewMsgEntity);
    }

    static goBack(viewTag: number) : void {
        let webViewMsgEntity: WebViewMsgEntity = new WebViewMsgEntity(WebView.MODULE_NAME, 'goBack', viewTag);
        WebView.parentPort.postMessage(webViewMsgEntity);
    }

    static goForward(viewTag: number) : void {
        let webViewMsgEntity: WebViewMsgEntity = new WebViewMsgEntity(WebView.MODULE_NAME, 'goForward', viewTag);
        WebView.parentPort.postMessage(webViewMsgEntity);
    }

    static setWebViewRect(viewTag: number, x: number, y: number, w: number, h: number) : void {
        let webViewMsgEntity: WebViewMsgEntity = new WebViewMsgEntity(WebView.MODULE_NAME, 'setWebViewRect', viewTag);
        let viewRect: ViewRect = new ViewRect(x, y, w, h);
        webViewMsgEntity.viewRect = viewRect;
        WebView.parentPort.postMessage(webViewMsgEntity);
    }

    static setVisible(viewTag: number, visible: boolean) : void {
        let webViewMsgEntity: WebViewMsgEntity = new WebViewMsgEntity(WebView.MODULE_NAME, 'setVisible', viewTag);
        webViewMsgEntity.visible = visible;
        WebView.parentPort.postMessage(webViewMsgEntity);
    }

    static setOpacityWebView(viewTag: number, opacity: number) : void {
        let webViewMsgEntity: WebViewMsgEntity = new WebViewMsgEntity(WebView.MODULE_NAME, 'setOpacityWebView', viewTag);
        webViewMsgEntity.opacity = opacity;
        WebView.parentPort.postMessage(webViewMsgEntity);
    }

    static setBackgroundTransparent(viewTag: number) : void {
        let webViewMsgEntity: WebViewMsgEntity = new WebViewMsgEntity(WebView.MODULE_NAME, 'setBackgroundTransparent', viewTag);
        WebView.parentPort.postMessage(webViewMsgEntity);
    }

    static evaluateJS(viewTag: number, js: string) : void {
        let webViewMsgEntity: WebViewMsgEntity = new WebViewMsgEntity(WebView.MODULE_NAME, 'evaluateJS', viewTag);
        webViewMsgEntity.js = js;
        WebView.parentPort.postMessage(webViewMsgEntity);
    }

    static setScalesPageToFit(viewTag: number, scalesPageToFit: boolean) : void {
        let webViewMsgEntity: WebViewMsgEntity = new WebViewMsgEntity(WebView.MODULE_NAME, 'setScalesPageToFit', viewTag);
        webViewMsgEntity.scalesPageToFit = scalesPageToFit;
        WebView.parentPort.postMessage(webViewMsgEntity);
    }
}