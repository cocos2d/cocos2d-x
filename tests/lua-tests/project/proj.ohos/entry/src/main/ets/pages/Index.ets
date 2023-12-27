import nativeRender from 'libnativerender.so'
import { ContextType } from '@ohos/libSysCapabilities'
import { TextInputInfo } from '@ohos/libSysCapabilities/src/main/ets/components/editbox/EditBoxMsg'
import { TextInputDialogEntity } from '@ohos/libSysCapabilities'
import { WebViewInfo } from '@ohos/libSysCapabilities/src/main/ets/components/webview/WebViewMsg'
import { VideoPlayerInfo } from '@ohos/libSysCapabilities/src/main/ets/components/videoplayer/VideoPlayerMsg'
import { WorkerMsgUtils } from '@ohos/libSysCapabilities/src/main/ets/utils/WorkerMsgUtils'
import { WorkerManager } from '../workers/WorkerManager'
import { CocosEditBox } from '../components/CocosEditBox'
import { CocosWebView } from '../components/CocosWebview'
import { CocosVideoPlayer } from '../components/CocosVideoPlayer'
import { TextInputDialog } from '../components/TextInputDialog'
import { GlobalContext,GlobalContextConstants} from "@ohos/libSysCapabilities"
const nativePageLifecycle:nativeRender.CPPFunctions  = nativeRender.getContext(ContextType.JSPAGE_LIFECYCLE);

@Entry
@Component
struct Index {

  cocosWorker = WorkerManager.getInstance().getWorker();
  xcomponentController: XComponentController = new XComponentController();

  // EditBox
  @State editBoxArray: TextInputInfo[] = [];
  private editBoxIndexMap: Map<number, TextInputInfo> = new Map;

  // WebView
  @State webViewArray: WebViewInfo[] = [];
  private webViewIndexMap: Map<number, number> = new Map;

  // videoPlayer
  @State videoPlayerInfoArray: VideoPlayerInfo[] = [];
  private videoPlayerIndexMap: Map<number, VideoPlayerInfo> = new Map;

  // textInputDialog
  showMessage: TextInputDialogEntity = new TextInputDialogEntity('');
  dialogController: CustomDialogController = new CustomDialogController({
    builder: TextInputDialog({
      showMessage: this.showMessage
    }),
    autoCancel: true,
    alignment: DialogAlignment.Bottom,
    customStyle: true,
  })

  onPageShow() {
    console.log('[LIFECYCLE-Page] onPageShow');
    GlobalContext.storeGlobalThis(GlobalContextConstants.COCOS2DX_EDIT_BOX_ARRAY, this.editBoxArray);
    GlobalContext.storeGlobalThis(GlobalContextConstants.COCOS2DX_EDIT_BOX_INDEX_MAP, this.editBoxIndexMap);
    GlobalContext.storeGlobalThis(GlobalContextConstants.COCOS2DX_COCOS_WORKER, this.cocosWorker);
    GlobalContext.storeGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_ARRAY, this.webViewArray);
    GlobalContext.storeGlobalThis(GlobalContextConstants.COCOS2DX_WEB_VIEW_INDEX_MAP, this.webViewIndexMap);
    GlobalContext.storeGlobalThis(GlobalContextConstants.COCOS2DX_VIDEO_PLAYER_ARRAY, this.videoPlayerInfoArray);
    GlobalContext.storeGlobalThis(GlobalContextConstants.COCOS2DX_VIDEO_PLAYER_INDEX_MAP, this.videoPlayerIndexMap);
    GlobalContext.storeGlobalThis(GlobalContextConstants.COCOS2DX_DIALOG_CONTROLLER, this.dialogController);
    GlobalContext.storeGlobalThis(GlobalContextConstants.COCOS2DX_SHOW_MESSAGE, this.showMessage);
    nativePageLifecycle.onPageShow();
  }

  onPageHide() {
    console.log('[LIFECYCLE-Page] onPageHide');
    nativePageLifecycle.onPageHide();
  }

  onBackPress() {
    console.log('[LIFECYCLE-Page] onBackPress');
    this.cocosWorker.postMessage({ type: "exit" });
    return true;
  }

  build() {
    Flex({ direction: FlexDirection.Column, alignItems: ItemAlign.Center, justifyContent: FlexAlign.Center }) {
      XComponent({
        id: 'xcomponentId',
        type: 'surface',
        libraryname: 'nativerender',
        controller: this.xcomponentController
      })
        .onLoad((context) => {
          console.log('[cocos] XComponent.onLoad Callback');
          this.cocosWorker.postMessage({ type: "abilityContextInit", data: GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_ABILITY_CONTEXT)});
          this.cocosWorker.postMessage({ type: "onXCLoad", data: "XComponent" });
          this.cocosWorker.onmessage = WorkerMsgUtils.recvWorkerThreadMessage;
        })
        .onDestroy(() => {
        })
      ForEach(this.editBoxArray, (item:TextInputInfo) => {
        CocosEditBox({ textInputInfo: item});
      }, (item:TextInputInfo) => item.viewTag.toString())

      ForEach(this.webViewArray, (item:WebViewInfo) => {
        CocosWebView({ viewInfo: item })
      }, (item:WebViewInfo) => item.uniqueId.toString())

      ForEach(this.videoPlayerInfoArray, (item:VideoPlayerInfo) => {
        CocosVideoPlayer({ videoPlayerInfo: item })
      }, (item:VideoPlayerInfo) => item.viewTag.toString())
    }
    .width('100%')
    .height('100%')
  }
}
