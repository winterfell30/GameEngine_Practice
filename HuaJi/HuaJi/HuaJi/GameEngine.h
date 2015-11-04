#pragma once

//-------------------------
//�����ļ�
//-------------------------

#include <Windows.h>

//-------------------------
//Windows��������
//-------------------------

int WINAPI        Winmain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR szCmdLine, int iCmdShow);
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//-------------------------
//��Ϸ���溯������
//-------------------------

BOOL GameInitialize(HINSTANCE hInstance);
void GameStart(HWND hWindow);
void GameEnd();
void GameActivate(HWND hWindows);
void GameDeactivate(HWND hWindows);
void GamePaint(HDC hDc);
void GameCycle();

//-------------------------
//GameEngine��
//-------------------------

class GameEngine
{
protected:
	static GameEngine* m_pGameEngine;
	HINSTANCE          m_hInstance;
	HWND               m_hWindow;
	TCHAR              m_szWindowClass[32];
	TCHAR              m_szTitle[32];
	WORD               m_wIcon, m_wSmallIcon;
	int                m_iWidth, m_iHeight;
	int                m_iFrameDelay;
	BOOL               m_bSleep;
public:
	//���캯��/��������
	GameEngine(HINSTANCE hInstanace, LPTSTR szWindowsClass, LPTSTR szTitle,
		WORD wIcon, WORD wSmallIcon, int iWidth = 640, int iHeight = 480);
	virtual ~GameEngine();
	//���淽��
	static GameEngine* GetEngine() { return m_pGameEngine; };
	BOOL               Initialize(int iCmdShow);
	LRESULT            HandleEvent(HWND hWindows, UINT msg, WPARAM wParam,
		LPARAM lParam);
	//���ʷ���
	HINSTANCE          GetInstance() { return m_hInstance; };
	HWND               GetWindow() { return m_hWindow; };
	void               SetWindow(HWND hWindows) { m_hWindow = hWindows; };
	LPTSTR             GetTitle() { return m_szTitle; };
	WORD               GetIcon() { return m_wIcon; };
	WORD               GetSmallIcon() { return m_wSmallIcon; };
	int                GetWidth() { return m_iWidth; };
	int                GetHeight() { return m_iHeight; };
	int                GetFrameDelay() { return m_iFrameDelay; };
	void               SetFrameDelay(int iFrameDelay) { m_iFrameDelay = 1000 / iFrameDelay; };
	BOOL               GetSleep() { return m_bSleep; };
	void               SetSleep(BOOL bSleep) { m_bSleep = bSleep; };
};

