#pragma once

// CInStore 对话框

class CInStore : public CDialogEx
{
	DECLARE_DYNAMIC(CInStore)

private:
	CDatabase m_db;

public:
	CInStore(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CInStore();

// 对话框数据
	enum { IDD = IDD_InStore };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_is_ISBN;
	CString m_is_title;
	CString m_is_author;
	double m_is_price;
	CString m_is_category;
	CString m_is_publisher;
	int m_is_pubyear;
	int m_is_num;
	afx_msg void OnBnClickedsingle();
	afx_msg void OnBnClickedamass();
	CString VariantToCString(CDBVariant* var);
};
