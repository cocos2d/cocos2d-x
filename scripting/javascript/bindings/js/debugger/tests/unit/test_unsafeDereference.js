// Any copyright is dedicated to the Public Domain.
// http://creativecommons.org/publicdomain/zero/1.0/

// Test Debugger.Object.prototype.unsafeDereference in the presence of
// interesting cross-compartment wrappers.
//
// This is not really a debugger server test; it's more of a Debugger test.
// But we need xpcshell and Components.utils.Sandbox to get
// cross-compartment wrappers with interesting properties, and this is the
// xpcshell test directory most closely related to the JS Debugger API.

Components.utils.import("resource://gre/modules/jsdebugger.jsm");
addDebuggerToGlobal(this);

// Add a method to Debugger.Object for fetching value properties
// conveniently.
Debugger.Object.prototype.getProperty = function (aName) {
  let desc = this.getOwnPropertyDescriptor(aName);
  if (!desc)
    return undefined;
  if (!desc.value) {
    throw Error("Debugger.Object.prototype.getProperty: " +
                "not a value property: " + aName);
  }
  return desc.value;
};

function run_test() {
  // Create a low-privilege sandbox, and a chrome-privilege sandbox.
  let contentBox = Components.utils.Sandbox('http://www.example.com');
  let chromeBox = Components.utils.Sandbox(this);

  // Create an objects in this compartment, and one in each sandbox. We'll
  // refer to the objects as "mainObj", "contentObj", and "chromeObj", in
  // variable and property names.
  var mainObj = { name: "mainObj" };
  Components.utils.evalInSandbox('var contentObj = { name: "contentObj" };',
                                 contentBox);
  Components.utils.evalInSandbox('var chromeObj = { name: "chromeObj" };',
                                 chromeBox);

  // Give each global a pointer to all the other globals' objects.
  contentBox.mainObj = chromeBox.mainObj = mainObj;
  var contentObj = chromeBox.contentObj = contentBox.contentObj;
  var chromeObj  = contentBox.chromeObj = chromeBox.chromeObj;

  // First, a whole bunch of basic sanity checks, to ensure that JavaScript
  // evaluated in various scopes really does see the world the way this
  // test expects it to.

  // The objects appear as global variables in the sandbox, and as
  // the sandbox object's properties in chrome.
  do_check_true(Components.utils.evalInSandbox('mainObj', contentBox)
                === contentBox.mainObj);
  do_check_true(Components.utils.evalInSandbox('contentObj', contentBox)
                === contentBox.contentObj);
  do_check_true(Components.utils.evalInSandbox('chromeObj', contentBox)
                === contentBox.chromeObj);
  do_check_true(Components.utils.evalInSandbox('mainObj', chromeBox)
                === chromeBox.mainObj);
  do_check_true(Components.utils.evalInSandbox('contentObj', chromeBox)
                === chromeBox.contentObj);
  do_check_true(Components.utils.evalInSandbox('chromeObj', chromeBox)
                === chromeBox.chromeObj);

  // We (the main global) can see properties of all objects in all globals.
  do_check_true(contentBox.mainObj.name === "mainObj");
  do_check_true(contentBox.contentObj.name === "contentObj");
  do_check_true(contentBox.chromeObj.name === "chromeObj");

  // chromeBox can see properties of all objects in all globals.
  do_check_eq(Components.utils.evalInSandbox('mainObj.name', chromeBox),
              'mainObj');
  do_check_eq(Components.utils.evalInSandbox('contentObj.name', chromeBox),
              'contentObj');
  do_check_eq(Components.utils.evalInSandbox('chromeObj.name', chromeBox),
              'chromeObj');

  // contentBox can see properties of the content object, but not of either
  // chrome object, because by default, content -> chrome wrappers hide all
  // object properties.
  do_check_eq(Components.utils.evalInSandbox('mainObj.name', contentBox),
              undefined);
  do_check_eq(Components.utils.evalInSandbox('contentObj.name', contentBox),
              'contentObj');
  do_check_eq(Components.utils.evalInSandbox('chromeObj.name', contentBox),
              undefined);

  // When viewing an object in compartment A from the vantage point of
  // compartment B, Debugger should give the same results as debuggee code
  // would.

  // Create a debugger, debugging our two sandboxes.
  let dbg = new Debugger;

  // Create Debugger.Object instances referring to the two sandboxes, as
  // seen from their own compartments.
  let contentBoxDO = dbg.addDebuggee(contentBox);
  let chromeBoxDO = dbg.addDebuggee(chromeBox);

  // Use Debugger to view the objects from contentBox. We should get the
  // same D.O instance from both getProperty and makeDebuggeeValue, and the
  // same property visibility we checked for above.
  let mainFromContentDO = contentBoxDO.getProperty('mainObj');
  do_check_eq(mainFromContentDO, contentBoxDO.makeDebuggeeValue(mainObj));
  do_check_eq(mainFromContentDO.getProperty('name'), undefined);
  do_check_eq(mainFromContentDO.unsafeDereference(), mainObj);

  let contentFromContentDO = contentBoxDO.getProperty('contentObj');
  do_check_eq(contentFromContentDO, contentBoxDO.makeDebuggeeValue(contentObj));
  do_check_eq(contentFromContentDO.getProperty('name'), 'contentObj');
  do_check_eq(contentFromContentDO.unsafeDereference(), contentObj);

  let chromeFromContentDO = contentBoxDO.getProperty('chromeObj');
  do_check_eq(chromeFromContentDO, contentBoxDO.makeDebuggeeValue(chromeObj));
  do_check_eq(chromeFromContentDO.getProperty('name'), undefined);
  do_check_eq(chromeFromContentDO.unsafeDereference(), chromeObj);

  // Similarly, viewing from chromeBox.
  let mainFromChromeDO = chromeBoxDO.getProperty('mainObj');
  do_check_eq(mainFromChromeDO, chromeBoxDO.makeDebuggeeValue(mainObj));
  do_check_eq(mainFromChromeDO.getProperty('name'), 'mainObj');
  do_check_eq(mainFromChromeDO.unsafeDereference(), mainObj);

  let contentFromChromeDO = chromeBoxDO.getProperty('contentObj');
  do_check_eq(contentFromChromeDO, chromeBoxDO.makeDebuggeeValue(contentObj));
  do_check_eq(contentFromChromeDO.getProperty('name'), 'contentObj');
  do_check_eq(contentFromChromeDO.unsafeDereference(), contentObj);

  let chromeFromChromeDO = chromeBoxDO.getProperty('chromeObj');
  do_check_eq(chromeFromChromeDO, chromeBoxDO.makeDebuggeeValue(chromeObj));
  do_check_eq(chromeFromChromeDO.getProperty('name'), 'chromeObj');
  do_check_eq(chromeFromChromeDO.unsafeDereference(), chromeObj);
}
