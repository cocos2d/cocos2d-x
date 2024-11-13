import { Dialog } from '../components/dialog/DialogWorker'
import { JumpManager } from '../system/appJump/JumpManager'
import { DeviceUtils } from '../system/device/DeviceUtils'
import { ApplicationManager } from '../system/application/ApplicationManager'
import { CocosEditBox } from '../components/editbox/CocosEditBox'
import { WebView } from '../components/webview/WebView'
import { VideoPlayer } from '../components/videoplayer/VideoPlayer'
import Accelerometer from '../system/sensor/AccelerometerUtils'

export class NapiHelper {

    static registerFunctions(registerFunc : Function) {
        NapiHelper.registerOthers(registerFunc);
        NapiHelper.registerDeviceUtils(registerFunc);
        NapiHelper.registerEditBox(registerFunc);
        NapiHelper.registerWebView(registerFunc);
        NapiHelper.registerVideoPlay(registerFunc);
        NapiHelper.registerSensor(registerFunc);
    }

    private static registerOthers(registerFunc : Function) {
        registerFunc('DiaLog.showDialog', Dialog.showDialog);
        registerFunc('DiaLog.showTextInputDialog', Dialog.showTextInputDialog);
        registerFunc('DiaLog.hideTextInputDialog', Dialog.hideTextInputDialog);
        registerFunc('ApplicationManager.exit', ApplicationManager.exit);
        registerFunc('ApplicationManager.getVersionName', ApplicationManager.getVersionName);
        registerFunc('JumpManager.openUrl', JumpManager.openUrl);
    }


    private static registerDeviceUtils(registerFunc : Function) {
        registerFunc('DeviceUtils.getDpi', DeviceUtils.getDpi);
        registerFunc('DeviceUtils.getSystemLanguage', DeviceUtils.getSystemLanguage);
        registerFunc('DeviceUtils.startVibration', DeviceUtils.startVibration);
        registerFunc('DeviceUtils.setKeepScreenOn', DeviceUtils.setKeepScreenOn);
        registerFunc('DeviceUtils.isRoundScreen', DeviceUtils.isRoundScreen);
        registerFunc('DeviceUtils.hasSoftKeys', DeviceUtils.hasSoftKeys);
        registerFunc('DeviceUtils.isCutoutEnable', DeviceUtils.isCutoutEnable);
        registerFunc('DeviceUtils.initScreenInfo', DeviceUtils.initScreenInfo);
        registerFunc('DeviceUtils.getOrientation', DeviceUtils.getOrientation);
        registerFunc('DeviceUtils.getCutoutHeight', DeviceUtils.getCutoutHeight);
        registerFunc('DeviceUtils.getCutoutWidth', DeviceUtils.getCutoutWidth);
    }

    private static registerEditBox(registerFunc : Function) {
        registerFunc('CocosEditBox.createCocosEditBox', CocosEditBox.createCocosEditBox);
        registerFunc('CocosEditBox.removeCocosEditBox', CocosEditBox.removeCocosEditBox);
        registerFunc('CocosEditBox.setCurrentText', CocosEditBox.setCurrentText);
        registerFunc('CocosEditBox.setEditBoxViewRect', CocosEditBox.setEditBoxViewRect);
        registerFunc('CocosEditBox.setEditBoxVisible', CocosEditBox.setEditBoxVisible);
        registerFunc('CocosEditBox.setEditBoxPlaceHolder', CocosEditBox.setEditBoxPlaceHolder);
        registerFunc('CocosEditBox.setEditBoxFontSize', CocosEditBox.setEditBoxFontSize);
        registerFunc('CocosEditBox.setEditBoxFontColor', CocosEditBox.setEditBoxFontColor);
        registerFunc('CocosEditBox.setEditBoxFontPath', CocosEditBox.setEditBoxFontPath);
        registerFunc('CocosEditBox.setEditBoxPlaceHolderFontSize', CocosEditBox.setEditBoxPlaceHolderFontSize);
        registerFunc('CocosEditBox.setEditBoxPlaceHolderFontColor', CocosEditBox.setEditBoxPlaceHolderFontColor);
        registerFunc('CocosEditBox.setEditBoxPlaceHolderFontPath', CocosEditBox.setEditBoxPlaceHolderFontPath);
        registerFunc('CocosEditBox.setEditBoxMaxLength', CocosEditBox.setEditBoxMaxLength);
        registerFunc('CocosEditBox.setNativeInputMode', CocosEditBox.setNativeInputMode);
        registerFunc('CocosEditBox.setNativeInputFlag', CocosEditBox.setNativeInputFlag);
        registerFunc('CocosEditBox.hideAllEditBox', CocosEditBox.hideAllEditBox);
    }

    private static registerWebView(registerFunc : Function) {
        registerFunc('WebView.createWebView', WebView.createWebView);
        registerFunc('WebView.removeWebView', WebView.removeWebView);
        registerFunc('WebView.setJavascriptInterfaceScheme', WebView.setJavascriptInterfaceScheme);
        registerFunc('WebView.loadData', WebView.loadData);
        registerFunc('WebView.loadURL', WebView.loadURL);
        registerFunc('WebView.loadFile', WebView.loadFile);
        registerFunc('WebView.stopLoading', WebView.stopLoading);
        registerFunc('WebView.reload', WebView.reload);
        registerFunc('WebView.canGoBack', WebView.canGoBack);
        registerFunc('WebView.canGoForward', WebView.canGoForward);
        registerFunc('WebView.goBack', WebView.goBack);
        registerFunc('WebView.goForward', WebView.goForward);
        registerFunc('WebView.setWebViewRect', WebView.setWebViewRect);
        registerFunc('WebView.setVisible', WebView.setVisible);
        registerFunc('WebView.setOpacityWebView', WebView.setOpacityWebView);
        registerFunc('WebView.setBackgroundTransparent', WebView.setBackgroundTransparent);
        registerFunc('WebView.evaluateJS', WebView.evaluateJS);
        registerFunc('WebView.setScalesPageToFit', WebView.setScalesPageToFit);
    }

    private static registerVideoPlay(registerFunc : Function) {
        registerFunc('VideoPlayer.createVideoPlayer', VideoPlayer.createVideoPlayer);
        registerFunc('VideoPlayer.removeVideoPlayer', VideoPlayer.removeVideoPlayer);
        registerFunc('VideoPlayer.setURL', VideoPlayer.setURL);
        registerFunc('VideoPlayer.setLooping', VideoPlayer.setLooping);
        registerFunc('VideoPlayer.setVideoPlayerRect', VideoPlayer.setVideoPlayerRect);
        registerFunc('VideoPlayer.play', VideoPlayer.play);
        registerFunc('VideoPlayer.pause', VideoPlayer.pause);
        registerFunc('VideoPlayer.stop', VideoPlayer.stop);
        registerFunc('VideoPlayer.setVisible', VideoPlayer.setVisible);
        registerFunc('VideoPlayer.requestFullscreen', VideoPlayer.requestFullscreen);
        registerFunc('VideoPlayer.seekTo', VideoPlayer.seekTo);
        registerFunc('VideoPlayer.setKeepAspectRatioEnabled', VideoPlayer.setKeepAspectRatioEnabled);
    }

    private static registerSensor(registerFunc : Function) {
        registerFunc('Accelerometer.enable', Accelerometer.enable);
        registerFunc('Accelerometer.disable', Accelerometer.disable);
    }
}