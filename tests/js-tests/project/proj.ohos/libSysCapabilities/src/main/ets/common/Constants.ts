export enum ContextType {
    APP_LIFECYCLE = 0,
    JSPAGE_LIFECYCLE,
    RAW_FILE_UTILS,
    WORKER_INIT,
    NATIVE_API,
    INPUT_NAPI,
    WEBVIEW_NAPI,
    VIDEOPLAYER_NAPI,
    SENSOR_API
}

export class Constants {
    static readonly APP_KEY_WORKER_MANAGER = "app_key_worker_manager";
}

export class AppPermissionConsts {
    static readonly REQUEST_CODE_REQUIRED: number = 1000;

    static readonly REQUEST_CODE_CUSTOM: number = 1001;
}