/* -*- js-indent-level: 2; indent-tabs-mode: nil -*- */
/* vim: set ft=javascript ts=2 et sw=2 tw=80: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

"use strict";

// const {Cc, Ci, Cu, components} = require("chrome");
// const {isWindowIncluded} = require("devtools/toolkit/layout/utils");

// Cu.import("resource://gre/modules/XPCOMUtils.jsm");

// loader.lazyImporter(this, "Services", "resource://gre/modules/Services.jsm");

// TODO: Bug 842672 - browser/ imports modules from toolkit/.
// Note that these are only used in WebConsoleCommands, see $0 and pprint().
// loader.lazyImporter(this, "VariablesView", "resource:///modules/devtools/VariablesView.jsm");
// const DevToolsUtils = require("devtools/toolkit/DevToolsUtils");

// Match the function name from the result of toString() or toSource().
//
// Examples:
// (function foobar(a, b) { ...
// function foobar2(a) { ...
// function() { ...

var exports = exports || {};


const REGEX_MATCH_FUNCTION_NAME = /^\(?function\s+([^(\s]+)\s*\(/;

// Match the function arguments from the result of toString() or toSource().
const REGEX_MATCH_FUNCTION_ARGS = /^\(?function\s*[^\s(]*\s*\((.+?)\)/;

// Number of terminal entries for the self-xss prevention to go away
const CONSOLE_ENTRY_THRESHOLD = 5;

// Provide an easy way to bail out of even attempting an autocompletion
// if an object has way too many properties. Protects against large objects
// with numeric values that wouldn't be tallied towards MAX_AUTOCOMPLETIONS.
const MAX_AUTOCOMPLETE_ATTEMPTS = exports.MAX_AUTOCOMPLETE_ATTEMPTS = 100000;

const CONSOLE_WORKER_IDS =  exports.CONSOLE_WORKER_IDS =[ 'SharedWorker', 'ServiceWorker', 'Worker' ];

// Prevent iterating over too many properties during autocomplete suggestions.
const MAX_AUTOCOMPLETIONS = exports.MAX_AUTOCOMPLETIONS = 1500;

var WebConsoleUtils = {

  /**
   * Wrap a string in an nsISupportsString object.
   *
   * @param string aString
   * @return nsISupportsString
   */
  supportsString: function WCU_supportsString(aString)
  {
    let str = Cc["@mozilla.org/supports-string;1"].
              createInstance(Ci.nsISupportsString);
    str.data = aString;
    return str;
  },

  /**
   * Clone an object.
   *
   * @param object aObject
   *        The object you want cloned.
   * @param boolean aRecursive
   *        Tells if you want to dig deeper into the object, to clone
   *        recursively.
   * @param function [aFilter]
   *        Optional, filter function, called for every property. Three
   *        arguments are passed: key, value and object. Return true if the
   *        property should be added to the cloned object. Return false to skip
   *        the property.
   * @return object
   *         The cloned object.
   */
  cloneObject: function WCU_cloneObject(aObject, aRecursive, aFilter)
  {
    if (typeof aObject != "object") {
      return aObject;
    }

    let temp;

    if (Array.isArray(aObject)) {
      temp = [];
      Array.forEach(aObject, function(aValue, aIndex) {
        if (!aFilter || aFilter(aIndex, aValue, aObject)) {
          temp.push(aRecursive ? WCU_cloneObject(aValue) : aValue);
        }
      });
    }
    else {
      temp = {};
      for (let key in aObject) {
        let value = aObject[key];
        if (aObject.hasOwnProperty(key) &&
            (!aFilter || aFilter(key, value, aObject))) {
          temp[key] = aRecursive ? WCU_cloneObject(value) : value;
        }
      }
    }

    return temp;
  },

  /**
   * Copies certain style attributes from one element to another.
   *
   * @param nsIDOMNode aFrom
   *        The target node.
   * @param nsIDOMNode aTo
   *        The destination node.
   */
  copyTextStyles: function WCU_copyTextStyles(aFrom, aTo)
  {
    let win = aFrom.ownerDocument.defaultView;
    let style = win.getComputedStyle(aFrom);
    aTo.style.fontFamily = style.getPropertyCSSValue("font-family").cssText;
    aTo.style.fontSize = style.getPropertyCSSValue("font-size").cssText;
    aTo.style.fontWeight = style.getPropertyCSSValue("font-weight").cssText;
    aTo.style.fontStyle = style.getPropertyCSSValue("font-style").cssText;
  },

  /**
   * Gets the ID of the inner window of this DOM window.
   *
   * @param nsIDOMWindow aWindow
   * @return integer
   *         Inner ID for the given aWindow.
   */
  getInnerWindowId: function WCU_getInnerWindowId(aWindow)
  {
    return aWindow.QueryInterface(Ci.nsIInterfaceRequestor).
             getInterface(Ci.nsIDOMWindowUtils).currentInnerWindowID;
  },

  /**
   * Recursively gather a list of inner window ids given a
   * top level window.
   *
   * @param nsIDOMWindow aWindow
   * @return Array
   *         list of inner window ids.
   */
  getInnerWindowIDsForFrames: function WCU_getInnerWindowIDsForFrames(aWindow)
  {
    let innerWindowID = this.getInnerWindowId(aWindow);
    let ids = [innerWindowID];

    if (aWindow.frames) {
      for (let i = 0; i < aWindow.frames.length; i++) {
        let frame = aWindow.frames[i];
        ids = ids.concat(this.getInnerWindowIDsForFrames(frame));
      }
    }

    return ids;
  },


  /**
   * Gets the ID of the outer window of this DOM window.
   *
   * @param nsIDOMWindow aWindow
   * @return integer
   *         Outer ID for the given aWindow.
   */
  getOuterWindowId: function WCU_getOuterWindowId(aWindow)
  {
    return aWindow.QueryInterface(Ci.nsIInterfaceRequestor).
           getInterface(Ci.nsIDOMWindowUtils).outerWindowID;
  },

  /**
   * Abbreviates the given source URL so that it can be displayed flush-right
   * without being too distracting.
   *
   * @param string aSourceURL
   *        The source URL to shorten.
   * @param object [aOptions]
   *        Options:
   *        - onlyCropQuery: boolean that tells if the URL abbreviation function
   *        should only remove the query parameters and the hash fragment from
   *        the given URL.
   * @return string
   *         The abbreviated form of the source URL.
   */
  abbreviateSourceURL:
  function WCU_abbreviateSourceURL(aSourceURL, aOptions = {})
  {
    if (!aOptions.onlyCropQuery && aSourceURL.substr(0, 5) == "data:") {
      let commaIndex = aSourceURL.indexOf(",");
      if (commaIndex > -1) {
        aSourceURL = "data:" + aSourceURL.substring(commaIndex + 1);
      }
    }

    // Remove any query parameters.
    let hookIndex = aSourceURL.indexOf("?");
    if (hookIndex > -1) {
      aSourceURL = aSourceURL.substring(0, hookIndex);
    }

    // Remove any hash fragments.
    let hashIndex = aSourceURL.indexOf("#");
    if (hashIndex > -1) {
      aSourceURL = aSourceURL.substring(0, hashIndex);
    }

    // Remove a trailing "/".
    if (aSourceURL[aSourceURL.length - 1] == "/") {
      aSourceURL = aSourceURL.replace(/\/+$/, "");
    }

    // Remove all but the last path component.
    if (!aOptions.onlyCropQuery) {
      let slashIndex = aSourceURL.lastIndexOf("/");
      if (slashIndex > -1) {
        aSourceURL = aSourceURL.substring(slashIndex + 1);
      }
    }

    return aSourceURL;
  },

  /**
   * Tells if the given function is native or not.
   *
   * @param function aFunction
   *        The function you want to check if it is native or not.
   * @return boolean
   *         True if the given function is native, false otherwise.
   */
  isNativeFunction: function WCU_isNativeFunction(aFunction)
  {
    return typeof aFunction == "function" && !("prototype" in aFunction);
  },

  /**
   * Tells if the given property of the provided object is a non-native getter or
   * not.
   *
   * @param object aObject
   *        The object that contains the property.
   * @param string aProp
   *        The property you want to check if it is a getter or not.
   * @return boolean
   *         True if the given property is a getter, false otherwise.
   */
  isNonNativeGetter: function WCU_isNonNativeGetter(aObject, aProp)
  {
    if (typeof aObject != "object") {
      return false;
    }
    let desc = this.getPropertyDescriptor(aObject, aProp);
    return desc && desc.get && !this.isNativeFunction(desc.get);
  },

  /**
   * Get the property descriptor for the given object.
   *
   * @param object aObject
   *        The object that contains the property.
   * @param string aProp
   *        The property you want to get the descriptor for.
   * @return object
   *         Property descriptor.
   */
  getPropertyDescriptor: function WCU_getPropertyDescriptor(aObject, aProp)
  {
    let desc = null;
    while (aObject) {
      try {
        if ((desc = Object.getOwnPropertyDescriptor(aObject, aProp))) {
          break;
        }
      } catch (ex) {
        // Native getters throw here. See bug 520882.
        // null throws TypeError.
        if (ex.name != "NS_ERROR_XPC_BAD_CONVERT_JS" &&
            ex.name != "NS_ERROR_XPC_BAD_OP_ON_WN_PROTO" &&
            ex.name != "TypeError") {
          throw ex;
        }
      }

      try {
        aObject = Object.getPrototypeOf(aObject);
      } catch (ex) {
        if (ex.name == "TypeError") {
          return desc;
        }
        throw ex;
      }
    }
    return desc;
  },

  /**
   * Sort function for object properties.
   *
   * @param object a
   *        Property descriptor.
   * @param object b
   *        Property descriptor.
   * @return integer
   *         -1 if a.name < b.name,
   *         1 if a.name > b.name,
   *         0 otherwise.
   */
  propertiesSort: function WCU_propertiesSort(a, b)
  {
    // Convert the pair.name to a number for later sorting.
    let aNumber = parseFloat(a.name);
    let bNumber = parseFloat(b.name);

    // Sort numbers.
    if (!isNaN(aNumber) && isNaN(bNumber)) {
      return -1;
    }
    else if (isNaN(aNumber) && !isNaN(bNumber)) {
      return 1;
    }
    else if (!isNaN(aNumber) && !isNaN(bNumber)) {
      return aNumber - bNumber;
    }
    // Sort string.
    else if (a.name < b.name) {
      return -1;
    }
    else if (a.name > b.name) {
      return 1;
    }
    else {
      return 0;
    }
  },

  /**
   * Create a grip for the given value. If the value is an object,
   * an object wrapper will be created.
   *
   * @param mixed aValue
   *        The value you want to create a grip for, before sending it to the
   *        client.
   * @param function aObjectWrapper
   *        If the value is an object then the aObjectWrapper function is
   *        invoked to give us an object grip. See this.getObjectGrip().
   * @return mixed
   *         The value grip.
   */
  createValueGrip: function WCU_createValueGrip(aValue, aObjectWrapper)
  {
    switch (typeof aValue) {
      case "boolean":
        return aValue;
      case "string":
        return aObjectWrapper(aValue);
      case "number":
        if (aValue === Infinity) {
          return { type: "Infinity" };
        }
        else if (aValue === -Infinity) {
          return { type: "-Infinity" };
        }
        else if (Number.isNaN(aValue)) {
          return { type: "NaN" };
        }
        else if (!aValue && 1 / aValue === -Infinity) {
          return { type: "-0" };
        }
        return aValue;
      case "undefined":
        return { type: "undefined" };
      case "object":
        if (aValue === null) {
          return { type: "null" };
        }
      case "function":
        return aObjectWrapper(aValue);
      default:
        Cu.reportError("Failed to provide a grip for value of " + typeof aValue
                       + ": " + aValue);
        return null;
    }
  },

  /**
   * Check if the given object is an iterator or a generator.
   *
   * @param object aObject
   *        The object you want to check.
   * @return boolean
   *         True if the given object is an iterator or a generator, otherwise
   *         false is returned.
   */
  isIteratorOrGenerator: function WCU_isIteratorOrGenerator(aObject)
  {
    if (aObject === null) {
      return false;
    }

    if (typeof aObject == "object") {
      if (typeof aObject.__iterator__ == "function" ||
          aObject.constructor && aObject.constructor.name == "Iterator") {
        return true;
      }

      try {
        let str = aObject.toString();
        if (typeof aObject.next == "function" &&
            str.indexOf("[object Generator") == 0) {
          return true;
        }
      }
      catch (ex) {
        // window.history.next throws in the typeof check above.
        return false;
      }
    }

    return false;
  },

  /**
   * Determine if the given request mixes HTTP with HTTPS content.
   *
   * @param string aRequest
   *        Location of the requested content.
   * @param string aLocation
   *        Location of the current page.
   * @return boolean
   *         True if the content is mixed, false if not.
   */
  isMixedHTTPSRequest: function WCU_isMixedHTTPSRequest(aRequest, aLocation)
  {
    try {
      let requestURI = Services.io.newURI(aRequest, null, null);
      let contentURI = Services.io.newURI(aLocation, null, null);
      return (contentURI.scheme == "https" && requestURI.scheme != "https");
    }
    catch (ex) {
      return false;
    }
  },

  /**
   * Helper function to deduce the name of the provided function.
   *
   * @param function aFunction
   *        The function whose name will be returned.
   * @return string
   *         Function name.
   */
  getFunctionName: function WCF_getFunctionName(aFunction)
  {
    let name = null;
    if (aFunction.name) {
      name = aFunction.name;
    }
    else {
      let desc;
      try {
        desc = aFunction.getOwnPropertyDescriptor("displayName");
      }
      catch (ex) { }
      if (desc && typeof desc.value == "string") {
        name = desc.value;
      }
    }
    if (!name) {
      try {
        let str = (aFunction.toString() || aFunction.toSource()) + "";
        name = (str.match(REGEX_MATCH_FUNCTION_NAME) || [])[1];
      }
      catch (ex) { }
    }
    return name;
  },

  /**
   * Get the object class name. For example, the |window| object has the Window
   * class name (based on [object Window]).
   *
   * @param object aObject
   *        The object you want to get the class name for.
   * @return string
   *         The object class name.
   */
  getObjectClassName: function WCU_getObjectClassName(aObject)
  {
    if (aObject === null) {
      return "null";
    }
    if (aObject === undefined) {
      return "undefined";
    }

    let type = typeof aObject;
    if (type != "object") {
      // Grip class names should start with an uppercase letter.
      return type.charAt(0).toUpperCase() + type.substr(1);
    }

    let className;

    try {
      className = ((aObject + "").match(/^\[object (\S+)\]$/) || [])[1];
      if (!className) {
        className = ((aObject.constructor + "").match(/^\[object (\S+)\]$/) || [])[1];
      }
      if (!className && typeof aObject.constructor == "function") {
        className = this.getFunctionName(aObject.constructor);
      }
    }
    catch (ex) { }

    return className;
  },

  /**
   * Check if the given value is a grip with an actor.
   *
   * @param mixed aGrip
   *        Value you want to check if it is a grip with an actor.
   * @return boolean
   *         True if the given value is a grip with an actor.
   */
  isActorGrip: function WCU_isActorGrip(aGrip)
  {
    return aGrip && typeof(aGrip) == "object" && aGrip.actor;
  },
  /**
   * Value of devtools.selfxss.count preference
   *
   * @type number
   * @private
   */
  _usageCount: 0,
  get usageCount() {
    if (WebConsoleUtils._usageCount < CONSOLE_ENTRY_THRESHOLD) {
      WebConsoleUtils._usageCount = Services.prefs.getIntPref("devtools.selfxss.count");
      if (Services.prefs.getBoolPref("devtools.chrome.enabled")) {
        WebConsoleUtils.usageCount = CONSOLE_ENTRY_THRESHOLD;
      }
    }
    return WebConsoleUtils._usageCount;
  },
  set usageCount(newUC) {
    if (newUC <= CONSOLE_ENTRY_THRESHOLD) {
      WebConsoleUtils._usageCount = newUC;
      Services.prefs.setIntPref("devtools.selfxss.count", newUC);
    }
  },
  /**
   * The inputNode "paste" event handler generator. Helps prevent self-xss attacks
   *
   * @param nsIDOMElement inputField
   * @param nsIDOMElement notificationBox
   * @returns A function to be added as a handler to 'paste' and 'drop' events on the input field
   */
  pasteHandlerGen: function WCU_pasteHandlerGen(inputField, notificationBox, msg, okstring) {
    let handler = function WCU_pasteHandler(aEvent) {
      if (WebConsoleUtils.usageCount >= CONSOLE_ENTRY_THRESHOLD) {
        inputField.removeEventListener("paste", handler);
        inputField.removeEventListener("drop", handler);
        return true;
      }
      if (notificationBox.getNotificationWithValue("selfxss-notification")) {
        aEvent.preventDefault();
        aEvent.stopPropagation();
        return false;
      }


      let notification = notificationBox.appendNotification(msg,
        "selfxss-notification", null, notificationBox.PRIORITY_WARNING_HIGH, null,
        function(eventType) {
          // Cleanup function if notification is dismissed
          if (eventType == "removed") {
            inputField.removeEventListener("keyup", pasteKeyUpHandler);
          }
        });

      function pasteKeyUpHandler(aEvent2) {
        let value = inputField.value || inputField.textContent;
        if (value.includes(okstring)) {
          notificationBox.removeNotification(notification);
          inputField.removeEventListener("keyup", pasteKeyUpHandler);
          WebConsoleUtils.usageCount = CONSOLE_ENTRY_THRESHOLD;
        }
      }
      inputField.addEventListener("keyup", pasteKeyUpHandler);

      aEvent.preventDefault();
      aEvent.stopPropagation();
      return false;
    };
    return handler;
  },


};

exports.Utils = WebConsoleUtils;

//////////////////////////////////////////////////////////////////////////
// Localization
//////////////////////////////////////////////////////////////////////////

WebConsoleUtils.l10n = function WCU_l10n(aBundleURI)
{
  this._bundleUri = aBundleURI;
};

WebConsoleUtils.l10n.prototype = {
  _stringBundle: null,

  get stringBundle()
  {
    if (!this._stringBundle) {
      this._stringBundle = Services.strings.createBundle(this._bundleUri);
    }
    return this._stringBundle;
  },

  /**
   * Generates a formatted timestamp string for displaying in console messages.
   *
   * @param integer [aMilliseconds]
   *        Optional, allows you to specify the timestamp in milliseconds since
   *        the UNIX epoch.
   * @return string
   *         The timestamp formatted for display.
   */
  timestampString: function WCU_l10n_timestampString(aMilliseconds)
  {
    let d = new Date(aMilliseconds ? aMilliseconds : null);
    let hours = d.getHours(), minutes = d.getMinutes();
    let seconds = d.getSeconds(), milliseconds = d.getMilliseconds();
    let parameters = [hours, minutes, seconds, milliseconds];
    return this.getFormatStr("timestampFormat", parameters);
  },

  /**
   * Retrieve a localized string.
   *
   * @param string aName
   *        The string name you want from the Web Console string bundle.
   * @return string
   *         The localized string.
   */
  getStr: function WCU_l10n_getStr(aName)
  {
    let result;
    try {
      result = this.stringBundle.GetStringFromName(aName);
    }
    catch (ex) {
      Cu.reportError("Failed to get string: " + aName);
      throw ex;
    }
    return result;
  },

  /**
   * Retrieve a localized string formatted with values coming from the given
   * array.
   *
   * @param string aName
   *        The string name you want from the Web Console string bundle.
   * @param array aArray
   *        The array of values you want in the formatted string.
   * @return string
   *         The formatted local string.
   */
  getFormatStr: function WCU_l10n_getFormatStr(aName, aArray)
  {
    let result;
    try {
      result = this.stringBundle.formatStringFromName(aName, aArray, aArray.length);
    }
    catch (ex) {
      Cu.reportError("Failed to format string: " + aName);
      throw ex;
    }
    return result;
  },
};


//////////////////////////////////////////////////////////////////////////
// JS Completer
//////////////////////////////////////////////////////////////////////////

(function _JSPP(WCU) {
const STATE_NORMAL = 0;
const STATE_QUOTE = 2;
const STATE_DQUOTE = 3;

const OPEN_BODY = "{[(".split("");
const CLOSE_BODY = "}])".split("");
const OPEN_CLOSE_BODY = {
  "{": "}",
  "[": "]",
  "(": ")",
};

/**
 * Analyses a given string to find the last statement that is interesting for
 * later completion.
 *
 * @param   string aStr
 *          A string to analyse.
 *
 * @returns object
 *          If there was an error in the string detected, then a object like
 *
 *            { err: "ErrorMesssage" }
 *
 *          is returned, otherwise a object like
 *
 *            {
 *              state: STATE_NORMAL|STATE_QUOTE|STATE_DQUOTE,
 *              startPos: index of where the last statement begins
 *            }
 */
function findCompletionBeginning(aStr)
{
  let bodyStack = [];

  let state = STATE_NORMAL;
  let start = 0;
  let c;
  for (let i = 0; i < aStr.length; i++) {
    c = aStr[i];

    switch (state) {
      // Normal JS state.
      case STATE_NORMAL:
        if (c == '"') {
          state = STATE_DQUOTE;
        }
        else if (c == "'") {
          state = STATE_QUOTE;
        }
        else if (c == ";") {
          start = i + 1;
        }
        else if (c == " ") {
          start = i + 1;
        }
        else if (OPEN_BODY.indexOf(c) != -1) {
          bodyStack.push({
            token: c,
            start: start
          });
          start = i + 1;
        }
        else if (CLOSE_BODY.indexOf(c) != -1) {
          var last = bodyStack.pop();
          if (!last || OPEN_CLOSE_BODY[last.token] != c) {
            return {
              err: "syntax error"
            };
          }
          if (c == "}") {
            start = i + 1;
          }
          else {
            start = last.start;
          }
        }
        break;

      // Double quote state > " <
      case STATE_DQUOTE:
        if (c == "\\") {
          i++;
        }
        else if (c == "\n") {
          return {
            err: "unterminated string literal"
          };
        }
        else if (c == '"') {
          state = STATE_NORMAL;
        }
        break;

      // Single quote state > ' <
      case STATE_QUOTE:
        if (c == "\\") {
          i++;
        }
        else if (c == "\n") {
          return {
            err: "unterminated string literal"
          };
        }
        else if (c == "'") {
          state = STATE_NORMAL;
        }
        break;
    }
  }

  return {
    state: state,
    startPos: start
  };
}

/**
 * Provides a list of properties, that are possible matches based on the passed
 * Debugger.Environment/Debugger.Object and inputValue.
 *
 * @param object aDbgObject
 *        When the debugger is not paused this Debugger.Object wraps the scope for autocompletion.
 *        It is null if the debugger is paused.
 * @param object anEnvironment
 *        When the debugger is paused this Debugger.Environment is the scope for autocompletion.
 *        It is null if the debugger is not paused.
 * @param string aInputValue
 *        Value that should be completed.
 * @param number [aCursor=aInputValue.length]
 *        Optional offset in the input where the cursor is located. If this is
 *        omitted then the cursor is assumed to be at the end of the input
 *        value.
 * @returns null or object
 *          If no completion valued could be computed, null is returned,
 *          otherwise a object with the following form is returned:
 *            {
 *              matches: [ string, string, string ],
 *              matchProp: Last part of the inputValue that was used to find
 *                         the matches-strings.
 *            }
 */
function JSPropertyProvider(aDbgObject, anEnvironment, aInputValue, aCursor)
{
  if (aCursor === undefined) {
    aCursor = aInputValue.length;
  }

  let inputValue = aInputValue.substring(0, aCursor);

  // Analyse the inputValue and find the beginning of the last part that
  // should be completed.
  let beginning = findCompletionBeginning(inputValue);

  // There was an error analysing the string.
  if (beginning.err) {
    return null;
  }

  // If the current state is not STATE_NORMAL, then we are inside of an string
  // which means that no completion is possible.
  if (beginning.state != STATE_NORMAL) {
    return null;
  }

  let completionPart = inputValue.substring(beginning.startPos);

  // Don't complete on just an empty string.
  if (completionPart.trim() == "") {
    return null;
  }

  let lastDot = completionPart.lastIndexOf(".");
  if (lastDot > 0 &&
      (completionPart[0] == "'" || completionPart[0] == '"') &&
      completionPart[lastDot - 1] == completionPart[0]) {
    // We are completing a string literal.
    let matchProp = completionPart.slice(lastDot + 1);
    return getMatchedProps(String.prototype, matchProp);
  }

  // We are completing a variable / a property lookup.
  let properties = completionPart.split(".");
  let matchProp = properties.pop().trimLeft();
  let obj = aDbgObject;

  // The first property must be found in the environment if the debugger is
  // paused.
  if (anEnvironment) {
    if (properties.length == 0) {
      return getMatchedPropsInEnvironment(anEnvironment, matchProp);
    }
    obj = getVariableInEnvironment(anEnvironment, properties.shift());
  }

  if (!isObjectUsable(obj)) {
    return null;
  }

  // We get the rest of the properties recursively starting from the Debugger.Object
  // that wraps the first property
  for (let prop of properties) {
    prop = prop.trim();
    if (!prop) {
      return null;
    }

    if (/\[\d+\]$/.test(prop)) {
      // The property to autocomplete is a member of array. For example
      // list[i][j]..[n]. Traverse the array to get the actual element.
      obj = getArrayMemberProperty(obj, prop);
    }
    else {
      obj = DevToolsUtils.getProperty(obj, prop);
    }

    if (!isObjectUsable(obj)) {
      return null;
    }
  }

  // If the final property is a primitive
  if (typeof obj != "object") {
    return getMatchedProps(obj, matchProp);
  }

  return getMatchedPropsInDbgObject(obj, matchProp);
}

/**
 * Get the array member of aObj for the given aProp. For example, given
 * aProp='list[0][1]' the element at [0][1] of aObj.list is returned.
 *
 * @param object aObj
 *        The object to operate on.
 * @param string aProp
 *        The property to return.
 * @return null or Object
 *         Returns null if the property couldn't be located. Otherwise the array
 *         member identified by aProp.
 */
function getArrayMemberProperty(aObj, aProp)
{
  // First get the array.
  let obj = aObj;
  let propWithoutIndices = aProp.substr(0, aProp.indexOf("["));
  obj = DevToolsUtils.getProperty(obj, propWithoutIndices);
  if (!isObjectUsable(obj)) {
    return null;
  }

  // Then traverse the list of indices to get the actual element.
  let result;
  let arrayIndicesRegex = /\[[^\]]*\]/g;
  while ((result = arrayIndicesRegex.exec(aProp)) !== null) {
    let indexWithBrackets = result[0];
    let indexAsText = indexWithBrackets.substr(1, indexWithBrackets.length - 2);
    let index = parseInt(indexAsText);

    if (isNaN(index)) {
      return null;
    }

    obj = DevToolsUtils.getProperty(obj, index);

    if (!isObjectUsable(obj)) {
      return null;
    }
  }

  return obj;
}

/**
 * Check if the given Debugger.Object can be used for autocomplete.
 *
 * @param Debugger.Object aObject
 *        The Debugger.Object to check.
 * @return boolean
 *         True if further inspection into the object is possible, or false
 *         otherwise.
 */
function isObjectUsable(aObject)
{
  if (aObject == null) {
    return false;
  }

  if (typeof aObject == "object" && aObject.class == "DeadObject") {
    return false;
  }

  return true;
}

/**
 * @see getExactMatch_impl()
 */
function getVariableInEnvironment(anEnvironment, aName)
{
  return getExactMatch_impl(anEnvironment, aName, DebuggerEnvironmentSupport);
}

/**
 * @see getMatchedProps_impl()
 */
function getMatchedPropsInEnvironment(anEnvironment, aMatch)
{
  return getMatchedProps_impl(anEnvironment, aMatch, DebuggerEnvironmentSupport);
}

/**
 * @see getMatchedProps_impl()
 */
function getMatchedPropsInDbgObject(aDbgObject, aMatch)
{
  return getMatchedProps_impl(aDbgObject, aMatch, DebuggerObjectSupport);
}

/**
 * @see getMatchedProps_impl()
 */
function getMatchedProps(aObj, aMatch)
{
  if (typeof aObj != "object") {
    aObj = aObj.constructor.prototype;
  }
  return getMatchedProps_impl(aObj, aMatch, JSObjectSupport);
}

/**
 * Get all properties in the given object (and its parent prototype chain) that
 * match a given prefix.
 *
 * @param mixed aObj
 *        Object whose properties we want to filter.
 * @param string aMatch
 *        Filter for properties that match this string.
 * @return object
 *         Object that contains the matchProp and the list of names.
 */
function getMatchedProps_impl(aObj, aMatch, {chainIterator, getProperties})
{
  let matches = new Set();
  let numProps = 0;

  // We need to go up the prototype chain.
  let iter = chainIterator(aObj);
  for (let obj of iter) {
    let props = getProperties(obj);
    numProps += props.length;

    // If there are too many properties to event attempt autocompletion,
    // or if we have already added the max number, then stop looping
    // and return the partial set that has already been discovered.
    if (numProps >= MAX_AUTOCOMPLETE_ATTEMPTS ||
        matches.size >= MAX_AUTOCOMPLETIONS) {
      break;
    }

    for (let i = 0; i < props.length; i++) {
      let prop = props[i];
      if (prop.indexOf(aMatch) != 0) {
        continue;
      }
      if (prop.indexOf('-') > -1) {
        continue;
      }
      // If it is an array index, we can't take it.
      // This uses a trick: converting a string to a number yields NaN if
      // the operation failed, and NaN is not equal to itself.
      if (+prop != +prop) {
        matches.add(prop);
      }

      if (matches.size >= MAX_AUTOCOMPLETIONS) {
        break;
      }
    }
  }

  return {
    matchProp: aMatch,
    matches: [...matches],
  };
}

/**
 * Returns a property value based on its name from the given object, by
 * recursively checking the object's prototype.
 *
 * @param object aObj
 *        An object to look the property into.
 * @param string aName
 *        The property that is looked up.
 * @returns object|undefined
 *        A Debugger.Object if the property exists in the object's prototype
 *        chain, undefined otherwise.
 */
function getExactMatch_impl(aObj, aName, {chainIterator, getProperty})
{
  // We need to go up the prototype chain.
  let iter = chainIterator(aObj);
  for (let obj of iter) {
    let prop = getProperty(obj, aName, aObj);
    if (prop) {
      return prop.value;
    }
  }
  return undefined;
}


var JSObjectSupport = {
  chainIterator: function*(aObj)
  {
    while (aObj) {
      yield aObj;
      aObj = Object.getPrototypeOf(aObj);
    }
  },

  getProperties: function(aObj)
  {
    return Object.getOwnPropertyNames(aObj);
  },

  getProperty: function()
  {
    // getProperty is unsafe with raw JS objects.
    throw "Unimplemented!";
  },
};

var DebuggerObjectSupport = {
  chainIterator: function*(aObj)
  {
    while (aObj) {
      yield aObj;
      aObj = aObj.proto;
    }
  },

  getProperties: function(aObj)
  {
    return aObj.getOwnPropertyNames();
  },

  getProperty: function(aObj, aName, aRootObj)
  {
    // This is left unimplemented in favor to DevToolsUtils.getProperty().
    throw "Unimplemented!";
  },
};

var DebuggerEnvironmentSupport = {
  chainIterator: function*(aObj)
  {
    while (aObj) {
      yield aObj;
      aObj = aObj.parent;
    }
  },

  getProperties: function(aObj)
  {
    return aObj.names();
  },

  getProperty: function(aObj, aName)
  {
    // TODO: we should use getVariableDescriptor() here - bug 725815.
    let result = aObj.getVariable(aName);
    // FIXME: Need actual UI, bug 941287.
    if (result === undefined || result.optimizedOut || result.missingArguments) {
      return null;
    }
    return { value: result };
  },
};


exports.JSPropertyProvider = DevToolsUtils.makeInfallible(JSPropertyProvider);
})(WebConsoleUtils);

///////////////////////////////////////////////////////////////////////////////
// The page errors listener
///////////////////////////////////////////////////////////////////////////////

/**
 * The nsIConsoleService listener. This is used to send all of the console
 * messages (JavaScript, CSS and more) to the remote Web Console instance.
 *
 * @constructor
 * @param nsIDOMWindow [aWindow]
 *        Optional - the window object for which we are created. This is used
 *        for filtering out messages that belong to other windows.
 * @param object aListener
 *        The listener object must have one method:
 *        - onConsoleServiceMessage(). This method is invoked with one argument,
 *        the nsIConsoleMessage, whenever a relevant message is received.
 */
function ConsoleServiceListener(aWindow, aListener)
{
  this.window = aWindow;
  this.listener = aListener;
}
exports.ConsoleServiceListener = ConsoleServiceListener;

ConsoleServiceListener.prototype =
{
  // QueryInterface: XPCOMUtils.generateQI([Ci.nsIConsoleListener]),

  /**
   * The content window for which we listen to page errors.
   * @type nsIDOMWindow
   */
  window: null,

  /**
   * The listener object which is notified of messages from the console service.
   * @type object
   */
  listener: null,

  /**
   * Initialize the nsIConsoleService listener.
   */
  init: function CSL_init()
  {
    Services.console.registerListener(this);
  },

  /**
   * The nsIConsoleService observer. This method takes all the script error
   * messages belonging to the current window and sends them to the remote Web
   * Console instance.
   *
   * @param nsIConsoleMessage aMessage
   *        The message object coming from the nsIConsoleService.
   */
  observe: function CSL_observe(aMessage)
  {
    if (!this.listener) {
      return;
    }

    if (this.window) {
      if (!(aMessage instanceof Ci.nsIScriptError) ||
          !aMessage.outerWindowID ||
          !this.isCategoryAllowed(aMessage.category)) {
        return;
      }

      let errorWindow = Services.wm.getOuterWindowWithId(aMessage .outerWindowID);
      if (!errorWindow || !isWindowIncluded(this.window, errorWindow)) {
        return;
      }
    }

    this.listener.onConsoleServiceMessage(aMessage);
  },

  /**
   * Check if the given message category is allowed to be tracked or not.
   * We ignore chrome-originating errors as we only care about content.
   *
   * @param string aCategory
   *        The message category you want to check.
   * @return boolean
   *         True if the category is allowed to be logged, false otherwise.
   */
  isCategoryAllowed: function CSL_isCategoryAllowed(aCategory)
  {
    if (!aCategory) {
      return false;
    }

    switch (aCategory) {
      case "XPConnect JavaScript":
      case "component javascript":
      case "chrome javascript":
      case "chrome registration":
      case "XBL":
      case "XBL Prototype Handler":
      case "XBL Content Sink":
      case "xbl javascript":
        return false;
    }

    return true;
  },

  /**
   * Get the cached page errors for the current inner window and its (i)frames.
   *
   * @param boolean [aIncludePrivate=false]
   *        Tells if you want to also retrieve messages coming from private
   *        windows. Defaults to false.
   * @return array
   *         The array of cached messages. Each element is an nsIScriptError or
   *         an nsIConsoleMessage
   */
  getCachedMessages: function CSL_getCachedMessages(aIncludePrivate = false)
  {
    let errors = Services.console.getMessageArray() || [];

    // if !this.window, we're in a browser console. Still need to filter
    // private messages.
    if (!this.window) {
      return errors.filter((aError) => {
        if (aError instanceof Ci.nsIScriptError) {
          if (!aIncludePrivate && aError.isFromPrivateWindow) {
            return false;
          }
        }

        return true;
      });
    }

    let ids = WebConsoleUtils.getInnerWindowIDsForFrames(this.window);

    return errors.filter((aError) => {
      if (aError instanceof Ci.nsIScriptError) {
        if (!aIncludePrivate && aError.isFromPrivateWindow) {
          return false;
        }
        if (ids &&
            (ids.indexOf(aError.innerWindowID) == -1 ||
             !this.isCategoryAllowed(aError.category))) {
          return false;
        }
      }
      else if (ids && ids[0]) {
        // If this is not an nsIScriptError and we need to do window-based
        // filtering we skip this message.
        return false;
      }

      return true;
    });
  },

  /**
   * Remove the nsIConsoleService listener.
   */
  destroy: function CSL_destroy()
  {
    Services.console.unregisterListener(this);
    this.listener = this.window = null;
  },
};


///////////////////////////////////////////////////////////////////////////////
// The window.console API observer
///////////////////////////////////////////////////////////////////////////////

/**
 * The window.console API observer. This allows the window.console API messages
 * to be sent to the remote Web Console instance.
 *
 * @constructor
 * @param nsIDOMWindow aWindow
 *        Optional - the window object for which we are created. This is used
 *        for filtering out messages that belong to other windows.
 * @param object aOwner
 *        The owner object must have the following methods:
 *        - onConsoleAPICall(). This method is invoked with one argument, the
 *        Console API message that comes from the observer service, whenever
 *        a relevant console API call is received.
 * @param string aConsoleID
 *        Options - The consoleID that this listener should listen to
 */
function ConsoleAPIListener(aWindow, aOwner, aConsoleID)
{
  this.window = aWindow;
  this.owner = aOwner;
  this.consoleID = aConsoleID;
}
exports.ConsoleAPIListener = ConsoleAPIListener;

ConsoleAPIListener.prototype =
{
  // QueryInterface: XPCOMUtils.generateQI([Ci.nsIObserver]),

  /**
   * The content window for which we listen to window.console API calls.
   * @type nsIDOMWindow
   */
  window: null,

  /**
   * The owner object which is notified of window.console API calls. It must
   * have a onConsoleAPICall method which is invoked with one argument: the
   * console API call object that comes from the observer service.
   *
   * @type object
   * @see WebConsoleActor
   */
  owner: null,

  /**
   * The consoleID that we listen for. If not null then only messages from this
   * console will be returned.
   */
  consoleID: null,

  /**
   * Initialize the window.console API observer.
   */
  init: function CAL_init()
  {
    // Note that the observer is process-wide. We will filter the messages as
    // needed, see CAL_observe().
    // Services.obs.addObserver(this, "console-api-log-event", false);
  },

  /**
   * The console API message observer. When messages are received from the
   * observer service we forward them to the remote Web Console instance.
   *
   * @param object aMessage
   *        The message object receives from the observer service.
   * @param string aTopic
   *        The message topic received from the observer service.
   */
  observe: function CAL_observe(aMessage, aTopic)
  {
    if (!this.owner) {
      return;
    }

    // Here, wrappedJSObject is not a security wrapper but a property defined
    // by the XPCOM component which allows us to unwrap the XPCOM interface and
    // access the underlying JSObject.
    let apiMessage = aMessage.wrappedJSObject;
    if (this.window && CONSOLE_WORKER_IDS.indexOf(apiMessage.innerID) == -1) {
      let msgWindow = Services.wm.getCurrentInnerWindowWithId(apiMessage.innerID);
      if (!msgWindow || !isWindowIncluded(this.window, msgWindow)) {
        // Not the same window!
        return;
      }
    }
    if (this.consoleID && apiMessage.consoleID != this.consoleID) {
      return;
    }

    this.owner.onConsoleAPICall(apiMessage);
  },

  /**
   * Get the cached messages for the current inner window and its (i)frames.
   *
   * @param boolean [aIncludePrivate=false]
   *        Tells if you want to also retrieve messages coming from private
   *        windows. Defaults to false.
   * @return array
   *         The array of cached messages.
   */
  getCachedMessages: function CAL_getCachedMessages(aIncludePrivate = false)
  {
    let messages = [];
    // let ConsoleAPIStorage = Cc["@mozilla.org/consoleAPI-storage;1"]
    //                           .getService(Ci.nsIConsoleAPIStorage);

    // // if !this.window, we're in a browser console. Retrieve all events
    // // for filtering based on privacy.
    // if (!this.window) {
    //   messages = ConsoleAPIStorage.getEvents();
    // } else {
    //   let ids = WebConsoleUtils.getInnerWindowIDsForFrames(this.window);
    //   ids.forEach((id) => {
    //     messages = messages.concat(ConsoleAPIStorage.getEvents(id));
    //   });
    // }

    // CONSOLE_WORKER_IDS.forEach((id) => {
    //   messages = messages.concat(ConsoleAPIStorage.getEvents(id));
    // });

    if (this.consoleID) {
      messages = messages.filter((m) => m.consoleID == this.consoleID);
    }

    if (aIncludePrivate) {
      return messages;
    }

    return messages.filter((m) => !m.private);
  },

  /**
   * Destroy the console API listener.
   */
  destroy: function CAL_destroy()
  {
    Services.obs.removeObserver(this, "console-api-log-event");
    this.window = this.owner = null;
  },
};

/**
 * WebConsole commands manager.
 *
 * Defines a set of functions /variables ("commands") that are available from
 * the Web Console but not from the web page.
 *
 */
var WebConsoleCommands = {
  _registeredCommands: new Map(),
  _originalCommands: new Map(),

  /**
   * @private
   * Reserved for built-in commands. To register a command from the code of an
   * add-on, see WebConsoleCommands.register instead.
   *
   * @see WebConsoleCommands.register
   */
  _registerOriginal: function (name, command) {
    this.register(name, command);
    this._originalCommands.set(name, this.getCommand(name));
  },

  /**
   * Register a new command.
   * @param {string} name The command name (example: "$")
   * @param {(function|object)} command The command to register.
   *  It can be a function so the command is a function (like "$()"),
   *  or it can also be a property descriptor to describe a getter / value (like
   *  "$0").
   *
   *  The command function or the command getter are passed a owner object as
   *  their first parameter (see the example below).
   *
   *  Note that setters don't work currently and "enumerable" and "configurable"
   *  are forced to true.
   *
   * @example
   *
   *   WebConsoleCommands.register("$", function JSTH_$(aOwner, aSelector)
   *   {
   *     return aOwner.window.document.querySelector(aSelector);
   *   });
   *
   *   WebConsoleCommands.register("$0", {
   *     get: function(aOwner) {
   *       return aOwner.makeDebuggeeValue(aOwner.selectedNode);
   *     }
   *   });
   */
  register: function(name, command) {
    this._registeredCommands.set(name, command);
  },

  /**
   * Unregister a command.
   *
   * If the command being unregister overrode a built-in command,
   * the latter is restored.
   *
   * @param {string} name The name of the command
   */
  unregister: function(name) {
    this._registeredCommands.delete(name);
    if (this._originalCommands.has(name)) {
      this.register(name, this._originalCommands.get(name));
    }
  },

  /**
   * Returns a command by its name.
   *
   * @param {string} name The name of the command.
   *
   * @return {(function|object)} The command.
   */
  getCommand: function(name) {
    return this._registeredCommands.get(name);
  },

  /**
   * Returns true if a command is registered with the given name.
   *
   * @param {string} name The name of the command.
   *
   * @return {boolean} True if the command is registered.
   */
  hasCommand: function(name) {
    return this._registeredCommands.has(name);
  },
};

exports.WebConsoleCommands = WebConsoleCommands;


/*
 * Built-in commands.
  *
  * A list of helper functions used by Firebug can be found here:
  *   http://getfirebug.com/wiki/index.php/Command_Line_API
 */

/**
 * Find a node by ID.
 *
 * @param string aId
 *        The ID of the element you want.
 * @return nsIDOMNode or null
 *         The result of calling document.querySelector(aSelector).
 */
WebConsoleCommands._registerOriginal("$", function JSTH_$(aOwner, aSelector)
{
  return aOwner.window.document.querySelector(aSelector);
});

/**
 * Find the nodes matching a CSS selector.
 *
 * @param string aSelector
 *        A string that is passed to window.document.querySelectorAll.
 * @return nsIDOMNodeList
 *         Returns the result of document.querySelectorAll(aSelector).
 */
WebConsoleCommands._registerOriginal("$$", function JSTH_$$(aOwner, aSelector)
{
  let nodes = aOwner.window.document.querySelectorAll(aSelector);

  // Calling aOwner.window.Array.from() doesn't work without accessing the
  // wrappedJSObject, so just loop through the results instead.
  let result = new aOwner.window.Array();
  for (let i = 0; i < nodes.length; i++) {
    result.push(nodes[i]);
  }
  return result;
});

/**
 * Returns the result of the last console input evaluation
 *
 * @return object|undefined
 * Returns last console evaluation or undefined
 */
WebConsoleCommands._registerOriginal("$_", {
  get: function(aOwner) {
    return aOwner.consoleActor.getLastConsoleInputEvaluation();
  }
});


/**
 * Runs an xPath query and returns all matched nodes.
 *
 * @param string aXPath
 *        xPath search query to execute.
 * @param [optional] nsIDOMNode aContext
 *        Context to run the xPath query on. Uses window.document if not set.
 * @return array of nsIDOMNode
 */
WebConsoleCommands._registerOriginal("$x", function JSTH_$x(aOwner, aXPath, aContext)
{
  let nodes = new aOwner.window.Array();

  // Not waiving Xrays, since we want the original Document.evaluate function,
  // instead of anything that's been redefined.
  let doc =  aOwner.window.document;
  aContext = aContext || doc;

  let results = doc.evaluate(aXPath, aContext, null,
                             Ci.nsIDOMXPathResult.ANY_TYPE, null);
  let node;
  while ((node = results.iterateNext())) {
    nodes.push(node);
  }

  return nodes;
});

/**
 * Returns the currently selected object in the highlighter.
 *
 * @return Object representing the current selection in the
 *         Inspector, or null if no selection exists.
 */
WebConsoleCommands._registerOriginal("$0", {
  get: function(aOwner) {
    return aOwner.makeDebuggeeValue(aOwner.selectedNode);
  }
});

/**
 * Clears the output of the WebConsole.
 */
WebConsoleCommands._registerOriginal("clear", function JSTH_clear(aOwner)
{
  aOwner.helperResult = {
    type: "clearOutput",
  };
});

/**
 * Clears the input history of the WebConsole.
 */
WebConsoleCommands._registerOriginal("clearHistory", function JSTH_clearHistory(aOwner)
{
  aOwner.helperResult = {
    type: "clearHistory",
  };
});

/**
 * Returns the result of Object.keys(aObject).
 *
 * @param object aObject
 *        Object to return the property names from.
 * @return array of strings
 */
WebConsoleCommands._registerOriginal("keys", function JSTH_keys(aOwner, aObject)
{
  // Need to waive Xrays so we can iterate functions and accessor properties
  return Cu.cloneInto(Object.keys(Cu.waiveXrays(aObject)), aOwner.window);
});

/**
 * Returns the values of all properties on aObject.
 *
 * @param object aObject
 *        Object to display the values from.
 * @return array of string
 */
WebConsoleCommands._registerOriginal("values", function JSTH_values(aOwner, aObject)
{
  let values = [];
  // Need to waive Xrays so we can iterate functions and accessor properties
  let waived = Cu.waiveXrays(aObject);
  let names = Object.getOwnPropertyNames(waived);

  for (let name of names) {
    values.push(waived[name]);
  }

  return Cu.cloneInto(values, aOwner.window);
});

/**
 * Opens a help window in MDN.
 */
WebConsoleCommands._registerOriginal("help", function JSTH_help(aOwner)
{
  aOwner.helperResult = { type: "help" };
});

/**
 * Change the JS evaluation scope.
 *
 * @param DOMElement|string|window aWindow
 *        The window object to use for eval scope. This can be a string that
 *        is used to perform document.querySelector(), to find the iframe that
 *        you want to cd() to. A DOMElement can be given as well, the
 *        .contentWindow property is used. Lastly, you can directly pass
 *        a window object. If you call cd() with no arguments, the current
 *        eval scope is cleared back to its default (the top window).
 */
WebConsoleCommands._registerOriginal("cd", function JSTH_cd(aOwner, aWindow)
{
  if (!aWindow) {
    aOwner.consoleActor.evalWindow = null;
    aOwner.helperResult = { type: "cd" };
    return;
  }

  if (typeof aWindow == "string") {
    aWindow = aOwner.window.document.querySelector(aWindow);
  }
  if (aWindow instanceof Ci.nsIDOMElement && aWindow.contentWindow) {
    aWindow = aWindow.contentWindow;
  }
  if (!(aWindow instanceof Ci.nsIDOMWindow)) {
    aOwner.helperResult = { type: "error", message: "cdFunctionInvalidArgument" };
    return;
  }

  aOwner.consoleActor.evalWindow = aWindow;
  aOwner.helperResult = { type: "cd" };
});

/**
 * Inspects the passed aObject. This is done by opening the PropertyPanel.
 *
 * @param object aObject
 *        Object to inspect.
 */
WebConsoleCommands._registerOriginal("inspect", function JSTH_inspect(aOwner, aObject)
{
  let dbgObj = aOwner.makeDebuggeeValue(aObject);
  let grip = aOwner.createValueGrip(dbgObj);
  aOwner.helperResult = {
    type: "inspectObject",
    input: aOwner.evalInput,
    object: grip,
  };
});

/**
 * Prints aObject to the output.
 *
 * @param object aObject
 *        Object to print to the output.
 * @return string
 */
WebConsoleCommands._registerOriginal("pprint", function JSTH_pprint(aOwner, aObject)
{
  if (aObject === null || aObject === undefined || aObject === true ||
      aObject === false) {
    aOwner.helperResult = {
      type: "error",
      message: "helperFuncUnsupportedTypeError",
    };
    return null;
  }

  aOwner.helperResult = { rawOutput: true };

  if (typeof aObject == "function") {
    return aObject + "\n";
  }

  let output = [];

  let obj = aObject;
  for (let name in obj) {
    let desc = WebConsoleUtils.getPropertyDescriptor(obj, name) || {};
    if (desc.get || desc.set) {
      // TODO: Bug 842672 - toolkit/ imports modules from browser/.
      let getGrip = VariablesView.getGrip(desc.get);
      let setGrip = VariablesView.getGrip(desc.set);
      let getString = VariablesView.getString(getGrip);
      let setString = VariablesView.getString(setGrip);
      output.push(name + ":", "  get: " + getString, "  set: " + setString);
    }
    else {
      let valueGrip = VariablesView.getGrip(obj[name]);
      let valueString = VariablesView.getString(valueGrip);
      output.push(name + ": " + valueString);
    }
  }

  return "  " + output.join("\n  ");
});

/**
 * Print the String representation of a value to the output, as-is.
 *
 * @param any aValue
 *        A value you want to output as a string.
 * @return void
 */
WebConsoleCommands._registerOriginal("print", function JSTH_print(aOwner, aValue)
{
  aOwner.helperResult = { rawOutput: true };
  if (typeof aValue === "symbol") {
    return Symbol.prototype.toString.call(aValue);
  }
  // Waiving Xrays here allows us to see a closer representation of the
  // underlying object. This may execute arbitrary content code, but that
  // code will run with content privileges, and the result will be rendered
  // inert by coercing it to a String.
  return String(Cu.waiveXrays(aValue));
});

/**
 * Copy the String representation of a value to the clipboard.
 *
 * @param any aValue
 *        A value you want to copy as a string.
 * @return void
 */
WebConsoleCommands._registerOriginal("copy", function JSTH_copy(aOwner, aValue)
{
  let payload;
  try {
    if (aValue instanceof Ci.nsIDOMElement) {
      payload = aValue.outerHTML;
    } else if (typeof aValue == "string") {
      payload = aValue;
    } else {
      payload = JSON.stringify(aValue, null, "  ");
    }
  } catch (ex) {
    payload = "/* " + ex  + " */";
  }
  aOwner.helperResult = {
    type: "copyValueToClipboard",
    value: payload,
  };
});


/**
 * (Internal only) Add the bindings to |owner.sandbox|.
 * This is intended to be used by the WebConsole actor only.
  *
  * @param object aOwner
  *        The owning object.
  */
function addWebConsoleCommands(owner) {
  if (!owner) {
    throw new Error("The owner is required");
  }
  for (let [name, command] of WebConsoleCommands._registeredCommands) {
    if (typeof command === "function") {
      owner.sandbox[name] = command.bind(undefined, owner);
    }
    else if (typeof command === "object") {
      // let clone = Object.assign({}, command, {
      //   // We force the enumerability and the configurability (so the
      //   // WebConsoleActor can reconfigure the property).
      //   enumerable: true,
      //   configurable: true
      // });
      let clone = {};
      for (let attr in command) {
        if (command.hasOwnProperty(attr))
          clone[attr] = command[attr];
      }
      clone.enumerable = true;
      clone.configurable = true;

      if (typeof command.get === "function") {
        clone.get = command.get.bind(undefined, owner);
      }
      if (typeof command.set === "function") {
        clone.set = command.set.bind(undefined, owner);
      }

      Object.defineProperty(owner.sandbox, name, clone);
    }
  }
}

exports.addWebConsoleCommands = addWebConsoleCommands;

/**
 * A ReflowObserver that listens for reflow events from the page.
 * Implements nsIReflowObserver.
 *
 * @constructor
 * @param object aWindow
 *        The window for which we need to track reflow.
 * @param object aOwner
 *        The listener owner which needs to implement:
 *        - onReflowActivity(aReflowInfo)
 */

function ConsoleReflowListener(aWindow, aListener)
{
  this.docshell = aWindow.QueryInterface(Ci.nsIInterfaceRequestor)
                         .getInterface(Ci.nsIWebNavigation)
                         .QueryInterface(Ci.nsIDocShell);
  this.listener = aListener;
  this.docshell.addWeakReflowObserver(this);
}

exports.ConsoleReflowListener = ConsoleReflowListener;

ConsoleReflowListener.prototype =
{
  // QueryInterface: XPCOMUtils.generateQI([Ci.nsIReflowObserver,
  //                                        Ci.nsISupportsWeakReference]),
  docshell: null,
  listener: null,

  /**
   * Forward reflow event to listener.
   *
   * @param DOMHighResTimeStamp aStart
   * @param DOMHighResTimeStamp aEnd
   * @param boolean aInterruptible
   */
  sendReflow: function CRL_sendReflow(aStart, aEnd, aInterruptible)
  {
    let frame = components.stack.caller.caller;

    let filename = frame.filename;

    if (filename) {
      // Because filename could be of the form "xxx.js -> xxx.js -> xxx.js",
      // we only take the last part.
      filename = filename.split(" ").pop();
    }

    this.listener.onReflowActivity({
      interruptible: aInterruptible,
      start: aStart,
      end: aEnd,
      sourceURL: filename,
      sourceLine: frame.lineNumber,
      functionName: frame.name
    });
  },

  /**
   * On uninterruptible reflow
   *
   * @param DOMHighResTimeStamp aStart
   * @param DOMHighResTimeStamp aEnd
   */
  reflow: function CRL_reflow(aStart, aEnd)
  {
    this.sendReflow(aStart, aEnd, false);
  },

  /**
   * On interruptible reflow
   *
   * @param DOMHighResTimeStamp aStart
   * @param DOMHighResTimeStamp aEnd
   */
  reflowInterruptible: function CRL_reflowInterruptible(aStart, aEnd)
  {
    this.sendReflow(aStart, aEnd, true);
  },

  /**
   * Unregister listener.
   */
  destroy: function CRL_destroy()
  {
    this.docshell.removeWeakReflowObserver(this);
    this.listener = this.docshell = null;
  },
};

function gSequenceId()
{
  return gSequenceId.n++;
}
gSequenceId.n = 0;

exports;

