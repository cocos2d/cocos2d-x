/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

"use strict";

function utf16to8(str) {
    var out, i, len, c;

    out = "";
    len = str.length;
    for(i = 0; i < len; i++) 
    { 
        c = str.charCodeAt(i);   
        if ((c >= 0x0001) && (c <= 0x007F))
        {
            out += str.charAt(i);
        }
        else if (c > 0x07FF)
        {
            out += String.fromCharCode(0xE0 | ((c >> 12) & 0x0F));
            out += String.fromCharCode(0x80 | ((c >>  6) & 0x3F));
            out += String.fromCharCode(0x80 | ((c >>  0) & 0x3F));
        } 
        else
        {
            out += String.fromCharCode(0xC0 | ((c >>  6) & 0x1F));
            out += String.fromCharCode(0x80 | ((c >>  0) & 0x3F));
        }
    }
    return out;
}

function utf8to16(str) {
     var out, i, len, c;
     var char2, char3;

     out = "";
     len = str.length;
     i = 0;
     while(i < len) {   c = str.charCodeAt(i++);   switch(c >> 4)
  {
    case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7:
      // 0xxxxxxx
      out += str.charAt(i-1);
      break;
    case 12: case 13:
      // 110x xxxx   10xx xxxx
      char2 = str.charCodeAt(i++);
      out += String.fromCharCode(((c & 0x1F) << 6) | (char2 & 0x3F));
      break;
    case 14:
      // 1110 xxxx  10xx xxxx  10xx xxxx
      char2 = str.charCodeAt(i++);
      char3 = str.charCodeAt(i++);
      out += String.fromCharCode(((c & 0x0F) << 12) |
         ((char2 & 0x3F) << 6) |
         ((char3 & 0x3F) << 0));
      break;
  }
     }

     return out;
 }

var dump = function(msg) {
  log(msg);
};

/* General utilities used throughout devtools. */

/* Turn the error e into a string, without fail. */
this.safeErrorString = function safeErrorString(aError) {
  try {
    var s = aError.toString();
    if (typeof s === "string")
      return s;
  } catch (ee) { }

  return "<failed trying to find error description>";
}

/**
 * Report that |aWho| threw an exception, |aException|.
 */
this.reportException = function reportException(aWho, aException) {
  let msg = aWho + " threw an exception: " + safeErrorString(aException);
  if (aException.stack) {
    msg += "\nCall stack:\n" + aException.stack;
  }

  dump(msg + "\n");

  // if (Components.utils.reportError) {
  //   /*
  //    * Note that the xpcshell test harness registers an observer for
  //    * console messages, so when we're running tests, this will cause
  //    * the test to quit.
  //    */
  //   Components.utils.reportError(msg);
  // }
}

/**
 * Given a handler function that may throw, return an infallible handler
 * function that calls the fallible handler, and logs any exceptions it
 * throws.
 *
 * @param aHandler function
 *      A handler function, which may throw.
 * @param aName string
 *      A name for aHandler, for use in error messages. If omitted, we use
 *      aHandler.name.
 *
 * (SpiderMonkey does generate good names for anonymous functions, but we
 * don't have a way to get at them from JavaScript at the moment.)
 */
this.makeInfallible = function makeInfallible(aHandler, aName) {
  if (!aName)
    aName = aHandler.name;

  return function (/* arguments */) {
    try {
      return aHandler.apply(this, arguments);
    } catch (ex) {
      let who = "Handler function";
      if (aName) {
        who += " " + aName;
      }
      reportException(who, ex);
    }
  }
}
