/****************************************************************************
 Copyright (c) 2015 Chukong Technologies Inc.
 
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


#ifndef __CC_PU_SCRIPT_PARSER_H__
#define __CC_PU_SCRIPT_PARSER_H__

#include <iostream>
#include <string>
#include <list>
#include <map>


#include "base/CCRef.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticle3DScriptLexer.h"

NS_CC_BEGIN

struct PUConcreteNode;

enum PUConcreteNodeType
{
    CNT_VARIABLE,
    CNT_VARIABLE_ASSIGN,
    CNT_WORD,
    CNT_IMPORT,
    CNT_QUOTE,
    CNT_LBRACE,
    CNT_RBRACE,
    CNT_COLON
};

typedef std::list<PUConcreteNode*> PUConcreteNodeList;

struct PUConcreteNode
{
    std::string  token, file;
    unsigned int line;
    PUConcreteNodeType type;
    PUConcreteNodeList children;
    PUConcreteNode *parent;

    ~PUConcreteNode();
};


void traceScriptParser(PUConcreteNodeList& nodes);

class PUScriptParser
{
    public:
        PUScriptParser();
        ~PUScriptParser();
    
        void parse(PUConcreteNodeList& nodes,const PUScriptTokenList& tokens);

    
        void parseChunk(PUConcreteNodeList& nodes, const PUScriptTokenList &tokens);
    private:

    PUScriptToken *getToken(PUScriptTokenList::iterator i, PUScriptTokenList::iterator end, int offset);
    PUScriptTokenList::const_iterator skipNewlines(PUScriptTokenList::const_iterator i, PUScriptTokenList::const_iterator end);
    
    
};

NS_CC_END

#endif /* defined(__cocos2d_libs__CCScriptParser__) */
