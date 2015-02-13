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

#ifndef __CC_PU_SCRIPT_COMPILER_H__
#define __CC_PU_SCRIPT_COMPILER_H__
#include "base/CCRef.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticle3DScriptParser.h"

NS_CC_BEGIN

/** This enum holds the types of the possible abstract nodes */
enum PUAbstractNodeType
{
    ANT_UNKNOWN,
    ANT_ATOM,
    ANT_OBJECT,
    ANT_PROPERTY,
    ANT_IMPORT,
    ANT_VARIABLE_SET,
    ANT_VARIABLE_ACCESS
};
class PUAbstractNode;
typedef std::list<PUAbstractNode*> PUAbstractNodeList;

class PUAbstractNode
{
public:
    std::string file;
    unsigned int line;
    PUAbstractNodeType type;
    PUAbstractNode *parent;
    Ref *context;
    
    //contextd//
//    Any context; // A holder for translation context data
public:
    PUAbstractNode(PUAbstractNode *ptr):line(0), type(ANT_UNKNOWN), parent(ptr), context(nullptr)
    {


    }
    virtual ~PUAbstractNode(){}
    /// Returns a new AbstractNode which is a replica of this one.
    virtual PUAbstractNode *clone() const = 0;
    /// Returns a string value depending on the type of the AbstractNode.
    virtual std::string getValue() const = 0;
};



/** This specific abstract node represents a script object */
class PUObjectAbstractNode : public PUAbstractNode
{
private:
    std::map<std::string,std::string> _env;
public:
    std::string name, cls;
    std::vector<std::string> bases;
    unsigned int id;
    bool abstract;
    PUAbstractNodeList children;
    PUAbstractNodeList values;
    PUAbstractNodeList overrides; // For use when processing object inheritance and overriding
public:
    PUObjectAbstractNode(PUAbstractNode *ptr);
    virtual ~PUObjectAbstractNode();
    PUAbstractNode *clone() const;
    std::string getValue() const;
    
    
    void addVariable(const std::string &name);
    void setVariable(const std::string &name, const std::string &value);
    std::pair<bool,std::string> getVariable(const std::string &name) const;
    const std::map<std::string,std::string> &getVariables() const;
};

/** This abstract node represents a script property */
class  PUPropertyAbstractNode : public PUAbstractNode
{
public:
    std::string name;
    unsigned int id;
    PUAbstractNodeList values;
public:
    PUPropertyAbstractNode(PUAbstractNode *ptr);
    virtual ~PUPropertyAbstractNode();
    PUAbstractNode *clone() const;
    std::string getValue() const;
};

/** This is an abstract node which cannot be broken down further */
class PUAtomAbstractNode : public PUAbstractNode
{
public:
    std::string value;
    unsigned int id;
public:
    PUAtomAbstractNode(PUAbstractNode *ptr);
    PUAbstractNode *clone() const;
    std::string getValue() const;
private:
    void parseNumber() const;
};

class PUParticleSystem3D;
class PUScriptCompiler
{

private:
    bool compile(const PUConcreteNodeList &nodes, const std::string &file);
    //is it excluded?//
    bool isNameExcluded(const std::string &cls, PUAbstractNode *parent);
    
public:
    typedef std::map<std::string,unsigned int> IdMap;
    
    static PUScriptCompiler* Instance();

    void setParticleSystem3D(PUParticleSystem3D *pu);

    const PUAbstractNodeList* compile(const std::string &file, bool &isFirstCompile);
    
    void convertToAST(const PUConcreteNodeList &nodes,PUAbstractNodeList &aNodes);
    
    std::map<std::string,std::string> env;
    
private:
    PUScriptCompiler();
    virtual ~PUScriptCompiler();

    void visitList(const PUConcreteNodeList &nodes);
    void visit(PUConcreteNode *node);
private:
    
    std::map<std::string, PUAbstractNodeList> _compiledScripts;
    PUAbstractNode *_current;
    PUAbstractNodeList *_nodes;
    PUParticleSystem3D *_puSystem;
};


NS_CC_END

#endif /* defined(__ssaafsdf__CCScriptCompile__) */
