// InStore.cpp : 实现文件
//

#include "stdafx.h"
#include "myLibrary.h"
#include "InStore.h"
#include "afxdialogex.h"
#include <sstream>
#include <fstream>

// CInStore 对话框

IMPLEMENT_DYNAMIC(CInStore, CDialogEx)

CInStore::CInStore(CWnd* pParent /*=NULL*/)
	: CDialogEx(CInStore::IDD, pParent)
	, m_is_ISBN(_T(""))
	, m_is_title(_T(""))
	, m_is_author(_T(""))
	, m_is_price(0)
	, m_is_category(_T(""))
	, m_is_publisher(_T(""))
	, m_is_pubyear(0)
	, m_is_num(0)
{

}

CInStore::~CInStore()
{
}

void CInStore::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ISBN, m_is_ISBN);
	DDX_Text(pDX, IDC_title, m_is_title);
	DDX_Text(pDX, IDC_author, m_is_author);
	DDX_Text(pDX, IDC_price, m_is_price);
	DDX_Text(pDX, IDC_incategory, m_is_category);
	DDX_Text(pDX, IDC_publisher, m_is_publisher);
	DDX_Text(pDX, IDC_pubyear, m_is_pubyear);
	DDX_Text(pDX, IDC_num, m_is_num);
}


BEGIN_MESSAGE_MAP(CInStore, CDialogEx)
	ON_BN_CLICKED(IDC_single, &CInStore::OnBnClickedsingle)
	ON_BN_CLICKED(IDC_amass, &CInStore::OnBnClickedamass)
END_MESSAGE_MAP()


// CInStore 消息处理程序


void CInStore::OnBnClickedsingle()
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
	int m_is_bno = 0;

	UpdateData(TRUE);

	if(m_is_ISBN == "" || m_is_category == ""|| m_is_title == "" || m_is_price < 0 ||
		m_is_publisher == "" || m_is_pubyear <= 0 || m_is_author == "" || m_is_num <= 0)
	{
		MessageBox(_T("输入信息有误，请检查！"));
		return;
	}

	try
	{
		if(MessageBox(_T("确认无误吗？"),_T("提示-图书管理系统"),MB_OKCANCEL)==IDCANCEL)
			return;
		query1.Format(_T("insert into lib_book_info values ")
			_T("('%s','%s','%s','%s',%d,'%s',%lf)"),
			m_is_ISBN, m_is_category, m_is_title, m_is_publisher, m_is_pubyear,
			m_is_author, m_is_price);
		m_db.ExecuteSQL(query1);
		query2.Format(_T("select MAX(bno) from lib_book_list"));
		m_set.Open(CRecordset::forwardOnly,query2);
		short nFields = m_set.GetODBCFieldCount();
		while(!m_set.IsEOF())
		{
			for(short index = 0; index < nFields; index++)
			{
				m_set.GetFieldValue(index, var);
				m_is_bno = _ttoi(VariantToCString(&var));
			}
			m_set.MoveNext();
		}
		for(int i = 1; i <= m_is_num; i++)
		{
			query3.Format(_T("insert into lib_book_list values (%d, '%s', 1)"),
				m_is_bno + i, m_is_ISBN);
			m_db.ExecuteSQL(query3);
		}
		MessageBox(_T("入库成功"));
	}
	catch(CDBException* pe)
	{
		MessageBox(_T("入库失败"));
		pe->Delete();
	}
	m_set.Close();
	m_db.Close();
}

void CInStore::OnBnClickedamass()
{
	// TODO: 在此添加控件通知处理程序代码

	// 设置过滤器    
    TCHAR szFilter[] = _T("文本文件(*.txt)|*.txt|所有文件(*.*)|*.*||");    
    // 构造打开文件对话框    
    CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);    
    CString strFilePath;    
 
    // 显示打开文件对话框    
    if (IDOK == fileDlg.DoModal())    
    {    
        // 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里    
        strFilePath = fileDlg.GetPathName();

		if(!m_db.IsOpen() && !m_db.OpenEx(_T("DSN=mydb;DATABASE=Library;UID=admin;PWD=admin"), 
			CDatabase::noOdbcDialog))
		{
			MessageBox(_T("数据库连接失败"));
			return;
		}

		USES_CONVERSION;
		CString temp[8];
		CDBVariant var;
		size_t comma = 0;
		LPSTR pfile = T2A(strFilePath);
		std::ifstream ifs(pfile);
		std::string line,word;

		try
		{
			while(std::getline(ifs,line))
			{
				for(int j = 0; j < 8; j++){temp[j]="";}
				
				std::istringstream stream(line);
				int m_is_bno = 0;
				int i = 0;
				CString query1, query2, query3 = NULL;
				CRecordset m_set(&m_db);

				for(int j = 0; j < line.size(); j++)
				{
					if(line[j]!=',')
					{
						temp[i] = temp[i] + line[j];
					}
					else
					{
						i++;
					}
				}

				if(temp[0] == "" || temp[1] == ""|| temp[2] == "" ||
					temp[3] == "" || _ttoi(temp[4]) <= 0 || temp[5] == "" || 
					_ttoi(temp[7]) <= 0 || _ttol(temp[6]) < 0)
				{
					MessageBox(_T("输入信息有误，跳过一行！"));
				}
				else
				{
					query1.Format(_T("insert into lib_book_info values ")
						_T("('%s','%s','%s','%s',%d,'%s',%lf)"),
						temp[0],temp[1],temp[2],temp[3],_ttoi(temp[4]),temp[5],_ttof(temp[6]));
					m_db.ExecuteSQL(query1);
					query2.Format(_T("select MAX(bno) from lib_book_list"));
					m_set.Open(CRecordset::forwardOnly,query2);
					short nFields = m_set.GetODBCFieldCount();
					while(!m_set.IsEOF())
					{
						for(short index = 0; index < nFields; index++)
						{
							m_set.GetFieldValue(index, var);
							m_is_bno = _ttoi(VariantToCString(&var));
						}
						m_set.MoveNext();
					}
					for(int j = 1; j <= _ttoi(temp[7]); j++)
					{
						query3.Format(_T("insert into lib_book_list values (%d, '%s', 1)"),
							m_is_bno + j, temp[0]);
						m_db.ExecuteSQL(query3);
					}
				}
				m_set.Close();
			}
			MessageBox(_T("入库完成"));
		}
		catch(CDBException* pe)
		{
			MessageBox(_T("入库失败"));
			pe->Delete();
		}
		m_db.Close();

	}
}

CString CInStore::VariantToCString(CDBVariant* var)
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