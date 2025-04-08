import worker from '@ohos.worker';
import { Constants } from '@ohos/libSysCapabilities';

export class WorkerManager {
  private cocosWorker: worker.ThreadWorker;

  private constructor() {
    this.cocosWorker = new worker.ThreadWorker("entry/ets/workers/CocosWorker.ts", {
      type: "classic",
      name: "CocosWorker"
    });
    this.cocosWorker.onerror = (e) => {
      let msg = e.message;
      let filename = e.filename;
      let lineno = e.lineno;
      let colno = e.colno;
      console.error(`on Error ${msg} ${filename} ${lineno} ${colno}`);
    }
  }

  public static getInstance(): WorkerManager {
    let workerManger: WorkerManager | undefined = AppStorage.get<WorkerManager>(Constants.APP_KEY_WORKER_MANAGER);
    if (workerManger == undefined) {
      workerManger = new WorkerManager;
      AppStorage.setOrCreate(Constants.APP_KEY_WORKER_MANAGER, workerManger);
      return workerManger;
    }
    return workerManger;
  }

  public getWorker(): worker.ThreadWorker {
    return this.cocosWorker;
  }
}