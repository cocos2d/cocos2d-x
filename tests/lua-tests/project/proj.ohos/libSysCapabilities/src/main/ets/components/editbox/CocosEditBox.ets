import { GlobalContext, GlobalContextConstants } from '../../common/GlobalContext';
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

export class CocosEditBox {
    static MODULE_NAME : string = 'EditBox';

    static createCocosEditBox(viewTag: number, x: number, y: number, w: number, h: number, paddingW: number, paddingH: number) : void {
        let newTextInputInfo = new TextInputInfo(x, y, w, h, paddingW, paddingH, viewTag);
        GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_EDIT_BOX_ARRAY).push(newTextInputInfo);
        GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_EDIT_BOX_INDEX_MAP)
            .set(viewTag, newTextInputInfo);
    }

    static removeCocosEditBox(viewTag: number) : void {
        let removeIndex = -1;
        GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_EDIT_BOX_ARRAY)
            .forEach((item: TextInputInfo, index: number) => {
                if (item.viewTag == viewTag) {
                    removeIndex = index;
                }
            });
        GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_EDIT_BOX_ARRAY).splice(removeIndex, 1);
        GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_EDIT_BOX_INDEX_MAP).delete(viewTag);
    }

    static setEditBoxViewRect(viewTag: number, x: number, y: number, w: number, h: number) : void {
        let textInputInfo: TextInputInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_EDIT_BOX_INDEX_MAP)
            .get(viewTag);
        textInputInfo.x = x;
        textInputInfo.y = y;
        textInputInfo.w = w;
        textInputInfo.h = h;
    }

    static setEditBoxVisible(viewTag: number, visible: boolean) : void {
        let textInputInfo: TextInputInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_EDIT_BOX_INDEX_MAP)
            .get(viewTag);
        textInputInfo.visible = visible;
    }

    static setCurrentText(viewTag: number, text: string) : void {
        let textInputInfo: TextInputInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_EDIT_BOX_INDEX_MAP)
            .get(viewTag);
        textInputInfo.text = text;
    }

    static setEditBoxFontSize(viewTag: number, size: number) : void {
        let textInputInfo: TextInputInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_EDIT_BOX_INDEX_MAP)
            .get(viewTag);
        textInputInfo.fontSize = size;
    }

    static setEditBoxFontColor(viewTag: number, r: number, g: number, b: number, a: number) : void {
        let textInputInfo: TextInputInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_EDIT_BOX_INDEX_MAP)
            .get(viewTag);
        textInputInfo.fontColor = new FontColor(r, g, b, a / 255);
    }

    static setEditBoxPlaceHolderFontColor(viewTag: number, r: number, g: number, b: number, a: number) : void {
        let textInputInfo: TextInputInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_EDIT_BOX_INDEX_MAP)
            .get(viewTag);
        textInputInfo.placeholderFontColor = new FontColor(r, g, b, a / 255);
    }

    static setEditBoxPlaceHolderFontSize(viewTag: number, size: number) : void {
        let textInputInfo: TextInputInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_EDIT_BOX_INDEX_MAP)
            .get(viewTag);
        textInputInfo.placeholderFontSize = size;
    }

    static setEditBoxPlaceHolder(viewTag: number, text: string) : void {
        let textInputInfo: TextInputInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_EDIT_BOX_INDEX_MAP)
            .get(viewTag);
        textInputInfo.placeHolder = text;
    }

    static setEditBoxMaxLength(viewTag: number, maxLength: number) : void {
        let textInputInfo: TextInputInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_EDIT_BOX_INDEX_MAP)
            .get(viewTag);
        textInputInfo.maxLength = maxLength;
    }

    static setNativeInputMode(viewTag: number, inputMode: number) : void {
        let textInputInfo: TextInputInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_EDIT_BOX_INDEX_MAP)
            .get(viewTag);
        textInputInfo.multiline = (inputMode == 0) ? true : false;
        if (textInputInfo.inputMode != InputType.Password) {
            switch (inputMode) {
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
    }

    static setNativeInputFlag(viewTag: number, inputFlag: number) : void {
        // Any type can be changed to a password. The password can be changed to any type,
        // but the password is mapped to the general type. Other changes are not allowed.
        let textInputInfo: TextInputInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_EDIT_BOX_INDEX_MAP)
            .get(viewTag);
        if (inputFlag == 0) {
            textInputInfo.inputMode = InputType.Password;
        } else if (textInputInfo.inputMode == InputType.Password) {
            textInputInfo.inputMode = InputType.Normal;
        }
    }

    static setEditBoxFontPath(viewTag: number, fontPath: string) : void {
        let textInputInfo: TextInputInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_EDIT_BOX_INDEX_MAP)
            .get(viewTag);
        textInputInfo.fontPath = fontPath;
    }

    static setEditBoxPlaceHolderFontPath(viewTag: number, fontPath: string) : void {
        let textInputInfo: TextInputInfo = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_EDIT_BOX_INDEX_MAP)
            .get(viewTag);
        textInputInfo.placeHolderFontPath = fontPath;
    }

    static hideAllEditBox() : void {
        let editBoxArray: TextInputInfo[] = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_EDIT_BOX_ARRAY);
        editBoxArray.forEach(item => {
            if (item.visible) {
                item.visible = false;
                let cocosWorker: worker.ThreadWorker = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_COCOS_WORKER);
                cocosWorker.postMessage({ type: "editBoxOnEnter", viewTag: item.viewTag, text: item.text })
            }
        })
    }
}