/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/* Implementation of macros to ensure correct use of RAII Auto* objects. */

#ifndef mozilla_GuardObjects_h
#define mozilla_GuardObjects_h

#include "mozilla/Assertions.h"
#include "mozilla/Types.h"

#ifdef __cplusplus

#ifdef DEBUG

namespace mozilla {
namespace detail {

/*
 * The following classes are designed to cause assertions to detect
 * inadvertent use of guard objects as temporaries. In other words,
 * when we have a guard object whose only purpose is its constructor and
 * destructor (and is never otherwise referenced), the intended use
 * might be:
 *
 *   AutoRestore savePainting(mIsPainting);
 *
 * but is is easy to accidentally write:
 *
 *   AutoRestore(mIsPainting);
 *
 * which compiles just fine, but runs the destructor well before the
 * intended time.
 *
 * They work by adding (#ifdef DEBUG) an additional parameter to the
 * guard object's constructor, with a default value, so that users of
 * the guard object's API do not need to do anything. The default value
 * of this parameter is a temporary object. C++ (ISO/IEC 14882:1998),
 * section 12.2 [class.temporary], clauses 4 and 5 seem to assume a
 * guarantee that temporaries are destroyed in the reverse of their
 * construction order, but I actually can't find a statement that that
 * is true in the general case (beyond the two specific cases mentioned
 * there). However, it seems to be true.
 *
 * These classes are intended to be used only via the macros immediately
 * below them:
 *
 *   MOZ_DECL_USE_GUARD_OBJECT_NOTIFIER declares (ifdef DEBUG) a member
 *     variable, and should be put where a declaration of a private
 *     member variable would be placed.
 *   MOZ_GUARD_OBJECT_NOTIFIER_PARAM should be placed at the end of the
 *     parameters to each constructor of the guard object; it declares
 *     (ifdef DEBUG) an additional parameter. (But use the *_ONLY_PARAM
 *     variant for constructors that take no other parameters.)
 *   MOZ_GUARD_OBJECT_NOTIFIER_PARAM_IN_IMPL should likewise be used in
 *     the implementation of such constructors when they are not inline.
 *   MOZ_GUARD_OBJECT_NOTIFIER_PARAM_TO_PARENT should be used in
 *     the implementation of such constructors to pass the parameter to
 *     a base class that also uses these macros
 *   MOZ_GUARD_OBJECT_NOTIFIER_INIT is a statement that belongs in each
 *     constructor. It uses the parameter declared by
 *     MOZ_GUARD_OBJECT_NOTIFIER_PARAM.
 *
 * For more details, and examples of using these macros, see
 * https://developer.mozilla.org/en/Using_RAII_classes_in_Mozilla
 */
class MOZ_EXPORT GuardObjectNotifier
{
  private:
    bool* statementDone;

  public:
    GuardObjectNotifier() : statementDone(NULL) { }

    ~GuardObjectNotifier() {
      *statementDone = true;
    }

    void setStatementDone(bool* statementIsDone) {
      statementDone = statementIsDone;
    }
};

class MOZ_EXPORT GuardObjectNotificationReceiver
{
  private:
    bool statementDone;

  public:
    GuardObjectNotificationReceiver() : statementDone(false) { }

    ~GuardObjectNotificationReceiver() {
      /*
       * Assert that the guard object was not used as a temporary.  (Note that
       * this assert might also fire if init is not called because the guard
       * object's implementation is not using the above macros correctly.)
       */
      MOZ_ASSERT(statementDone);
    }

    void init(const GuardObjectNotifier& constNotifier) {
      /*
       * constNotifier is passed as a const reference so that we can pass a
       * temporary, but we really intend it as non-const.
       */
      GuardObjectNotifier& notifier = const_cast<GuardObjectNotifier&>(constNotifier);
      notifier.setStatementDone(&statementDone);
    }
};

} /* namespace detail */
} /* namespace mozilla */

#endif /* DEBUG */

#ifdef DEBUG
#  define MOZ_DECL_USE_GUARD_OBJECT_NOTIFIER \
     mozilla::detail::GuardObjectNotificationReceiver _mCheckNotUsedAsTemporary;
#  define MOZ_GUARD_OBJECT_NOTIFIER_PARAM \
     , const mozilla::detail::GuardObjectNotifier& _notifier = \
         mozilla::detail::GuardObjectNotifier()
#  define MOZ_GUARD_OBJECT_NOTIFIER_ONLY_PARAM \
     const mozilla::detail::GuardObjectNotifier& _notifier = \
         mozilla::detail::GuardObjectNotifier()
#  define MOZ_GUARD_OBJECT_NOTIFIER_PARAM_IN_IMPL \
     , const mozilla::detail::GuardObjectNotifier& _notifier
#  define MOZ_GUARD_OBJECT_NOTIFIER_PARAM_TO_PARENT \
     , _notifier
#  define MOZ_GUARD_OBJECT_NOTIFIER_ONLY_PARAM_TO_PARENT \
       _notifier
#  define MOZ_GUARD_OBJECT_NOTIFIER_INIT \
     do { _mCheckNotUsedAsTemporary.init(_notifier); } while (0)
#else
#  define MOZ_DECL_USE_GUARD_OBJECT_NOTIFIER
#  define MOZ_GUARD_OBJECT_NOTIFIER_PARAM
#  define MOZ_GUARD_OBJECT_NOTIFIER_ONLY_PARAM
#  define MOZ_GUARD_OBJECT_NOTIFIER_PARAM_IN_IMPL
#  define MOZ_GUARD_OBJECT_NOTIFIER_ONLY_PARAM_TO_PARENT
#  define MOZ_GUARD_OBJECT_NOTIFIER_PARAM_TO_PARENT
#  define MOZ_GUARD_OBJECT_NOTIFIER_INIT do { } while (0)
#endif

#endif /* __cplusplus */

#endif /* mozilla_GuardObjects_h */
