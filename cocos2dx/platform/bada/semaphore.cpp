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

#include "semaphore.h"
#include <map>
#include <string>

static std::map<std::string, sem_t *> _semaphores;

int sem_destroy(sem_t*sem)
{
	if (sem)
	{
		if (sem->id)
		{
			delete sem->id;
			sem->id = null;
		}
		if (sem->mutex)
		{
			delete sem->mutex;
			sem->mutex = null;
		}
	}
	return 0;
}

static int atomic_add(int *number, int value, Osp::Base::Runtime::Mutex *mutex)
{
	if (!mutex || !number)
	{
		return -1;
	}
	mutex->Acquire();
	*number += value;
	mutex->Release();
	return 0;
}

int sem_getvalue(sem_t*sem,int*sval)
{
	if (!sem || !sval || sem->mutex)
	{
		return -1;
	}
	sem->mutex->Acquire();
	*sval =	sem->value;
	sem->mutex->Release();
	return 0;
}

int sem_init(sem_t*sem,int pshared,unsigned int value)
{
	if (!sem)
	{
		return -1;
	}
	sem->id = new Osp::Base::Runtime::Semaphore();
	sem->mutex = new Osp::Base::Runtime::Mutex();
	sem->id->Create(value);
	sem->mutex->Create();
	sem->value = value;
	return 0;
}
int sem_post(sem_t*sem)
{
	if (!sem || !sem->id)
	{
		return -1;
	}
	atomic_add(&sem->value, 1, sem->mutex);
	sem->id->Release();
	return 0;
}

int sem_trywait(sem_t*sem)
{
	if (!sem || !sem->id)
	{
		return -1;
	}
	sem->mutex->Acquire();
	int sval =	sem->value;
	sem->mutex->Release();
	if (sval > 0)
	{
		atomic_add(&sem->value, -1, sem->mutex);
		sem->id->Acquire();
		return 0;
	}
	return -1;
}

int sem_wait(sem_t*sem)
{
	if (!sem || !sem->id)
	{
		return -1;
	}
	atomic_add(&sem->value, -1, sem->mutex);
	sem->id->Acquire();
	return 0;
}

sem_t*sem_open(const char*name,int oflag,...)
{
	sem_t *sem = new sem_t();
	sem->id = new Osp::Base::Runtime::Semaphore();
	sem->mutex = new Osp::Base::Runtime::Mutex();
	sem->id->Create(name);
	sem->mutex->Create();
	sem->value = 1;
	_semaphores.insert(std::pair<std::string, sem_t *>(name, sem));
	return sem;
}

int sem_close(sem_t*sem)
{
	return sem_destroy(sem);
}

int sem_unlink(const char*name)
{
	std::map<std::string, sem_t *>::iterator I = _semaphores.find(name);
	if (I == _semaphores.end())
	{
		return -1;
	}
	sem_destroy(I->second);
	_semaphores.erase(name);
	return 0;
}

int sem_timedwait(sem_t*sem,const struct timespec*abstime)
{
	if (!sem || !sem->id || !abstime)
	{
		return -1;
	}
	sem->id->Acquire(abstime->tv_sec * 1000 + abstime->tv_nsec / 1000000);
	return 0;
}
