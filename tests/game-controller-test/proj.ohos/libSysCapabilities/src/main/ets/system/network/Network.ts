import wifiManager from '@ohos.wifiManager';
import connection from '@ohos.net.connection';

export default class Network {

    static isWifiConnected() : boolean {
        return wifiManager.isConnected();
    }

    static getNetWorkType() : number {
        let netHandle = connection.getDefaultNetSync();
        if(netHandle && netHandle.netId != 0) {
            // 待SDK更新后，放开下面的代码注释
            // let result = connection.getNetCapabilitiesSync(netHandle);
            // if (result && result.bearerTypes) {
            //     return result.bearerTypes[0];
            // }
        }
        return -1;
    }
}