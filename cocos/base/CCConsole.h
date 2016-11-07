/****************************************************************************
 Copyright (c) 2013-2016 Chukong Technologies Inc.

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

#ifndef __CCCONSOLE_H__
#define __CCCONSOLE_H__
/// @cond DO_NOT_SHOW

#if defined(_MSC_VER) || defined(__MINGW32__)
#include <BaseTsd.h>
#include <WinSock2.h>

#ifndef __SSIZE_T
#define __SSIZE_T
typedef SSIZE_T ssize_t;
#endif // __SSIZE_T

#else
#include <sys/select.h>
#endif

#include <thread>
#include <vector>
#include <map>
#include <functional>
#include <string>
#include <mutex>
#include <stdarg.h>

#include "base/CCRef.h"
#include "base/ccMacros.h"
#include "platform/CCPlatformMacros.h"

NS_CC_BEGIN

/// The max length of CCLog message.
static const int MAX_LOG_LENGTH = 16*1024;

/**
 @brief Output Debug message.
 */
void CC_DLL log(const char * format, ...) CC_FORMAT_PRINTF(1, 2);

/** Console is helper class that lets the developer control the game from TCP connection.
 Console will spawn a new thread that will listen to a specified TCP port.
 Console has a basic token parser. Each token is associated with an std::function<void(int)>.
 If the std::function<> needs to use the cocos2d API, it needs to call
 
 ```
 scheduler->performFunctionInCocosThread( ... );
 ```
 */

class CC_DLL Console
    : public Ref
{
public:
    /** Console Utils */
    class Utility {
    public:
        // Trimming functions
        static std::string& ltrim(std::string& s);
        static std::string& rtrim(std::string& s);
        static std::string& trim(std::string& s);
        
        // split
        static std::vector<std::string>& split(const std::string& s, char delim, std::vector<std::string>& elems);
        static std::vector<std::string> split(const std::string& s, char delim);
        
        /** Checks myString is a floating-point type. */
        static bool isFloat(const std::string& myString);
        
        /** send a message to console */
        static ssize_t sendToConsole(int fd, const void* buffer, size_t length, int flags = 0);
        
        /** my dprintf() */
        static ssize_t mydprintf(int sock, const char *format, ...);
        
        /** send prompt string to console */
        static void sendPrompt(int fd);
        
        /** set a new string for the prompt. */
        static void setPrompt(const std::string &prompt);
        
        /** get the prompt string. */
        static const std::string& getPrompt();
        
    private:
        static std::string _prompt;  /*!< prompt */
    };
    
    /** Command Struct */
    struct Command {
        using Callback = std::function<void(int fd, const std::string& args)>;
        std::string name;
        std::string help;
        Callback callback{nullptr};
        std::map<std::string, Command> subCommands;
        
        /** Constructor */
        Command() {}
        Command(std::string name_, std::string help_) : name(name_), help(help_) {};
        Command(std::string name_, std::string help_, Callback callback_) : name(name_), help(help_), callback(callback_) {};
        
        /** add callback */
        void addCallback(const Callback& callback);
        
        /** add sub command */
        void addSubCommand(const Command& subCmd);
        
        /** get sub command */
        const Command* getSubCommand(const std::string& subCmdName) const;
        
        /** delete sub command */
        void delSubCommand(const std::string& subCmdName);
        
        /** help command handler */
        void commandHelp(int fd, const std::string& args);
        
        /** generic command handler */
        void commandGeneric(int fd, const std::string& args);
    };

    /** Constructor */
    Console();

    /** Destructor */
    virtual ~Console();

    /** starts listening to specified TCP port */
    bool listenOnTCP(int port);

    /** starts listening to specified file descriptor */
    bool listenOnFileDescriptor(int fd);

    /** stops the Console. 'stop' will be called at destruction time as well */
    void stop();

    /** add custom command */
    void addCommand(const Command& cmd);
    void addSubCommand(const std::string& cmdName, const Command& subCmd);
    void addSubCommand(Command& cmd, const Command& subCmd);
    
    /** get custom command */
    const Command* getCommand(const std::string& cmdName);
    const Command* getSubCommand(const std::string& cmdName, const std::string& subCmdName);
    const Command* getSubCommand(const Command& cmd, const std::string& subCmdName);
    
    /** delete custom command */
    void delCommand(const std::string& cmdName);
    void delSubCommand(const std::string& cmdName, const std::string& subCmdName);
    void delSubCommand(Command& cmd, const std::string& subCmdName);

    /** log something in the console */
    void log(const char *buf);

    /**
     * set bind address
     *
     * @address : 127.0.0.1
     */
    void setBindAddress(const std::string &address);

protected:
    // Main Loop
    void loop();
    
    // Helpers
    ssize_t readline(int fd, char *buf, size_t maxlen);
    ssize_t readBytes(int fd, char* buffer, size_t maxlen, bool* more);
    bool parseCommand(int fd);
    
    void addClient();
    
    // create a map of command.
    void createCommandAllocator();
    void createCommandConfig();
    void createCommandDebugMsg();
    void createCommandDirector();
    void createCommandExit();
    void createCommandFileUtils();
    void createCommandFps();
    void createCommandHelp();
    void createCommandProjection();
    void createCommandResolution();
    void createCommandSceneGraph();
    void createCommandTexture();
    void createCommandTouch();
    void createCommandUpload();
    void createCommandVersion();

    // Add commands here
    void commandAllocator(int fd, const std::string& args);
    void commandConfig(int fd, const std::string& args);
    void commandDebugMsg(int fd, const std::string& args);
    void commandDebugMsgSubCommandOnOff(int fd, const std::string& args);
    void commandDirectorSubCommandPause(int fd, const std::string& args);
    void commandDirectorSubCommandResume(int fd, const std::string& args);
    void commandDirectorSubCommandStop(int fd, const std::string& args);
    void commandDirectorSubCommandStart(int fd, const std::string& args);
    void commandDirectorSubCommandEnd(int fd, const std::string& args);
    void commandExit(int fd, const std::string& args);
    void commandFileUtils(int fd, const std::string& args);
    void commandFileUtilsSubCommandFlush(int fd, const std::string& args);
    void commandFps(int fd, const std::string& args);
    void commandFpsSubCommandOnOff(int fd, const std::string& args);
    void commandHelp(int fd, const std::string& args);
    void commandProjection(int fd, const std::string& args);
    void commandProjectionSubCommand2d(int fd, const std::string& args);
    void commandProjectionSubCommand3d(int fd, const std::string& args);
    void commandResolution(int fd, const std::string& args);
    void commandResolutionSubCommandEmpty(int fd, const std::string& args);
    void commandSceneGraph(int fd, const std::string& args);
    void commandTextures(int fd, const std::string& args);
    void commandTexturesSubCommandFlush(int fd, const std::string& args);
    void commandTouchSubCommandTap(int fd, const std::string& args);
    void commandTouchSubCommandSwipe(int fd, const std::string& args);
    void commandUpload(int fd);
    void commandVersion(int fd, const std::string& args);
    // file descriptor: socket, console, etc.
    int _listenfd;
    int _maxfd;
    std::vector<int> _fds;
    std::thread _thread;

    fd_set _read_set;

    bool _running;
    bool _endThread;

    std::map<std::string, Command> _commands;

    // strings generated by cocos2d sent to the remote console
    bool _sendDebugStrings;
    std::mutex _DebugStringsMutex;
    std::vector<std::string> _DebugStrings;

    intptr_t _touchId;

    std::string _bindAddress;
private:
    CC_DISALLOW_COPY_AND_ASSIGN(Console);
    
    // helper functions
    int printSceneGraph(int fd, Node* node, int level);
    void printSceneGraphBoot(int fd);
    void printFileUtils(int fd);
    
    /** send help message to console */
    static void sendHelp(int fd, const std::map<std::string, Command>& commands, const char* msg);
};

NS_CC_END

/// @endcond
#endif /* defined(__CCCONSOLE_H__) */
