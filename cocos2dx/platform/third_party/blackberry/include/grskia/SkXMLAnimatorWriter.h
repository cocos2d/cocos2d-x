/* libs/graphics/animator/SkXMLAnimatorWriter.h
**
** Copyright 2006, The Android Open Source Project
**
** Licensed under the Apache License, Version 2.0 (the "License"); 
** you may not use this file except in compliance with the License. 
** You may obtain a copy of the License at 
**
**     http://www.apache.org/licenses/LICENSE-2.0 
**
** Unless required by applicable law or agreed to in writing, software 
** distributed under the License is distributed on an "AS IS" BASIS, 
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
** See the License for the specific language governing permissions and 
** limitations under the License.
*/

#ifndef SkXMLAnimatorWriter_DEFINED
#define SkXMLAnimatorWriter_DEFINED

#include "SkXMLWriter.h"

class SkAnimator;
class SkDisplayXMLParser;

class SkXMLAnimatorWriter : public SkXMLWriter {
public:
    SkXMLAnimatorWriter(SkAnimator*);
    virtual ~SkXMLAnimatorWriter();
    virtual void    writeHeader();
    SkDEBUGCODE(static void UnitTest(class SkCanvas* canvas);)
protected:
    virtual void onAddAttributeLen(const char name[], const char value[], size_t length);
    virtual void onEndElement();
    virtual void onStartElementLen(const char elem[], size_t length);
private:
    SkAnimator* fAnimator;
    SkDisplayXMLParser* fParser;
};

#endif // SkXMLAnimatorWriter_DEFINED

