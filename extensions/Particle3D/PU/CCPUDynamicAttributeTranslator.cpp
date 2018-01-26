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

#include "CCPUDynamicAttributeTranslator.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"

NS_CC_BEGIN
PUDynamicAttributeTranslator::PUDynamicAttributeTranslator()
{
    
}

PUDynamicAttributeTranslator::~PUDynamicAttributeTranslator()
{
    
}

void PUDynamicAttributeTranslator::translate(PUScriptCompiler* compiler, PUAbstractNode *node)
{
    PUObjectAbstractNode* obj = reinterpret_cast<PUObjectAbstractNode*>(node);

    // The first value is the type
    std::string type = obj->name;

    if (type == token[TOKEN_DYN_RANDOM])
    {
        _dynamicAttribute = new (std::nothrow) PUDynamicAttributeRandom();
    }
    else if (type == token[TOKEN_DYN_CURVED_LINEAR])
    {
        _dynamicAttribute = new (std::nothrow) PUDynamicAttributeCurved();
    }
    else if (type == token[TOKEN_DYN_CURVED_SPLINE])
    {
        _dynamicAttribute = new (std::nothrow) PUDynamicAttributeCurved();
    }
    else if (type == token[TOKEN_DYN_OSCILLATE])
    {
        _dynamicAttribute = new (std::nothrow) PUDynamicAttributeOscillate();
    }
    else
    {
        // Create a fixed one.
        _dynamicAttribute = new (std::nothrow) PUDynamicAttributeFixed();
    }

    // Run through properties
    for(PUAbstractNodeList::iterator i = obj->children.begin(); i != obj->children.end(); ++i)
    {
        if((*i)->type == ANT_PROPERTY)
        {
            PUPropertyAbstractNode* prop = reinterpret_cast<PUPropertyAbstractNode*>((*i));
            if (prop->name == token[TOKEN_DYN_MIN])
            {
                // Property: min
                if (_dynamicAttribute->getType() == PUDynamicAttribute::DAT_RANDOM)
                {
                    if (passValidateProperty(compiler, prop, token[TOKEN_DYN_MIN], VAL_REAL))
                    {
                        float val = 0.0f;
                        if(getFloat(*prop->values.front(), &val))
                        {
                            (static_cast<PUDynamicAttributeRandom*>(_dynamicAttribute))->setMin(val);
                        }
                    }
                }
            }
            else if (prop->name == token[TOKEN_DYN_MAX])
            {
                // Property: max
                if (_dynamicAttribute->getType() == PUDynamicAttribute::DAT_RANDOM)
                {
                    if (passValidateProperty(compiler, prop, token[TOKEN_DYN_MAX], VAL_REAL))
                    {
                        float val = 0.0f;
                        if(getFloat(*prop->values.front(), &val))
                        {
                            (static_cast<PUDynamicAttributeRandom*>(_dynamicAttribute))->setMax(val);
                        }
                    }
                }
            }
            else if (prop->name == token[TOKEN_DYN_CONTROL_POINT])
            {
                // Property: control_point
                if (_dynamicAttribute->getType() == PUDynamicAttribute::DAT_CURVED)
                {
                    if (passValidateProperty(compiler, prop, token[TOKEN_DYN_CONTROL_POINT], VAL_VECTOR2))
                    {
                        Vec2 val;
                        if(getVector2(prop->values.begin(), prop->values.end(), &val))
                        {
                            (static_cast<PUDynamicAttributeCurved*>(_dynamicAttribute))->addControlPoint(val.x, val.y);
                        }
                    }
                }
            }
            else if (prop->name == token[TOKEN_DYN_OSCILLATE_FREQUENCY])
            {
                // Property: oscillate_frequency
                if (_dynamicAttribute->getType() == PUDynamicAttribute::DAT_OSCILLATE)
                {
                    if (passValidateProperty(compiler, prop, token[TOKEN_DYN_OSCILLATE_FREQUENCY], VAL_REAL))
                    {
                        float val = 0.0f;
                        if(getFloat(*prop->values.front(), &val))
                        {
                            (static_cast<PUDynamicAttributeOscillate*>(_dynamicAttribute))->setFrequency(val);
                        }
                    }
                }
            }
            else if (prop->name == token[TOKEN_DYN_OSCILLATE_PHASE])
            {
                // Property: oscillate_phase
                if (_dynamicAttribute->getType() == PUDynamicAttribute::DAT_OSCILLATE)
                {
                    if (passValidateProperty(compiler, prop, token[TOKEN_DYN_OSCILLATE_PHASE], VAL_REAL))
                    {
                        float val = 0.0f;
                        if(getFloat(*prop->values.front(), &val))
                        {
                            (static_cast<PUDynamicAttributeOscillate*>(_dynamicAttribute))->setPhase(val);
                        }
                    }
                }
            }
            else if (prop->name == token[TOKEN_DYN_OSCILLATE_BASE])
            {
                // Property: oscillate_base
                if (_dynamicAttribute->getType() == PUDynamicAttribute::DAT_OSCILLATE)
                {
                    if (passValidateProperty(compiler, prop, token[TOKEN_DYN_OSCILLATE_BASE], VAL_REAL))
                    {
                        float val = 0.0f;
                        if(getFloat(*prop->values.front(), &val))
                        {
                            (static_cast<PUDynamicAttributeOscillate*>(_dynamicAttribute))->setBase(val);
                        }
                    }
                }
            }
            else if (prop->name == token[TOKEN_DYN_OSCILLATE_AMPLITUDE])
            {
                // Property: oscillate_amplitude
                if (_dynamicAttribute->getType() == PUDynamicAttribute::DAT_OSCILLATE)
                {
                    if (passValidateProperty(compiler, prop, token[TOKEN_DYN_OSCILLATE_AMPLITUDE], VAL_REAL))
                    {
                        float val = 0.0f;
                        if(getFloat(*prop->values.front(), &val))
                        {
                            (static_cast<PUDynamicAttributeOscillate*>(_dynamicAttribute))->setAmplitude(val);
                        }
                    }
                }
            }
            else if (prop->name == token[TOKEN_DYN_OSCILLATE_TYPE])
            {
                // Property: oscillate_type
                if (_dynamicAttribute->getType() == PUDynamicAttribute::DAT_OSCILLATE)
                {
                    if (passValidateProperty(compiler, prop, token[TOKEN_DYN_OSCILLATE_TYPE], VAL_STRING))
                    {
                        std::string val;
                        if(getString(*prop->values.front(), &val))
                        {
                            if (val == token[TOKEN_DYN_SINE])
                            {
                                (static_cast<PUDynamicAttributeOscillate*>(_dynamicAttribute))->setOscillationType(
                                    PUDynamicAttributeOscillate::OSCT_SINE);
                            }
                            else if (val == token[TOKEN_DYN_SQUARE])
                            {
                                (static_cast<PUDynamicAttributeOscillate*>(_dynamicAttribute))->setOscillationType(
                                    PUDynamicAttributeOscillate::OSCT_SQUARE);
                            }
                        }
                    }
                }
            }
            else
            {
                errorUnexpectedProperty(compiler, prop);
            }

        }
        else if((*i)->type == ANT_OBJECT)
        {
            processNode(compiler, *i);
        }
        else
        {
            errorUnexpectedToken(compiler, *i);
        }
    }

    // Set it in the context
    obj->context = _dynamicAttribute;
}



NS_CC_END
