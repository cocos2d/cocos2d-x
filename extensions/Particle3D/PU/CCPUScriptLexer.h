/****************************************************************************
 Copyright (C) 2013 Henry van Merode. All rights reserved.
 Copyright (c) 2015-2017 Chukong Technologies Inc.
 
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

#ifndef __CC_PU_SCRIPT_LEXER_H__
#define __CC_PU_SCRIPT_LEXER_H__

#include "base/CCRef.h"
#include <vector>
#include <string>

NS_CC_BEGIN
enum{
    TID_LBRACKET = 0, // {
    TID_RBRACKET, // }
    TID_COLON, // :
    TID_VARIABLE, // $...
    TID_WORD, // *
    TID_QUOTE, // "*"
    TID_NEWLINE, // \n
    TID_UNKNOWN,
    TID_END
};

/** This struct represents a token, which is an ID'd lexeme from the
 parsing input stream.
 */
struct PUScriptToken
{
    /// This is the lexeme for this token
    std::string lexeme, file;
    /// This is the id associated with the lexeme, which comes from a lexeme-token id mapping
    unsigned int type;
    /// This holds the line number of the input stream where the token was found.
    unsigned int line;
};

typedef std::vector<PUScriptToken*> PUScriptTokenList;



class PUScriptLexer
{
    public:
        PUScriptLexer();
        ~PUScriptLexer();

    void openLexer(const std::string &str,const std::string &source,PUScriptTokenList& tokenList);

    /** Tokenizes the given input and returns the list of tokens found */
        //tokenize(const std::string &str, const std::string &source);
    private: // Private utility operations
        void setToken(const std::string &lexeme, int line, const std::string &source, PUScriptTokenList *tokens);
        bool isWhitespace(char c) const;
        bool isNewline(char c) const;

    
};

NS_CC_END

#endif 