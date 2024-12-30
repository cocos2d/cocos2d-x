import { WebViewInfo } from "@ohos/libSysCapabilities/src/main/ets/components/webview/WebViewMsg"
import worker from '@ohos.worker';
import { WorkerManager } from '../workers/WorkerManager';

@Component
export struct CocosWebView {
  viewInfo: WebViewInfo = new WebViewInfo(0, 0, 0, 0, 0);
  cocosWorker: worker.ThreadWorker = WorkerManager.getInstance().getWorker();

  build() {
    Web({ src: this.viewInfo.isUrl ? this.viewInfo.url : $rawfile(this.viewInfo.url), controller: this.viewInfo.controller })
      .position({ x: this.viewInfo.x, y: this.viewInfo.y })
      .width(this.viewInfo.w)
      .height(this.viewInfo.h)
      .border({ width: 1 })
      .domStorageAccess(true)
      .databaseAccess(true)
      .imageAccess(true)
      .onlineImageAccess(true)
      .zoomAccess(this.viewInfo.zoomAccess)
      .javaScriptAccess(true)
      .visibility(this.viewInfo.visible ? Visibility.Visible : Visibility.None)
      .opacity(this.viewInfo.opacity)
      .backgroundColor(this.viewInfo.backgroundColor)
      .onPageBegin((event) => {
        this.cocosWorker.postMessage({ type: "onPageBegin", viewTag: this.viewInfo.viewTag, url: event == null ? '' : event.url });
      })
      .onPageEnd((event) => {
        this.cocosWorker.postMessage({ type: "onPageEnd", viewTag: this.viewInfo.viewTag, url: event == null ? '' : event.url })
        if(this.viewInfo.jsInterfaceScheme != "" && event != null && event.url.startsWith(this.viewInfo.jsInterfaceScheme)) {
          this.cocosWorker.postMessage({ type: "onJsCallBack", viewTag: this.viewInfo.viewTag, url: event == null ? '' : event.url })
        }
        // if u want use the javascript on ur page, u can use registerJavaScriptProxy() to register js function here
        // and confirm that just register once by a local variable
      })
      .onErrorReceive((event) => {
        this.cocosWorker.postMessage({ type: "onErrorReceive", viewTag: this.viewInfo.viewTag, url: this.viewInfo.url })
      })
      .onHttpErrorReceive((event) => {
        this.cocosWorker.postMessage({ type: "onErrorReceive", viewTag: this.viewInfo.viewTag, url: this.viewInfo.url })
      })
  }
}
