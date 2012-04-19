/* libs/graphics/xml/SkBML_Verbs.h
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

#ifndef SkBML_Verbs_DEFINED
#define SkBML_Verbs_DEFINED

enum Verbs {
    kStartElem_Value_Verb,
    kStartElem_Index_Verb,
    kEndElem_Verb,
    kAttr_Value_Value_Verb,
    kAttr_Value_Index_Verb,
    kAttr_Index_Value_Verb,
    kAttr_Index_Index_Verb,

    kVerbCount
};

#endif // SkBML_Verbs_DEFINED
