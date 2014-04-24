// Query.cpp : 实现文件
//

#include "stdafx.h"
#include "afxdialogex.h"
#include "myLibrary.h"
#include "Query.h"

// CQuery 对话框

IMPLEMENT_DYNAMIC(CQuery, CDialogEx)

CQuery::CQuery(CWnd* pParent /*=NULL*/)
	: CDialogEx(CQuery::IDD, pParent)
	, m_q_category(_T(""))
	, m_q_bookname(_T(""))
	, m_q_publisher(_T(""))
	, m_q_author(_T(""))
	, m_q_fromyear(0)
	, m_q_toyear(2050)
	, m_q_fromprice(0)
	, m_q_toprice(10000)
	, m_q_ISBN(_T(""))
{

}

CQuery::~CQuery()
{
}

void CQuery::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_category, m_q_category);
	DDX_Text(pDX, IDC_bkn, m_q_bookname);
	DDX_Text(pDX, IDC_pub, m_q_publisher);
	DDX_Text(pDX, IDC_author, m_q_author);
	DDX_Text(pDX, IDC_fromy, m_q_fromyear);
	DDX_Text(pDX, IDC_toy, m_q_toyear);
	DDX_Text(pDX, IDC_fromp, m_q_fromprice);
	DDX_Text(pDX, IDC_top, m_q_toprice);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
	DDX_Text(pDX, IDC_inv_ISBN, m_q_ISBN);
	DDX_Control(pDX, IDC_LIST2, m_ListCtrl2);
}


BEGIN_MESSAGE_MAP(CQuery, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CQuery::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDC_startQuery, &CQuery::OnBnClickedstartquery)
	ON_BN_CLICKED(IDC_startQuery2, &CQuery::OnBnClickedstartquery2)
END_MESSAGE_MAP()


// CQuery 消息处理程序


void CQuery::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CQuery::OnBnClickedstartquery()
{
	// TODO: 在此添加控件通知处理程序代码	

	if(!m_db.IsOpen() && !m_db.OpenEx(_T("DSN=mydb;DATABASE=Library;UID=admin;PWD=admin"), 
	CDatabase::openReadOnly | CDatabase::noOdbcDialog))
	{
		MessageBox(_T("数据库连接失败"));
		return;
	}

	CString  order = _T("title"); 
	CString c[] = {_T(""),_T(""),_T(""),_T(""),_T(""),_T("")};
	CString query, temp;
	CRecordset m_set(&m_db);

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

	UpdateData(TRUE); 

	if(m_q_category != _T(""))
		c[0].Format(_T("and category = '%s' "),m_q_category);
	if(m_q_bookname != _T(""))
		c[1].Format(_T("and title = '%s' "),m_q_bookname);
	if(m_q_publisher != _T(""))
		c[2].Format(_T("and publihser = '%s' "),m_q_publisher);
	c[3].Format(_T("and pub_year between %d and %d "),
			m_q_fromyear,m_q_toyear);
	if(m_q_author != _T(""))
		c[4].Format(_T("and author = '%s'"),m_q_author);
	c[5].Format(_T("and price between '%f' and '%f' "),
			m_q_fromprice, m_q_toprice);
	query.Format(_T("select * from lib_commonQuery where 1<=1 %s %s %s %s %s %s order by %s "),
		c[0],c[1],c[2],c[3],c[4],c[5],order);

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
		m_set.Close();//凡打开
		m_db.Close(); //皆关闭
	}
	catch(CDBException* pe)
	{
	   // The error code is in pe->m_nRetCode
	   MessageBox(_T("查询失败"));
	   pe->Delete();
	}
	m_set.Close();
	m_db.Close();
}


void CQuery::OnBnClickedstartquery2()
{
	// TODO: 在此添加控件通知处理程序代码
	
	if(!m_db.IsOpen() && !m_db.OpenEx(_T("DSN=mydb;DATABASE=Library;UID=admin;PWD=admin"), 
	CDatabase::openReadOnly | CDatabase::noOdbcDialog))
	{
		MessageBox(_T("数据库连接失败"));
		return;
	}

	CString query;
	CRecordset m_set(&m_db);

	m_ListCtrl2.InsertColumn(0, _T("书籍编号"), LVCFMT_CENTER, 80, 0);
	m_ListCtrl2.InsertColumn(1, _T("书号"), LVCFMT_CENTER, 120, 1);
	m_ListCtrl2.InsertColumn(2, _T("书名"), LVCFMT_CENTER, 196, 2);
	m_ListCtrl2.InsertColumn(3, _T("在库情况"), LVCFMT_CENTER, 80, 3);
	m_ListCtrl2.SetExtendedStyle(m_ListCtrl.GetExtendedStyle() | LVS_EX_GRIDLINES |
		LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP);

	UpdateData(TRUE); 

	if(m_q_ISBN == _T(""))
	{
		MessageBox(_T("请输入要查询的书籍！"));
		return;
	}
	else
	{
		query.Format(_T("select L.bno, L.ISBN, I.title, L.inStore ")
			_T("from lib_book_list as L, lib_book_info as I ")
			_T("where L.ISBN = I.ISBN and L.ISBN = '%s' order by bno"),
			m_q_ISBN);
	}

	try
	{
		m_set.Open(CRecordset::forwardOnly,query,CRecordset::readOnly);
		CDBVariant var; 
		m_ListCtrl2.DeleteAllItems();	
		short nFields = m_set.GetODBCFieldCount(); 
		int i = 0;
		while(!m_set.IsEOF())
		{
			for(short index = 0; index < nFields; index++)
			{
				m_set.GetFieldValue(index, var);
				if(index == 0)
					m_ListCtrl2.InsertItem(i, VariantToCString(&var));
				else
					m_ListCtrl2.SetItemText(i, index, VariantToCString(&var));
			}
			m_set.MoveNext();
			i++;
		}
		m_set.Close();//凡打开
		m_db.Close(); //皆关闭
	}
	catch(CDBException* pe)
	{
	   // The error code is in pe->m_nRetCode
	   MessageBox(_T("查询失败"));
	   pe->Delete();
	}
	m_set.Close();
	m_db.Close();
}

CString CQuery::VariantToCString(CDBVariant* var)
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