import measure from '@ohos.measure';

export default class StringUtils {

    public static getWidth(text: string, fontSize: number, fontWeight: number): number {
        return measure.measureText({ textContent: text, fontSize: fontSize + 'px', fontWeight: fontWeight });
    }
}