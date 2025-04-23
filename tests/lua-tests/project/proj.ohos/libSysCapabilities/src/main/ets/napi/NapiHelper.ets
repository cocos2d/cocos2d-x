import { Dialog } from '../components/dialog/DialogWorker'
import { JumpManager } from '../system/appJump/JumpManager'
import { DeviceUtils } from '../system/device/DeviceUtils'
import { ApplicationManager } from '../system/application/ApplicationManager'
import { CocosEditBox } from '../components/editbox/CocosEditBox'
import { WebView } from '../components/webview/WebView'
import { VideoPlayer } from '../components/videoplayer/VideoPlayer'
import Accelerometer from '../system/sensor/AccelerometerUtils'
import nativerender from "libnativerender.so";

export class NapiHelper {
    // The JS code needs to be executed in the worker thread and the method needs to be bound here.
    static registerFunctions() {
        NapiHelper.registerOthers();
        NapiHelper.registerDeviceUtils();
        NapiHelper.registerSensor();
    }

    // The JS code needs to be executed in the UI thread. The method is registered here.
    static registerUIFunctions() {
        NapiHelper.registerEditBox();
        NapiHelper.registerVideoPlay();
        NapiHelper.registerWebView();
        NapiHelper.registerOtherUIFunctions();
    }

    private static registerOthers() {
        nativerender.JSBind.bindFunction("ApplicationManager.getVersionName", ApplicationManager.getVersionName);
    }

    private static registerDeviceUtils() {
        nativerender.JSBind.bindFunction("DeviceUtils.getSystemLanguage", DeviceUtils.getSystemLanguage);
        nativerender.JSBind.bindFunction("DeviceUtils.getDpi", DeviceUtils.getDpi);
        nativerender.JSBind.bindFunction("DeviceUtils.startVibration", DeviceUtils.startVibration);
        nativerender.JSBind.bindFunction("DeviceUtils.setKeepScreenOn", DeviceUtils.setKeepScreenOn);
        nativerender.JSBind.bindFunction("DeviceUtils.isRoundScreen", DeviceUtils.isRoundScreen);
        nativerender.JSBind.bindFunction("DeviceUtils.hasSoftKeys", DeviceUtils.hasSoftKeys);
        nativerender.JSBind.bindFunction("DeviceUtils.isCutoutEnable", DeviceUtils.isCutoutEnable);
        nativerender.JSBind.bindFunction("DeviceUtils.initScreenInfo", DeviceUtils.initScreenInfo);
        nativerender.JSBind.bindFunction("DeviceUtils.getOrientation", DeviceUtils.getOrientation);
        nativerender.JSBind.bindFunction("DeviceUtils.getCutoutHeight", DeviceUtils.getCutoutHeight);
        nativerender.JSBind.bindFunction("DeviceUtils.getCutoutWidth", DeviceUtils.getCutoutWidth);
    }

    private static registerSensor() {
        nativerender.JSBind.bindFunction('Accelerometer.enable', Accelerometer.enable);
        nativerender.JSBind.bindFunction('Accelerometer.disable', Accelerometer.disable);
    }

    private static registerEditBox() {
        nativerender.JSBind.bindFunction('CocosEditBox.createCocosEditBox', CocosEditBox.createCocosEditBox);
        nativerender.JSBind.bindFunction('CocosEditBox.removeCocosEditBox', CocosEditBox.removeCocosEditBox);
        nativerender.JSBind.bindFunction('CocosEditBox.setCurrentText', CocosEditBox.setCurrentText);
        nativerender.JSBind.bindFunction('CocosEditBox.setEditBoxViewRect', CocosEditBox.setEditBoxViewRect);
        nativerender.JSBind.bindFunction('CocosEditBox.setEditBoxVisible', CocosEditBox.setEditBoxVisible);
        nativerender.JSBind.bindFunction('CocosEditBox.setEditBoxPlaceHolder', CocosEditBox.setEditBoxPlaceHolder);
        nativerender.JSBind.bindFunction('CocosEditBox.setEditBoxFontSize', CocosEditBox.setEditBoxFontSize);
        nativerender.JSBind.bindFunction('CocosEditBox.setEditBoxFontColor', CocosEditBox.setEditBoxFontColor);
        nativerender.JSBind.bindFunction('CocosEditBox.setEditBoxFontPath', CocosEditBox.setEditBoxFontPath);
        nativerender.JSBind.bindFunction('CocosEditBox.setEditBoxPlaceHolderFontSize', CocosEditBox.setEditBoxPlaceHolderFontSize);
        nativerender.JSBind.bindFunction('CocosEditBox.setEditBoxPlaceHolderFontColor', CocosEditBox.setEditBoxPlaceHolderFontColor);
        nativerender.JSBind.bindFunction('CocosEditBox.setEditBoxPlaceHolderFontPath', CocosEditBox.setEditBoxPlaceHolderFontPath);
        nativerender.JSBind.bindFunction('CocosEditBox.setEditBoxMaxLength', CocosEditBox.setEditBoxMaxLength);
        nativerender.JSBind.bindFunction('CocosEditBox.setNativeInputMode', CocosEditBox.setNativeInputMode);
        nativerender.JSBind.bindFunction('CocosEditBox.setNativeInputFlag', CocosEditBox.setNativeInputFlag);
        nativerender.JSBind.bindFunction('CocosEditBox.hideAllEditBox', CocosEditBox.hideAllEditBox);
    }

    private static registerVideoPlay() {
        nativerender.JSBind.bindFunction('VideoPlayer.createVideoPlayer', VideoPlayer.createVideoPlayer);
        nativerender.JSBind.bindFunction('VideoPlayer.removeVideoPlayer', VideoPlayer.removeVideoPlayer);
        nativerender.JSBind.bindFunction('VideoPlayer.setURL', VideoPlayer.setURL);
        nativerender.JSBind.bindFunction('VideoPlayer.setLooping', VideoPlayer.setLooping);
        nativerender.JSBind.bindFunction('VideoPlayer.setVideoPlayerRect', VideoPlayer.setVideoPlayerRect);
        nativerender.JSBind.bindFunction('VideoPlayer.play', VideoPlayer.play);
        nativerender.JSBind.bindFunction('VideoPlayer.pause', VideoPlayer.pause);
        nativerender.JSBind.bindFunction('VideoPlayer.stop', VideoPlayer.stop);
        nativerender.JSBind.bindFunction('VideoPlayer.setVisible', VideoPlayer.setVisible);
        nativerender.JSBind.bindFunction('VideoPlayer.requestFullscreen', VideoPlayer.requestFullscreen);
        nativerender.JSBind.bindFunction('VideoPlayer.seekTo', VideoPlayer.seekTo);
        nativerender.JSBind.bindFunction('VideoPlayer.setKeepAspectRatioEnabled', VideoPlayer.setKeepAspectRatioEnabled);
    }

    private static registerWebView() {
        nativerender.JSBind.bindFunction('WebView.createWebView', WebView.createWebView);
        nativerender.JSBind.bindFunction('WebView.removeWebView', WebView.removeWebView);
        nativerender.JSBind.bindFunction('WebView.setJavascriptInterfaceScheme', WebView.setJavascriptInterfaceScheme);
        nativerender.JSBind.bindFunction('WebView.loadData', WebView.loadData);
        nativerender.JSBind.bindFunction('WebView.loadURL', WebView.loadURL);
        nativerender.JSBind.bindFunction('WebView.loadFile', WebView.loadFile);
        nativerender.JSBind.bindFunction('WebView.stopLoading', WebView.stopLoading);
        nativerender.JSBind.bindFunction('WebView.reload', WebView.reload);
        nativerender.JSBind.bindFunction('WebView.canGoBack', WebView.canGoBack);
        nativerender.JSBind.bindFunction('WebView.canGoForward', WebView.canGoForward);
        nativerender.JSBind.bindFunction('WebView.goBack', WebView.goBack);
        nativerender.JSBind.bindFunction('WebView.goForward', WebView.goForward);
        nativerender.JSBind.bindFunction('WebView.setWebViewRect', WebView.setWebViewRect);
        nativerender.JSBind.bindFunction('WebView.setVisible', WebView.setVisible);
        nativerender.JSBind.bindFunction('WebView.setOpacityWebView', WebView.setOpacityWebView);
        nativerender.JSBind.bindFunction('WebView.setBackgroundTransparent', WebView.setBackgroundTransparent);
        nativerender.JSBind.bindFunction('WebView.evaluateJS', WebView.evaluateJS);
        nativerender.JSBind.bindFunction('WebView.setScalesPageToFit', WebView.setScalesPageToFit);
    }

    private static registerOtherUIFunctions() {
        nativerender.JSBind.bindFunction('JumpManager.openUrl', JumpManager.openUrl);
        nativerender.JSBind.bindFunction('ApplicationManager.exit', ApplicationManager.exit);
        nativerender.JSBind.bindFunction('DiaLog.showDialog', Dialog.showDialog);
        nativerender.JSBind.bindFunction('DiaLog.showTextInputDialog', Dialog.showTextInputDialog);
        nativerender.JSBind.bindFunction('DiaLog.hideTextInputDialog', Dialog.hideTextInputDialog);

        nativerender.JSBind.bindFunction("DeviceUtils.getSafeAreaLeft", DeviceUtils.getSafeAreaLeft);
        nativerender.JSBind.bindFunction("DeviceUtils.getSafeAreaTop", DeviceUtils.getSafeAreaTop);
        nativerender.JSBind.bindFunction("DeviceUtils.getSafeAreaWidth", DeviceUtils.getSafeAreaWidth);
        nativerender.JSBind.bindFunction("DeviceUtils.getSafeAreaHeight", DeviceUtils.getSafeAreaHeight);
    }
}
