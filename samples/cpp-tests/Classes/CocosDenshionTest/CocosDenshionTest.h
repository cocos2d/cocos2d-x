#ifndef __COCOS_DENSHION_TEST__
#define __COCOS_DENSHION_TEST__

#include "../testBasic.h"

class AudioSlider;

class CocosDenshionTest : public Layer
{
public:
    CocosDenshionTest(void);
    ~CocosDenshionTest(void);

    virtual void onExit() override;

private:
    void addButtons();
    void addSliders();
    void addChildAt(Node *node, float percentageX, float percentageY);

    void updateVolumes(float);

    unsigned int _soundId;
    float _musicVolume;
    float _effectsVolume;
    AudioSlider *_sliderPitch;
    AudioSlider *_sliderPan;
    AudioSlider *_sliderGain;
    AudioSlider *_sliderEffectsVolume;
    AudioSlider *_sliderMusicVolume;
};

class CocosDenshionTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif //__COCOS_DENSHION_TEST__
