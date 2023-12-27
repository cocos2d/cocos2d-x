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

/**
 * @file 日期工具
 */
export default class DateTimeUtil {

  /**
   * 时分秒
   */
  getTime() {
    const DATETIME = new Date()
    return this.concatTime(DATETIME.getHours(), DATETIME.getMinutes(), DATETIME.getSeconds())
  }

  /**
   * 年月日
   */
  getDate() {
    const DATETIME = new Date()
    return this.concatDate(DATETIME.getFullYear(), DATETIME.getMonth() + 1, DATETIME.getDate())
  }

  /**
   * 日期不足两位补充0
   * @param value-数据值
   */
  fill(value: number) {
    return (value > 9 ? '' : '0') + value
  }

  /**
   * 年月日格式修饰
   * @param year
   * @param month
   * @param date
   */
  concatDate(year: number, month: number, date: number) {
    return `${year}${this.fill(month)}${this.fill(date)}`
  }

  /**
   * 时分秒格式修饰
   * @param hours
   * @param minutes
   * @param seconds
   */
  concatTime(hours: number, minutes: number, seconds: number) {
    return `${this.fill(hours)}${this.fill(minutes)}${this.fill(seconds)}`
  }
}