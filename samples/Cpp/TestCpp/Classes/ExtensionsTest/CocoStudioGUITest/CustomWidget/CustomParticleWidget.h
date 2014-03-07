//
//  CustomParticleWidget.h
//  CustomUI
//
//  Created by cai wenzhi on 14-3-7.
//
//

#ifndef __CustomUI__CustomParticleWidget__
#define __CustomUI__CustomParticleWidget__

#include "cocos2d.h"
#include "cocos-ext.h"

class CustomParticleWidget : public cocos2d::ui::Widget
{
public:
    
    CustomParticleWidget();
    ~CustomParticleWidget();
    
    static CustomParticleWidget* create();
    static cocos2d::CCObject* createInstance();
    
    void setParticlePlist(const char* plist);
    const char* getParticlePlist() const;
    
    void setParticlePosition(const cocos2d::CCPoint& pos);
    const cocos2d::CCPoint& getParticlePosition() const;
    
protected:
    virtual bool init();
    virtual void initRenderer();
    
    virtual void removeAllChildren();
    
protected:
    cocos2d::CCParticleSystem* _emitter;
    const char* _emitterPlist;
    cocos2d::CCPoint _emitterPostion;
    
};

#endif /* defined(__CustomUI__CustomParticleWidget__) */
