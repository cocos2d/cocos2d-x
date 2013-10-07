function run_test()
{
  Components.utils.import("resource://gre/modules/jsdebugger.jsm");
  addDebuggerToGlobal(this);
  var xpcInspector = Cc["@mozilla.org/jsinspector;1"].getService(Ci.nsIJSInspector);
  var g = testGlobal("test1");

  var dbg = new Debugger();
  dbg.uncaughtExceptionHook = testExceptionHook;

  dbg.addDebuggee(g);
  dbg.onDebuggerStatement = function(aFrame) {
    do_check_true(aFrame === dbg.getNewestFrame());
    // Execute from the nested event loop, dbg.getNewestFrame() won't
    // be working anymore.

    do_execute_soon(function() {
      try {
        do_check_true(aFrame === dbg.getNewestFrame());
      } finally {
        xpcInspector.exitNestedEventLoop("test");
      }
    });
    xpcInspector.enterNestedEventLoop("test");
  };

  g.eval("function debuggerStatement() { debugger; }; debuggerStatement();");

  dbg.enabled = false;
}
