/****************************************************************************
Copyright (c) 2010-2013 cocos2d-x.org
Copyright (c) Microsoft Open Technologies, Inc.

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
#include "CCPThreadWinRT.h"


NS_CC_BEGIN

void pthread_mutex_init(pthread_mutex_t* m, void* attributes) {
	*m = CreateMutexEx(NULL,FALSE,0,NULL);
}

int pthread_mutex_lock(pthread_mutex_t* m) {
	return WaitForSingleObjectEx(*m,INFINITE,FALSE);
}

int pthread_mutex_unlock(pthread_mutex_t* m) {
	return ReleaseMutex(*m);
}

void pthread_mutex_destroy(pthread_mutex_t* m) 
{
	if(m)
	{
		CloseHandle(*m);
	}
}


NS_CC_END
