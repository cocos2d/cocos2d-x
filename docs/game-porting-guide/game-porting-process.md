# 游戏移植流程简介

游戏移植步骤主要可分为以下几步：

1、准备OpenHarmony的开发环境，包括DevEco Studio、SDK、NDK以及开发板；

2、梳理出引擎最小化移植需要的依赖，在这一步建议先将引擎自带的cpp-empty-test工程作为移植目标，确保引擎能够在OpnHarmony平台上运行成功后，再通过移植cpp-test工程来进一步识别引擎对三方库、系统能力的依赖，从而完成引擎最小功能的移植；

3、若游戏有使用到JS或Lua脚本语言，可在步骤2的基础上移植js-empty-test/lua-empty-test以及js-test/lua-test工程，重点关注使用到的三方库的移植（如luaJit、SpiderMonkey）；

4、完成上述步骤后，引擎最小集功能移植已完成，可以开始适配游戏的业务逻辑。