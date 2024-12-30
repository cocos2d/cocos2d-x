import prompt from '@system.prompt'
import Logger from '../../utils/Logger'
import { GlobalContext,GlobalContextConstants } from "../../common/GlobalContext"
import { TextInputDialogEntity } from '../../entity/TextInputDialogEntity';
import { DialogMsgEntity } from '../../entity/WorkerMsgEntity';


let log: Logger = new Logger(0x0001, "DialogMsg");

export function handleDialogMsg(eventData: DialogMsgEntity) : void {
    switch (eventData.function) {
        case "showDialog": {
            let title = eventData.title;
            let message = eventData.message;
            showDialog(title, message);
            break;
        }
        case "showTextInputDialog": {
            let tempShowMessage: TextInputDialogEntity = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_SHOW_MESSAGE);
            tempShowMessage.message = eventData.message;
            GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_DIALOG_CONTROLLER).open();
            break;
        }
        case "hideTextInputDialog": {
            let tempShowMessage: TextInputDialogEntity = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_SHOW_MESSAGE);
            tempShowMessage.message =  '';
            GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_DIALOG_CONTROLLER).close();
            break;
        }
    }
}

function showDialog(dialogTitle: string, dialogMessage: string) {
    prompt.showDialog({
        title: dialogTitle,
        message: dialogMessage,
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
