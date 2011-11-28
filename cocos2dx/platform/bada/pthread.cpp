/*
 Bada pthread
 Copyright (c) 2010 Markovtsev Vadim

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
*/

#ifndef CC_BADA_2_0

#include "pthread.h"
#include <FApp.h>
#include <FBaseRtThread.h>

using namespace Osp::Base;
using namespace Osp::Base::Runtime;

extern "C" {

typedef void*(*pthread_func)(void *);

//struct _pthread_fastlock
//{
//	int __spinlock;
//};

//typedef struct _pthread_descr_struct*_pthread_descr;
/* Mutexes */
struct pthread_mutex{
  Osp::Base::Runtime::Mutex *lock;
//  _pthread_descr owner;
  int kind;
  unsigned int count;
  bool acquired;
};

struct sched_param {
  int sched_priority;           /* Process execution scheduling priority */

#if defined(_POSIX_SPORADIC_SERVER)
  int ss_low_priority;          /* Low scheduling priority for sporadic */
                                /*   server */
  struct timespec ss_replenish_period;
                                /* Replenishment period for sporadic server */
  struct timespec ss_initial_budget;   /* Initial budget for sporadic server */
#endif
};

/* Attributes for threads.  */
struct pthread_attr{
  int		__detachstate;
  int		__schedpolicy;
  struct sched_param	__schedparam;
  int		__inheritsched;
  int		__scope;
  void *	__stackaddr;
  unsigned long __stacksize;
};

struct pthread_mutexattr{
  int __mutexkind;
};

struct pthread_cond{
  Osp::Base::Runtime::Monitor *lock;
//  _pthread_descr wait_chain;
};

class RunnableProxy :
		public Object,
  		public virtual IRunnable
{
private:
	pthread_func _func;
	void * _parameter;

public:
	void SetFunc(pthread_func func)
	{
		_func = func;
	}

	pthread_func GetFunc()
	{
		return _func;
	}

	void SetParameter(void *parameter)
	{
		_parameter = parameter;
	}

	void *GetParameter()
	{
		return _parameter;
	}

	Object* Run(void)
	{
		void *result = _func(_parameter);
		return (Object *)result;
	}
};

pthread_t pthread_self(void)
{
	return Thread::GetCurrentThread();
}

int pthread_create(pthread_t*__threadarg,
			const pthread_attr_t*__attr,
			void*(*__start_routine)(void *),
			void*__arg)
{
	if (NULL == __threadarg)
	{
		return -1;
	}
	Thread *thread = new Thread();
	RunnableProxy *proxy = new RunnableProxy();
	proxy->SetFunc(__start_routine);
	proxy->SetParameter(__arg);
	thread->Construct(*proxy);
	*__threadarg = thread;
	return (int)thread->Start();
}

void pthread_exit(void*__retval)
{
	Thread::Exit(-1);
}

int pthread_join(pthread_t __th,void**__thread_return)
{
	if (!__th)
	{
		return -1;
	}
	return ((Thread*)__th)->Join();
}

int pthread_cancel(pthread_t thread)
{
	if (!thread)
	{
		return -1;
	}
	return ((Thread*)thread)->Exit();
}

int pthread_detach(pthread_t __th)
{
	if (__th)
	{
		((Thread*)__th)->Exit();
		delete __th;
	}
	return 0;
}

int pthread_equal(pthread_t __thread1,pthread_t __thread2)
{
	if (!__thread1 || !__thread2)
	{
		return (void *)__thread1 == (void *)__thread2;
	}
	return ((Thread*)__thread1)->Equals(*((Thread*)__thread2));
}

int pthread_kill(pthread_t thread,int sig)
{
	if (!thread)
	{
		return -1;
	}
	return ((Thread*)thread)->Exit(sig);
}

int pthread_attr_init(pthread_attr_t*attr)
{
	*attr = new pthread_attr();
	(*attr)->__stacksize = Thread::DEFAULT_STACK_SIZE;
	struct sched_param param;
	param.sched_priority = THREAD_PRIORITY_MID;
	(*attr)->__schedparam = param;
	return 0;
}

int pthread_attr_destroy(pthread_attr_t*attr)
{
	return 0;
}

int pthread_attr_setdetachstate(pthread_attr_t*attr,const int detachstate)
{
	(*attr)->__detachstate = detachstate;
	return 0;
}

int pthread_attr_getdetachstate(const pthread_attr_t*attr,int*detachstate)
{
	*detachstate = (*attr)->__detachstate;
	return 0;
}

int pthread_mutexattr_init(pthread_mutexattr_t*attr)
{
	*attr = new pthread_mutexattr();
	return 0;
}

int pthread_mutexattr_destroy(pthread_mutexattr_t*attr)
{
	return 0;
}

int pthread_mutex_init(pthread_mutex_t*mutex,
		const pthread_mutexattr_t*mutexattr)
{
	if (!mutex)
	{
		return -1;
	}
	*mutex = new pthread_mutex();
	(*mutex)->lock = new Mutex();
	(*mutex)->acquired = false;
	return (*mutex)->lock->Create();
}

int pthread_mutex_lock(pthread_mutex_t*mutex)
{
	if (!mutex || !(*mutex)->lock)
	{
		return -1;
	}
	int res = (*mutex)->lock->Acquire();
	if (res == E_SUCCESS)
	{
		(*mutex)->acquired = true;
	}
	return res;
}

int pthread_mutex_unlock(pthread_mutex_t*mutex)
{
	if (!mutex || !(*mutex)->lock)
	{
		return -1;
	}
	int res = (*mutex)->lock->Release();
	if (res == E_SUCCESS)
	{
		(*mutex)->acquired = false;
	}
	return res;
}

int pthread_mutex_trylock(pthread_mutex_t*mutex)
{
	if (!mutex || !(*mutex)->lock)
	{
		return -1;
	}
	if (!(*mutex)->acquired)
	{
		int res = (*mutex)->lock->Acquire();
		if (res == E_SUCCESS)
		{
			(*mutex)->acquired = true;
		}
		return res;
	}
	return -1;
}

int pthread_mutex_destroy(pthread_mutex_t*mutex)
{
	delete (*mutex)->lock;
	(*mutex)->acquired = false;
	delete (*mutex);
	return 0;
}

int pthread_cond_init(pthread_cond_t*cond,pthread_condattr_t*cond_attr)
{
	if (!cond)
	{
		return -1;
	}
	*cond = new pthread_cond();
	(*cond)->lock = new Monitor();
	(*cond)->lock->Construct();
	return 0;
}

int pthread_cond_destroy(pthread_cond_t*cond)
{
	if (cond != NULL)
	{
		delete (*cond)->lock;
		delete (*cond);
		return 1;
	}
	return 0;
}

int pthread_cond_signal(pthread_cond_t*cond)
{
	if (!cond)
	{
		return -1;
	}
	return (*cond)->lock->Notify();
}

int pthread_cond_broadcast(pthread_cond_t*cond)
{
	if (!cond)
	{
		return -1;
	}
	return (*cond)->lock->NotifyAll();
}

int pthread_cond_timedwait(pthread_cond_t*cond,pthread_mutex_t*mutex,
			   const struct timespec*abstime)
{
	if (!cond)
	{
		return -1;
	}
	(*cond)->lock->Enter();
	(*cond)->lock->Wait();
	(*cond)->lock->Exit();
	return 1;
}

int pthread_cond_wait(pthread_cond_t*cond,pthread_mutex_t*mutex)
{
	if (!cond)
	{
		return -1;
	}
	(*cond)->lock->Enter();
	(*cond)->lock->Wait();
	(*cond)->lock->Exit();
	return 1;
}

int pthread_condattr_init(pthread_condattr_t*attr)
{
	return 0;
}

int pthread_condattr_destroy(pthread_condattr_t*attr)
{
	return 0;
}

int pthread_condattr_getpshared(const pthread_condattr_t*attr,int*pshared)
{
	return 0;
}

int pthread_condattr_setpshared(pthread_condattr_t*attr,int pshared)
{
	return 0;
}

}

#endif
