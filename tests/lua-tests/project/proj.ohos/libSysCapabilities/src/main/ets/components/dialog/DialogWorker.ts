import prompt from '@system.prompt'
import Logger from '../../utils/Logger'
import { GlobalContext,GlobalContextConstants } from "../../common/GlobalContext"
import { TextInputDialogEntity } from '../../entity/TextInputDialogEntity';

let log: Logger = new Logger(0x0001, "Dialog");
export class Dialog {
    static MODULE_NAME : string = 'Dialog';

    static showDialog(message: string, title: string) : void {
        prompt.showDialog({
            title: title,
            message: message,
            buttons: [
                {
                    text: 'OK',
                    color: '#000000'
                },
            ],
            success: function(data) {
                log.debug("handling callback, data:%{public}s", data);
            }
        });
    }

    static showTextInputDialog(message: string) : void {
        let tempShowMessage: TextInputDialogEntity = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_SHOW_MESSAGE);
        tempShowMessage.message = message;
        GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_DIALOG_CONTROLLER).open();

    }

    static hideTextInputDialog() : void {
        let tempShowMessage: TextInputDialogEntity = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_SHOW_MESSAGE);
        tempShowMessage.message =  '';
        GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_DIALOG_CONTROLLER).close();
    }
}
