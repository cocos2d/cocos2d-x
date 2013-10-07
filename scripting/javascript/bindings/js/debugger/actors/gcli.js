/* -*- Mode: js2; js2-basic-offset: 2; indent-tabs-mode: nil; -*- */
/* vim: set ts=2 et sw=2 tw=80: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

"use strict";

let { classes: Cc, interfaces: Ci, utils: Cu } = Components;

let { XPCOMUtils } = Cu.import("resource://gre/modules/XPCOMUtils.jsm", {});

XPCOMUtils.defineLazyModuleGetter(this, "console",
                                  "resource://gre/modules/devtools/Console.jsm");
XPCOMUtils.defineLazyModuleGetter(this, "CommandUtils",
                                  "resource:///modules/devtools/DeveloperToolbar.jsm");

XPCOMUtils.defineLazyGetter(this, "require", function() {
  let { require } = Cu.import("resource://gre/modules/devtools/Require.jsm", {});
  Cu.import("resource://gre/modules/devtools/gcli.jsm", {});
  return require;
});

XPCOMUtils.defineLazyGetter(this, "canon", () => require("gcli/canon"));
XPCOMUtils.defineLazyGetter(this, "Requisition", () => require("gcli/cli").Requisition);
XPCOMUtils.defineLazyGetter(this, "util", () => require("util/util"));


/**
 * Manage remote connections that want to talk to GCLI
 * @constructor
 * @param connection The connection to the client, DebuggerServerConnection
 * @param parentActor Optional, the parent actor
 */
function GcliActor(connection, parentActor) {
  this.connection = connection;
}

GcliActor.prototype.actorPrefix = "gcli";

GcliActor.prototype.disconnect = function() {
};

GcliActor.prototype.getCommandSpecs = function(request) {
  return { commandSpecs: canon.getCommandSpecs() };
};

GcliActor.prototype.execute = function(request) {
  let windowMediator = Cc["@mozilla.org/appshell/window-mediator;1"]
                        .getService(Ci.nsIWindowMediator);
  let chromeWindow = windowMediator.getMostRecentWindow("navigator:browser");
  let contentWindow = chromeWindow.gBrowser.selectedTab.linkedBrowser.contentWindow;

  let environment = CommandUtils.createEnvironment(chromeWindow.document,
                                                   contentWindow.document);

  let requisition = new Requisition(environment);
  requisition.updateExec(request.typed).then(output => {
    return output.promise.then(() => {
      this.connection.send({
        from: this.actorID,
        requestId: request.requestId,
        data: output.data,
        type: output.type,
        error: output.error
      });
    });
  }).then(null, console.error);
};

GcliActor.prototype.requestTypes = {
  getCommandSpecs: GcliActor.prototype.getCommandSpecs,
  execute: GcliActor.prototype.execute,
};

addTabActor(GcliActor, "gcliActor");
addGlobalActor(GcliActor, "gcliActor");
