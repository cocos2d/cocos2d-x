import worker, { MessageEvents, ThreadWorkerGlobalScope } from '@ohos.worker';
import nativeRender from "libnativerender.so";
import { ContextType } from "@ohos/libSysCapabilities"
import { NapiHelper } from "@ohos/libSysCapabilities/src/main/ets/napi/NapiHelper"
import { GlobalContext,GlobalContextConstants} from "@ohos/libSysCapabilities"
import { WorkerDataEntity } from './WorkerDataEntity';

const appLifecycle: nativeRender.CPPFunctions = nativeRender.getContext(ContextType.APP_LIFECYCLE);
const workerContext: nativeRender.CPPFunctions = nativeRender.getContext(ContextType.WORKER_INIT);
const inputNapi: nativeRender.CPPFunctions = nativeRender.getContext(ContextType.INPUT_NAPI);
const mouseNapi: nativeRender.CPPFunctions = nativeRender.getContext(ContextType.MOUSE_NAPI);
const webViewNapi: nativeRender.CPPFunctions = nativeRender.getContext(ContextType.WEBVIEW_NAPI);
const videoPlayNapi: nativeRender.CPPFunctions = nativeRender.getContext(ContextType.VIDEOPLAYER_NAPI);
const napiContext: nativeRender.CPPFunctions = nativeRender.getContext(ContextType.NATIVE_API);
workerContext.workerInit()

napiContext.nativeEngineStart();
NapiHelper.registerFunctions()

const workerPort: ThreadWorkerGlobalScope = worker.workerPort;

workerPort.onmessage = (e: MessageEvents) : void => {
    let data: WorkerDataEntity  = e.data;
    switch(data.type) {
        case "onXCLoad":
            console.log("[cocos] onXCLoad Callback");
            napiContext.initAsyncInfo();
            break;
        case "abilityContextInit":
            GlobalContext.storeGlobalThis(GlobalContextConstants.COCOS2DX_ABILITY_CONTEXT, data.context);
            break;
        case "editBoxOnFocus":
            inputNapi.editBoxOnFocusCB(data.viewTag);
            break;
        case "editBoxOnChange":
            inputNapi.editBoxOnChangeCB(data.viewTag, data.text);
            break;
        case "editBoxOnEnter":
            inputNapi.editBoxOnEnterCB(data.viewTag, data.text);
            break;
        case "textFieldTTFOnChange":
            inputNapi.textFieldTTFOnChangeCB(data.text);
            break;
        case "onMouseWheel":
            mouseNapi.mouseWheelCB(data.eventType, data.scrollY);
            break;
        case "onPageBegin":
            webViewNapi.shouldStartLoading(data.viewTag, data.url);
            break;
        case "onPageEnd":
            webViewNapi.finishLoading(data.viewTag, data.url);
            break;
        case "onJsCallBack":
            webViewNapi.jsCallback();
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


