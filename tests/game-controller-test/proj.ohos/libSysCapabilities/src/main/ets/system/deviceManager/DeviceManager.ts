// import deviceManager from "@ohos.driver.deviceManager";
// import type { BusinessError } from '@ohos.base';
// import rpc from '@ohos.rpc'
//
// export default class DeviceManager {
//
//   QueryingDeviceList() {
//     let matchDevice: deviceManager.USBDevice | null = null;
//     try {
//       let devices: Array<deviceManager.Device> = deviceManager.queryDevices(deviceManager.BusType.USB);
//       for (let item of devices) {
//         let device: deviceManager.USBDevice = item as deviceManager.USBDevice;
//         // 通过productId和vendorId来匹配要使用的USB设备
//         if (device.productId == 1234 && device.vendorId === 2345) {
//           matchDevice = device;
//           break;
//         }
//       }
//     } catch (error) {
//       let errCode = (error as BusinessError).code;
//       let message = (error as BusinessError).message;
//       console.error(`Failed to query device. Code is ${errCode}, message is ${message}`);
//     }
//     if (!matchDevice) {
//       console.error('No match device');
//     }
//   }
//
//   BindCorrespondingDevice() {
//
//     let remoteObject: rpc.IRemoteObject;
//     try {
//       // 12345678为示例deviceId，应用开发时可以通过queryDevices查询到相应设备的deviceId作为入参
//       deviceManager.bindDevice(12345678, (error: BusinessError, data) => {
//         console.error('Device is disconnected');
//       }, (error: BusinessError, data) => {
//         if (error) {
//           console.error(`bindDevice async fail. Code is ${error.code}, message is ${error.message}`);
//           return;
//         }
//         console.info('bindDevice success');
//         remoteObject = data.remote;
//       });
//     } catch (error) {
//       let errCode = (error as BusinessError).code;
//       let message = (error as BusinessError).message;
//       console.error(`bindDevice fail. Code is ${errCode}, message is ${message}`);
//     }
//     if (!remoteObject) {
//       console.error('Bind device failed');
//     }
//   }
//
//   UseDeviceCapability() {
//     let option: rpc.MessageOption = new rpc.MessageOption();
//     let data: rpc.MessageSequence = rpc.MessageSequence.create();
//     let reply: rpc.MessageSequence = rpc.MessageSequence.create();
//     data.writeString('hello');
//     let code = 1;
//     // remoteObject应用可以通过绑定设备获取到
//     let remoteObject: rpc.IRemoteObject;
//     // code和data内容取决于驱动提供的接口
//     remoteObject.sendMessageRequest(code, data, reply, option)
//       .then(() => {
//         console.info('sendMessageRequest finish.');
//       }).catch((error: BusinessError) => {
//       let errCode = (error as BusinessError).code;
//       console.error('sendMessageRequest fail. code:' + errCode);
//     });
//   }
//
//   UnbindingDevice() {
//     try {
//       // 12345678为示例deviceId，应用开发时可以通过queryDevices查询到相应设备的deviceId作为入参
//       deviceManager.unbindDevice(12345678, (error: BusinessError, data) => {
//         if (error) {
//           let errCode = (error as BusinessError).code;
//           let message = (error as BusinessError).message;
//           console.error(`unbindDevice async fail. Code is ${errCode}, message is ${message}`);
//           return;
//         }
//         console.info(`unbindDevice success`);
//       });
//     } catch (error) {
//       let errCode = (error as BusinessError).code;
//       let message = (error as BusinessError).message;
//       console.error(`unbindDevice fail. Code is ${errCode}, message is ${message}`);
//     }
//
//   }
// }
