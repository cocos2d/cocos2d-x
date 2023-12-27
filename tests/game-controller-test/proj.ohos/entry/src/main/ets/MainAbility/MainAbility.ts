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
        let windowClass = null;
        try {
            window.getLastWindow(this.context, (err, data) => { //获取窗口实例
                if (err.code) {
                    console.error('Failed to obtain last window. Cause:' + JSON.stringify(err));
                    return;
                }
                windowClass = data;
                // 设置状态栏和导航栏是否显示，不显示为[]
                let systemBarPromise = windowClass.setWindowSystemBarEnable([]);
                // 窗口的布局是否为全屏显示状态
                let fullScreenPromise = windowClass.setWindowLayoutFullScreen(true);
                // 设置屏幕是否为常亮状态
                let keepScreenOnPromise = windowClass.setWindowKeepScreenOn(true);
                Promise.all([systemBarPromise, fullScreenPromise, keepScreenOnPromise]).then(() => {
                    console.info('Succeeded in setting the window');
                }).catch((err) => {
                    console.error('Failed to set the window, cause ' + JSON.stringify(err));
                });
            });
        } catch (exception) {
            console.error('Failed to get or set the window, cause ' + JSON.stringify(exception));
        }
        nativeAppLifecycle.onCreate();
        GlobalContext.storeGlobalThis(GlobalContextConstants.COCOS2DX_ABILITY_CONTEXT, this.context);
        // 系统的 webView 内核初始化，如不使用，可不设置
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
