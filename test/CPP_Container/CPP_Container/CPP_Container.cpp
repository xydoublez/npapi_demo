// CPP_Container.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "CPP_Container.h"

#define MAX_LOADSTRING 100

#define DOT_NET_BUTTON_PRESSED  0x0400

// import C# control function and structures
#import "lib\DotNetActiveX.tlb" named_guids raw_interfaces_only

HWND										_hAtl;
HWND										_hSelf;
IUnknown*									_pUnk;
DotNetActiveX::ICSSExplorerInterfacePtr		_pDotNetCOMPtr;

HINSTANCE _hWebLib = ::LoadLibrary(TEXT("ATL.DLL"));

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name



// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
void				loadActiveX(LPCTSTR strActiveXName);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_CPP_CONTAINER, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CPP_CONTAINER));

	loadActiveX(TEXT("DotNetActiveX.MyDotNetActiveX"));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CPP_CONTAINER));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_CPP_CONTAINER);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
	
   _hSelf = hWnd;

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	char *strHelloWorld = "Hello World!";
	char *strOK = "OK";

	_bstr_t bstrHelloWorld(strHelloWorld);
	_bstr_t bstrOK(strOK);

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case IDM_BTN_CAP_HELLOWORLD:
			_pDotNetCOMPtr->setButtonCaption(bstrHelloWorld);
			break;
		case IDM_BTN_CAP_OK:
			_pDotNetCOMPtr->setButtonCaption(bstrOK);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_SIZE :
        // Get the dimensions of the main window's client 
        // area, and enumerate the child windows. Pass the 
        // dimensions to the child windows during enumeration. 
		RECT rcClient; 
        GetClientRect(_hSelf, &rcClient);  
		MoveWindow(_hAtl, 0, 0, rcClient.right, rcClient.bottom, TRUE);
		break;
	case WM_DESTROY:
		_pDotNetCOMPtr->Release();
		::DestroyWindow(_hAtl);
		_pUnk->Release();	
		::FreeLibrary(_hWebLib);		
		PostQuitMessage(0);
		break;
	case DOT_NET_BUTTON_PRESSED:
		MessageBox(NULL, TEXT("Message from C# arrived: Button Pressed!!"), szTitle, MB_OK | MB_ICONINFORMATION);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

void loadActiveX(LPCTSTR strActiveXName)
{
	//Initialize ATL control containment code.
	BOOL (WINAPI *m_AtlAxWinInit)();
	m_AtlAxWinInit = (BOOL (WINAPI *)(void))::GetProcAddress(_hWebLib, "AtlAxWinInit");
    m_AtlAxWinInit();

	// Get the dimensions of the main window's client 
    // area, and enumerate the child windows. Pass the 
    // dimensions to the child windows during enumeration. 
	RECT rcClient; 

    GetClientRect(_hSelf, &rcClient); 

	_hAtl = ::CreateWindowEx(
			WS_EX_CLIENTEDGE,\
			TEXT("AtlAxWin"),\
			strActiveXName,\
			WS_CHILD | WS_VISIBLE | /*WS_CLIPCHILDREN | */WS_EX_RTLREADING,\
			0, 0, rcClient.right, rcClient.bottom,\
			_hSelf,\
			NULL,\
			NULL,\
			NULL);

	if (!_hAtl)
	{
		MessageBox( NULL, TEXT("Can not load AtlAxWin!"), szTitle, MB_OK | MB_ICONSTOP);
		throw int(106901);
	}

	HRESULT (WINAPI *m_AtlAxGetControl) (HWND h, IUnknown** pp);
	m_AtlAxGetControl = (HRESULT (WINAPI *) (HWND, IUnknown**))::GetProcAddress(_hWebLib, "AtlAxGetControl");

	m_AtlAxGetControl(_hAtl, &_pUnk);

	_pUnk->QueryInterface(__uuidof(DotNetActiveX::ICSSExplorerInterface),(LPVOID *) &_pDotNetCOMPtr);

	if (_pDotNetCOMPtr != NULL)
	{
		_pDotNetCOMPtr->setAdapterDllPtr((long) _hSelf);
	}
	else
	{
		// Get the dimensions of the main window's client 
		// area, and enumerate the child windows. Pass the 
		// dimensions to the child windows during enumeration. 
		RECT rcClient; 
		GetClientRect(_hSelf, &rcClient);

		::DestroyWindow(_hAtl);
		_hAtl = ::CreateWindowEx(
					WS_EX_CLIENTEDGE,\
					TEXT("AtlAxWin"),\
					TEXT("MSHTML:""Please register ActiveX control before using this plugin."""),\
					WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_EX_RTLREADING,\
					0, 0, rcClient.right, rcClient.bottom,\
					_hSelf,\
					NULL,\
					NULL,\
					NULL);
	}
}
