#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CLAB 对话框

class CLAB : public CDialogEx
{
	DECLARE_DYNAMIC(CLAB)

private:
	CDatabase m_db;

public:
	CLAB(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLAB();

// 对话框数据
	enum { IDD = IDD_LAB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_lab_bno;
	afx_msg void OnBnClickedpersonaldata();
	CListCtrl m_ListCtrl;
	int m_lab_uid;
	afx_msg void OnBnClickedlendnew();
	afx_msg void OnBnClickedborrownew();
	CString VariantToCString(CDBVariant* var);
};
