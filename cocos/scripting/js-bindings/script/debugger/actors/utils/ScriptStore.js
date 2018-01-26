/* -*- indent-tabs-mode: nil; js-indent-level: 2; js-indent-level: 2 -*- */
/* vim: set ft=javascript ts=2 et sw=2 tw=80: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

"use strict";

const { noop } = DevToolsUtils;

/**
 * A `ScriptStore` is a cache of `Debugger.Script` instances. It holds strong
 * references to the cached scripts to alleviate the GC-sensitivity issues that
 * plague `Debugger.prototype.findScripts`, but this means that its lifetime
 * must be managed carefully. It is the `ScriptStore` user's responsibility to
 * ensure that the `ScriptStore` stays up to date.
 *
 * Implementation Notes:
 *
 * The ScriptStore's prototype methods are very hot, in general. To help the
 * JIT, they avoid ES6-isms and higher-order iteration functions, for the most
 * part. You might be wondering why we don't maintain indices on, say,
 * Debugger.Source for faster querying, if these methods are so hot. First, the
 * hottest method is actually just getting all scripts; second, populating the
 * store becomes prohibitively expensive. So we fall back to linear queries
 * (which isn't so bad, because Debugger.prototype.findScripts is also linear).
 */
function ScriptStore() {
  // Set of every Debugger.Script in the cache.
  this._scripts = new NoDeleteSet;
}

// module.exports = ScriptStore;

ScriptStore.prototype = {
  // Populating a ScriptStore.

  /**
   * Add one script to the cache.
   *
   * @param Debugger.Script script
   */
  addScript: function(script) {
    this._scripts.add(script);
  },

  /**
   * Add many scripts to the cache at once.
   *
   * @param Array scripts
   *        The set of Debugger.Scripts to add to the cache.
   */
  addScripts: function(scripts) {
    for (var i = 0, len = scripts.length; i < len; i++) {
      this.addScript(scripts[i]);
    }
  },

  // Querying a ScriptStore.

  /**
   * Get all the sources for which we have scripts cached.
   *
   * @returns Array of Debugger.Source
   */
  getSources: function() {
    return [...new Set(this._scripts.items.map(s => s.source))];
  },

  /**
   * Get all the scripts in the cache.
   *
   * @returns read-only Array of Debugger.Script.
   *
   * NB: The ScriptStore retains ownership of the returned array, and the
   * ScriptStore's consumers MUST NOT MODIFY its contents!
   */
  getAllScripts: function() {
    return this._scripts.items;
  },

  getScriptsBySourceActor: function(sourceActor) {
    return sourceActor.source ?
           this.getScriptsBySource(sourceActor.source) :
           this.getScriptsByURL(sourceActor._originalUrl);
  },

  getScriptsBySourceActorAndLine: function(sourceActor, line) {
    return sourceActor.source ?
           this.getScriptsBySourceAndLine(sourceActor.source, line) :
           this.getScriptsByURLAndLine(sourceActor._originalUrl, line);
  },

  /**
   * Get all scripts produced from the given source.
   *
   * @param Debugger.Source source
   * @returns Array of Debugger.Script
   */
  getScriptsBySource: function(source) {
    var results = [];
    var scripts = this._scripts.items;
    var length = scripts.length;
    for (var i = 0; i < length; i++) {
      if (scripts[i].source === source) {
        results.push(scripts[i]);
      }
    }
    return results;
  },

  /**
   * Get all scripts produced from the given source whose source code definition
   * spans the given line.
   *
   * @param Debugger.Source source
   * @param Number line
   * @returns Array of Debugger.Script
   */
  getScriptsBySourceAndLine: function(source, line) {
    var results = [];
    var scripts = this._scripts.items;
    var length = scripts.length;
    for (var i = 0; i < length; i++) {
      var script = scripts[i];
      if (script.source === source &&
          script.startLine <= line &&
          (script.startLine + script.lineCount) > line) {
        results.push(script);
      }
    }
    return results;
  },

  /**
   * Get all scripts defined by a source at the given URL.
   *
   * @param String url
   * @returns Array of Debugger.Script
   */
  getScriptsByURL: function(url) {
    var results = [];
    var scripts = this._scripts.items;
    var length = scripts.length;
    for (var i = 0; i < length; i++) {
      if (scripts[i].url === url) {
        results.push(scripts[i]);
      }
    }
    return results;
  },

  /**
   * Get all scripts defined by a source a the given URL and whose source code
   * definition spans the given line.
   *
   * @param String url
   * @param Number line
   * @returns Array of Debugger.Script
   */
  getScriptsByURLAndLine: function(url, line) {
    var results = [];
    var scripts = this._scripts.items;
    var length = scripts.length;
    for (var i = 0; i < length; i++) {
      var script = scripts[i];
      if (script.url === url &&
          script.startLine <= line &&
          (script.startLine + script.lineCount) > line) {
        results.push(script);
      }
    }
    return results;
  },
};


/**
 * A set which can only grow, and does not support the delete operation.
 * Provides faster iteration than the native Set by maintaining an array of all
 * items, in addition to the internal set of all items, which allows direct
 * iteration (without the iteration protocol and calling into C++, which are
 * both expensive).
 */
function NoDeleteSet() {
  this._set = new Set();
  this.items = [];
}

NoDeleteSet.prototype = {
  /**
   * An array containing every item in the set for convenience and faster
   * iteration. This is public for reading only, and consumers MUST NOT modify
   * this array!
   */
  items: null,

  /**
   * Add an item to the set.
   *
   * @param any item
   */
  add: function(item) {
    if (!this._set.has(item)) {
      this._set.add(item);
      this.items.push(item);
    }
  },

  /**
   * Return true if the item is in the set, false otherwise.
   *
   * @param any item
   * @returns Boolean
   */
  has: function(item) {
    return this._set.has(item);
  }
};
