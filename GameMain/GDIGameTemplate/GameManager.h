#pragma once
#include "WinMain.h"
#include "InputSystem.h"
#include "TimeSystem.h"
#include "RenderSystem.h"
#include "SoundManager.h"
#include "CScene.h"
#include "StartScene.h"
#include "SceneManager.h"
namespace Game
{
	class GameManager
	{
	public:
		GameManager();

		~GameManager();

		void Initialize();

		void Update();

		void FixeUpdate();

		void Render();

		void Finalize();

		void Run();

		static GameManager* GetInstance();

		static void DestroyInstance();

	private:
		static GameManager* instance;
		SceneManager* m_sceneManager;
		CScene* m_curScene;
		HWND m_hWnd = nullptr;
		HDC m_hdc = nullptr;
		int m_UpdateCount = { 0 };
		int m_FixedUpdateCount = { 0 };
	};
}

