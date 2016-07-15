//
//  etcdec.h
//  cocos2d_libs
//
#ifndef etcdec_h
#define etcdec_h

extern "C" int UnpackETC(const unsigned char* srcETC, int srcFormat, int activeWidth, int activeHeight, unsigned char* dstImage);

#endif /* etcdec_h */
