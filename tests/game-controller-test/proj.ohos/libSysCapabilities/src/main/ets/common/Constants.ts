/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
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