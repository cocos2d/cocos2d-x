/****************************************************************************
 Copyright (c) 2013-2014 Chukong Technologies Inc.
 
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

#include <stdio.h>
#include <vector>
#include <cstdio>
#include <stdint.h>
#include "rapidjson.h"
#include "document.h"

namespace cocostudio {
    
#pragma pack (4)
    struct  stExpCocoAttribDesc
    {
        rapidjson::Type			m_Type;
		uint64_t	m_szName;				//对应的名称
		uint64_t	m_szDefaultValue;		//对应的默认值
    public:
        
        void	ReBuild(char* pStringMemoryAddr)
        {
			m_szName = m_szName + (uint64_t)pStringMemoryAddr;
			m_szDefaultValue = m_szDefaultValue + (uint64_t)pStringMemoryAddr;
        }
    }
    ;
    
    struct  stExpCocoObjectDesc
    {
        uint32_t		m_nAttribNum;			//属性数量
		uint64_t		m_szName;				//对应的名称字符串的位置,默认为0
		uint64_t		m_pAttribDescArray;		//属性数组
    public:
        
        void	ReBuild(char* pAttribMemoryAddr,char* pStringMemoryAddr)
        {
			m_szName = m_szName + (uint64_t)pStringMemoryAddr;
			m_pAttribDescArray = m_pAttribDescArray + (uint64_t)pAttribMemoryAddr;
			stExpCocoAttribDesc* tpAttribDescArray = (stExpCocoAttribDesc*)m_pAttribDescArray;
			for(int i = 0 ; i < m_nAttribNum ; i++)
			{
				tpAttribDescArray[i].ReBuild(pStringMemoryAddr);
			}
        }
        
    };
    
    class CocoLoader;
    
    struct  stExpCocoNode
    {
    protected:
		int32_t						m_ObjIndex;				//对应的物体索引
		int32_t						m_AttribIndex;			//属性的物体索引
		uint32_t					m_ChildNum;				//子节点数量
        uint64_t					m_szValue;				//对应的默认值
		uint64_t					m_ChildArray;			//对应的子节点数组
    public:
        
        
        rapidjson::Type				GetType(CocoLoader*		pCoco);
        
        char*				GetName(CocoLoader*		pCoco);
        
        char*				GetValue();
        
        int					GetChildNum();
        
        stExpCocoNode*		GetChildArray();
    public:
        
        inline  void	ReBuild(char* pCocoNodeAddr,char* pStringMemoryAddr);
        
    }
    ;
    
    
    struct		stCocoFileHeader
    {
		char			m_FileDesc[32];
		char			m_Version[32];
		uint32_t		m_nFirstUsed;
		uint32_t		m_ObjectCount;
		uint64_t		m_lAttribMemAddr;
		uint64_t		m_CocoNodeMemAddr;
		uint64_t		m_lStringMemAddr;
        
    };
    
    
    class CocoLoader
    {
        
        stCocoFileHeader*			m_pFileHeader;
        
        stExpCocoNode*				m_pRootNode;
        
        stExpCocoObjectDesc*		m_pObjectDescArray;
        
    public:
        
        CocoLoader();
        
        ~CocoLoader();
        
    public:
        
        
        bool					ReadCocoBinBuff(char* pBinBuff);
        
        stCocoFileHeader*		GetFileHeader(){return m_pFileHeader;}
        
        stExpCocoNode*			GetRootCocoNode(){return	m_pRootNode;}
        
        stExpCocoObjectDesc*	GetCocoObjectDesc(){return	m_pObjectDescArray;}
        
    };
    
#pragma pack ()
}



#endif