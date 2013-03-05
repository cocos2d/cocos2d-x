/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef json_h___
#define json_h___

#include "jsprvtd.h"
#include "jspubtd.h"
#include "jsapi.h"

#include "js/Vector.h"

#define JSON_MAX_DEPTH  2048
#define JSON_PARSER_BUFSIZE 1024

extern JSObject *
js_InitJSONClass(JSContext *cx, js::HandleObject obj);

extern JSBool
js_Stringify(JSContext *cx, js::MutableHandleValue vp,
             JSObject *replacer, js::Value space,
             js::StringBuffer &sb);

// Avoid build errors on certain platforms that define these names as constants
#undef STRICT
#undef LEGACY

/*
 * The type of JSON decoding to perform.  Strict decoding is to-the-spec;
 * legacy decoding accepts a few non-JSON syntaxes historically accepted by the
 * implementation.  (Full description of these deviations is deliberately
 * omitted.)  New users should use strict decoding rather than legacy decoding,
 * as legacy decoding might be removed at a future time.
 */
enum DecodingMode { STRICT, LEGACY };

namespace js {

extern JS_FRIEND_API(JSBool)
ParseJSONWithReviver(JSContext *cx, JS::StableCharPtr chars, size_t length, HandleValue filter,
                     MutableHandleValue vp, DecodingMode decodingMode = STRICT);

} /* namespace js */

#endif /* json_h___ */
