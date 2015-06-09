/****************************************************************************
 Copyright (C) 2013 Henry van Merode. All rights reserved.
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

#include "CCPUScriptParser.h"

NS_CC_BEGIN

PUScriptParser::PUScriptParser()
{
    
}

PUScriptParser::~PUScriptParser()
{
    
}
void traceScriptParserCell(PUConcreteNodeList& nodes,int level)
{
      PUConcreteNodeList::const_iterator it = nodes.begin();
    for(;it != nodes.end();it++)
    {
        printf("%s,##%d\n",(*it)->token.c_str(),level);
        if((*it)->children.size() != 0)
        {
            traceScriptParserCell((*it)->children,level+1);
        }
    }
}

void traceScriptParser(PUConcreteNodeList& nodes)
{
    
    traceScriptParserCell(nodes,1);
    
}

void PUScriptParser::parse(PUConcreteNodeList& nodes,const PUScriptTokenList& tokens)
{
    // MEMCATEGORY_GENERAL because SharedPtr can only free using that category

    
    enum{READY, OBJECT};
    unsigned int state = READY;
    
    PUConcreteNode *parent = 0;
    PUConcreteNode* node;
    PUScriptToken *token = 0;
    PUScriptTokenList::const_iterator i = tokens.begin(), end = tokens.end();
  //  int kkkk = 0;
    while(i != end)
    {
        
//        kkkk ++;
        token = (*i);
        
        switch(state)
        {
            case READY:
                if(token->type == TID_WORD)
                {
                    if(token->lexeme == "import")
                    {
                        node = new (std::nothrow) PUConcreteNode;
                        
                        node->token = token->lexeme;
                        node->file = token->file;
                        node->line = token->line;
                        node->type = CNT_IMPORT;
                        
                        // The next token is the target
                        ++i;
                        if(i == end || ((*i)->type != TID_WORD && (*i)->type != TID_QUOTE))
                        {
                            printf("Except,expected import target at line :%d,ScriptParser::parse",node->line);
                        }
                        PUConcreteNode* temp = new (std::nothrow) PUConcreteNode;
                        temp->parent = node;
                        temp->file = (*i)->file;
                        temp->line = (*i)->line;
                        temp->type = (*i)->type == TID_WORD ? CNT_WORD : CNT_QUOTE;
                        if(temp->type == CNT_QUOTE)
                            temp->token = (*i)->lexeme.substr(1, token->lexeme.size() - 2);
                        else
                            temp->token = (*i)->lexeme;
                        node->children.push_back(temp);
                        
                        // The second-next token is the source
                        ++i;
                        ++i;
                        if(i == end || ((*i)->type != TID_WORD && (*i)->type != TID_QUOTE))
                        {
                            printf("expected import source at line :%d,ScriptParser::parse",node->line);
                        }
                        temp = new (std::nothrow) PUConcreteNode;
                        temp->parent = node;
                        temp->file = (*i)->file;
                        temp->line = (*i)->line;
                        temp->type = (*i)->type == TID_WORD ? CNT_WORD : CNT_QUOTE;
                        if(temp->type == CNT_QUOTE)
                            temp->token = (*i)->lexeme.substr(1, (*i)->lexeme.size() - 2);
                        else
                            temp->token = (*i)->lexeme;
                        
                        node->children.push_back(temp);
                        
                        // Consume all the newlines
                        i = skipNewlines(i, end);
                        
                        // Insert the node
                        if(parent)
                        {
                            node->parent = parent;
                            parent->children.push_back(node);
                        }
                        else
                        {
                            node->parent = 0;
                            nodes.push_back(node);
                        }
                        node = nullptr;
                    }
                    else if(token->lexeme == "set")
                    {
                        node = new (std::nothrow) PUConcreteNode;
                        node->token = token->lexeme;
                        node->file = token->file;
                        node->line = token->line;
                        node->type = CNT_VARIABLE_ASSIGN;
                        
                        // The next token is the variable
                        ++i;
                        if(i == end || (*i)->type != TID_VARIABLE)
                        {
                            printf("Exception");
                        }
                        PUConcreteNode* temp = new (std::nothrow) PUConcreteNode;
                        temp->parent = node;
                        temp->file = (*i)->file;
                        temp->line = (*i)->line;
                        temp->type = CNT_VARIABLE;
                        temp->token = (*i)->lexeme;
                        node->children.push_back(temp);
                        
                        // The next token is the assignment
                        ++i;
                        if(i == end || ((*i)->type != TID_WORD && (*i)->type != TID_QUOTE))
                        {
                            printf("expected variable value at line %d ScriptParser::parse\n",node->line);
                        }
                        temp = new (std::nothrow) PUConcreteNode;
                        temp->parent = node;
                        temp->file = (*i)->file;
                        temp->line = (*i)->line;
                        temp->type = (*i)->type == TID_WORD ? CNT_WORD : CNT_QUOTE;
                        if(temp->type == CNT_QUOTE)
                            temp->token = (*i)->lexeme.substr(1, (*i)->lexeme.size() - 2);
                        else
                            temp->token = (*i)->lexeme;
                        node->children.push_back(temp);
                        
                        // Consume all the newlines
                        i = skipNewlines(i, end);
                        
                        // Insert the node
                        if(parent)
                        {
                            node->parent = parent;
                            parent->children.push_back(node);
                        }
                        else
                        {
                            node->parent = 0;
                            nodes.push_back(node);
                        }
                        node = nullptr;
                    }
                    else
                    {
                        node = new (std::nothrow) PUConcreteNode();
                        node->file = token->file;
                        node->line = token->line;
                        node->type = token->type == TID_WORD ? CNT_WORD : CNT_QUOTE;
                        if(node->type == CNT_QUOTE)
                            node->token = token->lexeme.substr(1, token->lexeme.size() - 2);
                        else
                            node->token = token->lexeme;
                        
                        // Insert the node
                        if(parent)
                        {
                            node->parent = parent;
                            parent->children.push_back(node);
                        }
                        else
                        {
                            node->parent = 0;
                            nodes.push_back(node);
                        }
                        
                        // Set the parent
                        parent = node;
                        
                        // Switch states
                        state = OBJECT;
                        
                        node = nullptr;
                    }
                }
                else if(token->type == TID_RBRACKET)
                {
                    // Go up one level if we can
                    if(parent)
                        parent = parent->parent;
                    
                    node = new (std::nothrow) PUConcreteNode();
                    node->token = token->lexeme;
                    node->file = token->file;
                    node->line = token->line;
                    node->type = CNT_RBRACE;
                    
                    // Consume all the newlines
                    i = skipNewlines(i, end);
                    
                    // Insert the node
                    if(parent)
                    {
                        node->parent = parent;
                        parent->children.push_back(node);
                    }
                    else
                    {
                        node->parent = 0;
                        nodes.push_back(node);
                    }
                    
                    // Move up another level
                    if(parent)
                        parent = parent->parent;
                    
                    node = nullptr;
                }
                break;
            case OBJECT:
                if(token->type == TID_NEWLINE)
                {
                    // Look ahead to the next non-newline token and if it isn't an {, this was a property
                    PUScriptTokenList::const_iterator next = skipNewlines(i, end);
                    if(next == end || (*next)->type != TID_LBRACKET)
                    {
                        // Ended a property here
                        if(parent)
                            parent = parent->parent;
                        state = READY;
                    }
                }
                else if(token->type == TID_COLON)
                {
                    node = new (std::nothrow) PUConcreteNode();
                    node->token = token->lexeme;
                    node->file = token->file;
                    node->line = token->line;
                    node->type = CNT_COLON;
                    
                    // The following token are the parent objects (base classes).
                    // Require at least one of them.
                    
                    PUScriptTokenList::const_iterator j = i + 1;
                    j = skipNewlines(j, end);
                    if(j == end || ((*j)->type != TID_WORD && (*j)->type != TID_QUOTE)) {
                    
                        printf("expected object identifier at line %d ScriptParser::parse\n",node->line);
                    }
                    
                    while(j != end && ((*j)->type == TID_WORD || (*j)->type == TID_QUOTE))
                    {
                        PUConcreteNode* tempNode = new (std::nothrow) PUConcreteNode;
                        tempNode->token = (*j)->lexeme;
                        tempNode->file = (*j)->file;
                        tempNode->line = (*j)->line;
                        tempNode->type = (*j)->type == TID_WORD ? CNT_WORD : CNT_QUOTE;
                        tempNode->parent = node;
                        node->children.push_back(tempNode);
                        ++j;
                    }
                    
                    // Move it backwards once, since the end of the loop moves it forwards again anyway
                    j--;
                    i = j;
                    
                    // Insert the node
                    if(parent)
                    {
                        node->parent = parent;
                        parent->children.push_back(node);
                    }
                    else
                    {
                        node->parent = 0;
                        nodes.push_back(node);
                    }
                    node = nullptr;
                }
                else if(token->type == TID_LBRACKET)
                {
                    node = new (std::nothrow) PUConcreteNode;
                    node->token = token->lexeme;
                    node->file = token->file;
                    node->line = token->line;
                    node->type = CNT_LBRACE;
                    
                    // Consume all the newlines
                    i = skipNewlines(i, end);
                    
                    // Insert the node
                    if(parent)
                    {
                        node->parent = parent;
                        parent->children.push_back(node);
                    }
                    else
                    {
                        node->parent = 0;
                        nodes.push_back(node);
                    }
                    
                    // Set the parent
                    parent = node;
                    
                    // Change the state
                    state = READY;
                    
                    node = nullptr;
                }
                else if(token->type == TID_RBRACKET)
                {
                    // Go up one level if we can
                    if(parent)
                        parent = parent->parent;
                    
                    // If the parent is currently a { then go up again
                    if(parent && parent->type == CNT_LBRACE && parent->parent)
                        parent = parent->parent;
                    
                    node = new (std::nothrow) PUConcreteNode;
                    node->token = token->lexeme;
                    node->file = token->file;
                    node->line = token->line;
                    node->type = CNT_RBRACE;
                    
                    // Consume all the newlines
                    i = skipNewlines(i, end);
                    
                    // Insert the node
                    if(parent)
                    {
                        node->parent = parent;
                        parent->children.push_back(node);
                    }
                    else
                    {
                        node->parent = 0;
                        nodes.push_back(node);
                    }
                    
                    // Move up another level
                    if(parent)
                        parent = parent->parent;
                    
                    node = nullptr;
                    state = READY;
                }
                else if(token->type == TID_VARIABLE)
                {
                    node = new (std::nothrow) PUConcreteNode;
                    node->token = token->lexeme;
                    node->file = token->file;
                    node->line = token->line;
                    node->type = CNT_VARIABLE;
                    
                    // Insert the node
                    if(parent)
                    {
                        node->parent = parent;
                        parent->children.push_back(node);
                    }
                    else
                    {
                        node->parent = 0;
                        nodes.push_back(node);
                    }
                    node = nullptr;
                }
                else if(token->type == TID_QUOTE)
                {
                    node = new (std::nothrow) PUConcreteNode;
                    node->token = token->lexeme.substr(1, token->lexeme.size() - 2);
                    node->file = token->file;
                    node->line = token->line;
                    node->type = CNT_QUOTE;
                    
                    // Insert the node
                    if(parent)
                    {
                        node->parent = parent;
                        parent->children.push_back(node);
                    }
                    else
                    {
                        node->parent = 0;
                        nodes.push_back(node);
                    }
                    node = nullptr;
                }
                else if(token->type == TID_WORD)
                {
                    node = new (std::nothrow) PUConcreteNode;
                    node->token = token->lexeme;
                    node->file = token->file;
                    node->line = token->line;
                    node->type = CNT_WORD;
                    
                    // Insert the node
                    if(parent)
                    {
                        node->parent = parent;
                        parent->children.push_back(node);
                    }
                    else
                    {
                        node->parent = 0;
                        nodes.push_back(node);
                    }
                    node = nullptr;
                }
                break;
        }
        
        ++i;
    }
    
    
//    traceScriptParser(nodes);//
//    printf("kkkk:%d\n",kkkk);//
    
    
}




void PUScriptParser::parseChunk(PUConcreteNodeList& nodes, const PUScriptTokenList &tokens)
{
    PUConcreteNode* node = nullptr;
    PUScriptToken *token = 0;
    for(PUScriptTokenList::const_iterator i = tokens.begin(); i != tokens.end(); ++i)
    {
        token = *i;
        
        node = nullptr;
        switch(token->type)
        {
            case TID_VARIABLE:
                node = new (std::nothrow) PUConcreteNode;
                node->file = token->file;
                node->line = token->line;
                node->parent = 0;
                node->token = token->lexeme;
                node->type = CNT_VARIABLE;
                break;
            case TID_WORD:
                node = new (std::nothrow) PUConcreteNode;
                node->file = token->file;
                node->line = token->line;
                node->parent = 0;
                node->token = token->lexeme;
                node->type = CNT_WORD;
                break;
            case TID_QUOTE:
                node = new (std::nothrow) PUConcreteNode;
                node->file = token->file;
                node->line = token->line;
                node->parent = 0;
                node->token = token->lexeme.substr(1, token->lexeme.size() - 2);
                node->type = CNT_QUOTE;
            default:
                printf("unexpected token,%s,%d\n",token->lexeme.c_str(),token->line);
        }
        
        if(node != nullptr)
            nodes.push_back(node);
    }
}

PUScriptToken *PUScriptParser::getToken(PUScriptTokenList::iterator i, PUScriptTokenList::iterator end, int offset)
{
    PUScriptToken *token = 0;
    PUScriptTokenList::iterator iter = i + offset;
    if(iter != end)
        token = (*i);
    return token;
}

PUScriptTokenList::const_iterator PUScriptParser::skipNewlines(PUScriptTokenList::const_iterator i, PUScriptTokenList::const_iterator end)
{
    while(i != end && (*i)->type == TID_NEWLINE)
        ++i;
    return i;
}

PUConcreteNode::~PUConcreteNode()
{
    for (auto iter : children){
        delete iter;
    }
}

NS_CC_END