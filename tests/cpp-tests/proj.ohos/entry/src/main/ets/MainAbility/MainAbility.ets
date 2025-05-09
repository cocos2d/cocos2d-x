import window from '@ohos.window';
import UIAbility from '@ohos.app.ability.UIAbility';
import nativeRender from "libnativerender.so";
import { ContextType, DeviceUtils  } from "@ohos/libSysCapabilities"
import { GlobalContext,GlobalContextConstants} from "@ohos/libSysCapabilities"
import { BusinessError } from '@kit.BasicServicesKit';
import { WorkerManager } from '../workers/WorkerManager';
import Want from '@ohos.app.ability.Want';
import AbilityConstant from '@ohos.app.ability.AbilityConstant';

const nativeAppLifecycle: nativeRender.CPPFunctions = nativeRender.getContext(ContextType.APP_LIFECYCLE);
const rawFileUtils: nativeRender.CPPFunctions = nativeRender.getContext(ContextType.RAW_FILE_UTILS);
let cocosWorker = WorkerManager.getInstance().getWorker();
GlobalContext.storeGlobalThis(GlobalContextConstants.COCOS2DX_SHOW_FLAG, true);
GlobalContext.storeGlobalThis(GlobalContextConstants.COCOS2DX_HIDE_FLAG, true);
export default class MainAbility extends UIAbility {
    onCreate(want: Want, launchParam: AbilityConstant.LaunchParam): void {
        nativeAppLifecycle.onCreate();
        GlobalContext.storeGlobalThis(GlobalContextConstants.COCOS2DX_ABILITY_CONTEXT, this.context);
        console.info('[LIFECYCLE-App] onCreate')
    }

    onDestroy() {
        nativeAppLifecycle.onDestroy();
        console.info('[LIFECYCLE-App] onDestroy')
    }

    onWindowStageCreate(windowStage: window.WindowStage): void {
        // Main window is created, set main page for this ability
        windowStage.loadContent('pages/Index', (err:BusinessError, data) => {
            if (err.code) {
                return;
            }
            rawFileUtils.nativeResourceManagerInit(this.context.resourceManager);
            rawFileUtils.writablePathInit(this.context.filesDir);
        });

        windowStage.getMainWindow().then((windowIns: window.Window) => {
            GlobalContext.storeGlobalThis(GlobalContextConstants.COCOS2DX_MAIN_WINDOW, windowIns);
            // Set whether to display the status bar and navigation bar. If they are not displayed, [] is displayed.
            let systemBarPromise = windowIns.setWindowSystemBarEnable([]);
            // Whether the window layout is displayed in full screen mode
            let fullScreenPromise = windowIns.setWindowLayoutFullScreen(true);
            // Sets whether the screen is always on.
            let keepScreenOnPromise = windowIns.setWindowKeepScreenOn(true);
            Promise.all([systemBarPromise, fullScreenPromise, keepScreenOnPromise]).then(() => {
                console.info('Succeeded in setting the window');
            }).catch((err: BusinessError) => {
                console.error('Failed to set the window, cause ', err.code, err.message);
            });

            try {
                DeviceUtils.calculateSafeArea(cocosWorker, windowIns.getWindowAvoidArea(window.AvoidAreaType.TYPE_CUTOUT), windowIns.getWindowProperties().windowRect);
                windowIns.on('avoidAreaChange', (data) => {
                    console.info('getSafeAreaRect Succeeded in enabling the listener for system avoid area changes. type:' +
                    JSON.stringify(data.type) + ', area: ' + JSON.stringify(data.area));

                    if(data.type == window.AvoidAreaType.TYPE_SYSTEM_GESTURE || data.type == window.AvoidAreaType.TYPE_KEYBOARD) {
                        return;
                    }

                    let mainWindow: window.Window = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_MAIN_WINDOW);
                    DeviceUtils.calculateSafeArea(cocosWorker, data.area, mainWindow.getWindowProperties().windowRect);
                });
            } catch (exception) {
                console.error(`Failed to enable the listener for system avoid area changes. Cause code: ${exception.code}, message: ${exception.message}`);
            }
        })

        windowStage.on("windowStageEvent", (data:window.WindowStageEventType) => {
            let stageEventType: window.WindowStageEventType = data;
            switch (stageEventType) {
                case window.WindowStageEventType.RESUMED:
                    console.info('[LIFECYCLE-App] onShow_RESUMED')
                    if(GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_SHOW_FLAG)){
                        nativeAppLifecycle.onShow();
                        GlobalContext.storeGlobalThis(GlobalContextConstants.COCOS2DX_SHOW_FLAG, false);
                        GlobalContext.storeGlobalThis(GlobalContextConstants.COCOS2DX_HIDE_FLAG, true);
                    }
                    break;
                case window.WindowStageEventType.PAUSED:
                    if(GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_HIDE_FLAG)){
                        console.info('[LIFECYCLE-App] onHide_PAUSED')
                        nativeAppLifecycle.onHide();
                        GlobalContext.storeGlobalThis(GlobalContextConstants.COCOS2DX_HIDE_FLAG, false);
                        GlobalContext.storeGlobalThis(GlobalContextConstants.COCOS2DX_SHOW_FLAG, true);
                    }
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
        if(GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_SHOW_FLAG)){
            // Ability has brought to foreground
            console.info('[LIFECYCLE-App] onShow')
            nativeAppLifecycle.onShow();
            GlobalContext.storeGlobalThis(GlobalContextConstants.COCOS2DX_SHOW_FLAG, false);
            GlobalContext.storeGlobalThis(GlobalContextConstants.COCOS2DX_HIDE_FLAG, true);
        }
    }

    onBackground() {
        if(GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_HIDE_FLAG)){
            // Ability has back to background
            console.info('[LIFECYCLE-App] onHide')
            nativeAppLifecycle.onHide();
            GlobalContext.storeGlobalThis(GlobalContextConstants.COCOS2DX_HIDE_FLAG, false);
            GlobalContext.storeGlobalThis(GlobalContextConstants.COCOS2DX_SHOW_FLAG, true);
        }
    }
};
