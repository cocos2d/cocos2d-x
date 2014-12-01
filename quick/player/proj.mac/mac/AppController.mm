
#import "AppController.h"

#include "AppDelegate.h"
#include "glfw3.h"
#include "glfw3native.h"

#include "cocos2d.h"
#include "CCLuaEngine.h"

#include "PlayerMac.h"

USING_NS_CC;

std::string getCurAppPath(void)
{
    return [[[NSBundle mainBundle] bundlePath] UTF8String];
}

std::string getCurAppName(void)
{
    string appName = [[[NSProcessInfo processInfo] processName] UTF8String];
    int found = appName.find(" ");
    if (found!=std::string::npos)
        appName = appName.substr(0,found);
    
    return appName;
}

void createSimulator(const char* viewName, float width, float height,bool isLandscape,float frameZoomFactor)
{
}

@implementation AppController

@synthesize menu;

- (void) dealloc
{
    if (_buildTask)
    {
        [_buildTask interrupt];
        _buildTask = nil;
    }
    [super dealloc];
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    auto player = player::PlayerMac::create();
    player->setController(self);

    _isAlwaysOnTop = NO;
    _debugLogFile = 0;

    _buildTask = nil;
    _isBuildingFinished = YES;

    // load QUICK_V3_ROOT from ~/.QUICK_V3_ROOT
    NSMutableString *path = [NSMutableString stringWithString:NSHomeDirectory()];
    [path appendString:@"/.QUICK_V3_ROOT"];
    NSError *error = [[[NSError alloc] init] autorelease];
    NSString *env = [NSString stringWithContentsOfFile:path
                                              encoding:NSUTF8StringEncoding
                                                 error:&error];
    if ([error code] || env.length == 0)
    {
        [self showAlertWithoutSheet:@"Please run \"setup_mac.sh\", set quick-cocos2d-x root path."
                          withTitle:@"quick player error"];
        [[NSApplication sharedApplication] terminate:self];
    }

    env = [env stringByTrimmingCharactersInSet:[NSCharacterSet newlineCharacterSet]];
    SimulatorConfig::getInstance()->setQuickCocos2dxRootPath([env cStringUsingEncoding:NSUTF8StringEncoding]);

    [self updateProjectFromCommandLineArgs:&_project];
    [self createWindowAndGLView];
    [self registerEventsHandler];
    [self startup];
}

- (BOOL) windowShouldClose:(id)sender
{
    return YES;
}

- (void) windowWillClose:(NSNotification *)notification
{
    [[NSRunningApplication currentApplication] terminate];
}

- (BOOL) applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)theApplication
{
    return YES;
}

- (NSMutableArray*) makeCommandLineArgsFromProjectConfig
{
    return [self makeCommandLineArgsFromProjectConfig:kProjectConfigAll];
}

- (NSMutableArray*) makeCommandLineArgsFromProjectConfig:(unsigned int)mask
{
    _project.setWindowOffset(Vec2(_window.frame.origin.x, _window.frame.origin.y));
    NSString *commandLine = [NSString stringWithCString:_project.makeCommandLine(mask).c_str()
                                               encoding:NSUTF8StringEncoding];
    return [NSMutableArray arrayWithArray:[commandLine componentsSeparatedByString:@" "]];
}

- (void) updateProjectFromCommandLineArgs:(ProjectConfig*)config
{
    NSArray *nsargs = [[NSProcessInfo processInfo] arguments];
    long n = [nsargs count];
    if (n >= 2)
    {
        vector<string> args;
        for (int i = 0; i < [nsargs count]; ++i)
        {
            string arg = [[nsargs objectAtIndex:i] cStringUsingEncoding:NSUTF8StringEncoding];
            if (arg.length()) args.push_back(arg);
        }

        if (args.size() && args.at(1).at(0) == '/')
        {
            // for Code IDE before RC2
            config->setProjectDir(args.at(1));
            config->setDebuggerType(kCCLuaDebuggerCodeIDE);
        }
        config->parseCommandLine(args);
    }

    if (config->getProjectDir().length() == 0)
    {
        config->resetToWelcome();
    }
}

- (void) launch:(NSArray*)args
{
    NSURL *url = [NSURL fileURLWithPath:[[NSBundle mainBundle] bundlePath]];
    NSMutableDictionary *configuration = [NSMutableDictionary dictionaryWithObject:args forKey:NSWorkspaceLaunchConfigurationArguments];
    NSError *error = [[[NSError alloc] init] autorelease];
    [[NSWorkspace sharedWorkspace] launchApplicationAtURL:url
                                                  options:NSWorkspaceLaunchNewInstance
                                            configuration:configuration error:&error];
}

- (void) relaunch:(NSArray*)args
{
    [self launch:args];
    [[NSApplication sharedApplication] terminate:self];
}

- (void) relaunch
{
    [self relaunch:[self makeCommandLineArgsFromProjectConfig]];
}

- (void) showAlertWithoutSheet:(NSString*)message withTitle:(NSString*)title
{
    NSAlert *alert = [[[NSAlert alloc] init] autorelease];
	[alert addButtonWithTitle:@"OK"];
	[alert setMessageText:message];
	[alert setInformativeText:title];
	[alert setAlertStyle:NSWarningAlertStyle];
    [alert runModal];
}

- (void) loadLuaConfig
{
    LuaEngine* pEngine = LuaEngine::getInstance();
    ScriptEngineManager::getInstance()->setScriptEngine(pEngine);

    luaopen_PlayerLuaCore(pEngine->getLuaStack()->getLuaState());
    luaopen_PlayerLuaCore_Manual(pEngine->getLuaStack()->getLuaState());
    

    NSMutableString *path = [NSMutableString stringWithString:NSHomeDirectory()];
    [path appendString:@"/"];

    
    //
    // set user home dir
    //
    lua_pushstring(pEngine->getLuaStack()->getLuaState(), path.UTF8String);
    lua_setglobal(pEngine->getLuaStack()->getLuaState(), "__USER_HOME__");


    //
    // ugly: Add the opening project to the "Open Recents" list
    //
    lua_pushstring(pEngine->getLuaStack()->getLuaState(), _project.getProjectDir().c_str());
    lua_setglobal(pEngine->getLuaStack()->getLuaState(), "__PLAYER_OPEN_TITLE__");
    
    lua_pushstring(pEngine->getLuaStack()->getLuaState(), _project.makeCommandLine().c_str());
    lua_setglobal(pEngine->getLuaStack()->getLuaState(), "__PLAYER_OPEN_COMMAND__");

    //
    // load player.lua file
    //
    string playerCoreFilePath = SimulatorConfig::getInstance()->getQuickCocos2dxRootPath() + "quick/welcome/src/player.lua";
    pEngine->executeScriptFile(playerCoreFilePath.c_str());
}

- (void) adjustEditMenuIndex
{
    NSApplication *thisApp = [NSApplication sharedApplication];
    NSMenu *mainMenu = [thisApp mainMenu];

    NSMenuItem *editMenuItem = [mainMenu itemWithTitle:@"Edit"];
    if (editMenuItem)
    {
        NSUInteger index = 2;
        if (index > [mainMenu itemArray].count)
            index = [mainMenu itemArray].count;
        [[editMenuItem menu] removeItem:editMenuItem];
        [mainMenu insertItem:editMenuItem atIndex:index];
    }
}

#pragma mark -
#pragma mark functions

- (void) createWindowAndGLView
{
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    GLView::setGLContextAttrs(glContextAttrs);
    
    float frameScale = _project.getFrameScale();
    
    // create opengl view
    cocos2d::Size frameSize = _project.getFrameSize();

    const cocos2d::Rect frameRect = cocos2d::Rect(0, 0, frameSize.width, frameSize.height);
    GLViewImpl *eglView = GLViewImpl::createWithRect("player", frameRect, frameScale, _project.isResizeWindow());

    auto director = Director::getInstance();
    director->setOpenGLView(eglView);
    
    _window = eglView->getCocoaWindow();
    [NSApp setDelegate:self];
    [_window center];

    if (_project.getProjectDir().length())
    {
        [self setZoom:_project.getFrameScale()];
        Vec2 pos = _project.getWindowOffset();
        if (pos.x != 0 && pos.y != 0)
        {
            [_window setFrameOrigin:NSMakePoint(pos.x, pos.y)];
        }
    }
}

- (IBAction) onFileClose:(id)sender
{
    EventCustom event("APP.WINDOW_CLOSE_EVENT");
    event.setDataString("{\"name\":\"close\"}");
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}

- (void) registerEventsHandler
{
    [self registerKeyboardEventHandler];
    [self registerWindowEventsHandler];
}

- (void) registerWindowEventsHandler
{
    auto eventDispatcher = Director::getInstance()->getEventDispatcher();
    eventDispatcher->addCustomEventListener("APP.WINDOW_CLOSE_EVENT", [&](EventCustom* event)
        {
            // If script set event's result to "cancel", ignore window close event
            EventCustom forwardEvent("APP.EVENT");
            stringstream buf;
            buf << "{\"name\":\"close\"}";
            forwardEvent.setDataString(buf.str());
            Director::getInstance()->getEventDispatcher()->dispatchEvent(&forwardEvent);
            if (forwardEvent.getResult().compare("cancel") != 0)
            {
                GLViewImpl *glview = (GLViewImpl *) Director::getInstance()->getOpenGLView();
                glfwSetWindowShouldClose(glview->getWindow(), 1);
            }
        });
    
    ProjectConfig& lambdaProject = _project;
    eventDispatcher->addCustomEventListener("APP.VIEW_SCALE", [&](EventCustom* event)
        {
            float scale = atof(event->getDataString().c_str());
            lambdaProject.setFrameScale(scale);
            cocos2d::Director::getInstance()->getOpenGLView()->setFrameZoomFactor(scale);
        });
}

- (void) registerKeyboardEventHandler
{
    auto keyEvent = cocos2d::EventListenerKeyboard::create();
    keyEvent->onKeyReleased = [](EventKeyboard::KeyCode key, Event*) {
        auto event = EventCustom("APP.EVENT");
        stringstream data;
        data << "{\"name\":\"keyReleased\",\"data\":" << (int)key << "}";
        event.setDataString(data.str());
        Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
    };
    
    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(keyEvent, 1);
}

- (void) startup
{
    FileUtils::getInstance()->setPopupNotify(false);
    
    std::string path = SimulatorConfig::getInstance()->getQuickCocos2dxRootPath();
    const string projectDir = _project.getProjectDir();
    if (projectDir.length())
    {
        FileUtils::getInstance()->setSearchRootPath(projectDir.c_str());
        if (_project.isWriteDebugLogToFile())
        {
            [self writeDebugLogToFile:_project.getDebugLogFilePath()];
        }
    }
    
    // set framework path
    if (!_project.isLoadPrecompiledFramework())
    {
        FileUtils::getInstance()->addSearchPath(SimulatorConfig::getInstance()->getQuickCocos2dxRootPath() + "quick/");
    }

    const string writablePath = _project.getWritableRealPath();
    if (writablePath.length())
    {
        FileUtils::getInstance()->setWritablePath(writablePath.c_str());
    }

    if (_project.isShowConsole())
    {
        [self openConsoleWindow];
        CCLOG("%s\n",Configuration::getInstance()->getInfo().c_str());
    }
    
    [self loadLuaConfig];
    [self adjustEditMenuIndex];
    if (!_project.isAppMenu())
    {
        NSMenu *mainMenu = [[NSApplication sharedApplication] mainMenu];
        NSArray *menuArray = [mainMenu itemArray];
        for (int i = 1; i < [menuArray count]; i++)
        {
            id onemenu = [menuArray objectAtIndex:i];
            [mainMenu removeItem:onemenu];
        }
    }
    
    // app
    _app = new AppDelegate();
    _app->setProjectConfig(_project);
    Application::getInstance()->run();
    // After run, application needs to be terminated immediately.
    [NSApp terminate: self];
}

- (void) openConsoleWindow
{
    if (!_consoleController)
    {
        _consoleController = [[ConsoleWindowController alloc] initWithWindowNibName:@"ConsoleWindow"];
    }
    [_consoleController.window orderFrontRegardless];

    //set console pipe
    _pipe = [NSPipe pipe] ;
    _pipeReadHandle = [_pipe fileHandleForReading] ;

    int outfd = [[_pipe fileHandleForWriting] fileDescriptor];
    if (dup2(outfd, fileno(stderr)) != fileno(stderr) || dup2(outfd, fileno(stdout)) != fileno(stdout))
    {
        perror("Unable to redirect output");
        //        [self showAlert:@"Unable to redirect output to console!" withTitle:@"player error"];
    }
    else
    {
        [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(handleNotification:) name: NSFileHandleReadCompletionNotification object: _pipeReadHandle] ;
        [_pipeReadHandle readInBackgroundAndNotify] ;
    }
}

- (bool) writeDebugLogToFile:(const string)path
{
    if (_debugLogFile) return true;
    //log to file
    if(_fileHandle) return true;
    NSString *fPath = [NSString stringWithCString:path.c_str() encoding:[NSString defaultCStringEncoding]];
    [[NSFileManager defaultManager] createFileAtPath:fPath contents:nil attributes:nil] ;
    _fileHandle = [NSFileHandle fileHandleForWritingAtPath:fPath];
    [_fileHandle retain];
    return true;
}

- (void)handleNotification:(NSNotification *)note
{
    //NSLog(@"Received notification: %@", note);
    [_pipeReadHandle readInBackgroundAndNotify] ;
    NSData *data = [[note userInfo] objectForKey:NSFileHandleNotificationDataItem];
    NSString *str = [[[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding] autorelease];

    //show log to console
    [_consoleController trace:str];
    if(_fileHandle!=nil){
        [_fileHandle writeData:[str dataUsingEncoding:NSUTF8StringEncoding]];
    }

}

- (void) close_debugLogFile
{
    if(_fileHandle){
        [_fileHandle closeFile];
        [_fileHandle release];
        _fileHandle = nil;
    }
    if (_debugLogFile)
    {
        close(_debugLogFile);
        _debugLogFile = 0;
        NSNotificationCenter *nc = [NSNotificationCenter defaultCenter];
        [nc removeObserver:self];
    }
}

- (void) setZoom:(float)scale
{
    Director::getInstance()->getOpenGLView()->setFrameZoomFactor(scale);
    _project.setFrameScale(scale);
}

@end
