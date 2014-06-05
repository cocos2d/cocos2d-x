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
#include "rapidjson.h"
#include "document.h"

namespace cocostudio {
    
    struct  stExpCocoAttribDesc
    {
        rapidjson::Type			m_Type;
        char*					m_szName;
        char*					m_szDefaultValue;
    public:
        
        void	ReBuild(char* pStringMemoryAddr)
        {
            m_szName = (char*)((unsigned long)m_szName + pStringMemoryAddr);
            m_szDefaultValue = (char*)((unsigned long)m_szDefaultValue + pStringMemoryAddr);
        }
    }
    ;
    
    struct  stExpCocoObjectDesc
    {
        char*					m_szName;
        int						m_nAttribNum;
        stExpCocoAttribDesc*	m_pAttribDescArray;
    public:
        
        void	ReBuild(char* pAttribMemoryAddr,char* pStringMemoryAddr)
        {
            m_szName = (char*)((unsigned long)m_szName + pStringMemoryAddr);
            m_pAttribDescArray = (stExpCocoAttribDesc*)((unsigned long)m_pAttribDescArray + pAttribMemoryAddr);
            for(int i = 0 ; i < m_nAttribNum ; i++)
            {
                m_pAttribDescArray[i].ReBuild(pStringMemoryAddr);
            }
        }
        
    };
    
    class CocoLoader;
    
    struct  stExpCocoNode
    {
    protected:
        int						m_ObjIndex;
        int						m_AttribIndex;
        char*					m_szValue;
        int						m_ChildNum;
        stExpCocoNode*			m_ChildArray;
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
        int				m_nFirstUsed;
        char			m_FileDesc[32];
        char			m_Version[32];
        int				m_ObjectCount;
        unsigned long	m_lAttribMemAddr;
        unsigned long   m_CocoNodeMemAddr;
        unsigned long   m_lStringMemAddr;
        
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
}



#endif