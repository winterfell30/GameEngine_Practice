//--------------------------------
//HuaJi
//C++源文件
//--------------------------------

//--------------------------------
//包含文件
//--------------------------------

#include "Huaji.h"

//--------------------------------
//游戏引擎函数
//--------------------------------

BOOL GameInitialize(HINSTANCE hInstance)
{
	//创建游戏引擎
	g_pGame = new GameEngine(hInstance, TEXT("HUAJI"),
		TEXT("HUAJI"), IDI_HUAJI, IDI_HUAJI_SM);
	if (g_pGame == NULL)
		return FALSE;
	
	//设置频帧
	g_pGame->SetFrameDelay(15);
	return TRUE;
}

void GameStart(HWND hWindow)
{
	//生成随机数生成器种子
	srand(GetTickCount());
}

void GameEnd()
{
	//清理游戏引擎
	delete g_pGame;
}

void GameActivate(HWND hWindow)
{
	HDC hDC;
	RECT rect;

	//在游戏屏幕上绘制文本
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

	//在游戏屏幕上绘制文本
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

	//在游戏屏幕上的随机位置绘制滑稽图标
	hDC = GetDC(hWindow);
	DrawIcon(hDC, rand() % g_pGame->GetWidth(), rand() % g_pGame->GetHeight(),
		(HICON)GetClassLong(hWindow, GCL_HICON));
	ReleaseDC(hWindow, hDC);
}