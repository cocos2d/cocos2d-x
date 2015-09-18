#ifndef __COCOS_DENSHION_TEST__
#define __COCOS_DENSHION_TEST__

#include "../BaseTest.h"

class AudioSlider;

DEFINE_TEST_SUITE(CocosDenshionTests);

class CocosDenshionTest : public TestCase
{
public:
    CREATE_FUNC(CocosDenshionTest);

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

#endif //__COCOS_DENSHION_TEST__
