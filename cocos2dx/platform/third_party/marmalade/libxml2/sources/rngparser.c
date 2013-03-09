/**
 * rngparser.c: parser for the Relax-NG compact syntax.
 *
 * Based on:
 *   RELAX NG Compact Syntax
 *   Committee Specification 21 November 2002
 *   http://www.oasis-open.org/committees/relax-ng/compact-20021121.html
 *
 * See Copyright for the status of this software.
 *
 * Daniel Veillard <veillard@redhat.com>
 */

#include <string.h>

#include <libxml/parser.h>
#include <libxml/parserInternals.h>
#include <libxml/relaxng.h>
#include <libxml/dict.h>

#define TODO 								\
    xmlGenericError(xmlGenericErrorContext,				\
	    "Unimplemented block at %s:%d\n",				\
            __FILE__, __LINE__);

#define MAX_TOKEN 10

typedef enum {
    CRNG_NONE = 0,
    CRNG_OP = 1,
    CRNG_KEYWORD,
    CRNG_IDENTIFIER,
    CRNG_LITERAL_SEGMENT,
    CRNG_CNAME,
    CRNG_QNAME,
    CRNG_NSNAME,
    CRNG_DOCUMENTATION
} xmlCRNGTokType;

typedef enum {
    CRNG_OKAY = 0,
    CRNG_MEMORY_ERROR,
    CRNG_INVALID_CHAR_ERROR,
    CRNG_END_ERROR,
    CRNG_ENCODING_ERROR
} xmlCRNGError;

typedef enum {
    XML_CRNG_ERROR = -1,
    XML_CRNG_OK = 0,
    XML_CRNG_EOF = 1
} xmlCRelaxNGParserState;

typedef struct _token _token;
typedef _token *tokenPtr;
struct _token {
    xmlCRNGTokType toktype;
    int toklen;
    const xmlChar *token;
    const xmlChar *prefix;
};

typedef struct _xmlCRelaxNGParserCtxt xmlCRelaxNGParserCtxt;
typedef xmlCRelaxNGParserCtxt *xmlCRelaxNGParserCtxtPtr;
struct _xmlCRelaxNGParserCtxt {
    void *userData;			/* user specific data block */
    xmlRelaxNGValidityErrorFunc error;	/* the callback in case of errors */
    xmlRelaxNGValidityWarningFunc warning;/* the callback in case of warning */
    xmlRelaxNGValidErr err;

    const xmlChar *compact;
    const xmlChar *end;
    const xmlChar *cur;
    int isElem;
    int lineno;
    const xmlChar *linestart;
    const char *filename;

    int  nbTokens;
    int  firstToken;
    _token tokens[MAX_TOKEN];
    int  totalToken;

    xmlCRelaxNGParserState state;

    int            nbErrors;

    xmlDocPtr      res;			/* the result */
    xmlNodePtr     ins;			/* the current insertion node */

    xmlNsPtr       nsDef;
    tokenPtr token;

    xmlHashTablePtr namespaces;
    xmlHashTablePtr datatypes;

    /*
     * dictionnary and keywords
     */
    xmlDictPtr     dict;
    const xmlChar *key_attribute;
    const xmlChar *key_default;
    const xmlChar *key_datatypes;
    const xmlChar *key_div;
    const xmlChar *key_element;
    const xmlChar *key_empty;
    const xmlChar *key_external;
    const xmlChar *key_grammar;
    const xmlChar *key_include;
    const xmlChar *key_inherit;
    const xmlChar *key_list;
    const xmlChar *key_mixed;
    const xmlChar *key_namespace;
    const xmlChar *key_notAllowed;
    const xmlChar *key_parent;
    const xmlChar *key_start;
    const xmlChar *key_string;
    const xmlChar *key_text;
    const xmlChar *key_token;
    const xmlChar *key_equal;
    const xmlChar *key_orequal;
    const xmlChar *key_andequal;
    const xmlChar *key_combine;
    const xmlChar *key_or;
    const xmlChar *key_comma;
    const xmlChar *key_and;
    const xmlChar *key_choice;
    const xmlChar *key_group;
    const xmlChar *key_interleave;
    const xmlChar *key_ref;
    const xmlChar *key_define;

    /* results */
    xmlDocPtr doc;	/* the resulting doc */
    xmlNodePtr insert;	/* the insertion point */
    xmlAttrPtr attrs;   /* pending attributes */
};

static const xmlChar *xmlCRelaxNGInherit = BAD_CAST "Inherit string";
static const xmlChar *xmlCRelaxNGDefault = BAD_CAST "Default string";

#define CUR_CHAR(l) xmlXPathCurrentChar(ctxt, &l)
/**
 * IS_BLANK:
 * @c:  an UNICODE value (int)
 *
 * Macro to check the following production in the XML spec:
 *
 * [3] S ::= (#x20 | #x9 | #xD | #xA)+
 */
#ifndef IS_BLANK
#define IS_BLANK(c) (((c) == 0x20) || ((c) == 0x09) || ((c) == 0xA) ||	\
                     ((c) == 0x0D))
#endif
#define IS_SEPARATOR(c) (((c) == 0x20) || ((c) == 0x09) || ((c) == 0xA) || \
                     ((c) == 0x0D) || (c == '#'))

#define CRNG_ERROR0(X)							\
    { xmlCRNGErr(ctxt, X, NULL); return(0); }
#define CRNG_ERROR(X)							\
    { xmlCRNGErr(ctxt, X, NULL); }

#define CRNG_MEM_ERROR0()						\
    { xmlCRNGErr(ctxt, CRNG_MEMORY_ERROR, NULL); return(0); }
#define CRNG_MEM_ERROR()						\
    { xmlCRNGErr(ctxt, CRNG_MEMORY_ERROR, NULL); }

#define ERROR(str) xmlCRNGErr(ctxt, 0, str);

static void
xmlCRNGErr(xmlCRelaxNGParserCtxtPtr ctxt, int err_no, const char *err_msg) {
    const xmlChar *cur;
    xmlChar buffer[150];
    int i, l;

    if (ctxt != NULL) {
        if (ctxt->filename != NULL)
	    fprintf(stderr, "%s:%d ", ctxt->filename, ctxt->lineno);
    }
    if (err_msg != NULL) {
	fprintf(stderr, "error: %s\n", err_msg);
    } else if (err_no != 0)
	fprintf(stderr, "error %d\n", err_no);
    cur = ctxt->cur;
    while ((*cur != '\n') && (*cur != '\r') && (ctxt->cur - cur < 80)) cur--;
    l = ctxt->cur - cur;
    cur++;
    for (i = 0; i < 100;i++) {
        if ((*cur == '\n') || (*cur == '\r')) break;
        buffer[i] = *cur++;
    }
    buffer[i] = 0;
    fprintf(stderr, "%s\n", buffer);
    for (i = 0; i < l;i++) buffer[i] = ' ';
    buffer[i++] = '^';
    buffer[i++] = 0;
    fprintf(stderr, "%s\n", buffer);
}

/**
 * IS_OP
 * @c:  an UNICODE value (int)
 *
 * Macro to check for operator value
 */
#ifndef IS_OP
#define IS_OP(c) (((c) == ',') || ((c) == '&') || ((c) == '|') ||	\
		  ((c) == '?') || ((c) == '-') || ((c) == '*') ||	\
		  ((c) == '{') || ((c) == '}') || ((c) == '(') ||	\
		  ((c) == ')') || ((c) == '+') || ((c) == '=') ||	\
		  ((c) == ':'))
#endif

static int
xmlCRNGIsKeyword(xmlCRelaxNGParserCtxtPtr ctxt, const xmlChar *str) {
    if ((str == ctxt->key_attribute) ||
        (str == ctxt->key_default) ||
        (str == ctxt->key_datatypes) ||
        (str == ctxt->key_div) ||
        (str == ctxt->key_element) ||
        (str == ctxt->key_empty) ||
        (str == ctxt->key_external) ||
        (str == ctxt->key_grammar) ||
        (str == ctxt->key_include) ||
        (str == ctxt->key_inherit) ||
        (str == ctxt->key_list) ||
        (str == ctxt->key_mixed) ||
        (str == ctxt->key_namespace) ||
        (str == ctxt->key_notAllowed) ||
        (str == ctxt->key_parent) ||
        (str == ctxt->key_start) ||
        (str == ctxt->key_string) ||
        (str == ctxt->key_text) ||
        (str == ctxt->key_token))
	return(1);
    return(0);

}

/*
 * xmlCRNGNextToken:
 * ctxt:  a compact RNG parser context
 *
 * Scan the schema to get the next token
 *
 * Return 0 if success and -1 in case of error
 */

static int
xmlCRNGNextToken(xmlCRelaxNGParserCtxtPtr ctxt) {
    const xmlChar *cur;
    tokenPtr token;

    if (ctxt == NULL) return(-1);
    if (ctxt->nbTokens >= MAX_TOKEN) return(-1);
    token = &(ctxt->tokens[(ctxt->firstToken + ctxt->nbTokens) % MAX_TOKEN]);
    token->toktype = CRNG_NONE;

    if (ctxt->cur == NULL) {
        ctxt->cur = ctxt->compact;
    }
retry:
    if (ctxt->cur >= ctxt->end) {
	ctxt->state = XML_CRNG_EOF;
	return(-1);
    }
    while ((ctxt->cur < ctxt->end) &&
           (IS_BLANK(*ctxt->cur))) ctxt->cur++;
    if (ctxt->cur >= ctxt->end) {
	ctxt->state = XML_CRNG_EOF;
	return(-1);
    }
    if (*ctxt->cur == '#') {
        cur = ctxt->cur;
	cur++;
	while ((cur < ctxt->end) && (*cur != '\n') && (*cur != '\r'))
	    cur++;
        ctxt->cur = cur;
	goto retry;
    } else if (*ctxt->cur == '"') {
        /* string, check for '"""' */
	ctxt->cur++;
	if (ctxt->cur >= ctxt->end) goto eof;
	cur = ctxt->cur;
        if ((ctxt->end - ctxt->end > 2) && 
	    (*cur == '"') && (cur[1] == '"')) {
	    TODO
	} else {
	    while ((cur < ctxt->end) && (*cur != '"')) cur++;
	    if (cur >= ctxt->end) goto eof;
	    token->toklen = cur - ctxt->cur;
	    token->token = xmlDictLookup(ctxt->dict, ctxt->cur, token->toklen);
	    token->toktype = CRNG_LITERAL_SEGMENT;
	    token->prefix = NULL;
	    cur++;
	    ctxt->cur = cur;
	}
    } else if (*ctxt->cur == '\'') {
        /* string, check for "'''" */
	TODO
    } else if ((IS_OP(*ctxt->cur)) || (*ctxt->cur == ':')) {
        cur = ctxt->cur;
	cur++;
	if ((cur < ctxt->end) &&
	    (((*cur == '=') &&
	      ((*ctxt->cur == '|') || (*ctxt->cur == '&'))) ||
	     ((*cur == '*') && (*ctxt->cur == ':')))) {
	    token->toklen = 2;
	} else {
	    token->toklen = 1;
	}
	token->token = xmlDictLookup(ctxt->dict, ctxt->cur, token->toklen);
	token->toktype = CRNG_OP;
	token->prefix = NULL;
	ctxt->cur += token->toklen;
    } else {
        int escape = 0;

        cur = ctxt->cur;
        if (*cur == '\\') {
	    escape = 1;
	    cur++;
	    ctxt->cur++;
	}
	while ((cur < ctxt->end) &&
	       (!(IS_SEPARATOR(*cur))) && (!(IS_OP(*cur)))) cur++;

	token->toklen = cur - ctxt->cur;
	token->token = xmlDictLookup(ctxt->dict, ctxt->cur, token->toklen);
	token->prefix = NULL;
	ctxt->cur = cur;
	if ((escape == 0) && (xmlCRNGIsKeyword(ctxt, token->token)))
	    token->toktype = CRNG_KEYWORD;
	else {
	    token->toktype = CRNG_IDENTIFIER;
	}
	if (*ctxt->cur == ':') {
	    ctxt->cur++;
	    if (*ctxt->cur == '*') {
		ctxt->cur++;
		token->toktype = CRNG_NSNAME;
	    } else {
	        cur = ctxt->cur;
		while ((cur < ctxt->end) &&
		       (!(IS_SEPARATOR(*cur))) && (!(IS_OP(*cur)))) cur++;
		token->prefix = token->token;
		token->toklen = cur - ctxt->cur;
		token->token = xmlDictLookup(ctxt->dict, ctxt->cur,
		                             token->toklen);
		ctxt->cur = cur;
		if (xmlValidateNCName(token->token, 0) == 0)
		    token->toktype = CRNG_QNAME;
		else {
		    TODO /* sounds like an error ! */
		    token->toktype = CRNG_IDENTIFIER;
		}
	    }
	}
    }
    ctxt->nbTokens++;
    return(0);
eof:
    ctxt->state = XML_CRNG_EOF;
    CRNG_ERROR(CRNG_END_ERROR);
    return(-1);
}

/**
 * xmlParseCRNGGetToken:
 * @ctxt: a compact RNG parser context
 * @no: the number of the token from 1 for the first one
 *      and 2, 3 ... for read-ahead
 *
 * Token reading interface
 *
 * returns a pointer to the new token, or NULL in case of error or EOF
 */
static tokenPtr
xmlParseCRNGGetToken(xmlCRelaxNGParserCtxtPtr ctxt, int no) {
    tokenPtr ret;
    int res;

    if ((no <= 0) || (no >= MAX_TOKEN)) return(NULL);
    no--;
    while (ctxt->nbTokens <= no) {
        res = xmlCRNGNextToken(ctxt);
	if (res < 0)
	    return(NULL);
    }
    ret = &(ctxt->tokens[(ctxt->firstToken + no) % MAX_TOKEN]);
    return(ret);
}

/**
 * xmlParseCRNGDropTokens:
 * @ctxt: a compact RNG parser context
 * @nr: the number of token marked as read
 * 
 * mark a number of token as read and consumed.
 *
 * Returns -1 in case of error and 0 otherwise
 */
static int
xmlParseCRNGDropTokens(xmlCRelaxNGParserCtxtPtr ctxt, int nr) {
    if ((nr <= 0) || (nr >= MAX_TOKEN)) return(-1);
    while ((ctxt->nbTokens >0) && (nr > 0)) {
        ctxt->firstToken++;
	nr--;
	ctxt->nbTokens--;
	ctxt->totalToken++;
	if (ctxt->totalToken == 384) 
	    fprintf(stderr, "found\n");
    }
    ctxt->firstToken = ctxt->firstToken % MAX_TOKEN;
    return(0);
}

static void
xmlParseCRNGTokenize(xmlCRelaxNGParserCtxtPtr ctxt) {
    tokenPtr token;
    
    token = xmlParseCRNGGetToken(ctxt, 1);
    while (token != NULL) {
        switch (token->toktype) {
            case CRNG_NONE: printf("none"); break;
            case CRNG_OP: printf("op"); break;
            case CRNG_KEYWORD: printf("keyword"); break;
            case CRNG_IDENTIFIER: printf("identifier"); break;
            case CRNG_LITERAL_SEGMENT: printf("literal"); break;
            case CRNG_CNAME: printf("cname"); break;
            case CRNG_QNAME: printf("qname"); break;
            case CRNG_NSNAME: printf("nsname"); break;
            case CRNG_DOCUMENTATION: printf("doc"); break;
	}
        printf(":%s\n", token->token);
	xmlParseCRNGDropTokens(ctxt, 1);
	token = xmlParseCRNGGetToken(ctxt, 1);
    }
}

/**
 * xmlParseCRNG_attribute:
 * @ctxt: a compact RNG parser context
 * @name: the attribute name
 * @ns: the attribute namespace
 * @value: the attribute value
 *
 * implements attribute of the RELAX NG Compact Syntax Appendix A
 *
 * Returns 0 in case of success and -1 in case of error
 */
static int
xmlParseCRNG_attribute(xmlCRelaxNGParserCtxtPtr ctxt, 
                       const xmlChar *name,
                       xmlNsPtr ns,
		       const xmlChar *value)
{
    xmlAttrPtr attr;

    attr = xmlNewNsPropEatName(NULL, ns, (xmlChar *) name, value);
    if (attr == NULL) CRNG_MEM_ERROR0();
    attr->next = ctxt->attrs;
    if (ctxt->attrs != NULL)
        ctxt->attrs->prev = attr;
    ctxt->attrs = attr;
    return(0);
}

/**
 * xmlParseCRNG_bindPrefix:
 * @ctxt: a compact RNG parser context
 * @prefix: the namespace prefix or NULL
 * @namespace: the namespace name
 *
 * implements bindPrefix of the RELAX NG Compact Syntax Appendix A
 *
 * Returns 0 in case of success and -1 in case of error
 */
static int
xmlParseCRNG_bindPrefix(xmlCRelaxNGParserCtxtPtr ctxt, 
                        const xmlChar *prefix,
			const xmlChar *namespace)
{
    int ret;

    if ((prefix != NULL) && (xmlStrEqual(prefix, BAD_CAST "xml"))  &&
        (!xmlStrEqual(namespace, XML_XML_NAMESPACE))) {
	ERROR("The \"xml\" prefix must be bound to \"http://www.w3.org/XML/1998/namespace\"");
	return(-1);
    } else if ((xmlStrEqual(namespace, XML_XML_NAMESPACE)) &&
               (!xmlStrEqual(prefix, BAD_CAST "xml"))) {
	ERROR("The \"http://www.w3.org/XML/1998/namespace\" name must be bound to \"xml\" prefix");
	return(-1);
    }
    if (ctxt->namespaces == NULL)
        ctxt->namespaces = xmlHashCreate(10);
    if (ctxt->namespaces == NULL) {
        ERROR("Failed to create namespace hash table");
	return(-1);
    }
    if (prefix == NULL)
        ret = xmlHashAddEntry(ctxt->namespaces, xmlCRelaxNGDefault,
	                      (void *) namespace);
    else
        ret = xmlHashAddEntry(ctxt->namespaces, prefix, 
	                      (void *) namespace);
    if (ret < 0) {
        if (prefix == NULL) {
	    ERROR("Redefinition of default namespace");
	} else {
	    ERROR("Redefinition of namespace");
	}
	return(-1);
    }

    return(0);
}

/**
 * xmlParseCRNG_bindDatatypePrefix:
 * @ctxt: a compact RNG parser context
 * @prefix: the datatype prefix
 * @namespace: the datatype identifier
 *
 * implements bindDatatypePrefix of the RELAX NG Compact Syntax Appendix A
 *
 * Returns 0 in case of success and -1 in case of error
 */
static int
xmlParseCRNG_bindDatatypePrefix(xmlCRelaxNGParserCtxtPtr ctxt ATTRIBUTE_UNUSED, 
                                const xmlChar *prefix,
			        const xmlChar *namespace)
{
    int ret;

    if ((prefix != NULL) && (xmlStrEqual(prefix, BAD_CAST "xsd"))  &&
        (!xmlStrEqual(namespace, 
		  BAD_CAST "http://www.w3.org/2001/XMLSchema-datatypes"))) {
	ERROR("The \"xsd\" prefix must be bound to \"http://www.w3.org/2001/XMLSchema-datatypes\"");
	return(-1);
    }
    if (ctxt->datatypes == NULL)
        ctxt->datatypes = xmlHashCreate(10);
    if (ctxt->datatypes == NULL) {
        ERROR("Failed to create namespace hash table");
	return(-1);
    }
    ret = xmlHashAddEntry(ctxt->datatypes, prefix, 
                          (void *) namespace);
    if (ret < 0) {
	ERROR("Redefinition of datatype");
	return(-1);
    }
    return(0);
}

/**
 * xmlParseCRNG_lookupPrefix:
 * @ctxt: a compact RNG parser context
 * @prefix: the namespace prefix or NULL
 *
 * implements lookupPrefix of the RELAX NG Compact Syntax Appendix A
 *
 * Returns the prefix in case of success or NULL in case of error
 */
static const xmlChar *
xmlParseCRNG_lookupPrefix(xmlCRelaxNGParserCtxtPtr ctxt ATTRIBUTE_UNUSED, 
                        const xmlChar *prefix)
{
    const xmlChar *ret;

    if (prefix == NULL)
        ret = xmlHashLookup(ctxt->namespaces, xmlCRelaxNGDefault);
    else
        ret = xmlHashLookup(ctxt->namespaces, prefix);
    return(ret);
}

/**
 * xmlParseCRNG_lookupDatatypePrefix:
 * @ctxt: a compact RNG parser context
 * @prefix: the namespace prefix or NULL
 *
 * implements lookupDatatypePrefix of the RELAX NG Compact Syntax Appendix A
 *
 * Returns the prefix in case of success or NULL in case of error
 */
static const xmlChar *
xmlParseCRNG_lookupDatatypePrefix(xmlCRelaxNGParserCtxtPtr ctxt ATTRIBUTE_UNUSED, 
                        const xmlChar *prefix)
{
    const xmlChar *ret;
    ret = xmlHashLookup(ctxt->datatypes, prefix);
    return(ret);
}

/**
 * xmlParseCRNG_datatypeAttributes:
 * @ctxt: a compact RNG parser context
 * @prefix: the namespace prefix or NULL
 *
 * implements lookupPrefix of the RELAX NG Compact Syntax Appendix A
 *
 * Returns the prefix in case of success or NULL in case of error
 */
static xmlAttrPtr
xmlParseCRNG_datatypeAttributes(xmlCRelaxNGParserCtxtPtr ctxt ATTRIBUTE_UNUSED, 
                        const xmlChar *library, const xmlChar *type)
{
    xmlAttrPtr lib, typ;

    lib = xmlNewNsProp(NULL, NULL, BAD_CAST "datatypeLibrary", library);
    if (lib == NULL) {
        CRNG_MEM_ERROR();
	return(NULL);
    }
    typ = xmlNewNsProp(NULL, NULL, BAD_CAST "type", type);
    if (typ == NULL) {
        CRNG_MEM_ERROR();
	return(lib);
    }
    lib->next = typ;

    return(lib);
}

/**
 * xmlParseCRNG_XXX:
 * @ctxt: a compact RNG parser context
 *
 * Parse XXX of the RELAX NG Compact Syntax Appendix A
 *
 * Returns 0 in case of success and -1 in case of error
 */
static int
xmlParseCRNG_XXX(xmlCRelaxNGParserCtxtPtr ctxt ATTRIBUTE_UNUSED)
{
    return(0);
}

static int xmlParseCRNG_pattern(xmlCRelaxNGParserCtxtPtr ctxt);
static int xmlParseCRNG_nameClass(xmlCRelaxNGParserCtxtPtr ctxt);

/**
 * xmlParseCRNG_params:
 * @ctxt: a compact RNG parser context
 *
 * Parse params of the RELAX NG Compact Syntax Appendix A
 *
 * Returns 0 in case of success and -1 in case of error
 */
static int
xmlParseCRNG_params(xmlCRelaxNGParserCtxtPtr ctxt ATTRIBUTE_UNUSED)
{
    TODO
    return(0);
}

/**
 * xmlParseCRNG_exceptNameClass:
 * @ctxt: a compact RNG parser context
 *
 * Parse exceptNameClass of the RELAX NG Compact Syntax Appendix A
 *
 * Returns 0 in case of success and -1 in case of error
 */
static int
xmlParseCRNG_exceptNameClass(xmlCRelaxNGParserCtxtPtr ctxt ATTRIBUTE_UNUSED)
{
    tokenPtr token;
    xmlNodePtr insert = ctxt->insert, cur;

    token = xmlParseCRNGGetToken(ctxt, 1);
    if ((token->toktype == CRNG_OP) &&
        (token->token[0] == '-') && (token->token[1] == 0)) {
	xmlParseCRNGDropTokens(ctxt, 1);
	cur = xmlNewNode(NULL, BAD_CAST "except");
	if (cur == NULL) CRNG_MEM_ERROR0();
	if (ctxt->insert != NULL)
	    xmlAddChild(ctxt->insert, cur);
	ctxt->insert = cur;
	xmlParseCRNG_nameClass(ctxt);
    }
    ctxt->insert = insert;
    return(0);
}

/**
 * xmlParseCRNG_innerNameClass:
 * @ctxt: a compact RNG parser context
 *
 * Parse innerNameClass of the RELAX NG Compact Syntax Appendix A
 *
 * Returns 0 in case of success and -1 in case of error
 */
static int
xmlParseCRNG_innerNameClass(xmlCRelaxNGParserCtxtPtr ctxt)
{
    tokenPtr token;
    xmlNodePtr cur;

    token = xmlParseCRNGGetToken(ctxt, 1);
    if (token->toktype == CRNG_OP) {
        if ((token->token[0] == '(') && (token->token[1] == 0)) {
	    xmlParseCRNGDropTokens(ctxt, 1);
	    xmlParseCRNG_nameClass(ctxt);
	    token = xmlParseCRNGGetToken(ctxt, 1);
	    if ((token->toktype != CRNG_OP) ||
	        (token->token[0] != ')') || (token->token[1] != 0)) {
		ERROR("Expecting \")\" here");
	    }
	    xmlParseCRNGDropTokens(ctxt, 1);
	} else if ((token->token[0] == '*') && (token->token[1] == 0)) {
	    xmlParseCRNGDropTokens(ctxt, 1);
	    cur = xmlNewNode(NULL, BAD_CAST "anyName");
	    if (cur == NULL) CRNG_MEM_ERROR0();
	    if (ctxt->insert != NULL)
		xmlAddChild(ctxt->insert, cur);
	    ctxt->insert = cur;
	    xmlParseCRNG_exceptNameClass(ctxt);
	} else {
	    TODO
	}
    } else if ((token->toktype == CRNG_IDENTIFIER) ||
               (token->toktype == CRNG_KEYWORD)) {
	cur = xmlNewNode(NULL, BAD_CAST "name");
	if (cur == NULL) CRNG_MEM_ERROR0();
	if (ctxt->isElem) {
	    xmlSetProp(cur, BAD_CAST "ns",
	               xmlParseCRNG_lookupPrefix(ctxt, NULL)); 
	} else {
	    xmlSetProp(cur, BAD_CAST "ns", BAD_CAST ""); 
	}
	xmlNodeAddContent(cur, token->token);
	if (ctxt->insert != NULL)
	    xmlAddChild(ctxt->insert, cur);
	ctxt->insert = cur;
	xmlParseCRNGDropTokens(ctxt, 1);
    } else if (token->toktype == CRNG_CNAME) {
        TODO
    } else if (token->toktype == CRNG_NSNAME) {
	cur = xmlNewNode(NULL, BAD_CAST "nsName");
	if (cur == NULL) CRNG_MEM_ERROR0();
        xmlSetProp(cur, BAD_CAST "ns",
	           xmlParseCRNG_lookupPrefix(ctxt, token->token)); 
	if (ctxt->insert != NULL)
	    xmlAddChild(ctxt->insert, cur);
	ctxt->insert = cur;
	xmlParseCRNGDropTokens(ctxt, 1);
	xmlParseCRNG_exceptNameClass(ctxt);
    } else {
        TODO /* probably an error */
    }

    return(0);
}

/**
 * xmlParseCRNG_nameClass:
 * @ctxt: a compact RNG parser context
 *
 * Parse nameClass of the RELAX NG Compact Syntax Appendix A
 *
 * Returns 0 in case of success and -1 in case of error
 */
static int
xmlParseCRNG_nameClass(xmlCRelaxNGParserCtxtPtr ctxt)
{
    tokenPtr token;
    xmlNodePtr insert = ctxt->insert, last, choice;

    ctxt->insert = NULL;
    xmlParseCRNG_innerNameClass(ctxt);
    last = ctxt->insert;
    token = xmlParseCRNGGetToken(ctxt, 1);
    while ((token->toktype == CRNG_OP) &&
        (token->token[0] == '|') && (token->token[1] == 0)) {
	choice = xmlNewNodeEatName(NULL, (xmlChar *) ctxt->key_choice);
	xmlParseCRNGDropTokens(ctxt, 1);
	if (choice == NULL) CRNG_MEM_ERROR0();
	ctxt->insert = NULL;
	xmlParseCRNG_innerNameClass(ctxt);
	xmlAddChild(choice, last);
	xmlAddChild(choice, ctxt->insert);
	last = choice;
	token = xmlParseCRNGGetToken(ctxt, 1);
    }
    xmlAddChild(insert, last);

    ctxt->insert = insert;
    return(0);
}

/**
 * xmlParseCRNG_patternBlock:
 * @ctxt: a compact RNG parser context
 *
 * Parse a pattern block of the RELAX NG Compact Syntax Appendix A
 *
 * Returns 0 in case of success and -1 in case of error
 */
static int
xmlParseCRNG_patternBlock(xmlCRelaxNGParserCtxtPtr ctxt)
{
    tokenPtr token;

    token = xmlParseCRNGGetToken(ctxt, 1);
    if ((token->toktype != CRNG_OP) ||
	(token->token[0] != '{') || (token->token[1] != 0)) {
	ERROR("Expecting \"{\" here");
    }
    xmlParseCRNGDropTokens(ctxt, 1);
    xmlParseCRNG_pattern(ctxt);
    token = xmlParseCRNGGetToken(ctxt, 1);
    if ((token->toktype != CRNG_OP) ||
	(token->token[0] != '}') || (token->token[1] != 0)) {
	ERROR("Expecting \"}\" here");
    }
    xmlParseCRNGDropTokens(ctxt, 1);
    return(0);
}

/**
 * xmlParseCRNG_datatype:
 * @ctxt: a compact RNG parser context
 *
 * Parse datatype of the RELAX NG Compact Syntax Appendix A
 *
 * Returns 0 in case of success and -1 in case of error
 */
static int
xmlParseCRNG_datatype(xmlCRelaxNGParserCtxtPtr ctxt ATTRIBUTE_UNUSED)
{
    tokenPtr token;
    xmlAttrPtr attrs = NULL;

    token = xmlParseCRNGGetToken(ctxt, 1);
    if (token->toktype == CRNG_KEYWORD) {
	if (token->token == ctxt->key_string) {
	    attrs = xmlParseCRNG_datatypeAttributes(ctxt, BAD_CAST "", 
	                                            token->token);
	    xmlParseCRNGDropTokens(ctxt, 1);
	} else if (token->token == ctxt->key_token) {
	    attrs = xmlParseCRNG_datatypeAttributes(ctxt, BAD_CAST "", 
	                                            token->token);
	    xmlParseCRNGDropTokens(ctxt, 1);
	} else {
	    TODO /* probably an error */
	}
    } else if (token->toktype == CRNG_LITERAL_SEGMENT) {
	ctxt->insert = xmlNewNode(NULL, BAD_CAST "value");
	xmlParseCRNGDropTokens(ctxt, 1);
	if (ctxt->insert == NULL) CRNG_MEM_ERROR0();
	xmlNodeAddContent(ctxt->insert, token->token);
    } else if (token->toktype == CRNG_QNAME) {
	attrs = xmlParseCRNG_datatypeAttributes(ctxt, 
	            xmlParseCRNG_lookupDatatypePrefix(ctxt, token->prefix),
		    token->token);
    } else {
        TODO
    }
    if (attrs != NULL) {
	token = xmlParseCRNGGetToken(ctxt, 1);
	if (token->toktype == CRNG_LITERAL_SEGMENT) {
	    ctxt->insert = xmlNewNode(NULL, BAD_CAST "value");
	    xmlParseCRNGDropTokens(ctxt, 1);
	    if (ctxt->insert == NULL) {
	        xmlFreePropList(attrs);
		CRNG_MEM_ERROR0();
	    }
	    ctxt->insert->properties = attrs;
	    xmlNodeAddContent(ctxt->insert, token->token);
	} else if ((token->toktype == CRNG_OP) &&
	           (token->token[0] == '{') && (token->token[0] == 0)) {
	    ctxt->insert = xmlNewNode(NULL, BAD_CAST "data");
	    xmlParseCRNGDropTokens(ctxt, 1);
	    if (ctxt->insert == NULL) {
	        xmlFreePropList(attrs);
		CRNG_MEM_ERROR0();
	    }
	    ctxt->insert->properties = attrs;
	    xmlParseCRNG_params(ctxt);
        } else {
	    ctxt->insert = xmlNewNode(NULL, BAD_CAST "data");
	    xmlParseCRNGDropTokens(ctxt, 1);
	    if (ctxt->insert == NULL) {
	        xmlFreePropList(attrs);
		CRNG_MEM_ERROR0();
	    }
	    ctxt->insert->properties = attrs;
	    xmlNodeAddContent(ctxt->insert, token->token);
	}
    }
    return(0);
}

/**
 * xmlParseCRNG_primary:
 * @ctxt: a compact RNG parser context
 *
 * Parse primary of the RELAX NG Compact Syntax Appendix A
 *
 * Returns 0 in case of success and -1 in case of error
 */
static int
xmlParseCRNG_primary(xmlCRelaxNGParserCtxtPtr ctxt ATTRIBUTE_UNUSED)
{
    tokenPtr token;

    token = xmlParseCRNGGetToken(ctxt, 1);
    if (token == NULL)
        return(0);
    if (token->toktype == CRNG_KEYWORD) {
        if (token->token == ctxt->key_element) {
	    ctxt->insert = xmlNewNodeEatName(NULL, (xmlChar *) token->token);
	    xmlParseCRNGDropTokens(ctxt, 1);
	    if (ctxt->insert == NULL) CRNG_MEM_ERROR0();
	    ctxt->isElem = 1;
	    xmlParseCRNG_nameClass(ctxt);
	    xmlParseCRNG_patternBlock(ctxt);
	} else if (token->token == ctxt->key_attribute) {
	    ctxt->insert = xmlNewNodeEatName(NULL, (xmlChar *) token->token);
	    xmlParseCRNGDropTokens(ctxt, 1);
	    if (ctxt->insert == NULL) CRNG_MEM_ERROR0();
	    ctxt->isElem = 0;
	    xmlParseCRNG_nameClass(ctxt);
	    xmlParseCRNG_patternBlock(ctxt);
	} else if (token->token == ctxt->key_mixed) {
	    ctxt->insert = xmlNewNodeEatName(NULL, (xmlChar *) token->token);
	    xmlParseCRNGDropTokens(ctxt, 1);
	    if (ctxt->insert == NULL) CRNG_MEM_ERROR0();
	    xmlParseCRNG_patternBlock(ctxt);
	} else if (token->token == ctxt->key_list) {
	    ctxt->insert = xmlNewNodeEatName(NULL, (xmlChar *) token->token);
	    xmlParseCRNGDropTokens(ctxt, 1);
	    if (ctxt->insert == NULL) CRNG_MEM_ERROR0();
	    xmlParseCRNG_patternBlock(ctxt);
	} else if (token->token == ctxt->key_empty) {
	    ctxt->insert = xmlNewNodeEatName(NULL, (xmlChar *) token->token);
	    xmlParseCRNGDropTokens(ctxt, 1);
	    if (ctxt->insert == NULL) CRNG_MEM_ERROR0();
	} else if (token->token == ctxt->key_notAllowed) {
	    ctxt->insert = xmlNewNodeEatName(NULL, (xmlChar *) token->token);
	    xmlParseCRNGDropTokens(ctxt, 1);
	    if (ctxt->insert == NULL) CRNG_MEM_ERROR0();
	} else if (token->token == ctxt->key_text) {
	    ctxt->insert = xmlNewNodeEatName(NULL, (xmlChar *) token->token);
	    xmlParseCRNGDropTokens(ctxt, 1);
	    if (ctxt->insert == NULL) CRNG_MEM_ERROR0();
	} else if (token->token == ctxt->key_parent) {
	    ctxt->insert = xmlNewNodeEatName(NULL, (xmlChar *) token->token);
	    xmlParseCRNGDropTokens(ctxt, 1);
	    if (ctxt->insert == NULL) CRNG_MEM_ERROR0();
	    TODO
	} else if (token->token == ctxt->key_grammar) {
	    ctxt->insert = xmlNewNodeEatName(NULL, (xmlChar *) token->token);
	    xmlParseCRNGDropTokens(ctxt, 1);
	    if (ctxt->insert == NULL) CRNG_MEM_ERROR0();
	    TODO
	} else if (token->token == ctxt->key_external) {
	    ctxt->insert = xmlNewNode(NULL, BAD_CAST "externalRef");
	    xmlParseCRNGDropTokens(ctxt, 1);
	    if (ctxt->insert == NULL) CRNG_MEM_ERROR0();
	    TODO
	} else {
	   TODO
	}
    } else if (token->toktype == CRNG_IDENTIFIER) {
	ctxt->insert = xmlNewNodeEatName(NULL, (xmlChar *) ctxt->key_ref);
	if (ctxt->insert == NULL) CRNG_MEM_ERROR0();
	xmlSetProp(ctxt->insert, BAD_CAST "name", token->token);
	xmlParseCRNGDropTokens(ctxt, 1);
    } else if (token->toktype == CRNG_QNAME) {
        xmlParseCRNG_datatype(ctxt);
    } else if (token->toktype == CRNG_LITERAL_SEGMENT) {
        xmlParseCRNG_datatype(ctxt);
    } else if ((token->toktype == CRNG_OP) &&
               (token->token[0] == '(') && (token->token[1] == 0)) {
	xmlParseCRNGDropTokens(ctxt, 1);
	xmlParseCRNG_pattern(ctxt);
	token = xmlParseCRNGGetToken(ctxt, 1);
	if ((token->toktype != CRNG_OP) ||
	    (token->token[0] != ')') || (token->token[1] != 0)) {
	    ERROR("Expecting \")\" here");
	}
	xmlParseCRNGDropTokens(ctxt, 1);
    }
    return(0);
}

/**
 * xmlParseCRNG_particle:
 * @ctxt: a compact RNG parser context
 *
 * Parse particle of the RELAX NG Compact Syntax Appendix A
 *
 * Returns 0 in case of success and -1 in case of error
 */
static int
xmlParseCRNG_particle(xmlCRelaxNGParserCtxtPtr ctxt)
{
    tokenPtr token;
    xmlNodePtr insert = ctxt->insert, res, tmp = NULL;

    ctxt->insert = NULL;
    xmlParseCRNG_primary(ctxt);
    res = ctxt->insert;
    token = xmlParseCRNGGetToken(ctxt, 1);
    if ((token != NULL) && (token->toktype == CRNG_OP)) {
        if ((token->token[0] == '*') && (token->token[1] == 0)) {
	    tmp = xmlNewNode(NULL, BAD_CAST "zeroOrMore");
	    if (tmp == NULL) CRNG_MEM_ERROR0();
	} else if ((token->token[0] == '+') && (token->token[1] == 0)) {
	    tmp = xmlNewNode(NULL, BAD_CAST "oneOrMore");
	    if (tmp == NULL) CRNG_MEM_ERROR0();
	} else if ((token->token[0] == '?') && (token->token[1] == 0)) {
	    tmp = xmlNewNode(NULL, BAD_CAST "optional");
	    if (tmp == NULL) CRNG_MEM_ERROR0();
	}
	if (tmp != NULL) {
	    xmlAddChild(tmp, res);
	    res = tmp;
	    xmlParseCRNGDropTokens(ctxt, 1);
	}
    }
    if (insert != NULL) {
        xmlAddChild(insert, res);
	ctxt->insert = insert;
    } else
        ctxt->insert = res;
    return(0);
}

/**
 * xmlParseCRNG_pattern:
 * @ctxt: a compact RNG parser context
 *
 * Parse pattern of the RELAX NG Compact Syntax Appendix A
 *
 * Returns 0 in case of success and -1 in case of error
 */
static int
xmlParseCRNG_pattern(xmlCRelaxNGParserCtxtPtr ctxt)
{
    tokenPtr token;
    xmlNodePtr insert = ctxt->insert, prev, grp;

    ctxt->insert = NULL;
    xmlParseCRNG_particle(ctxt);
    prev = ctxt->insert;
    token = xmlParseCRNGGetToken(ctxt, 1);
    while ((prev != NULL) && (token != NULL) && (token->toktype == CRNG_OP)) {
        if (token->token == ctxt->key_or) {
	    grp = xmlNewNodeEatName(NULL, (xmlChar *) ctxt->key_choice);
	    if (grp == NULL) CRNG_MEM_ERROR0();
	} else if (token->token == ctxt->key_and) {
	    grp = xmlNewNodeEatName(NULL, (xmlChar *) ctxt->key_interleave);
	    if (grp == NULL) CRNG_MEM_ERROR0();
	} else if (token->token == ctxt->key_comma) {
	    grp = xmlNewNodeEatName(NULL, (xmlChar *) ctxt->key_group);
	    if (grp == NULL) CRNG_MEM_ERROR0();
	} else
	   break;
	xmlParseCRNGDropTokens(ctxt, 1);
        ctxt->insert = NULL;
	xmlParseCRNG_particle(ctxt);
	xmlAddChild(grp, prev);
	xmlAddChild(grp, ctxt->insert);
	prev = grp;
	token = xmlParseCRNGGetToken(ctxt, 1);
    }
    if (insert != NULL) {
	xmlAddChild(insert, prev);
	ctxt->insert = insert;
    } else {
	ctxt->insert = prev;
    }
        
    return(0);
}

/**
 * xmlParseCRNG_component:
 * @ctxt: a compact RNG parser context
 *
 * Parse component of the RELAX NG Compact Syntax Appendix A
 *
 * Returns 0 in case of success and -1 in case of error
 */
static int
xmlParseCRNG_component(xmlCRelaxNGParserCtxtPtr ctxt)
{
    tokenPtr token, tok2;
    xmlNodePtr insert = ctxt->insert;
    
    token = xmlParseCRNGGetToken(ctxt, 1);
    if (token == NULL)
        return(0);
    if (token->toktype == CRNG_KEYWORD) {
        if (token->token == ctxt->key_start) {
	    xmlNodePtr start;

	    start = xmlNewNodeEatName(NULL, (xmlChar *) ctxt->key_start);
	    if (start == NULL) CRNG_MEM_ERROR0();
	    if (ctxt->insert != NULL)
	        xmlAddChild(ctxt->insert, start);
	    ctxt->insert = start;
            xmlParseCRNGDropTokens(ctxt, 1);
	    token = xmlParseCRNGGetToken(ctxt, 1);

            if ((token->toktype == CRNG_OP) &&
	        (token->token == ctxt->key_equal)) {
	    } else if ((token->toktype == CRNG_OP) &&
	               (token->token == ctxt->key_orequal)) {
		xmlParseCRNG_attribute(ctxt, ctxt->key_combine, NULL,
		                       BAD_CAST "choice");
	    } else if ((token->toktype == CRNG_OP) &&
	               (token->token == ctxt->key_andequal)) {
		xmlParseCRNG_attribute(ctxt, ctxt->key_combine, NULL,
		                       BAD_CAST "interleave");
	    } else {
	        ERROR("expecting \"=\" or \"&=\" or \"|=\" here")
		return(-1);
	    }
	    start->properties = ctxt->attrs;
	    ctxt->attrs = NULL;
            xmlParseCRNGDropTokens(ctxt, 1);
	    xmlParseCRNG_pattern(ctxt);

	} else if (token->token == ctxt->key_include) {
	    TODO
	} else if (token->token == ctxt->key_div) {
	    TODO
	} else {
	    return(-1);
	}
    } else if (token->toktype == CRNG_IDENTIFIER) {
        xmlNodePtr define;
	const xmlChar *identifier;

        identifier = token->token;
	tok2 = xmlParseCRNGGetToken(ctxt, 2);
	if ((tok2->toktype == CRNG_OP) &&
	    (tok2->token == ctxt->key_equal)) {
	} else if ((tok2->toktype == CRNG_OP) &&
		   (tok2->token == ctxt->key_orequal)) {
	    xmlParseCRNG_attribute(ctxt, ctxt->key_combine, NULL,
				   BAD_CAST "choice");
	} else if ((tok2->toktype == CRNG_OP) &&
		   (tok2->token == ctxt->key_andequal)) {
	    xmlParseCRNG_attribute(ctxt, ctxt->key_combine, NULL,
				   BAD_CAST "interleave");
	} else {
	    ERROR("expecting \"=\" or \"&=\" or \"|=\" here")
	    return(-1);
	}
	xmlParseCRNGDropTokens(ctxt, 2);

	define = xmlNewNodeEatName(NULL, (xmlChar *) ctxt->key_define);
	if (define == NULL) CRNG_MEM_ERROR0();
	define->properties = ctxt->attrs;
	ctxt->attrs = NULL;
	xmlSetProp(define, BAD_CAST "name", identifier);
	if (ctxt->insert != NULL)
	    xmlAddChild(ctxt->insert, define);
	ctxt->insert = define;
	xmlParseCRNG_pattern(ctxt);
    } else {
	return(-1);
    }
    ctxt->insert = insert;
    return(0);
}

/**
 * xmlParseCRNG_grammar:
 * @ctxt: a compact RNG parser context
 *
 * Parse grammar of the RELAX NG Compact Syntax Appendix A
 *
 * Returns 0 in case of success and -1 in case of error
 */
static int
xmlParseCRNG_grammar(xmlCRelaxNGParserCtxtPtr ctxt ATTRIBUTE_UNUSED)
{
    tokenPtr token;
    int ret;
    
    token = xmlParseCRNGGetToken(ctxt, 1);
    while (token != NULL) {
        ret = xmlParseCRNG_component(ctxt);
	if (ret != 0)
	    break;
	token = xmlParseCRNGGetToken(ctxt, 1);
    }
    return(0);
}

/**
 * xmlParseCRNG_topLevelBody:
 * @ctxt: a compact RNG parser context
 *
 * Parse topLevelBody of the RELAX NG Compact Syntax Appendix A
 *
 * Returns 0 in case of success and -1 in case of error
 */
static int
xmlParseCRNG_topLevelBody(xmlCRelaxNGParserCtxtPtr ctxt)
{
    tokenPtr token, tok2;
    
    token = xmlParseCRNGGetToken(ctxt, 1);
    if (token->toktype == CRNG_KEYWORD) {
        if ((token->token == ctxt->key_start) ||
	    (token->token == ctxt->key_include) ||
	    (token->token == ctxt->key_div)) {
	    xmlNodePtr grammar;

	    grammar = xmlNewNodeEatName(NULL, (xmlChar *) ctxt->key_grammar);
	    if (grammar == NULL) CRNG_MEM_ERROR0();
	    xmlDocSetRootElement(ctxt->doc, grammar);
	    ctxt->insert = grammar;
	    
	    xmlParseCRNG_grammar(ctxt);
	} else {
	    xmlParseCRNG_pattern(ctxt);
	}
    } else {
        tok2 = xmlParseCRNGGetToken(ctxt, 2);
	if ((tok2->toktype == CRNG_OP) && 
	    ((tok2->token == ctxt->key_equal) ||
	     (tok2->token == ctxt->key_orequal) ||
	     (tok2->token == ctxt->key_andequal))) {
	    xmlNodePtr grammar;

	    grammar = xmlNewNodeEatName(NULL, (xmlChar *) ctxt->key_grammar);
	    if (grammar == NULL) CRNG_MEM_ERROR0();
	    xmlDocSetRootElement(ctxt->doc, grammar);
	    ctxt->insert = grammar;
	    
	    xmlParseCRNG_grammar(ctxt);
	} else {
	    xmlParseCRNG_pattern(ctxt);
	}
    }
    return(0);
}

/**
 * xmlParseCRNG_namespacePrefix:
 * @ctxt: a compact RNG parser context
 *
 * Parse namespacePrefix of the RELAX NG Compact Syntax Appendix A
 *
 * Returns the prefix or NULL in case of error
 */
static const xmlChar *
xmlParseCRNG_namespacePrefix(xmlCRelaxNGParserCtxtPtr ctxt)
{
    tokenPtr token;
    const xmlChar *prefix = NULL;

    token = xmlParseCRNGGetToken(ctxt, 1);
    if (token->toktype == CRNG_IDENTIFIER) {
        prefix = token->token;
    } else if (token->toktype == CRNG_OP) {
	if ((token->token[0] == '=') && (token->token[1] == 0))
	    return(NULL);
        prefix = token->token;
    } else {
	ERROR("Expecting a namespace prefix");
	return(NULL);
    }
    xmlParseCRNGDropTokens(ctxt, 1);

    if (xmlStrEqual(prefix, BAD_CAST "xmlns")) {
	ERROR("Namespace prefix \"xmlns\" is forbidden");
    }
    return(prefix);
}

/**
 * xmlParseCRNG_decl:
 * @ctxt: a compact RNG parser context
 *
 * Parse decl of the RELAX NG Compact Syntax Appendix A
 *
 * Returns 0 in case of success and -1 in case of error
 */
static int
xmlParseCRNG_decl(xmlCRelaxNGParserCtxtPtr ctxt)
{
    const xmlChar *prefix = NULL;
    const xmlChar *namespace = NULL;
    tokenPtr token;
    
    token = xmlParseCRNGGetToken(ctxt, 1);
    if (token->toktype != CRNG_KEYWORD) return(-1);
    if (token->token == ctxt->key_default) {
        xmlParseCRNGDropTokens(ctxt, 1);
        token = xmlParseCRNGGetToken(ctxt, 1);
        if ((token->toktype != CRNG_KEYWORD) ||
	    (token->token != ctxt->key_namespace)) {
	    ERROR("Expecting keyword \"namespace\" after \"default\"");
	}
        xmlParseCRNGDropTokens(ctxt, 1);
	prefix = xmlParseCRNG_namespacePrefix(ctxt);
        token = xmlParseCRNGGetToken(ctxt, 1);
        if ((token->toktype != CRNG_OP) ||
	    (token->token[0] != '=') || (token->token[1] != 0)) {
	    ERROR("Expecting keyword \"=\" here");
	}
        xmlParseCRNGDropTokens(ctxt, 1);
        token = xmlParseCRNGGetToken(ctxt, 1);
        if ((token->toktype == CRNG_KEYWORD) &&
	    (token->token == ctxt->key_inherit)) {
	    namespace = xmlCRelaxNGInherit;
	} else if (token->toktype == CRNG_LITERAL_SEGMENT) {
	    namespace = token->token;
	} else {
	    ERROR("Expecting an URI or \"inherit\" value");
	}
        xmlParseCRNGDropTokens(ctxt, 1);
        if (namespace != NULL) {
	    if (prefix != NULL)
		xmlParseCRNG_bindPrefix(ctxt, prefix, namespace);
            xmlParseCRNG_bindPrefix(ctxt, NULL, namespace);
	}
    } else if (token->token == ctxt->key_namespace) {
        xmlParseCRNGDropTokens(ctxt, 1);
	prefix = xmlParseCRNG_namespacePrefix(ctxt);
        token = xmlParseCRNGGetToken(ctxt, 1);
        if ((token->toktype != CRNG_OP) ||
	    (token->token[0] != '=') || (token->token[1] != 0)) {
	    ERROR("Expecting keyword \"=\" here");
	}
        xmlParseCRNGDropTokens(ctxt, 1);
        token = xmlParseCRNGGetToken(ctxt, 1);
        if ((token->toktype == CRNG_KEYWORD) &&
	    (token->token == ctxt->key_inherit)) {
	    namespace = xmlCRelaxNGInherit;
	} else if (token->toktype == CRNG_LITERAL_SEGMENT) {
	    namespace = token->token;
	} else {
	    ERROR("Expecting an URI or \"inherit\" value");
	}
        xmlParseCRNGDropTokens(ctxt, 1);
        if (namespace != NULL)
	    xmlParseCRNG_bindPrefix(ctxt, prefix, namespace);
    } else if (token->token == ctxt->key_datatypes) {
        xmlParseCRNGDropTokens(ctxt, 1);
        
        token = xmlParseCRNGGetToken(ctxt, 1);
	if ((token->toktype != CRNG_KEYWORD) &&
	    (token->toktype != CRNG_IDENTIFIER)) {
	    ERROR("Expecting a datatype prefix identifier here");
	} else 
	    prefix = token->token;
        xmlParseCRNGDropTokens(ctxt, 1);
        token = xmlParseCRNGGetToken(ctxt, 1);
        if ((token->toktype != CRNG_OP) ||
	    (token->token[0] != '=') || (token->token[1] != 0)) {
	    ERROR("Expecting keyword \"=\" here");
	}
        xmlParseCRNGDropTokens(ctxt, 1);
        token = xmlParseCRNGGetToken(ctxt, 1);
	if (token->toktype == CRNG_LITERAL_SEGMENT) {
	    namespace = token->token;
	} else {
	    ERROR("Expecting a literal value for the datatype identifier");
	}
        xmlParseCRNGDropTokens(ctxt, 1);
        if ((namespace != NULL) && (prefix != NULL))
	    xmlParseCRNG_bindDatatypePrefix(ctxt, prefix, namespace);
    }

    return(0);
}

/**
 * xmlParseCRNG_preamble:
 * @ctxt: a compact RNG parser context
 *
 * Parse preamble of the RELAX NG Compact Syntax Appendix A
 *
 * Returns 0 in case of success and -1 in case of error
 */
static int
xmlParseCRNG_preamble(xmlCRelaxNGParserCtxtPtr ctxt)
{
    tokenPtr token;
    
    token = xmlParseCRNGGetToken(ctxt, 1);
    while (token != NULL) {
	if (token == NULL) return(-1);
	if ((token->toktype == CRNG_KEYWORD) &&
	    ((token->token == ctxt->key_default) ||
	     (token->token == ctxt->key_namespace) ||
	     (token->token == ctxt->key_datatypes))) {
	    xmlParseCRNG_decl(ctxt);
	} else
	    break;
	token = xmlParseCRNGGetToken(ctxt, 1);
    }
    return(0);
}

/**
 * xmlParseCRNG_topLevel:
 * @ctxt: a compact RNG parser context
 *
 * Parse topLevel of the RELAX NG Compact Syntax Appendix A
 *
 * Returns 0 in case of success and -1 in case of error
 */
static int
xmlParseCRNG_topLevel(xmlCRelaxNGParserCtxtPtr ctxt)
{
    xmlParseCRNG_preamble(ctxt);
    xmlParseCRNG_topLevelBody(ctxt);
    return(0);
}

/**
 * xmlConvertCRNG:
 * @schemas:  pointer to the text of the compact schemas
 * @len:  length of the schemas in bytes (or 0)
 * @encoding:  encoding indicated by the context or NULL
 *
 * Compiles the schemas into the equivalent Relax-NG XML structure
 *
 * Returns the xmlDocPtr resulting from the compilation or
 *         NULL in case of error
 */
xmlDocPtr
xmlConvertCRNG(const char *schemas, int len, const char *encoding) {
    struct _xmlCRelaxNGParserCtxt ctxt;
    xmlDocPtr ret = NULL;

    if (schemas == NULL) return(NULL);
    if (len <= 5) len = xmlStrlen((const unsigned char *) schemas);
    if (len <= 0) return(NULL);

    memset(&ctxt, 0, sizeof(ctxt));
    ctxt.compact = (const unsigned char *) schemas;
    ctxt.cur = (const unsigned char *) schemas;
    ctxt.end = (const unsigned char *) &schemas[len];
    ctxt.dict = xmlDictCreate();
    if (ctxt.dict == NULL)
        return(NULL);
    ctxt.doc = xmlNewDoc(NULL);
    if (ctxt.doc == NULL) {
	xmlDictFree(ctxt.dict);
	return(NULL);
    }
    ctxt.doc->dict = ctxt.dict;
    xmlDictReference(ctxt.dict);

    ctxt.nbTokens = 0;
    ctxt.firstToken = 0;
    ctxt.key_attribute = xmlDictLookup(ctxt.dict, BAD_CAST "attribute", -1);
    ctxt.key_default = xmlDictLookup(ctxt.dict, BAD_CAST "default", -1);
    ctxt.key_datatypes = xmlDictLookup(ctxt.dict, BAD_CAST "datatypes", -1);
    ctxt.key_div = xmlDictLookup(ctxt.dict, BAD_CAST "div", -1);
    ctxt.key_element = xmlDictLookup(ctxt.dict, BAD_CAST "element", -1);
    ctxt.key_empty = xmlDictLookup(ctxt.dict, BAD_CAST "empty", -1);
    ctxt.key_external = xmlDictLookup(ctxt.dict, BAD_CAST "external", -1);
    ctxt.key_grammar = xmlDictLookup(ctxt.dict, BAD_CAST "grammar", -1);
    ctxt.key_include = xmlDictLookup(ctxt.dict, BAD_CAST "include", -1);
    ctxt.key_inherit = xmlDictLookup(ctxt.dict, BAD_CAST "inherit", -1);
    ctxt.key_list = xmlDictLookup(ctxt.dict, BAD_CAST "list", -1);
    ctxt.key_mixed = xmlDictLookup(ctxt.dict, BAD_CAST "mixed", -1);
    ctxt.key_namespace = xmlDictLookup(ctxt.dict, BAD_CAST "namespace", -1);
    ctxt.key_notAllowed = xmlDictLookup(ctxt.dict, BAD_CAST "notAllowed", -1);
    ctxt.key_parent = xmlDictLookup(ctxt.dict, BAD_CAST "parent", -1);
    ctxt.key_start = xmlDictLookup(ctxt.dict, BAD_CAST "start", -1);
    ctxt.key_string = xmlDictLookup(ctxt.dict, BAD_CAST "string", -1);
    ctxt.key_text = xmlDictLookup(ctxt.dict, BAD_CAST "text", -1);
    ctxt.key_token = xmlDictLookup(ctxt.dict, BAD_CAST "token", -1);
    ctxt.key_equal = xmlDictLookup(ctxt.dict, BAD_CAST "=", 1);
    ctxt.key_orequal = xmlDictLookup(ctxt.dict, BAD_CAST "|=", 2);
    ctxt.key_andequal = xmlDictLookup(ctxt.dict, BAD_CAST "&=", 2);
    ctxt.key_combine = xmlDictLookup(ctxt.dict, BAD_CAST "&=", 2);
    ctxt.key_or = xmlDictLookup(ctxt.dict, BAD_CAST "|", 1);
    ctxt.key_comma = xmlDictLookup(ctxt.dict, BAD_CAST ",", 1);
    ctxt.key_and = xmlDictLookup(ctxt.dict, BAD_CAST "&", 1);
    ctxt.key_choice = xmlDictLookup(ctxt.dict, BAD_CAST "choice", -1);
    ctxt.key_group = xmlDictLookup(ctxt.dict, BAD_CAST "group", -1);
    ctxt.key_interleave = xmlDictLookup(ctxt.dict, BAD_CAST "interleave", -1);
    ctxt.key_ref = xmlDictLookup(ctxt.dict, BAD_CAST "ref", 3);
    ctxt.key_define = xmlDictLookup(ctxt.dict, BAD_CAST "define", 6);

    /* xmlConvertCRNGTokenize(&ctxt); */
    xmlConvertCRNG_topLevel(&ctxt);

    xmlDictFree(ctxt.dict);

    ret = ctxt.doc;
    return(ret);
}

/**
 * xmlConvertCRNGFile:
 * @URL: URL or filename for the resource
 * @encoding:  encoding indicated by the context or NULL
 *
 * Compiles the schemas into the equivalent Relax-NG XML structure
 *
 * Returns the xmlDocPtr resulting from the compilation or
 *         NULL in case of error
 */
xmlDocPtr
xmlConvertCRNGFile(const char *URL, const char *encoding) {
}

#ifdef STANDALONE
const xmlChar *schemas = 
"# RELAX NG XML syntax specified in compact syntax.\n\
\n\
default namespace rng = \"http://relaxng.org/ns/structure/1.0\"\n\
namespace local = \"\"\n\
datatypes xsd = \"http://www.w3.org/2001/XMLSchema-datatypes\"\n\
\n\
start = pattern\n\
\n\
pattern =\n\
  element element { (nameQName | nameClass), (common & pattern+) }\n\
  | element attribute { (nameQName | nameClass), (common & pattern?) }\n\
  | element group|interleave|choice|optional\n\
            |zeroOrMore|oneOrMore|list|mixed { common & pattern+ }\n\
  | element ref|parentRef { nameNCName, common }\n\
  | element empty|notAllowed|text { common }\n\
  | element data { type, param*, (common & exceptPattern?) }\n\
  | element value { commonAttributes, type?, xsd:string }\n\
  | element externalRef { href, common }\n\
  | element grammar { common & grammarContent* }\n\
\n\
param = element param { commonAttributes, nameNCName, xsd:string }\n\
\n\
exceptPattern = element except { common & pattern+ }\n\
\n\
grammarContent =\n\
  definition\n\
  | element div { common & grammarContent* }\n\
  | element include { href, (common & includeContent*) }\n\
\n\
includeContent =\n\
  definition\n\
  | element div { common & includeContent* }\n\
\n\
definition =\n\
  element start { combine?, (common & pattern+) }\n\
  | element define { nameNCName, combine?, (common & pattern+) }\n\
\n\
combine = attribute combine { \"choice\" | \"interleave\" }\n\
\n\
nameClass =\n\
  element name { commonAttributes, xsd:QName }\n\
  | element anyName { common & exceptNameClass? }\n\
  | element nsName { common & exceptNameClass? }\n\
  | element choice { common & nameClass+ }\n\
\n\
exceptNameClass = element except { common & nameClass+ }\n\
\n\
nameQName = attribute name { xsd:QName }\n\
nameNCName = attribute name { xsd:NCName }\n\
href = attribute href { xsd:anyURI }\n\
type = attribute type { xsd:NCName }\n\
\n\
common = commonAttributes, foreignElement*\n\
\n\
commonAttributes =\n\
  attribute ns { xsd:string }?,\n\
  attribute datatypeLibrary { xsd:anyURI }?,\n\
  foreignAttribute*\n\
\n\
foreignElement = element * - rng:* { (anyAttribute | text | anyElement)* }\n\
foreignAttribute = attribute * - (rng:*|local:*) { text }\n\
anyElement = element * { (anyAttribute | text | anyElement)* }\n\
anyAttribute = attribute * { text }\n\
";

int main(int argc ATTRIBUTE_UNUSED, char **argv ATTRIBUTE_UNUSED) {
    xmlDocPtr res;

    res = xmlConvertCRNG(schemas, -1);
    if (res != NULL) {
        xmlDocFormatDump(stdout, res, 1);
	xmlFreeDoc(res);
    }
    return(0);
}
#endif
#define bottom_rngparser
#include "elfgcchack.h"
