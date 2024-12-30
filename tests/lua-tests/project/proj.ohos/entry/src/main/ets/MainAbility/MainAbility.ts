import window from '@ohos.window';
import UIAbility from '@ohos.app.ability.UIAbility';
import web_webview from '@ohos.web.webview';
import nativeRender from "libnativerender.so";
import { ContextType } from "@ohos/libSysCapabilities"
import { GlobalContext,GlobalContextConstants} from "@ohos/libSysCapabilities"

const nativeAppLifecycle: nativeRender.CPPFunctions = nativeRender.getContext(ContextType.APP_LIFECYCLE);
const rawFileUtils: nativeRender.CPPFunctions = nativeRender.getContext(ContextType.RAW_FILE_UTILS);

export default class MainAbility extends UIAbility {
    onCreate(want, launchParam) {
        nativeAppLifecycle.onCreate();
        GlobalContext.storeGlobalThis(GlobalContextConstants.COCOS2DX_ABILITY_CONTEXT, this.context);
        // Initializes the webView kernel of the system. This parameter is optional if it is not used.
        web_webview.WebviewController.initializeWebEngine();
        GlobalContext.storeGlobalThis(GlobalContextConstants.COCOS2DX_ABILITY_WANT, this.context);
        console.info('[LIFECYCLE-App] onCreate')
    }

    onDestroy() {
        nativeAppLifecycle.onDestroy();
        console.info('[LIFECYCLE-App] onDestroy')
    }

    onWindowStageCreate(windowStage) {
        // Main window is created, set main page for this ability
        windowStage.loadContent('pages/Index', (err, data) => {
            if (err.code) {
                return;
            }
            rawFileUtils.nativeResourceManagerInit(this.context.resourceManager);
            rawFileUtils.writablePathInit(this.context.filesDir);
        });

        windowStage.getMainWindow().then((windowIns: window.Window) => {
            // Set whether to display the status bar and navigation bar. If they are not displayed, [] is displayed.
            let systemBarPromise = windowIns.setWindowSystemBarEnable([]);
            // Whether the window layout is displayed in full screen mode
            let fullScreenPromise = windowIns.setWindowLayoutFullScreen(true);
            // Sets whether the screen is always on.
            let keepScreenOnPromise = windowIns.setWindowKeepScreenOn(true);
            Promise.all([systemBarPromise, fullScreenPromise, keepScreenOnPromise]).then(() => {
                console.info('Succeeded in setting the window');
            }).catch((err) => {
                console.error('Failed to set the window, cause ' + JSON.stringify(err));
            });
        })
        
        windowStage.on("windowStageEvent", (data) => {
            let stageEventType: window.WindowStageEventType = data;
            switch (stageEventType) {
                case window.WindowStageEventType.RESUMED:
                    nativeAppLifecycle.onShow();
                    break;
                case window.WindowStageEventType.PAUSED:
                    nativeAppLifecycle.onHide();
                    break;
                default:
                    break;
            }
        });
    }

    onWindowStageDestroy() {
        // Main window is destroyed, release UI related resources
    }

    onForeground() {
        // Ability has brought to foreground
        console.info('[LIFECYCLE-App] onShow')
        nativeAppLifecycle.onShow();
    }

    onBackground() {
        // Ability has back to background
        console.info('[LIFECYCLE-App] onDestroy')
        nativeAppLifecycle.onHide();
    }
};
