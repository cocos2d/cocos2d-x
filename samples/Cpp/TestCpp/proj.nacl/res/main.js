chrome.app.runtime.onLaunched.addListener(function() {
  var screenWidth = screen.availWidth;
  var screenHeight = screen.availHeight;
  var width = 800;
  var height = 640;

  chrome.app.window.create('index.html', {
     width: width,
     height: height,
     minWidth: width,
     minHeight: height,
     type: 'panel',
     left: (screenWidth-width)/2,
     top: (screenHeight-height)/2
  });
});
