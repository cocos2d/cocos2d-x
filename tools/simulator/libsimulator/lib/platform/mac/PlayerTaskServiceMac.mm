/****************************************************************************
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


#include "PlayerTaskServiceMac.h"

@implementation PlayerTaskPrivate

@synthesize buildTask = _buildTask;
@synthesize isRunning = _isRunning;
@synthesize exitCode  = _exitCode;
@synthesize output    = _output;

-(id) init
{
    if ((self = [super init])) {
        _isRunning = NO;
        _exitCode = 0;
    }
    
    return self;
}

-(void) dealloc
{
    [_output release];
    [super dealloc];
}

-(void)performSelectorInBackground:(SEL)selector withObjects:(id)object, ...
{
    NSMethodSignature *signature = [self methodSignatureForSelector:selector];
    
    // setup the invocation
    NSInvocation *invocation = [NSInvocation invocationWithMethodSignature:signature];
    invocation.target = self;
    invocation.selector = selector;
    
    // associate the arguments
    va_list objects;
    va_start(objects, object);
    unsigned int objectCounter = 2;
    for (id obj = object; obj != nil; obj = va_arg(objects, id))
    {
        [invocation setArgument:&obj atIndex:objectCounter++];
    }
    va_end(objects);
    
    // make sure to invoke on a background queue
    NSInvocationOperation *operation = [[NSInvocationOperation alloc] initWithInvocation:invocation];
    NSOperationQueue *backgroundQueue = [[NSOperationQueue alloc] init];
    [backgroundQueue addOperation:operation];
}

- (void) runScriptAsyn:(NSString *)absScriptPath withArguments:(NSArray *) arguments
{
    _isRunning = YES;
    [self performSelectorInBackground:@selector(runScriptSync:withArguments:)
                          withObjects:absScriptPath, arguments, nil];
}

- (void) runScriptSync:(NSString *)absScriptPath withArguments:(NSArray *)arguments
{
    if (!absScriptPath)
    {
        CCLOG("Please check your script (%s)", absScriptPath.UTF8String);
        return ;
    }
    
    _buildTask = [[NSTask alloc] init];
    [_buildTask setLaunchPath:absScriptPath];
    
    if (!arguments)
    {
        arguments = [NSArray array];
    }
    [_buildTask setArguments:arguments];
    
    //
    NSPipe *pipe;
    pipe = [NSPipe pipe];
    [_buildTask setStandardOutput: pipe];
    
    fileHandle = [pipe fileHandleForReading];
    
    //
    [_buildTask launch];
    [_buildTask waitUntilExit];

    NSData *data;
    data = [fileHandle readDataToEndOfFile];
    
    _output = [[NSString alloc] initWithData: data
                                    encoding: NSUTF8StringEncoding];
    _isRunning = NO;
    _exitCode = [_buildTask terminationStatus];
    
    [fileHandle closeFile];
    [_buildTask release];
    _buildTask = nil;
}

@end

PLAYER_NS_BEGIN

PlayerTaskMac *PlayerTaskMac::create(const std::string &name, const std::string &executePath, const std::string &commandLineArguments)
{
    PlayerTaskMac *task = new PlayerTaskMac(name, executePath, commandLineArguments);
    task->autorelease();
    return task;
}

PlayerTaskMac::PlayerTaskMac(const std::string &name,
                             const std::string &executePath,
                             const std::string &commandLineArguments)
: PlayerTask(name, executePath, commandLineArguments)
{
    _taskPrivate = [[PlayerTaskPrivate alloc] init];
}

PlayerTaskMac::~PlayerTaskMac()
{
    cleanup();
}

bool PlayerTaskMac::run()
{
    if (!isIdle())
    {
        CCLOG("PlayerTaskMac::run() - task is not idle");
        return false;
    }
    
    NSString *commandLine = [NSString stringWithCString:_commandLineArguments.c_str()
                                               encoding:NSUTF8StringEncoding];
    [_taskPrivate runScriptAsyn:[NSString stringWithUTF8String:_executePath.data()]
                  withArguments:[NSMutableArray arrayWithArray:[commandLine componentsSeparatedByString:@" "]]];
    _state = STATE_RUNNING;
    
    cocos2d::Director::getInstance()->getScheduler()->scheduleUpdate(this, 0, false);
    return true;
}

void PlayerTaskMac::runInTerminal()
{
    NSString *s = [NSString stringWithFormat:
                   @"tell application \"Terminal\" to do script \"%s %s\"", _executePath.c_str(), _commandLineArguments.c_str()];
    
    NSAppleScript *as = [[NSAppleScript alloc] initWithSource: s];
    [as executeAndReturnError:nil];
}

void PlayerTaskMac::stop()
{
    cleanup();
}

void PlayerTaskMac::update(float dt)
{
    _lifetime += dt;
    
    if (_taskPrivate.isRunning)
    {
        return ;
    }
    
    cocos2d::Director::getInstance()->getScheduler()->unscheduleAllForTarget(this);
    cleanup();
}

void PlayerTaskMac::appendOutput(const char *data)
{
    _output.append(data);
}

void PlayerTaskMac::cleanup()
{
    
    _state = STATE_COMPLETED;
    
    [NSObject cancelPreviousPerformRequestsWithTarget:_taskPrivate];
    [_taskPrivate.buildTask interrupt];
    
    _resultCode = _taskPrivate.exitCode;
    _output.append(_taskPrivate.output.UTF8String);
    
    [_taskPrivate release];
    _taskPrivate = nil;
    CCLOG("\nCMD: (exit code: %d) %s", _resultCode, _output.c_str());
    
    cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(_name);
}

std::u16string PlayerTaskMac::makeCommandLine() const
{
    std::stringstream buf;
    buf << "\"";
    buf << _executePath;
    buf << "\" ";
    buf << _commandLineArguments;
    
    std::u16string u16command;
    cocos2d::StringUtils::UTF8ToUTF16(buf.str(), u16command);
    return u16command;
}

PlayerTaskServiceMac::PlayerTaskServiceMac()
{
}

PlayerTaskServiceMac::~PlayerTaskServiceMac()
{
    for (auto it = _tasks.begin(); it != _tasks.end(); ++it)
    {
        it->second->stop();
    }
}

PlayerTask *PlayerTaskServiceMac::createTask(const std::string &name,
                                             const std::string &executePath,
                                             const std::string &commandLineArguments)
{
    CCASSERT(_tasks.find(name) == _tasks.end(), "Task already exists.");
    PlayerTaskMac *task = PlayerTaskMac::create(name, executePath, commandLineArguments);
    _tasks.insert(name, task);
    return task;
}

PlayerTask *PlayerTaskServiceMac::getTask(const std::string &name)
{
    auto it = _tasks.find(name);
    return it != _tasks.end() ? it->second : nullptr;
}

void PlayerTaskServiceMac::removeTask(const std::string &name)
{
    auto it = _tasks.find(name);
    if (it != _tasks.end())
    {
        if (!it->second->isCompleted())
        {
            it->second->stop();
        }
        _tasks.erase(it);
    }
}

PLAYER_NS_END
