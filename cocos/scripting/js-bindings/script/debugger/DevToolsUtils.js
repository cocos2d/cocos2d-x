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

/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

"use strict";

/* General utilities used throughout devtools. */

// var { Ci, Cu, Cc, components } = require("chrome");
// var Services = require("Services");
// var promise = require("promise");

// loader.lazyRequireGetter(this, "FileUtils",
//                          "resource://gre/modules/FileUtils.jsm", true);

function DevToolsUtils() {

}

DevToolsUtils.utf16to8 = function utf16to8(str) {
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

DevToolsUtils.utf8to16 = function utf8to16(str) {
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

/**
 * Turn the error |aError| into a string, without fail.
 */
DevToolsUtils.safeErrorString = function safeErrorString(aError) {
  try {
    let errorString = aError.toString();
    if (typeof errorString == "string") {
      // Attempt to attach a stack to |errorString|. If it throws an error, or
      // isn't a string, don't use it.
      try {
        if (aError.stack) {
          let stack = aError.stack.toString();
          if (typeof stack == "string") {
            errorString += "\nStack: " + stack;
          }
        }
      } catch (ee) { }

      // Append additional line and column number information to the output,
      // since it might not be part of the stringified error.
      if (typeof aError.lineNumber == "number" && typeof aError.columnNumber == "number") {
        errorString += "Line: " + aError.lineNumber + ", column: " + aError.columnNumber;
      }

      return errorString;
    }
  } catch (ee) { }

  // We failed to find a good error description, so do the next best thing.
  return Object.prototype.toString.call(aError);
}

/**
 * Report that |aWho| threw an exception, |aException|.
 */
DevToolsUtils.reportException = function reportException(aWho, aException) {
  let msg = aWho + " threw an exception: " + DevToolsUtils.safeErrorString(aException);

  log(msg + "\n");

  // if (Cu && Cu.reportError) {
    
  //    * Note that the xpcshell test harness registers an observer for
  //    * console messages, so when we're running tests, this will cause
  //    * the test to quit.
     
  //   Cu.reportError(msg);
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
DevToolsUtils.makeInfallible = function makeInfallible(aHandler, aName) {
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
      return DevToolsUtils.reportException(who, ex);
    }
  }
}
/**
 * Interleaves two arrays element by element, returning the combined array, like
 * a zip. In the case of arrays with different sizes, undefined values will be
 * interleaved at the end along with the extra values of the larger array.
 *
 * @param Array a
 * @param Array b
 * @returns Array
 *          The combined array, in the form [a1, b1, a2, b2, ...]
 */
DevToolsUtils.zip = function zip(a, b) {
  if (!b) {
    return a;
  }
  if (!a) {
    return b;
  }
  const pairs = [];
  for (let i = 0, aLength = a.length, bLength = b.length;
       i < aLength || i < bLength;
       i++) {
    pairs.push([a[i], b[i]]);
  }
  return pairs;
};


/**
 * Converts an object into an array with 2-element arrays as key/value
 * pairs of the object. `{ foo: 1, bar: 2}` would become
 * `[[foo, 1], [bar 2]]` (order not guaranteed);
 *
 * @param object obj
 * @returns array
 */
DevToolsUtils.entries = function entries(obj) {
  return Object.keys(obj).map(k => [k, obj[k]]);
}

/**
 * Composes the given functions into a single function, which will
 * apply the results of each function right-to-left, starting with
 * applying the given arguments to the right-most function.
 * `compose(foo, bar, baz)` === `args => foo(bar(baz(args)`
 *
 * @param ...function funcs
 * @returns function
 */
DevToolsUtils.compose = function compose(...funcs) {
  return (...args) => {
    const initialValue = funcs[funcs.length - 1].apply(null, args);
    const leftFuncs = funcs.slice(0, -1);
    return leftFuncs.reduceRight((composed, f) => f(composed),
                                 initialValue);
  };
}


/**
 * Waits for the next tick in the event loop to execute a callback.
 */
DevToolsUtils.executeSoon = function executeSoon(aFn) {
  if (isWorker) {
    setImmediate(aFn);
  } else {
    Services.tm.mainThread.dispatch({
      run: DevToolsUtils.makeInfallible(aFn)
    }, Ci.nsIThread.DISPATCH_NORMAL);
  }
};

/**
 * Waits for the next tick in the event loop.
 *
 * @return Promise
 *         A promise that is resolved after the next tick in the event loop.
 */
DevToolsUtils.waitForTick = function waitForTick() {
  let deferred = promise.defer();
  DevToolsUtils.executeSoon(deferred.resolve);
  return deferred.promise;
};

/**
 * Waits for the specified amount of time to pass.
 *
 * @param number aDelay
 *        The amount of time to wait, in milliseconds.
 * @return Promise
 *         A promise that is resolved after the specified amount of time passes.
 */
DevToolsUtils.waitForTime = function waitForTime(aDelay) {
  let deferred = promise.defer();
  require("Timer").setTimeout(deferred.resolve, aDelay);
  return deferred.promise;
};

/**
 * Like Array.prototype.forEach, but doesn't cause jankiness when iterating over
 * very large arrays by yielding to the browser and continuing execution on the
 * next tick.
 *
 * @param Array aArray
 *        The array being iterated over.
 * @param Function aFn
 *        The function called on each item in the array. If a promise is
 *        returned by this function, iterating over the array will be paused
 *        until the respective promise is resolved.
 * @returns Promise
 *          A promise that is resolved once the whole array has been iterated
 *          over, and all promises returned by the aFn callback are resolved.
 */
DevToolsUtils.yieldingEach = function yieldingEach(aArray, aFn) {
  const deferred = promise.defer();

  let i = 0;
  let len = aArray.length;
  let outstanding = [deferred.promise];

  (function loop() {
    const start = Date.now();

    while (i < len) {
      // Don't block the main thread for longer than 16 ms at a time. To
      // maintain 60fps, you have to render every frame in at least 16ms; we
      // aren't including time spent in non-JS here, but this is Good
      // Enough(tm).
      if (Date.now() - start > 16) {
        DevToolsUtils.executeSoon(loop);
        return;
      }

      try {
        outstanding.push(aFn(aArray[i], i++));
      } catch (e) {
        deferred.reject(e);
        return;
      }
    }

    deferred.resolve();
  }());

  return promise.all(outstanding);
}

/**
 * Like XPCOMUtils.defineLazyGetter, but with a |this| sensitive getter that
 * allows the lazy getter to be defined on a prototype and work correctly with
 * instances.
 *
 * @param Object aObject
 *        The prototype object to define the lazy getter on.
 * @param String aKey
 *        The key to define the lazy getter on.
 * @param Function aCallback
 *        The callback that will be called to determine the value. Will be
 *        called with the |this| value of the current instance.
 */
DevToolsUtils.defineLazyPrototypeGetter =
function defineLazyPrototypeGetter(aObject, aKey, aCallback) {
  Object.defineProperty(aObject, aKey, {
    configurable: true,
    get: function() {
      const value = aCallback.call(this);

      Object.defineProperty(this, aKey, {
        configurable: true,
        writable: true,
        value: value
      });

      return value;
    }
  });
}

/**
 * Safely get the property value from a Debugger.Object for a given key. Walks
 * the prototype chain until the property is found.
 *
 * @param Debugger.Object aObject
 *        The Debugger.Object to get the value from.
 * @param String aKey
 *        The key to look for.
 * @return Any
 */
DevToolsUtils.getProperty = function getProperty(aObj, aKey) {
  let root = aObj;
  try {
    do {
      const desc = aObj.getOwnPropertyDescriptor(aKey);
      if (desc) {
        if ("value" in desc) {
          return desc.value;
        }
        // Call the getter if it's safe.
        return DevToolsUtils.hasSafeGetter(desc) ? desc.get.call(root).return : undefined;
      }
      aObj = aObj.proto;
    } while (aObj);
  } catch (e) {
    // If anything goes wrong report the error and return undefined.
    DevToolsUtils.reportException("getProperty", e);
  }
  return undefined;
};

/**
 * Determines if a descriptor has a getter which doesn't call into JavaScript.
 *
 * @param Object aDesc
 *        The descriptor to check for a safe getter.
 * @return Boolean
 *         Whether a safe getter was found.
 */
DevToolsUtils.hasSafeGetter = function hasSafeGetter(aDesc) {
  // Scripted functions that are CCWs will not appear scripted until after
  // unwrapping.
  // let fn = aDesc.get.unwrap();
  let fn = aDesc.get;
  return fn && fn.callable && fn.class == "Function" && fn.script === undefined;
};

/**
 * Check if it is safe to read properties and execute methods from the given JS
 * object. Safety is defined as being protected from unintended code execution
 * from content scripts (or cross-compartment code).
 *
 * See bugs 945920 and 946752 for discussion.
 *
 * @type Object aObj
 *       The object to check.
 * @return Boolean
 *         True if it is safe to read properties from aObj, or false otherwise.
 */
DevToolsUtils.isSafeJSObject = function isSafeJSObject(aObj) {
  return true;
  // If we are running on a worker thread, Cu is not available. In this case,
  // we always return false, just to be on the safe side.
  // if (isWorker) {
  //   return false;
  // }

  // if (Cu.getGlobalForObject(aObj) ==
  //     Cu.getGlobalForObject(DevToolsUtils.isSafeJSObject)) {
  //   return true; // aObj is not a cross-compartment wrapper.
  // }

  // let principal = Cu.getObjectPrincipal(aObj);
  // if (Services.scriptSecurityManager.isSystemPrincipal(principal)) {
  //   return true; // allow chrome objects
  // }

  // return Cu.isXrayWrapper(aObj);
};

DevToolsUtils.dumpn = function dumpn(str) {
  if (DevToolsUtils.dumpn.wantLogging) {
    dump("DBG-SERVER: " + str + "\n");
  }
}

// We want wantLogging to be writable. The DevToolsUtils object is frozen by the
// loader, so define it on dumpn instead.
DevToolsUtils.dumpn.wantLogging = false;

/**
 * A verbose logger for low-level tracing.
 */
DevToolsUtils.dumpv = function(msg) {
  if (DevToolsUtils.dumpv.wantVerbose) {
    DevToolsUtils.dumpn(msg);
  }
};

// We want wantLogging to be writable. The DevToolsUtils object is frozen by the
// loader, so define it on dumpn instead.
DevToolsUtils.dumpv.wantVerbose = false;

DevToolsUtils.dbg_assert = function dbg_assert(cond, e) {
  if (!cond) {
    return e;
  }
};


/**
 * Utility function for updating an object with the properties of
 * other objects.
 *
 * @param aTarget Object
 *        The object being updated.
 * @param aNewAttrs Object
 *        The rest params are objects to update aTarget with. You
 *        can pass as many as you like.
 */
DevToolsUtils.update = function update(aTarget, ...aArgs) {
  for (let attrs of aArgs) {
    for (let key in attrs) {
      let desc = Object.getOwnPropertyDescriptor(attrs, key);

      if (desc) {
        Object.defineProperty(aTarget, key, desc);
      }
    }
  }

  return aTarget;
}

/**
 * Utility function for getting the values from an object as an array
 *
 * @param aObject Object
 *        The object to iterate over
 */
DevToolsUtils.values = function values(aObject) {
  return Object.keys(aObject).map(k => aObject[k]);
}

/**
 * Defines a getter on a specified object that will be created upon first use.
 *
 * @param aObject
 *        The object to define the lazy getter on.
 * @param aName
 *        The name of the getter to define on aObject.
 * @param aLambda
 *        A function that returns what the getter should return.  This will
 *        only ever be called once.
 */
DevToolsUtils.defineLazyGetter = function defineLazyGetter(aObject, aName, aLambda) {
  Object.defineProperty(aObject, aName, {
    get: function () {
      delete aObject[aName];
      return aObject[aName] = aLambda.apply(aObject);
    },
    configurable: true,
    enumerable: true
  });
};

/**
 * Defines a getter on a specified object for a module.  The module will not
 * be imported until first use.
 *
 * @param aObject
 *        The object to define the lazy getter on.
 * @param aName
 *        The name of the getter to define on aObject for the module.
 * @param aResource
 *        The URL used to obtain the module.
 * @param aSymbol
 *        The name of the symbol exported by the module.
 *        This parameter is optional and defaults to aName.
 */
DevToolsUtils.defineLazyModuleGetter = function defineLazyModuleGetter(aObject, aName,
                                                                 aResource,
                                                                 aSymbol)
{
  this.defineLazyGetter(aObject, aName, function XPCU_moduleLambda() {
    var temp = {};
    Cu.import(aResource, temp);
    return temp[aSymbol || aName];
  });
};

DevToolsUtils.defineLazyGetter(this, "NetUtil", () => {
  return Cu.import("resource://gre/modules/NetUtil.jsm", {}).NetUtil;
});

DevToolsUtils.defineLazyGetter(this, "OS", () => {
  return Cu.import("resource://gre/modules/osfile.jsm", {}).OS;
});

DevToolsUtils.defineLazyGetter(this, "TextDecoder", () => {
  return Cu.import("resource://gre/modules/osfile.jsm", {}).TextDecoder;
});

DevToolsUtils.defineLazyGetter(this, "NetworkHelper", () => {
  return require("devtools/toolkit/webconsole/network-helper");
});

/**
 * Performs a request to load the desired URL and returns a promise.
 *
 * @param aURL String
 *        The URL we will request.
 * @param aOptions Object
 *        An object with the following optional properties:
 *        - loadFromCache: if false, will bypass the cache and
 *          always load fresh from the network (default: true)
 *        - policy: the nsIContentPolicy type to apply when fetching the URL
 *        - window: the window to get the loadGroup from
 *        - charset: the charset to use if the channel doesn't provide one
 * @returns Promise that resolves with an object with the following members on
 *          success:
 *           - content: the document at that URL, as a string,
 *           - contentType: the content type of the document
 *
 *          If an error occurs, the promise is rejected with that error.
 *
 * XXX: It may be better to use nsITraceableChannel to get to the sources
 * without relying on caching when we can (not for eval, etc.):
 * http://www.softwareishard.com/blog/firebug/nsitraceablechannel-intercept-http-traffic/
 */
function mainThreadFetch(aURL, aOptions={ loadFromCache: true,
                                          policy: Ci.nsIContentPolicy.TYPE_OTHER,
                                          window: null,
                                          charset: null }) {
  // Create a channel.
  let url = aURL.split(" -> ").pop();
  let channel;
  try {
    channel = newChannelForURL(url, aOptions);
  } catch (ex) {
    return promise.reject(ex);
  }

  // Set the channel options.
  channel.loadFlags = aOptions.loadFromCache
    ? channel.LOAD_FROM_CACHE
    : channel.LOAD_BYPASS_CACHE;

  if (aOptions.window) {
    // Respect private browsing.
    channel.loadGroup = aOptions.window.QueryInterface(Ci.nsIInterfaceRequestor)
                          .getInterface(Ci.nsIWebNavigation)
                          .QueryInterface(Ci.nsIDocumentLoader)
                          .loadGroup;
  }

  let deferred = promise.defer();
  let onResponse = (stream, status, request) => {
    if (!components.isSuccessCode(status)) {
      deferred.reject(new Error('Failed to fetch ${url}. Code ${status}.'));
      return;
    }

    try {
      // We cannot use NetUtil to do the charset conversion as if charset
      // information is not available and our default guess is wrong the method
      // might fail and we lose the stream data. This means we can't fall back
      // to using the locale default encoding (bug 1181345).

      // Read and decode the data according to the locale default encoding.
      let available = stream.available();
      let source = NetUtil.readInputStreamToString(stream, available);
      stream.close();

      // If the channel or the caller has correct charset information, the
      // content will be decoded correctly. If we have to fall back to UTF-8 and
      // the guess is wrong, the conversion fails and convertToUnicode returns
      // the input unmodified. Essentially we try to decode the data as UTF-8
      // and if that fails, we use the locale specific default encoding. This is
      // the best we can do if the source does not provide charset info.
      let charset = channel.contentCharset || aOptions.charset || "UTF-8";
      let unicodeSource = NetworkHelper.convertToUnicode(source, charset);

      deferred.resolve({
        content: unicodeSource,
        contentType: request.contentType
      });
    } catch (ex) {
      let uri = request.originalURI;
      if (ex.name === "NS_BASE_STREAM_CLOSED" && uri instanceof Ci.nsIFileURL) {
        // Empty files cause NS_BASE_STREAM_CLOSED exception. Use OS.File to
        // differentiate between empty files and other errors (bug 1170864).
        // This can be removed when bug 982654 is fixed.

        uri.QueryInterface(Ci.nsIFileURL);
        let result = OS.File.read(uri.file.path).then(bytes => {
          // Convert the bytearray to a String.
          let decoder = new TextDecoder();
          let content = decoder.decode(bytes);

          // We can't detect the contentType without opening a channel
          // and that failed already. This is the best we can do here.
          return {
            content,
            contentType: "text/plain"
          };
        });

        deferred.resolve(result);
      } else {
        deferred.reject(ex);
      }
    }
  };

  // Open the channel
  try {
    NetUtil.asyncFetch(channel, onResponse);
  } catch (ex) {
    return promise.reject(ex);
  }

  return deferred.promise;
}

/**
 * Opens a channel for given URL. Tries a bit harder than NetUtil.newChannel.
 *
 * @param {String} url - The URL to open a channel for.
 * @param {Object} options - The options object passed to @method fetch.
 * @return {nsIChannel} - The newly created channel. Throws on failure.
 */
function newChannelForURL(url, { policy }) {
  let channelOptions = {
    contentPolicyType: policy,
    loadUsingSystemPrincipal: true,
    uri: url
  };

  try {
    return NetUtil.newChannel(channelOptions);
  } catch (e) {
    // In the xpcshell tests, the script url is the absolute path of the test
    // file, which will make a malformed URI error be thrown. Add the file
    // scheme to see if it helps.
    channelOptions.uri = "file://" + url;

    return NetUtil.newChannel(channelOptions);
  }
}

// Fetch is defined differently depending on whether we are on the main thread
// or a worker thread.
if (!this.isWorker) {
  DevToolsUtils.fetch = mainThreadFetch;
} else {
  // Services is not available in worker threads, nor is there any other way
  // to fetch a URL. We need to enlist the help from the main thread here, by
  // issuing an rpc request, to fetch the URL on our behalf.
  DevToolsUtils.fetch = function (url, options) {
    return rpc("fetch", url, options);
  }
}

/**
 * Returns a promise that is resolved or rejected when all promises have settled
 * (resolved or rejected).
 *
 * This differs from Promise.all, which will reject immediately after the first
 * rejection, instead of waiting for the remaining promises to settle.
 *
 * @param values
 *        Iterable of promises that may be pending, resolved, or rejected. When
 *        when all promises have settled (resolved or rejected), the returned
 *        promise will be resolved or rejected as well.
 *
 * @return A new promise that is fulfilled when all values have settled
 *         (resolved or rejected). Its resolution value will be an array of all
 *         resolved values in the given order, or undefined if values is an
 *         empty array. The reject reason will be forwarded from the first
 *         promise in the list of given promises to be rejected.
 */
DevToolsUtils.settleAll = values => {
  if (values === null || typeof(values[Symbol.iterator]) != "function") {
    throw new Error("settleAll() expects an iterable.");
  }

  let deferred = promise.defer();

  values = Array.isArray(values) ? values : [...values];
  let countdown = values.length;
  let resolutionValues = new Array(countdown);
  let rejectionValue;
  let rejectionOccurred = false;

  if (!countdown) {
    deferred.resolve(resolutionValues);
    return deferred.promise;
  }

  function checkForCompletion() {
    if (--countdown > 0) {
      return;
    }
    if (!rejectionOccurred) {
      deferred.resolve(resolutionValues);
    } else {
      deferred.reject(rejectionValue);
    }
  }

  for (let i = 0; i < values.length; i++) {
    let index = i;
    let value = values[i];
    let resolver = result => {
      resolutionValues[index] = result;
      checkForCompletion();
    };
    let rejecter = error => {
      if (!rejectionOccurred) {
        rejectionValue = error;
        rejectionOccurred = true;
      }
      checkForCompletion();
    };

    if (value && typeof(value.then) == "function") {
      value.then(resolver, rejecter);
    } else {
      // Given value is not a promise, forward it as a resolution value.
      resolver(value);
    }
  }

  return deferred.promise;
};

/**
 * When the testing flag is set, various behaviors may be altered from
 * production mode, typically to enable easier testing or enhanced debugging.
 */
var testing = false;
Object.defineProperty(DevToolsUtils, "testing", {
  get: function() {
    return testing;
  },
  set: function(state) {
    testing = state;
  }
});

/**
 * Open the file at the given path for reading.
 *
 * @param {String} filePath
 *
 * @returns Promise<nsIInputStream>
 */
DevToolsUtils.openFileStream = function (filePath) {
  return new Promise((resolve, reject) => {
    const uri = NetUtil.newURI(new FileUtils.File(filePath));
    NetUtil.asyncFetch(
      { uri, loadUsingSystemPrincipal: true },
      (stream, result) => {
        if (!components.isSuccessCode(result)) {
          reject(new Error('Could not open "${filePath}": result = ${result}'));
          return;
        }

        resolve(stream);
      }
    );
  });
}
