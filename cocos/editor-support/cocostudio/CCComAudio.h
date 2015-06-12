/****************************************************************************
Copyright (c) 2013-2014 Chukong Technologies Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#ifndef __CC_EXTENTIONS_CCCOMAUDIO_H__
#define __CC_EXTENTIONS_CCCOMAUDIO_H__

#include "CCComBase.h"
#include "2d/CCComponent.h"
#include "cocostudio/CocosStudioExport.h"

namespace cocostudio {

/** 
 * @class ComAudio
 * @brief @~english ComAudio.
 * @~chinese �Զ����������.
 * @details @~english offers a very simple interface to play background music & sound effects.
 * @~chinese �ṩ������Ч�ͱ������ֵ�һϵ�нӿ�.
*/
class CC_STUDIO_DLL ComAudio : public cocos2d::Component
{

    DECLARE_CLASS_COMPONENT_INFO

public:
    /**
     * @brief @~english ComAudio constructor.
     * @~chinese ����������캯����
     * @js ctor
     */
    ComAudio(void);
    /**
     * @brief @~english ComAudio destructor.
     * @~chinese �����������������
     * @js NA
     * @lua NA
     */
    virtual ~ComAudio(void);
    
public:
    /**
     * @brief @~english initialize a ComAudio.
     * @~chinese ��ʼ�����������
     * @return @~english true initialize successfully false failed to initialize.
     * @~chinese true ��ʼ���ɹ�������false��
     */
    virtual bool init() override;

    /**
     * @brief @~english Event callback that is invoked every time when Node enters the 'stage'.
     * If the Node enters the 'stage' with a transition, this event is called when the transition starts.
     * During onEnter you can't access a "sister/brother" node.
     * If you override onEnter, you shall call its parent's one, e.g., Node::onEnter().
     * @~chinese ÿ�ε�Node���롰stage��ʱ�ŵ����¼��ص���
     * ���Node���롰stage��״̬ʱ������һ��ת����transition��,��ô�¼����������ת����ʼ��ʱ�򱻵��á�
     * ��onEnter�����У��㲻�ܹ����롰sister/brother�����ýڵ㡣
     * �������д��onEnter��������Ӧ�õ������ĸ��࣬e.g., Node::onEnter().
     * @js NA
     * @lua NA
     */
    virtual void onEnter() override;

    /**
     * @brief @~english Event callback that is invoked every time the Node leaves the 'stage'.
     * If the Node leaves the 'stage' with a transition, this event is called when the transition finishes.
     * During onExit you can't access a sibling node.
     * If you override onExit, you shall call its parent's one, e.g., Node::onExit().
     * @~chinese ÿ�ε�Node�뿪��stage��ʱ�ŵ����¼��ص���
     * ���Node�뿪��stage��״̬ʱ������һ��ת����transition��, ��ô�¼����������ת��������ʱ�򱻵��á�
     * ��onEnter���������㲻�ܹ�����һ�����ýڵ㡣
     * �������дonExit, ��Ӧ�õ������ĸ���, e.g., Node::onExit().
     * @js NA
     * @lua NA
     */
    virtual void onExit() override;

    /** 
     * @brief @~english Returns whether or not the ComAudio is enabled.
     * @~chinese ������������Ƿ����á�
     * @return @~english Whether or not the ComAudio is enabled. 
     * @~chinese ��������Ƿ����á�
     */
    virtual bool isEnabled() const override;

    /**  
     * @brief @~english enables or disables the ComAudio.
     * @~chinese ���û�������������
     * @param enabled @~english true enable the menu ComAudio, false disabled the ComAudio. 
     * @~chinese true������������� false���������������
     */
    virtual void setEnabled(bool b) override;

    /**
     * @brief @~english deserialization export data of cocos studio 1.x scene editor.
     * @~chinese �����л�cocos studio 1.x �����༭�����������ݡ�
     * @param r @~english SerData object point.
     * @~chinese SerData����ָ�롣
     * @return @~english true deserialize successfully false failed to deserialize.
     * @~chinese true �����л��ɹ�������false��
     */
    virtual bool serialize(void* r) override;

    /**
     * @brief @~english Allocates and initializes a create.
     * @~chinese ���䲢�ҳ�ʼ�����������
     * @return @~english A initialized ComAudio which is marked as "autorelease".
     * @~chinese һ����ʼ��������������ýڵ���Զ������Ϊ��autorelease��(�Զ��ͷ�)��
     */
    static ComAudio* create(void);
   
public:
    /**
     * @brief @~english Release the shared Engine object.
     * @~chinese �ͷ���Ч����ʵ����
     * @warning @~english It must be called before the application exit, or it will lead to memory leaks.
     * @~chinese ����Ϸ�˳�ʱ��Ҫ���������������Ȼ�Ļ��ᵼ���ڴ�й©��
     */
    void end();

    /**
     * @brief @~english Preload background music.
     * @~chinese Ԥ���ر������֡�
     * @param pszFilePath @~english The path of the background music file.
     * @~chinese �������ֵ��ļ�·����
     */
    void preloadBackgroundMusic(const char* pszFilePath);

    /**
     * @~brief @~english Play background music.
     * @~chinese ���ű������֡�
     * 
     * @param pszFilePath @~english The path of the background music file,or the FileName of T_SoundResInfo.
     * @~chinese �������ֵ��ļ�·����T_SoundResInfo�е�FileName�ֶΡ�
     * @param loop @~english Whether the background music loop or not.
     * @~chinese ���������Ƿ�ѭ�����š�
     */
    void playBackgroundMusic(const char* pszFilePath, bool bLoop);

    /**
     * @~brief @~english Play background music based _loop of property. 
     * @~chinese ���ű������֡�
     * @param pszFilePath @~english The path of the background music file,or the FileName of T_SoundResInfo.
     * @~chinese �������ֵ��ļ�·����T_SoundResInfo�е�FileName�ֶΡ�
     */
    void playBackgroundMusic(const char* pszFilePath);

    /**
     * @~brief @~english Play background music based _loop and _filePath of property. 
     * @~chinese ���ű������֡�
     */
    void playBackgroundMusic();

    /**
     * @brief @~english Stop playing background music.
     * @~chinese ֹͣ���ű������֡�
     * @param releaseData @~english If release the background music data or not.As default value is false.
     * @~chinese �Ƿ��ͷű������ֵ����ݣ�Ĭ��ֵΪfalse��
     */
    void stopBackgroundMusic(bool bReleaseData);

    /**
     * @brief @~english Stop playing background music.
     * @~chinese ֹͣ���ű������֡�
     */
    void stopBackgroundMusic();

    /**
     * @brief @~english Pause playing background music.
     * @~chinese ��ͣ���ű������֡�
     */
    void pauseBackgroundMusic();

    /**
     * @brief @~english Resume playing background music.
     * @~chinese �ָ����ű������֡�
     */
    void resumeBackgroundMusic();

    /**
     * @brief @~english Rewind playing background music.
     * @~chinese ���������ֵ�����ʼ�㲥�š�
     */
    void rewindBackgroundMusic();

    /**
     * @brief @~english Indicates whether any background music can be played or not.
     * @~chinese �Ƿ�Ქ�ű������֡�
     * @return true @~english if background music can be played, otherwise false.
     * @~chinese ����������ֻᱻ���ŷ���true�����򷵻�false��
     */
    bool willPlayBackgroundMusic();

    /**
     * @brief @~english Indicates whether the background music is playing.
     * @~chinese ���������Ƿ��ڲ��š�
     * @return true @~english if the background music is playing, otherwise false.
     * @~chinese ���ڲ��ŷ���true�����򷵻�false��
     */
    bool isBackgroundMusicPlaying();

    /**
     * @brief @~english The volume of the background music within the range of 0.0 as the minimum and 1.0 as the maximum.
     * @~chinese ��ȡ�������ֵ�������������ֵ�ķ�ΧΪ0.0��1.0��
     */
    float getBackgroundMusicVolume();


    void setBackgroundMusicVolume(float volume);

    /**
     * @brief @~english The volume of the effects within the range of 0.0 as the minimum and 1.0 as the maximum.
     * @~chinese ��ȡ��Ч��������С,������С��ΧΪ0.0��1.0��
     */
    float getEffectsVolume();

    /**
     * @brief @~english Set the volume of sound effects.
     * @~chinese ������Ч��������С��
     * @param volume @~english must be within the range of 0.0 as the minimum and 1.0 as the maximum.
     * @~chinese ��Ч��������С����ΧΪ0.0��1.0��
     */
    void setEffectsVolume(float volume);

    /**
     * @brief @~english Play sound effect with a file path and loop.
     * @~chinese ������Ч
     * @param pszFilePath @~english The path of the effect file. 
     * @~chinese ��Ч�ļ���·����
     * @param bLoop @~english Determines whether to loop the effect playing or not. 
     * @~chinese �Ƿ�ѭ������,Ĭ��Ϊfalse,��ѭ����
     * @return @~english The sound id. 
     * @~chinese ����id��
     */
    unsigned int playEffect(const char* pszFilePath, bool bLoop);

    /**
     * @brief @~english Play sound effect with a file path and _loop of property
     * @~chinese ������Ч
     * @param pszFilePath @~english The path of the effect file. 
     * @~chinese ��Ч�ļ���·����
     * @param bLoop @~english Determines whether to loop the effect playing or not. 
     * @~chinese �Ƿ�ѭ������,Ĭ��Ϊfalse,��ѭ����
     * @return @~english The sound id. 
     * @~chinese ����id��
     */
    unsigned int playEffect(const char* pszFilePath);

    /**
     * @brief @~english Play sound effect with _filePath and _loop of property
     * @~chinese ������Ч
     * @return @~english The sound id. 
     * @~chinese ����id��
     */
    unsigned int playEffect();

    /**
     * @brief @~english Pause playing sound effect.
     * @~chinese ��ͣ����ָ����Ч��
     * @param nSoundId @~english The return value of function playEffect.
     * @~chinese ��Чid��
     */
    void pauseEffect(unsigned int nSoundId);

    /**
     * @brief @~english Pause all playing sound effect.
     * @~chinese ��ͣ���в��ŵ���Ч��
     */
    void pauseAllEffects();

    /**
     * @brief @~english Resume playing sound effect.
     * @~chinese �ָ���ͣ����ָ������Ч��
     * @param nSoundId @~english The return value of function playEffect.
     * @~chinese playEffect���ص���Դid��
     */
    void resumeEffect(unsigned int nSoundId);

    /**
     * @brief @~english Resume all playing sound effect.
     * @~chinese �ָ�������ͣ����Ч��
     */
    void resumeAllEffects();

    /**
     * @brief @~english Stop playing sound effect.
     * @~chinese ֹͣ����ָ������Ч��
     *
     * @param nSoundId @~english The return value of function playEffect.
     * @~chinese playEffect���ص���Դid��
     */
    void stopEffect(unsigned int nSoundId);

    /**
     * @brief @~english Stop all playing sound effects.
     * @~chinese ֹͣ���в��ŵ���Ч��
     */
    void stopAllEffects();

    /**
     * @brief @~english Preload a compressed audio file.
     * The compressed audio will be decoded to wave, then written into an internal buffer in SimpleAudioEngine.
     * @~chinese Ԥ������Ч�ļ���
     *
     * @param pszFilePath @~english The path of the effect file. 
     * @~chinese ��Ч�ļ�·����
     * @js NA
     */
    void preloadEffect(const char* pszFilePath);

    /**
     * @brief @~english Unload the preloaded effect from internal buffer.
     * @~chinese ж��Ԥ���ص��ڴ��е���Ч�ļ���
     *
     * @param pszFilePath @~english The path of the effect file.
     * @~chinese ��Ч�ļ���·����
     */
    void unloadEffect(const char* pszFilePath);

    /**
     * @brief @~english Set file path.
     * @~chinese ����·����
     */
    void setFile(const char* pszFilePath);

    /**
     * @brief @~english Get file path.
     * @~chinese ��ȡ·����
     * @return @~english file path.
     * @~chinese �����ļ���
     */
    const char* getFile();

    /**  
     * @brief @~english Sets hether or not the sound is loop.
     * @~chinese ���������Ƿ�ѭ����
     * @param bLoop @~english true ComAudio is loop, false ComAudio is not loop. 
     * @~chinese true�������������ѭ�� false�����������ѭ����
     */
    void setLoop(bool bLoop);

    /** 
     * @brief @~english Returns whether or not the sound is loop.
     * @~chinese ������������Ƿ�ѭ����
     * @return @~english Whether or not the ComAudio is loop. 
     * @~chinese ��������Ƿ�ѭ����
     */
    bool isLoop();
private:
	std::string _filePath;
	bool _loop;
};

}

#endif  // __FUNDATION__CCCOMPONENT_H__
