//
//  PerformanceCallbackTest.h

#ifndef __PERFORMANCE_CALLBACK_TEST_H__
#define __PERFORMANCE_CALLBACK_TEST_H__

#include "PerformanceTest.h"

class CallbackBasicLayer : public PerformBasicLayer
{
public:
    CallbackBasicLayer(bool bControlMenuVisible, int nMaxCases = 0, int nCurCase = 0);
    
    virtual void showCurrentTest();
};

class PerformanceCallbackScene : public Scene
{
public:
    virtual void onEnter() override;
    virtual std::string title() const;
    virtual std::string subtitle() const;
    virtual void onUpdate(float dt) {};
    
    void dumpProfilerInfo(float dt);
protected:
    
    std::string _profileName;
    int _placeHolder; // To avoid compiler optimization
    static const int LOOP_COUNT = 10000;
};

class SimulateNewSchedulerCallbackPerfTest : public PerformanceCallbackScene
{
public:
    CREATE_FUNC(SimulateNewSchedulerCallbackPerfTest);
    
    // overrides
    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual void onUpdate(float dt) override;
    
    virtual void update(float dt) override { _placeHolder = 100; };
    
    void simulateSchedulePerFrame(const std::function<void(float)>& callback)
    {
        _callback = callback;
    }
    
    template <class T>
    void simulateScheduleUpdate(T* target)
    {
        target->simulateSchedulePerFrame([target](float dt){
            target->update(dt);
        });
    }
    
private:
    std::function<void(float)> _callback;
};


// InvokeMemberFunctionPerfTest
class InvokeMemberFunctionPerfTest : public PerformanceCallbackScene
{
public:
    CREATE_FUNC(InvokeMemberFunctionPerfTest);
    
    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual void onUpdate(float dt) override;
    
    virtual void update(float dt) override { _placeHolder = 200; };
    
private:
    Node* _target;
    SEL_SCHEDULE _selector;
};

// InvokeStdFunctionPerfTest
class InvokeStdFunctionPerfTest : public PerformanceCallbackScene
{
public:
    CREATE_FUNC(InvokeStdFunctionPerfTest);
    
    // overrides
    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual void onUpdate(float dt) override;
    
    virtual void update(float dt) override { _placeHolder = 100; };
private:
    std::function<void(float)> _callback;
};

void runCallbackPerformanceTest();

#endif /* __PERFORMANCE_CALLBACK_TEST_H__ */
