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

#include "CCPUScriptTranslator.h"
#include "extensions/Particle3D/PU/CCPUTranslateManager.h"

NS_CC_BEGIN
PUScriptTranslator::PUScriptTranslator(void)
{
}

PUScriptTranslator::~PUScriptTranslator(void)
{
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

bool PUScriptTranslator::getFloat(const PUAbstractNode &node, float *result)
{
    if(node.type != ANT_ATOM)
        return false;
    
    PUAtomAbstractNode *atom = (PUAtomAbstractNode*)(&node);
    int n = sscanf(atom->value.c_str(), "%f", result);
    if(n == 0 || n == EOF)
        return false; // Conversion failed
    
    return true;
}

bool PUScriptTranslator::getInt(const PUAbstractNode &node, int *result)
{
    if(node.type != ANT_ATOM)
        return false;
    
    PUAtomAbstractNode *atom = (PUAtomAbstractNode*)&node;
    int n = sscanf(atom->value.c_str(), "%d", result);
    if(n == 0 || n == EOF)
        return false; // Conversion failed
    
    return true;
}

bool PUScriptTranslator::getUInt(const PUAbstractNode &node, unsigned int *result)
{
    if(node.type != ANT_ATOM)
        return false;
    
    PUAtomAbstractNode *atom = (PUAtomAbstractNode*)&node;
    int n = sscanf(atom->value.c_str(), "%u", result);
    if(n == 0 || n == EOF)
        return false; // Conversion failed
    return true;
}

bool PUScriptTranslator::getBoolean(const PUAbstractNode &node, bool *result)
{
    if(node.type != ANT_ATOM)
        return false;
    PUAtomAbstractNode *atom = (PUAtomAbstractNode*)&node;
    //if(atom->id != 1 && atom->id != 2)
    //    return false;
    
    *result = atom->value == "true" ? true : false;
    return true;
}

bool PUScriptTranslator::getString( const PUAbstractNode &node, std::string *result )
{
    if(node.type != ANT_ATOM)
        return false;
    PUAtomAbstractNode *atom = (PUAtomAbstractNode*)&node;
    *result = atom->value;
    return true;
}

bool PUScriptTranslator::getVector2(PUAbstractNodeList::const_iterator i,
                                  PUAbstractNodeList::const_iterator end,
                                  Vec2* result,
                                  int maxEntries)
{
    int n = 0;
    while(i != end && n < maxEntries)
    {
        float v = 0;
        if(getFloat(**i, &v))
        {
            switch(n)
            {
                case 0:
                    result->x = v;
                    break;
                case 1:
                    result->y = v;
                    break;
            }
        }
        else
        {
            return false;
        }
        ++n;
        ++i;
    }
    // return error if we found less than xy before end, unless constrained
    return (n >= 2 || n == maxEntries);
}
//-------------------------------------------------------------------------
bool PUScriptTranslator::getVector3(PUAbstractNodeList::const_iterator i,
                                  PUAbstractNodeList::const_iterator end,
                                  Vec3* result,
                                  int maxEntries)
{
    int n = 0;
    while(i != end && n < maxEntries)
    {
        float v = 0;
        if(getFloat(**i, &v))
        {
            switch(n)
            {
                case 0:
                    result->x = v;
                    break;
                case 1:
                    result->y = v;
                    break;
                case 2:
                    result->z = v;
                    break;
            }
        }
        else
        {
            return false;
        }
        ++n;
        ++i;
    }
    // return error if we found less than xyz before end, unless constrained
    return (n >= 3 || n == maxEntries);
}
//-------------------------------------------------------------------------
bool PUScriptTranslator::getVector4(PUAbstractNodeList::const_iterator i,
                                  PUAbstractNodeList::const_iterator end,
                                  Vec4* result,
                                  int maxEntries)
{
    int n = 0;
    while(i != end && n < maxEntries)
    {
        float v = 0;
        if(getFloat(**i, &v))
        {
            switch(n)
            {
                case 0:
                    result->x = v;
                    break;
                case 1:
                    result->y = v;
                    break;
                case 2:
                    result->z = v;
                    break;
                case 3:
                    result->w = v;
                    break;
            }
        }
        else
        {
            return false;
        }
        ++n;
        ++i;
    }
    // return error if we found less than xyz before end, unless constrained
    return (n >= 4 || n == maxEntries);
}
//-------------------------------------------------------------------------
bool PUScriptTranslator::getQuaternion(PUAbstractNodeList::const_iterator i,
                                     PUAbstractNodeList::const_iterator end,
                                     Quaternion* result,
                                     int maxEntries)
{
    int n = 0;
    while(i != end && n < maxEntries)
    {
        float v = 0;
        if(getFloat(**i, &v))
        {
            switch(n)
            {
                case 0:
                    result->w = v;
                    break;
                case 1:
                    result->x = v;
                    break;
                case 2:
                    result->y = v;
                    break;
                case 3:
                    result->z = v;
                    break;
            }
        }
        else
        {
            return false;
        }
        ++n;
        ++i;
    }
    // return error if we found less than xyz before end, unless constrained
    return (n >= 4 || n == maxEntries);
}
//-------------------------------------------------------------------------
bool PUScriptTranslator::passValidateProperty(PUScriptCompiler* compiler,
                                            PUPropertyAbstractNode* prop,
                                            const std::string& token2,
                                            ValidationType validationType)
{
    if (!passValidatePropertyNoValues(compiler, prop, token2))
    {
        return false;
    }
    
    bool ret = true;
    switch(validationType)
    {
        case VAL_BOOL:
        {
            ret = passValidatePropertyNumberOfValues(compiler, prop, token2, 1) && passValidatePropertyValidBool(compiler, prop);
        }
            break;
        case VAL_COLOURVALUE:
        {
            ret = passValidatePropertyNumberOfValuesRange(compiler, prop, token2, 3, 4);
        }
            break;
        case VAL_INT:
        {
            ret = passValidatePropertyNumberOfValues(compiler, prop, token2, 1) && passValidatePropertyValidInt(compiler, prop);
        }
            break;
        case VAL_QUATERNION:
        {
            ret = passValidatePropertyNumberOfValues(compiler, prop, token2, 4) && passValidatePropertyValidQuaternion(compiler, prop);
        }
            break;
        case VAL_REAL:
        {
            ret = passValidatePropertyNumberOfValues(compiler, prop, token2, 1) && passValidatePropertyValidReal(compiler, prop);
        }
            break;
        case VAL_STRING:
        {
            ret = passValidatePropertyNumberOfValues(compiler, prop, token2, 1);
        }
            break;
        case VAL_UINT:
        {
            ret = passValidatePropertyNumberOfValues(compiler, prop, token2, 1) && passValidatePropertyValidUint(compiler, prop);
        }
            break;
        case VAL_VECTOR2:
        {
            ret = passValidatePropertyNumberOfValues(compiler, prop, token2, 2) && passValidatePropertyValidVector2(compiler, prop);
        }
            break;
        case VAL_VECTOR3:
        {
            ret = passValidatePropertyNumberOfValues(compiler, prop, token2, 3) && passValidatePropertyValidVector3(compiler, prop);
        }
            break;
        case VAL_VECTOR4:
        {
            ret = passValidatePropertyNumberOfValues(compiler, prop, token2, 4) && passValidatePropertyValidVector4(compiler, prop);
        }
            break;
    }
    
    return ret;
}

//-------------------------------------------------------------------------
bool PUScriptTranslator::passValidatePropertyNoValues(PUScriptCompiler* /*compiler*/,
                                                    PUPropertyAbstractNode* prop,
                                                    const std::string& /*token2*/)
{
    if(prop->values.empty())
    {
//        compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, prop->file, prop->line, "PU Compiler: No values found for " + token2 + ".");
        return false;
    }
    return true;
}
//-------------------------------------------------------------------------
bool PUScriptTranslator::passValidatePropertyNumberOfValues(PUScriptCompiler* /*compiler*/,
                                                          PUPropertyAbstractNode* prop,
                                                          const std::string& /*token2*/,
                                                          unsigned short numberOfValues)
{
    if(prop->values.size() > numberOfValues)
    {
        return false;
    }
    return true;
}
//-------------------------------------------------------------------------
bool PUScriptTranslator::passValidatePropertyNumberOfValuesRange(PUScriptCompiler* /*compiler*/,
                                                               PUPropertyAbstractNode* prop,
                                                               const std::string& /*token2*/,
                                                               unsigned short minNumberOfValues,
                                                               unsigned short maxNumberOfValues)
{
    if(prop->values.size() < minNumberOfValues || prop->values.size() > maxNumberOfValues)
    {
        return false;
    }
    return true;
}
//-------------------------------------------------------------------------
bool PUScriptTranslator::passValidatePropertyValidReal(PUScriptCompiler* /*compiler*/,
                                                     PUPropertyAbstractNode* prop)
{
    float val = 0.0f;
    if(getFloat(*(prop->values.front()), &val))
    {
        return true;
    }
    
//    compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, prop->file, prop->line,
//                       "PU Compiler: " + prop->values.front()->getValue() + " is not a valid Real");
    return false;
}

//-------------------------------------------------------------------------
bool PUScriptTranslator::passValidatePropertyValidInt(PUScriptCompiler* /*compiler*/,
                                                    PUPropertyAbstractNode* prop)
{
    int val = 0;
    if(getInt(*prop->values.front(), &val))
    {
        return true;
    }
    
//    compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, prop->file, prop->line,
//                       "PU Compiler: " + prop->values.front()->getValue() + " is not a valid int");
    return false;
}
//-------------------------------------------------------------------------
bool PUScriptTranslator::passValidatePropertyValidUint(PUScriptCompiler* /*compiler*/,
                                                     PUPropertyAbstractNode* prop)
{
    unsigned int val = 0;
    if(getUInt(*prop->values.front(), &val))
    {
        return true;
    }
    
//    compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, prop->file, prop->line,
//                       "PU Compiler: " + prop->values.front()->getValue() + " is not a valid uint");
    return false;
}

//-------------------------------------------------------------------------
bool PUScriptTranslator::passValidatePropertyValidBool(PUScriptCompiler* /*compiler*/,
                                                     PUPropertyAbstractNode* prop)
{
    bool val;
    if(getBoolean(*prop->values.front(), &val))
    {
        return true;
    }
    
//    compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, prop->file, prop->line,
//                       "PU Compiler: " + prop->values.front()->getValue() + " is not a valid bool");
    return false;
}
//-------------------------------------------------------------------------
bool PUScriptTranslator::passValidatePropertyValidVector2(PUScriptCompiler* /*compiler*/,
                                                        PUPropertyAbstractNode* prop)
{
    Vec2 val;
    if(getVector2(prop->values.begin(), prop->values.end(), &val))
    {
        return true;
    }
    
//    compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, prop->file, prop->line,
//                       "PU Compiler: " + prop->values.front()->getValue() + " is not a valid Vector2");
    return false;
}
//-------------------------------------------------------------------------
bool PUScriptTranslator::passValidatePropertyValidVector3(PUScriptCompiler* /*compiler*/,
                                                        PUPropertyAbstractNode* prop)
{
    Vec3 val;
    if(getVector3(prop->values.begin(), prop->values.end(), &val))
    {
        return true;
    }
    
//    compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, prop->file, prop->line,
//                       "PU Compiler: " + prop->values.front()->getValue() + " is not a valid Vector3");
    return false;
}
//-------------------------------------------------------------------------
bool PUScriptTranslator::passValidatePropertyValidVector4(PUScriptCompiler* /*compiler*/,
                                                        PUPropertyAbstractNode* prop)
{
    Vec4 val;
    if(getVector4(prop->values.begin(), prop->values.end(), &val))
    {
        return true;
    }
    
//    compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, prop->file, prop->line,
//                       "PU Compiler: " + prop->values.front()->getValue() + " is not a valid Vector4");
    return false;
}
//-------------------------------------------------------------------------
bool PUScriptTranslator::passValidatePropertyValidQuaternion(PUScriptCompiler* /*compiler*/,
                                                           PUPropertyAbstractNode* prop)
{
    Quaternion val;
    if(getQuaternion(prop->values.begin(), prop->values.end(), &val))
    {
        return true;
    }
    
//    compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, prop->file, prop->line,
//                       "PU Compiler: " + prop->values.front()->getValue() + " is not a valid Quaternion");
    return false;
}
//-------------------------------------------------------------------------
void PUScriptTranslator::errorUnexpectedToken(PUScriptCompiler* /*compiler*/,
                                            PUAbstractNode* /*token2*/)
{
//    CCLOGERROR("PU Compiler: token2 is not recognized tokenFile:%s tokenLine:%s",)
//    printf()
//    compiler->addError(ScriptCompiler::CE_UNEXPECTEDTOKEN, token.getPointer()->file, token.getPointer()->line, 
//                       );
}
//-------------------------------------------------------------------------
void PUScriptTranslator::errorUnexpectedProperty(PUScriptCompiler* /*compiler*/,
                                               PUPropertyAbstractNode* /*prop*/)
{
//    compiler->addError(ScriptCompiler::CE_UNEXPECTEDTOKEN, prop->file, prop->line, 
//                       "PU Compiler: token \"" + prop->name + "\" is not recognized");
}

void PUScriptTranslator::processNode( PUScriptCompiler *compiler, PUAbstractNode *node )
{
    if(node->type != ANT_OBJECT)
        return;

    // Abstract objects are completely skipped
    if((reinterpret_cast<PUObjectAbstractNode*>(node))->abstract)
        return;

    // Retrieve the translator to use
    PUScriptTranslator *translator = PUTranslateManager::Instance()->getTranslator(node);

    if(translator)
        translator->translate(compiler, node);
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

NS_CC_END
