export class GlobalContext {
  public  static loadGlobalThis(name: string) {
    return globalThis[name]
  }

  public static storeGlobalThis(name: string, obj: Object) {
    globalThis[name] = obj
  }
}

export class GlobalContextConstants {
  static readonly COCOS2DX_EDIT_BOX_ARRAY = "Cocos2dx.editBoxArray";
  static readonly COCOS2DX_EDIT_BOX_INDEX_MAP = "Cocos2dx.editBoxIndexMap";
  static readonly COCOS2DX_COCOS_WORKER = "Cocos2dx.cocosWorker";
  static readonly COCOS2DX_WEB_VIEW_ARRAY = "Cocos2dx.WebViewArray";
  static readonly COCOS2DX_WEB_VIEW_INDEX_MAP = "Cocos2dx.WebViewIndexMap";
  static readonly COCOS2DX_VIDEO_PLAYER_ARRAY = "Cocos2dx.VideoPlayerArray";
  static readonly COCOS2DX_VIDEO_PLAYER_INDEX_MAP = "Cocos2dx.VideoPlayerIndexMap";
  static readonly COCOS2DX_DIALOG_CONTROLLER = "Cocos2dx.dialogController";
  static readonly COCOS2DX_SHOW_MESSAGE = "Cocos2dx.showMessage";

  static readonly COCOS2DX_ABILITY_CONTEXT = "Cocos2dx.abilityContext";
  static readonly COCOS2DX_ABILITY_WANT = "Cocos2dx.abilityWant";
  static readonly COCOS2DX_WEB_RESULT= "Cocos2dx.webResult";
}