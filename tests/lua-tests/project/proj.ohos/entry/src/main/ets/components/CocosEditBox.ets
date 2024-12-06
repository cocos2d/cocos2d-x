import { TextInputInfo } from '@ohos/libSysCapabilities/src/main/ets/components/editbox/EditBoxMsg'
import worker from '@ohos.worker';
import { WorkerManager } from '../workers/WorkerManager';

@Component
export struct CocosEditBox {
  @ObjectLink textInputInfo: TextInputInfo;
  cocosWorker: worker.ThreadWorker = WorkerManager.getInstance().getWorker();

  build(){
    if(this.textInputInfo.multiline){
      TextArea({text: this.textInputInfo.text, placeholder: this.textInputInfo.placeHolder})
        .id('TextArea'+this.textInputInfo.viewTag)
        .position({x: px2vp(this.textInputInfo.x), y: px2vp(this.textInputInfo.y)})
        .size({width: px2vp(this.textInputInfo.w), height: px2vp(this.textInputInfo.h)})
        .padding({top: px2vp(this.textInputInfo.paddingH), right: px2vp(this.textInputInfo.paddingW),
          bottom: px2vp(this.textInputInfo.paddingH), left: px2vp(this.textInputInfo.paddingW)})
        .borderRadius(0)
        .maxLength(this.textInputInfo.maxLength)
        .type(TextAreaType.NORMAL)
        .fontFamily($rawfile(this.textInputInfo.fontPath))
        .fontSize(px2fp(this.textInputInfo.fontSize))
        .fontColor(`rgba(${this.textInputInfo.fontColor.r}, ${this.textInputInfo.fontColor.g}, ${this.textInputInfo.fontColor.b}, ${this.textInputInfo.fontColor.a})`)
        .placeholderFont({size: px2fp(this.textInputInfo.placeholderFontSize), family: $rawfile(this.textInputInfo.placeHolderFontPath)})
        .placeholderColor(`rgba(${this.textInputInfo.placeholderFontColor.r}, ${this.textInputInfo.placeholderFontColor.g}, ${this.textInputInfo.placeholderFontColor.b}, ${this.textInputInfo.placeholderFontColor.a})`)
        .backgroundColor(Color.Transparent)
        .visibility(this.textInputInfo.visible ? Visibility.Visible : Visibility.None)
        .onVisibleAreaChange([0.0, 1.0], () => {
          focusControl.requestFocus('TextArea' + this.textInputInfo.viewTag);
        })
        .onFocus(() => {
          this.cocosWorker.postMessage({type: "editBoxOnFocus", viewTag: this.textInputInfo.viewTag});
        })
        .onChange((value: string)=>{
          this.textInputInfo.text = value;
          this.cocosWorker.postMessage({type: "editBoxOnChange", viewTag: this.textInputInfo.viewTag, value: value});
        })
        .onBlur(()=> {
          this.textInputInfo.visible = false
          this.cocosWorker.postMessage({type: "editBoxOnEnter", viewTag: this.textInputInfo.viewTag, text: this.textInputInfo.text});
        })
        .onSubmit(()=>{
          this.cocosWorker.postMessage({type: "editBoxOnEnter", viewTag: this.textInputInfo.viewTag, text: this.textInputInfo.text});
        })
    }else{
      TextInput({text: this.textInputInfo.text, placeholder: this.textInputInfo.placeHolder})
        .id('TextInput'+this.textInputInfo.viewTag)
        .position({x: px2vp(this.textInputInfo.x), y: px2vp(this.textInputInfo.y)})
        .size({width: px2vp(this.textInputInfo.w), height: px2vp(this.textInputInfo.h)})
        .padding({top: px2vp(this.textInputInfo.paddingH), right: px2vp(this.textInputInfo.paddingW),
          bottom: px2vp(this.textInputInfo.paddingH), left: px2vp(this.textInputInfo.paddingW)})
        .borderRadius(0)
        .maxLength(this.textInputInfo.maxLength)
        .type(this.textInputInfo.inputMode)
        .fontFamily($rawfile(this.textInputInfo.fontPath))
        .fontSize(px2fp(this.textInputInfo.fontSize))
        .fontColor(`rgba(${this.textInputInfo.fontColor.r}, ${this.textInputInfo.fontColor.g}, ${this.textInputInfo.fontColor.b}, ${this.textInputInfo.fontColor.a})`)
        .placeholderFont({size: px2fp(this.textInputInfo.placeholderFontSize), family: $rawfile(this.textInputInfo.placeHolderFontPath)})
        .placeholderColor(`rgba(${this.textInputInfo.placeholderFontColor.r}, ${this.textInputInfo.placeholderFontColor.g}, ${this.textInputInfo.placeholderFontColor.b}, ${this.textInputInfo.placeholderFontColor.a})`)
        .backgroundColor(Color.Transparent)
        .visibility(this.textInputInfo.visible ? Visibility.Visible : Visibility.None)
        .showPasswordIcon(false)
        .onVisibleAreaChange([0.0, 1.0], () => {
          focusControl.requestFocus('TextInput' + this.textInputInfo.viewTag);
        })
        .onFocus(() => {
          this.cocosWorker.postMessage({type: "editBoxOnFocus", viewTag: this.textInputInfo.viewTag});
        })
        .onChange((value: string)=>{
          this.textInputInfo.text = value;
          this.cocosWorker.postMessage({type: "editBoxOnChange", viewTag: this.textInputInfo.viewTag, value: value});
        })
        .onBlur(()=> {
          this.textInputInfo.visible = false
          this.cocosWorker.postMessage({type: "editBoxOnEnter", viewTag: this.textInputInfo.viewTag, text: this.textInputInfo.text});
        })
        .onSubmit(()=>{
          this.cocosWorker.postMessage({type: "editBoxOnEnter", viewTag: this.textInputInfo.viewTag, text: this.textInputInfo.text});
        })
    }
  }
}
