/****************************************************************************
Copyright (c) 2013 cocos2d-x.org

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

NS_CC_EXT_BEGIN
/**
 *  @lua NA
 */
class CCComAudio : public cocos2d::CCComponent
{
	DECLARE_CLASS_COMPONENT_INFO
protected:
    CCComAudio(void);
    virtual ~CCComAudio(void);
    
public:
   virtual bool init();
   virtual void onEnter();
   virtual void onExit();
   virtual bool isEnabled() const;
   virtual void setEnabled(bool b);
   virtual bool serialize(void* r);

   static CCComAudio* create(void);
   
public:
   void end();
   void preloadBackgroundMusic(const char* pszFilePath);
   void playBackgroundMusic(const char* pszFilePath, bool bLoop);
   void playBackgroundMusic(const char* pszFilePath);
   void playBackgroundMusic();
   void stopBackgroundMusic(bool bReleaseData);
   void stopBackgroundMusic();
   void pauseBackgroundMusic();
   void resumeBackgroundMusic();
   void rewindBackgroundMusic();
   bool willPlayBackgroundMusic();
   bool isBackgroundMusicPlaying();
   float getBackgroundMusicVolume();
   void setBackgroundMusicVolume(float volume);
   float getEffectsVolume();
   void setEffectsVolume(float volume);
   unsigned int playEffect(const char* pszFilePath, bool bLoop);
   unsigned int playEffect(const char* pszFilePath);
   unsigned int playEffect();
   void pauseEffect(unsigned int nSoundId);
   void pauseAllEffects();
   void resumeEffect(unsigned int nSoundId);
   void resumeAllEffects();
   void stopEffect(unsigned int nSoundId);
   void stopAllEffects();
   void preloadEffect(const char* pszFilePath);
   void unloadEffect(const char* pszFilePath);
   void setFile(const char* pszFilePath);
   const char* getFile();
   void setLoop(bool bLoop);
   bool isLoop();
private:
   std::string m_strFilePath;
   bool m_bLoop;
};

NS_CC_EXT_END

#endif  // __FUNDATION__CCCOMPONENT_H__
