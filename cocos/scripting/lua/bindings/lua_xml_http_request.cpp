
#include "lua_xml_http_request.h"

extern "C"
{
#include "tolua_fix.h"
}

#include <string>

using namespace std;

LuaMinXmlHttpRequest::LuaMinXmlHttpRequest():_isNetwork(true)
{
    _httpHeader.clear();
    _requestHeader.clear();
    _withCredentialsValue = true;
    _httpRequest  = new network::HttpRequest();
}

LuaMinXmlHttpRequest::~LuaMinXmlHttpRequest()
{
    _httpHeader.clear();
    _requestHeader.clear();
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
    unsigned found_header_field = header.find_first_of(":");
    
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
            unsigned found_http = val.find("HTTP");
            
            // Check for HTTP Header to set statusText
            if (found_http != std::string::npos) {
                
                stringstream mystream;
                
                // Get Response Status
                pch = strtok (NULL, " ");
                mystream << pch;
                
                pch = strtok (NULL, " ");
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
    _httpRequest->setResponseCallback(this, httpresponse_selector(LuaMinXmlHttpRequest::handle_requestResponse));
    network::HttpClient::getInstance()->send(_httpRequest);
    _httpRequest->release();
}


/**
 *  @brief Callback for HTTPRequest. Handles the response and invokes Callback.
 *  @param sender   Object which initialized callback
 *  @param respone  Response object
 *  @js NA
 */
void LuaMinXmlHttpRequest::handle_requestResponse(network::HttpClient *sender, network::HttpResponse *response)
{
    if (0 != strlen(response->getHttpRequest()->getTag()))
    {
        CCLOG("%s completed", response->getHttpRequest()->getTag());
    }
    
    int statusCode = response->getResponseCode();
    char statusString[64] = {};
    sprintf(statusString, "HTTP Status Code: %d, tag = %s", statusCode, response->getHttpRequest()->getTag());
    
    if (!response->isSucceed())
    {
        CCLOG("response failed");
        CCLOG("error buffer: %s", response->getErrorBuffer());
        return;
    }
    
    // set header
    std::vector<char> *headers = response->getResponseHeader();
    
    char* concatHeader = (char*) malloc(headers->size() + 1);
    std::string header(headers->begin(), headers->end());
    strcpy(concatHeader, header.c_str());
    
    std::istringstream stream(concatHeader);
    std::string line;
    while(std::getline(stream, line)) {
        _gotHeader(line);
    }

    /** get the response data **/
    std::vector<char> *buffer = response->getResponseData();
    char* concatenated = (char*) malloc(buffer->size() + 1);
    std::string s2(buffer->begin(), buffer->end());
    
    strcpy(concatenated, s2.c_str());
    
    if (statusCode == 200)
    {
        //Succeeded
        _status = 200;
        _readyState = DONE;
        _data << concatenated;
        _dataSize = buffer->size();
    }
    else
    {
        _status = 0;
    }
    // Free Memory.
    free((void*) concatHeader);
    free((void*) concatenated);
    
    // call back lua function --TODO
    int handler = 0;
}

/* function to regType */
static void lua_reg_xml_http_request(lua_State* L)
{
    tolua_usertype(L, "XMLHttpRequest");
}

static int lua_collect_xml_http_request (lua_State* L)
{
    LuaMinXmlHttpRequest* self = (LuaMinXmlHttpRequest*) tolua_tousertype(L,1,0);
    Mtolua_delete(self);
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
        self = new LuaMinXmlHttpRequest();
        self->autorelease();
        int ID =  self? (int)self->_ID : -1;
        int* luaID = self? &self->_luaID : NULL;
        toluafix_pushusertype_ccobject(L, ID, luaID, (void*)self, "XMLHttpRequest");
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "XMLHttpRequest",argc, 0);
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
    if (!tolua_isusertype(L,1,"XMLHttpRequest",0,&tolua_err)) goto tolua_lerror;
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
    if (!tolua_isusertype(L,1,"XMLHttpRequest",0,&tolua_err)) goto tolua_lerror;
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
    
    CCLOG("'setResponseType' function of XMLHttpRequest wrong number of arguments: %d, was expecting %d\n", argc, 1);
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
    if (!tolua_isusertype(L,1,"XMLHttpRequest",0,&tolua_err)) goto tolua_lerror;
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
    if (!tolua_isusertype(L,1,"XMLHttpRequest",0,&tolua_err)) goto tolua_lerror;
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
    
    CCLOG("'setWithCredentials' function of XMLHttpRequest wrong number of arguments: %d, was expecting %d\n", argc, 1);
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
    if (!tolua_isusertype(L,1,"XMLHttpRequest",0,&tolua_err)) goto tolua_lerror;
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
    if (!tolua_isusertype(L,1,"XMLHttpRequest",0,&tolua_err)) goto tolua_lerror;
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
    
    CCLOG("'setTimeout' function of XMLHttpRequest wrong number of arguments: %d, was expecting %d\n", argc, 1);
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
    if (!tolua_isusertype(L,1,"XMLHttpRequest",0,&tolua_err)) goto tolua_lerror;
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
    if (!tolua_isusertype(L,1,"XMLHttpRequest",0,&tolua_err)) goto tolua_lerror;
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
    if (!tolua_isusertype(L,1,"XMLHttpRequest",0,&tolua_err)) goto tolua_lerror;
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

static int lua_get_XMLHttpRequest_response(lua_State* L)
{
    LuaMinXmlHttpRequest* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"XMLHttpRequest",0,&tolua_err)) goto tolua_lerror;
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
        //TODO
        return 0;
    }
    else if(self->getResponseType() == LuaMinXmlHttpRequest::ResponseType::ARRAY_BUFFER)
    {
        //TODO
        return 0;
    }
    else
    {
        lua_pushstring(L, self->getStatusText().c_str());
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
    if (!tolua_isusertype(L,1,"XMLHttpRequest",0,&tolua_err)) goto tolua_lerror;
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
            else
            {
                self->getHttpRequest()->setRequestType(network::HttpRequest::Type::GET);
            }
            
            self->getHttpRequest()->setUrl(url.c_str());
            
        }
        
        self->setIsNetWork(true);
        self->setReadyState(LuaMinXmlHttpRequest::OPENED);

        return 0;
    }
    
    CCLOG("'open' function of XMLHttpRequest wrong number of arguments: %d, was expecting %d\n", argc, 2);
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
    std::string data = "";
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"XMLHttpRequest",0,&tolua_err)) goto tolua_lerror;
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

    if ( 1 == argc )
    {
#if COCOS2D_DEBUG >= 1
        if (!tolua_isstring(L, 2, 0, &tolua_err))
            goto tolua_lerror;
#endif
        data = tolua_tostring(L, 2, "");
    }
    
    if (data.length() > 0 &&
        (self->getMethod().compare("post") == 0 || self->getMethod().compare("POST") == 0) &&
        nullptr != self->getHttpRequest())
    {
        self->getHttpRequest()->setRequestData(data.c_str(), data.length());
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
    return 0;
}

static int lua_cocos2dx_XMLHttpRequest_setRequestHeader(lua_State* L)
{
    int argc = 0;
    LuaMinXmlHttpRequest* self = nullptr;
    const char* field = "";
    const char* value = "";
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"XMLHttpRequest",0,&tolua_err)) goto tolua_lerror;
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
    
    CCLOG("'setRequestHeader' function of XMLHttpRequest wrong number of arguments: %d, was expecting %d\n", argc, 2);
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
    if (!tolua_isusertype(L,1,"XMLHttpRequest",0,&tolua_err)) goto tolua_lerror;
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
    
    CCLOG("'getAllResponseHeaders' function of XMLHttpRequest wrong number of arguments: %d, was expecting %d\n", argc, 0);
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
    if (!tolua_isusertype(L,1,"XMLHttpRequest",0,&tolua_err)) goto tolua_lerror;
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
    
    CCLOG("'getResponseHeader' function of XMLHttpRequest wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_XMLHttpRequest_getAllResponseHeaders'.",&tolua_err);
    return 0;
#endif
}

TOLUA_API int lua_xml_http_request_open(lua_State* L)
{
    tolua_open(L);
    lua_reg_xml_http_request(L);
    tolua_module(L,NULL,0);
    tolua_beginmodule(L,NULL);
      tolua_cclass(L,"XMLHttpRequest","XMLHttpRequest","",lua_collect_xml_http_request);
      tolua_beginmodule(L,"XMLHttpRequest");
        tolua_variable(L, "responseType", lua_get_XMLHttpRequest_responseType, lua_set_XMLHttpRequest_responseType);
        tolua_variable(L, "withCredentials", lua_get_XMLHttpRequest_withCredentials, lua_set_XMLHttpRequest_withCredentials);
        tolua_variable(L, "timeout", lua_get_XMLHttpRequest_timeout, lua_set_XMLHttpRequest_timeout);
        tolua_variable(L, "readyState", lua_get_XMLHttpRequest_readyState, nullptr);
        tolua_variable(L, "status",lua_get_XMLHttpRequest_status,nullptr);
        tolua_variable(L, "statusText", lua_get_XMLHttpRequest_statusText, nullptr);
        tolua_variable(L, "response", lua_get_XMLHttpRequest_response, nullptr);
        tolua_function(L, "new", lua_cocos2dx_XMLHttpRequest_constructor);
        tolua_function(L, "open", lua_cocos2dx_XMLHttpRequest_open);
        tolua_function(L, "send", lua_cocos2dx_XMLHttpRequest_send);
        tolua_function(L, "abort", lua_cocos2dx_XMLHttpRequest_abort);
        tolua_function(L, "setRequestHeader", lua_cocos2dx_XMLHttpRequest_setRequestHeader);
        tolua_function(L, "getAllResponseHeaders", lua_cocos2dx_XMLHttpRequest_getAllResponseHeaders);
        tolua_function(L, "getResponseHeader", lua_cocos2dx_XMLHttpRequest_getResponseHeader);
      tolua_endmodule(L);
    tolua_endmodule(L);
    return 1;
}
