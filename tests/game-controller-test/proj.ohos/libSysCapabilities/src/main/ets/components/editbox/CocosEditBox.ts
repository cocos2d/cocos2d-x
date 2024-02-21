import { Color4B, EditBoxMsgEntity, ViewRect } from '../../entity/WorkerMsgEntity';

export class CocosEditBox {
    static MODULE_NAME : string = 'EditBox';

    private static parentPort;

    static init(parentPort) : void {
        CocosEditBox.parentPort = parentPort;
    }

    static createCocosEditBox(viewTag: number, x: number, y: number, w: number, h: number, paddingW: number, paddingH: number) : void {
        let editBoxMsgEntity: EditBoxMsgEntity = new EditBoxMsgEntity(CocosEditBox.MODULE_NAME, 'createCocosEditBox', viewTag);
        let viewRect: ViewRect = new ViewRect(x, y, w, h);
        editBoxMsgEntity.viewRect = viewRect;
        editBoxMsgEntity.paddingW = paddingW;
        editBoxMsgEntity.paddingH = paddingH;
        CocosEditBox.parentPort.postMessage(editBoxMsgEntity);
    }

    static removeCocosEditBox(viewTag: number) : void {
        let editBoxMsgEntity: EditBoxMsgEntity = new EditBoxMsgEntity(CocosEditBox.MODULE_NAME, 'removeCocosEditBox', viewTag);
        CocosEditBox.parentPort.postMessage(editBoxMsgEntity);
    }

    static setEditBoxViewRect(viewTag: number, x: number, y: number, w: number, h: number) : void {
        let editBoxMsgEntity: EditBoxMsgEntity = new EditBoxMsgEntity(CocosEditBox.MODULE_NAME, 'setEditBoxViewRect', viewTag);
        let viewRect: ViewRect = new ViewRect(x, y, w, h);
        editBoxMsgEntity.viewRect = viewRect;
        CocosEditBox.parentPort.postMessage(editBoxMsgEntity);
    }

    static setEditBoxVisible(viewTag: number, visible: boolean) : void {
        let editBoxMsgEntity: EditBoxMsgEntity = new EditBoxMsgEntity(CocosEditBox.MODULE_NAME, 'setEditBoxVisible', viewTag);
        editBoxMsgEntity.visible = visible;
        CocosEditBox.parentPort.postMessage(editBoxMsgEntity);
    }

    static setCurrentText(viewTag: number, text: string) : void {
        let editBoxMsgEntity: EditBoxMsgEntity = new EditBoxMsgEntity(CocosEditBox.MODULE_NAME, 'setCurrentText', viewTag);
        editBoxMsgEntity.text = text;
        CocosEditBox.parentPort.postMessage(editBoxMsgEntity);
    }

    static setEditBoxFontSize(viewTag: number, size: number) : void {
        let editBoxMsgEntity: EditBoxMsgEntity = new EditBoxMsgEntity(CocosEditBox.MODULE_NAME, 'setEditBoxFontSize', viewTag);
        editBoxMsgEntity.fontSize = size;
        CocosEditBox.parentPort.postMessage(editBoxMsgEntity);
    }

    static setEditBoxFontColor(viewTag: number, r: number, g: number, b: number, a: number) : void {
        let editBoxMsgEntity: EditBoxMsgEntity = new EditBoxMsgEntity(CocosEditBox.MODULE_NAME, 'setEditBoxFontColor', viewTag);
        let color: Color4B = new Color4B(r, g, b, a);
        editBoxMsgEntity.color = color;
        CocosEditBox.parentPort.postMessage(editBoxMsgEntity);
    }

    static setEditBoxPlaceHolderFontColor(viewTag: number, r: number, g: number, b: number, a: number) : void {
        let editBoxMsgEntity: EditBoxMsgEntity = new EditBoxMsgEntity(CocosEditBox.MODULE_NAME, 'setEditBoxPlaceHolderFontColor', viewTag);
        let color: Color4B = new Color4B(r, g, b, a);
        editBoxMsgEntity.placeHolderColor = color;
        CocosEditBox.parentPort.postMessage(editBoxMsgEntity);
    }

    static setEditBoxPlaceHolderFontSize(viewTag: number, size: number) : void {
        let editBoxMsgEntity: EditBoxMsgEntity = new EditBoxMsgEntity(CocosEditBox.MODULE_NAME, 'setEditBoxPlaceHolderFontSize', viewTag);
        editBoxMsgEntity.placeHolderSize = size;
        CocosEditBox.parentPort.postMessage(editBoxMsgEntity);
    }

    static setEditBoxPlaceHolder(viewTag: number, text: string) : void {
        let editBoxMsgEntity: EditBoxMsgEntity = new EditBoxMsgEntity(CocosEditBox.MODULE_NAME, 'setEditBoxPlaceHolder', viewTag);
        editBoxMsgEntity.placeHolderText = text;
        CocosEditBox.parentPort.postMessage(editBoxMsgEntity);
    }

    static setEditBoxMaxLength(viewTag: number, maxLength: number) : void {
        let editBoxMsgEntity: EditBoxMsgEntity = new EditBoxMsgEntity(CocosEditBox.MODULE_NAME, 'setEditBoxMaxLength', viewTag);
        editBoxMsgEntity.maxLength = maxLength;
        CocosEditBox.parentPort.postMessage(editBoxMsgEntity);
    }

    static setNativeInputMode(viewTag: number, inputMode: number) : void {
        let editBoxMsgEntity: EditBoxMsgEntity = new EditBoxMsgEntity(CocosEditBox.MODULE_NAME, 'setNativeInputMode', viewTag);
        editBoxMsgEntity.inputMode = inputMode;
        CocosEditBox.parentPort.postMessage(editBoxMsgEntity);
    }

    static setNativeInputFlag(viewTag: number, inputFlag: number) : void {
        let editBoxMsgEntity: EditBoxMsgEntity = new EditBoxMsgEntity(CocosEditBox.MODULE_NAME, 'setNativeInputFlag', viewTag);
        editBoxMsgEntity.inputFlag = inputFlag;
        CocosEditBox.parentPort.postMessage(editBoxMsgEntity);
    }

    static setEditBoxFontPath(viewTag: number, fontPath: string) : void {
        let editBoxMsgEntity: EditBoxMsgEntity = new EditBoxMsgEntity(CocosEditBox.MODULE_NAME, 'setEditBoxFontPath', viewTag);
        editBoxMsgEntity.fontPath = fontPath;
        CocosEditBox.parentPort.postMessage(editBoxMsgEntity);
    }

    static setEditBoxPlaceHolderFontPath(viewTag: number, fontPath: string) : void {
        let editBoxMsgEntity: EditBoxMsgEntity = new EditBoxMsgEntity(CocosEditBox.MODULE_NAME, 'setEditBoxPlaceHolderFontPath', viewTag);
        editBoxMsgEntity.placeHolderFontPath = fontPath;
        CocosEditBox.parentPort.postMessage(editBoxMsgEntity);
    }

    static hideAllEditBox() : void {
        let editBoxMsgEntity: EditBoxMsgEntity = new EditBoxMsgEntity(CocosEditBox.MODULE_NAME, 'hideAllEditBox');
        CocosEditBox.parentPort.postMessage(editBoxMsgEntity);
    }
}