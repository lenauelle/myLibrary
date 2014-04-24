#pragma once
#include "afxcmn.h"



// CQuery 对话框

class CQuery : public CDialogEx
{
	DECLARE_DYNAMIC(CQuery)

private:
	CDatabase m_db;

public:
	CQuery(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CQuery();

// 对话框数据
	enum { IDD = IDD_Query };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	CString m_q_category;
	CString m_q_bookname;
	CString m_q_publisher;
	CString m_q_author;
	int m_q_fromyear;
	int m_q_toyear;
	float m_q_fromprice;
	float m_q_toprice;
	afx_msg void OnBnClickedstartquery();
	CListCtrl m_ListCtrl;
	CString m_q_ISBN;
	afx_msg void OnBnClickedstartquery2();
	CListCtrl m_ListCtrl2;

	CString VariantToCString(CDBVariant* var);
};
