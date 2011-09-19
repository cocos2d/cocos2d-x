/*
 * WavHead.h
 *
 *  Created on: 2011-1-21
 *      Author: Administrator
 */

#ifndef WAVHEAD_H_
#define WAVHEAD_H_

#include <stdio.h>
/* WAVE文件头 */

typedef struct wave_tag

{

    char              ChunkID[5]; // "RIFF"标志

    unsigned long int ChunkSize;  // 文件长度(WAVE文件的大小, 不含前8个字节)

    char              Format[5];  // "WAVE"标志



    char              SubChunk1ID[5];// "fmt "标志

    unsigned long int SubChunk1Size; /*

                                    * 过渡字节(不定)

                                    * 16 for PCM. This is the size of the rest of the

                                    * Subchunk which follows this number.

                                    */

    unsigned short int   AudioFormat;  /*

                                    * 格式类别(10H为PCM格式的声音数据)

                                    * PCM=1 (i.e. Linear quantization)

                                    * Values other than 1 indicate some form of compression.

                                    */

    unsigned short int   NumChannels;  // 通道数(单声道为1, 双声道为2)

    //unsigned short int SampleRate;       // 采样率(每秒样本数), 表示每个通道的播放速度

    unsigned long int    SampleRate;       // 采样率(每秒样本数), 表示每个通道的播放速度

    unsigned long int    ByteRate;     /*

                                     * 波形音频数据传输速率, 其值为:通道数*每秒数据位数*每样本的数据位数/8

                                     * 播放软件可以利用该值估计缓冲区大小

                                     */

    unsigned short int   BlockAlign;       /*

                                      * 每样本的数据位数(按字节算), 其值为:通道数*每样本的数据位值/8， 播放

                                     * 软件需要一次处理多个该值大小的字节数据, 以便将其值用于缓冲区的调整

                                     */

    unsigned short int   BitsPerSample;    /*

                                    * 每样本的数据位数, 表示每个声道中各个样本的数据位数. 如果有多个声道,

                                    * 对每个声道而言, 样本大小都一样

                                    */



    char              SubChunk2ID[5];   // 数据标记"data"

    unsigned long int SubChunk2Size;    // 语音数据的长度

} WAVE;

/*
 * pBuffer内部申请空间，需要由外部释放
 */

bool GetWaveHeadInfo(FILE*stream, WAVE& outWavHead);

#endif /* WAVHEAD_H_ */
