/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is Mozilla Communicator client code, released
 * March 31, 1998.
 *
 * The Initial Developer of the Original Code is
 * Netscape Communications Corporation.
 * Portions created by the Initial Developer are Copyright (C) 1998
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either of the GNU General Public License Version 2 or later (the "GPL"),
 * or the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */
#ifndef jslock_h__
#define jslock_h__

#include "jsapi.h"

#ifdef JS_THREADSAFE

# include "pratom.h"
# include "prlock.h"
# include "prcvar.h"
# include "prthread.h"
# include "prinit.h"

# define JS_ATOMIC_INCREMENT(p)      PR_ATOMIC_INCREMENT((PRInt32 *)(p))
# define JS_ATOMIC_DECREMENT(p)      PR_ATOMIC_DECREMENT((PRInt32 *)(p))
# define JS_ATOMIC_ADD(p,v)          PR_ATOMIC_ADD((PRInt32 *)(p), (PRInt32)(v))
# define JS_ATOMIC_SET(p,v)          PR_ATOMIC_SET((PRInt32 *)(p), (PRInt32)(v))

#else  /* JS_THREADSAFE */

# define JS_ATOMIC_INCREMENT(p)      (++*(p))
# define JS_ATOMIC_DECREMENT(p)      (--*(p))
# define JS_ATOMIC_ADD(p,v)          (*(p) += (v))
# define JS_ATOMIC_SET(p,v)          (*(p) = (v))

#endif /* JS_THREADSAFE */

namespace js {

class AutoAtomicIncrement
{
    int32_t *p;
    JS_DECL_USE_GUARD_OBJECT_NOTIFIER

  public:
    AutoAtomicIncrement(int32_t *p JS_GUARD_OBJECT_NOTIFIER_PARAM)
      : p(p) {
        JS_GUARD_OBJECT_NOTIFIER_INIT;
        JS_ATOMIC_INCREMENT(p);
    }

    ~AutoAtomicIncrement() {
        JS_ATOMIC_DECREMENT(p);
    }
};

}  /* namespace js */

#endif /* jslock_h___ */
