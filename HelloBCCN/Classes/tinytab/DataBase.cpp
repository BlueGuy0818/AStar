
/**	GMDataBase.cpp
 *
 *	功能：	管理全部的配置表
 *
 *	修改记录：
 *			080324	增加 DBC_EQUIP_LOC 针对主角换装表格改造
 *			
 *			080331	增加 DayTips.tab
 *			080410	增加 TopList.tab
 *			080410	增加 questlog.tab
 */
#include <assert.h>

#include "DataBase.h"
#include "DBC.h"
#include "DBC_Struct.h"

//============================================================================

CDataBase::CDataBase(INT id)
{
	m_pFileDBC = new DBC::DBCFile(id);
}

CDataBase::~CDataBase()
{
	delete m_pFileDBC;
}


const tDataBase::DBC_FIELD* CDataBase::Search_Index_EQU(INT iIndexValue) const 
{
	return (DBC_FIELD*)m_pFileDBC->Search_Index_EQU(iIndexValue);
}

const tDataBase::DBC_FIELD* CDataBase::Search_LineNum_EQU(INT iLineNum) const
{
	return  (DBC_FIELD*)m_pFileDBC->Search_Posistion(iLineNum, 0); 
}

// 查找某列等于指定值的第一行
const tDataBase::DBC_FIELD* CDataBase::Search_First_Column_Equ(INT nColumnNum, const DBC_FIELD& value) const
{
	return (DBC_FIELD*)m_pFileDBC->Search_First_Column_Equ(nColumnNum, value.iValue);
}


//查找某列等于指定值的第nRow行
const tDataBase::DBC_FIELD*	CDataBase::Search_Column_Equ(INT nRow,INT nColumnNum, const DBC_FIELD& value) const
{
	return (DBC_FIELD*)m_pFileDBC->Search_Column_Equ(nRow,nColumnNum,value.iValue);
}

// 取得ID
INT CDataBase::GetID(VOID) const
{
	return m_pFileDBC->GetID(); 
}

// 取得列数
UINT CDataBase::GetFieldsNum(VOID) const
{ 
	return m_pFileDBC->GetFieldsNum(); 
}

// 取得记录的条数
UINT CDataBase::GetRecordsNum(VOID) const
{ 
	return m_pFileDBC->GetRecordsNum(); 
}

// 直接打开一个dbc文件
BOOL CDataBase::Util_OpenDBCFromTxt(const CHAR* szFileName, DBC::DBCFile* pDBCFile)
{
	STRING strFileName = "tab/";
	strFileName += szFileName;
	if (::PathFileExistsA(strFileName.c_str()))
	{
		return pDBCFile->OpenFromTXT(strFileName.c_str()); 
	}

	return FALSE;
}

BOOL CDataBase::OpenFromTXT(const CHAR* szFileName)
{
	return Util_OpenDBCFromTxt(szFileName, m_pFileDBC);
}


vector<string> CDataBase::GetSplitData(string split)
{
	string tok = "|";
	split += tok;
	
	vector<string> result;
	int size = split.size();

	for (int i = 0; i < size; i++)
	{
		int pos = split.find(tok, i);
		
		if (pos < size)
		{
			string s = split.substr(i, pos-i);
			result.push_back(s);
			i = pos + tok.size()-1;
		}
	}

	return result;
}

INT CDataBase::GetSplitData_Int( const CHAR* szData, UINT nCount)
{
	return -1;
}

INT CDataBase::GetCharOff(const CHAR* szStr, const CHAR ch, UINT nCount)
{
	if (NULL == szStr)
		return -1;

	int nNum = 0;
	int nSize = (int)strlen(szStr);

	for (int i=0; i<nSize; ++i)
	{
		if (ch == szStr[i])
		{
			++nNum;
			if (nNum >= nCount)
				return i;
		}
	}

	return -1;
}


//============================================================================
CDataBaseSystem* CDataBaseSystem::s_pMe = NULL;

CDataBaseSystem::CDataBaseSystem()
{
	s_pMe = this;
}

CDataBaseSystem::~CDataBaseSystem()
{
}


VOID CDataBaseSystem::Initial(VOID*)
{
	OpenAllDataBase();
}

VOID CDataBaseSystem::Release(VOID)
{
	CloseAllDataBase();
}

VOID CDataBaseSystem::OpenAllDataBase(VOID)
{
	// 所有需要打开的数据库定义
	struct _DATABASE_DEFINE
	{
		INT				idDatabase;
		const CHAR*		pFileName;
	};

	_DATABASE_DEFINE  s_dbToLoad[] = 
	{
		{ DBC_GENERAL,  "general.txt"	},	// 武将表
		{ DBC_SOLIDER,  "solider.txt"	},	// 士兵表
		{ DBC_FORMATION,  "formation.txt"	},	// 阵型表
		{ DBC_EQUIPMENT,  "equipment.txt"	},	// 装备表
		{ DBC_SKILL,  "skill.txt"	},	// 技能表
		{ DBC_GEM,  "gem.txt"	},	// 宝石表
		{ DBC_SOUL_BEAD,  "soulBead.txt"	},	// 魂珠表
		{ DBC_RIDE,  "ride.txt"	},	// 坐骑表
		{ DBC_TELENT,  "talent.txt"	},	// 天赋表
		{ DBC_GEM_STRENGTHEN, "gemStrengthen.txt"}, // 宝石强化表
		{ DBC_ADVANCED, "advanced.txt"},  // 将领进阶表
		{ DBC_RIDE_STRENGTHEN_MANAGER, "rideStrengthen.txt"},  // 坐骑强化表
		{ DBC_OFFICIAL, "official.txt"},  // 官职表
		{ DBC_ROUND, "round.txt"},  // 战斗回合表
		{ DBC_SOLIDER_POSITION, "soliderPosition.txt"}  // 士兵占位表
	};

	// 打开所有数据库
	INT nNum = sizeof(s_dbToLoad)/sizeof(_DATABASE_DEFINE);
	for(INT i=0; i<nNum; i++)
	{
		CDataBase* pDataBase = new CDataBase(s_dbToLoad[i].idDatabase);
		if( !pDataBase )
			return; //KLhrow( "New DataBase %d Error!", nNum );

		if(!(pDataBase->OpenFromTXT (s_dbToLoad[i].pFileName)))
		{
			return; //KLThrow("Open %s Error!", s_dbToLoad[i].pFileName);
		}

		if(m_mapDataBaseBuf.find(s_dbToLoad[i].idDatabase) != m_mapDataBaseBuf.end())
		{
			return; //KLThrow("DBC ID Multi define(%s)", s_dbToLoad[i].pFileName);
		}

		m_mapDataBaseBuf.insert(std::make_pair(s_dbToLoad[i].idDatabase, pDataBase));
	}
}

VOID CDataBaseSystem::CloseAllDataBase(VOID)
{
	std::map< INT, CDataBase* >::iterator it;
	for(it = m_mapDataBaseBuf.begin(); it!=m_mapDataBaseBuf.end(); it++)
	{
		if(it->second)
		{
			delete (it->second);
			it->second = NULL;
		}
	}

	m_mapDataBaseBuf.clear();
}

const tDataBase* CDataBaseSystem::GetDataBase(INT idDataBase) const
{
	std::map< INT, CDataBase* >::const_iterator it = m_mapDataBaseBuf.find(idDataBase);
	return (const tDataBase*)(it->second);
}