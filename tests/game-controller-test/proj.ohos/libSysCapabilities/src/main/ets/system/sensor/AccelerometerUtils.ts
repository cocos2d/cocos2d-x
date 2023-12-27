import { getContext } from "libnativerender.so";
import { ContextType } from "../../common/Constants"
import sensor from '@ohos.sensor';
import display from '@ohos.display';
import {Result} from "../../entity/Result"
import Logger from '../../utils/Logger'

let log: Logger = new Logger(0x0001, "AccelerometerUtils");

const accUtils = getContext(ContextType.SENSOR_API);

export default class Accelerometer {

    private static instance = new Accelerometer();

    static getInstance() : Accelerometer {
        return Accelerometer.instance;
    }

    static enable(intervalTime: number) : void {
        try {
            /* HarmonyOS allow multiple subscriptions, but the game only need one
             so if the interval changed, cancel subscription and redo with the new interval */
            sensor.off(sensor.SensorId.ACCELEROMETER);
            sensor.on(sensor.SensorId.ACCELEROMETER, function (data) {
                let rotation = display.getDefaultDisplaySync().rotation;
                if (rotation === 0) {
                    // 显示设备屏幕旋转为0°
                    accUtils.onAccelerometerCallBack(data.x, data.y, data.z, intervalTime);
                } else if (rotation === 1) {
                    // 显示设备屏幕旋转为90°
                    accUtils.onAccelerometerCallBack(data.y, -data.x, data.z, intervalTime);
                } else if (rotation === 2) {
                    // 显示设备屏幕旋转为180°
                    accUtils.onAccelerometerCallBack(-data.x, -data.y, data.z, intervalTime);
                } else if (rotation === 3) {
                     // 显示设备屏幕旋转为270°
                     accUtils.onAccelerometerCallBack(-data.y, data.x, data.z, intervalTime);
                } else {
                    log.error('Accelerometer init fail, err: %{public}s', JSON.stringify(Result.error(-1, 'unsupported rotation: ' + rotation)));
                }
            }, { interval: intervalTime });
        } catch (err) {
            log.error('Accelerometer init fail,  err: %{public}s', JSON.stringify(Result.error(-1, JSON.stringify(err))) ?? '');
        }
    }

    static disable() : void {
        try {
            sensor.off(sensor.SensorId.ACCELEROMETER);
        } catch (err) {
            log.error('Accelerometer off fail,  err: %{public}s', JSON.stringify(Result.error(-1, JSON.stringify(err))) ?? '');
        }
    }
}