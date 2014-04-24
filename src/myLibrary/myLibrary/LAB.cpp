// LAB.cpp : 实现文件
//

#include "stdafx.h"
#include "myLibrary.h"
#include "LAB.h"
#include "afxdialogex.h"

// CLAB 对话框

IMPLEMENT_DYNAMIC(CLAB, CDialogEx)

CLAB::CLAB(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLAB::IDD, pParent)
	, m_lab_bno(99999)
	, m_lab_uid(99999)
{

}

CLAB::~CLAB()
{
}

void CLAB::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_lab_bno);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
	DDX_Text(pDX, IDC_EDIT1, m_lab_uid);
}


BEGIN_MESSAGE_MAP(CLAB, CDialogEx)
	ON_BN_CLICKED(IDC_personalData, &CLAB::OnBnClickedpersonaldata)
	ON_BN_CLICKED(IDC_lendNew, &CLAB::OnBnClickedlendnew)
	ON_BN_CLICKED(IDC_borrowNew, &CLAB::OnBnClickedborrownew)
END_MESSAGE_MAP()


// CLAB 消息处理程序


void CLAB::OnBnClickedpersonaldata()
{
	// TODO: 在此添加控件通知处理程序代码

	if(!m_db.IsOpen() && !m_db.OpenEx(_T("DSN=mydb;DATABASE=Library;UID=admin;PWD=admin"), 
	 CDatabase::noOdbcDialog))
	{
		MessageBox(_T("数据库连接失败"));
		return;
	}
	
	CString query;
	CRecordset m_set(&m_db);

	UpdateData(TRUE); 

	query.Format(_T("select distinct Q.* from lib_commonQuery as Q,")
		_T("lib_book_list as L, lib_record as R ")
		_T("where R.bno = L.bno and R.lib_uid = %d and R.isReturned = 0 and Q.ISBN = L.ISBN ")
		_T("order by title"),
		m_lab_uid);

	m_ListCtrl.InsertColumn(0, _T("书号"), LVCFMT_CENTER, 120, 0);
	m_ListCtrl.InsertColumn(1, _T("类别"), LVCFMT_CENTER, 100, 1);
	m_ListCtrl.InsertColumn(2, _T("书名"), LVCFMT_CENTER, 160, 2);
	m_ListCtrl.InsertColumn(3, _T("出版社"), LVCFMT_CENTER, 100, 3);
	m_ListCtrl.InsertColumn(4, _T("年份"), LVCFMT_CENTER, 40, 4);
	m_ListCtrl.InsertColumn(5, _T("作者"), LVCFMT_CENTER,100, 5);
	m_ListCtrl.InsertColumn(6, _T("价格"), LVCFMT_CENTER, 40, 6);
	m_ListCtrl.InsertColumn(7, _T("总量"), LVCFMT_CENTER, 40, 7);
	m_ListCtrl.InsertColumn(8, _T("库存"), LVCFMT_CENTER, 40, 8);
	m_ListCtrl.SetExtendedStyle(m_ListCtrl.GetExtendedStyle() | LVS_EX_GRIDLINES |
		LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP);

	try
	{
		m_set.Open(CRecordset::forwardOnly,query,CRecordset::readOnly);
		CDBVariant var; 
		m_ListCtrl.DeleteAllItems();	
		short nFields = m_set.GetODBCFieldCount(); 
		int i = 0;
		while(!m_set.IsEOF())
		{
			for(short index = 0; index < nFields; index++)
			{
				m_set.GetFieldValue(index, var);
				if(index == 0)
					m_ListCtrl.InsertItem(i, VariantToCString(&var));
				else
					m_ListCtrl.SetItemText(i, index, VariantToCString(&var));
			}
			m_set.MoveNext();
			i++;
		}
		m_set.Close();
		m_db.Close(); 
	}
	catch(CDBException* pe)
	{
	   // The error code is in pe->m_nRetCode
	   MessageBox(_T("无此记录。"));
	   pe->Delete();
	}
	m_db.Close();
	
}

void CLAB::OnBnClickedlendnew()
{
	// TODO: 在此添加控件通知处理程序代码

	if(!m_db.IsOpen() && !m_db.OpenEx(_T("DSN=mydb;DATABASE=Library;UID=admin;PWD=admin"), 
	 CDatabase::noOdbcDialog))
	{
		MessageBox(_T("数据库连接失败"));
		return;
	}

	CRecordset m_set(&m_db);
	CString query1, query2, query3;
	CDBVariant var;
	extern int nowuid;

	UpdateData(TRUE); 

	if(m_lab_uid == 0){MessageBox(_T("请输入借书证号！"));return;}
	if(m_lab_bno == 0){MessageBox(_T("请输入书号！"));return;}
	query1.Format(_T("select instore from lib_book_list where bno = %d"), m_lab_bno);

	try
	{
		m_set.Open(CRecordset::forwardOnly,query1);
		short nFields = m_set.GetODBCFieldCount();
		CString temp;
		while(!m_set.IsEOF())
		{
			for(short index = 0; index < nFields; index++)
			{
				m_set.GetFieldValue(index, var);
				temp = VariantToCString(&var);
			}
			m_set.MoveNext();
		}
		if(temp == _T("0"))
		{	
			/*
			CString query4, recent;
			query4.Format(_T("select MAX(R.date_return) ")
				_T("from lib_record as R, lib_book_list as L1, lib_book_list as L2 ")
				_T("where L1.bno = %d and L1.ISBN = L2.ISBN and L2.bno = R.bno")
				,m_lab_bno);
			m_set.Open(CRecordset::forwardOnly,query4);
			short nFields = m_set.GetODBCFieldCount();
			while(!m_set.IsEOF())
			{
				for(short index = 0; index < nFields; index++)
				{
					m_set.GetFieldValue(index, var);
					recent = VariantToCString(&var);
				}
				m_set.MoveNext();
			}
			MessageBox(_T("此书已被借走，相同书籍最近归还时间为%s"),recent);*/
			MessageBox(_T("此书已被借走"));
		}
		else
		{
			query2.Format(_T("insert into lib_record values ")
				_T("((select MAX(rid) from lib_record)+1, %d, %d, ")
				_T("%d, GETDATE(), default, 0)"),
				m_lab_uid, nowuid, m_lab_bno);
			m_db.ExecuteSQL(query2);
			query3.Format(_T("update lib_book_list set inStore = 0 where bno = %d;"),
				m_lab_bno);
			m_db.ExecuteSQL(query3);
			MessageBox(_T("借书成功"));
		}
	}
	catch(CDBException* pe)
	{
		MessageBox(_T("查询失败"));
		pe->Delete();
	}
	m_set.Close();
	m_db.Close();
}

void CLAB::OnBnClickedborrownew()
{
	// TODO: 在此添加控件通知处理程序代码
	
	if(!m_db.IsOpen() && !m_db.OpenEx(_T("DSN=mydb;DATABASE=Library;UID=admin;PWD=admin"), 
	 CDatabase::noOdbcDialog))
	{
		MessageBox(_T("数据库连接失败"));
		return;
	}

	CRecordset m_set(&m_db);
	CString query1, query2, query3;
	CDBVariant var;

	UpdateData(TRUE); 

	if(m_lab_uid == 0){MessageBox(_T("请输入借书证号！"));return;}
	if(m_lab_bno == 0){MessageBox(_T("请输入书号！"));return;}
	query1.Format(_T("select bno from lib_record where lib_uid = %d ")
		_T("and isReturned = 0"), m_lab_uid);

	try
	{
		CString temp; 
		temp.Format(_T("%d"),m_lab_bno);
		int exists = 0;

		m_set.Open(CRecordset::forwardOnly,query1);
		short nFields = m_set.GetODBCFieldCount();
	
		while(!m_set.IsEOF())
		{
			for(short index = 0; index < nFields; index++)
			{
				m_set.GetFieldValue(index, var);
				if(temp == VariantToCString(&var)){exists =1;break;}
			}
			m_set.MoveNext();
		}
		if(exists == 0)
		{
			MessageBox(_T("此书不在借阅列表中"));
		}
		else
		{
			query2.Format(_T("update lib_record set ")
				_T("date_return = GETDATE(), isReturned = 1 ")
				_T("where rid = (select rid from lib_record ")
				_T("where bno = %d and isReturned = 0)"),
				m_lab_bno);
			m_db.ExecuteSQL(query2);
			query3.Format(_T("update lib_book_list set inStore = 1 where bno = %d;"),
				m_lab_bno);
			m_db.ExecuteSQL(query3);
			MessageBox(_T("还书成功"));
		}
	}
	catch(CDBException* pe)
	{
		MessageBox(_T("查询失败"));
		pe->Delete();
	}
	m_set.Close();
	m_db.Close();
}

CString CLAB::VariantToCString(CDBVariant* var)
{
	CString str; //转换以后的字符串

	if(!var)
	{
		str = "NULL Var Parameter";
		return str;
	}
	switch(var->m_dwType)
	{
	case DBVT_SHORT:
		str.Format(L"%d",(int)var->m_iVal);
		break;
	case DBVT_LONG:
		str.Format(L"%d",var->m_lVal);
		break;
	case DBVT_SINGLE:
		str.Format(L"%10.6f",(double)var->m_fltVal);
		break;
	case DBVT_DOUBLE:
		str.Format(L"%10.6f",var->m_dblVal);
		break;
	case DBVT_BOOL:
		str = (var->m_boolVal==0) ?L"FALSE": L"TRUE";
		break;
	case DBVT_STRING:
		str = var->m_pstring->GetBuffer();
		break;
	case DBVT_ASTRING: 
		str = var->m_pstringA->GetBuffer(); 
		break; 
	case DBVT_WSTRING: 
		str = var->m_pstringW->GetBuffer(); 
		break;
	case DBVT_DATE:
		str.Format(L"%d-%d-%d",(var->m_pdate)->year,(var->m_pdate)->month,(var->m_pdate)->day);
		break;
	default:
		str.Format(L"Unk type %d\n",var->m_dwType);
		TRACE(L"Unknown type %d\n",var->m_dwType);
	}
	return str;
}