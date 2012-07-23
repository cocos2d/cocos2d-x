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

#ifndef SEMAPHORE_H_
#define SEMAPHORE_H_

#include <FBaseRtThread.h>
#include <time.h>

typedef struct sem{
  Osp::Base::Runtime::Semaphore *id;
  int value;
  Osp::Base::Runtime::Mutex *mutex;
}sem_t;

#define SEM_FAILED	((sem_t*)0)
#define SEM_VALUE_MAX	((int)((~0u)>>1))
#define SEM_MAGIC	0x35d108f2

int sem_destroy(sem_t*sem);
int sem_getvalue(sem_t*sem,int*sval);
int sem_init(sem_t*sem,int pshared,unsigned int value);
int sem_post(sem_t*sem);
int sem_trywait(sem_t*sem);
int sem_wait(sem_t*sem);

sem_t*sem_open(const char*name,int oflag,...);
int sem_close(sem_t*sem);
int sem_unlink(const char*name);

int sem_timedwait(sem_t*sem,const struct timespec*abstime);

#endif /* SEMAPHORE_H_ */
