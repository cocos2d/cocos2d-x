import worker, { ThreadWorkerGlobalScope, MessageEvents } from '@ohos.worker';
import nativeRender from "libnativerender.so";
import { ContextType, DeviceUtils } from "@ohos/libSysCapabilities"
import { VideoPlayer } from "@ohos/libSysCapabilities"
import { ApplicationManager } from "@ohos/libSysCapabilities"
import { CocosEditBox } from "@ohos/libSysCapabilities"
import { Dialog } from "@ohos/libSysCapabilities"
import { WebView } from "@ohos/libSysCapabilities"
import { JumpManager } from "@ohos/libSysCapabilities"
import { NapiHelper } from "@ohos/libSysCapabilities"
import { GlobalContext,GlobalContextConstants} from "@ohos/libSysCapabilities"

const appLifecycle: nativeRender.CPPFunctions = nativeRender.getContext(ContextType.APP_LIFECYCLE);
const workerContext: nativeRender.CPPFunctions = nativeRender.getContext(ContextType.WORKER_INIT);
const inputNapi: nativeRender.CPPFunctions = nativeRender.getContext(ContextType.INPUT_NAPI);
const mouseNapi: nativeRender.CPPFunctions = nativeRender.getContext(ContextType.MOUSE_NAPI);
const webViewNapi: nativeRender.CPPFunctions = nativeRender.getContext(ContextType.WEBVIEW_NAPI);
const videoPlayNapi: nativeRender.CPPFunctions = nativeRender.getContext(ContextType.VIDEOPLAYER_NAPI);
const napiContext: nativeRender.CPPFunctions = nativeRender.getContext(ContextType.NATIVE_API);
workerContext.workerInit()

napiContext.nativeEngineStart();
NapiHelper.registerFunctions(napiContext.registerFunction)

const workerPort: ThreadWorkerGlobalScope = worker.workerPort;

workerPort.onmessage = (e: MessageEvents) => {
    switch(e.data.type) {
        case "onXCLoad":
            console.log("[cocos] onXCLoad Callback");
            Dialog.init(workerPort);
            CocosEditBox.init(workerPort);
            JumpManager.init(workerPort);
            WebView.init(workerPort);
            ApplicationManager.init(workerPort);
            VideoPlayer.init(workerPort);
            napiContext.initAsyncInfo();
            break;
        case "abilityContextInit":
            GlobalContext.storeGlobalThis(GlobalContextConstants.COCOS2DX_ABILITY_CONTEXT, e.data.data);
            break;
        case "editBoxOnFocus":
            inputNapi.editBoxOnFocusCB(e.data.viewTag);
            break;
        case "editBoxOnChange":
            inputNapi.editBoxOnChangeCB(e.data.viewTag, e.data.value);
            break;
        case "editBoxOnEnter":
            inputNapi.editBoxOnEnterCB(e.data.viewTag, e.data.text);
            break;
        case "textFieldTTFOnChange":
            inputNapi.textFieldTTFOnChangeCB(e.data.data);
            break;
        case "onMouseWheel":
            mouseNapi.mouseWheelCB(e.data.eventType, e.data.scrollY);
            break;
        case "onPageBegin":
            webViewNapi.shouldStartLoading(e.data.viewTag, e.data.url);
            break;
        case "onPageEnd":
            webViewNapi.finishLoading(e.data.viewTag, e.data.url);
            break;
        case "onJsCallBack":
            webViewNapi.jsCallback();
            break;
        case "onErrorReceive":
            webViewNapi.failLoading(e.data.viewTag, e.data.url);
            break;
        case "onVideoCallBack":
            videoPlayNapi.onVideoCallBack(e.data.viewTag, e.data.event);
            break;
        case "exit":
            appLifecycle.onBackPress();
            break;
        case "updateSafeArea":
            DeviceUtils.updateWorkerSafeArea(e.data.safeArea);
            break;
        default:
            console.error("cocos worker: message type unknown")
    }
}


