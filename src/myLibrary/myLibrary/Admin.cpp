// Admin.cpp : 实现文件
//

#include "stdafx.h"
#include "myLibrary.h"
#include "Admin.h"
#include "afxdialogex.h"
#include "InStore.h"
#include "LAB.h"
#include "IDCard.h"
#include "Query.h"


// CAdmin 对话框

IMPLEMENT_DYNAMIC(CAdmin, CDialogEx)

CAdmin::CAdmin(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAdmin::IDD, pParent)
{

}

CAdmin::~CAdmin()
{
}

void CAdmin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAdmin, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CAdmin::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CAdmin::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CAdmin::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CAdmin::OnBnClickedButton4)
END_MESSAGE_MAP()


// CAdmin 消息处理程序

void CAdmin::OnBnClickedButton1()
{
	CInStore instoreDlg;
	instoreDlg.DoModal();
}

void CAdmin::OnBnClickedButton3()
{
	CLAB labDlg;
	labDlg.DoModal();
}


void CAdmin::OnBnClickedButton2()
{
	CIDCard idDlg;
	idDlg.DoModal();
}


void CAdmin::OnBnClickedButton4()
{
	CQuery queryDlg;
	queryDlg.DoModal();
}
