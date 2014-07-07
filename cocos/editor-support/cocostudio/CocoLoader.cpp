#include "CocoLoader.h"
#include "zlib.h"

using namespace std;
using namespace rapidjson;

namespace cocostudio{
    

char	cTypeName[] = {'N','F','T','O','A','S','V'};
const	char* kTypeNames[] = { "Null", "False", "True", "Object", "Array", "String", "Number" };
const   char* kObjKeyName[] = { "__type" , "classname" };
char	g_Buff[2048];

char*	stExpCocoAttribDesc::GetName(CocoLoader* pCoco)
{
    return ( pCoco->GetMemoryAddr_String() + m_szName );
}

char*	stExpCocoObjectDesc::GetName(CocoLoader* pCoco)
{
    return ( pCoco->GetMemoryAddr_String() + m_szName );
}

int	stExpCocoObjectDesc::GetAttribNum()
{
    return m_cAttribNum;
}

stExpCocoAttribDesc* stExpCocoObjectDesc::GetAttribDescArray(CocoLoader* pCoco)
{
    return (stExpCocoAttribDesc*)( pCoco->GetMemoryAddr_AttribDesc() + m_pAttribDescArray );
}
    
Type stExpCocoNode::GetType(CocoLoader*	pCoco)
{
    
    Type	tType = kObjectType;
    if(m_ObjIndex >= 0)
    {
        stExpCocoObjectDesc*	tpCocoObjectDesc = pCoco->GetCocoObjectDescArray() ;
        if( m_AttribIndex >= 0 )
        {
            stExpCocoAttribDesc* tpAttribDescArray = (stExpCocoAttribDesc*) tpCocoObjectDesc[m_ObjIndex].GetAttribDescArray(pCoco);
            tType = Type(tpAttribDescArray[m_AttribIndex].m_cTypeName - 'N' + kNullType);
            
            if(kFalseType == tType || kTrueType == tType)
            {
                char* szValue = (char*)GetValue(pCoco);
                if(szValue[0] == '0')
                {
                    return kFalseType;
                }
                else
                {
                    return kTrueType;
                }
            }
            
        }
        else
        {
            tType = kObjectType;
        }
    }
    else
    {
        if(m_AttribIndex >= 0)
        {
            tType   = (Type)m_ChildNum;
            
            if(kFalseType == tType || kTrueType == tType)
            {
                char* szValue = (char*)GetValue(pCoco);
                if(szValue[0] == '0')
                {
                    return kFalseType;
                }
                else
                {
                    return kTrueType;
                }
            }
        }
        else
        {
            tType = kArrayType;
        }
    }
    return tType;
}

char*	stExpCocoNode::GetName(CocoLoader*		pCoco)
{
    char*   szName  = NULL ;
    if(m_ObjIndex >= 0)
    {
        stExpCocoObjectDesc*	tpCocoObjectDesc = pCoco->GetCocoObjectDescArray();
        if( m_AttribIndex >= 0 )
        {
            stExpCocoAttribDesc* tpAttribDescArray = (stExpCocoAttribDesc*) tpCocoObjectDesc[m_ObjIndex].GetAttribDescArray(pCoco);
            szName = tpAttribDescArray[m_AttribIndex].GetName(pCoco);
        }
        else
        {
            char* szValue = GetValue(pCoco);
            if(szValue[0])
            {
                szName = GetValue(pCoco);
            }
            else
            {
                szName = tpCocoObjectDesc[m_ObjIndex].GetName(pCoco);
            }
        }
    }
    else
    {
        if(m_AttribIndex >= 0)
        {
            char*   pStringAddr = (char*)pCoco->GetCocoObjectDescArray() + pCoco->GetFileHeader()->m_lStringMemAddr ;
            szName  = m_ChildArray + pStringAddr;	
        }
        else
        {
            szName = (char*)GetValue(pCoco);
        }
    }
    return szName ;
    
}

char* stExpCocoNode::GetValue(CocoLoader* pCoco)
{
    return ( pCoco->GetMemoryAddr_String() + m_szValue );
}

int	stExpCocoNode::GetChildNum()
{
    return m_ChildNum;
}

stExpCocoNode*	stExpCocoNode::GetChildArray(CocoLoader* pCoco)
{
    return (stExpCocoNode*)( pCoco->GetMemoryAddr_CocoNode() + m_ChildArray );
}

CocoLoader::CocoLoader()
{
    m_pRootNode = NULL;
    m_pObjectDescArray = NULL;
    m_pMemoryBuff = NULL;
}

CocoLoader::~CocoLoader()
{
    if(m_pMemoryBuff)
    {
        delete[] m_pMemoryBuff;
        m_pMemoryBuff = NULL;
    }
    
}

bool	CocoLoader::ReadCocoBinBuff(char* pBinBuff)
{
    if(m_pMemoryBuff)return true;
	char*	pTempBuff = pBinBuff;
    
	m_pFileHeader = (stCocoFileHeader*)pTempBuff;
	pTempBuff += sizeof(stCocoFileHeader);
	char*   pStartAddr = m_pMemoryBuff = pTempBuff;
    
	if( m_pFileHeader->m_nCompressSize > 0 )
	{
		char*	pDestBuff  = new char[m_pFileHeader->m_nDataSize];
		uLongf		dwSrcSize  = m_pFileHeader->m_nCompressSize;
		uLongf		dwDestSize  = m_pFileHeader->m_nDataSize;
		int			nRes = uncompress((Bytef*)pDestBuff,&dwDestSize,(Bytef*)m_pMemoryBuff,dwSrcSize);
		pStartAddr = m_pMemoryBuff = pDestBuff;
	}
    
	m_pObjectDescArray = (stExpCocoObjectDesc*)pStartAddr;
    
	char*	pCocoMemAddr = pStartAddr + m_pFileHeader->m_CocoNodeMemAddr;
    
	m_pRootNode = (stExpCocoNode*)pCocoMemAddr;
    
	return true;
}

stExpCocoObjectDesc*	CocoLoader::GetCocoObjectDesc(const char* szObjDesc)
{
    for(int i = 0 ; i < m_pFileHeader->m_ObjectCount ; i++)
    {
        if(0 == strcmp((char*)m_pObjectDescArray[i].m_szName,szObjDesc))
        {
            return	&m_pObjectDescArray[i];
        }
    }
    return NULL;
}

stExpCocoObjectDesc*	CocoLoader::GetCocoObjectDesc(int vIndex)
{
    if(vIndex >= 0 && vIndex <  m_pFileHeader->m_ObjectCount)
    {
        return	&m_pObjectDescArray[vIndex];
    }
    return NULL;
}

char*	CocoLoader::GetMemoryAddr_AttribDesc()
{
    return m_pMemoryBuff + m_pFileHeader->m_lAttribMemAddr ;
}

char*	CocoLoader::GetMemoryAddr_CocoNode()
{
    return m_pMemoryBuff + m_pFileHeader->m_CocoNodeMemAddr;
}

char*	CocoLoader::GetMemoryAddr_String()
{
    return m_pMemoryBuff + m_pFileHeader->m_lStringMemAddr ;
    
}
}
