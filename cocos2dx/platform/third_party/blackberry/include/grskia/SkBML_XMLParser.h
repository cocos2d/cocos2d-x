/*
 * Copyright (C) 2006 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SkBML_XMLParser_DEFINED
#define SkBML_XMLParser_DEFINED

class SkStream;
class SkWStream;
class SkXMLParser;
class SkXMLWriter;

class BML_XMLParser {
public:
    /** Read the byte XML stream and write the decompressed XML.
    */
    static void Read(SkStream& s, SkXMLWriter& writer);
    /** Read the byte XML stream and write the decompressed XML into a writable stream.
    */
    static void Read(SkStream& s, SkWStream& output);
    /** Read the byte XML stream and write the decompressed XML into an XML parser.
    */
    static void Read(SkStream& s, SkXMLParser& output);
};

#endif // SkBML_XMLParser_DEFINED

