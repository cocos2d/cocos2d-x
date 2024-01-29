/****************************************************************************
Copyright (c) 2013 cocos2d-x.org
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

#include "FileServer.h"
#include "Runtime.h"
#include "zlib.h"
#include "ConfigParser.h"

// header files for directory operation
#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#endif

USING_NS_CC;

//1M size
#define MAXPROTOLENGTH 1048576

#define PROTO_START "RuntimeSend:"

FileServer* FileServer::s_sharedFileServer = nullptr;
FileServer* FileServer::getShareInstance()
{
	if (s_sharedFileServer == nullptr)
	{
		s_sharedFileServer = new FileServer;
	}
	return s_sharedFileServer;
}

void FileServer::purge()
{
	CC_SAFE_DELETE(s_sharedFileServer);
}

void FileServer::readResFileFinfo()
{
    std::string filecfg = _writePath + "/fileinfo_debug.json";
    FILE * pFile = fopen (filecfg.c_str() , "r");
    if(pFile)
    {
        char buffer[65536];
        rapidjson::FileReadStream inputStream(pFile, buffer, sizeof(buffer));
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
        std::string filecfg = _writePath + "/fileinfo_debug.json";
        FILE * pFile = fopen(filecfg.c_str(), "w");
        if (!pFile) return ;
        fwrite(str, sizeof(char), strlen(str), pFile);
        fclose(pFile);
    },this, 5.0f, false, "fileinfo");
}

void FileServer::addResFileInfo(const char* filename, uint64_t u64)
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
    _filecfgjson.AddMember(filenameValue, filetimeValue, _filecfgjson.GetAllocator());
}

void FileServer::removeResFileInfo(const char *filename)
{
    if (_filecfgjson.HasMember(filename)) {
        _filecfgjson.RemoveMember(filename);
    }
}

std::string FileServer::getTransingFileName()
{
    _fileNameMutex.lock();
    std::string filename = _strFileName;
    _fileNameMutex.unlock();
    return filename;
}

void FileServer::setTransingFileName(const std::string &filename)
{
    _fileNameMutex.lock();
    _strFileName = filename;
    _fileNameMutex.unlock();
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
        
        auto address = ConfigParser::getInstance()->getBindAddress();

        // bind address
        if (address.length() > 0)
        {
            if (res->ai_family == AF_INET)
            {
                struct sockaddr_in *sin = (struct sockaddr_in*) res->ai_addr;
                inet_pton(res->ai_family, address.c_str(), (void*)&sin->sin_addr);
            }
            else if (res->ai_family == AF_INET6)
            {
                struct sockaddr_in6 *sin = (struct sockaddr_in6*) res->ai_addr;
                inet_pton(res->ai_family, address.c_str(), (void*)&sin->sin6_addr);
            }
        }
        
        if (::bind(listenfd, res->ai_addr, res->ai_addrlen) == 0)
            break;          /* success */
   
		/* bind error, close and try next one */
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		closesocket(listenfd);
#else
		close(listenfd);
#endif
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
    _receiveThread = std::thread(std::bind( &FileServer::loopReceiveFile, this));
    _writeThread = std::thread(std::bind(&FileServer::loopWriteFile, this));
    _responseThread = std::thread(std::bind(&FileServer::loopResponse, this));
    return true;
}

void FileServer::stop()
{
	_receiveEndThread = true;
	_writeEndThread = true;
	_responseEndThread = true;

    if (_receiveRunning && _receiveThread.joinable())
    {
        _receiveThread.join();
    }

    if (_writeRunning && _writeThread.joinable())
	{
		_writeThread.join();
	}

    if (_responseRunning && _responseThread.joinable())
	{
		_responseThread.join();
	}
}

FileServer::FileServer() :
_listenfd(-1),
_receiveRunning(false),
_receiveEndThread(false),
_writeRunning(false),
_writeEndThread(false),
_responseRunning(false),
_responseEndThread(false)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    // need to be opened by Code IDE
    _isUsingWritePath = false;
#else
    _isUsingWritePath = true;
#endif
    
    _writePath = FileUtils::getInstance()->getWritablePath();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
#include "Widget_mac.h"
    _writePath += getCurAppName();
    _writePath += "/";
#endif
    
    _writePath += "debugruntime/";
    
    _writePath = replaceAll(_writePath, "\\", "/");
    if (_writePath.at(_writePath.length() - 1) != '/'){
        _writePath.append("/");
    }
}

FileServer::~FileServer()
{
	stop();
}

void FileServer::loopReceiveFile()
{
    struct sockaddr client;
    socklen_t client_len;

    /* new client */
    client_len = sizeof(client);
    int fd = accept(_listenfd, (struct sockaddr *)&client, &client_len );
    char *protoBuf = new char[MAXPROTOLENGTH];

    while(!_receiveEndThread) { 

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
        memset(protoBuf, 0, MAXPROTOLENGTH);
        recvBuf(fd, protoBuf, protolength.uint16_type);

        RecvBufStruct recvDataBuf;
        recvDataBuf.fd = fd;
        recvDataBuf.fileProto.ParseFromString(protoBuf);
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
                memset(protoBuf, 0, MAXPROTOLENGTH);
                unsigned long result = recv(fd, protoBuf, recvLen,0);
                if (result <= 0)
                {
                    usleep(1);
                    continue;
                }
                memcpy(contentbuf + contentSize - recvTotalLen, protoBuf, result);
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

	_receiveRunning = false;

	CC_SAFE_DELETE_ARRAY(protoBuf);
}

void FileServer::loopWriteFile()
{
	_writeRunning = true;
    while(!_writeEndThread)
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
        std::string filename = recvDataBuf.fileProto.file_name();
        std::string fullfilename = _writePath;
        fullfilename += filename;
        _fileNameMutex.lock();
        _strFileName = filename;
        _fileNameMutex.unlock();
        //cocos2d::log("WriteFile:: fullfilename = %s",filename.c_str());
        createDir(fullfilename.substr(0, fullfilename.find_last_of("/")).c_str());
        
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

	_writeRunning = false;
}

void FileServer::addResponse(int fd, std::string filename, int errortype, int errornum)
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
	_responseRunning = true;
    while(!_responseEndThread) {
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
        std::string responseString;
        runtime::FileSendComplete  fileSendProtoComplete;
        fileSendProtoComplete.set_file_name(responseBuf.fileResponseProto.file_name());
        fileSendProtoComplete.set_result(responseBuf.fileResponseProto.result());
        fileSendProtoComplete.set_error_num(responseBuf.fileResponseProto.error_num());
        fileSendProtoComplete.SerializeToString(&responseString);
        char dataBuf[1024] = {0};
        struct ResponseHeaderStruct
        {
            char startFlag[13]; // needs to store PROTO_START, which is 12+NULL long
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

	_responseRunning = false;
}

bool createDir(const char *sPathName)
{
    char   DirName[256]={0};
    strcpy(DirName, sPathName);
    size_t i, len = strlen(DirName);
    if(DirName[len - 1] != '/')
    {
        strcat(DirName, "/");
    }
    
    len = strlen(DirName);
    for(i = 1; i < len; i++)
    {
        if(DirName[i] == '/')
        {
            DirName[i] = 0;
#ifdef _WIN32
            if(_access(DirName, 0) != 0)
            {
                if(_mkdir(DirName/*, 0755*/) == -1)
#else
			if (access(DirName, 0) != 0)
			{
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
