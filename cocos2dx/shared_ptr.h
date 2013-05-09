/****************************************************************************
 Copyright (c) 2013      Zynga Inc.

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

#ifndef __cocos2dx__shared_ptr__
#define __cocos2dx__shared_ptr__

#include "cocoa/CCObject.h"
#include "platform/CCPlatformMacros.h"

NS_CC_BEGIN

//
// code based on the following articles:
// http://techieworldz.blogspot.com/2012/04/simple-sharedptr-implementation.html
// http://en.wikipedia.org/wiki/Auto_ptr
//

/** A simple shared pointer to be used only with CCObject and subclasses.
 It allows CCObject objects to be used in STL containers like std::map and std::vector.
 Instead of implementing its own reference counting, it uses the referece counting implemented by the CCObject.
 */
class shared_ptr
{

public:
	//
	// 20.4.5.1 construct/copy/destroy:
	//

	/** Constructor */
	explicit shared_ptr(CCObject* p = 0) : m_ptr(p)
	{
		// retain the inner copy
		if( m_ptr != NULL )
			m_ptr->retain();
	}

	/** Copy constructor */
	shared_ptr(const shared_ptr& rhs)
	{
		//during copy construction share the object pointer
		// and ref counting pointer
		this->m_ptr = rhs.m_ptr;

		//increment the counter as we have one more object now
		this->m_ptr->retain();
	}

	/** Assignment */
	shared_ptr& operator=(shared_ptr& rhs)
	{
		if(this->m_ptr != rhs.m_ptr)
		{
			if(this->m_ptr != NULL)
			{
				//decrement this counter
				m_ptr->release();
			}
			//assing rhs and increment counter
			this->m_ptr = rhs.m_ptr;
			this->m_ptr->retain();
		}
		return *this;
	}

	/** destructor. It will call "release" on the shared object. */
	~shared_ptr()
	{
		m_ptr->release();
	}

	/** returns a reference to the shared object */
	CCObject& operator*() const {
		return *m_ptr;
	};

	/** returns the shared object (the pointer) */
	CCObject* operator->() const {
		return m_ptr;
	}

	/** returns the shared object (the pointer) */
	CCObject* get() const  {
		return m_ptr;
	}

private:
	CCObject* m_ptr;
};

NS_CC_END

#endif /* defined(__cocos2dx__shared_ptr__) */
