/****************************************************************************
 Copyright (c) 2013-2014 Chukong Technologies Inc.
 
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
#include "lua_xml_http_request.h"
#include <string>
#include "tolua_fix.h"
#include "CCLuaStack.h"
#include "CCLuaValue.h"
#include "CCLuaEngine.h"
#include "LuaScriptHandlerMgr.h"


using namespace cocos2d;
using namespace std;

LuaMinXmlHttpRequest::LuaMinXmlHttpRequest()
:
_url(""),
_meth(""),
_type(""),
_dataSize(0),
_readyState(UNSENT),
_status(0),
_statusText(""),
_responseType(ResponseType::STRING),
_timeout(0),
_isAsync(false),
_isNetwork(true),
_withCredentialsValue(true),
_errorFlag(false),
_isAborted(false)
{
    _httpHeader.clear();
    _requestHeader.clear();
    _httpRequest = new (std::nothrow)cocos2d::network::HttpRequest();
}

LuaMinXmlHttpRequest::~LuaMinXmlHttpRequest()
{
    _httpHeader.clear();
    _requestHeader.clear();
    CC_SAFE_RELEASE_NULL(_httpRequest);
}

/**
 *  @brief Implementation for header retrieving.
 *  @param header
 */
void LuaMinXmlHttpRequest::_gotHeader(string header)
{
	// Get Header and Set StatusText
    // Split String into Tokens
    char * cstr = new char [header.length()+1];
    
    // check for colon.
    size_t found_header_field = header.find_first_of(":");
    
    if (found_header_field != std::string::npos)
    {
        // Found a header field.
        string http_field;
        string http_value;
        
        http_field = header.substr(0,found_header_field);
        http_value = header.substr(found_header_field+1, header.length());
        
        // Get rid of all \n
        if (!http_value.empty() && http_value[http_value.size() - 1] == '\n') {
        	http_value.erase(http_value.size() - 1);
        }
        
        _httpHeader[http_field] = http_value;
        
    }
    else
    {
        // Seems like we have the response Code! Parse it and check for it.
        char * pch;
        strcpy(cstr, header.c_str());
        
        pch = strtok(cstr," ");
        while (pch != NULL)
        {
            
            stringstream ss;
            string val;
            
            ss << pch;
            val = ss.str();
            size_t found_http = val.find("HTTP");
            
            // Check for HTTP Header to set statusText
            if (found_http != std::string::npos) {
                
                stringstream mystream;
                
                // Get Response Status
                pch = strtok (NULL, " ");
                mystream << pch;
                
                pch = strtok (NULL, "\n");
                mystream << " " << pch;
                
                _statusText = mystream.str();
                
            }
            
            pch = strtok (NULL, " ");
        }
    }
    
    CC_SAFE_DELETE_ARRAY(cstr);
}

/**
 *  @brief Set Request header for next call.
 *  @param field  Name of the Header to be set.
 *  @param value  Value of the Headerfield
 */
void LuaMinXmlHttpRequest::setRequestHeader(const char* field, const char* value)
{
    stringstream header_s;
    stringstream value_s;
    string header;
    
    map<string, string>::iterator iter = _requestHeader.find(field);
    
    // Concatenate values when header exists.
    if (iter != _requestHeader.end())
    {
        value_s << iter->second << "," << value;
    }
    else
    {
        value_s << value;
    }
    
    _requestHeader[field] = value_s.str();
}

/**
 * @brief  If headers has been set, pass them to curl.
 *
 */
void LuaMinXmlHttpRequest::_setHttpRequestHeader()
{
    std::vector<string> header;
    
    for (auto it = _requestHeader.begin(); it != _requestHeader.end(); ++it)
    {
        const char* first = it->first.c_str();
        const char* second = it->second.c_str();
        size_t len = sizeof(char) * (strlen(first) + 3 + strlen(second));
        char* test = (char*) malloc(len);
        memset(test, 0,len);
        
        strcpy(test, first);
        strcpy(test + strlen(first) , ": ");
        strcpy(test + strlen(first) + 2, second);
        
        header.push_back(test);
        
        free(test);
        
    }
    
    if (!header.empty())
    {
        _httpRequest->setHeaders(header);
    }
    
}

/**
 * @brief   Send out request and fire callback when done.
 */
void LuaMinXmlHttpRequest::_sendRequest()
{
    _httpRequest->setResponseCallback([this](cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response){
        if (_isAborted)
            return ;
        
        if (0 != strlen(response->getHttpRequest()->getTag()))
        {
            CCLOG("%s completed", response->getHttpRequest()->getTag());
        }
        
        long statusCode = response->getResponseCode();
        
        if (!response->isSucceed())
        {
            CCLOG("Response failed, error buffer: %s", response->getErrorBuffer());
            if(statusCode == 0)
            {
                _errorFlag = true;
                _status    = 0;
                _statusText.clear();
            }
            // TODO: call back lua function
            int handler = cocos2d::ScriptHandlerMgr::getInstance()->getObjectHandler((void*)this, cocos2d::ScriptHandlerMgr::HandlerType::XMLHTTPREQUEST_READY_STATE_CHANGE );
            
            if (0 != handler)
            {
                CCLOG("come in handler, handler is %d", handler);
                cocos2d::CommonScriptData data(handler,"");
                cocos2d::ScriptEvent event(cocos2d::ScriptEventType::kCommonEvent,(void*)&data);
                cocos2d::ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
            }
            return;
        }
        
        // set header
        std::vector<char> *headers = response->getResponseHeader();
        
        std::string header(headers->begin(), headers->end());
        std::istringstream stream(header);
        std::string line;
        while(std::getline(stream, line)) {
            _gotHeader(line);
        }
        
        /** get the response data **/
        std::vector<char> *buffer = response->getResponseData();
        
        if (statusCode == 200)
        {
            //Succeeded
            _status = 200;
            _readyState = DONE;
            _data.assign(buffer->begin(), buffer->end());
            _dataSize = buffer->size();
        }
        else
        {
            _status = 0;
        }
        
        // TODO: call back lua function
        int handler = cocos2d::ScriptHandlerMgr::getInstance()->getObjectHandler((void*)this, cocos2d::ScriptHandlerMgr::HandlerType::XMLHTTPREQUEST_READY_STATE_CHANGE );
        
        if (0 != handler)
        {
            cocos2d::CommonScriptData data(handler,"");
            cocos2d::ScriptEvent event(cocos2d::ScriptEventType::kCommonEvent,(void*)&data);
            cocos2d::ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
        }
        release();
    });
    network::HttpClient::getInstance()->sendImmediate(_httpRequest);
    retain();
}

void LuaMinXmlHttpRequest::getByteData(unsigned char* byteData)
{
    memcpy((char*)byteData, _data.c_str(), _dataSize);
}

/* function to regType */
static void lua_reg_xml_http_request(lua_State* L)
{
    tolua_usertype(L, "cc.XMLHttpRequest");
}

static int lua_collect_xml_http_request (lua_State* L)
{
    LuaMinXmlHttpRequest* self = (LuaMinXmlHttpRequest*) tolua_tousertype(L,1,0);
    self->release();
    return 0;
}

static int lua_cocos2dx_XMLHttpRequest_constructor(lua_State* L)
{
    int argc = 0;
    LuaMinXmlHttpRequest* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    argc = lua_gettop(L)-1;
    if (argc == 0)
    {
        self = new (std::nothrow) LuaMinXmlHttpRequest();
        tolua_pushusertype(L, (void*)self, "cc.XMLHttpRequest");
        tolua_register_gc(L, lua_gettop(L));
        return 1;
    }
    
    luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "XMLHttpRequest",argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_XMLHttpRequest_constructor'.",&tolua_err);
    return 0;
#endif
}

static int lua_get_XMLHttpRequest_responseType(lua_State* L)
{    
    LuaMinXmlHttpRequest* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"cc.XMLHttpRequest",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = (LuaMinXmlHttpRequest*)  tolua_tousertype(L,1,0);
#if COCOS2D_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(L,"invalid 'self' in function 'lua_get_XMLHttpRequest_responseType'\n", nullptr);
		return 0;
    }
#endif
    
    tolua_pushnumber(L, (lua_Number)self->getResponseType());
    return 1;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_get_XMLHttpRequest_responseType'.",&tolua_err);
    return 0;
#endif
}

static int lua_set_XMLHttpRequest_responseType(lua_State* L)
{
    int argc = 0;
    LuaMinXmlHttpRequest* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"cc.XMLHttpRequest",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = (LuaMinXmlHttpRequest*)  tolua_tousertype(L,1,0);
#if COCOS2D_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(L,"invalid 'self' in function 'lua_set_XMLHttpRequest_responseType'\n", nullptr);
		return 0;
    }
#endif
    
    argc = lua_gettop(L) - 1;
    
    if (1 == argc)
    {        
#if COCOS2D_DEBUG >= 1
        if (!tolua_isnumber(L, 2, 0, &tolua_err))
            goto tolua_lerror;
#endif
        int responseType = (int)tolua_tonumber(L,2,0);
        
        self->setResponseType((LuaMinXmlHttpRequest::ResponseType)responseType);
        
        return 0;
    }
    
    luaL_error(L, "'setResponseType' function of XMLHttpRequest wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_set_XMLHttpRequest_responseType'.",&tolua_err);
    return 0;
#endif
}

static int lua_get_XMLHttpRequest_withCredentials(lua_State* L)
{
    LuaMinXmlHttpRequest* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"cc.XMLHttpRequest",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = (LuaMinXmlHttpRequest*)  tolua_tousertype(L,1,0);
#if COCOS2D_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(L,"invalid 'self' in function 'lua_get_XMLHttpRequest_withCredentials'\n", nullptr);
		return 0;
    }
#endif
    
    tolua_pushboolean(L, self->getWithCredentialsValue());
    return 1;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_get_XMLHttpRequest_withCredentials'.",&tolua_err);
    return 0;
#endif
}

static int lua_set_XMLHttpRequest_withCredentials(lua_State* L)
{
    int argc = 0;
    LuaMinXmlHttpRequest* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"cc.XMLHttpRequest",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = (LuaMinXmlHttpRequest*)  tolua_tousertype(L,1,0);
#if COCOS2D_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(L,"invalid 'self' in function 'lua_set_XMLHttpRequest_withCredentials'\n", nullptr);
		return 0;
    }
#endif
    
    argc = lua_gettop(L) - 1;
    
    if (1 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!tolua_isboolean(L, 2, 0, &tolua_err))
            goto tolua_lerror;
#endif
        self->setWithCredentialsValue((bool)tolua_toboolean(L, 2, 0));
        return 0;
    }
    
    luaL_error(L, "'setWithCredentials' function of XMLHttpRequest wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_set_XMLHttpRequest_withCredentials'.",&tolua_err);
    return 0;
#endif
}

static int lua_get_XMLHttpRequest_timeout(lua_State* L)
{
    LuaMinXmlHttpRequest* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"cc.XMLHttpRequest",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = (LuaMinXmlHttpRequest*)  tolua_tousertype(L,1,0);
#if COCOS2D_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(L,"invalid 'self' in function 'lua_get_XMLHttpRequest_timeout'\n", nullptr);
		return 0;
    }
#endif
    
    tolua_pushnumber(L, (lua_Number)self->getTimeout());
    return 1;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_get_XMLHttpRequest_timeout'.",&tolua_err);
    return 0;
#endif
}

static int lua_set_XMLHttpRequest_timeout(lua_State* L)
{
    int argc = 0;
    LuaMinXmlHttpRequest* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"cc.XMLHttpRequest",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = (LuaMinXmlHttpRequest*)  tolua_tousertype(L,1,0);
#if COCOS2D_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(L,"invalid 'self' in function 'lua_set_XMLHttpRequest_timeout'\n", nullptr);
		return 0;
    }
#endif
    
    argc = lua_gettop(L) - 1;
    
    if (1 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!tolua_isnumber(L, 2, 0, &tolua_err))
            goto tolua_lerror;
#endif
        self->setTimeout((unsigned)tolua_tonumber(L, 2, 0));
        return 0;
    }
    
    luaL_error(L, "'setTimeout' function of XMLHttpRequest wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_set_XMLHttpRequest_timeout'.",&tolua_err);
    return 0;
#endif
}

static int lua_get_XMLHttpRequest_readyState(lua_State* L)
{
    LuaMinXmlHttpRequest* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"cc.XMLHttpRequest",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = (LuaMinXmlHttpRequest*)  tolua_tousertype(L,1,0);
#if COCOS2D_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(L,"invalid 'self' in function 'lua_get_XMLHttpRequest_readyState'\n", nullptr);
		return 0;
    }
#endif
    
    lua_pushinteger(L, (lua_Integer)self->getReadyState());
    
    return 1;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_get_XMLHttpRequest_readyState'.",&tolua_err);
    return 0;
#endif
}

static int lua_get_XMLHttpRequest_status(lua_State* L)
{
    LuaMinXmlHttpRequest* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"cc.XMLHttpRequest",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = (LuaMinXmlHttpRequest*)  tolua_tousertype(L,1,0);
#if COCOS2D_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(L,"invalid 'self' in function 'lua_get_XMLHttpRequest_status'\n", nullptr);
		return 0;
    }
#endif
    
    lua_pushinteger(L, (lua_Integer)self->getStatus());
    
    return 1;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_get_XMLHttpRequest_status'.",&tolua_err);
    return 0;
#endif
}

static int lua_get_XMLHttpRequest_statusText(lua_State* L)
{
    LuaMinXmlHttpRequest* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"cc.XMLHttpRequest",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = (LuaMinXmlHttpRequest*)  tolua_tousertype(L,1,0);
#if COCOS2D_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(L,"invalid 'self' in function 'lua_get_XMLHttpRequest_statusText'\n", nullptr);
		return 0;
    }
#endif
    
    lua_pushstring(L, self->getStatusText().c_str());
    
    return 1;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_get_XMLHttpRequest_statusText'.",&tolua_err);
    return 0;
#endif
}

static int lua_get_XMLHttpRequest_responseText(lua_State* L)
{
    LuaMinXmlHttpRequest* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"cc.XMLHttpRequest",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = (LuaMinXmlHttpRequest*)  tolua_tousertype(L,1,0);
#if COCOS2D_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(L,"invalid 'self' in function 'lua_get_XMLHttpRequest_responseText'\n", nullptr);
		return 0;
    }
#endif
    lua_pushlstring(L, self->getDataStr().c_str(), self->getDataSize());
    return 1;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_get_XMLHttpRequest_responseText'.",&tolua_err);
    return 0;
#endif
}

static int lua_get_XMLHttpRequest_response(lua_State* L)
{
    LuaMinXmlHttpRequest* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"cc.XMLHttpRequest",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = (LuaMinXmlHttpRequest*)  tolua_tousertype(L,1,0);
#if COCOS2D_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(L,"invalid 'self' in function 'lua_get_XMLHttpRequest_response'\n", nullptr);
		return 0;
    }
#endif
    
    if (self->getResponseType() == LuaMinXmlHttpRequest::ResponseType::JSON)
    {
        if (self->getReadyState() != LuaMinXmlHttpRequest::DONE || self->getErrorFlag())
            return 0;
        
        lua_pushlstring(L, self->getDataStr().c_str(), self->getDataSize());
        return 1;
    }
    else if(self->getResponseType() == LuaMinXmlHttpRequest::ResponseType::ARRAY_BUFFER)
    {
        if (self->getReadyState() != LuaMinXmlHttpRequest::DONE || self->getErrorFlag())
            return 0;
        
        LuaStack *pStack = LuaEngine::getInstance()->getLuaStack();
        if (NULL == pStack) {
            return 0;
        }
        
        lua_State *tolua_s = pStack->getLuaState();
        if (NULL == tolua_s) {
            return 0;
        }
        
        LuaValueArray array;
        
        uint8_t* tmpData = new uint8_t[self->getDataSize()];
        if (nullptr == tmpData)
        {
            return 0;
        }
        
        self->getByteData(tmpData);
        
        for (int i = 0 ; i < self->getDataSize(); i++)
        {
            LuaValue value = LuaValue::intValue(tmpData[i]);
            array.push_back(value);
        }
        
        pStack->pushLuaValueArray(array);
        
        CC_SAFE_DELETE_ARRAY(tmpData);
        return 1;
    }
    else
    {
        lua_pushlstring(L, self->getDataStr().c_str(), self->getDataSize());
        return 1;
    }
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_get_XMLHttpRequest_response'.",&tolua_err);
    return 0;
#endif
}

static int lua_cocos2dx_XMLHttpRequest_open(lua_State* L)
{
    int argc = 0;
    LuaMinXmlHttpRequest* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"cc.XMLHttpRequest",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = (LuaMinXmlHttpRequest*)  tolua_tousertype(L,1,0);
#if COCOS2D_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_XMLHttpRequest_open'\n", nullptr);
		return 0;
    }
#endif
    
    argc = lua_gettop(L) - 1;
    
    if ( argc >= 2)
    {
#if COCOS2D_DEBUG >= 1
        if (!tolua_isstring(L, 2, 0, &tolua_err) ||
            !tolua_isstring(L, 3, 0, &tolua_err))
            goto tolua_lerror;
#endif
        
        std::string method = tolua_tostring(L, 2, "");
        std::string url    = tolua_tostring(L, 3, "");
        bool async = true;
        if (argc > 2)
        {
#if COCOS2D_DEBUG >= 1
            if (!tolua_isboolean(L, 4, 0, &tolua_err) )
                goto tolua_lerror;
#endif
            async = tolua_toboolean(L, 4, 0);
        }
        
        self->setUrl(url);
        self->setMethod(method);
        self->setReadyState(1);
        self->setAsync(async);
        
        if (url.length() > 5 && url.compare(url.length() - 5, 5, ".json") == 0 )
        {
            self->setResponseType(LuaMinXmlHttpRequest::ResponseType::JSON);
        }
        
        if (nullptr != self->getHttpRequest())
        {
            if (method.compare("post") == 0 || method.compare("POST") == 0)
            {
                self->getHttpRequest()->setRequestType(network::HttpRequest::Type::POST);
            }
            else if(method.compare("get") == 0 || method.compare("GET") == 0)
            {
                self->getHttpRequest()->setRequestType(network::HttpRequest::Type::GET);
            }
            else if(method.compare("put") == 0 || method.compare("PUT") == 0)
            {
                self->getHttpRequest()->setRequestType(network::HttpRequest::Type::PUT);
            }
            else if(method.compare("delete") == 0 || method.compare("DELETE") == 0)
            {
                self->getHttpRequest()->setRequestType(network::HttpRequest::Type::DELETE);
            }
            else
            {
                self->getHttpRequest()->setRequestType(network::HttpRequest::Type::UNKNOWN);
            }
            
            self->getHttpRequest()->setUrl(url.c_str());
            
        }
        
        self->setIsNetWork(true);
        self->setReadyState(LuaMinXmlHttpRequest::OPENED);
        self->setStatus(0);
        self->setAborted(false);

        return 0;
    }
    
    luaL_error(L, "'open' function of XMLHttpRequest wrong number of arguments: %d, was expecting %d\n", argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_XMLHttpRequest_open'.",&tolua_err);
    return 0;
#endif
}

static int lua_cocos2dx_XMLHttpRequest_send(lua_State* L)
{
    int argc = 0;
    LuaMinXmlHttpRequest* self = nullptr;
    //std::string data = "";
    const char* data = NULL;
    size_t size = 0;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"cc.XMLHttpRequest",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = (LuaMinXmlHttpRequest*)  tolua_tousertype(L,1,0);
#if COCOS2D_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_XMLHttpRequest_send'\n", nullptr);
		return 0;
    }
#endif
    self->getHttpHeader().clear();
    self->setErrorFlag(false);
    
    argc = lua_gettop(L) - 1;

    if ( 1 == argc )
    {
#if COCOS2D_DEBUG >= 1
        if (!tolua_isstring(L, 2, 0, &tolua_err))
            goto tolua_lerror;
#endif
        //data = tolua_tostring(L, 2, "");
        data = (const char*) lua_tolstring(L, 2, &size);
    }
    
    if (size > 0 &&
        (self->getMethod().compare("post") == 0 || self->getMethod().compare("POST") == 0
         || self->getMethod().compare("put") == 0 || self->getMethod().compare("PUT") == 0 )&&
        nullptr != self->getHttpRequest())
    {
        self->getHttpRequest()->setRequestData(data,size);
    }
    
    self->_setHttpRequestHeader();
    self->_sendRequest();
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_XMLHttpRequest_send'.",&tolua_err);
    return 0;
#endif
}

/**
 * @brief abort function Placeholder!
 */
static int lua_cocos2dx_XMLHttpRequest_abort(lua_State* L)
{
    int argc = 0;
    LuaMinXmlHttpRequest* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"cc.XMLHttpRequest",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = (LuaMinXmlHttpRequest*)  tolua_tousertype(L,1,0);
#if COCOS2D_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_XMLHttpRequest_send'\n", nullptr);
		return 0;
    }
#endif
    
    argc = lua_gettop(L) - 1;
    
    if ( 0 == argc )
    {
        self->setAborted(true);
        self->setReadyState(LuaMinXmlHttpRequest::UNSENT);
    }
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_XMLHttpRequest_send'.",&tolua_err);
    return 0;
#endif
}

static int lua_cocos2dx_XMLHttpRequest_setRequestHeader(lua_State* L)
{
    int argc = 0;
    LuaMinXmlHttpRequest* self = nullptr;
    const char* field = "";
    const char* value = "";
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"cc.XMLHttpRequest",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = (LuaMinXmlHttpRequest*)  tolua_tousertype(L,1,0);
#if COCOS2D_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_XMLHttpRequest_setRequestHeader'\n", nullptr);
		return 0;
    }
#endif
    
    argc = lua_gettop(L) - 1;
    
    if ( 2 == argc )
    {
#if COCOS2D_DEBUG >= 1
        if (!tolua_isstring(L, 2, 0, &tolua_err) ||
            !tolua_isstring(L, 3, 0, &tolua_err) )
            goto tolua_lerror;
#endif
        
        field = tolua_tostring(L, 2, "");
        value = tolua_tostring(L, 3, "");
        self->setRequestHeader(field, value);
        return 0;
    }
    
    luaL_error(L, "'setRequestHeader' function of XMLHttpRequest wrong number of arguments: %d, was expecting %d\n", argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_XMLHttpRequest_setRequestHeader'.",&tolua_err);
    return 0;
#endif
}

static int lua_cocos2dx_XMLHttpRequest_getAllResponseHeaders(lua_State* L)
{
    int argc = 0;
    LuaMinXmlHttpRequest* self = nullptr;
    
    stringstream responseheaders;
    string responseheader = "";
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"cc.XMLHttpRequest",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = (LuaMinXmlHttpRequest*)  tolua_tousertype(L,1,0);
#if COCOS2D_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_XMLHttpRequest_getAllResponseHeaders'\n", nullptr);
		return 0;
    }
#endif
    
    argc = lua_gettop(L) - 1;
    
    if ( 0 == argc )
    {
        map<string, string> httpHeader = self->getHttpHeader();
        
        for (auto it = httpHeader.begin(); it != httpHeader.end(); ++it)
        {
            responseheaders << it->first << ": "<< it->second << "\n";
        }
        
        responseheader = responseheaders.str();
        tolua_pushstring(L, responseheader.c_str());
        return 1;
    }
    
    luaL_error(L, "'getAllResponseHeaders' function of XMLHttpRequest wrong number of arguments: %d, was expecting %d\n", argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_XMLHttpRequest_getAllResponseHeaders'.",&tolua_err);
    return 0;
#endif
}

static int lua_cocos2dx_XMLHttpRequest_getResponseHeader(lua_State* L)
{
    int argc = 0;
    LuaMinXmlHttpRequest* self = nullptr;
    
    string responseheader = "";
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"cc.XMLHttpRequest",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = (LuaMinXmlHttpRequest*)  tolua_tousertype(L,1,0);
#if COCOS2D_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_XMLHttpRequest_getAllResponseHeaders'\n", nullptr);
		return 0;
    }
#endif
    
    argc = lua_gettop(L) - 1;
    
    if ( 1 == argc )
    {
#if COCOS2D_DEBUG >= 1
        if (!tolua_isstring(L, 2, 0, &tolua_err) )
            goto tolua_lerror;
#endif
        responseheader = tolua_tostring(L, 2, "");
        
        stringstream streamData;
        streamData << responseheader;
        
        string value = streamData.str();
        
        
        auto iter = self->getHttpHeader().find(value);
        if (iter != self->getHttpHeader().end())
        {
            tolua_pushstring(L, (iter->second).c_str());
            return 1;
        }
    }
    
    luaL_error(L, "'getResponseHeader' function of XMLHttpRequest wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_XMLHttpRequest_getAllResponseHeaders'.",&tolua_err);
    return 0;
#endif
}

static int lua_cocos2dx_XMLHttpRequest_registerScriptHandler(lua_State* L)
{
    int argc = 0;
    LuaMinXmlHttpRequest* self = nullptr;
    
    string responseheader = "";
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"cc.XMLHttpRequest",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = (LuaMinXmlHttpRequest*)  tolua_tousertype(L,1,0);
#if COCOS2D_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_XMLHttpRequest_registerScriptHandler'\n", nullptr);
		return 0;
    }
#endif
    
    argc = lua_gettop(L) - 1;
    
    if (1 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(L,2,"LUA_FUNCTION",0,&tolua_err))
            goto tolua_lerror;
#endif
        
        int handler = (  toluafix_ref_function(L,2,0));
        cocos2d::ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, cocos2d::ScriptHandlerMgr::HandlerType::XMLHTTPREQUEST_READY_STATE_CHANGE);
        return 0;
    }
    
    luaL_error(L, "'registerScriptHandler' function of XMLHttpRequest wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_XMLHttpRequest_registerScriptHandler'.",&tolua_err);
    return 0;
#endif
}

static int lua_cocos2dx_XMLHttpRequest_unregisterScriptHandler(lua_State* L)
{
    int argc = 0;
    LuaMinXmlHttpRequest* self = nullptr;
    
    string responseheader = "";
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"cc.XMLHttpRequest",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = (LuaMinXmlHttpRequest*)  tolua_tousertype(L,1,0);
#if COCOS2D_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_XMLHttpRequest_unregisterScriptHandler'\n", nullptr);
		return 0;
    }
#endif
    
    argc = lua_gettop(L) - 1;
    
    if (0 == argc)
    {                
        cocos2d::ScriptHandlerMgr::getInstance()->removeObjectHandler((void*)self, cocos2d::ScriptHandlerMgr::HandlerType::XMLHTTPREQUEST_READY_STATE_CHANGE);
        
        return 0;
    }
    
    luaL_error(L, "'unregisterScriptHandler' function of XMLHttpRequest wrong number of arguments: %d, was expecting %d\n", argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_XMLHttpRequest_unregisterScriptHandler'.",&tolua_err);
    return 0;
#endif
    
}


TOLUA_API int register_xml_http_request(lua_State* L)
{
    tolua_open(L);
    lua_reg_xml_http_request(L);
    tolua_module(L,"cc",0);
    tolua_beginmodule(L,"cc");
      tolua_cclass(L,"XMLHttpRequest","cc.XMLHttpRequest","cc.Ref",lua_collect_xml_http_request);
      tolua_beginmodule(L,"XMLHttpRequest");
        tolua_variable(L, "responseType", lua_get_XMLHttpRequest_responseType, lua_set_XMLHttpRequest_responseType);
        tolua_variable(L, "withCredentials", lua_get_XMLHttpRequest_withCredentials, lua_set_XMLHttpRequest_withCredentials);
        tolua_variable(L, "timeout", lua_get_XMLHttpRequest_timeout, lua_set_XMLHttpRequest_timeout);
        tolua_variable(L, "readyState", lua_get_XMLHttpRequest_readyState, nullptr);
        tolua_variable(L, "status",lua_get_XMLHttpRequest_status,nullptr);
        tolua_variable(L, "statusText", lua_get_XMLHttpRequest_statusText, nullptr);
        tolua_variable(L, "responseText", lua_get_XMLHttpRequest_responseText, nullptr);
        tolua_variable(L, "response", lua_get_XMLHttpRequest_response, nullptr);
        tolua_function(L, "new", lua_cocos2dx_XMLHttpRequest_constructor);
        tolua_function(L, "open", lua_cocos2dx_XMLHttpRequest_open);
        tolua_function(L, "send", lua_cocos2dx_XMLHttpRequest_send);
        tolua_function(L, "abort", lua_cocos2dx_XMLHttpRequest_abort);
        tolua_function(L, "setRequestHeader", lua_cocos2dx_XMLHttpRequest_setRequestHeader);
        tolua_function(L, "getAllResponseHeaders", lua_cocos2dx_XMLHttpRequest_getAllResponseHeaders);
        tolua_function(L, "getResponseHeader", lua_cocos2dx_XMLHttpRequest_getResponseHeader);
        tolua_function(L, "registerScriptHandler", lua_cocos2dx_XMLHttpRequest_registerScriptHandler);
        tolua_function(L, "unregisterScriptHandler", lua_cocos2dx_XMLHttpRequest_unregisterScriptHandler);
      tolua_endmodule(L);
    tolua_endmodule(L);
    return 1;
}
