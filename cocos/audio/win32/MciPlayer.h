#ifndef _MCI_PLAYER_WIN32_H_
#define _MCI_PLAYER_WIN32_H_

#include "CCStdC.h"
#include <mmsystem.h>
#include "oae.h"
#include <string>

namespace CocosDenshion {

class MciPlayer
{
public:
    MciPlayer();
    ~MciPlayer();

    void Close();

    /**
    @brief ���������ļ�
    @param pFileName ���ŵ������ļ����ƣ���Ҫ�����ļ���·��
    @param nTimes    ���������ļ���ѭ��������Ĭ��ֵΪ 1��������һ��
    */
    void Open(const char* pFileName, UINT uId);

    void Play(UINT uTimes = 1);

    /**
    @brief ��ͣ��������
    */
    void Pause();

    /**
    @brief ������������
    */
    void Resume();

    /**
    @brief ֹͣ��������
    */
    void Stop();

    /**
    @brief ���²���
    */
    void Rewind();

    /**
    @brief ��ȡ��������ǰ�Ƿ����ڲ�����
    */
    bool IsPlaying();


    /**
    @brief ��ȡ��ǰ���ŵ���Ч ID
    @return ��ǰ���ŵ���ЧID
    */
    UINT GetSoundID();
public:
	static oae::Renderer* dev;
	static HMODULE lib;

	std::string m_strFileName;
	oae::Screamer* m_scr;

	UINT        m_nSoundID;
    UINT        m_uTimes;
};

} // end of namespace CocosDenshion

#endif
