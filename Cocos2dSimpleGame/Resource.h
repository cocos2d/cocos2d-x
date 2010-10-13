#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include "SimpleAudioEngine/SimpleAudioEngine.h"
#include "cocos2dsimplegame_res_def.h"
#include "cocos2d.h"

using namespace cocos2d;

const T_ImageResInfo ResInfo[] =
{
    { "CloseNormal",    COCOS2_ID_BITMAP_CloseNormal },
    { "CloseSelected",  COCOS2_ID_BITMAP_CloseSelected },
    { "Player",         COCOS2_ID_BITMAP_Player },
    { "Projectile",     COCOS2_ID_BITMAP_Projectile },
    { "Target",         COCOS2_ID_BITMAP_Target },
};

/**
@warning 在声音数据信息的结构体中，FileName必须包含文件的扩展名，并且需要与原始文件的扩展名一致
         否则无法播放
*/
const T_SoundResInfo SoundResInfo[] =
{
    { "background-music-aac.mp3",     COCOS2_ID_RAWDATA_background_music_aac },
    { "pew-pew-lei.wav",              COCOS2_ID_RAWDATA_pew_pew_lei },
};

#endif
