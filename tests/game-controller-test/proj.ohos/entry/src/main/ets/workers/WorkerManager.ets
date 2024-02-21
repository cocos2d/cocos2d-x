/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import worker from '@ohos.worker';
import { Constants } from '@ohos/libSysCapabilities';

export class WorkerManager {
  private cocosWorker: worker.ThreadWorker;

  private constructor() {
    this.cocosWorker = new worker.ThreadWorker("/entry/ets/workers/CocosWorker.ts", {
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