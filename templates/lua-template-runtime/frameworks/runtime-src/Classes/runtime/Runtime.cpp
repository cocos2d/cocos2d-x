/****************************************************************************
Copyright (c) 2013 cocos2d-x.org

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

#include "Runtime.h"
#include "lua_debugger.h"
#include "CCLuaEngine.h"
#include "cocos2d.h"
#include "json/document.h"
#include "json/filestream.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#include "LuaBasicConversions.h"
#include "VisibleRect.h"
#include "ConfigParser.h"
#include "Protos.pb.h"
#include "zlib.h"
#include "lua.h"

// header files for directory operation
#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#endif

#include <vector>
#include <string>

using namespace std;
using namespace cocos2d;

std::string g_resourcePath;
static std::string g_projectPath;

//1M size 
#define MAXPROTOLENGTH 1048576

#define PROTO_START "RuntimeSend:"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#define usleep(t) Sleep(t)
#else
#include <unistd.h>
#endif

extern string getIPAddress();

const char* getRuntimeVersion()
{
    return "1.5";
}

static string& replaceAll(string& str, const string& old_value, const string& new_value)
{
    size_t start = 0;
    while(true)
    {
        size_t pos = 0;
        if((pos = str.find(old_value, start)) != string::npos) {
            str.replace(pos, old_value.length(), new_value);
            start = pos + new_value.length();
        }
        else break;
    }
    return str;
}

void startScript(string strDebugArg)
{
    // register lua engine
    auto engine = LuaEngine::getInstance();
    if (!strDebugArg.empty())
    {
        // open debugger.lua module
        luaopen_lua_debugger(engine->getLuaStack()->getLuaState());
        engine->executeString(strDebugArg.c_str());
    }
    cocos2d::log("debug args = %s", strDebugArg.c_str());
    engine->executeScriptFile(ConfigParser::getInstance()->getEntryFile().c_str());
}

static void resetLuaModule(const string& fileName)
{
    if (fileName.empty())
    {
        return;
    }
    auto engine = LuaEngine::getInstance();
    LuaStack* luaStack = engine->getLuaStack();
    lua_State* stack = luaStack->getLuaState();
    lua_getglobal(stack, "package");                         /* L: package */
    lua_getfield(stack, -1, "loaded");                       /* L: package loaded */
    lua_pushnil(stack);                                     /* L: lotable ?-.. nil */
    while (0 != lua_next(stack, -2))                     /* L: lotable ?-.. key value */
    {
        //CCLOG("%s - %s \n", tolua_tostring(stack, -2, ""), lua_typename(stack, lua_type(stack, -1)));
        std::string key = tolua_tostring(stack, -2, "");
        std::string tableKey = key;
        size_t found = tableKey.rfind(".lua");
        if (found != std::string::npos)
            tableKey = tableKey.substr(0, found);
        tableKey = replaceAll(tableKey, ".", "/");
        tableKey = replaceAll(tableKey, "\\", "/");
        tableKey.append(".lua");
        found = fileName.rfind(tableKey);
        if (0 == found || (found != std::string::npos && fileName.at(found - 1) == '/'))
        {
            lua_pushstring(stack, key.c_str());
            lua_pushnil(stack);
            if (lua_istable(stack, -5))
            {
                lua_settable(stack, -5);
            }
        }
        lua_pop(stack, 1);
    }
    lua_pop(stack, 2);
}

bool reloadScript(const string& file)
{
    auto director = Director::getInstance();
    FontFNT::purgeCachedData();
    if (director->getOpenGLView())
    {
        SpriteFrameCache::getInstance()->removeSpriteFrames();
        director->getTextureCache()->removeAllTextures();
    }
    FileUtils::getInstance()->purgeCachedEntries();
    string modulefile = file;
    
    if (! modulefile.empty())
    {
        resetLuaModule(modulefile);
    }
    else
    {
        modulefile = ConfigParser::getInstance()->getEntryFile().c_str();
    }
    
    auto engine = LuaEngine::getInstance();
    LuaStack* luaStack = engine->getLuaStack();
    std::string require = "require \'" + modulefile + "\'";
    return luaStack->executeString(require.c_str());
}

// header files for socket
#ifdef _WIN32
#include <io.h>
#include <WS2tcpip.h>

#define bzero(a, b) memset(a, 0, b);

#else
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#endif

class  FileServer
{
   static FileServer *s_sharedFileServer;
public:
    static FileServer* getShareInstance()
    {
        if (s_sharedFileServer == nullptr)
        {
            s_sharedFileServer = new FileServer();
        }
        return s_sharedFileServer;
    }
    bool listenOnTCP(int port);
    void stop();
    
    void readResFileFinfo();
    void addResFileInfo(const char* filename,uint64_t u64);
    void removeResFileInfo(const char *filename);
    rapidjson::Document* getFileCfgJson()
    {
        return &_filecfgjson;
    };
    string getTransingFileName()
    {
        _fileNameMutex.lock();
        string filename = _strFileName;
        _fileNameMutex.unlock();
        return filename;
    }
protected:
    FileServer()
    {
        _listenfd = -1;
        _running = false;
        _endThread = false;
        _protoBuf =nullptr;
    }
    ~FileServer()
    {
        CC_SAFE_DELETE_ARRAY(_protoBuf);
    }
private:
    void loopReceiveFile();
    void loopWriteFile();
    void loopResponse();
    void addResponse(int fd, string filename,int errortype,int errornum);
    enum PROTONUM
    {
        FILEPROTO = 1,
        FILESENDCOMPLETE = 2,
        DIRPROTO = 3,
        DIRSENDCOMPLETE = 4
    };

    struct RecvBufStruct
    {
        runtime::FileSendProtos fileProto;
        std::string contentBuf;
        int fd;
    };

    struct ResponseStruct
    {
        runtime::FileSendComplete fileResponseProto;
        int fd;
    };

    // file descriptor: socket, console, etc.
    int _listenfd;
    int _maxfd;
    std::vector<int> _fds;
    std::thread _responseThread;
    std::thread _receiveThread;
    std::thread _writeThread;
    fd_set _read_set;
    bool _running;
    bool _endThread;
    char *_protoBuf;

    std::list<RecvBufStruct> _recvBufList;
    std::list<ResponseStruct> _responseBufList;
    std::mutex _recvBufListMutex;
    std::mutex _responseBufListMutex;

    rapidjson::Document _filecfgjson; 

    string _strFileName;
    std::mutex _fileNameMutex;

    string _recvErrorFile;
    string _writeErrorFile;
};

FileServer* FileServer::s_sharedFileServer =nullptr;
void FileServer::readResFileFinfo()
{
    string filecfg = g_resourcePath;
    filecfg.append("/");
    filecfg.append("fileinfo_debug.json");
    FILE * pFile = fopen (filecfg.c_str() , "r");
    if(pFile)
    {
        rapidjson::FileStream inputStream(pFile);
        _filecfgjson.ParseStream<0>(inputStream);
        fclose(pFile);
    }
    if(! _filecfgjson.IsObject()){
        _filecfgjson.SetObject();
    }

    //save file info to disk every five second
    Director::getInstance()->getScheduler()->schedule([&](float){
        rapidjson::StringBuffer buffer;
        rapidjson::Writer< rapidjson::StringBuffer > writer(buffer);
        _filecfgjson.Accept(writer);
        const char* str = buffer.GetString();
        string filecfg = g_resourcePath;
        filecfg.append("/");
        filecfg.append("fileinfo_debug.json");
        FILE * pFile = fopen(filecfg.c_str(), "w");
        if (!pFile) return ;
        fwrite(str,sizeof(char), strlen(str), pFile);
        fclose(pFile);
    },this, 5.0f, false, "fileinfo");
}

void FileServer::addResFileInfo(const char* filename,uint64_t u64)
{
    if(_filecfgjson.HasMember(filename)){
        _filecfgjson.RemoveMember(filename);
    }
    char filetime[512]= {0};
    sprintf(filetime, "%llu", u64);
    rapidjson::Value filetimeValue(rapidjson::kStringType);
    filetimeValue.SetString(filetime, _filecfgjson.GetAllocator());
    rapidjson::Value filenameValue(rapidjson::kStringType);
    filenameValue.SetString(filename,_filecfgjson.GetAllocator());
    _filecfgjson.AddMember(filenameValue.GetString(), filetimeValue, _filecfgjson.GetAllocator());
}

void FileServer::removeResFileInfo(const char *filename)
{
    if (_filecfgjson.HasMember(filename)) {
        _filecfgjson.RemoveMember(filename);
    }
}

bool FileServer::listenOnTCP(int port)
{
    int listenfd, n;
    const int on = 1;
    struct addrinfo hints, *res, *ressave;
    char serv[30];

    snprintf(serv, sizeof(serv)-1, "%d", port );
    serv[sizeof(serv)-1]=0;

    bzero(&hints, sizeof(struct addrinfo));
    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_INET; // AF_UNSPEC: Do we need IPv6 ?
    hints.ai_socktype = SOCK_STREAM;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    WSADATA wsaData;
    n = WSAStartup(MAKEWORD(2, 2),&wsaData);
#endif

    if ( (n = getaddrinfo(NULL, serv, &hints, &res)) != 0) {
        fprintf(stderr,"net_listen error for %s: %s", serv, gai_strerror(n));
        return false;
    }

    ressave = res;
    do {
        listenfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if (listenfd < 0)
            continue;       /* error, try next one */
        
        setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (const char*)&on, sizeof(on));
        //setsockopt(listenfd, IPPROTO_TCP, TCP_NODELAY, (const char*)&on, sizeof(on));
        if (::bind(listenfd, res->ai_addr, res->ai_addrlen) == 0)
            break;          /* success */
        
        close(listenfd);    /* bind error, close and try next one */
    } while ((res = res->ai_next) != NULL);

    if (res == NULL)
    {
        perror("net_listen:");
        freeaddrinfo(ressave);
        return false;
    }

    listen(listenfd, 1);

    if (res->ai_family == AF_INET) 
    {
        char buf[INET_ADDRSTRLEN] = "";
        struct sockaddr_in *sin = (struct sockaddr_in*) res->ai_addr;
        if( inet_ntop(res->ai_family, &sin->sin_addr, buf, sizeof(buf)) != NULL )
            cocos2d::log("Console: listening on  %s : %d", buf, ntohs(sin->sin_port));
        else
            perror("inet_ntop");
    } else if (res->ai_family == AF_INET6) 
    {
        char buf[INET6_ADDRSTRLEN] = "";
        struct sockaddr_in6 *sin = (struct sockaddr_in6*) res->ai_addr;
        if( inet_ntop(res->ai_family, &sin->sin6_addr, buf, sizeof(buf)) != NULL )
            cocos2d::log("Console: listening on  %s : %d", buf, ntohs(sin->sin6_port));
        else
            perror("inet_ntop");
    }
    freeaddrinfo(ressave);
    _listenfd = listenfd;
    _receiveThread = std::thread( std::bind( &FileServer::loopReceiveFile, this) );
    _writeThread = std::thread(std::bind(&FileServer::loopWriteFile, this));
    _responseThread = std::thread(std::bind(&FileServer::loopResponse, this));
    return true;	
}
    
void FileServer::stop()
{
    if(_running)
    {
        _endThread = true;
        _receiveThread.join();
        _writeThread.join();
        _responseThread.join();
    }
}

static bool CreateDir(const char *sPathName)
{
    char   DirName[256]={0};
    strcpy(DirName, sPathName);
    size_t i, len = strlen(DirName);
    if(DirName[len-1] != '/')
    {
        strcat(DirName, "/");
    }
    
    len = strlen(DirName);
    for(i = 1; i < len; i++)
    {
        if(DirName[i] == '/')
        {
            DirName[i] = 0;
            if(access(DirName, NULL) != 0)
            {
#ifdef _WIN32
                if(_mkdir(DirName/*, 0755*/) == -1)
#else
                if(mkdir(DirName, 0755) == -1)
#endif
                {
                    perror("mkdir error");
                    return false;
                }
            }  
            DirName[i] = '/';  
        }  
    }  
    
    return true;
}

static void recvBuf(int fd, char *pbuf, unsigned long bufsize)
{
    unsigned long leftLength = bufsize;
    while (leftLength != 0)
    {
        size_t recvlen = recv(fd, pbuf + bufsize - leftLength, leftLength ,0);
        if (recvlen <= 0)
        {
            usleep(1);
            continue;
        }
        leftLength -= recvlen;
    }
}

static void sendBuf(int fd, const char *pbuf, unsigned long bufsize)
{
    unsigned long leftLength = bufsize;
    while (leftLength != 0)
    {
        size_t sendlen = send(fd, pbuf + bufsize - leftLength, leftLength ,0);
        if (sendlen <= 0)
        {
            usleep(1);
            continue;
        }
        leftLength -= sendlen;
    }
}

void FileServer::loopReceiveFile()
{
    struct sockaddr client;
    socklen_t client_len;

    /* new client */
    client_len = sizeof(client);
    int fd = accept(_listenfd, (struct sockaddr *)&client, &client_len );
    if (_protoBuf == nullptr)
    {
        _protoBuf = new char[MAXPROTOLENGTH];
    }

    while(!_endThread) { 

        // recv start flag
        char startflag[13] = {0};
        recvBuf(fd, startflag, sizeof(startflag) - 1);
        if (strcmp(startflag, PROTO_START) != 0)
        {
            continue;
        }
    
        // recv proto num
        union 
        {
            char char_type[3];
            unsigned short uint16_type;
        }protonum;
        recvBuf(fd, protonum.char_type, sizeof(protonum.char_type) - 1);
        //recv protobuf length
        union 
        {
            char char_type[3];
            unsigned short uint16_type;
        }protolength;
        recvBuf(fd, protolength.char_type, sizeof(protolength.char_type) - 1);

        //recv variable length
        memset(_protoBuf, 0, MAXPROTOLENGTH);
        recvBuf(fd, _protoBuf, protolength.uint16_type);

        RecvBufStruct recvDataBuf;
        recvDataBuf.fd = fd;
        recvDataBuf.fileProto.ParseFromString(_protoBuf);
        if (1 == recvDataBuf.fileProto.package_seq())
        {
            _recvErrorFile = "";
        } else
        {
            // recv error
            if (_recvErrorFile == recvDataBuf.fileProto.file_name())
            {
                continue;
            }
        }
        unsigned long contentSize = recvDataBuf.fileProto.content_size();
        if (contentSize == 0)
        {
            recvDataBuf.contentBuf="";
            _recvBufListMutex.lock();
            _recvBufList.push_back(recvDataBuf);
            _recvBufListMutex.unlock();
        }else if(contentSize > 0)
        {  
            //recv body data
            Bytef *contentbuf = new Bytef[contentSize+1];
            memset(contentbuf, 0, contentSize+1);
            unsigned long recvTotalLen = contentSize;
            while (recvTotalLen != 0){
                unsigned long recvLen = MAXPROTOLENGTH;
                if(recvTotalLen < MAXPROTOLENGTH)
                    recvLen = recvTotalLen;
                memset(_protoBuf, 0, MAXPROTOLENGTH);
                unsigned long result = recv(fd, _protoBuf, recvLen,0);
                if (result <= 0)
                {
                    usleep(1);
                    continue;
                }
                memcpy(contentbuf + contentSize - recvTotalLen, _protoBuf, result);
                recvTotalLen -= result;
            }
        
            if (recvDataBuf.fileProto.compress_type() == runtime::FileSendProtos_CompressType::FileSendProtos_CompressType_ZIP){
                unsigned long uncompressSize = recvDataBuf.fileProto.uncompress_size();
                Bytef *buff = new Bytef[uncompressSize * sizeof(Bytef)];
                memset(buff, 0, uncompressSize * sizeof(Bytef));
                int err = ::uncompress(buff, &uncompressSize,contentbuf, contentSize * sizeof(Bytef));
                if (err != Z_OK){
                    CC_SAFE_DELETE_ARRAY(buff);
                    CC_SAFE_DELETE_ARRAY(contentbuf);
                    addResponse(recvDataBuf.fd, recvDataBuf.fileProto.file_name(), runtime::FileSendComplete::RESULTTYPE::FileSendComplete_RESULTTYPE_UNCOMPRESS_ERROR, err);
                    continue;
                }
                CC_SAFE_DELETE_ARRAY(contentbuf);
                contentbuf = buff;
                contentSize = uncompressSize; 
            }
            recvDataBuf.contentBuf.assign((const char*)contentbuf, contentSize);
            CC_SAFE_DELETE_ARRAY(contentbuf);
        
            _recvBufListMutex.lock();
            _recvBufList.push_back(recvDataBuf);
            _recvBufListMutex.unlock();
        }
    }
}
    
void FileServer::loopWriteFile()
{
     while(!_endThread)
     {
         _recvBufListMutex.lock();
         size_t recvSize = _recvBufList.size();
         _recvBufListMutex.unlock();
         if(0 == recvSize)
         {
             usleep(500);
             continue;
         }

         _recvBufListMutex.lock();
         RecvBufStruct recvDataBuf = _recvBufList.front();
         _recvBufList.pop_front();
         _recvBufListMutex.unlock();
         string filename = recvDataBuf.fileProto.file_name();
         string fullfilename = g_resourcePath;
         fullfilename += filename;
         _fileNameMutex.lock();
         _strFileName = filename;
         _fileNameMutex.unlock();
         //cocos2d::log("WriteFile:: fullfilename = %s",filename.c_str());
         CreateDir(fullfilename.substr(0, fullfilename.find_last_of("/")).c_str());

         FILE *fp= nullptr;
         if (1 == recvDataBuf.fileProto.package_seq())
         {
             _writeErrorFile ="";
             fp = fopen(fullfilename.c_str(), "wb");
         } else
         {
             if (_writeErrorFile == filename)
             {
                 continue;
             }
             fp=fopen(fullfilename.c_str(), "ab");
         }
         if (nullptr == fp)
         {
              addResponse(recvDataBuf.fd, filename, runtime::FileSendComplete::RESULTTYPE::FileSendComplete_RESULTTYPE_FOPEN_ERROR, errno);
              continue;
         }
         if (fp)
         {
             if (recvDataBuf.contentBuf.size() > 0 && 0 == fwrite(recvDataBuf.contentBuf.c_str(), sizeof(char), recvDataBuf.contentBuf.size(), fp))
             {
                 addResponse(recvDataBuf.fd, filename, runtime::FileSendComplete::RESULTTYPE::FileSendComplete_RESULTTYPE_FWRITE_ERROR, errno);
                 fclose(fp);
                 continue;
             }
             fclose(fp);
         }

         if (1 == recvDataBuf.fileProto.package_seq())
         {
             //record new file modify
             addResFileInfo(filename.c_str(), recvDataBuf.fileProto.modified_time());
             addResponse(recvDataBuf.fd, filename, runtime::FileSendComplete::RESULTTYPE::FileSendComplete_RESULTTYPE_SUCCESS, 0);
         }
     }
}

void FileServer::addResponse(int fd, string filename, int errortype, int errornum)
{
    switch (errortype)
    {
    case runtime::FileSendComplete::RESULTTYPE::FileSendComplete_RESULTTYPE_UNCOMPRESS_ERROR:
    case runtime::FileSendComplete::RESULTTYPE::FileSendComplete_RESULTTYPE_RECV_ERROR:
        _recvErrorFile = filename;
        break;
    case runtime::FileSendComplete::RESULTTYPE::FileSendComplete_RESULTTYPE_FOPEN_ERROR:
    case runtime::FileSendComplete::RESULTTYPE::FileSendComplete_RESULTTYPE_FWRITE_ERROR:
        _writeErrorFile = filename;
        break;
    default:
        break;
    }
  
    ResponseStruct responseBuf;
    responseBuf.fd = fd;
    responseBuf.fileResponseProto.set_file_name(filename.c_str());
    responseBuf.fileResponseProto.set_result((::runtime::FileSendComplete_RESULTTYPE)errortype);
    responseBuf.fileResponseProto.set_error_num(errornum);

    // push Response struct
    _responseBufListMutex.lock();
    _responseBufList.push_back(responseBuf);
    _responseBufListMutex.unlock();
}

void FileServer::loopResponse()
{
    while(!_endThread) {
        _responseBufListMutex.lock();
        size_t responseSize = _responseBufList.size();
        _responseBufListMutex.unlock();
        if(0 == responseSize)
        {
            usleep(500);
            /* error */
            continue;
        }

        _responseBufListMutex.lock();
        ResponseStruct responseBuf = _responseBufList.front();
        _responseBufList.pop_front();
        _responseBufListMutex.unlock();
        //send response
        string responseString;
        runtime::FileSendComplete  fileSendProtoComplete;
        fileSendProtoComplete.set_file_name(responseBuf.fileResponseProto.file_name());
        fileSendProtoComplete.set_result(responseBuf.fileResponseProto.result());
        fileSendProtoComplete.set_error_num(responseBuf.fileResponseProto.error_num());
        fileSendProtoComplete.SerializeToString(&responseString);
        char dataBuf[1024] = {0};
        struct ResponseHeaderStruct
        {
            char startFlag[12];
            unsigned short protoNum;
            unsigned short protoBufLen;
        };
        ResponseHeaderStruct responseHeader;
        strcpy(responseHeader.startFlag, PROTO_START);
        responseHeader.protoNum = PROTONUM::FILESENDCOMPLETE;
        responseHeader.protoBufLen = (unsigned short) responseString.size();
        memcpy(dataBuf, &responseHeader, sizeof(responseHeader));
        memcpy(dataBuf + sizeof(responseHeader), responseString.c_str(), responseString.size());
        
        sendBuf(responseBuf.fd, dataBuf, sizeof(responseHeader) + responseString.size());
        cocos2d::log("responseFile:%s,result:%d", fileSendProtoComplete.file_name().c_str(), fileSendProtoComplete.result());
    }
}

class ConnectWaitLayer: public Layer
{
private:
    Label* _labelUploadFile;
public:
    ConnectWaitLayer()
    {
#include "ResData.h"
        int designWidth = 1280;
        int designHeight = 800;
        Image* imagebg = new Image();
        
        if (ConfigParser::getInstance()->isLanscape())
        {
            imagebg->initWithImageData(__landscapePngData, sizeof(__landscapePngData));
            Director::getInstance()->getOpenGLView()->setDesignResolutionSize(designWidth, designHeight, ResolutionPolicy::EXACT_FIT);
        } else
        {
            imagebg->initWithImageData(__portraitPngData, sizeof(__portraitPngData));
            Director::getInstance()->getOpenGLView()->setDesignResolutionSize(designHeight, designWidth, ResolutionPolicy::EXACT_FIT);
        }
        Texture2D* texturebg = Director::getInstance()->getTextureCache()->addImage(imagebg, "play_background");
        auto background = Sprite::createWithTexture(texturebg);
        background->setAnchorPoint(Vec2(0.5, 0.5));
        background->setPosition(VisibleRect::center());
        addChild(background, 9000);

        // variable of below is"play" button position.
        int portraitX = 400;
        int portraitY = 500;
        int lanscaptX = 902;
        int lanscaptY = 400;
        Image* imageplay = new Image();
        imageplay->initWithImageData(__playEnablePngData, sizeof(__playEnablePngData));
        Texture2D* textureplay = Director::getInstance()->getTextureCache()->addImage(imageplay, "play_enable");
        auto playSprite = Sprite::createWithTexture(textureplay);
        addChild(playSprite, 9999);

        Image* imageShine = new Image();
        imageShine->initWithImageData(__shinePngData, sizeof(__shinePngData));
        Texture2D* textureShine = Director::getInstance()->getTextureCache()->addImage(imageShine, "shine");
        auto shineSprite = Sprite::createWithTexture(textureShine);
        shineSprite->setOpacity(0);
        Vector<FiniteTimeAction*> arrayOfActions;
        arrayOfActions.pushBack(DelayTime::create(0.4f));
        arrayOfActions.pushBack(FadeTo::create(0.8f, 200));
        arrayOfActions.pushBack(FadeTo::create(0.8f, 255));
        arrayOfActions.pushBack(FadeTo::create(0.8f, 200));
        arrayOfActions.pushBack(FadeTo::create(0.8f, 0));
        arrayOfActions.pushBack(DelayTime::create(0.4f));
        shineSprite->runAction(RepeatForever::create(Sequence::create(arrayOfActions)));
        addChild(shineSprite, 9998);

        string strip = getIPAddress();
        char szIPAddress[64] = {0};
        sprintf(szIPAddress, "IP: %s", strip.c_str());
        auto IPlabel = Label::createWithSystemFont(szIPAddress, "", 72);
        IPlabel->setAnchorPoint(Vec2(0, 0));
        int spaceSizex = 72;
        int spaceSizey = 200;
        IPlabel->setPosition(Point(VisibleRect::leftTop().x + spaceSizex, VisibleRect::top().y - spaceSizey));
        addChild(IPlabel, 9001);

        string transferTip = "waiting for file transfer ...";
        if (CC_PLATFORM_WIN32 == CC_TARGET_PLATFORM || CC_PLATFORM_MAC == CC_TARGET_PLATFORM)
        {
            transferTip = "waiting for debugger to connect ...";
        }

        char szVersion[256] = {0};
        sprintf(szVersion, "runtimeVersion:%s \nengineVersion:%s", getRuntimeVersion(), cocos2dVersion());
        Label* verLable = Label::createWithSystemFont(szVersion, "", 24);
        verLable->setAnchorPoint(Vec2(0, 0));
        int width = verLable->getBoundingBox().size.width;
        verLable->setPosition(Point(VisibleRect::right().x - width, VisibleRect::rightBottom().y));
        verLable->setAlignment(TextHAlignment::LEFT);
        addChild(verLable, 9002);
        _labelUploadFile = Label::createWithSystemFont(transferTip, "", 36);
        _labelUploadFile->setAnchorPoint(Vec2(0, 0));
        _labelUploadFile->setPosition(Point(VisibleRect::leftTop().x + spaceSizex, IPlabel->getPositionY()- spaceSizex));
        _labelUploadFile->setAlignment(TextHAlignment::LEFT);
        addChild(_labelUploadFile, 9003);

        if (ConfigParser::getInstance()->isLanscape())
        {
            playSprite->setPosition(lanscaptX, lanscaptY);
            shineSprite->setPosition(lanscaptX, lanscaptY);
        }
        else
        {
            playSprite->setPosition(portraitX, portraitY);
            shineSprite->setPosition(portraitX, portraitY);
        }

        auto listener = EventListenerTouchOneByOne::create();
        listener->onTouchBegan = [](Touch* touch, Event  *event)->bool{
            auto target = static_cast<Sprite*>(event->getCurrentTarget());
            Vec2 point = target->convertToNodeSpace(Director::getInstance()->convertToGL(touch->getLocationInView()));
            auto rect = Rect(0, 0, target->getContentSize().width, target->getContentSize().height);
            if (!rect.containsPoint(point)) return false;
            target->stopAllActions();
            target->runAction(Sequence::createWithTwoActions(ScaleBy::create(0.05f, 0.9f), ScaleTo::create(0.125f, 1)));
            return true;
        };
        listener->onTouchEnded = [](Touch* touch, Event  *event){
            auto target = static_cast<Sprite*>(event->getCurrentTarget());
            Vec2 point = target->convertToNodeSpace(Director::getInstance()->convertToGL(touch->getLocationInView()));
            auto rect = Rect(0, 0, target->getContentSize().width, target->getContentSize().height);
            if (!rect.containsPoint(point)) return;
            startScript("");
        };
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, playSprite);

        this->scheduleUpdate();
    }

    // clean up: ignore stdin, stdout and stderr
    void update(float fDelta)
    {  
        string transferTip = FileServer::getShareInstance()->getTransingFileName();
        if (transferTip.empty()){
            return;
        }
        _labelUploadFile->setString(transferTip);
    } 
};

class ConsoleCustomCommand
{
public:
    void init()
    {
        cocos2d::Console *_console = Director::getInstance()->getConsole();
        static struct Console::Command commands[] =
        {
            {"sendrequest","send command to runtime.Args[json format]",std::bind(&ConsoleCustomCommand::onSendCommand, this, std::placeholders::_1, std::placeholders::_2)},
        };
        for (int i=0;i< sizeof(commands)/sizeof(Console::Command);i++)
        {
            _console->addCommand(commands[i]);
        }
#if(CC_PLATFORM_MAC == CC_TARGET_PLATFORM || CC_PLATFORM_WIN32 == CC_TARGET_PLATFORM)
        _console->listenOnTCP(ConfigParser::getInstance()->getConsolePort());
#else
        _console->listenOnTCP(6010);
#endif
        _fileserver = nullptr;
        _fileserver= FileServer::getShareInstance();
#if(CC_PLATFORM_MAC == CC_TARGET_PLATFORM || CC_PLATFORM_WIN32 == CC_TARGET_PLATFORM)
        _fileserver->listenOnTCP(ConfigParser::getInstance()->getUploadPort());
#else
        _fileserver->listenOnTCP(6020);
#endif
        _fileserver->readResFileFinfo();
    }

    ~ConsoleCustomCommand()
    {
        Director::getInstance()->getConsole()->stop();
        if(_fileserver)
            _fileserver->stop();
    }

    void onSendCommand(int fd, const std::string &args)
    {
        Director::getInstance()->getScheduler()->performFunctionInCocosThread([=](){
            rapidjson::Document dArgParse;
            dArgParse.Parse<0>(args.c_str());
            if (dArgParse.HasMember("cmd"))
            {
                string strcmd = dArgParse["cmd"].GetString();
                
                rapidjson::Document dReplyParse;
                dReplyParse.SetObject();
                dReplyParse.AddMember("cmd",strcmd.c_str(),dReplyParse.GetAllocator());
                if (dArgParse.HasMember("seq"))
                {
                    dReplyParse.AddMember("seq",dArgParse["seq"],dReplyParse.GetAllocator());
                }
                
                if(strcmp(strcmd.c_str(), "start-logic") == 0)
                {
                    char szDebugArg[1024] = {0};
                    sprintf(szDebugArg, "require('debugger')(%s,'%s')",dArgParse["debugcfg"].GetString(), g_resourcePath.c_str());
                    startScript(szDebugArg);
                    dReplyParse.AddMember("code", 0, dReplyParse.GetAllocator());

                } else if(strcmp(strcmd.c_str(), "reload") == 0)
                {
                    if (dArgParse.HasMember("modulefiles"))
                    {
                        rapidjson::Value bodyvalue(rapidjson::kObjectType);
                        const rapidjson::Value& objectfiles = dArgParse["modulefiles"];
                        for (rapidjson::SizeType i = 0; i < objectfiles.Size(); i++)
                        {
                            if (!reloadScript(objectfiles[i].GetString()))
                            {
                                bodyvalue.AddMember(objectfiles[i].GetString(), 1, dReplyParse.GetAllocator());
                            }
                        }
                        if (0 == objectfiles.Size())
                        {
                            reloadScript("");
                        }
                        dReplyParse.AddMember("body", bodyvalue, dReplyParse.GetAllocator());
                    }
                    dReplyParse.AddMember("code", 0, dReplyParse.GetAllocator());
                } else if(strcmp(strcmd.c_str(), "getversion") == 0)
                {
                    rapidjson::Value bodyvalue(rapidjson::kObjectType);
                    bodyvalue.AddMember("version", getRuntimeVersion(), dReplyParse.GetAllocator());
                    dReplyParse.AddMember("body", bodyvalue, dReplyParse.GetAllocator());
                    dReplyParse.AddMember("code", 0, dReplyParse.GetAllocator());
                } else if(strcmp(strcmd.c_str(), "getfileinfo") == 0)
                {
                    rapidjson::Value bodyvalue(rapidjson::kObjectType);
                    if(_fileserver){
                        rapidjson::Document* filecfgjson = _fileserver->getFileCfgJson();
                        for (auto it=filecfgjson->MemberonBegin(); it != filecfgjson->MemberonEnd(); ++it)
                        {
                            bodyvalue.AddMember(it->name.GetString(), it->value.GetString(), dReplyParse.GetAllocator());
                        }
                    }
                    dReplyParse.AddMember("body",bodyvalue,dReplyParse.GetAllocator());
                    dReplyParse.AddMember("code",0,dReplyParse.GetAllocator());
                   
                } else if (strcmp(strcmd.c_str(), "getEntryfile") == 0)
                {
                    rapidjson::Value bodyvalue(rapidjson::kObjectType);
                    rapidjson::Value entryFileValue(rapidjson::kStringType);
                    entryFileValue.SetString(ConfigParser::getInstance()->getEntryFile().c_str(), dReplyParse.GetAllocator());
                    bodyvalue.AddMember("entryfile", entryFileValue, dReplyParse.GetAllocator());
                    dReplyParse.AddMember("body", bodyvalue,dReplyParse.GetAllocator());
                    dReplyParse.AddMember("code", 0, dReplyParse.GetAllocator());
                } else if(strcmp(strcmd.c_str(), "getIP") == 0)
                {
                    rapidjson::Value bodyvalue(rapidjson::kObjectType);
                    rapidjson::Value IPValue(rapidjson::kStringType);
                    IPValue.SetString(getIPAddress().c_str(), dReplyParse.GetAllocator());
                    bodyvalue.AddMember("IP", IPValue,dReplyParse.GetAllocator());
                    dReplyParse.AddMember("body", bodyvalue,dReplyParse.GetAllocator());
                    dReplyParse.AddMember("code", 0, dReplyParse.GetAllocator());

                } else if(strcmp(strcmd.c_str(), "remove") == 0)
                {
                    if (dArgParse.HasMember("files"))
                    {
                        rapidjson::Value bodyvalue(rapidjson::kObjectType);
                        const rapidjson::Value& objectfiles = dArgParse["files"];
                        const char* filename = NULL;
                        for (rapidjson::SizeType i = 0; i < objectfiles.Size(); i++)
                        {
                            filename = objectfiles[i].GetString();
                            
                            // remove file from disk
                            string filepath(g_resourcePath + "/" + filename);
                            if (FileUtils::getInstance()->isFileExist(filepath)) 
                            {
                                if(remove(filepath.c_str()) != 0) 
                                {
                                    // remove failed
                                    bodyvalue.AddMember(filename, 2, dReplyParse.GetAllocator());
                                }
                            } else
                            {
                                // file not exist
                                bodyvalue.AddMember(filename, 1, dReplyParse.GetAllocator());
                            }

                            if (_fileserver)
                            {
                                // file remove success, remove it from record
                                if (! FileUtils::getInstance()->isFileExist(filepath))
                                    _fileserver->removeResFileInfo(filename);
                            }
                        }

                        dReplyParse.AddMember("body", bodyvalue, dReplyParse.GetAllocator());
                    }

                    dReplyParse.AddMember("code",0,dReplyParse.GetAllocator());
                }else if(strcmp(strcmd.c_str(),"shutdownapp")==0)
                {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
                    extern void shutDownApp();
                    shutDownApp();
#else
                    exit(0);
#endif	
                } else if(strcmp(strcmd.c_str(),"getplatform") == 0)
                {
                    string platform="UNKNOW";
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
                    platform = "WIN32";
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
                    platform = "MAC";
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
                    platform = "IOS";
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
                    platform = "ANDROID";
#endif
                    rapidjson::Value bodyvalue(rapidjson::kObjectType);
                    rapidjson::Value platformValue(rapidjson::kStringType);
                    platformValue.SetString(platform.c_str(), dReplyParse.GetAllocator());
                    bodyvalue.AddMember("platform", platformValue, dReplyParse.GetAllocator());
                    dReplyParse.AddMember("body", bodyvalue, dReplyParse.GetAllocator());
                    dReplyParse.AddMember("code", 0, dReplyParse.GetAllocator());
                }
                
                rapidjson::StringBuffer buffer;
                rapidjson::Writer< rapidjson::StringBuffer > writer(buffer);
                dReplyParse.Accept(writer);
                string msgContent = buffer.GetString();
                char msgLength[64] = {0x1, 0};
                sprintf(msgLength + 1, "%d:", msgContent.size());
                
                string msg(msgLength + msgContent);
                
                sendBuf(fd, msg.c_str(), msg.size());
            }
        });
    }
private:
    FileServer* _fileserver;
};

int lua_cocos2dx_runtime_addSearchPath(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FileUtils* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FileUtils",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::FileUtils*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_FileUtils_addSearchPath'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        std::string originPath = arg0;
        if (!FileUtils::getInstance()->isAbsolutePath(originPath))
            arg0 = g_resourcePath + originPath;
        cobj->addSearchPath(arg0);

        if (!FileUtils::getInstance()->isAbsolutePath(originPath))
#if(CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
            cobj->addSearchPath(g_projectPath + originPath);
#endif
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            cobj->addSearchPath(originPath);
#endif
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "addSearchPath",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_FileUtils_addSearchPath'.",&tolua_err);
#endif

    return 0;
}

int lua_cocos2dx_runtime_setSearchPaths(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FileUtils* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FileUtils",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::FileUtils*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_runtime_setSearchPaths'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::vector<std::string> vecPaths;

        ok &= luaval_to_std_vector_string(tolua_S, 2,&vecPaths);
        if(!ok)
            return 0;
        std::vector<std::string> originPath; // for IOS platform.
        std::vector<std::string> projPath; // for Desktop platform.
        for (int i = 0; i < vecPaths.size(); i++)
        {
            if (!FileUtils::getInstance()->isAbsolutePath(vecPaths[i]))
            {
                originPath.push_back(vecPaths[i]); // for IOS platform.
                projPath.push_back(g_projectPath+vecPaths[i]); //for Desktop platform.
                vecPaths[i] = g_resourcePath + vecPaths[i];
            }
        }
#if(CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
        vecPaths.insert(vecPaths.end(),projPath.begin(),projPath.end());
#endif
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        vecPaths.insert(vecPaths.end(),originPath.begin(),originPath.end());
#endif
        cobj->setSearchPaths(vecPaths);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setSearchPaths",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_runtime_setSearchPaths'.",&tolua_err);
#endif

    return 0;
}

static void register_runtime_override_function(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.FileUtils");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1)){
        tolua_function(tolua_S,"addSearchPath",lua_cocos2dx_runtime_addSearchPath);
        tolua_function(tolua_S,"setSearchPaths",lua_cocos2dx_runtime_setSearchPaths);
    }
    lua_pop(tolua_S, 1);
}

void initRuntime()
{
    vector<string> searchPathArray = FileUtils::getInstance()->getSearchPaths();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    // add peoject's root directory to search path
    if (g_projectPath.empty())
    {
        extern std::string getCurAppPath();
        string appPath = getCurAppPath();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
        appPath.append("/../../");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
        appPath.append("/../../../");
#endif
        appPath = replaceAll(appPath, "\\", "/");
        g_projectPath = appPath;
    }    
    searchPathArray.insert(searchPathArray.begin(), g_projectPath);
#endif

    // add writable path to search path
    g_resourcePath = FileUtils::getInstance()->getWritablePath();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    std::string getCurAppName(void);
    g_resourcePath += getCurAppName();
    g_resourcePath += "/";
#endif

    g_resourcePath += "debugruntime/";
    
    g_resourcePath = replaceAll(g_resourcePath, "\\", "/");
    if (g_resourcePath.at(g_resourcePath.length() - 1) != '/'){
        g_resourcePath.append("/");
    }
    
    searchPathArray.insert(searchPathArray.begin(), g_resourcePath);
    FileUtils::getInstance()->setSearchPaths(searchPathArray);

    auto engine = LuaEngine::getInstance();
    ScriptEngineManager::getInstance()->setScriptEngine(engine);
    register_runtime_override_function(engine->getLuaStack()->getLuaState());

    static ConsoleCustomCommand *g_customCommand;
    g_customCommand = new ConsoleCustomCommand();
    g_customCommand->init();
}

void startRuntime()
{
    auto scene = Scene::create();
    auto connectLayer = new ConnectWaitLayer();
    connectLayer->autorelease();
    auto director = Director::getInstance();
    scene->addChild(connectLayer);
    director->runWithScene(scene);
}
