
/****************************************************************************
Copyright(c) 2018 Xiamen Yaji Software Co., Ltd.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#pragma once
#include <mutex>
#include <memory>

#include "base/CCRef.h"

namespace cocos2d {
    namespace atomic
    {
        

        /**
        * Guard is a recursive_mutex wrap for pointer T*, provide RAII-style 
        * mechanism for owning a mutex for the duration of a scoped block.
        *
        * It trys to call lock(), when a Guard object is created. 
        * unlock() will be called when control leaves the scope and Guard will be destroyed.
        * 
        * Guard should be fetched by Atomic#load() only.
        * 
        * Operation to `T*` can be performed through `->` or `*`
        */
        template<typename T>
        class Guard {
        public:
            /**
            * construct a Guard and acquire lock
            * this should not be called manually
            */
            Guard(std::shared_ptr<T> d, std::shared_ptr<std::recursive_mutex> mtx) :_mtx(mtx), _data(d) { _mtx->lock(); }

            /**
            * copy constructor of Guard and acquire lock
            * this should not be called manually
            */
            Guard(const Guard &o) :_mtx(o._mtx), _data(o._data) { _mtx->lock(); }

            /**
            * destructor of Guard, release unlock
            */
            virtual ~Guard() { _mtx->unlock(); }

            operator bool() { return _data != nullptr; }

            /**
            * accquire inner pointer T*
            */
            T * operator ->() { return _data.get(); }
            
            /**
            * accquire inner pointer T*
            */
            const T * operator ->() const { return _data.get(); }
            
            /**
            * accquire inner data reference T&
            */
            T& operator *() { return *_data.get(); }

            /**
            * accquire inner data reference T&
            */
            const T& operator *() const { return *_data.get(); }
        private:
            std::shared_ptr<std::recursive_mutex> _mtx;
            std::shared_ptr<T> _data = nullptr;
        };

        /**
        * Atomic bind data `T*` with a `recursive_mutex` and enforce accquiring the
        * lock before accessing data. 
        * 
        * here is an example that shows the usage
        * ```
        * Atomic<std::vector<std::string>> atomicVec(new std::vector<std::string>>());
        * 
        * //thread 1
        * {
        *     auto vecGuard = atomicVec.load();
        *     vecGuard->push_back("a");
        *     vecGuard->push_back("b");
        * }
        * //thread 2
        * {
        *     auto vecGuard = atomicVec.load();
        *     for(auto str : *vecGuard)
        *     {
        *       //iter ... 
        *     }
        * }
        * ```
        */
        template<typename T>
        class Atomic {
        public:
            /**
            * Constructor of Atomic. 
            * create a internal recursive_mutex used to protect data `T*`
            */
            Atomic(T *data) {
                _data = std::shared_ptr<T>(data);
                _mtx = std::make_shared<std::recursive_mutex>();
            }

            Atomic(const Atomic &a) : _data(a._data), _mtx(a._mtx) {}


            virtual ~Atomic() {}
            /**
            * Creates a Guard object and that is the only way to access internal data T*.
            */
            Guard<T> load() {
                std::lock_guard<std::recursive_mutex> guard(*_mtx);
                return Guard<T>(_data, _mtx);
            }

            /**
            * Creates a Guard object and that is the only way to access internal data T*.
            */
            const Guard<T> load() const {
                std::lock_guard<std::recursive_mutex> guard(*_mtx);
                return Guard<T>(_data, _mtx);
            }
        private:
            std::shared_ptr<T> _data = nullptr;
            std::shared_ptr<std::recursive_mutex> _mtx = nullptr;

            //memory T should be managed by std::shared_ptr only, cocos2d::Ref would cause 
            static_assert(!std::is_base_of<cocos2d::Ref, typename std::remove_const<T>::type>::value, "T should not be derived from cocos2d::Ref, it is not supported");
        };
    }
}
