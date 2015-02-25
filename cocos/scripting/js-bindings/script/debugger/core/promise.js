//;(function(id, factory) { // Module boilerplate :(
//  if (typeof(define) === 'function') { // RequireJS
//    define(factory);
//  } else if (typeof(require) === 'function') { // CommonJS
//    factory.call(this, require, exports, module);
//  } else if (String(this).indexOf('BackstagePass') >= 0) { // JSM
//    this[factory.name] = {};
//    try {
//      this.console = this['Components'].utils
//          .import('resource://gre/modules/devtools/Console.jsm', {}).console;
//    }
//    catch (ex) {
//      // Avoid failures on different toolkit configurations.
//    }
//    factory(function require(uri) {
//      var imports = {};
//      this['Components'].utils.import(uri, imports);
//      return imports;
//    }, this[factory.name], { uri: __URI__, id: id });
//    this.EXPORTED_SYMBOLS = [factory.name];
//  } else {  // Browser or alike
//    var globals = this;
//    factory(function require(id) {
//      return globals[id];
//    }, (globals[id] = {}), { uri: document.location.href + '#' + id, id: id });
//  }
//}).call(this, 'promise/core', function Promise(require, exports, module) {

'use strict';

var exports = exports || {};

//module.metadata = {
//  "stability": "unstable"
//};

/**
 * Internal utility: Wraps given `value` into simplified promise, successfully
 * fulfilled to a given `value`. Note the result is not a complete promise
 * implementation, as its method `then` does not returns anything.
 */
function fulfilled(value) {
  return { then: function then(fulfill) { fulfill(value); } };
}

/**
 * Internal utility: Wraps given input into simplified promise, pre-rejected
 * with a given `reason`. Note the result is not a complete promise
 * implementation, as its method `then` does not returns anything.
 */
function rejected(reason) {
  return { then: function then(fulfill, reject) { reject(reason); } };
}

/**
 * Internal utility: Returns `true` if given `value` is a promise. Value is
 * assumed to be a promise if it implements method `then`.
 */
function isPromise(value) {
  return value && typeof(value.then) === 'function';
}

/**
 * Creates deferred object containing fresh promise & methods to either resolve
 * or reject it. The result is an object with the following properties:
 * - `promise` Eventual value representation implementing CommonJS [Promises/A]
 *   (http://wiki.commonjs.org/wiki/Promises/A) API.
 * - `resolve` Single shot function that resolves enclosed `promise` with a
 *   given `value`.
 * - `reject` Single shot function that rejects enclosed `promise` with a given
 *   `reason`.
 *
 * An optional `prototype` argument is used as a prototype of the returned
 * `promise` allowing one to implement additional API. If prototype is not
 * passed then it falls back to `Object.prototype`.
 *
 *  ## Example
 *
 *  function fetchURI(uri, type) {
 *    var deferred = defer();
 *    var request = new XMLHttpRequest();
 *    request.open("GET", uri, true);
 *    request.responseType = type;
 *    request.onload = function onload() {
 *      deferred.resolve(request.response);
 *    }
 *    request.onerror = function(event) {
 *     deferred.reject(event);
 *    }
 *    request.send();
 *
 *    return deferred.promise;
 *  }
 */
function defer(prototype) {
  // Define FIFO queue of observer pairs. Once promise is resolved & all queued
  // observers are forwarded to `result` and variable is set to `null`.
  var observers = [];

  // Promise `result`, which will be assigned a resolution value once promise
  // is resolved. Note that result will always be assigned promise (or alike)
  // object to take care of propagation through promise chains. If result is
  // `null` promise is not resolved yet.
  var result = null;

  prototype = (prototype || prototype === null) ? prototype : Object.prototype;

  // Create an object implementing promise API.
  var promise = Object.create(prototype, {
    then: { value: function then(onFulfill, onError) {
      var deferred = defer(prototype);

      function resolve(value) {
        // If `onFulfill` handler is provided resolve `deferred.promise` with
        // result of invoking it with a resolution value. If handler is not
        // provided propagate value through.
        try {
          deferred.resolve(onFulfill ? onFulfill(value) : value);
        }
        // `onFulfill` may throw exception in which case resulting promise
        // is rejected with thrown exception.
        catch(error) {
          if (exports._reportErrors && typeof(console) === 'object')
            console.error(error);
          // Note: Following is equivalent of `deferred.reject(error)`,
          // we use this shortcut to reduce a stack.
          deferred.resolve(rejected(error));
        }
      }

      function reject(reason) {
        try {
          if (onError) deferred.resolve(onError(reason));
          else deferred.resolve(rejected(reason));
        }
        catch(error) {
          if (exports._reportErrors && typeof(console) === 'object')
            console.error(error);
          deferred.resolve(rejected(error));
        }
      }

      // If enclosed promise (`this.promise`) observers queue is still alive
      // enqueue a new observer pair into it. Note that this does not
      // necessary means that promise is pending, it may already be resolved,
      // but we still have to queue observers to guarantee an order of
      // propagation.
      if (observers) {
        observers.push({ resolve: resolve, reject: reject });
      }
      // Otherwise just forward observer pair right to a `result` promise.
      else {
        result.then(resolve, reject);
      }

      return deferred.promise;
    }}
  })

  var deferred = {
    promise: promise,
    /**
     * Resolves associated `promise` to a given `value`, unless it's already
     * resolved or rejected. Note that resolved promise is not necessary a
     * successfully fulfilled. Promise may be resolved with a promise `value`
     * in which case `value` promise's fulfillment / rejection will propagate
     * up to a promise resolved with `value`.
     */
    resolve: function resolve(value) {
      if (!result) {
        // Store resolution `value` in a `result` as a promise, so that all
        // the subsequent handlers can be simply forwarded to it. Since
        // `result` will be a promise all the value / error propagation will
        // be uniformly taken care of.
        result = isPromise(value) ? value : fulfilled(value);

        // Forward already registered observers to a `result` promise in the
        // order they were registered. Note that we intentionally dequeue
        // observer at a time until queue is exhausted. This makes sure that
        // handlers registered as side effect of observer forwarding are
        // queued instead of being invoked immediately, guaranteeing FIFO
        // order.
        while (observers.length) {
          var observer = observers.shift();
          result.then(observer.resolve, observer.reject);
        }

        // Once `observers` queue is exhausted we `null`-ify it, so that
        // new handlers are forwarded straight to the `result`.
        observers = null;
      }
    },
    /**
     * Rejects associated `promise` with a given `reason`, unless it's already
     * resolved / rejected. This is just a (better performing) convenience
     * shortcut for `deferred.resolve(reject(reason))`.
     */
    reject: function reject(reason) {
      // Note that if promise is resolved that does not necessary means that it
      // is successfully fulfilled. Resolution value may be a promise in which
      // case its result propagates. In other words if promise `a` is resolved
      // with promise `b`, `a` is either fulfilled or rejected depending
      // on weather `b` is fulfilled or rejected. Here `deferred.promise` is
      // resolved with a promise pre-rejected with a given `reason`, there for
      // `deferred.promise` is rejected with a given `reason`. This may feel
      // little awkward first, but doing it this way greatly simplifies
      // propagation through promise chains.
      deferred.resolve(rejected(reason));
    }
  };

  return deferred;
}
exports.defer = defer;

/**
 * Returns a promise resolved to a given `value`. Optionally a second
 * `prototype` argument may be provided to be used as a prototype for the
 * returned promise.
 */
function resolve(value, prototype) {
  var deferred = defer(prototype);
  deferred.resolve(value);
  return deferred.promise;
}
exports.resolve = resolve;

/**
 * Returns a promise rejected with a given `reason`. Optionally a second
 * `prototype` argument may be provided to be used as a prototype for the
 * returned promise.
 */
function reject(reason, prototype) {
  var deferred = defer(prototype);
  deferred.reject(reason);
  return deferred.promise;
}
exports.reject = reject;

var promised = (function() {
  // Note: Define shortcuts and utility functions here in order to avoid
  // slower property accesses and unnecessary closure creations on each
  // call of this popular function.

  var call = Function.call;
  var concat = Array.prototype.concat;

  // Utility function that does following:
  // execute([ f, self, args...]) => f.apply(self, args)
  function execute(args) { return call.apply(call, args) }

  // Utility function that takes promise of `a` array and maybe promise `b`
  // as arguments and returns promise for `a.concat(b)`.
  function promisedConcat(promises, unknown) {
    return promises.then(function(values) {
      return resolve(unknown).then(function(value) {
        return values.concat([ value ]);
      });
    });
  }

  return function promised(f, prototype) {
    /**
    Returns a wrapped `f`, which when called returns a promise that resolves to
    `f(...)` passing all the given arguments to it, which by the way may be
    promises. Optionally second `prototype` argument may be provided to be used
    a prototype for a returned promise.

    ## Example

    var promise = promised(Array)(1, promise(2), promise(3))
    promise.then(console.log) // => [ 1, 2, 3 ]
    **/

    return function promised() {
      // create array of [ f, this, args... ]
      return concat.apply([ f, this ], arguments).
        // reduce it via `promisedConcat` to get promised array of fulfillments
        reduce(promisedConcat, resolve([], prototype)).
        // finally map that to promise of `f.apply(this, args...)`
        then(execute);
    };
  }
})();
exports.promised = promised;
//
var all = promised(Array);
exports.all = all;
//
//});
