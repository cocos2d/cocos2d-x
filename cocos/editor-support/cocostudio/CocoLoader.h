/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
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

#ifndef _COCOLOADER_H
#define _COCOLOADER_H

#include <stdint.h>
#include "json/document.h"
#include "cocostudio/CocosStudioExport.h"

#pragma pack (4)

namespace cocostudio{
        
class CocoLoader;
    
struct CC_STUDIO_DLL stExpCocoAttribDesc
{
    char	m_cTypeName;
    uint32_t m_szName;
public:
    /**
    * Get type name.
    *
    * @parame pCoco  property loader
    *
    * @return type name
    */
    char* GetName(CocoLoader*	pCoco);
};

struct CC_STUDIO_DLL stExpCocoObjectDesc
{
    unsigned char	m_cAttribNum;
    uint32_t		m_szName;
    uint32_t		m_pAttribDescArray;
public:
    /**
    * Get type name.
    *
    * @parame pCoco  property loader
    *
    * @return type name
    */
    char*	GetName(CocoLoader*	pCoco);
    /**
    * Get attribute count.
    *
    * @return count of attributes
    */
    int		GetAttribNum();
    /**
    * Get attributes description array.
    *
    * @parame pCoco  property loader
    *
    * @return attributes description array
    */
    stExpCocoAttribDesc*	GetAttribDescArray(CocoLoader*	pCoco);
};

struct CC_STUDIO_DLL stExpCocoNode
{
public:
    int16_t			m_ObjIndex;
    int16_t			m_AttribIndex;
    unsigned char	m_ChildNum;
    uint32_t		m_szValue;
    uint32_t		m_ChildArray;
public:
    /**
    * Get json value type.
    *
    * @parame pCoco  property loader
    *
    * @return json value type
    */
    rapidjson::Type		GetType(CocoLoader*	pCoco);
    /**
    * Get type name.
    *
    * @parame pCoco  property loader
    *
    * @return type name
    */
    char*				GetName(CocoLoader*	pCoco);
    /**
    * Get value.
    *
    * @parame pCoco  property loader
    *
    * @return value
    */
    char*				GetValue(CocoLoader*	pCoco);
    /**
    * Get child count.
    *
    * @return count of child
    */
    int					GetChildNum();
    /**
    * Get child array.
    *
    * @parame pCoco  property loader
    *
    * @return child array
    */
    stExpCocoNode*		GetChildArray(CocoLoader*	pCoco);
public:
    void WriteJson(CocoLoader* pCoco,void* pFileName = nullptr, int vLayer = 0, bool bEndNode = false, bool bParentNodeIsArray = false);
};

struct CC_STUDIO_DLL stCocoFileHeader
{
    char		m_FileDesc[32];
    char		m_Version[32];
    uint32_t	m_nDataSize;
    uint32_t	m_nCompressSize;
    uint32_t	m_ObjectCount;
    uint32_t	m_lAttribMemAddr;
    uint32_t	m_CocoNodeMemAddr;
    uint32_t	m_lStringMemAddr;
    
};

class CC_STUDIO_DLL CocoLoader
{
    stCocoFileHeader*			m_pFileHeader;
    stExpCocoNode*				m_pRootNode;
    stExpCocoObjectDesc*		m_pObjectDescArray;
    char*						m_pMemoryBuff;
    
public:
    CocoLoader();
    ~CocoLoader();
public:

    /**
    * Read binary data buffer.
    *
    * @parame pBinBuff  binary buffer
    *
    * @return if load success return true
    */
    bool					ReadCocoBinBuff(char* pBinBuff);
    /**
    * Get the header of description data.
    *
    * @return header buffer pointer
    */
    stCocoFileHeader*		GetFileHeader(){ return m_pFileHeader; }
    /**
    * Get the root node.
    *
    * @return root node
    */
    stExpCocoNode*			GetRootCocoNode(){ return	m_pRootNode; }
    /**
    * Get attributes description array.
    *
    * @return attributes description array
    */
    stExpCocoObjectDesc*	GetCocoObjectDescArray(){ return	m_pObjectDescArray; }
    /**
    * Get attribute description buffer address
    *
    * @return buffer address
    */
    char*					GetMemoryAddr_AttribDesc();
    /**
    * Get node address
    *
    * @return buffer address
    */
    char*					GetMemoryAddr_CocoNode();
    /**
    * Get string buffer address
    *
    * @return buffer address
    */
    char*					GetMemoryAddr_String();
    
};

}

#pragma pack ()
#endif
