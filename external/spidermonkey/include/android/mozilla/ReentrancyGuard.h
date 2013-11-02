/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim: set ts=8 sts=2 et sw=2 tw=80: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/* Small helper class for asserting uses of a class are non-reentrant. */

#ifndef mozilla_ReentrancyGuard_h
#define mozilla_ReentrancyGuard_h

#include "mozilla/Assertions.h"
#include "mozilla/Attributes.h"
#include "mozilla/GuardObjects.h"

namespace mozilla {

/* Useful for implementing containers that assert non-reentrancy */
class ReentrancyGuard
{
    MOZ_DECL_USE_GUARD_OBJECT_NOTIFIER
#ifdef DEBUG
    bool& entered;
#endif

  public:
    template<class T>
#ifdef DEBUG
    ReentrancyGuard(T& obj
                    MOZ_GUARD_OBJECT_NOTIFIER_PARAM)
      : entered(obj.entered)
#else
    ReentrancyGuard(T&
                    MOZ_GUARD_OBJECT_NOTIFIER_PARAM)
#endif
    {
      MOZ_GUARD_OBJECT_NOTIFIER_INIT;
#ifdef DEBUG
      MOZ_ASSERT(!entered);
      entered = true;
#endif
    }
    ~ReentrancyGuard()
    {
#ifdef DEBUG
      entered = false;
#endif
    }

  private:
    ReentrancyGuard(const ReentrancyGuard&) MOZ_DELETE;
    void operator=(const ReentrancyGuard&) MOZ_DELETE;
};

} // namespace mozilla

#endif /* mozilla_ReentrancyGuard_h */
