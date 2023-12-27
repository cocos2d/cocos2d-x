import common from '@ohos.app.ability.common';
import abilityAccessCtrl, { Permissions } from '@ohos.abilityAccessCtrl';
import picker from '@ohos.file.picker';
import fs from '@ohos.file.fs';
import image from '@ohos.multimedia.image';
import promptAction from '@ohos.promptAction';
import Logger from '../../utils/Logger';
import { GlobalContext, GlobalContextConstants } from '../../common/GlobalContext';
import { BusinessError } from '@ohos.base';
import worker from '@ohos.worker';

let log: Logger = new Logger(0x0001, "ImagePicker");

export function openImagePicker(pWidth: number, pHeight: number): void {
  let permissionNames: Array<Permissions> = ['ohos.permission.WRITE_MEDIA', 'ohos.permission.READ_MEDIA', 'ohos.permission.CAMERA'];
  let atManager: abilityAccessCtrl.AtManager = abilityAccessCtrl.createAtManager();
  try {
    atManager.requestPermissionsFromUser(GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_ABILITY_CONTEXT), permissionNames)
      .then((data) => {
        if (!grantFlag(data.authResults)) {
          promptAction.showToast({
            message: '请前往"设置->隐私->权限管理"进行授权'
          })
          return;
        }
        //同意权限打开相册选择图片
        const photoSelectOptions = new picker.PhotoSelectOptions();
        photoSelectOptions.MIMEType = picker.PhotoViewMIMETypes.IMAGE_TYPE; // 过滤选择媒体文件类型为IMAGE
        photoSelectOptions.maxSelectNumber = 1; // 选择媒体文件的最大数目
        const photoPicker = new picker.PhotoViewPicker();
        photoPicker.select(photoSelectOptions)
          .then(async (photoSelectResult) => {
            setTimeout(() => {
              if (!photoSelectResult || !photoSelectResult.photoUris || photoSelectResult.photoUris.length < 1) {
                return;
              }
              // 获取到图片或者视频文件的URI后进行文件读取等操作
              let uri = photoSelectResult.photoUris[0];
              // 处理压缩照片，上传接口只支持internal格式，将datashare格式转换为internal格式
              handleImage(uri, pWidth, pHeight);
            }, 500);
          })
          .catch((err: BusinessError) => {
            log.error(`Failed to photoPicker.select. Code: ${err.code}, message: ${err.message}`);
          })
      })
      .catch((err: BusinessError) => {
        log.error(`Failed to request permissions from user.select. err: ${JSON.stringify(err)}`);
      })
  } catch (err) {
    let e: BusinessError = err as BusinessError;
    log.error(`catch err->${JSON.stringify(e)}`);
  }
}

function handleImage(uri: string, pWidth: number, pHeight: number): void {
  let context: common.UIAbilityContext = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_ABILITY_CONTEXT);
  let cacheDir = context.cacheDir;
  let srcFile: fs.File | undefined = undefined;
  let destFile: fs.File | undefined = undefined;
  try {
    srcFile = fs.openSync(uri, fs.OpenMode.READ_WRITE);
    // 解码压缩
    let imageSource: image.ImageSource = image.createImageSource(srcFile.fd);
    let decodingOptions: image.DecodingOptions = {
      sampleSize: 1,
      desiredSize: {
        height: pHeight,
        width: pWidth
      }
    };

    imageSource.createPixelMap(decodingOptions).then(async (pixelMap) => {
      const imagePackerApi = image.createImagePacker();
      let packOpts: image.PackingOption = { format: "image/jpeg", quality: 75 };
      imagePackerApi.packing(pixelMap, packOpts).then(data => {
        // data 为打包获取到的文件流，写入文件保存即可得到一张图片
        let imagePath: string = `${cacheDir}/${new Date().getTime().toString()}.jpg`
        destFile = fs.openSync(imagePath, fs.OpenMode.READ_WRITE | fs.OpenMode.CREATE);
        fs.writeSync(destFile.fd, data);
        let cocosWorker: worker.ThreadWorker = GlobalContext.loadGlobalThis(GlobalContextConstants.COCOS2DX_COCOS_WORKER);
        cocosWorker.postMessage({ type: "setImagePickerResult", imagePath: imagePath });
      }).catch((error: BusinessError) => {
        log.error('Failed to pack the image. And the error is: ' + error);
      })
    });
  } catch (err) {
    let e: BusinessError = err as BusinessError;
    log.error('Failed to showImagePicker : err : %{public}s', JSON.stringify(e));
  } finally {
    if (srcFile) {
      fs.closeSync(srcFile);
    }
    if (destFile) {
      fs.closeSync(destFile);
    }
  }
}

function grantFlag(grantStatus: Array<number>): Boolean {
  let length: number = grantStatus.length;
  let grantFlag: Boolean = true;
  for (let i = 0;i < length; i++) {
    if (grantStatus[i] != 0) {
      grantFlag = false;
    }
  }
  return grantFlag;
}