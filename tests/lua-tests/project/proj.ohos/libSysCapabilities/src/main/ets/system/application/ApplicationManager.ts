import process from '@ohos.process';
import bundleManager from '@ohos.bundle.bundleManager';

export default class ApplicationManager {
    static pro = new process.ProcessManager();

    static exit() : void {
        ApplicationManager.pro.exit(0);
    }

    static getVersionName() : string {
        let bundleFlags = bundleManager.BundleFlag.GET_BUNDLE_INFO_DEFAULT;
        return bundleManager.getBundleInfoForSelfSync(bundleFlags).versionName;
    }
}