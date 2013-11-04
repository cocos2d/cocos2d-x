/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim: set ts=8 sts=2 et sw=2 tw=80: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/* A number of structures to simplify scope-based RAII management. */

#ifndef mozilla_Scoped_h
#define mozilla_Scoped_h

/*
 * Resource Acquisition Is Initialization is a programming idiom used
 * to write robust code that is able to deallocate resources properly,
 * even in presence of execution errors or exceptions that need to be
 * propagated.  The Scoped* classes defined in this header perform the
 * deallocation of the resource they hold once program execution
 * reaches the end of the scope for which they have been defined.
 *
 * This header provides the following RAII classes:
 *
 * - |ScopedFreePtr| - a container for a pointer, that automatically calls
 *   |free()| at the end of the scope;
 * - |ScopedDeletePtr| - a container for a pointer, that automatically calls
 *   |delete| at the end of the scope;
 * - |ScopedDeleteArray| - a container for a pointer to an array, that
 *   automatically calls |delete[]| at the end of the scope.
 *
 * The general scenario for each of the RAII classes is the following:
 *
 * ScopedClass foo(create_value());
 * // ... In this scope, |foo| is defined. Use |foo.get()| or |foo.rwget()|
 *        to access the value.
 * // ... In case of |return| or |throw|, |foo| is deallocated automatically.
 * // ... If |foo| needs to be returned or stored, use |foo.forget()|
 *
 * Note that the RAII classes defined in this header do _not_ perform any form
 * of reference-counting or garbage-collection. These classes have exactly two
 * behaviors:
 *
 * - if |forget()| has not been called, the resource is always deallocated at
 *   the end of the scope;
 * - if |forget()| has been called, any control on the resource is unbound
 *   and the resource is not deallocated by the class.
 *
 * Extension:
 *
 * In addition, this header provides class |Scoped| and macros |SCOPED_TEMPLATE|
 * and |MOZ_TYPE_SPECIFIC_SCOPED_POINTER_TEMPLATE|  to simplify the definition
 * of RAII classes for other scenarios. These macros have been used to
 * automatically close file descriptors/file handles when reaching the end of
 * the scope, graphics contexts, etc.
 */

#include "mozilla/Attributes.h"
#include "mozilla/GuardObjects.h"
#include "mozilla/NullPtr.h"

namespace mozilla {

/*
 * Scoped is a helper to create RAII wrappers
 * Type argument |Traits| is expected to have the following structure:
 *
 *   struct Traits {
 *     // Define the type of the value stored in the wrapper
 *     typedef value_type type;
 *     // Returns the value corresponding to the uninitialized or freed state
 *     const static type empty();
 *     // Release resources corresponding to the wrapped value
 *     // This function is responsible for not releasing an |empty| value
 *     const static void release(type);
 *   }
 */
template<typename Traits>
class Scoped
{
  public:
    typedef typename Traits::type Resource;

    explicit Scoped(MOZ_GUARD_OBJECT_NOTIFIER_ONLY_PARAM)
      : value(Traits::empty())
    {
      MOZ_GUARD_OBJECT_NOTIFIER_INIT;
    }
    explicit Scoped(const Resource& v
                    MOZ_GUARD_OBJECT_NOTIFIER_PARAM)
      : value(v)
    {
      MOZ_GUARD_OBJECT_NOTIFIER_INIT;
    }
    ~Scoped() {
      Traits::release(value);
    }

    // Constant getter
    operator const Resource&() const { return value; }
    const Resource& operator->() const { return value; }
    const Resource& get() const { return value; }
    // Non-constant getter.
    Resource& rwget() { return value; }

    /*
     * Forget the resource.
     *
     * Once |forget| has been called, the |Scoped| is neutralized, i.e. it will
     * have no effect at destruction (unless it is reset to another resource by
     * |operator=|).
     *
     * @return The original resource.
     */
    Resource forget() {
      Resource tmp = value;
      value = Traits::empty();
      return tmp;
    }

    /*
     * Perform immediate clean-up of this |Scoped|.
     *
     * If this |Scoped| is currently empty, this method has no effect.
     */
    void dispose() {
      Traits::release(value);
      value = Traits::empty();
    }

    bool operator==(const Resource& other) const {
      return value == other;
    }

    /*
     * Replace the resource with another resource.
     *
     * Calling |operator=| has the side-effect of triggering clean-up. If you do
     * not want to trigger clean-up, you should first invoke |forget|.
     *
     * @return this
     */
    Scoped<Traits>& operator=(const Resource& other) {
      return reset(other);
    }
    Scoped<Traits>& reset(const Resource& other) {
      Traits::release(value);
      value = other;
      return *this;
    }

  private:
    explicit Scoped(const Scoped<Traits>& value) MOZ_DELETE;
    Scoped<Traits>& operator=(const Scoped<Traits>& value) MOZ_DELETE;

  private:
    Resource value;
    MOZ_DECL_USE_GUARD_OBJECT_NOTIFIER
};

/*
 * SCOPED_TEMPLATE defines a templated class derived from Scoped
 * This allows to implement templates such as ScopedFreePtr.
 *
 * @param name The name of the class to define.
 * @param Traits A struct implementing clean-up. See the implementations
 * for more details.
 */
#define SCOPED_TEMPLATE(name, Traits)                          \
template<typename Type>                                        \
struct name : public mozilla::Scoped<Traits<Type> >            \
{                                                              \
    typedef mozilla::Scoped<Traits<Type> > Super;              \
    typedef typename Super::Resource Resource;                 \
    name& operator=(Resource ptr) {                            \
      Super::operator=(ptr);                                   \
      return *this;                                            \
    }                                                          \
    explicit name(MOZ_GUARD_OBJECT_NOTIFIER_ONLY_PARAM)        \
      : Super(MOZ_GUARD_OBJECT_NOTIFIER_ONLY_PARAM_TO_PARENT)  \
    {}                                                         \
    explicit name(Resource ptr                                 \
                  MOZ_GUARD_OBJECT_NOTIFIER_PARAM)             \
      : Super(ptr MOZ_GUARD_OBJECT_NOTIFIER_PARAM_TO_PARENT)   \
    {}                                                         \
  private:                                                     \
    explicit name(name& source) MOZ_DELETE;                    \
    name& operator=(name& source) MOZ_DELETE;                  \
};

/*
 * ScopedFreePtr is a RAII wrapper for pointers that need to be free()d.
 *
 *   struct S { ... };
 *   ScopedFreePtr<S> foo = malloc(sizeof(S));
 *   ScopedFreePtr<char> bar = strdup(str);
 */
template<typename T>
struct ScopedFreePtrTraits
{
    typedef T* type;
    static T* empty() { return nullptr; }
    static void release(T* ptr) { free(ptr); }
};
SCOPED_TEMPLATE(ScopedFreePtr, ScopedFreePtrTraits)

/*
 * ScopedDeletePtr is a RAII wrapper for pointers that need to be deleted.
 *
 *   struct S { ... };
 *   ScopedDeletePtr<S> foo = new S();
 */
template<typename T>
struct ScopedDeletePtrTraits : public ScopedFreePtrTraits<T>
{
    static void release(T* ptr) { delete ptr; }
};
SCOPED_TEMPLATE(ScopedDeletePtr, ScopedDeletePtrTraits)

/*
 * ScopedDeleteArray is a RAII wrapper for pointers that need to be delete[]ed.
 *
 *   struct S { ... };
 *   ScopedDeleteArray<S> foo = new S[42];
 */
template<typename T>
struct ScopedDeleteArrayTraits : public ScopedFreePtrTraits<T>
{
    static void release(T* ptr) { delete [] ptr; }
};
SCOPED_TEMPLATE(ScopedDeleteArray, ScopedDeleteArrayTraits)

/*
 * MOZ_TYPE_SPECIFIC_SCOPED_POINTER_TEMPLATE makes it easy to create scoped
 * pointers for types with custom deleters; just overload
 * TypeSpecificDelete(T*) in the same namespace as T to call the deleter for
 * type T.
 *
 * @param name The name of the class to define.
 * @param Type A struct implementing clean-up. See the implementations
 * for more details.
 * *param Deleter The function that is used to delete/destroy/free a
 *        non-null value of Type*.
 *
 * Example:
 *
 *   MOZ_TYPE_SPECIFIC_SCOPED_POINTER_TEMPLATE(ScopedPRFileDesc, PRFileDesc, \
 *                                             PR_Close)
 *   ...
 *   {
 *       ScopedPRFileDesc file(PR_OpenFile(...));
 *       ...
 *   } // file is closed with PR_Close here
 */
#define MOZ_TYPE_SPECIFIC_SCOPED_POINTER_TEMPLATE(name, Type, Deleter) \
template <> inline void TypeSpecificDelete(Type * value) { Deleter(value); } \
typedef ::mozilla::TypeSpecificScopedPointer<Type> name;

template <typename T> void TypeSpecificDelete(T * value);

template <typename T>
struct TypeSpecificScopedPointerTraits
{
    typedef T* type;
    const static type empty() { return nullptr; }
    const static void release(type value)
    {
      if (value)
        TypeSpecificDelete(value);
    }
};

SCOPED_TEMPLATE(TypeSpecificScopedPointer, TypeSpecificScopedPointerTraits)

} /* namespace mozilla */

#endif /* mozilla_Scoped_h */
