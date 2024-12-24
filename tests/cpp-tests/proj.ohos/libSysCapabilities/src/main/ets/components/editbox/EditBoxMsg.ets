import { GlobalContext, GlobalContextConstants } from '../../common/GlobalContext';
import { EditBoxMsgEntity } from '../../entity/WorkerMsgEntity';
import worker from '@ohos.worker';

@Observed
export class TextInputInfo {
  public viewTag: number = 0;
  public x: number = 0;
  public y: number = 0;
  public w: number = 0;
  public h: number = 0;
  public paddingW: number = 0;
  public paddingH: number = 0;
  public fontSize: number = 0;
  public fontColor: FontColor = new FontColor(0, 0, 0, 1);
  public text: string = '';
  public fontPath: string = '';
  public placeholderFontSize: number = 0;
  public placeholderFontColor: FontColor = new FontColor(0, 0, 0, 0.5);
  public placeHolder: string = '';
  public placeHolderFontPath: string = '';
  public maxLength = 256;
  public inputMode = InputType.Normal;
  public visible: boolean = false;
  public multiline: boolean = false;

  constructor(x: number, y: number, w: number, h: number, paddingW: number, paddingH: number, viewTag: number) {
    this.x = x;
    this.y = y;
    this.w = w;
    this.h = h;
    this.paddingW = paddingW;
    this.paddingH = paddingH;
    this.viewTag = viewTag;
  }
}

@Observed
class FontColor {
  public r: number = 0;
  public g: number = 0;
  public b: number = 0;
  public a: number = 1;

  constructor(r: number, g: number, b: number, a: number) {
    this.r = r;
    this.g = g;
    this.b = b;
    this.a = a;
  }
}

export function handleEditBoxMsg(eventData: EditBoxMsgEntity) {
  switch (eventData.function) {
    case "createCocosEditBox": {
      let newTextInputInfo = new TextInputInfo(eventData.viewRect.x, eventData.viewRect.y, eventData.viewRect.w, eventData.viewRect.h, eventData.paddingW, eventData.paddingH, eventData.viewTag);
      GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_EDIT_BOX_ARRAY).push(newTextInputInfo);
      GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_EDIT_BOX_INDEX_MAP)
        .set(eventData.viewTag, newTextInputInfo);
      break;
    }
    case "removeCocosEditBox": {
      let removeIndex = -1;
      GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_EDIT_BOX_ARRAY)
        .forEach((item: TextInputInfo, index: number) => {
          if (item.viewTag == eventData.viewTag) {
            removeIndex = index;
          }
        });
      GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_EDIT_BOX_ARRAY).splice(removeIndex, 1);
      GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_EDIT_BOX_INDEX_MAP).delete(eventData.viewTag);
      break;
    }
    case "setCurrentText": {
      let textInputInfo: TextInputInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_EDIT_BOX_INDEX_MAP)
        .get(eventData.viewTag);
      textInputInfo.text = eventData.text;
      break;
    }
    case "setEditBoxViewRect": {
      let textInputInfo: TextInputInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_EDIT_BOX_INDEX_MAP)
        .get(eventData.viewTag);
      textInputInfo.x = eventData.viewRect.x;
      textInputInfo.y = eventData.viewRect.y;
      textInputInfo.w = eventData.viewRect.w;
      textInputInfo.h = eventData.viewRect.h;
      break;
    }
    case "setEditBoxVisible": {
      let textInputInfo: TextInputInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_EDIT_BOX_INDEX_MAP)
        .get(eventData.viewTag);
      textInputInfo.visible = eventData.visible;
      break;
    }
    case "setEditBoxFontSize": {
      let textInputInfo: TextInputInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_EDIT_BOX_INDEX_MAP)
        .get(eventData.viewTag);
      textInputInfo.fontSize = eventData.fontSize;
      break;
    }
    case "setEditBoxFontColor": {
      let textInputInfo: TextInputInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_EDIT_BOX_INDEX_MAP)
        .get(eventData.viewTag);
      textInputInfo.fontColor = new FontColor(eventData.color.r, eventData.color.g, eventData.color.b, eventData.color.a / 255);
      break;
    }
    case "setEditBoxPlaceHolderFontSize": {
      let textInputInfo: TextInputInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_EDIT_BOX_INDEX_MAP)
        .get(eventData.viewTag);
      textInputInfo.placeholderFontSize = eventData.placeHolderSize;
      break;
    }
    case "setEditBoxPlaceHolderFontColor": {
      let textInputInfo: TextInputInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_EDIT_BOX_INDEX_MAP)
        .get(eventData.viewTag);
      textInputInfo.placeholderFontColor = new FontColor(eventData.placeHolderColor.r, eventData.placeHolderColor.g, eventData.placeHolderColor.b, eventData.placeHolderColor.a / 255);
      break;
    }
    case "setEditBoxPlaceHolder": {
      let textInputInfo: TextInputInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_EDIT_BOX_INDEX_MAP)
        .get(eventData.viewTag);
      textInputInfo.placeHolder = eventData.placeHolderText;
      break;
    }
    case "setEditBoxMaxLength": {
      let textInputInfo: TextInputInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_EDIT_BOX_INDEX_MAP)
        .get(eventData.viewTag);
      textInputInfo.maxLength = eventData.maxLength;
      break;
    }
    case "setNativeInputMode": {
      let textInputInfo: TextInputInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_EDIT_BOX_INDEX_MAP)
        .get(eventData.viewTag);
      textInputInfo.multiline = (eventData.inputMode == 0) ? true : false;
      if (textInputInfo.inputMode != InputType.Password) {
        switch (eventData.inputMode) {
          case 0:
          case 4:
          case 6:
            textInputInfo.inputMode = InputType.Normal;
            break;
          case 2:
          case 5:
            textInputInfo.inputMode = InputType.Number;
            break;
          case 3:
            textInputInfo.inputMode = InputType.PhoneNumber;
            break;
          case 1:
            textInputInfo.inputMode = InputType.Email;
            break;
          default:
            break;
        }
      }
      break;
    }
    case "setNativeInputFlag": {
      // Any type can be changed to a password. The password can be changed to any type,
      // but the password is mapped to the general type. Other changes are not allowed.
      let textInputInfo: TextInputInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_EDIT_BOX_INDEX_MAP)
        .get(eventData.viewTag);
      if (eventData.inputFlag == 0) {
        textInputInfo.inputMode = InputType.Password;
      } else if (textInputInfo.inputMode == InputType.Password) {
        textInputInfo.inputMode = InputType.Normal;
      }
      break;
    }
    case "setEditBoxFontPath": {
      let textInputInfo: TextInputInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_EDIT_BOX_INDEX_MAP)
        .get(eventData.viewTag);
      textInputInfo.fontPath = eventData.fontPath;
      break;
    }
    case "setEditBoxPlaceHolderFontPath": {
      let textInputInfo: TextInputInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_EDIT_BOX_INDEX_MAP)
        .get(eventData.viewTag);
      textInputInfo.placeHolderFontPath = eventData.placeHolderFontPath;
      break;
    }
    case "hideAllEditBox": {
      let editBoxArray: TextInputInfo[] = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_EDIT_BOX_ARRAY);
      editBoxArray.forEach(item => {
        if (item.visible) {
          item.visible = false;
          let cocosWorker: worker.ThreadWorker = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_COCOS_WORKER);
          cocosWorker.postMessage({ type: "editBoxOnEnter", viewTag: item.viewTag, text: item.text })
        }
      })
      break;
    }
  }
}
