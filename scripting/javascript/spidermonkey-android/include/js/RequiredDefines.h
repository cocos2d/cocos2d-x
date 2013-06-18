/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * vim: set ts=8 sw=4 et tw=79:
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/*
 * Various #defines required to build SpiderMonkey.  Embedders should add this
 * file to the start of the command line via -include or a similar mechanism,
 * or SpiderMonkey public headers may not work correctly.
 */

#ifndef js_RequiredDefines_h___
#define js_RequiredDefines_h___

/*
 * The c99 defining the limit macros (UINT32_MAX for example), says:
 * C++ implementations should define these macros only when __STDC_LIMIT_MACROS
 * is defined before <stdint.h> is included.
 */
#define __STDC_LIMIT_MACROS

#endif /* js_RequiredDefines_h___ */
