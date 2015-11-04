//--------------------------------
//HuaJi
//C++Դ�ļ�
//--------------------------------

//--------------------------------
//�����ļ�
//--------------------------------

#include "Huaji.h"

//--------------------------------
//��Ϸ���溯��
//--------------------------------

BOOL GameInitialize(HINSTANCE hInstance)
{
	//������Ϸ����
	g_pGame = new GameEngine(hInstance, TEXT("HUAJI"),
		TEXT("HUAJI"), IDI_HUAJI, IDI_HUAJI_SM);
	if (g_pGame == NULL)
		return FALSE;
	
	//����Ƶ֡
	g_pGame->SetFrameDelay(15);
	return TRUE;
}

void GameStart(HWND hWindow)
{
	//�������������������
	srand(GetTickCount());
}

void GameEnd()
{
	//������Ϸ����
	delete g_pGame;
}

void GameActivate(HWND hWindow)
{
	HDC hDC;
	RECT rect;

	//����Ϸ��Ļ�ϻ����ı�
	GetClientRect(hWindow, &rect);
	hDC = GetDC(hWindow);
	DrawText(hDC, TEXT("Here comes the HUAJI!"), -1, &rect,
		DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	ReleaseDC(hWindow, hDC);
}

void GameDeactivate(HWND hWindow)
{
	HDC hDC;
	RECT rect;

	//����Ϸ��Ļ�ϻ����ı�
	GetClientRect(hWindow, &rect);
	hDC = GetDC(hWindow);
	DrawText(hDC, TEXT("The HUAJI has passed."), -1, &rect,
		DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	ReleaseDC(hWindow, hDC);
}

void GamePaint(HDC hDC)
{
}

void GameCycle()
{
	HDC hDC;
	HWND hWindow = g_pGame->GetWindow();

	//����Ϸ��Ļ�ϵ����λ�û��ƻ���ͼ��
	hDC = GetDC(hWindow);
	DrawIcon(hDC, rand() % g_pGame->GetWidth(), rand() % g_pGame->GetHeight(),
		(HICON)GetClassLong(hWindow, GCL_HICON));
	ReleaseDC(hWindow, hDC);
}