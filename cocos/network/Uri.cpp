/*
 * Copyright 2017 Facebook, Inc.
 * Copyright (c) 2017 Chukong Technologies
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * Uri class is based on the original file here https://github.com/facebook/folly/blob/master/folly/Uri.cpp
 */

#include "network/Uri.h"
#include "base/CCConsole.h" // For CCLOGERROR macro

#include <regex>
#include <sstream>

#include <ctype.h>
#include <stdlib.h>

#undef LIKELY
#undef UNLIKELY

#if defined(__GNUC__) && __GNUC__ >= 4
#define LIKELY(x)   (__builtin_expect((x), 1))
#define UNLIKELY(x) (__builtin_expect((x), 0))
#else
#define LIKELY(x)   (x)
#define UNLIKELY(x) (x)
#endif


namespace {

template<typename T>
std::string toString(T arg)
{
    std::stringstream ss;
    ss << arg;
    return ss.str();
}

std::string submatch(const std::smatch& m, int idx)
{
    auto& sub = m[idx];
    return std::string(sub.first, sub.second);
}

template <class String>
void toLower(String& s)
{
    for (auto& c : s) {
        c = char(tolower(c));
    }
}

}  // namespace

NS_CC_BEGIN

namespace network {

Uri::Uri()
: _isValid(false)
, _isSecure(false)
, _hasAuthority(false)
, _port(0)
{

}

Uri::Uri(const Uri& o)
{
    *this = o;
}

Uri::Uri(Uri&& o)
{
    *this = std::move(o);
}

Uri& Uri::operator=(const Uri& o)
{
    if (this != &o)
    {
        _isValid = o._isValid;
        _isSecure = o._isSecure;
        _scheme = o._scheme;
        _username = o._username;
        _password = o._password;
        _host = o._host;
        _hostName = o._hostName;
        _hasAuthority = o._hasAuthority;
        _port = o._port;
        _authority = o._authority;
        _pathEtc = o._pathEtc;
        _path = o._path;
        _query = o._query;
        _fragment = o._fragment;
        _queryParams = o._queryParams;
    }

    return *this;
}

Uri& Uri::operator=(Uri&& o)
{
    if (this != &o)
    {
        _isValid = o._isValid;
        o._isValid = false;
        _isSecure = o._isSecure;
        o._isSecure = false;
        _scheme = std::move(o._scheme);
        _username = std::move(o._username);
        _password = std::move(o._password);
        _host = std::move(o._host);
        _hostName = std::move(o._hostName);
        _hasAuthority = o._hasAuthority;
        o._hasAuthority = false;
        _port = o._port;
        o._port = 0;
        _authority = std::move(o._authority);
        _pathEtc = std::move(o._pathEtc);
        _path = std::move(o._path);
        _query = std::move(o._query);
        _fragment = std::move(o._fragment);
        _queryParams = std::move(o._queryParams);
    }
    return *this;
}

bool Uri::operator==(const Uri& o) const
{
    return (_isValid == o._isValid
        && _isSecure == o._isSecure
        && _scheme == o._scheme
        && _username == o._username
        && _password == o._password
        && _host == o._host
        && _hostName == o._hostName
        && _hasAuthority == o._hasAuthority
        && _port == o._port
        && _authority == o._authority
        && _pathEtc == o._pathEtc
        && _path == o._path
        && _query == o._query
        && _fragment == o._fragment
        && _queryParams == o._queryParams);
}

Uri Uri::parse(const std::string &str)
{
    Uri uri;

    if (!uri.doParse(str))
    {
        uri.clear();
    }

    return uri;
}

bool Uri::doParse(const std::string& str)
{
    static const std::regex uriRegex(
      "([a-zA-Z][a-zA-Z0-9+.-]*):"  // scheme:
      "([^?#]*)"                    // authority and path
      "(?:\\?([^#]*))?"             // ?query
      "(?:#(.*))?");                // #fragment
    static const std::regex authorityAndPathRegex("//([^/]*)(/.*)?");

    if (str.empty())
    {
        CCLOGERROR("%s", "Empty URI is invalid!");
        return false;
    }

    bool hasScheme = true;;
    std::string copied(str);
    if (copied.find("://") == std::string::npos)
    {
        hasScheme = false;
        copied.insert(0, "abc://"); // Just make regex happy.
    }

    std::smatch match;
    if (UNLIKELY(!std::regex_match(copied.cbegin(), copied.cend(), match, uriRegex))) {
        CCLOGERROR("Invalid URI: %s", str.c_str());
        return false;
    }

    if (hasScheme)
    {
        _scheme = submatch(match, 1);
        toLower(_scheme);
        if (_scheme == "https" || _scheme == "wss")
        {
            _isSecure = true;
        }
    }

    std::string authorityAndPath(match[2].first, match[2].second);
    std::smatch authorityAndPathMatch;
    if (!std::regex_match(authorityAndPath.cbegin(),
                          authorityAndPath.cend(),
                          authorityAndPathMatch,
                          authorityAndPathRegex)) {
        // Does not start with //, doesn't have authority
        _hasAuthority = false;
        _path = authorityAndPath;
    } else {
        static const std::regex authorityRegex(
            "(?:([^@:]*)(?::([^@]*))?@)?"  // username, password
            "(\\[[^\\]]*\\]|[^\\[:]*)"     // host (IP-literal (e.g. '['+IPv6+']',
                                           // dotted-IPv4, or named host)
            "(?::(\\d*))?");               // port

        auto authority = authorityAndPathMatch[1];
        std::smatch authorityMatch;
        if (!std::regex_match(authority.first,
                                authority.second,
                                authorityMatch,
                                authorityRegex)) {
            std::string invalidAuthority(authority.first, authority.second);
            CCLOGERROR("Invalid URI authority: %s", invalidAuthority.c_str());
            return false;
        }

        std::string port(authorityMatch[4].first, authorityMatch[4].second);
        if (!port.empty()) {
            _port = static_cast<uint16_t>(atoi(port.c_str()));
        }

        _hasAuthority = true;
        _username = submatch(authorityMatch, 1);
        _password = submatch(authorityMatch, 2);
        _host = submatch(authorityMatch, 3);
        _path = submatch(authorityAndPathMatch, 2);
    }

    _query = submatch(match, 3);
    _fragment = submatch(match, 4);
    _isValid = true;

    // Assign authority part
    //
    // Port is 5 characters max and we have up to 3 delimiters.
    _authority.reserve(getHost().size() + getUserName().size() + getPassword().size() + 8);

    if (!getUserName().empty() || !getPassword().empty()) {
        _authority.append(getUserName());

        if (!getPassword().empty()) {
            _authority.push_back(':');
            _authority.append(getPassword());
        }

        _authority.push_back('@');
    }

    _authority.append(getHost());

    if (getPort() != 0) {
        _authority.push_back(':');
        _authority.append(::toString(getPort()));
    }

    // Assign path etc part
    _pathEtc = _path;
    if (!_query.empty())
    {
        _pathEtc += '?';
        _pathEtc += _query;
    }

    if (!_fragment.empty())
    {
        _pathEtc += '#';
        _pathEtc += _fragment;
    }

    // Assign host name
    if (!_host.empty() && _host[0] == '[') {
        // If it starts with '[', then it should end with ']', this is ensured by
        // regex
        _hostName = _host.substr(1, _host.size() - 2);
    } else {
        _hostName = _host;
    }

    return true;
}

void Uri::clear()
{
    _isValid = false;
    _isSecure = false;
    _scheme.clear();
    _username.clear();
    _password.clear();
    _host.clear();
    _hostName.clear();
    _hasAuthority = false;
    _port = 0;
    _authority.clear();
    _pathEtc.clear();
    _path.clear();
    _query.clear();
    _fragment.clear();
    _queryParams.clear();
}

const std::vector<std::pair<std::string, std::string>>& Uri::getQueryParams()
{
    if (!_query.empty() && _queryParams.empty()) {
        // Parse query string
        static const std::regex queryParamRegex(
            "(^|&)" /*start of query or start of parameter "&"*/
            "([^=&]*)=?" /*parameter name and "=" if value is expected*/
            "([^=&]*)" /*parameter value*/
            "(?=(&|$))" /*forward reference, next should be end of query or
                          start of next parameter*/);
        std::cregex_iterator paramBeginItr(
            _query.data(), _query.data() + _query.size(), queryParamRegex);
        std::cregex_iterator paramEndItr;
        for (auto itr = paramBeginItr; itr != paramEndItr; itr++) {
            if (itr->length(2) == 0) {
                // key is empty, ignore it
                continue;
            }
            _queryParams.emplace_back(
                std::string((*itr)[2].first, (*itr)[2].second), // parameter name
                std::string((*itr)[3].first, (*itr)[3].second) // parameter value
            );
        }
    }
    return _queryParams;
}

std::string Uri::toString() const
{
    std::stringstream ss;
    if (_hasAuthority) {
        ss << _scheme << "://";
        if (!_password.empty()) {
            ss << _username << ":" << _password << "@";
        } else if (!_username.empty()) {
            ss << _username << "@";
        }
        ss << _host;
        if (_port != 0) {
            ss << ":" << _port;
        }
    } else {
        ss << _scheme << ":";
    }
    ss << _path;
    if (!_query.empty()) {
        ss << "?" << _query;
    }
    if (!_fragment.empty()) {
        ss << "#" << _fragment;
    }
    return ss.str();
}

} // namespace network {

NS_CC_END
