/****************************************************************************
 Copyright (C) 2013 Henry van Merode. All rights reserved.
 Copyright (c) 2015-2016 Chukong Technologies Inc.
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

#include "CCPUScriptCompiler.h"
#include "extensions/Particle3D/PU/CCPUTranslateManager.h"
#include "platform/CCFileUtils.h"
NS_CC_BEGIN

// ObjectAbstractNode
PUObjectAbstractNode::PUObjectAbstractNode(PUAbstractNode *ptr)
:PUAbstractNode(ptr), id(0), abstract(false)
{
    type = ANT_OBJECT;
}

PUAbstractNode *PUObjectAbstractNode::clone() const
{
    PUObjectAbstractNode *node = new (std::nothrow) PUObjectAbstractNode(parent);
    node->file = file;
    node->line = line;
    node->type = type;
    node->name = name;
    node->cls = cls;
    node->id = id;
    node->abstract = abstract;
    node->context = context;
    for(PUAbstractNodeList::const_iterator i = children.begin(); i != children.end(); ++i)
    {
        PUAbstractNode* newNode = (PUAbstractNode*)((*i)->clone());
        newNode->parent = (PUAbstractNode*)node;
        node->children.push_back(newNode);
    }
    for(PUAbstractNodeList::const_iterator i = values.begin(); i != values.end(); ++i)
    {
        PUAbstractNode* newNode = (PUAbstractNode*)((*i)->clone());
        newNode->parent = (PUAbstractNode*)node;
        node->values.push_back(newNode);
    }
    node->_env = _env;
    return (PUAbstractNode*)node;
}

std::string PUObjectAbstractNode::getValue() const
{
    return cls;
}

void PUObjectAbstractNode::addVariable(const std::string &inName)
{
    _env.emplace(inName, "");
}

void PUObjectAbstractNode::setVariable(const std::string &inName, const std::string &value)
{
    _env[inName] = value;
}


std::pair<bool,std::string> PUObjectAbstractNode::getVariable(const std::string &inName) const
{
    std::unordered_map<std::string,std::string>::const_iterator i = _env.find(inName);
    if(i != _env.end())
        return std::make_pair(true, i->second);

    PUObjectAbstractNode *parentNode = (PUObjectAbstractNode*)this->parent;
    while(parentNode)
    {
        i = parentNode->_env.find(inName);
        if(i != parentNode->_env.end())
            return std::make_pair(true, i->second);
        parentNode = (PUObjectAbstractNode*)parentNode->parent;
    }
    return std::make_pair(false, "");
}

const std::unordered_map<std::string,std::string> &PUObjectAbstractNode::getVariables() const
{
    return _env;
}

PUObjectAbstractNode::~PUObjectAbstractNode()
{
    for (auto iter : children){
        delete iter;
    }

    for (auto iter : values){
        delete iter;
    }

    for (auto iter : overrides){
        delete iter;
    }
}



// PropertyAbstractNode//
PUPropertyAbstractNode::PUPropertyAbstractNode(PUAbstractNode *ptr)
:PUAbstractNode(ptr), id(0)
{
    type = ANT_PROPERTY;
}

PUAbstractNode *PUPropertyAbstractNode::clone() const
{
    PUPropertyAbstractNode *node = new (std::nothrow) PUPropertyAbstractNode(parent);
    node->file = file;
    node->line = line;
    node->type = type;
    node->name = name;
    node->id = id;
    for(PUAbstractNodeList::const_iterator i = values.begin(); i != values.end(); ++i)
    {
        PUAbstractNode* newNode = (PUAbstractNode*)((*i)->clone());
        newNode->parent = (PUAbstractNode*)node;
        node->values.push_back(newNode);
    }
    return (PUAbstractNode*)node;
}

std::string PUPropertyAbstractNode::getValue() const
{
    return name;
}

PUPropertyAbstractNode::~PUPropertyAbstractNode()
{
    for (auto iter : values){
        delete iter;
    }
}


PUAtomAbstractNode::PUAtomAbstractNode(PUAbstractNode *ptr)
:PUAbstractNode(ptr), id(0)
{
    type = ANT_ATOM;
}

PUAbstractNode *PUAtomAbstractNode::clone() const
{
    PUAtomAbstractNode *node = new (std::nothrow) PUAtomAbstractNode(parent);
    node->file = file;
    node->line = line;
    node->id = id;
    node->type = type;
    node->value = value;
    return node;
}

std::string PUAtomAbstractNode::getValue() const
{
    return value;
}




PUScriptCompiler::PUScriptCompiler():_current(nullptr),_nodes(nullptr), _PUParticleSystem3D(nullptr)
{
}
PUScriptCompiler::~PUScriptCompiler()
{
    for (auto iter : _compiledScripts){
        for (auto miter : iter.second){
            delete miter;
        }
    }
    _compiledScripts.clear();
}

bool PUScriptCompiler::compile(const PUConcreteNodeList &nodes, const std::string &file)
{
    if (nodes.empty()) return false;

    PUAbstractNodeList aNodes;
    convertToAST(nodes,aNodes);

    _compiledScripts[file] = aNodes;
    //for(PUAbstractNodeList::iterator i = aNodes.begin(); i != aNodes.end(); ++i)
    //{
    //    PUScriptTranslator *translator = PUTranslateManager::Instance()->getTranslator(*i);
    //    if(translator){
    //        if (translator->isParticleSystemTranslator())
    //        {
    //            PUParticleSystem3DTranslator *ps = static_cast<PUParticleSystem3DTranslator *>(translator);
    //            if (ps) ps->setParticleSystem3D(_PUParticleSystem3D);
    //        }
    //        translator->translate(this, *i);
    //    }
    //}

    //for (auto iter : aNodes){
    //    delete iter;
    //}
    return true;
}

const PUAbstractNodeList* PUScriptCompiler::compile(const std::string &file, bool &isFirstCompile)
{
    auto iter = _compiledScripts.find(file);
    if (iter != _compiledScripts.end()){
        isFirstCompile = false;
        return &iter->second;
    }

    std::string data = FileUtils::getInstance()->getStringFromFile(file);
    PUScriptLexer lexer;
    PUScriptParser parser;
    PUScriptTokenList tokenList;
    PUConcreteNodeList creteNodeList;
    lexer.openLexer(data, file, tokenList);
    parser.parse(creteNodeList, tokenList);
    bool state = compile(creteNodeList, file);

    for (auto iter1 : creteNodeList){
        delete iter1;
    }

    for (auto iter2 : tokenList){
        delete iter2;
    }

    isFirstCompile = true;
    if (state){
        return &_compiledScripts[file];
    }
    return nullptr;
}



void PUScriptCompiler::convertToAST(const PUConcreteNodeList &nodes,PUAbstractNodeList &aNodes)
{

    _current = NULL;
    _nodes = &aNodes;
    visitList(nodes);
}

//    CNT_VARIABLE,
//    CNT_VARIABLE_ASSIGN,
//    CNT_WORD,need handle
//    CNT_IMPORT,
//    CNT_QUOTE,
//    CNT_LBRACE,need handle
//    CNT_RBRACE,need handle
//    CNT_COLON

void PUScriptCompiler::visitList(const PUConcreteNodeList &nodes)
{
    for(const auto& node : nodes)
    {
        this->visit(node);
    }
}


void PUScriptCompiler::visit(PUConcreteNode *node)
{
    PUAbstractNode* asn = NULL;

    // Handle properties and objects here
    if(!node->children.empty())
    {
        // Grab the last two nodes
        PUConcreteNode* temp1 = NULL;
        PUConcreteNode* temp2 = NULL;
        PUConcreteNodeList::reverse_iterator iter = node->children.rbegin();
        if(iter != node->children.rend())
        {
            temp1 = *iter;
            ++iter;
        }
        if(iter != node->children.rend())
            temp2 = *iter;


        //brance inner
        if(temp1 && temp1->type == CNT_RBRACE && temp2 && temp2->type == CNT_LBRACE)
        {

            if(node->children.size() < 2)
            {
                return;
            }

            PUObjectAbstractNode *impl = new  (std::nothrow) PUObjectAbstractNode(_current);
            impl->line = node->line;
            impl->file = node->file;
            impl->abstract = false;

            std::list<PUConcreteNode*> temp;
            temp.push_back(node);
            for(const auto& child : node->children)
            {
                temp.push_back(child);
            }

            //add brance type//
            PUConcreteNodeList::const_iterator iter1 = temp.begin();
            impl->cls = (*iter1)->token;
            ++iter1;

            //add brance name//
            if(iter1 != temp.end() && ((*iter1)->type == CNT_WORD))
            {
                impl->name = (*iter1)->token;
                ++iter1;
            }

            while(iter1 != temp.end() && (*iter1)->type != CNT_LBRACE)
            {
                PUAtomAbstractNode *atom = new (std::nothrow) PUAtomAbstractNode(impl);
                atom->file = (*iter1)->file;
                atom->line = (*iter1)->line;
                atom->type = ANT_ATOM;
                atom->value = (*iter1)->token;
                impl->values.push_back(atom);
                ++iter1;
            }

            asn = impl;
            _current = impl;
            visitList(temp2->children);
            _current = impl->parent;
        }
        //no brance//
        else
        {
            PUPropertyAbstractNode *impl = new (std::nothrow) PUPropertyAbstractNode(_current);
            impl->line = node->line;
            impl->file = node->file;
            impl->name = node->token;

            asn = impl;
            _current = impl;

            // Visit the children of the {
            visitList(node->children);

            // Go back up the stack
            _current = impl->parent;
        }
    }
    else
    {
        PUAtomAbstractNode *impl = new (std::nothrow) PUAtomAbstractNode(_current);
        impl->line = node->line;
        impl->file = node->file;
        impl->value = node->token;
        asn = impl;
    }

    if(asn)
    {
        if(_current)
        {
            if(_current->type == ANT_PROPERTY)
            {
                PUPropertyAbstractNode *impl = reinterpret_cast<PUPropertyAbstractNode*>(_current);
                //PUAtomAbstractNode* assd = dynamic_cast<PUAtomAbstractNode*>(asn);
                impl->values.push_back(asn);
            }
            else
            {
                PUObjectAbstractNode *impl = reinterpret_cast<PUObjectAbstractNode*>(_current);
                impl->children.push_back(asn);
            }
        }
        else
        {
            _nodes->push_back(asn);
        }
    }
}

void PUScriptCompiler::setParticleSystem3D( PUParticleSystem3D *pu )
{
    _PUParticleSystem3D = pu;
}

PUScriptCompiler* PUScriptCompiler::Instance()
{
    static PUScriptCompiler psc;
    return &psc;
}

NS_CC_END
