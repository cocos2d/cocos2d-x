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

#ifndef SkPDFPage_DEFINED
#define SkPDFPage_DEFINED

#include "SkPDFTypes.h"
#include "SkPDFStream.h"
#include "SkRefCnt.h"
#include "SkTDArray.h"

class SkPDFCatalog;
class SkPDFDevice;
class SkWStream;

/** \class SkPDFPage

    A SkPDFPage contains meta information about a page, is used in the page
    tree and points to the content of the page.
*/
class SkPDFPage : public SkPDFDict {
public:
    /** Create a PDF page with the passed PDF device.  The device need not
     *  have content on it yet.
     *  @param content    The page content.
     */
    explicit SkPDFPage(const SkRefPtr<SkPDFDevice>& content);
    ~SkPDFPage();

    /** Before a page and its contents can be sized and emitted, it must
     *  be finalized.  No changes to the PDFDevice will be honored after
     *  finalizePage has been called.  This function adds the page content
     *  to the passed catalog, so it must be called for each document
     *  that the page is part of.
     *  @param catalog         The catalog to add page content objects to.
     *  @param firstPage       Indicate if this is the first page of a document.
     *  @param resourceObjects The resource objects used on the page are added
     *                         to this array.  This gives the caller a chance
     *                         to deduplicate resources across pages.
     */
    void finalizePage(SkPDFCatalog* catalog, bool firstPage,
                      SkTDArray<SkPDFObject*>* resourceObjects);

    /** Determine the size of the page content and store to the catalog
     *  the offsets of all nonresource-indirect objects that make up the page
     *  content.  This must be called before emitPage(), but after finalizePage.
     *  @param catalog    The catalog to add the object offsets to.
     *  @param fileOffset The file offset where the page content will be
     *                    emitted.
     */
    off_t getPageSize(SkPDFCatalog* catalog, off_t fileOffset);

    /** Output the page content to the passed stream.
     *  @param stream     The writable output stream to send the content to.
     *  @param catalog    The active object catalog.
     */
    void emitPage(SkWStream* stream, SkPDFCatalog* catalog);

    /** Generate a page tree for the passed vector of pages.  New objects are
     *  added to the catalog.  The pageTree vector is populated with all of
     *  the 'Pages' dictionaries as well as the 'Page' objects.  Page trees
     *  have both parent and children links, creating reference cycles, so
     *  it must be torn down explicitly.  The first page is not added to
     *  the pageTree dictionary array so the caller can handle it specially.
     *  @param pages      The ordered vector of page objects.
     *  @param catalog    The catalog to add new objects into.
     *  @param pageTree   An output vector with all of the internal and leaf
     *                    nodes of the pageTree.
     *  @param rootNode   An output parameter set to the root node.
     */
    static void generatePageTree(const SkTDArray<SkPDFPage*>& pages,
                                 SkPDFCatalog* catalog,
                                 SkTDArray<SkPDFDict*>* pageTree,
                                 SkPDFDict** rootNode);

    /** Get the fonts used on this page.
     */
    SK_API const SkTDArray<SkPDFFont*>& getFontResources() const;

private:
    // Multiple pages may reference the content.
    SkRefPtr<SkPDFDevice> fDevice;

    // Once the content is finalized, put it into a stream for output.
    SkRefPtr<SkPDFStream> fContentStream;
};

#endif
