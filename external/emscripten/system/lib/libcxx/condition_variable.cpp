//===-------------------- condition_variable.cpp --------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "condition_variable"
#include "thread"
#include "system_error"
#include "cassert"

_LIBCPP_BEGIN_NAMESPACE_STD

condition_variable::~condition_variable()
{
    pthread_cond_destroy(&__cv_);
}

void
condition_variable::notify_one() _NOEXCEPT
{
    pthread_cond_signal(&__cv_);
}

void
condition_variable::notify_all() _NOEXCEPT
{
    pthread_cond_broadcast(&__cv_);
}

void
condition_variable::wait(unique_lock<mutex>& lk)
{
    if (!lk.owns_lock())
        __throw_system_error(EPERM,
                                  "condition_variable::wait: mutex not locked");
    int ec = pthread_cond_wait(&__cv_, lk.mutex()->native_handle());
    if (ec)
        __throw_system_error(ec, "condition_variable wait failed");
}

void
condition_variable::__do_timed_wait(unique_lock<mutex>& lk,
               chrono::time_point<chrono::system_clock, chrono::nanoseconds> tp)
{
    using namespace chrono;
    if (!lk.owns_lock())
        __throw_system_error(EPERM,
                            "condition_variable::timed wait: mutex not locked");
    nanoseconds d = tp.time_since_epoch();
    if (d > nanoseconds(0x59682F000000E941))
        d = nanoseconds(0x59682F000000E941);
    timespec ts;
    seconds s = duration_cast<seconds>(d);
    typedef decltype(ts.tv_sec) ts_sec;
    _LIBCPP_CONSTEXPR ts_sec ts_sec_max = numeric_limits<ts_sec>::max();
    if (s.count() < ts_sec_max)
    {
        ts.tv_sec = static_cast<ts_sec>(s.count());
        ts.tv_nsec = static_cast<decltype(ts.tv_nsec)>((d - s).count());
    }
    else
    {
        ts.tv_sec = ts_sec_max;
        ts.tv_nsec = giga::num - 1;
    }
    int ec = pthread_cond_timedwait(&__cv_, lk.mutex()->native_handle(), &ts);
    if (ec != 0 && ec != ETIMEDOUT)
        __throw_system_error(ec, "condition_variable timed_wait failed");
}

void
notify_all_at_thread_exit(condition_variable& cond, unique_lock<mutex> lk)
{
    __thread_local_data()->notify_all_at_thread_exit(&cond, lk.release());
}

_LIBCPP_END_NAMESPACE_STD
