/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

"use strict";

let Cc = Components.classes;
let Ci = Components.interfaces;
let Cu = Components.utils;

Cu.import("resource://gre/modules/XPCOMUtils.jsm");
Cu.import("resource://gre/modules/Services.jsm");
Cu.import("resource://gre/modules/NetUtil.jsm");
Cu.import("resource://gre/modules/FileUtils.jsm");

let TRANSITION_CLASS = "moz-styleeditor-transitioning";
let TRANSITION_DURATION_MS = 500;
let TRANSITION_RULE = "\
:root.moz-styleeditor-transitioning, :root.moz-styleeditor-transitioning * {\
transition-duration: " + TRANSITION_DURATION_MS + "ms !important; \
transition-delay: 0ms !important;\
transition-timing-function: ease-out !important;\
transition-property: all !important;\
}";

let LOAD_ERROR = "error-load";

/**
 * Creates a StyleEditorActor. StyleEditorActor provides remote access to the
 * built-in style editor module.
 */
function StyleEditorActor(aConnection, aParentActor)
{
  this.conn = aConnection;
  this._onDocumentLoaded = this._onDocumentLoaded.bind(this);
  this._onSheetLoaded = this._onSheetLoaded.bind(this);

  if (aParentActor instanceof BrowserTabActor &&
      aParentActor.browser instanceof Ci.nsIDOMWindow) {
    this._window = aParentActor.browser;
  }
  else if (aParentActor instanceof BrowserTabActor &&
           aParentActor.browser instanceof Ci.nsIDOMElement) {
    this._window = aParentActor.browser.contentWindow;
  }
  else {
    this._window = Services.wm.getMostRecentWindow("navigator:browser");
  }

  // keep a map of sheets-to-actors so we don't create two actors for one sheet
  this._sheets = new Map();

  this._actorPool = new ActorPool(this.conn);
  this.conn.addActorPool(this._actorPool);
}

StyleEditorActor.prototype = {
  /**
   * Actor pool for all of the actors we send to the client.
   */
  _actorPool: null,

  /**
   * The debugger server connection instance.
   */
  conn: null,

  /**
   * The content window we work with.
   */
  get win() this._window,

  /**
   * The current content document of the window we work with.
   */
  get doc() this._window.document,

  /**
   * A window object, usually the browser window
   */
  _window: null,

  actorPrefix: "styleEditor",

  form: function()
  {
    return { actor: this.actorID };
  },

  /**
   * Destroy the current StyleEditorActor instance.
   */
  disconnect: function()
  {
    if (this._observer) {
      this._observer.disconnect();
      delete this._observer;
    }

    this._sheets.clear();

    this.conn.removeActorPool(this._actorPool);
    this._actorPool = null;
    this.conn = this._window = null;
  },

  /**
   * Release an actor from our actor pool.
   */
  releaseActor: function(actor)
  {
    if (this._actorPool) {
      this._actorPool.removeActor(actor.actorID);
    }
  },

  /**
   * Get the BaseURI for the document.
   *
   * @return {object} JSON message to with BaseURI
   */
  onGetBaseURI: function() {
    return { baseURI: this.doc.baseURIObject };
  },

  /**
   * Called when target navigates to a new document.
   * Adds load listeners to document.
   */
  onNewDocument: function() {
    // delete previous document's actors
    this._clearStyleSheetActors();

    // Note: listening for load won't be necessary once
    // https://bugzilla.mozilla.org/show_bug.cgi?id=839103 is fixed
    if (this.doc.readyState == "complete") {
      this._onDocumentLoaded();
    }
    else {
      this.win.addEventListener("load", this._onDocumentLoaded, false);
    }
    return {};
  },

  /**
   * Event handler for document loaded event. Add actor for each stylesheet
   * and send an event notifying of the load
   */
  _onDocumentLoaded: function(event) {
    if (event) {
      this.win.removeEventListener("load", this._onDocumentLoaded, false);
    }

    let documents = [this.doc];
    var forms = [];
    for (let doc of documents) {
      let sheetForms = this._addStyleSheets(doc.styleSheets);
      forms = forms.concat(sheetForms);
      // Recursively handle style sheets of the documents in iframes.
      for (let iframe of doc.getElementsByTagName("iframe")) {
        documents.push(iframe.contentDocument);
      }
    }

    this.conn.send({
      from: this.actorID,
      type: "documentLoad",
      styleSheets: forms
    });
  },

  /**
   * Add all the stylesheets to the map and create an actor
   * for each one if not already created. Send event that there
   * are new stylesheets.
   *
   * @param {[DOMStyleSheet]} styleSheets
   *        Stylesheets to add
   * @return {[object]}
   *         Array of forms for each StyleSheetActor created
   */
  _addStyleSheets: function(styleSheets)
  {
    let sheets = [];
    for (let i = 0; i < styleSheets.length; i++) {
      let styleSheet = styleSheets[i];
      sheets.push(styleSheet);

      // Get all sheets, including imported ones
      let imports = this._getImported(styleSheet);
      sheets = sheets.concat(imports);
    }

    let forms = sheets.map((sheet) => {
      let actor = this._createStyleSheetActor(sheet);
      return actor.form();
    });

    return forms;
  },

  /**
   * Get all the stylesheets @imported from a stylesheet.
   *
   * @param  {DOMStyleSheet} styleSheet
   *         Style sheet to search
   * @return {array}
   *         All the imported stylesheets
   */
  _getImported: function(styleSheet) {
   let imported = [];

   for (let i = 0; i < styleSheet.cssRules.length; i++) {
      let rule = styleSheet.cssRules[i];
      if (rule.type == Ci.nsIDOMCSSRule.IMPORT_RULE) {
        // Associated styleSheet may be null if it has already been seen due to
        // duplicate @imports for the same URL.
        if (!rule.styleSheet) {
          continue;
        }
        imported.push(rule.styleSheet);

        // recurse imports in this stylesheet as well
        imported = imported.concat(this._getImported(rule.styleSheet));
      }
      else if (rule.type != Ci.nsIDOMCSSRule.CHARSET_RULE) {
        // @import rules must precede all others except @charset
        break;
      }
    }
    return imported;
  },

  /**
   * Create a new actor for a style sheet, if it hasn't
   * already been created, and return it.
   *
   * @param  {DOMStyleSheet} aStyleSheet
   *         The style sheet to create an actor for.
   * @return {StyleSheetActor}
   *         The actor for this style sheet
   */
  _createStyleSheetActor: function(aStyleSheet)
  {
    if (this._sheets.has(aStyleSheet)) {
      return this._sheets.get(aStyleSheet);
    }
    let actor = new StyleSheetActor(aStyleSheet, this);
    this._actorPool.addActor(actor);
    this._sheets.set(aStyleSheet, actor);
    return actor;
  },

  /**
   * Clear all the current stylesheet actors in map.
   */
  _clearStyleSheetActors: function() {
    for (let actor in this._sheets) {
      this.releaseActor(this._sheets[actor]);
    }
    this._sheets.clear();
  },

  /**
   * Get the actors of all the stylesheets in the current document.
   *
   * @return {object} JSON message with the stylesheet actors' forms
   */
  onGetStyleSheets: function() {
    let forms = this._addStyleSheets(this.doc.styleSheets);
    return { "styleSheets": forms };
  },

  /**
   * Handler for style sheet loading event. Add
   * a new actor for the sheet and notify.
   *
   * @param  {Event} event
   */
  _onSheetLoaded: function(event) {
    let style = event.target;
    style.removeEventListener("load", this._onSheetLoaded, false);

    let actor = this._createStyleSheetActor(style.sheet);
    this._notifyStyleSheetsAdded([actor.form()]);
  },

  /**
   * Create a new style sheet in the document with the given text.
   * Return an actor for it.
   *
   * @param  {object} request
   *         Debugging protocol request object, with 'text property'
   * @return {object}
   *         Object with 'styelSheet' property for form on new actor.
   */
  onNewStyleSheet: function(request) {
    let parent = this.doc.documentElement;
    let style = this.doc.createElementNS("http://www.w3.org/1999/xhtml", "style");
    style.setAttribute("type", "text/css");

    if (request.text) {
      style.appendChild(this.doc.createTextNode(request.text));
    }
    parent.appendChild(style);

    let actor = this._createStyleSheetActor(style.sheet);
    return { styleSheet: actor.form() };
  }
};

/**
 * The request types this actor can handle.
 */
StyleEditorActor.prototype.requestTypes = {
  "getStyleSheets": StyleEditorActor.prototype.onGetStyleSheets,
  "newStyleSheet": StyleEditorActor.prototype.onNewStyleSheet,
  "getBaseURI": StyleEditorActor.prototype.onGetBaseURI,
  "newDocument": StyleEditorActor.prototype.onNewDocument
};


function StyleSheetActor(aStyleSheet, aParentActor) {
  this.styleSheet = aStyleSheet;
  this.parentActor = aParentActor;

  // text and index are unknown until source load
  this.text = null;
  this._styleSheetIndex = -1;

  this._transitionRefCount = 0;

  this._onSourceLoad = this._onSourceLoad.bind(this);
  this._notifyError = this._notifyError.bind(this);

  // if this sheet has an @import, then it's rules are loaded async
  let ownerNode = this.styleSheet.ownerNode;
  if (ownerNode) {
    let onSheetLoaded = function(event) {
      ownerNode.removeEventListener("load", onSheetLoaded, false);
      this._notifyPropertyChanged("ruleCount");
    }.bind(this);

    ownerNode.addEventListener("load", onSheetLoaded, false);
  }
}

StyleSheetActor.prototype = {
  actorPrefix: "stylesheet",

  toString: function() {
    return "[StyleSheetActor " + this.actorID + "]";
  },

  disconnect: function() {
    this.parentActor.releaseActor(this);
  },

  /**
   * Window of target
   */
  get win() {
    return this.parentActor._window;
  },

  /**
   * Document of target.
   */
  get doc() {
    return this.win.document;
  },

  /**
   * Retrieve the index (order) of stylesheet in the document.
   *
   * @return number
   */
  get styleSheetIndex()
  {
    if (this._styleSheetIndex == -1) {
      for (let i = 0; i < this.doc.styleSheets.length; i++) {
        if (this.doc.styleSheets[i] == this.styleSheet) {
          this._styleSheetIndex = i;
          break;
        }
      }
    }
    return this._styleSheetIndex;
  },

  /**
   * Get the current state of the actor
   *
   * @return {object}
   *         With properties of the underlying stylesheet, plus 'text',
   *        'styleSheetIndex' and 'parentActor' if it's @imported
   */
  form: function() {
    let form = {
      actor: this.actorID,  // actorID is set when this actor is added to a pool
      href: this.styleSheet.href,
      disabled: this.styleSheet.disabled,
      title: this.styleSheet.title,
      styleSheetIndex: this.styleSheetIndex,
      text: this.text
    }

    // get parent actor if this sheet was @imported
    let parent = this.styleSheet.parentStyleSheet;
    if (parent) {
      form.parentActor = this.parentActor._sheets.get(parent);
    }

    try {
      form.ruleCount = this.styleSheet.cssRules.length;
    }
    catch(e) {
      // stylesheet had an @import rule that wasn't loaded yet
    }

    return form;
  },

  /**
   * Toggle the disabled property of the style sheet
   *
   * @return {object}
   *         'disabled' - the disabled state after toggling.
   */
  onToggleDisabled: function() {
    this.styleSheet.disabled = !this.styleSheet.disabled;
    this._notifyPropertyChanged("disabled");

    return { disabled: this.styleSheet.disabled };
  },

  /**
   * Send an event notifying that a property of the stylesheet
   * has changed.
   *
   * @param  {string} property
   *         Name of the changed property
   */
  _notifyPropertyChanged: function(property) {
    this.conn.send({
      from: this.actorID,
      type: "propertyChange-" + this.actorID,
      property: property,
      value: this.form()[property]
    })
  },

  /**
   * Send an event notifying that an error has occured
   *
   * @param  {string} message
   *         Error message
   */
  _notifyError: function(message) {
    this.conn.send({
      from: this.actorID,
      type: "error-" + this.actorID,
      errorMessage: message
    });
  },

  /**
   * Handler for event when the style sheet's full text has been
   * loaded from its source.
   *
   * @param  {string} source
   *         Text of the style sheet
   * @param  {[type]} charset
   *         Optional charset of the source
   */
  _onSourceLoad: function(source, charset) {
    this.text = this._decodeCSSCharset(source, charset || "");

    this.conn.send({
      from: this.actorID,
      type: "sourceLoad-" + this.actorID,
      source: this.text
    });
  },

  /**
   * Fetch the source of the style sheet from its URL
   */
  onFetchSource: function() {
    if (!this.styleSheet.href) {
      // this is an inline <style> sheet
      let source = this.styleSheet.ownerNode.textContent;
      this._onSourceLoad(source);
      return {};
    }

    let scheme = Services.io.extractScheme(this.styleSheet.href);
    switch (scheme) {
      case "file":
        this._styleSheetFilePath = this.styleSheet.href;
      case "chrome":
      case "resource":
        this._loadSourceFromFile(this.styleSheet.href);
        break;
      default:
        this._loadSourceFromCache(this.styleSheet.href);
        break;
    }
    return {};
  },

  /**
   * Decode a CSS source string to unicode according to the character set rules
   * defined in <http://www.w3.org/TR/CSS2/syndata.html#charset>.
   *
   * @param string string
   *        Source of a CSS stylesheet, loaded from file or cache.
   * @param string channelCharset
   *        Charset of the source string if set by the HTTP channel.
   * @return string
   *         The CSS string, in unicode.
   */
  _decodeCSSCharset: function(string, channelCharset)
  {
    // StyleSheet's charset can be specified from multiple sources

    if (channelCharset.length > 0) {
      // step 1 of syndata.html: charset given in HTTP header.
      return this._convertToUnicode(string, channelCharset);
    }

    let sheet = this.styleSheet;
    if (sheet) {
      // Do we have a @charset rule in the stylesheet?
      // step 2 of syndata.html (without the BOM check).
      if (sheet.cssRules) {
        let rules = sheet.cssRules;
        if (rules.length
            && rules.item(0).type == Ci.nsIDOMCSSRule.CHARSET_RULE) {
          return this._convertToUnicode(string, rules.item(0).encoding);
        }
      }

      // step 3: charset attribute of <link> or <style> element, if it exists
      if (sheet.ownerNode && sheet.ownerNode.getAttribute) {
        let linkCharset = sheet.ownerNode.getAttribute("charset");
        if (linkCharset != null) {
          return this._convertToUnicode(string, linkCharset);
        }
      }

      // step 4 (1 of 2): charset of referring stylesheet.
      let parentSheet = sheet.parentStyleSheet;
      if (parentSheet && parentSheet.cssRules &&
          parentSheet.cssRules[0].type == Ci.nsIDOMCSSRule.CHARSET_RULE) {
        return this._convertToUnicode(string,
            parentSheet.cssRules[0].encoding);
      }

      // step 4 (2 of 2): charset of referring document.
      if (sheet.ownerNode && sheet.ownerNode.ownerDocument.characterSet) {
        return this._convertToUnicode(string,
            sheet.ownerNode.ownerDocument.characterSet);
      }
    }

    // step 5: default to utf-8.
    return this._convertToUnicode(string, "UTF-8");
  },

  /**
   * Convert a given string, encoded in a given character set, to unicode.
   *
   * @param string string
   *        A string.
   * @param string charset
   *        A character set.
   * @return string
   *         A unicode string.
   */
  _convertToUnicode: function(string, charset) {
    // Decoding primitives.
    let converter = Cc["@mozilla.org/intl/scriptableunicodeconverter"]
        .createInstance(Ci.nsIScriptableUnicodeConverter);

    try {
      converter.charset = charset;
      return converter.ConvertToUnicode(string);
    } catch(e) {
      return string;
    }
  },

  /**
   * Load source from a file or file-like resource.
   *
   * @param string href
   *        URL for the stylesheet.
   */
  _loadSourceFromFile: function(href)
  {
    try {
      NetUtil.asyncFetch(href, (stream, status) => {
        if (!Components.isSuccessCode(status)) {
          this._notifyError(LOAD_ERROR);
          return;
        }
        let source = NetUtil.readInputStreamToString(stream, stream.available());
        stream.close();
        this._onSourceLoad(source);
      });
    } catch (ex) {
      this._notifyError(LOAD_ERROR);
    }
  },

  /**
   * Load source from the HTTP cache.
   *
   * @param string href
   *        URL for the stylesheet.
   */
  _loadSourceFromCache: function(href)
  {
    let channel = Services.io.newChannel(href, null, null);
    let chunks = [];
    let channelCharset = "";
    let streamListener = { // nsIStreamListener inherits nsIRequestObserver
      onStartRequest: (aRequest, aContext, aStatusCode) => {
        if (!Components.isSuccessCode(aStatusCode)) {
          this._notifyError(LOAD_ERROR);
        }
      },
      onDataAvailable: (aRequest, aContext, aStream, aOffset, aCount) => {
        let channel = aRequest.QueryInterface(Ci.nsIChannel);
        if (!channelCharset) {
          channelCharset = channel.contentCharset;
        }
        chunks.push(NetUtil.readInputStreamToString(aStream, aCount));
      },
      onStopRequest: (aRequest, aContext, aStatusCode) => {
        if (!Components.isSuccessCode(aStatusCode)) {
          this._notifyError(LOAD_ERROR);
          return;
        }
        let source = chunks.join("");
        this._onSourceLoad(source, channelCharset);
      }
    };

    if (channel instanceof Ci.nsIPrivateBrowsingChannel) {
      let loadContext = this.win.QueryInterface(Ci.nsIInterfaceRequestor)
                          .getInterface(Ci.nsIWebNavigation)
                          .QueryInterface(Ci.nsILoadContext);
      channel.setPrivate(loadContext.usePrivateBrowsing);
    }
    channel.loadFlags = channel.LOAD_FROM_CACHE;
    channel.asyncOpen(streamListener, null);
  },

  /**
   * Update the style sheet in place with new text
   *
   * @param  {object} request
   *         'text' - new text
   *         'transition' - whether to do CSS transition for change.
   */
  onUpdate: function(request) {
    DOMUtils.parseStyleSheet(this.styleSheet, request.text);

    this._notifyPropertyChanged("ruleCount");

    if (request.transition) {
      this._insertTransistionRule();
    }
    else {
      this._notifyStyleApplied();
    }

    return {};
  },

  /**
   * Insert a catch-all transition rule into the document. Set a timeout
   * to remove the rule after a certain time.
   */
  _insertTransistionRule: function() {
    // Insert the global transition rule
    // Use a ref count to make sure we do not add it multiple times.. and remove
    // it only when all pending StyleEditor-generated transitions ended.
    if (this._transitionRefCount == 0) {
      this.styleSheet.insertRule(TRANSITION_RULE, this.styleSheet.cssRules.length);
      this.doc.documentElement.classList.add(TRANSITION_CLASS);
    }

    this._transitionRefCount++;

    // Set up clean up and commit after transition duration (+10% buffer)
    // @see _onTransitionEnd
    this.win.setTimeout(this._onTransitionEnd.bind(this),
                           Math.floor(TRANSITION_DURATION_MS * 1.1));
  },

  /**
    * This cleans up class and rule added for transition effect and then
    * notifies that the style has been applied.
    */
  _onTransitionEnd: function()
  {
    if (--this._transitionRefCount == 0) {
      this.doc.documentElement.classList.remove(TRANSITION_CLASS);
      this.styleSheet.deleteRule(this.styleSheet.cssRules.length - 1);
    }

    this._notifyStyleApplied();
  },

  /**
   * Send and event notifying that the new style has been applied fully.
   */
  _notifyStyleApplied: function()
  {
    this.conn.send({
      from: this.actorID,
      type: "styleApplied-" + this.actorID
    })
  }
}

StyleSheetActor.prototype.requestTypes = {
  "toggleDisabled": StyleSheetActor.prototype.onToggleDisabled,
  "fetchSource": StyleSheetActor.prototype.onFetchSource,
  "update": StyleSheetActor.prototype.onUpdate
};

DebuggerServer.addTabActor(StyleEditorActor, "styleEditorActor");

XPCOMUtils.defineLazyGetter(this, "DOMUtils", function () {
  return Cc["@mozilla.org/inspector/dom-utils;1"].getService(Ci.inIDOMUtils);
});
