#include "GameEngine.h"

//--------------------
//��̬������ʼ��
//--------------------

GameEngine *GameEngine::m_pGameEngine = NULL;

//--------------------
//Windows����
//--------------------

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR szCmdLine, int iCmdShow)
{
	MSG            msg;
	static int     iTickTrigger = 0;
	int            iTickCount;

	if (GameInitialize(hInstance))
	{
		//��ʼ����Ϸ����
		if (!GameEngine::GetEngine()->Initialize(iCmdShow))
			return FALSE;
		//��������Ϣѭ��
		while (TRUE)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				//������Ϣ
				if (msg.message == WM_QUIT)
					break;
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				//ȷ����Ϸ����û������
				if (!GameEngine::GetEngine()->GetSleep())
				{
					//���δ�������鿴�Ƿ����һ������
					iTickCount = GetTickCount();
					if (iTickCount > iTickTrigger)
					{
						iTickTrigger = iTickCount + GameEngine::GetEngine()->GetFrameDelay();
					}
				}
			}
		}
		return (int)msg.wParam;
	}
	//������Ϸ
	GameEnd();
	return true;
}

LRESULT CALLBACK WndProc(HWND hWindows, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//�����е�Windows��Ϣ���ݸ���Ϸ����
	return GameEngine::GetEngine()->HandleEvent(hWindows, msg, wParam, lParam);
}

//-----------------
//GameEngine�Ĺ��캯��/��������
//-----------------

GameEngine::GameEngine(HINSTANCE hInstance, LPTSTR szWindowsClass,
	LPTSTR szTitle, WORD wIcon, WORD wSmallIcon, int iWidth, int iHeight)
{
	//������Ϸ����ĳ�Ա����
	m_pGameEngine = this;
	m_hInstance = hInstance;
	m_hWindow = NULL;
	if (lstrlen(szWindowsClass) > 0)
		lstrcpy(m_szWindowClass, szWindowsClass);
	if (lstrlen(m_szTitle) > 0)
		lstrcpy(m_szTitle, szTitle);
	m_wIcon = wIcon;
	m_wSmallIcon = wSmallIcon;
	m_iWidth = iWidth;
	m_iHeight = iHeight;
	m_iFrameDelay = 50; //Ĭ��Ϊ20֡ÿ��
	m_bSleep = TRUE;
}

GameEngine::~GameEngine()
{
}

//---------------------
//��Ϸ���泣�淽��
//---------------------

BOOL GameEngine::Initialize(int iCmdShow)
{
	WNDCLASSEX wndclass;

	//���������ڵĴ�����
	wndclass.cbSize = sizeof(wndclass);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = m_hInstance;
	wndclass.hIcon = LoadIcon(m_hInstance, MAKEINTRESOURCE(GetIcon()));
	wndclass.hIconSm = LoadIcon(m_hInstance, MAKEINTRESOURCE(GetSmallIcon()));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = m_szWindowClass;

	//ע�ᴰ����
	if (!RegisterClassEx(&wndclass))
		return FALSE;

	//������Ϸ��С���㴰�ڴ�С��λ��
	int iWindowWidth = m_iWidth + GetSystemMetrics(SM_CXFIXEDFRAME) * 2,
		iWindowHeight = m_iHeight + GetSystemMetrics(SM_CXFIXEDFRAME) * 2 +
		GetSystemMetrics(SM_CYCAPTION);
	if (wndclass.lpszMenuName != NULL)
		iWindowHeight += GetSystemMetrics(SM_CYMENU);
	int iXWindowPos = (GetSystemMetrics(SM_CXSCREEN) - iWindowWidth) / 2,
		iYWindowPos = (GetSystemMetrics(SM_CYSCREEN) - iWindowHeight) / 2;

	//��������
	m_hWindow = CreateWindow(m_szWindowClass, m_szTitle, WS_POPUPWINDOW |
		WS_CAPTION | WS_MINIMIZEBOX, iXWindowPos, iYWindowPos, iWindowWidth,
		iWindowHeight, NULL, NULL, m_hInstance, NULL);
	if (!m_hWindow)
		return FALSE;

	//��ʾ�͸��´���
	ShowWindow(m_hWindow, iCmdShow);
	UpdateWindow(m_hWindow);

	return TRUE;
}

LRESULT GameEngine::HandleEvent(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//��Windows��Ϣ���ݸ���Ϸ�����Ա����
	switch (msg)
	{
	case WM_CREATE:
		//������Ϸ���ڲ���ʼ��Ϸ
		SetWindow(hWindow);
		GameStart(hWindow);
		return 0;

	case WM_SETFOCUS:
		//������Ϸ����������״̬
		GameActivate(hWindow);
		SetSleep(FALSE);
		return 0;

	case WM_KILLFOCUS:
		//ͣ����Ϸ����������״̬
		GameDeactivate(hWindow);
		SetSleep(TRUE);
		return 0;

	case WM_PAINT:
		HDC       hDC;
		PAINTSTRUCT  ps;
		hDC = BeginPaint(hWindow, &ps);

		//������Ϸ
		GamePaint(hDC);

		EndPaint(hWindow, &ps);
		return 0;
	case WM_DESTROY:
		//������Ϸ���˳�Ӧ�ó���
		GameEnd();
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWindow, msg, wParam, lParam);
}