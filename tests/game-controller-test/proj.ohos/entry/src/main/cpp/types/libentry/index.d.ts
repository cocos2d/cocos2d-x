import resmgr from '@ohos.resourceManager';

export interface CPPFunctions {
  onCreate: () => void;
  onShow: () => void;
  onHide: () => void;
  onBackPress: () => void;
  onDestroy: () => void;
  onPageShow: () => void;
  onPageHide: () => void;
  nativeResourceManagerInit: (resourceManager: resmgr.ResourceManager) => void;
  writablePathInit: (writePath: string) => void;
  workerInit: () => void;
  nativeEngineStart: () => void;
  registerFunction: () => void;
  initAsyncInfo: () => void;
  editBoxOnChangeCB: (viewTag: number, text: string) => void;
  editBoxOnEnterCB: (viewTag: number, text: string) => void;
  textFieldTTFOnChangeCB: (text: string) => void;
  shouldStartLoading: (viewTag: number, url: string) => void;
  finishLoading: (viewTag: number, url: string) => void;
  failLoading: (viewTag: number, url: string) => void;
  jsCallback: () => void;
  onVideoCallBack: (viewTag: number, event: number) => void;
}

export const getContext: (a: number) => CPPFunctions;
export const getSDKContext: (a: number) => CPPFunctions;