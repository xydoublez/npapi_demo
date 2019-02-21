// DigTest.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DigTest.h"
#include "afxdialogex.h"

HINSTANCE _hWebLib = ::LoadLibrary(TEXT("ActivexTest.dll"));


// CDigTest �Ի���

IMPLEMENT_DYNAMIC(CDigTest, CDialogEx)

CDigTest::CDigTest(CWnd* pParent /*=NULL*/)
	: CDialogEx(digTest, pParent)
{

}

CDigTest::~CDigTest()
{
}

void CDigTest::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDigTest, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDigTest::OnBnClickedOk)
END_MESSAGE_MAP()


// CDigTest ��Ϣ�������


void CDigTest::OnBnClickedOk()
{
	 
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}

int CDigTest::AndTo(int a, int b)
{
	int sum = a + b;
	CString str;
	
	str.Format("%d", sum);
	/*BSTR bstrText = str.AllocSysString();
	BSTR* sAnswers;
		

	m_pDotNetCOMPtr->Say(bstrText, sAnswers);*/
	
	CEdit* pBoxOne;
	pBoxOne = (CEdit*)GetDlgItem(txtEdit);
	/*CStringA msg(*sAnswers);*/
	pBoxOne->SetWindowText(str);
	
	//SysFreeString(bstrText); // �����ͷ�
	//*sAnswers = NULL;
	return sum;
}



void CDigTest::loadActiveX(LPCTSTR strActiveXName)
{
	////Initialize ATL control containment code.
	//BOOL(WINAPI *m_AtlAxWinInit)();
	//m_AtlAxWinInit = (BOOL(WINAPI *)(void))::GetProcAddress(_hWebLib, "AtlAxWinInit");
	//if (m_AtlAxWinInit == NULL)
	//{
	//	//not find
	//}
	//m_AtlAxWinInit();

	_hSelf = this->m_hWnd;
	
	
	// Get the dimensions of the main window's client 
	// area, and enumerate the child windows. Pass the 
	// dimensions to the child windows during enumeration. 
	RECT rcClient;
	//::GetWindowRect(_hSelf, &rcClient);
	::GetClientRect(_hSelf,&rcClient);

	_hAtl = ::CreateWindowEx(
		WS_EX_CLIENTEDGE, \
		TEXT("AtlAxWin"), \
		strActiveXName, \
		WS_CHILD | WS_VISIBLE |WS_EX_RTLREADING, 
		0, 0, rcClient.right, rcClient.bottom, 
		_hSelf, 
		NULL, 
		NULL, 
		NULL);

	if (!_hAtl)
	{
		::MessageBox(this->m_hWnd, "��־ǿ�Ҳ�����", "", 0);
		//throw int(106901);
	}

	//HRESULT(WINAPI *m_AtlAxGetControl) (HWND h, IUnknown** pp);
	//m_AtlAxGetControl = (HRESULT(WINAPI *) (HWND, IUnknown**))::GetProcAddress(_hWebLib, "AtlAxGetControl");

	//m_AtlAxGetControl(_hAtl, &_pUnk);

	//_pUnk->QueryInterface(__uuidof(ActivexTest::IDemo), (LPVOID *)&_pDotNetCOMPtr);

	//if (_pDotNetCOMPtr != NULL)
	//{
	//	//_pDotNetCOMPtr->setAdapterDllPtr((long)_hSelf);
	//}
	
	
}



BOOL CDigTest::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	CEdit* pBoxOne;
	pBoxOne = (CEdit*)GetDlgItem(txtEdit);
	pBoxOne->SetWindowText("TEST1");

	loadActiveX(TEXT("ActivexTest.Demo"));

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
