/****************************************************************************
 Copyright (c) 2010 cocos2d-x.org
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <string>
#include <vector>

#import "SimulatorApp.h"
#include "AppDelegate.h"
#include "glfw3.h"
#include "glfw3native.h"
#include "runtime/Runtime.h"
#include "runtime/ConfigParser.h"

#include "cocos2d.h"

#include "platform/mac/PlayerMac.h"
#include "AppEvent.h"
#include "AppLang.h"


#if (GLFW_VERSION_MAJOR >= 3) && (GLFW_VERSION_MINOR >= 1)
#define PLAYER_SUPPORT_DROP 1
#else
#define PLAYER_SUPPORT_DROP 0
#endif

using namespace std;
using namespace cocos2d;

static id SIMULATOR = nullptr;
@implementation AppController

@synthesize menu;

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

#if (PLAYER_SUPPORT_DROP > 0)
static void glfwDropFunc(GLFWwindow *window, int count, const char **files)
{
    AppEvent forwardEvent(kAppEventDropName, APP_EVENT_DROP);
    std::string firstFile(files[0]);
    forwardEvent.setDataString(firstFile);
    
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&forwardEvent);
}
#endif

-(void) dealloc
{
    Director::getInstance()->end();
    player::PlayerProtocol::getInstance()->purgeInstance();
    [super dealloc];
}

#pragma mark -
#pragma delegates

-(BOOL)application:(NSApplication*)app openFile:(NSString*)path
{
    NSFileManager *fm = [NSFileManager defaultManager];
    BOOL isDirectory = NO;
    if (![fm fileExistsAtPath:path isDirectory:&isDirectory])
    {
        return NO;
    }
    
    if (isDirectory)
    {
        // check src folder
        if ([fm fileExistsAtPath:[path stringByAppendingString:@"/src/main.lua"]])
        {
            _project.setProjectDir([path cStringUsingEncoding:NSUTF8StringEncoding]);
            _entryPath = "$(PROJDIR)/src/main.lua";
        }
        else if ([fm fileExistsAtPath:[path stringByAppendingString:@"/src/main.js"]])
        {
            _project.setProjectDir([path cStringUsingEncoding:NSUTF8StringEncoding]);
            _entryPath = "$(PROJDIR)/src/main.js";
        }
    }
    else
    {
        _project.setProjectDir([path cStringUsingEncoding:NSUTF8StringEncoding]);
        _entryPath = [path cStringUsingEncoding:NSUTF8StringEncoding];
    }
    
    return YES;
}

-(void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    SIMULATOR = self;
    player::PlayerMac::create();
    
    _debugLogFile = 0;
    
    [self parseCocosProjectConfig:&_project];
    [self updateProjectFromCommandLineArgs:&_project];
    
    if (_entryPath.length())
    {
        _project.setScriptFile(_entryPath);
    }
    
    [self createWindowAndGLView];
    [self startup];
}

#pragma mark -
#pragma mark functions

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
    vector<string> args = _project.makeCommandLineVector();
    NSMutableArray *commandArray = [NSMutableArray arrayWithCapacity:args.size()];
    for (auto &path : args)
    {
        [commandArray addObject:[NSString stringWithUTF8String:path.c_str()]];
    }
    return commandArray;
}

- (void) parseCocosProjectConfig:(ProjectConfig*)config
{
    // get project directory
    ProjectConfig tmpConfig;
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
            // FIXME:
            // for Code IDE before RC2
            tmpConfig.setProjectDir(args.at(1));
        }
        
        tmpConfig.parseCommandLine(args);
    }
    
    // set project directory as search root path
    string solutionDir = tmpConfig.getProjectDir();
    string spath = solutionDir;
    if (!solutionDir.empty())
    {
        for (int i = 0; i < solutionDir.size(); ++i)
        {
            if (solutionDir[i] == '\\')
            {
                solutionDir[i] = '/';
            }
        }

        spath = solutionDir;
        if (spath[spath.length() - 1] == '/') {
            spath = spath.substr(0, spath.length() - 1);
        }
        string strExtention = FileUtils::getInstance()->getFileExtension(spath);
        int pos = -1;
        if(strExtention.compare(".csd") == 0)
        {
            pos = spath.rfind('/');
            if(pos > 0)
                spath = spath.substr(0, pos);
        }
        pos = spath.rfind('/');
        if(pos > 0)
            spath = spath.substr(0, pos+1);
        FileUtils::getInstance()->addSearchPath(spath);

        FileUtils::getInstance()->setDefaultResourceRootPath(solutionDir);
        FileUtils::getInstance()->addSearchPath(solutionDir);
        FileUtils::getInstance()->addSearchPath(tmpConfig.getProjectDir());
    }
    else
    {
        FileUtils::getInstance()->setDefaultResourceRootPath(tmpConfig.getProjectDir());
    }

    // parse config.json
    auto parser = ConfigParser::getInstance();
    auto configPath = spath.append(CONFIG_FILE);
    if(!FileUtils::getInstance()->isFileExist(configPath))
        configPath = solutionDir.append(CONFIG_FILE);
    parser->readConfig(configPath);
    
    // set information
    config->setConsolePort(parser->getConsolePort());
    config->setFileUploadPort(parser->getUploadPort());
    config->setFrameSize(parser->getInitViewSize());
    if (parser->isLanscape())
    {
        config->changeFrameOrientationToLandscape();
    }
    else
    {
        config->changeFrameOrientationToPortait();
    }
    config->setScriptFile(parser->getEntryFile());
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
            config->setDebuggerType(kCCRuntimeDebuggerCodeIDE);
        }
        config->parseCommandLine(args);
    }
}

- (bool) launch:(NSArray*)args
{
    NSURL *url = [NSURL fileURLWithPath:[[NSBundle mainBundle] bundlePath]];
    NSMutableDictionary *configuration = [NSMutableDictionary dictionaryWithObject:args forKey:NSWorkspaceLaunchConfigurationArguments];
    NSError *error = [[[NSError alloc] init] autorelease];
    [[NSWorkspace sharedWorkspace] launchApplicationAtURL:url
                                                  options:NSWorkspaceLaunchNewInstance
                                            configuration:configuration
                                                    error:&error];
    
    if (error.code != 0)
    {
        NSLog(@"Failed to launch app: %@", [error localizedDescription]);
    }
    return (error.code==0);
}

- (void) relaunch:(NSArray*)args
{
    if ([self launch:args])
    {
        [[NSApplication sharedApplication] terminate:self];
    }
    else
    {
        NSLog(@"RELAUNCH: %@", args);
    }
}

- (void) relaunch
{
    [self relaunch:[self makeCommandLineArgsFromProjectConfig]];
}

- (float) titleBarHeight
{
    NSRect frame = NSMakeRect (0, 0, 100, 100);
    
    NSRect contentRect;
    contentRect = [NSWindow contentRectForFrameRect: frame
                                          styleMask: NSTitledWindowMask];
    
    return (frame.size.height - contentRect.size.height);
    
}

- (void) createWindowAndGLView
{
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    GLView::setGLContextAttrs(glContextAttrs);
    
    // create console window **MUST** before create opengl view
    float frameScale = _project.getFrameScale();
    
    // get frame size
    cocos2d::Size frameSize = _project.getFrameSize();
    ConfigParser::getInstance()->setInitViewSize(frameSize);
    
    // check screen workarea size
    NSRect workarea = [NSScreen mainScreen].visibleFrame;
    float workareaWidth = workarea.size.width;
    float workareaHeight = workarea.size.height - [self titleBarHeight];
    CCLOG("WORKAREA WIDTH %0.2f, HEIGHT %0.2f", workareaWidth, workareaHeight);
    while (true && frameScale > 0.25f)
    {
        if (frameSize.width * frameScale > workareaWidth || frameSize.height * frameScale > workareaHeight)
        {
            frameScale = frameScale - 0.25f;
        }
        else
        {
            break;
        }
    }
    
    if (frameScale < 0.25f) frameScale = 0.25f;
    _project.setFrameScale(frameScale);
    CCLOG("FRAME SCALE = %0.2f", frameScale);
    
    // check window offset
    Vec2 pos = _project.getWindowOffset();
    if (pos.x < 0) pos.x = 0;
    if (pos.y < 0) pos.y = 0;
    
    // create opengl view
    const cocos2d::Rect frameRect = cocos2d::Rect(0, 0, frameSize.width, frameSize.height);
    std::stringstream title;
    title << "Cocos Simulator (" << _project.getFrameScale() * 100 << "%)";
    GLViewImpl *eglView = GLViewImpl::createWithRect(title.str(), frameRect, frameScale);
    
    auto director = Director::getInstance();
    director->setOpenGLView(eglView);
    
    _window = eglView->getCocoaWindow();
    [[NSApplication sharedApplication] setDelegate: self];
    [_window center];
    
    [self setZoom:_project.getFrameScale()];
    if (pos.x != 0 && pos.y != 0)
    {
        [_window setFrameOrigin:NSMakePoint(pos.x, pos.y)];
    }
    
#if (PLAYER_SUPPORT_DROP > 0)
    glfwSetDropCallback(eglView->getWindow(), glfwDropFunc);
#endif
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
- (void) startup
{
    FileUtils::getInstance()->setPopupNotify(false);
    
    _project.dump();
    
    const string projectDir = _project.getProjectDir();
    if (projectDir.length())
    {
        FileUtils::getInstance()->setDefaultResourceRootPath(projectDir);
        if (_project.isWriteDebugLogToFile())
        {
            [self writeDebugLogToFile:_project.getDebugLogFilePath()];
        }
    }
    
    const string writablePath = _project.getWritableRealPath();
    if (writablePath.length())
    {
        FileUtils::getInstance()->setWritablePath(writablePath.c_str());
    }
    
    // path for looking Lang file, Studio Default images
    NSString *resourcePath = [[NSBundle mainBundle] resourcePath];
    FileUtils::getInstance()->addSearchPath(resourcePath.UTF8String);
    
    // app
    _app = new AppDelegate();
    
    [self setupUI];
    [self adjustEditMenuIndex];
    
    RuntimeEngine::getInstance()->setProjectConfig(_project);
    Application::getInstance()->run();
    CC_SAFE_DELETE(_app);
    // After run, application needs to be terminated immediately.
    [NSApp terminate: self];
}

- (void) setupUI
{
    auto menuBar = player::PlayerProtocol::getInstance()->getMenuService();
    
    // VIEW
    menuBar->addItem("VIEW_MENU", tr("View"));
    SimulatorConfig *config = SimulatorConfig::getInstance();
    int current = config->checkScreenSize(_project.getFrameSize());
    for (int i = 0; i < config->getScreenSizeCount(); i++)
    {
        SimulatorScreenSize size = config->getScreenSize(i);
        std::stringstream menuId;
        menuId << "VIEWSIZE_ITEM_MENU_" << i;
        auto menuItem = menuBar->addItem(menuId.str(), size.title.c_str(), "VIEW_MENU");
        
        if (i == current)
        {
            menuItem->setChecked(true);
        }
    }
    
    menuBar->addItem("DIRECTION_MENU_SEP", "-", "VIEW_MENU");
    menuBar->addItem("DIRECTION_PORTRAIT_MENU", tr("Portrait"), "VIEW_MENU")
    ->setChecked(_project.isPortraitFrame());
    menuBar->addItem("DIRECTION_LANDSCAPE_MENU", tr("Landscape"), "VIEW_MENU")
    ->setChecked(_project.isLandscapeFrame());
    
    menuBar->addItem("VIEW_SCALE_MENU_SEP", "-", "VIEW_MENU");
    
    std::vector<player::PlayerMenuItem*> scaleMenuVector;
    auto scale100Menu = menuBar->addItem("VIEW_SCALE_MENU_100", tr("Zoom Out").append(" (100%)"), "VIEW_MENU");
    scale100Menu->setShortcut("super+0");
    
    auto scale75Menu = menuBar->addItem("VIEW_SCALE_MENU_75", tr("Zoom Out").append(" (75%)"), "VIEW_MENU");
    scale75Menu->setShortcut("super+7");
    
    auto scale50Menu = menuBar->addItem("VIEW_SCALE_MENU_50", tr("Zoom Out").append(" (50%)"), "VIEW_MENU");
    scale50Menu->setShortcut("super+6");
    
    auto scale25Menu = menuBar->addItem("VIEW_SCALE_MENU_25", tr("Zoom Out").append(" (25%)"), "VIEW_MENU");
    scale25Menu->setShortcut("super+5");
    
    int frameScale = int(_project.getFrameScale() * 100);
    if (frameScale == 100)
    {
        scale100Menu->setChecked(true);
    }
    else if (frameScale == 75)
    {
        scale75Menu->setChecked(true);
    }
    else if (frameScale == 50)
    {
        scale50Menu->setChecked(true);
    }
    else if (frameScale == 25)
    {
        scale25Menu->setChecked(true);
    }
    else
    {
        scale100Menu->setChecked(true);
    }
    
    scaleMenuVector.push_back(scale100Menu);
    scaleMenuVector.push_back(scale75Menu);
    scaleMenuVector.push_back(scale50Menu);
    scaleMenuVector.push_back(scale25Menu);
    
    menuBar->addItem("REFRESH_MENU_SEP", "-", "VIEW_MENU");
    menuBar->addItem("REFRESH_MENU", tr("Refresh"), "VIEW_MENU")->setShortcut("super+r");
    
    ProjectConfig &project = _project;
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto window = _window;
    dispatcher->addEventListenerWithFixedPriority(EventListenerCustom::create(kAppEventName, [&project, scaleMenuVector, window](EventCustom* event){
        auto menuEvent = dynamic_cast<AppEvent*>(event);
        if (menuEvent)
        {
            rapidjson::Document dArgParse;
            dArgParse.Parse<0>(menuEvent->getDataString().c_str());
            if (dArgParse.HasMember("name"))
            {
                string strcmd = dArgParse["name"].GetString();
                
                if (strcmd == "menuClicked")
                {
                    player::PlayerMenuItem *menuItem = static_cast<player::PlayerMenuItem*>(menuEvent->getUserData());
                    if (menuItem)
                    {
                        if (menuItem->isChecked())
                        {
                            return ;
                        }
                        
                        string data = dArgParse["data"].GetString();
                        if ((data == "CLOSE_MENU") || (data == "EXIT_MENU"))
                        {
                            Director::getInstance()->end();
                        }
                        else if (data == "REFRESH_MENU")
                        {
                            [SIMULATOR relaunch];
                        }
                        else if (data.find("VIEW_SCALE_MENU_") == 0) // begin with VIEW_SCALE_MENU_
                        {
                            string tmp = data.erase(0, strlen("VIEW_SCALE_MENU_"));
                            float scale = atof(tmp.c_str()) / 100.0f;
                            [SIMULATOR setZoom:scale];
                            
                            // update scale menu state
                            for (auto &it : scaleMenuVector)
                            {
                                it->setChecked(false);
                            }
                            menuItem->setChecked(true);
                        }
                        else if (data.find("VIEWSIZE_ITEM_MENU_") == 0) // begin with VIEWSIZE_ITEM_MENU_
                        {
                            string tmp = data.erase(0, strlen("VIEWSIZE_ITEM_MENU_"));
                            int index = atoi(tmp.c_str());
                            SimulatorScreenSize size = SimulatorConfig::getInstance()->getScreenSize(index);
                            
                            if (project.isLandscapeFrame())
                            {
                                std::swap(size.width, size.height);
                            }
                            
                            project.setFrameSize(cocos2d::Size(size.width, size.height));
                            [SIMULATOR relaunch];
                        }
                        else if (data == "DIRECTION_PORTRAIT_MENU")
                        {
                            project.changeFrameOrientationToPortait();
                            [SIMULATOR relaunch];
                        }
                        else if (data == "DIRECTION_LANDSCAPE_MENU")
                        {
                            project.changeFrameOrientationToLandscape();
                            [SIMULATOR relaunch];
                        }
                    }
                }
            }
        }
    }), 1);
    
    // drop
    AppDelegate *app = _app;
    auto listener = EventListenerCustom::create(kAppEventDropName, [&project, app](EventCustom* event)
    {
        AppEvent *dropEvent = dynamic_cast<AppEvent*>(event);
        if (dropEvent)
        {
            string dirPath = dropEvent->getDataString() + "/";
            string configFilePath = dirPath + CONFIG_FILE;
            
            if (FileUtils::getInstance()->isDirectoryExist(dirPath) &&
                FileUtils::getInstance()->isFileExist(configFilePath))
            {
                // parse config.json
                ConfigParser::getInstance()->readConfig(configFilePath);
                
                project.setProjectDir(dirPath);
                project.setScriptFile(ConfigParser::getInstance()->getEntryFile());
                project.setWritablePath(dirPath);
                
                RuntimeEngine::getInstance()->setProjectConfig(project);
//                app->setProjectConfig(project);
//                app->reopenProject();
            }
        }
    });
    dispatcher->addEventListenerWithFixedPriority(listener, 1);
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
    
    if (str)
    {
        //show log to console
        [_consoleController trace:str];
        if(_fileHandle!=nil)
        {
            [_fileHandle writeData:[str dataUsingEncoding:NSUTF8StringEncoding]];
        }
    }
}

- (void) setZoom:(float)scale
{
    Director::getInstance()->getOpenGLView()->setFrameZoomFactor(scale);
    _project.setFrameScale(scale);
    std::stringstream title;
    title << "Cocos " << tr("Simulator") << " (" << _project.getFrameScale() * 100 << "%)";
    [_window setTitle:[NSString stringWithUTF8String:title.str().c_str()]];
}

- (BOOL) applicationShouldHandleReopen:(NSApplication *)sender hasVisibleWindows:(BOOL)flag
{
    return NO;
}

#pragma mark - 

-(IBAction)onFileClose:(id)sender
{
    CC_SAFE_DELETE(_app);
    [[NSApplication sharedApplication] terminate:self];
}

-(IBAction)onWindowAlwaysOnTop:(id)sender
{
    NSInteger state = [sender state];
    
    if (state == NSOffState)
    {
        [_window setLevel:NSFloatingWindowLevel];
        [sender setState:NSOnState];
    }
    else
    {
        [_window setLevel:NSNormalWindowLevel];
        [sender setState:NSOffState];
    }
}

- (void)applicationWillTerminate:(NSNotification *)notification
{
    CC_SAFE_DELETE(_app);
    [[NSApplication sharedApplication] terminate:self];
}

@end
