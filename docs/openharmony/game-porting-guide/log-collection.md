# 日志收集
## HiLog日志系统
HiLog是OpenHarmony的日志系统—，提供给系统框架、服务、以及应用打印日志，记录用户操作、系统运行状态等。
> 关于HiLog的api参考与代码demo，参阅OpenHarmony [HiLog开发指导（Native）](https://gitee.com/openharmony/docs/blob/master/zh-cn/application-dev/dfx/hilog-guidelines.md)

## 查看日志
### 在DevEco Studio IDE中查看日志

1. 调试设备连接上个人电脑，点击Run->Run...，成功后应用运行于调试设备上。

2. 点击ide下方的Log标签页，ide自动抓取HiLog并显示在窗口中。
![img](在IDE中查看日志.png)

### 在命令行中查看日志

1. 调试设备连接上个人电脑

2. 利用hdc命令行工具，在命令行窗口中输入命令即可显示大量日志：`hdc shell hilog`

#### 通过hilog命令行工具来过滤保留当前应用的日志日志。

hilog -T xxx 按tag过滤;

hilog –D xxx 按domain过滤;

hilog -e 对日志内容匹配，支持正则式tag, domain, pid都支持多重过滤,组合过滤以及反向过滤。

更多hilog命令行工具[常见问题](https://gitee.com/openharmony/docs/blob/master/zh-cn/application-dev/faqs/faqs-dfx.md)