
/** GMDataBase.h
 *	
 *	功能：	数据库系统， 客户端用来读取数据表
 *	
 *	修改记录：	
 *			
 *			
 */

#pragma once
#include "IDataBase.h"

//----------------------------------------------------------
//数据库
class CDataBase : public tDataBase
{
public:

	//按照索引查找
	virtual const DBC_FIELD*	Search_Index_EQU(INT iIndexValue) const;
	//按照行
	virtual const DBC_FIELD*	Search_LineNum_EQU(INT iLineNum) const;
	//查找某列等于指定值的第一行
	virtual const DBC_FIELD*	Search_First_Column_Equ(INT nColumnNum, const DBC_FIELD& value) const;
	virtual const DBC_FIELD*	Search_Column_Equ(INT nRow,INT nColumnNum, const DBC_FIELD& value) const;
public:

	virtual	const DBC::DBCFile*	GetDBCFile( VOID ) const		{ return m_pFileDBC; }
	//取得ID
	virtual INT					GetID(VOID)const;
	//取得列数
	virtual UINT				GetFieldsNum(VOID)const;
	//取得记录的条数
	virtual UINT				GetRecordsNum(VOID)const;
	//直接打开一个dbc文件
	static BOOL					Util_OpenDBCFromTxt(const CHAR* szFileName, DBC::DBCFile* pDBCFile);

	// 切割字符串，将用“|”分割的字符串顺序拆分出来，并输出需求的字符。
	// 参数：(需要解析的字符串， 第几块数据， 输出的字符串)
	static vector<string>	    GetSplitData(string split);

	//利用GetSplitData,将切割后的值,按INT型返回
	static INT					GetSplitData_Int( const CHAR* szData, UINT nCount);

protected:
	// 查找字符串中 指定字符的 第某个位置, 返回为字符串下标
	static INT					GetCharOff( const CHAR* szStr, const CHAR ch, UINT nCount);


public:
	CDataBase(INT id);
	virtual ~CDataBase();

protected:

	//打开文本文件，生成一个数据库
	BOOL					OpenFromTXT(const CHAR* szFileName);

protected:
	DBC::DBCFile*			m_pFileDBC;

	friend class CDataBaseSystem;
};

//----------------------------------------------------------
//数据库管理器
class CDataBaseSystem : public tDataBaseSystem
{
public:
	//打开系统中所有数据库
	virtual VOID				OpenAllDataBase(VOID);
	//关闭系统中所有数据库
	virtual VOID				CloseAllDataBase(VOID);
	//得到一个已近打开的数据库，返回数据库指针
	virtual const tDataBase*	GetDataBase(INT idDataBase) const;

public:
	virtual VOID				Initial(VOID*);
	virtual VOID				Release(VOID);

protected:

protected:
	//数据库
	std::map< INT, CDataBase* >	m_mapDataBaseBuf;

public:
	CDataBaseSystem();
	virtual ~CDataBaseSystem();
	static CDataBaseSystem* GetMe(VOID) 
	{
		static CDataBaseSystem dataBaseSystem; 
		return &dataBaseSystem;
	}

protected:
	static CDataBaseSystem* s_pMe;
};