/****************************************************************************
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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

#include <list>
#include <vector>
#include <unordered_map>
#include <functional>

#include <thread>
#include <mutex>

#include <cassert>

#ifdef _CC_LOOP_DEFINE_LOCK_GUARD_
#error "_CC_LOOP_DEFINE_LOCK_GUARD_ already defined!"
#endif // _CC_LOOP_DEFINE_LOCK_GUARD_


#define _CC_LOOP_DEFINE_LOCK_GUARD_ std::lock_guard<std::recursive_mutex> guard(_mtx)

namespace cocos2d
{
    namespace loop
    {
        template<typename T>
        class ThreadSafeQueue {
        public:
            void pushBack(T&& ele) { _CC_LOOP_DEFINE_LOCK_GUARD_; _data.push_back(ele); }
            void pushBack(T& ele) { _CC_LOOP_DEFINE_LOCK_GUARD_; _data.push_back(ele); }
            void pushBack(const T& ele) { _CC_LOOP_DEFINE_LOCK_GUARD_; _data.push_back(ele); }

            void pushFront(T &ele) { _CC_LOOP_DEFINE_LOCK_GUARD_; _data.push_front(ele); }
            void pushFront(const T &ele) { _CC_LOOP_DEFINE_LOCK_GUARD_; _data.push_front(ele); }
            void pushFront(T &&ele) { _CC_LOOP_DEFINE_LOCK_GUARD_; _data.push_front(ele); }

            void popBack() { _CC_LOOP_DEFINE_LOCK_GUARD_; _data.pop_back(); }
            T popFront() { _CC_LOOP_DEFINE_LOCK_GUARD_; assert(_data.size() > 0); T x = _data.front(); _data.pop_front(); return x; }

            T &front() { _CC_LOOP_DEFINE_LOCK_GUARD_; return _data.front(); }
            T &back() { _CC_LOOP_DEFINE_LOCK_GUARD_; return _data.back(); }

            void clear() { _CC_LOOP_DEFINE_LOCK_GUARD_; _data.clear(); }

            size_t size() const { return _data.size(); }
            std::recursive_mutex& getMutex() { return _mtx; }
            std::list<T> & getQueue() { return _data; }

        private:
            std::recursive_mutex _mtx;
            std::list<T> _data;
        };

        template<typename K, typename V>
        class ThreadSafeMap {
        public:
            V & operator[](const K &key) { _CC_LOOP_DEFINE_LOCK_GUARD_; return _data[key]; }
            void insert(const K &key,const V &value) { _CC_LOOP_DEFINE_LOCK_GUARD_; _data.insert(std::make_pair(key, value)); }
            void erase(const K &key) { _CC_LOOP_DEFINE_LOCK_GUARD_; _data.erase(key); }
            bool exists(const K &key) { _CC_LOOP_DEFINE_LOCK_GUARD_; return _data.find(key) != _data.end(); }
            V getOrBuild(const K &key,const std::function<V(void)>& crtFn)
            {
                _CC_LOOP_DEFINE_LOCK_GUARD_;
                if (_data.find(key) == _data.end()) { //not found
                    _data.insert(std::make_pair(key, crtFn()));
                }
                return _data[key];
            }
            V &getOrInit(const K &key,const std::function<void(V&)>& initFn)
            {
                _CC_LOOP_DEFINE_LOCK_GUARD_;
                if (_data.find(key) == _data.end()) { //do init once
                    initFn(_data[key]);
                }
                return _data[key];
            }

            std::recursive_mutex& getMutex() { return _mtx; }
        private:
            std::unordered_map<K, V> _data;
            std::recursive_mutex _mtx;
        };

        template<typename K, typename V>
        class ThreadSafeMapArray {
        public:
            void add(const K&key,const V &value) { _CC_LOOP_DEFINE_LOCK_GUARD_; _data[key].push_back(value); }
            void clear(const K &key) { _CC_LOOP_DEFINE_LOCK_GUARD_; _data[key].clear(); }
            std::vector<V>& get(const K&key) { _CC_LOOP_DEFINE_LOCK_GUARD_; return _data[key]; }
            void forEach(const K &key,const std::function<void(V&)>& iterFn)
            {
                _CC_LOOP_DEFINE_LOCK_GUARD_;
                auto &list = _data[key];
                for (auto m = list.begin(); m != list.end(); m++)
                {
                    iterFn(*m);
                }
            }
            std::recursive_mutex& getMutex() { return _mtx; }
        private:
            std::unordered_map<K, std::vector<V> > _data;
            std::recursive_mutex _mtx;
        };
    }
}
#undef _CC_LOOP_DEFINE_LOCK_GUARD_
