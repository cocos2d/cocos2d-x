#ifndef __HELLOWORLDUNICODESCRIPT_STR_H__
#define __HELLOWORLDUNICODESCRIPT_STR_H__


#define AppName_HelloWorld__N \
    "H\x00\x65\x00l\x00l\x00o\x00W\x00o\x00r\x00l\x00\x64\x00"
#define AppName_HelloWorld__C \
    AppName_HelloWorld__N"\x00\x00"
#define AppName_HelloWorld \
    ((const unsigned short *)(AppName_HelloWorld__C))
#define AppName_HelloWorld__N16 \
    0x0048,0x0065,0x006c,0x006c,0x006f,0x0057,0x006f,0x0072,0x006c,0x0064
#define AppName_HelloWorld_16 \
    {AppName_HelloWorld__N16,0x0000}
// 原始串信息：
// HelloWorld


#endif  //__HELLOWORLDUNICODESCRIPT_STR_H__
