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

#include "Queue.h"

NS_CC_BEGIN
namespace android {

Queue::PopDelegate::~PopDelegate() {

}

Queue::Payload::Payload()
:code_(0),type_(Type::Empty), null_(nullptr)
{
}
Queue::Payload::Payload(Payload const& other)
:code_(other.code_),type_(other.type_)
{
	copy(other);
}
Queue::Payload& Queue::Payload::operator=(Payload const& other)
{
	del();
	copy(other);
	return *this;
}

void Queue::Payload::copy(Payload const& other)
{
	switch(other.type_){
	case Type::Empty:
		this->null_ = nullptr;
		break;
	case Type::String:
		new (&this->string_) std::string (other.string_);
		break;
	case Type::Function:
		new (&this->function_) std::function<void()> (other.function_);
		break;
	case Type::Integer:
		this->int_ = other.int_;
		break;
	case Type::Float:
		this->float_ = other.float_;
		break;
	case Type::Binary:
		new (&this->binary_) std::vector<char> (other.binary_);
		break;
	case Type::Array:
		this->array_ = other.array_;
		break;
	case Type::Object:
		this->object_ = other.object_;
		break;
	}
	const_cast<int&>(this->code_) = other.code_;
	const_cast<Type&>(this->type_) = other.type_;
}
void Queue::Payload::del()
{
	switch(this->type_){
	case Type::Empty:
		break;
	case Type::String:
		this->string_.~basic_string<char>();
		break;
	case Type::Function:
		this->function_.~function();
		break;
	case Type::Integer:
		break;
	case Type::Float:
		break;
	case Type::Binary:
		this->binary_.~vector();
		break;
	case Type::Array:
		this->array_->release();
		break;
	case Type::Object:
		this->object_->release();
		break;
	}
	const_cast<int&>(this->code_) = 0;
	const_cast<Type&>(this->type_) = Type::Empty;
	this->null_ = nullptr;
}

std::string Queue::Payload::typeString() const
{
	switch(this->type_){
	case Type::Empty:
		return "nullptr_t";
	case Type::String:
		return "std::string";
	case Type::Function:
		return "std::function<void()>";
	case Type::Integer:
		return "int";
	case Type::Float:
		return "float";
	case Type::Binary:
		return "std::vector<char>";
	case Type::Array:
		return "cocos2d::Array*";
	case Type::Object:
		return "cocos2d::Object*";
	}
}

void Queue::Payload::unbox(PopDelegate& listener)
{
	switch(this->type_){
	case Type::Empty:
		break;
	case Type::String:
		listener.onPopString(code_, string_);
		break;
	case Type::Function:
		listener.onPopFunction(code_, function_);
		break;
	case Type::Integer:
		listener.onPopInteger(code_, int_);
		break;
	case Type::Float:
		listener.onPopFloat(code_, float_);
		break;
	case Type::Binary:
		listener.onPopBinary(code_, binary_);
		break;
	case Type::Array:
		listener.onPopArray(code_, array_);
		break;
	case Type::Object:
		listener.onPopObject(code_, object_);
		break;
	}
}
Queue::Payload::~Payload()
{
	del();
}

bool Queue::pop(PopDelegate& listener)
{
	Payload p;
	if( this->pop(p) ) {
		p.unbox(listener);
		return true;
	}else{
		return false;
	}
}

bool Queue::pop(Queue::Payload& p)
{
	Lock lock(mutex_);
	if( this->queue_.empty() ) {
		return false;
	}else{
		p = this->queue_.front();
		this->queue_.pop_front();
		return true;
	}
}
bool Queue::pop()
{
	Lock lock(mutex_);
	if( this->queue_.empty() ) {
		return false;
	}else{
		this->queue_.pop_front();
		return true;
	}
}

}
NS_CC_END
