// 构造单例对象
export class GlobalContext {
  public  static loadGlobalThis(name: string) {
    return globalThis[name]
  }

  public static storeGlobalThis(name: string, obj: Object) {
    globalThis[name] = obj
  }
}

export class GlobalContextConstants {
  static readonly COCOS2DX_ABILITY_CONTEXT = "Cocos2dx.abilityContext";
}