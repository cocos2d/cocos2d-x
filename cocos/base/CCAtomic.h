
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



namespace cocos2d {
    namespace atomic
    {
        template<typename T>
        class Guard {
        public:
            Guard(std::shared_ptr<T> d, std::shared_ptr<std::recursive_mutex> mtx) :_mtx(mtx), _data(d) { _mtx->lock(); }
            Guard(const Guard &o) :_mtx(o._mtx), _data(o._data) { _mtx->lock(); }
            virtual ~Guard() { _mtx->unlock(); }
            operator bool() { return _data != nullptr; }
            T * operator ->() { return _data.get(); }
            const T * operator ->() const { return _data.get(); }
            T& operator *() { return *_data.get(); }
            const T& operator *() const { return *_data.get(); }
        private:
            std::shared_ptr<std::recursive_mutex> _mtx;
            std::shared_ptr<T> _data = nullptr;
        };

        template<typename T>
        class Atomic {
        public:
            Atomic(T *data) {
                _data = std::shared_ptr<T>(data);
                _mtx = std::make_shared<std::recursive_mutex>();
            }
            virtual ~Atomic() {}
            /**
            * accquire Guard scope object
            */
            Guard<T> load() {
                std::lock_guard<std::recursive_mutex> guard(*_mtx);
                return Guard<T>(_data, _mtx);
            }
            const Guard<T> load() const {
                std::lock_guard<std::recursive_mutex> guard(*_mtx);
                return Guard<T>(_data, _mtx);
            }
        private:
            std::shared_ptr<T> _data = nullptr;
            std::shared_ptr<std::recursive_mutex> _mtx = nullptr;
        };
    }
}
