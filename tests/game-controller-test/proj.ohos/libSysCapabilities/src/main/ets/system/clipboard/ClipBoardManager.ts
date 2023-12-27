import { Result } from "../../entity/Result"
import StringUtils from "../../utils/StringUtils"
import pasteboard from '@ohos.pasteboard';
import Logger from '../../utils/Logger'

let log: Logger = new Logger(0x0001, "ClipBoardManager");

// 剪贴板API是异步的，此处暂时使用规避方式
export default class ClipBoard {

    static  clipBoardData = "";

    static setClipBoardText(content : string) : void{
        var pasteData = pasteboard.createData(pasteboard.MIMETYPE_TEXT_PLAIN, content);
        var systemPasteboard = pasteboard.getSystemPasteboard();
        systemPasteboard.setData(pasteData, (err, data) => {
          if (err) {
            log.error('setClipBoardText : err : %{public}s', JSON.stringify(Result.error(-1, JSON.stringify(err))) ?? '');
            return;
          }
          globalThis.clipBoardUtils.clipBoardData = content;
        });
    }

    static getClipBoardText() : string {
      var text = "";
      var systemPasteboard = pasteboard.getSystemPasteboard();
      systemPasteboard.getData((err, pasteData) => {
        if (err) {
          log.error('getClipBoardText : err : %{public}s', JSON.stringify(Result.error(-1, JSON.stringify(err))) ?? '');
          return "";
        }
        text = pasteData.getPrimaryText();
        if(StringUtils.isNilOrWhitespace(text)){
          text = "";
        }
        globalThis.clipBoardUtils.clipBoardData = text;
      });
      return text;
    }
}
globalThis.clipBoardUtils = {};
globalThis.clipBoardUtils.clipBoardData = ClipBoard.clipBoardData;
