#ifndef RAPIDXML_SAX3_HPP_INCLUDED
#define RAPIDXML_SAX3_HPP_INCLUDED

// Copyright (C) 2006, 2009 Marcin Kalicinski
// Version 1.13
// Revision $DateTime: 2009/05/13 01:46:17 $
//! \file rapidxml_sax3.hpp This file contains rapidxml SAX parser implementation
#include <vector>
#include <utility>
#include "platform/rapidxml.hpp"

// On MSVC, disable "conditional expression is constant" warning (level 4). 
// This warning is almost impossible to avoid with certain types of templated code
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4127)   // Conditional expression is constant
#endif

#if !defined(RAPIDXML_PARSE_ERROR)
#define RAPIDXML_PARSE_ERROR(what, where) throw parse_error(what, where)
#endif

namespace rapidxml
{
    const int parse_normal = parse_no_data_nodes;

    /*class tok_string
    {
    public:
        tok_string() : value_(nullstring()), length_(0) {}
        tok_string(char* v) : value_(v), length_(0) {}
        tok_string(char* v, size_t l) : value_(v), length_(l) {}

        char*   value() const { return value_; }
        void    value(char* v) { value_ = v; }

        size_t  length() const { return length_; }
        void    length(size_t l) { length_ = l; }
        void    length(char* end) { length_ = end - value_; }

        char& operator[](size_t index)
        {
            return value_[index];
        }

        void write_null_terminator()
        {
            value_[length_] = '\0';
        }
    private:
        static char *nullstring()
        {
            static char zero = ('\0');
            return &zero;
        }

    private:
        char*       value_;
        size_t      length_;
    };*/

    typedef std::pair<char*, size_t> tok_string;
    typedef std::pair<const char*, size_t> const_tok_string;

    class xml_sax3_handler
    {
    public:
        virtual ~xml_sax3_handler() {}

        virtual void xmlSAX3StartElement(char *name, size_t) = 0;

        virtual void xmlSAX3Attr(const char* name, size_t,
            const char* value, size_t) = 0;

        virtual void xmlSAX3EndAttr() = 0;

        virtual void xmlSAX3EndElement(const char *name, size_t) = 0;

        virtual void xmlSAX3Text(const char *text, size_t len) = 0;
    };

    ///////////////////////////////////////////////////////////////////////////
    // XML sax parser
    class xml_sax2_handler : public xml_sax3_handler
    {
    public:
        xml_sax2_handler() { elementAttrs.reserve(64); }

        /**
        * @remark: The parameter 'name' without null terminator charactor
        */
        virtual void xmlSAX2StartElement(const char *name, size_t, const char **atts, size_t) = 0;

        /**
        * @remark: The parameter 'name' has null terminator charactor
        */
        virtual void xmlSAX2EndElement(const char *name, size_t) = 0;
        /**
        * @remark: The parameter 's' has null terminator charactor
        */
        virtual void xmlSAX2Text(const char *s, size_t) = 0;


        /// Implement SAX3 interfaces:
        virtual void xmlSAX3StartElement(char * name, size_t size) final
        {
            elementName.first = name;
            elementName.second = size;
        }

        virtual void xmlSAX3Attr(
            const char* name, size_t,
            const char* value, size_t) final
        {
            elementAttrs.push_back(name);
            elementAttrs.push_back(value);
        }

        void xmlSAX3EndAttr() final
        {
            auto chTemp = elementName.first[elementName.second];
            elementName.first[elementName.second] = '\0';

            if (!elementAttrs.empty()) {
                elementAttrs.push_back(nullptr);
                xmlSAX2StartElement(elementName.first, elementName.second, &elementAttrs[0], elementAttrs.size() - 1);
                elementAttrs.clear();
            }
            else {
                const char* attr = nullptr;
                const char** attrs = &attr;
                xmlSAX2StartElement(elementName.first, elementName.second, attrs, 0);
            }

            elementName.first[elementName.second] = chTemp;
        }

        virtual void xmlSAX3EndElement(const char *name, size_t len) final
        {
            xmlSAX2EndElement(name, len);
        }

        virtual void xmlSAX3Text(const char *s, size_t len) final
        {
            xmlSAX2Text(s, len);
        }

        tok_string elementName;
        std::vector<const char*> elementAttrs;
    };

    //! This class represents root of the DOM hierarchy. 
    //! It is also an xml_node and a memory_pool through public inheritance.
    //! Use parse() function to build a DOM tree from a zero-terminated XML text string.
    //! parse() function allocates memory for nodes and attributes by using functions of xml_document, 
    //! which are inherited from memory_pool.
    //! To access root node of the document, use the document itself, as if it was an xml_node.
    //! \param Ch Character type to use.
    template<class Ch = char>
    class xml_sax3_parser
    {
        xml_sax3_handler* handler_;
    public:

        //! Constructs empty XML document
        xml_sax3_parser(xml_sax3_handler* handler)
        {
            handler_ = handler;
            endptr_ = nullptr;
        }

        Ch *endptr_;
        //! Parses zero-terminated XML string according to given flags.
        //! Passed string will be modified by the parser, unless rapidxml::parse_non_destructive flag is used.
        //! The string must persist for the lifetime of the document.
        //! In case of error, rapidxml::parse_error exception will be thrown.
        //! <br><br>
        //! If you want to parse contents of a file, you must first load the file into the memory, and pass pointer to its beginning.
        //! Make sure that data is zero-terminated.
        //! <br><br>
        //! Document can be parsed into multiple times. 
        //! Each new call to parse removes previous nodes and attributes (if any), but does not clear memory pool.
        //! \param text XML data to parse; pointer is non-const to denote fact that this data may be modified by the parser.
        template<int Flags = parse_normal>
        void parse(Ch *text, int nLen)
        {
            assert(text);

            // Remove current contents
            //this->remove_all_nodes();
            //this->remove_all_attributes();

            endptr_ = nullptr;
            if (nLen > 0)
            {
                endptr_ = text + nLen;
            }

            // Parse BOM, if any
            parse_bom<Flags>(text);

            // Parse children
            while (1)
            {
                // Skip whitespace before node
                skip<whitespace_pred, Flags>(text, endptr_);
                if (*text == 0 || text >= endptr_)
                    break;

                // Parse and append new child
                if (*text == Ch('<'))
                {
                    ++text;     // Skip '<'
                    parse_node<Flags>(text);
                }
                else
                    RAPIDXML_PARSE_ERROR("expected <", text);
            }

        }

        //! Clears the document by deleting all nodes and clearing the memory pool.
        //! All nodes owned by document pool are destroyed.
        void clear()
        {
            //this->remove_all_nodes();
            //this->remove_all_attributes();
            //memory_pool<Ch>::clear();
        }

    private:

        ///////////////////////////////////////////////////////////////////////
        // Internal character utility functions

        // Detect whitespace character
        struct whitespace_pred
        {
            static unsigned char test(Ch ch)
            {
                return internal::lookup_tables<0>::lookup_whitespace[static_cast<unsigned char>(ch)];
            }
        };

        // Detect node name character
        struct node_name_pred
        {
            static unsigned char test(Ch ch)
            {
                return internal::lookup_tables<0>::lookup_node_name[static_cast<unsigned char>(ch)];
            }
        };

        // Detect attribute name character
        struct attribute_name_pred
        {
            static unsigned char test(Ch ch)
            {
                return internal::lookup_tables<0>::lookup_attribute_name[static_cast<unsigned char>(ch)];
            }
        };

        // Detect text character (PCDATA)
        struct text_pred
        {
            static unsigned char test(Ch ch)
            {
                return internal::lookup_tables<0>::lookup_text[static_cast<unsigned char>(ch)];
            }
        };

        // Detect text character (PCDATA) that does not require processing
        struct text_pure_no_ws_pred
        {
            static unsigned char test(Ch ch)
            {
                return internal::lookup_tables<0>::lookup_text_pure_no_ws[static_cast<unsigned char>(ch)];
            }
        };

        // Detect text character (PCDATA) that does not require processing
        struct text_pure_with_ws_pred
        {
            static unsigned char test(Ch ch)
            {
                return internal::lookup_tables<0>::lookup_text_pure_with_ws[static_cast<unsigned char>(ch)];
            }
        };

        // Detect attribute value character
        template<Ch Quote>
        struct attribute_value_pred
        {
            static unsigned char test(Ch ch)
            {
                if (Quote == Ch('\''))
                    return internal::lookup_tables<0>::lookup_attribute_data_1[static_cast<unsigned char>(ch)];
                if (Quote == Ch('\"'))
                    return internal::lookup_tables<0>::lookup_attribute_data_2[static_cast<unsigned char>(ch)];
                return 0;       // Should never be executed, to avoid warnings on Comeau
            }
        };

        // Detect attribute value character
        template<Ch Quote>
        struct attribute_value_pure_pred
        {
            static unsigned char test(Ch ch)
            {
                if (Quote == Ch('\''))
                    return internal::lookup_tables<0>::lookup_attribute_data_1_pure[static_cast<unsigned char>(ch)];
                if (Quote == Ch('\"'))
                    return internal::lookup_tables<0>::lookup_attribute_data_2_pure[static_cast<unsigned char>(ch)];
                return 0;       // Should never be executed, to avoid warnings on Comeau
            }
        };

        // Insert coded character, using UTF8 or 8-bit ASCII
        template<int Flags>
        static void insert_coded_character(Ch *&text, unsigned long code)
        {
            if (Flags & parse_no_utf8)
            {
                // Insert 8-bit ASCII character
                // Todo: possibly verify that code is less than 256 and use replacement char otherwise?
                text[0] = static_cast<unsigned char>(code);
                text += 1;
            }
            else
            {
                // Insert UTF8 sequence
                if (code < 0x80)    // 1 byte sequence
                {
                    text[0] = static_cast<unsigned char>(code);
                    text += 1;
                }
                else if (code < 0x800)  // 2 byte sequence
                {
                    text[1] = static_cast<unsigned char>((code | 0x80) & 0xBF); code >>= 6;
                    text[0] = static_cast<unsigned char>(code | 0xC0);
                    text += 2;
                }
                else if (code < 0x10000)    // 3 byte sequence
                {
                    text[2] = static_cast<unsigned char>((code | 0x80) & 0xBF); code >>= 6;
                    text[1] = static_cast<unsigned char>((code | 0x80) & 0xBF); code >>= 6;
                    text[0] = static_cast<unsigned char>(code | 0xE0);
                    text += 3;
                }
                else if (code < 0x110000)   // 4 byte sequence
                {
                    text[3] = static_cast<unsigned char>((code | 0x80) & 0xBF); code >>= 6;
                    text[2] = static_cast<unsigned char>((code | 0x80) & 0xBF); code >>= 6;
                    text[1] = static_cast<unsigned char>((code | 0x80) & 0xBF); code >>= 6;
                    text[0] = static_cast<unsigned char>(code | 0xF0);
                    text += 4;
                }
                else    // Invalid, only codes up to 0x10FFFF are allowed in Unicode
                {
                    RAPIDXML_PARSE_ERROR("invalid numeric character entity", text);
                }
            }
        }

        // Skip characters until predicate evaluates to true
        template<class StopPred, int Flags>
        static void skip(Ch *&text, Ch *textEnd = NULL)
        {
            Ch *tmp = text;
            while ((textEnd == NULL || tmp < textEnd) && StopPred::test(*tmp))
                ++tmp;
            text = tmp;
        }

        // Skip characters until predicate evaluates to true while doing the following:
        // - replacing XML character entity references with proper characters (&apos; &amp; &quot; &lt; &gt; &#...;)
        // - condensing whitespace sequences to single space character
        template<class StopPred, class StopPredPure, int Flags>
        static Ch *skip_and_expand_character_refs(Ch *&text)
        {
            // If entity translation, whitespace condense and whitespace trimming is disabled, use plain skip
            if (Flags & parse_no_entity_translation &&
                !(Flags & parse_normalize_whitespace) &&
                !(Flags & parse_trim_whitespace))
            {
                skip<StopPred, Flags>(text);
                return text;
            }

            // Use simple skip until first modification is detected
            skip<StopPredPure, Flags>(text);

            // Use translation skip
            Ch *src = text;
            Ch *dest = src;
            while (StopPred::test(*src))
            {
                // If entity translation is enabled    
                if (!(Flags & parse_no_entity_translation))
                {
                    // Test if replacement is needed
                    if (src[0] == Ch('&'))
                    {
                        switch (src[1])
                        {

                            // &amp; &apos;
                        case Ch('a'):
                            if (src[2] == Ch('m') && src[3] == Ch('p') && src[4] == Ch(';'))
                            {
                                *dest = Ch('&');
                                ++dest;
                                src += 5;
                                continue;
                            }
                            if (src[2] == Ch('p') && src[3] == Ch('o') && src[4] == Ch('s') && src[5] == Ch(';'))
                            {
                                *dest = Ch('\'');
                                ++dest;
                                src += 6;
                                continue;
                            }
                            break;

                            // &quot;
                        case Ch('q'):
                            if (src[2] == Ch('u') && src[3] == Ch('o') && src[4] == Ch('t') && src[5] == Ch(';'))
                            {
                                *dest = Ch('"');
                                ++dest;
                                src += 6;
                                continue;
                            }
                            break;

                            // &gt;
                        case Ch('g'):
                            if (src[2] == Ch('t') && src[3] == Ch(';'))
                            {
                                *dest = Ch('>');
                                ++dest;
                                src += 4;
                                continue;
                            }
                            break;

                            // &lt;
                        case Ch('l'):
                            if (src[2] == Ch('t') && src[3] == Ch(';'))
                            {
                                *dest = Ch('<');
                                ++dest;
                                src += 4;
                                continue;
                            }
                            break;

                            // &#...; - assumes ASCII
                        case Ch('#'):
                            if (src[2] == Ch('x'))
                            {
                                unsigned long code = 0;
                                src += 3;   // Skip &#x
                                while (1)
                                {
                                    unsigned char digit = internal::lookup_tables<0>::lookup_digits[static_cast<unsigned char>(*src)];
                                    if (digit == 0xFF)
                                        break;
                                    code = code * 16 + digit;
                                    ++src;
                                }
                                insert_coded_character<Flags>(dest, code);    // Put character in output
                            }
                            else
                            {
                                unsigned long code = 0;
                                src += 2;   // Skip &#
                                while (1)
                                {
                                    unsigned char digit = internal::lookup_tables<0>::lookup_digits[static_cast<unsigned char>(*src)];
                                    if (digit == 0xFF)
                                        break;
                                    code = code * 10 + digit;
                                    ++src;
                                }
                                insert_coded_character<Flags>(dest, code);    // Put character in output
                            }
                            if (*src == Ch(';'))
                                ++src;
                            else
                                RAPIDXML_PARSE_ERROR("expected ;", src);
                            continue;

                            // Something else
                        default:
                            // Ignore, just copy '&' verbatim
                            break;

                        }
                    }
                }

                // If whitespace condensing is enabled
                if (Flags & parse_normalize_whitespace)
                {
                    // Test if condensing is needed                 
                    if (whitespace_pred::test(*src))
                    {
                        *dest = Ch(' '); ++dest;    // Put single space in dest
                        ++src;                      // Skip first whitespace char
                        // Skip remaining whitespace chars
                        while (whitespace_pred::test(*src))
                            ++src;
                        continue;
                    }
                }

                // No replacement, only copy character
                *dest++ = *src++;

            }

            // Return new end
            text = src;
            return dest;

        }

        ///////////////////////////////////////////////////////////////////////
        // Internal parsing functions

        // Parse UTF-8 BOM, if any
        template<int Flags>
        void parse_bom(char *&text)
        {
            if (static_cast<unsigned char>(text[0]) == 0xEF &&
                static_cast<unsigned char>(text[1]) == 0xBB &&
                static_cast<unsigned char>(text[2]) == 0xBF)
            {
                text += 3;
            }
        }

        // Parse UTF-16/32 BOM, if any
        template<int Flags>
        void parse_bom(wchar_t *&text)
        {
            const wchar_t bom = 0xFEFF;
            if (text[0] == bom)
            {
                ++text;
            }
        }
        // Parse XML declaration (<?xml...)
        template<int Flags>
        void parse_xml_declaration(Ch *&text)
        {
            // If parsing of declaration is disabled
            if (!(Flags & parse_declaration_node))
            {
                // Skip until end of declaration
                while (text[0] != Ch('?') || text[1] != Ch('>'))
                {
                    if (!text[0])
                        RAPIDXML_PARSE_ERROR("unexpected end of data", text);
                    ++text;
                }
                text += 2;    // Skip '?>'
                return; // return 0;
            }

            // Create declaration
            // xml_node<Ch> *declaration = this->allocate_node(node_declaration);

            // Skip whitespace before attributes or ?>
            skip<whitespace_pred, Flags>(text, endptr_);

            // Parse declaration attributes
            parse_node_attributes<Flags>(text/*, declaration*/);

            // Skip ?>
            if (text[0] != Ch('?') || text[1] != Ch('>'))
                RAPIDXML_PARSE_ERROR("expected ?>", text);
            text += 2;

            // return declaration;
        }

        // Parse XML comment (<!--...)
        template<int Flags>
        void parse_comment(Ch *&text)
        {
            // If parsing of comments is disabled
            if (!(Flags & parse_comment_nodes))
            {
                // Skip until end of comment
                while (text[0] != Ch('-') || text[1] != Ch('-') || text[2] != Ch('>'))
                {
                    if (!text[0])
                        RAPIDXML_PARSE_ERROR("unexpected end of data", text);
                    ++text;
                }
                text += 3;     // Skip '-->'
                return;// return 0;      // Do not produce comment node
            }

            // Remember value start
            Ch *value = text;

            // Skip until end of comment
            while (text[0] != Ch('-') || text[1] != Ch('-') || text[2] != Ch('>'))
            {
                if (!text[0])
                    RAPIDXML_PARSE_ERROR("unexpected end of data", text);
                ++text;
            }

            // Create comment node
            // xml_node<Ch> *comment = this->allocate_node(node_comment);
            // comment->value(value, text - value); // TODO: DNT implement comment

            // Place zero terminator after comment value
            if (!(Flags & parse_no_string_terminators))
                *text = Ch('\0');

            text += 3;     // Skip '-->'
            return;
        }

        // Parse DOCTYPE
        template<int Flags>
        void parse_doctype(Ch *&text)
        {
            // Remember value start
            Ch *value = text;

            // Skip to >
            while (*text != Ch('>'))
            {
                // Determine character type
                switch (*text)
                {

                    // If '[' encountered, scan for matching ending ']' using naive algorithm with depth
                    // This works for all W3C test files except for 2 most wicked
                case Ch('['):
                {
                    ++text;     // Skip '['
                    int depth = 1;
                    while (depth > 0)
                    {
                        switch (*text)
                        {
                        case Ch('['): ++depth; break;
                        case Ch(']'): --depth; break;
                        case 0: RAPIDXML_PARSE_ERROR("unexpected end of data", text);
                        default: break;
                        }
                        ++text;
                    }
                    break;
                }

                // Error on end of text
                case Ch('\0'):
                    RAPIDXML_PARSE_ERROR("unexpected end of data", text);

                    // Other character, skip it
                default:
                    ++text;

                }
            }

            // If DOCTYPE nodes enabled
            if (Flags & parse_doctype_node)
            {
#if 0
                // Create a new doctype node
                xml_node<Ch> *doctype = this->allocate_node(node_doctype);
                doctype->value(value, text - value);
#endif               
                // Place zero terminator after value
                if (!(Flags & parse_no_string_terminators))
                    *text = Ch('\0');

                text += 1;      // skip '>'

                return;// return doctype;
            }
            else
            {
                text += 1;      // skip '>'
                return;// return 0;
            }

        }

        // Parse PI
        template<int Flags>
        void parse_pi(Ch *&text)
        {
            // If creation of PI nodes is enabled
            if (Flags & parse_pi_nodes)
            {
                // Create pi node
                // xml_node<Ch> *pi = this->allocate_node(node_pi);

                // Extract PI target name
                Ch *name = text;
                skip<node_name_pred, Flags>(text, endptr_);
                if (text == name)
                    RAPIDXML_PARSE_ERROR("expected PI target", text);
                // pi->name(name, text - name); // TODO: DNT notify for pi

                // Skip whitespace between pi target and pi
                skip<whitespace_pred, Flags>(text, endptr_);

                // Remember start of pi
                Ch *value = text;

                // Skip to '?>'
                while (text[0] != Ch('?') || text[1] != Ch('>'))
                {
                    if (*text == Ch('\0'))
                        RAPIDXML_PARSE_ERROR("unexpected end of data", text);
                    ++text;
                }

#if 0   // TODO: DNT notify for pi
                // Set pi value (verbatim, no entity expansion or whitespace normalization)
                pi->value(value, text - value);

                // Place zero terminator after name and value
                if (!(Flags & parse_no_string_terminators))
                {
                    pi->name()[pi->name_size()] = Ch('\0');
                    pi->value()[pi->value_size()] = Ch('\0');
                }
#endif

                text += 2;                          // Skip '?>'
                return; // return pi;
            }
            else
            {
                // Skip to '?>'
                while (text[0] != Ch('?') || text[1] != Ch('>'))
                {
                    if (*text == Ch('\0'))
                        RAPIDXML_PARSE_ERROR("unexpected end of data", text);
                    ++text;
                }
                text += 2;    // Skip '?>'
                return; // return 0;
            }
        }

        // Parse and append data
        // Return character that ends data.
        // This is necessary because this character might have been overwritten by a terminating 0
        template<int Flags>
        Ch parse_and_append_data(/*const tok_string& elementName unused for SAX,*/ Ch *&text, Ch *contents_start)
        {
            // Backup to contents start if whitespace trimming is disabled
            if (!(Flags & parse_trim_whitespace))
                text = contents_start;

            // Skip until end of data
            Ch *value = text, *end;
            if (Flags & parse_normalize_whitespace)
                end = skip_and_expand_character_refs<text_pred, text_pure_with_ws_pred, Flags>(text);
            else
                end = skip_and_expand_character_refs<text_pred, text_pure_no_ws_pred, Flags>(text);

            // Trim trailing whitespace if flag is set; leading was already trimmed by whitespace skip after >
            if (Flags & parse_trim_whitespace)
            {
                if (Flags & parse_normalize_whitespace)
                {
                    // Whitespace is already condensed to single space characters by skipping function, so just trim 1 char off the end
                    if (*(end - 1) == Ch(' '))
                        --end;
                }
                else
                {
                    // Backup until non-whitespace character is found
                    while (whitespace_pred::test(*(end - 1)))
                        --end;
                }
            }

#if 0 // disable data node
            // If characters are still left between end and value (this test is only necessary if normalization is enabled)
            // Create new data node
            if (!(Flags & parse_no_data_nodes))
            {
                xml_node<Ch> *data = this->allocate_node(node_data);
                data->value(value, end - value);
                node->append_node(data);
            }
#endif

            // Add data to parent node if no data exists yet
#if 0
            if (!(Flags & parse_no_element_values))
                if (*node->value() == Ch('\0'))
                    ;// node->value(value, end - value);       
#endif

            Ch ch = *text;
            // Place zero terminator after value
            if (!(Flags & parse_no_string_terminators))
            {
                //Ch ch = *text;
                *end = Ch('\0');
                //return ch;      // Return character that ends data; this is required because zero terminator overwritten it
            }

            handler_->xmlSAX3Text(value, end - value);

            // Return character that ends data
            return ch;
        }

        // Parse CDATA
        template<int Flags>
        void parse_cdata(Ch *&text)
        {
            // If CDATA is disabled
            if (Flags & parse_no_data_nodes)
            {
                // Skip until end of cdata
                while (text[0] != Ch(']') || text[1] != Ch(']') || text[2] != Ch('>'))
                {
                    if (!text[0])
                        RAPIDXML_PARSE_ERROR("unexpected end of data", text);
                    ++text;
                }
                text += 3;      // Skip ]]>
                return; // return 0;       // Do not produce CDATA node
            }

            // Skip until end of cdata
            Ch *value = text;
            while (text[0] != Ch(']') || text[1] != Ch(']') || text[2] != Ch('>'))
            {
                if (!text[0])
                    RAPIDXML_PARSE_ERROR("unexpected end of data", text);
                ++text;
            }

#if 0 // TODO: disable CDATA
            // Create new cdata node
            xml_node<Ch> *cdata = this->allocate_node(node_cdata);
            cdata->value(value, text - value);
#endif

            // Place zero terminator after value
            if (!(Flags & parse_no_string_terminators))
                *text = Ch('\0');

            text += 3;      // Skip ]]>
            return;// return cdata;
        }

        // Parse element node
        template<int Flags>
        void parse_element(Ch *&text)
        {
            // Create element node
            // xml_node<Ch> *element = this->allocate_node(node_element);

            // Extract element name
            tok_string elementName(text, 0);
            skip<node_name_pred, Flags>(text, endptr_);
            elementName.second = text - elementName.first;
            if (0 == elementName.second)
                RAPIDXML_PARSE_ERROR("expected element name", text);

            handler_->xmlSAX3StartElement(elementName.first, elementName.second);

            // Skip whitespace between element name and attributes or >
            skip<whitespace_pred, Flags>(text, endptr_);

            // Parse attributes, if any
            parse_node_attributes<Flags>(text);

            handler_->xmlSAX3EndAttr();

            // Determine ending type
            if (*text == Ch('>'))
            {
                ++text;
                parse_node_contents<Flags>(text, elementName);
            }
            else if (*text == Ch('/'))
            {
                ++text;
                if (*text != Ch('>'))
                    RAPIDXML_PARSE_ERROR("expected >", text);
                ++text;
            }
            else
                RAPIDXML_PARSE_ERROR("expected >", text);

            // Place zero terminator after name
            if (!(Flags & parse_no_string_terminators)) {
                elementName.first[elementName.second] = (Ch)'\0';
            }

            // Return parsed element
            handler_->xmlSAX3EndElement(elementName.first, elementName.second);
            // return element;
        }

        // Determine node type, and parse it
        template<int Flags>
        void parse_node(Ch *&text)
        {
            // Parse proper node type
            switch (text[0])
            {

                // <...
            default:
                // Parse and append element node
                return parse_element<Flags>(text);

                // <?...
            case Ch('?'):
                ++text;     // Skip ?
                if ((text[0] == Ch('x') || text[0] == Ch('X')) &&
                    (text[1] == Ch('m') || text[1] == Ch('M')) &&
                    (text[2] == Ch('l') || text[2] == Ch('L')) &&
                    whitespace_pred::test(text[3]))
                {
                    // '<?xml ' - xml declaration
                    text += 4;      // Skip 'xml '
                    return parse_xml_declaration<Flags>(text);
                }
                else
                {
                    // Parse PI
                    return parse_pi<Flags>(text);
                }

                // <!...
            case Ch('!'):

                // Parse proper subset of <! node
                switch (text[1])
                {

                    // <!-
                case Ch('-'):
                    if (text[2] == Ch('-'))
                    {
                        // '<!--' - xml comment
                        text += 3;     // Skip '!--'
                        return parse_comment<Flags>(text);
                    }
                    break;

                    // <![
                case Ch('['):
                    if (text[2] == Ch('C') && text[3] == Ch('D') && text[4] == Ch('A') &&
                        text[5] == Ch('T') && text[6] == Ch('A') && text[7] == Ch('['))
                    {
                        // '<![CDATA[' - cdata
                        text += 8;     // Skip '![CDATA['
                        return parse_cdata<Flags>(text);
                    }
                    break;

                    // <!D
                case Ch('D'):
                    if (text[2] == Ch('O') && text[3] == Ch('C') && text[4] == Ch('T') &&
                        text[5] == Ch('Y') && text[6] == Ch('P') && text[7] == Ch('E') &&
                        whitespace_pred::test(text[8]))
                    {
                        // '<!DOCTYPE ' - doctype
                        text += 9;      // skip '!DOCTYPE '
                        return parse_doctype<Flags>(text);
                    }
                    break;

                default: break;
                }   // switch

                // Attempt to skip other, unrecognized node types starting with <!
                ++text;     // Skip !
                while (*text != Ch('>'))
                {
                    if (*text == 0)
                        RAPIDXML_PARSE_ERROR("unexpected end of data", text);
                    ++text;
                }
                ++text;     // Skip '>'
                return; // return 0;   // No node recognized

            }
        }

        // Parse contents of the node - children, data etc.
        template<int Flags>
        void parse_node_contents(Ch *&text, const tok_string& elementName/*element name*/)
        {
            // For all children and text
            while (1)
            {
                // Skip whitespace between > and node contents
                Ch *contents_start = text;      // Store start of node contents before whitespace is skipped
                skip<whitespace_pred, Flags>(text, endptr_);
                Ch next_char = *text;

                // After data nodes, instead of continuing the loop, control jumps here.
                // This is because zero termination inside parse_and_append_data() function
                // would wreak havoc with the above code.
                // Also, skipping whitespace after data nodes is unnecessary.
            after_data_node:

                // Determine what comes next: node closing, child node, data node, or 0?
                switch (next_char)
                {

                    // Node closing or child node
                case Ch('<'):
                    if (text[1] == Ch('/'))
                    {
                        // Node closing
                        text += 2;      // Skip '</'
                        if (Flags & parse_validate_closing_tags)
                        {
                            // Skip and validate closing tag name
                            Ch *closing_name = text;
                            skip<node_name_pred, Flags>(text, endptr_);
                            if (!internal::compare(elementName.first, elementName.second, closing_name, text - closing_name, true))
                                RAPIDXML_PARSE_ERROR("invalid closing tag name", text);
                        }
                        else
                        {
                            // No validation, just skip name
                            skip<node_name_pred, Flags>(text, endptr_);
                        }
                        // Skip remaining whitespace after node name
                        skip<whitespace_pred, Flags>(text, endptr_);
                        if (*text != Ch('>'))
                            RAPIDXML_PARSE_ERROR("expected >", text);
                        ++text;     // Skip '>'
                        return;     // Node closed, finished parsing contents
                    }
                    else
                    {
                        // Child node
                        ++text;     // Skip '<'
                        parse_node<Flags>(text);
                        /*if (xml_node<Ch> *child = parse_node<Flags>(text))
                            node->append_node(child);*/
                    }
                    break;

                    // End of data - error
                case Ch('\0'):
                    RAPIDXML_PARSE_ERROR("unexpected end of data", text);

                    // Data node
                default:
                    next_char = parse_and_append_data<Flags>(/*elementName, */text, contents_start);
                    goto after_data_node;   // Bypass regular processing after data nodes

                }
            }
        }

        // Parse XML attributes of the node
        template<int Flags>
        void parse_node_attributes(Ch *&text)
        {
            // For all attributes 
            while (attribute_name_pred::test(*text))
            {
                // Extract attribute name
                Ch *name = text;
                ++text;     // Skip first character of attribute name
                skip<attribute_name_pred, Flags>(text, endptr_);
                if (text == name)
                    RAPIDXML_PARSE_ERROR("expected attribute name", name);

                // Create new attribute
                // xml_attribute<Ch> *attribute = this->allocate_attribute();
                // attribute->name(name, text - name);
                auto namesize = text - name;
                // node->append_attribute(attribute);

                // Skip whitespace after attribute name
                skip<whitespace_pred, Flags>(text, endptr_);

                // Skip =
                if (*text != Ch('='))
                    RAPIDXML_PARSE_ERROR("expected =", text);
                ++text;

                // Add terminating zero after name
                if (!(Flags & parse_no_string_terminators))
                    name[namesize] = 0;

                // Skip whitespace after =
                skip<whitespace_pred, Flags>(text, endptr_);

                // Skip quote and remember if it was ' or "
                Ch quote = *text;
                if (quote != Ch('\'') && quote != Ch('"'))
                    RAPIDXML_PARSE_ERROR("expected ' or \"", text);
                ++text;

                // Extract attribute value and expand char refs in it
                Ch *value = text, *end;
                const int AttFlags = Flags & ~parse_normalize_whitespace;   // No whitespace normalization in attributes
                if (quote == Ch('\''))
                    end = skip_and_expand_character_refs<attribute_value_pred<Ch('\'')>, attribute_value_pure_pred<Ch('\'')>, AttFlags>(text);
                else
                    end = skip_and_expand_character_refs<attribute_value_pred<Ch('"')>, attribute_value_pure_pred<Ch('"')>, AttFlags>(text);

                // Set attribute value
                // attribute->value(value, end - value);
                auto valuesize = end - value;

                // Make sure that end quote is present
                if (*text != quote)
                    RAPIDXML_PARSE_ERROR("expected ' or \"", text);
                ++text;     // Skip quote

                // Add terminating zero after value
                if (!(Flags & parse_no_string_terminators))
                    value[valuesize] = 0;

                handler_->xmlSAX3Attr(name, namesize, value, valuesize);

                // Skip whitespace after attribute value
                skip<whitespace_pred, Flags>(text, endptr_);
            }
        }

    };
}

// Undefine internal macros
#undef RAPIDXML_PARSE_ERROR

// On MSVC, restore warnings state
#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif
