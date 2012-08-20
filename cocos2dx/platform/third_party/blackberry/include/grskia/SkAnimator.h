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

#ifndef SkAnimator_DEFINED
#define SkAnimator_DEFINED

#include "SkScalar.h"
#include "SkKey.h"
#include "SkEventSink.h"

class SkAnimateMaker;
class SkCanvas;
class SkDisplayable;
class SkEvent;
class SkExtras;
struct SkMemberInfo;
class SkPaint;
struct SkRect;
class SkStream;
class SkTypedArray;
class SkXMLParserError;
class SkDOM;
struct SkDOMNode;

/** SkElementType is the type of element: a rectangle, a color, an animator, and so on.
    This enum is incomplete and will be fleshed out in a future release */
enum SkElementType {
    kElementDummyType
};
/** SkFieldType is the type of field: a scalar, a string, an integer, a boolean, and so on.
    This enum is incomplete and will be fleshed out in a future release */
enum SkFieldType {
    kFieldDummyType
};

/** \class SkAnimator

    The SkAnimator class decodes an XML stream into a display list. The
    display list can be drawn statically as a picture, or can drawn 
    different elements at different times to form a moving animation.

    SkAnimator does not read the system time on its own; it relies on the
    caller to pass the current time. The caller can pause, speed up, or
    reverse the animation by varying the time passed in.

    The XML describing the display list must conform to the schema 
    described by SkAnimateSchema.xsd. 

    The XML must contain an <event> element to draw. Usually, it contains
    an <event kind="onload" /> block to add some drawing elements to the
    display list when the document is first decoded.

    Here's an "Hello World" XML sample:

    <screenplay>
        <event kind="onload" >
            <text text="Hello World" y="20" />
        </event>
    </screenplay>

    To read and draw this sample:

        // choose one of these two
        SkAnimator animator; // declare an animator instance on the stack
    //  SkAnimator* animator = new SkAnimator() // or one could instantiate the class

        // choose one of these three
        animator.decodeMemory(buffer, size); // to read from RAM
        animator.decodeStream(stream); // to read from a user-defined stream (e.g., a zip file)
        animator.decodeURI(filename); // to read from a web location, or from a local text file

        // to draw to the current window:
        SkCanvas canvas(getBitmap()); // create a canvas
        animator.draw(canvas, &paint, 0); // draw the scene
*/
class SkAnimator : public SkEventSink {
public:
    SkAnimator();
    virtual ~SkAnimator();

    /** Add a drawable extension to the graphics engine. Experimental. 
        @param extras A derived class that implements methods that identify and instantiate the class
    */
    void addExtras(SkExtras* extras);

    /** Read in XML from a stream, and append it to the current
        animator. Returns false if an error was encountered.
        Error diagnostics are stored in fErrorCode and fLineNumber.
        @param stream  The stream to append.
        @return true if the XML was parsed successfully.
    */
    bool appendStream(SkStream* stream);

    /** Read in XML from memory. Returns true if the file can be 
        read without error. Returns false if an error was encountered.
        Error diagnostics are stored in fErrorCode and fLineNumber.
        @param buffer  The XML text as UTF-8 characters.
        @param size  The XML text length in bytes.
        @return true if the XML was parsed successfully.
    */
    bool decodeMemory(const void* buffer, size_t size);

    /** Read in XML from a stream. Returns true if the file can be 
        read without error. Returns false if an error was encountered.
        Error diagnostics are stored in fErrorCode and fLineNumber.
        @param stream  The stream containg the XML text as UTF-8 characters.
        @return true if the XML was parsed successfully.
    */
    virtual bool decodeStream(SkStream* stream);

    /** Parse the DOM tree starting at the specified node. Returns true if it can be 
        parsed without error. Returns false if an error was encountered.
        Error diagnostics are stored in fErrorCode and fLineNumber.
        @return true if the DOM was parsed successfully.
    */
    virtual bool decodeDOM(const SkDOM&, const SkDOMNode*);

    /** Read in XML from a URI. Returns true if the file can be 
        read without error. Returns false if an error was encountered.
        Error diagnostics are stored in fErrorCode and fLineNumber.
        @param uri The complete url path to be read (either ftp, http or https).
        @return true if the XML was parsed successfully.
    */
    bool decodeURI(const char uri[]);

    /** Pass a char event, usually a keyboard symbol, to the animator.
        This triggers events of the form <event kind="keyChar" key="... />
        @param ch  The character to match against <event> element "key" 
            attributes.
        @return true if the event was dispatched successfully.
    */
    bool doCharEvent(SkUnichar ch);

    /** Experimental:
        Pass a mouse click event along with the mouse coordinates to 
        the animator. This triggers events of the form <event kind="mouseDown" ... />
        and other mouse events.
        @param state The mouse state, described by SkView::Click::State : values are
        down == 0, moved == 1, up == 2
        @param x    The x-position of the mouse
        @param y The y-position of the mouse
        @return true if the event was dispatched successfully.
    */
    bool doClickEvent(int state, SkScalar x, SkScalar y);

    /** Pass a meta-key event, such as an arrow , to the animator.
        This triggers events of the form <event kind="keyPress" code="... />
        @param code  The key to match against <event> element "code" 
            attributes.
        @return true if the event was dispatched successfully.
    */
    bool doKeyEvent(SkKey code);
    bool doKeyUpEvent(SkKey code);
    
    /** Send an event to the animator. The animator's clock is set 
        relative to the current time.
        @return true if the event was dispatched successfully.
    */
    bool doUserEvent(const SkEvent& evt);

    /** The possible results from the draw function. 
    */
    enum DifferenceType {
        kNotDifferent,
        kDifferent,
        kPartiallyDifferent
    };
    /** Draws one frame of the animation. The first call to draw always 
        draws the initial frame of the animation. Subsequent calls draw 
        the offset into the animation by 
        subtracting the initial time from the current time.
        @param canvas  The canvas to draw into.
        @param paint     The paint to draw with.
        @param time  The offset into the current animation.
        @return kNotDifferent if there are no active animations; kDifferent if there are active animations; and
        kPartiallyDifferent if the document contains an active <bounds> element that specifies a minimal 
        redraw area.
    */
    DifferenceType draw(SkCanvas* canvas, SkPaint* paint, SkMSec time);

    /** Draws one frame of the animation, using a new Paint each time.
        The first call to draw always 
        draws the initial frame of the animation. Subsequent calls draw 
        the offset into the animation by 
        subtracting the initial time from the current time.
        @param canvas  The canvas to draw into.
        @param time  The offset into the current animation.
        @return kNotDifferent if there are no active animations; kDifferent if there are active animations; and
        kPartiallyDifferent if the document contains an active <bounds> element that specifies a minimal 
        redraw area.
    */
    DifferenceType draw(SkCanvas* canvas, SkMSec time);

    /** Experimental:
        Helper to choose whether to return a SkView::Click handler.
        @param x ignored
        @param y ignored
        @return true if a mouseDown event handler is enabled.
    */
    bool findClickEvent(SkScalar x, SkScalar y); 


    /** Get the nested animator associated with this element, if any.
        Use this to access a movie's event sink, to send events to movies.
        @param element the value returned by getElement
        @return the internal animator.
    */
    const SkAnimator* getAnimator(const SkDisplayable* element) const;

    /** Returns the scalar value of the specified element's attribute[index]
        @param element the value returned by getElement
        @param field the value returned by getField
        @param index the array entry
        @return the integer value to retrieve, or SK_NaN32 if unsuccessful
    */
    int32_t getArrayInt(const SkDisplayable* element, const SkMemberInfo* field, int index);

    /** Returns the scalar value of the specified element's attribute[index]
        @param elementID is the value of the id attribute in the XML of this element
        @param fieldName specifies the name of the attribute  
        @param index the array entry
        @return the integer value to retrieve, or SK_NaN32 if unsuccessful
    */
    int32_t getArrayInt(const char* elementID, const char* fieldName, int index);

    /** Returns the scalar value of the specified element's attribute[index]
        @param element the value returned by getElement
        @param field the value returned by getField
        @param index the array entry
        @return the scalar value to retrieve, or SK_ScalarNaN if unsuccessful
    */
    SkScalar getArrayScalar(const SkDisplayable* element, const SkMemberInfo* field, int index);

    /** Returns the scalar value of the specified element's attribute[index]
        @param elementID is the value of the id attribute in the XML of this element
        @param fieldName specifies the name of the attribute  
        @param index the array entry
        @return the scalar value to retrieve, or SK_ScalarNaN if unsuccessful
    */
    SkScalar getArrayScalar(const char* elementID, const char* fieldName, int index);

    /** Returns the string value of the specified element's attribute[index]
        @param element is a value returned by getElement
        @param field is a value returned by getField  
        @param index the array entry
        @return the string value to retrieve, or null if unsuccessful
    */
    const char* getArrayString(const SkDisplayable* element, const SkMemberInfo* field, int index);

    /** Returns the string value of the specified element's attribute[index]
        @param elementID is the value of the id attribute in the XML of this element
        @param fieldName specifies the name of the attribute  
        @param index the array entry
        @return the string value to retrieve, or null if unsuccessful
    */
    const char* getArrayString(const char* elementID, const char* fieldName, int index);

    /** Returns the XML element corresponding to the given ID.
        @param elementID is the value of the id attribute in the XML of this element 
        @return the element matching the ID, or null if the element can't be found
    */
    const SkDisplayable* getElement(const char* elementID);

    /** Returns the element type corresponding to the XML element.
        The element type matches the element name; for instance, <line> returns kElement_LineType
        @param element is a value returned by getElement  
        @return element type, or 0 if the element can't be found
    */
    SkElementType getElementType(const SkDisplayable* element);

    /** Returns the element type corresponding to the given ID.
        @param elementID is the value of the id attribute in the XML of this element 
        @return element type, or 0 if the element can't be found
    */
    SkElementType getElementType(const char* elementID);

    /** Returns the XML field of the named attribute in the XML element.
        @param element is a value returned by getElement
        @param fieldName is the attribute to return  
        @return the attribute matching the fieldName, or null if the element can't be found
    */
    const SkMemberInfo* getField(const SkDisplayable* element, const char* fieldName);

    /** Returns the XML field of the named attribute in the XML element matching the elementID.
        @param elementID is the value of the id attribute in the XML of this element
        @param fieldName is the attribute to return  
        @return the attribute matching the fieldName, or null if the element can't be found
    */
    const SkMemberInfo* getField(const char* elementID, const char* fieldName);

    /** Returns the value type coresponding to the element's attribute.
        The value type matches the XML schema: and may be kField_BooleanType, kField_ScalarType, etc.
        @param field is a value returned by getField  
        @return the attribute type, or 0 if the element can't be found
    */
    SkFieldType getFieldType(const SkMemberInfo* field);

    /** Returns the value type coresponding to the element's attribute.
        @param elementID is the value of the id attribute in the XML of this element
        @param fieldName specifies the name of the attribute  
        @return the attribute type, or 0 if the element can't be found
    */
    SkFieldType getFieldType(const char* elementID, const char* fieldName);

    /** Returns the recommended animation interval. Returns zero if no
        interval is specified.
    */
    SkMSec getInterval();

    /** Returns the partial rectangle to invalidate after drawing. Call after draw() returns
    kIsPartiallyDifferent to do a mimimal inval(). */
    void getInvalBounds(SkRect* inval); 

    /** Returns the details of any error encountered while parsing the XML. 
    */
    const SkXMLParserError* getParserError();
    
    /** Returns the details of any error encountered while parsing the XML as string. 
    */
    const char* getParserErrorString();
    
    /** Returns the scalar value of the specified element's attribute
        @param element is a value returned by getElement
        @param field is a value returned by getField  
        @return the integer value to retrieve, or SK_NaN32 if not found
    */
    int32_t getInt(const SkDisplayable* element, const SkMemberInfo* field);

    /** Returns the scalar value of the specified element's attribute
        @param elementID is the value of the id attribute in the XML of this element
        @param fieldName specifies the name of the attribute  
        @return the integer value to retrieve, or SK_NaN32 if not found
    */
    int32_t getInt(const char* elementID, const char* fieldName);

    /** Returns the scalar value of the specified element's attribute
        @param element is a value returned by getElement
        @param field is a value returned by getField  
        @return the scalar value to retrieve, or SK_ScalarNaN if not found
    */
    SkScalar getScalar(const SkDisplayable* element, const SkMemberInfo* field);

    /** Returns the scalar value of the specified element's attribute
        @param elementID is the value of the id attribute in the XML of this element
        @param fieldName specifies the name of the attribute  
        @return the scalar value to retrieve, or SK_ScalarNaN if not found
    */
    SkScalar getScalar(const char* elementID, const char* fieldName);

    /** Returns the string value of the specified element's attribute
        @param element is a value returned by getElement
        @param field is a value returned by getField  
        @return the string value to retrieve, or null if not found
    */
    const char* getString(const SkDisplayable* element, const SkMemberInfo* field);

    /** Returns the string value of the specified element's attribute
        @param elementID is the value of the id attribute in the XML of this element
        @param fieldName specifies the name of the attribute  
        @return the string value to retrieve, or null if not found
    */
    const char* getString(const char* elementID, const char* fieldName);

    /** Gets the file default directory of the URL base path set explicitly or by reading the last URL. */
    const char* getURIBase();

    /** Resets the animator to a newly created state with no animation data. */
    void initialize();

    /** Experimental. Resets any active animations so that the next time passed is treated as 
        time zero. */
    void reset();
    
    /** Sets the scalar value of the specified element's attribute
        @param elementID is the value of the id attribute in the XML of this element
        @param fieldName specifies the name of the attribute  
        @param array is the c-style array of integers
        @param count is the length of the array
        @return true if the value was set successfully
    */
    bool setArrayInt(const char* elementID, const char* fieldName, const int* array, int count);
    
    /** Sets the scalar value of the specified element's attribute
        @param elementID is the value of the id attribute in the XML of this element
        @param fieldName specifies the name of the attribute  
        @param array is the c-style array of strings
        @param count is the length of the array
        @return true if the value was set successfully
    */
    bool setArrayString(const char* elementID, const char* fieldName, const char** array, int count);
    
    /** Sets the scalar value of the specified element's attribute
        @param elementID is the value of the id attribute in the XML of this element
        @param fieldName specifies the name of the attribute  
        @param data the integer value to set
        @return true if the value was set successfully
    */
    bool setInt(const char* elementID, const char* fieldName, int32_t data);

    /** Sets the scalar value of the specified element's attribute
        @param elementID is the value of the id attribute in the XML of this element
        @param fieldName specifies the name of the attribute  
        @param data the scalar value to set
        @return true if the value was set successfully
    */
    bool setScalar(const char* elementID, const char* fieldName, SkScalar data);

    /** Sets the string value of the specified element's attribute
        @param elementID is the value of the id attribute in the XML of this element
        @param fieldName specifies the name of the attribute  
        @param data the string value to set
        @return true if the value was set successfully
    */
    bool setString(const char* elementID, const char* fieldName, const char* data);

    /** Sets the file default directory of the URL base path 
        @param path the directory path 
    */
    void setURIBase(const char* path);

    typedef void* Handler;
    // This guy needs to be exported to java, so don't make it virtual
    void setHostHandler(Handler handler) {
        this->onSetHostHandler(handler);
    }

    /** \class Timeline
    Returns current time to animator. To return a custom timeline, create a child
    class and override the getMSecs method.
    */
    class Timeline {
    public:
        virtual ~Timeline() {}

        /** Returns the current time in milliseconds */
        virtual SkMSec getMSecs() const = 0;
    };

    /** Sets a user class to return the current time to the animator. 
        Optional; if not called, the system clock will be used by calling SkTime::GetMSecs instead.
        @param callBack the time function
    */
    void setTimeline(const Timeline& );

    static void Init(bool runUnitTests);
    static void Term();
    
    /** The event sink events generated by the animation are posted to. 
        Screenplay also posts an inval event to this event sink after processing an
        event to force a redraw.
        @param target the event sink id
    */
    void setHostEventSinkID(SkEventSinkID hostID);
    SkEventSinkID getHostEventSinkID() const;
    
    // helper
    void setHostEventSink(SkEventSink* sink) {
        this->setHostEventSinkID(sink ? sink->getSinkID() : 0);
    }
    
    virtual void setJavaOwner(Handler owner);
    
#ifdef SK_DEBUG
    virtual void eventDone(const SkEvent& evt);
    virtual bool isTrackingEvents();
    static bool NoLeaks();
#endif  
    
protected:
    virtual void onSetHostHandler(Handler handler);
    virtual void onEventPost(SkEvent*, SkEventSinkID);
    virtual void onEventPostTime(SkEvent*, SkEventSinkID, SkMSec time);

private:
// helper functions for setters
    bool setArray(SkDisplayable* element, const SkMemberInfo* field, SkTypedArray array);
    bool setArray(const char* elementID, const char* fieldName, SkTypedArray array);
    bool setInt(SkDisplayable* element, const SkMemberInfo* field, int32_t data);
    bool setScalar(SkDisplayable* element, const SkMemberInfo* field, SkScalar data);
    bool setString(SkDisplayable* element, const SkMemberInfo* field, const char* data);
    
    virtual bool onEvent(const SkEvent&);
    SkAnimateMaker* fMaker;
    friend class SkAnimateMaker;
    friend class SkAnimatorScript;
    friend class SkAnimatorScript2;
    friend class SkApply;
    friend class SkDisplayMovie;
    friend class SkDisplayType;
    friend class SkPost;
    friend class SkXMLAnimatorWriter;
};

#endif

