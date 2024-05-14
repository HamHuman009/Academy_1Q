#include "WinMain.h"




//AnimationResource* g_PlayerAnim;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
bool g_Mirror = false;
// 비주얼 스튜디오가 만든 템플릿은 다른 추가적인 내용이 많아 이해하기 어려워 가장 간단하게 작성함.

// 윈도우 프로시저 함수 선언

//void LoadResource();
//void ReleaseResource();

namespace global
{
	WinApp winApp;

	const WinApp& GetWinApp()
	{
		return winApp;
	}
}

constexpr int SCREEN_START_LEFT = 0;

constexpr int SCREEN_START_TOP = 0;

#define SCREEN_WIDTH  1920									// We want a 800 pixel width resolution
#define SCREEN_HEIGHT 1080	

BOOL bFullScreen = FALSE;
const TCHAR* appName = TEXT("Test Game Framework");

void ChangeToFullScreen(int width, int height);

void WinApp::Initialize(HINSTANCE hInstance)
{
	m_hInstance = hInstance;

	//const TCHAR* appName = TEXT("Test Game Framework");

	//Step 1: Registering the Window Class

	WNDCLASS wndClass;

	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = appName;

	RegisterClass(&wndClass);


	

	// Step 2: Creating the Window

	// 원하는 크기가 조정되어 리턴
	//SIZE clientSize = { 1920, 1080 };
	//RECT clientRect = { 0, 0, clientSize.cx, clientSize.cy };
	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CXSCREEN);
	RECT clientRect = { 0, 0, width, height };
	
	AdjustWindowRect(&clientRect, WS_OVERLAPPEDWINDOW, FALSE);


	/*m_hWnd = CreateWindow(appName, appName, WS_OVERLAPPED | WS_SYSMENU,
		SCREEN_START_LEFT, SCREEN_START_TOP, clientSize.cx, clientSize.cy, NULL, NULL, hInstance, NULL);*/
	m_hWnd = CreateWindow(appName, appName, WS_POPUP | WS_SYSMENU,
		SCREEN_START_LEFT, SCREEN_START_TOP, width, height, NULL, NULL, hInstance, NULL);

	
	if (!m_hWnd)
	{
		MessageBox(NULL, L"윈도우 생성 실패", L"에러", MB_OK | MB_ICONERROR);
		return;
	}


	//ShowWindow(m_hWnd, SW_SHOWNORMAL);
	ShowWindow(m_hWnd, SW_MAXIMIZE);
	
	UpdateWindow(m_hWnd);

	//Render::InitRender(m_hWnd, clientSize.cx, clientSize.cy);
	Render::InitRender(m_hWnd, width, height);

	// Step 3: Game Initialize Here
	Game::GameManager::GetInstance()->Initialize();
}


// 프로젝트 속성 -> 링커 -> 시스템 -> 하위 시스템 -> Windows로 변경
// 진입점 함수 정의

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	global::winApp.Initialize(hInstance);

	bool bUseConsole = true;
	if (bUseConsole)
	{
		AllocConsole();
		FILE* _tempFile;
		freopen_s(&_tempFile, "CONOUT$", "w", stdout);
	}	

	
	//LoadResource();

	// 대기가 없는 메세지 루프
	MSG msg;
	while (true)
	{
		// 메시지가 있으면 처리, 없으면 바로 게임 루프로 이동
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// WM_QUIT 메시지 확인
			if (msg.message == WM_QUIT)
				break;

			if (msg.message == WM_KEYDOWN)
			{
				Input::KeyDown(msg.wParam);
			}
			else if (msg.message == WM_KEYUP)
			{
				Input::KeyUp(msg.wParam);
			}
			else
			{
				DispatchMessage(&msg);
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// 게임 루프			
			Game::GameManager::GetInstance()->Run();
		}
	}

	//ReleaseResource();
	Game::GameManager::GetInstance()->ReleaseResource();
	if (bUseConsole)
	{
		FreeConsole();
	}

	//UnregisterClass(appName, hInstance);

	return static_cast<int>(msg.wParam);
}

// 윈도우 프로시저 함수 정의
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}
