#pragma once
#import "..\\lib\\ActivexTest.tlb" named_guids raw_interfaces_only


// CDigTest 对话框

class CDigTest : public CDialogEx
{
	DECLARE_DYNAMIC(CDigTest)

protected:
	HWND										_hAtl;
	HWND										_hSelf;
	IUnknown*									_pUnk;
	ActivexTest::IDemoPtr _pDotNetCOMPtr;


	HWND m_hActiveXSelf;
	IUnknown* m_pUnk;
	ActivexTest::IDemoPtr m_pDotNetCOMPtr;
	


	CWnd* m_pWndFramework;
	
public:
	CDigTest(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDigTest();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = digTest };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	int AndTo(int a, int b);
	void loadActiveX(LPCTSTR strActiveXName);

	virtual BOOL OnInitDialog();
};