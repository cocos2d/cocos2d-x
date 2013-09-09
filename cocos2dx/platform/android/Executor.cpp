/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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

#include "Executor.h"

NS_CC_BEGIN
namespace android {

class SchedulerReceiver final :public Object {
private:
	Executor& self_;
	ObjPtr<Scheduler> const scheduler_;
	Queue& queue_;
	std::unique_ptr<Queue::PopDelegate> const& processor_;
public:
	SchedulerReceiver(Executor& self, ObjPtr<Scheduler> const& scheduler, Queue& queue, std::unique_ptr<Queue::PopDelegate> const& processor)
	:self_(self)
	,scheduler_(scheduler)
	,queue_(queue)
	,processor_(processor)
	{
	}
	void process(float delta){
		Queue::Payload p;
		while( queue_.pop(p) ){
			p.unbox(*processor_.get());
		}
		scheduler_->pauseTarget(this);
	}
private:
	bool init(){
		return true;
	}
public:
	static SchedulerReceiver* create(Executor& self, ObjPtr<Scheduler> const& scheduler, Queue& queue, std::unique_ptr<Queue::PopDelegate> const& processor)
	{
		SchedulerReceiver *pRet = new SchedulerReceiver(self, scheduler, queue, processor);
		if (pRet && pRet->init())
		{
			pRet->autorelease();
			return pRet;
		}
		else
		{
			delete pRet;
			pRet = nullptr;
			return nullptr;
		}
	}
};

class SchedulerProcessor final :public Queue::PopDelegate {
	virtual void onPopFunction(int const code, std::function<void()> const& val) {
		val();
	};
};

Executor::Executor()
:scheduler_(Director::getInstance()->getScheduler())
,processor_(new SchedulerProcessor)
,receiver_(SchedulerReceiver::create(*this, scheduler_, queue_, processor_))
{
	registerScheduler();
}

Executor::Executor(Scheduler* const scheduler)
:scheduler_(scheduler)
,processor_(new SchedulerProcessor)
,receiver_(SchedulerReceiver::create(*this, scheduler_, queue_, processor_))
{
	registerScheduler();
}

Executor::~Executor()
{
	//cocos2d-x does not use exception.
	//try {
		if(isRegistered()){
			unregisterScheduler();
		}
	//} catch (...) {}
}

void Executor::post(std::function<void()> const& f) {
	queue_.push(0, f);
	this->scheduler_->resumeTarget(receiver_.get());
}

bool Executor::isRegistered()
{
	return this->scheduler_->isScheduledForTarget(schedule_selector(SchedulerReceiver::process), receiver_.get());
}

void Executor::registerScheduler()
{
	this->scheduler_->scheduleSelector(schedule_selector(SchedulerReceiver::process), receiver_.get(), 0, true);
}
void Executor::unregisterScheduler()
{
	this->scheduler_->unscheduleAllForTarget(receiver_.get());
}

Executor* Executor::getInstance()
{
	static std::unique_ptr<Executor> p;
	if(!p){
		std::unique_ptr<Executor>(new Executor).swap(p);
	}
	return p.get();
}

}
NS_CC_END
