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
#include <string>
#include <functional>
#include "cocos2d.h"

NS_CC_BEGIN
namespace android {

class Queue final {
	typedef std::recursive_mutex Mutex;
	typedef std::lock_guard<Mutex> Lock;
public:
	class PopDelegate{
	public:
		PopDelegate() = default;
		virtual ~PopDelegate() = 0;
	public:
		virtual void onPopString(int const code, std::string const& val) {CC_UNUSED_PARAM(code);CC_UNUSED_PARAM(val);};
		virtual void onPopFunction(int const code, std::function<void()> const& val) {CC_UNUSED_PARAM(code);CC_UNUSED_PARAM(val);};
		virtual void onPopInteger(int const code, int val) {CC_UNUSED_PARAM(code);CC_UNUSED_PARAM(val);};
		virtual void onPopFloat(int const code, float val) {CC_UNUSED_PARAM(code);CC_UNUSED_PARAM(val);};
		virtual void onPopBinary(int const code, std::vector<char> const& val) {CC_UNUSED_PARAM(code);CC_UNUSED_PARAM(val);};
		virtual void onPopArray(int const code, cocos2d::Array* val) {CC_UNUSED_PARAM(code);CC_UNUSED_PARAM(val);};
		virtual void onPopObject(int const code, cocos2d::Object* val) {CC_UNUSED_PARAM(code);CC_UNUSED_PARAM(val);};
	};
	class Payload final {
	public:
		enum class Type {
			Empty,
			String,
			Function,
			Integer,
			Float,
			Binary,
			Array,
			Object
		};
	public:
		template <typename T> Payload(int code, T const& t);
		~Payload();
		Payload();
		Payload(Payload const& other);
		Payload& operator=(Payload const& other);
	private:
		const int code_;
		Type const type_;
		union {
			std::nullptr_t null_;
			std::string string_;
			std::function<void()> function_;
			int int_;
			float float_;
			std::vector<char> binary_;
			cocos2d::Array* array_;
			cocos2d::Object* object_;
		};
	private:
		void copy(Payload const& other);
		void del();
	public:
		template <typename T> bool is() const;
		template <typename T> T const& as(T const& defaultValue) const;
		int code() const { return code_; };
		Type type() const { return type_; };
		std::string typeString() const;
		void unbox(PopDelegate& listener);
		template <typename T, typename U> Payload& ifTypeIs(std::function<U(int,T const&)> const& f) {
			if(is<T>()){
				f(code_, this->as<T>(T()));
			}
			return *this;
		};
	};
private:
	std::deque<Payload> queue_;
	Mutex mutex_;
public:
	template <typename T> inline void push(int const code, T const& t) {
		Lock lock(mutex_);
		this->queue_.push_back( Payload(code, t) );
	}
	bool pop(Payload& p);
	bool pop();
	bool pop(PopDelegate& listener);
	template <typename T> inline bool pop(int& code, T& t) {
	}
};

#define IS(type, varname, Enum) template <> inline bool Queue::Payload::is< type >() const { return this->type_ == Type::Enum; };
		IS(std::nullptr_t, null_, Empty);
		IS(std::string, string_, String);
		IS(std::function<void()>, function_, Function);
		IS(int, int_, Integer);
		IS(float, float_, Float);
		IS(std::vector<char>, binary_, Binary);
		IS(cocos2d::Array*, array_, Array);
		IS(cocos2d::Object*, object_, Object);
#undef IS
#define AS(type, varname, Enum)\
	template <> inline type const& Queue::Payload::as< type >(type const& defaultValue) const {\
		if(is<type>()) {\
			return varname;\
		}else{\
			std::string msg(std::string("Type mismatched: " #type "!= ") + typeString());\
			CCLOGERROR("%s", msg.c_str() );\
			return defaultValue;\
		}\
	};
		AS(std::nullptr_t, null_, Empty);
		AS(std::string, string_, String);
		AS(std::function<void()>, function_, Function);
		AS(int, int_, Integer);
		AS(float, float_, Float);
		AS(std::vector<char>, binary_, Binary);
		AS(cocos2d::Array*, array_, Array);
		AS(cocos2d::Object*, object_, Object);
#undef AS
#define CONS(type, varname, Enum)\
	template <> inline Queue::Payload::Payload(int code,type const& t)\
	:code_(code)\
	 ,type_(Type::Enum)\
	 ,varname(t){};
		CONS(std::nullptr_t, null_, Empty);
		CONS(std::string, string_, String);
		CONS(std::function<void()>, function_, Function);
		CONS(int, int_, Integer);
		CONS(float, float_, Float);
		CONS(std::vector<char>, binary_, Binary);
		CONS(cocos2d::Array*, array_, Array);
		CONS(cocos2d::Object*, object_, Object);
#undef CONS

}
NS_CC_END

