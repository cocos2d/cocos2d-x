/*
 * Copyright (C) 2010 The Android Open Source Project
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

#ifndef SkPDFTypes_DEFINED
#define SkPDFTypes_DEFINED

#include "SkRefCnt.h"
#include "SkScalar.h"
#include "SkString.h"
#include "SkTDArray.h"
#include "SkTypes.h"

class SkPDFCatalog;
class SkWStream;

/** \class SkPDFObject

    A PDF Object is the base class for primitive elements in a PDF file.  A
    common subtype is used to ease the use of indirect object references,
    which are common in the PDF format.
*/
class SkPDFObject : public SkRefCnt {
public:
    /** Create a PDF object.
     */
    SkPDFObject();
    virtual ~SkPDFObject();

    /** Subclasses must implement this method to print the object to the
     *  PDF file.
     *  @param catalog  The object catalog to use.
     *  @param indirect If true, output an object identifier with the object.
     *  @param stream   The writable output stream to send the output to.
     */
    virtual void emitObject(SkWStream* stream, SkPDFCatalog* catalog,
                            bool indirect) = 0;

    /** Return the size (number of bytes) of this object in the final output
     *  file. Compound objects or objects that are computationally intensive
     *  to output should override this method.
     *  @param catalog  The object catalog to use.
     *  @param indirect If true, output an object identifier with the object.
     */
    virtual size_t getOutputSize(SkPDFCatalog* catalog, bool indirect);

    /** If this object explicitly depends on other objects, add them to the
     *  end of the list.  This only applies to higher level object, where
     *  the depenency is explicit and introduced by the class.  i.e. an
     *  SkPDFImage added to an SkPDFDevice, but not an SkPDFObjRef added to
     *  an SkPDFArray.
     *  @param resourceList  The list to append dependant resources to.
     */
    virtual void getResources(SkTDArray<SkPDFObject*>* resourceList);

    /** Helper function to output an indirect object.
     *  @param catalog The object catalog to use.
     *  @param stream  The writable output stream to send the output to.
     */
    void emitIndirectObject(SkWStream* stream, SkPDFCatalog* catalog);

    /** Helper function to find the size of an indirect object.
     *  @param catalog The object catalog to use.
     */
    size_t getIndirectOutputSize(SkPDFCatalog* catalog);
};

/** \class SkPDFObjRef

    An indirect reference to a PDF object.
*/
class SkPDFObjRef : public SkPDFObject {
public:
    /** Create a reference to an existing SkPDFObject.
     *  @param obj The object to reference.
     */
    explicit SkPDFObjRef(SkPDFObject* obj);
    virtual ~SkPDFObjRef();

    // The SkPDFObject interface.
    virtual void emitObject(SkWStream* stream, SkPDFCatalog* catalog,
                            bool indirect);
    virtual size_t getOutputSize(SkPDFCatalog* catalog, bool indirect);

private:
    SkRefPtr<SkPDFObject> fObj;
};

/** \class SkPDFInt

    An integer object in a PDF.
*/
class SkPDFInt : public SkPDFObject {
public:
    /** Create a PDF integer (usually for indirect reference purposes).
     *  @param value An integer value between 2^31 - 1 and -2^31.
     */
    explicit SkPDFInt(int32_t value);
    virtual ~SkPDFInt();

    // The SkPDFObject interface.
    virtual void emitObject(SkWStream* stream, SkPDFCatalog* catalog,
                            bool indirect);

private:
    int32_t fValue;
};

/** \class SkPDFBool

    An boolean value in a PDF.
*/
class SkPDFBool : public SkPDFObject {
public:
    /** Create a PDF boolean.
     *  @param value true or false.
     */
    explicit SkPDFBool(bool value);
    virtual ~SkPDFBool();

    // The SkPDFObject interface.
    virtual void emitObject(SkWStream* stream, SkPDFCatalog* catalog,
                            bool indirect);
    virtual size_t getOutputSize(SkPDFCatalog* catalog, bool indirect);

private:
    bool fValue;
};

/** \class SkPDFScalar

    A real number object in a PDF.
*/
class SkPDFScalar : public SkPDFObject {
public:
    /** Create a PDF real number.
     *  @param value A real value.
     */
    explicit SkPDFScalar(SkScalar value);
    virtual ~SkPDFScalar();

    static void Append(SkScalar value, SkWStream* stream);

    // The SkPDFObject interface.
    virtual void emitObject(SkWStream* stream, SkPDFCatalog* catalog,
                            bool indirect);

private:
    SkScalar fValue;
};

/** \class SkPDFString

    A string object in a PDF.
*/
class SkPDFString : public SkPDFObject {
public:
    /** Create a PDF string. Maximum length (in bytes) is 65,535.
     *  @param value A string value.
     */
    explicit SkPDFString(const char value[]);
    explicit SkPDFString(const SkString& value);

    /** Create a PDF string. Maximum length (in bytes) is 65,535.
     *  @param value     A string value.
     *  @param len       The length of value.
     *  @param wideChars Indicates if the top byte in value is significant and
     *                   should be encoded (true) or not (false).
     */
    SkPDFString(const uint16_t* value, size_t len, bool wideChars);
    virtual ~SkPDFString();

    // The SkPDFObject interface.
    virtual void emitObject(SkWStream* stream, SkPDFCatalog* catalog,
                            bool indirect);
    virtual size_t getOutputSize(SkPDFCatalog* catalog, bool indirect);

    static SkString formatString(const char* input, size_t len);
    static SkString formatString(const uint16_t* input, size_t len,
                                 bool wideChars);
private:
    static const size_t kMaxLen = 65535;

    const SkString fValue;

    static SkString doFormatString(const void* input, size_t len,
                                 bool wideInput, bool wideOutput);
};

/** \class SkPDFName

    A name object in a PDF.
*/
class SkPDFName : public SkPDFObject {
public:
    /** Create a PDF name object. Maximum length is 127 bytes.
     *  @param value The name.
     */
    explicit SkPDFName(const char name[]);
    explicit SkPDFName(const SkString& name);
    virtual ~SkPDFName();

    // The SkPDFObject interface.
    virtual void emitObject(SkWStream* stream, SkPDFCatalog* catalog,
                            bool indirect);
    virtual size_t getOutputSize(SkPDFCatalog* catalog, bool indirect);

private:
    static const size_t kMaxLen = 127;

    const SkString fValue;

    static SkString formatName(const SkString& input);
};

/** \class SkPDFArray

    An array object in a PDF.
*/
class SkPDFArray : public SkPDFObject {
public:
    /** Create a PDF array. Maximum length is 8191.
     */
    SkPDFArray();
    virtual ~SkPDFArray();

    // The SkPDFObject interface.
    virtual void emitObject(SkWStream* stream, SkPDFCatalog* catalog,
                            bool indirect);
    virtual size_t getOutputSize(SkPDFCatalog* catalog, bool indirect);

    /** The size of the array.
     */
    int size() { return fValue.count(); }

    /** Preallocate space for the given number of entries.
     *  @param length The number of array slots to preallocate.
     */
    void reserve(int length);

    /** Returns the object at the given offset in the array.
     *  @param index The index into the array to retrieve.
     */
    SkPDFObject* getAt(int index) { return fValue[index]; }

    /** Set the object at the given offset in the array. Ref's value.
     *  @param index The index into the array to set.
     *  @param value The value to add to the array.
     *  @return The value argument is returned.
     */
    SkPDFObject* setAt(int index, SkPDFObject* value);

    /** Append the object to the end of the array and increments its ref count.
     *  @param value The value to add to the array.
     *  @return The value argument is returned.
     */
    SkPDFObject* append(SkPDFObject* value);

private:
    static const int kMaxLen = 8191;
    SkTDArray<SkPDFObject*> fValue;
};

/** \class SkPDFDict

    A dictionary object in a PDF.
*/
class SkPDFDict : public SkPDFObject {
public:
    /** Create a PDF dictionary. Maximum number of entries is 4095.
     */
    SkPDFDict();

    /** Create a PDF dictionary with a Type entry.
     *  @param type   The value of the Type entry.
     */
    explicit SkPDFDict(const char type[]);

    virtual ~SkPDFDict();

    // The SkPDFObject interface.
    virtual void emitObject(SkWStream* stream, SkPDFCatalog* catalog,
                            bool indirect);
    virtual size_t getOutputSize(SkPDFCatalog* catalog, bool indirect);

    /** The size of the dictionary.
     */
    int size() { return fValue.count(); }

    /** Add the value to the dictionary with the given key.  Refs value.
     *  @param key   The key for this dictionary entry.
     *  @param value The value for this dictionary entry.
     *  @return The value argument is returned.
     */
    SkPDFObject* insert(SkPDFName* key, SkPDFObject* value);

    /** Add the value to the dictionary with the given key.  Refs value.  The
     *  method will create the SkPDFName object.
     *  @param key   The text of the key for this dictionary entry.
     *  @param value The value for this dictionary entry.
     *  @return The value argument is returned.
     */
    SkPDFObject* insert(const char key[], SkPDFObject* value);

    /** Remove all entries from the dictionary.
     */
    void clear();

private:
    static const int kMaxLen = 4095;

    struct Rec {
      SkPDFName* key;
      SkPDFObject* value;
    };

    SkTDArray<struct Rec> fValue;
};

#endif
