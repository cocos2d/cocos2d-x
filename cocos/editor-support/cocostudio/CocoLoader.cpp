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

#include "CocoLoader.h"

namespace cocostudio {
    const	char* kTypeNames[] = { "Null", "False", "True", "Object", "Array", "String", "Number" };
    const   char* kObjKeyName[] = { "__type" , "classname" };
    char	g_Buff[2048];
    
    rapidjson::Type	stExpCocoNode::GetType(CocoLoader*		pCoco)
    {
        rapidjson::Type	tType = rapidjson::kObjectType;
        if(m_ObjIndex >= 0)
        {
            stExpCocoObjectDesc*	tpCocoObjectDesc = pCoco->GetCocoObjectDesc();
            if( m_AttribIndex >= 0 )
            {
                tType = tpCocoObjectDesc[m_ObjIndex].m_pAttribDescArray[m_AttribIndex].m_Type;
                if(rapidjson::kFalseType == tType || rapidjson::kTrueType == tType)
                {
                    if(m_szValue[0] == '0')
                    {
                        return rapidjson::kFalseType;
                    }
                    else
                    {
                        return rapidjson::kTrueType;
                    }
                }
                
            }
            else
            {
                tType = rapidjson::kObjectType;
            }
        }
        else
        {
            if(m_AttribIndex >= 0)
            {
//                char*   pStringAddr = (char*)pCoco->GetCocoObjectDesc() + pCoco->GetFileHeader()->m_lStringMemAddr ;
                tType   = (rapidjson::Type)m_ChildNum;
                
                if(rapidjson::kFalseType == tType || rapidjson::kTrueType == tType)
                {
                    if(m_szValue[0] == '0')
                    {
                        return rapidjson::kFalseType;
                    }
                    else
                    {
                        return rapidjson::kTrueType;
                    }
                }
            }
            else
            {
                tType = rapidjson::kArrayType;
            }
        }
        return tType;
    }
   
    char*	stExpCocoNode::GetName(CocoLoader*		pCoco)
    {
        char*   szName  = NULL ;
        if(m_ObjIndex >= 0)
        {
            stExpCocoObjectDesc*	tpCocoObjectDesc = pCoco->GetCocoObjectDesc();
            if( m_AttribIndex >= 0 )
            {
                szName = tpCocoObjectDesc[m_ObjIndex].m_pAttribDescArray[m_AttribIndex].m_szName;
            }
            else
            {
                
                if(m_szValue[0])
                {
                    szName = m_szValue;
                }
                else
                {
                    szName = tpCocoObjectDesc[m_ObjIndex].m_szName;
                }
            }
        }
        else
        {
            if(m_AttribIndex >= 0)
            {
                char*   pStringAddr = (char*)pCoco->GetCocoObjectDesc() + pCoco->GetFileHeader()->m_lStringMemAddr ;
                szName  = (char*)((unsigned long)m_ChildArray + pStringAddr);
            }
            else
            {
                szName = m_szValue;
            }
        }
        return szName ;
    }
    
    char*	stExpCocoNode::GetValue()
    {
        return m_szValue;
    }
    
    int		stExpCocoNode::GetChildNum()
    {
        return m_ChildNum;
    }
    
    stExpCocoNode*		stExpCocoNode::GetChildArray()
    {
        return m_ChildArray;
    }
   
    void	stExpCocoNode::ReBuild(char* pCocoNodeAddr,char* pStringMemoryAddr)
    {
        m_szValue = (char*)((unsigned long)m_szValue + pStringMemoryAddr);
        
   
        if( -1 == m_AttribIndex )
        {
            if(m_ChildNum > 0)
            {
                m_ChildArray = (stExpCocoNode*)((unsigned long)(m_ChildArray) + pCocoNodeAddr );
            }
            
            for(int i = 0 ; i < m_ChildNum ; i++)
            {
                m_ChildArray[i].ReBuild(pCocoNodeAddr,pStringMemoryAddr);
            }
        }
        
    }
   
    CocoLoader::CocoLoader()
    {
        m_pRootNode = NULL;
        m_pObjectDescArray = NULL;
    }
    
    CocoLoader::~CocoLoader()
    {
        
    }
    
    bool	CocoLoader::ReadCocoBinBuff(char* pBinBuff)
    {
        //Type
        char*	pTempBuff = pBinBuff;
        
    
        m_pFileHeader = (stCocoFileHeader*)pTempBuff;
        pTempBuff += sizeof(stCocoFileHeader);
        
    
        char*   pStartAddr = pTempBuff;
        m_pObjectDescArray = (stExpCocoObjectDesc*)pStartAddr;
        
        char*   pAttrAddr = pStartAddr + m_pFileHeader->m_lAttribMemAddr ;
        char*	pCocoMemAddr = pStartAddr + m_pFileHeader->m_CocoNodeMemAddr;
        char*   pStringAddr = pStartAddr + m_pFileHeader->m_lStringMemAddr ;
        
        m_pRootNode = (stExpCocoNode*)pCocoMemAddr;
        
        if(1 == m_pFileHeader->m_nFirstUsed)
        {	
            for(int i = 0 ; i < m_pFileHeader->m_ObjectCount ; i++)
            {
                m_pObjectDescArray[i].ReBuild(pAttrAddr,pStringAddr)	;
            }
            m_pRootNode->ReBuild(pCocoMemAddr,pStringAddr);
            
            m_pFileHeader->m_nFirstUsed = 0;
        }
        
        return true;
    }

}

