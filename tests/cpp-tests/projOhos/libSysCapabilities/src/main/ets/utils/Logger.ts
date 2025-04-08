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