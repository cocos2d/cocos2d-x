import worker, { ThreadWorkerGlobalScope } from '@ohos.worker';
import nativeRender from 'libnativerender.so';
import {
    CocosEditBox,
    ContextType,
    DeviceUtils,
    Dialog,
    GlobalContext,
    GlobalContextConstants,
    JumpManager,
    NapiHelper,
    VideoPlayer,
    WebView
} from '@ohos/libSysCapabilities';

const appLifecycle: nativeRender.CPPFunctions = nativeRender.getContext(ContextType.APP_LIFECYCLE);
const workerContext: nativeRender.CPPFunctions = nativeRender.getContext(ContextType.WORKER_INIT);
const inputNapi: nativeRender.CPPFunctions = nativeRender.getContext(ContextType.INPUT_NAPI);
const webViewNapi: nativeRender.CPPFunctions = nativeRender.getContext(ContextType.WEBVIEW_NAPI);
const videoPlayNapi: nativeRender.CPPFunctions = nativeRender.getContext(ContextType.VIDEOPLAYER_NAPI);
const napiContext: nativeRender.CPPFunctions = nativeRender.getContext(ContextType.NATIVE_API);
workerContext.workerInit()

napiContext.nativeEngineStart();
NapiHelper.registerFunctions(napiContext.registerFunction)

const workerPort: ThreadWorkerGlobalScope = worker.workerPort;

workerPort.onmessage = function(e) : void {
    let data = e.data;
    switch(data.type) {
        case "onXCLoad":
            console.log("[cocos] onXCLoad Callback");
            Dialog.init(workerPort);
            CocosEditBox.init(workerPort);
            JumpManager.init(workerPort);
            WebView.init(workerPort);
            VideoPlayer.init(workerPort);
            DeviceUtils.init(workerPort);
            napiContext.initAsyncInfo();
            break;
        case "abilityContextInit":
            GlobalContext.storeGlobalThis(GlobalContextConstants.COCOS2DX_ABILITY_CONTEXT, data.data);
            break;
        case "editBoxOnChange":
            inputNapi.editBoxOnChangeCB(data.viewTag, data.value);
            break;
        case "editBoxOnEnter":
            inputNapi.editBoxOnEnterCB(data.viewTag, data.text);
            break;
        case "textFieldTTFOnChange":
            inputNapi.textFieldTTFOnChangeCB(data.data);
            break;
        case "onPageBegin":
            webViewNapi.shouldStartLoading(data.viewTag, data.url);
            break;
        case "onPageEnd":
            webViewNapi.finishLoading(data.viewTag, data.url);
            break;
        case "onErrorReceive":
            webViewNapi.failLoading(data.viewTag, data.url);
            break;
        case "onVideoCallBack":
            videoPlayNapi.onVideoCallBack(data.viewTag, data.event);
            break;
        case "exit":
            appLifecycle.onBackPress();
            break;
        default:
            console.error("cocos worker: message type unknown")
    }
}


