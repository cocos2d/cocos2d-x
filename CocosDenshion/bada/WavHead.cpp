/*
 * WaveHead.cpp
 *
 *  Created on: 2011-1-21
 *      Author: Administrator
 */

#include "WavHead.h"
#include <stdio.h>
#include <FBaseSys.h>

bool GetWaveHeadInfo(FILE*stream, WAVE& outWavHead)
{
	char szTmp[100] = {0};
	int i = 0;

//    FILE   *stream;

//	if((stream = fopen(fileName,"rb"))==NULL)
//	{
//		AppLog("ERROR:can't   open   the   file!");
//
//		return false;
//	}
    /*

     * 读wav文件的各个field

     */

    fread(outWavHead.ChunkID, 4, 1, stream);

    outWavHead.ChunkID[4] = (char)0;

    fread(&(outWavHead.ChunkSize),4, 1, stream);

    fread(outWavHead.Format, 4, 1, stream);

    outWavHead.Format[4] = (char)0;

    fread(outWavHead.SubChunk1ID, 4, 1, stream);

    outWavHead.SubChunk1ID[4] = (char)0;

    fread(&(outWavHead.SubChunk1Size), 4, 1, stream);

    fread(&(outWavHead.AudioFormat),   2, 1, stream);

    fread(&(outWavHead.NumChannels),   2, 1, stream);

    fread(&(outWavHead.SampleRate), 4, 1, stream);

    fread(&(outWavHead.ByteRate),      4, 1, stream);

    fread(&(outWavHead.BlockAlign), 2, 1, stream);

    fread(&(outWavHead.BitsPerSample), 2, 1, stream);

	fseek(stream, 0, SEEK_SET);


	fread(szTmp, 64, 1, stream);

	for (i = 0; i <= 60; i++)
	{
		if (szTmp[i] == 'd' && szTmp[i+1] == 'a' && szTmp[i+2] == 't' && szTmp[i+3] == 'a')
		{
			break;
		}
	}

	fseek(stream, i, SEEK_SET);

    fread(outWavHead.SubChunk2ID,      4, 1, stream);

     outWavHead.SubChunk2ID[4] = (char)0;

     fread(&(outWavHead.SubChunk2Size), 4, 1, stream);

     return true;
}
