#pragma once

#include <SDKDDKVer.h>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "stdafx.h"

#include "System/InputSystem.h"
#include "System/RenderSystem.h"
#include "System/TimeSystem.h"

#include "Manager/GameManager.h"

#include "GameLogic/AnimationResource.h"

class WinApp
{
public:

	WinApp() = default;
	~WinApp() = default;

	void Initialize(HINSTANCE hInstance);

	HINSTANCE GetInstance() const { return m_hInstance; }

	HWND GetWindow() const { return m_hWnd; }

	const int GetWidth() const { return width; }
	const int GetHeight() const { return height; }

	//static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:

	HINSTANCE m_hInstance = { 0 };  // HINSTANCE is a handle to an instance of a module.
	HWND m_hWnd = { 0 };			// HWND is a handle to a window.

	int width = 1024;
	int height = 768;
};

namespace global
{
	const WinApp& GetWinApp();
}