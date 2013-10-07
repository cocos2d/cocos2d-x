function run_test()
{
  Components.utils.import("resource://gre/modules/jsdebugger.jsm");
  addDebuggerToGlobal(this);
  var g = testGlobal("test1");

  var dbg = new Debugger();
  dbg.addDebuggee(g);
  dbg.onDebuggerStatement = function(aFrame) {
    let args = aFrame.arguments;
    try {
      args[0];
      do_check_true(true);
    } catch(ex) {
      do_check_true(false);
    }
  };

  g.eval("function stopMe(arg) {debugger;}");

  g2 = testGlobal("test2");
  g2.g = g;
  g2.eval("(" + function createBadEvent() {
    let parser = Components.classes["@mozilla.org/xmlextras/domparser;1"].createInstance(Components.interfaces.nsIDOMParser);
    let doc = parser.parseFromString("<foo></foo>", "text/xml");
    g.stopMe(doc.createEvent("MouseEvent"));
  } + ")()");

  dbg.enabled = false;
}
