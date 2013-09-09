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

#pragma once
#include "cocos2d.h"
#include "Queue.h"

NS_CC_BEGIN
namespace android {

template <typename T>
class ObjPtr {
	T* ptr_;
public:
	T* get() const { return ptr_; };
public:
	ObjPtr():ptr_(nullptr) {

	}
	ObjPtr(T* t):ptr_(t){
		if(ptr_){
			ptr_->retain();
		}
	}
	template <typename O>
	ObjPtr(ObjPtr<O> const& o):ptr_(o.get()){
		if(ptr_){
			ptr_->retain();
		}
	}
	template <typename O>
	ObjPtr<T>& operator=(ObjPtr<O> const& o_) {
		O* o = o_.get();
		if( o ){
			o->retain();
		}
		if(ptr_){
			ptr_->release();
		}
		ptr_ = o;
		return *this;
	}
	~ObjPtr()
	{
		if(ptr_){
			ptr_->release();
		}
	}
	T* operator->() const{
		return ptr_;
	}
};

class Executor {
private:
	Queue queue_;
	ObjPtr<Object> receiver_;
	std::unique_ptr<Queue::PopDelegate> processor_;
private:
	ObjPtr<Scheduler> const scheduler_;
public:
	Executor(Scheduler* const scheduler);
	Executor();
	~Executor();
public:
	void post(std::function<void()> const& f);
	template <typename U>
	inline void post(U f){
		post(std::function<void()>([f](){ f(); }));
	}
public:
	bool isRegistered();
	void registerScheduler();
	void unregisterScheduler();
public:
	static Executor* getInstance();
};

}
NS_CC_END
