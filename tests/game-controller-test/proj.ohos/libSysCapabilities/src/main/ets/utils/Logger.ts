/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
import hilog from '@ohos.hilog'

export default class Logger {
  private domain: number
  private prefix: string

  constructor(domain : number, prefix: string) {
    this.domain = domain
    this.prefix = prefix
  }

  debug(format: string, ...args: any[]) {
    hilog.debug(this.domain, this.prefix, format, args)
  }

  info(format: string, ...args: any[]) {
    hilog.info(this.domain, this.prefix, format, args)
  }

  warn(format: string, ...args: any[]) {
    hilog.warn(this.domain, this.prefix, format, args)
  }

  error(format: string, ...args: any[]) {
    hilog.error(this.domain, this.prefix, format, args)
  }
}