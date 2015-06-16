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
    char     m_cTypeName;
    uint32_t m_szName;
public:
    /**
    * @~english Get type name.
    * @~chinese 获取类型名称.
    *
    * @parame pCoco  @~english property loader @~chinese 属性加载器
    *
    * @return @~english type name @~chinese 类型名称
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
    * @~english Get type name.
    * @~chinese 获取类型名称.
    *
    * @parame pCoco  @~english property loader @~chinese 属性加载器
    *
    * @return @~english type name @~chinese 类型名称
    */
    char*	GetName(CocoLoader*	pCoco);
    /**
    * @~english Get attribute count.
    * @~chinese 获取属性数量.
    *
    * @return @~english count of attributes @~chinese 属性总数
    */
    int		GetAttribNum();
    /**
    * @~english Get attributes description array.
    * @~chinese 获取属性描述数组.
    *
    * @parame pCoco  @~english property loader @~chinese 属性加载器
    *
    * @return @~english attributes description array @~chinese 属性描述数组
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
    * @~english Get json value type.
    * @~chinese 获取json值得类型.
    *
    * @parame pCoco  @~english property loader @~chinese 属性加载器
    *
    * @return @~english json value type @~chinese json值类型
    */
    rapidjson::Type		GetType(CocoLoader*	pCoco);
    /**
    * @~english Get type name.
    * @~chinese 获取类型名称.
    *
    * @parame pCoco  @~english property loader @~chinese 属性加载器
    *
    * @return @~english type name @~chinese 类型名称
    */
    char*				GetName(CocoLoader*	pCoco);
    /**
    * @~english Get type name.
    * @~chinese 获取类型名称.
    *
    * @parame pCoco  @~english property loader @~chinese 属性加载器
    *
    * @return @~english type name @~chinese 类型名称
    */
    char*				GetValue(CocoLoader*	pCoco);
    /**
    * @~english Get child array.
    * @~chinese 获取数组中子节点数量.
    *
    * @return @~english count of child @~chinese 子节点数量
    */
    int					GetChildNum();
    /**
    * @~english Get child array.
    * @~chinese 获取子节点列表.
    *
    * @parame pCoco  @~english property loader @~chinese 属性加载器
    *
    * @return @~english child array @~chinese 子节点列表
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
    * @~english Read binary data buffer.
    * @~chinese 读取二进制缓存.
    *
    * @parame pBinBuff  @~english binary buffer @~chinese 二进制缓存
    *
    * @return @~english if load successed @~chinese 是否读取成功
    */
    bool					ReadCocoBinBuff(char* pBinBuff);
    /**
    * @~english Get the header of description data.
    * @~chinese 获取描述数据头.
    *
    * @return @~english header buffer pointer @~chinese 头数据缓冲区指针
    */
    stCocoFileHeader*		GetFileHeader(){ return m_pFileHeader; }
    /**
    * @~english Get the root node.
    * @~chinese 获取根节点.
    *
    * @return @~english root node @~chinese 根节点
    */
    stExpCocoNode*			GetRootCocoNode(){ return	m_pRootNode; }
    /**
    * @~english Get attributes description array.
    * @~chinese 获取属性描述数组.
    *
    * @return @~english attributes description array @~chinese 属性描述数组
    */
    stExpCocoObjectDesc*	GetCocoObjectDescArray(){ return	m_pObjectDescArray; }
    /**
    * @~english Get attribute description buffer address
    * @~chinese 获取属性描述缓冲区地址
    *
    * @return @~english buffer address @~chinese 缓冲区地址
    */
    char*					GetMemoryAddr_AttribDesc();
    /**
    * @~english Get node address
    * @~chinese 获取节点指针
    *
    * @return @~english buffer address @~chinese 缓冲区地址
    */
    char*					GetMemoryAddr_CocoNode();
    /**
    * @~english Get string buffer address
    * @~chinese 获取字符串缓冲区地址
    *
    * @return @~english buffer address @~chinese 缓冲区地址
    */
    char*					GetMemoryAddr_String();
    
};

}

#pragma pack ()
#endif
