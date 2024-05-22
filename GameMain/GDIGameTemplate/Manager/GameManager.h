#pragma once
#include "../WinMain.h"

#include "../System/InputSystem.h"
#include "../System/TimeSystem.h"
#include "../System/RenderSystem.h"
#include "../System/SoundSystem.h"

#include "../Manager/SceneManager.h"

#include "../GameLogic/Animation.h"
#include "../GameLogic/Ranking.h"
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

		void PostProcessing();

		void EndRender();

		void Finalize();

		void Run();

		void LoadResource();

		void ReleaseResource();

		static GameManager* GetInstance();

		static void DestroyInstance();

		Gdiplus::Bitmap* sceneBitmap;

		UINT FinalScore;

		UINT BossCount;

		int GetRoot();

		void SetRoot(int root);

		Ranking* m_Ranking;

		Vector2 m_cameraPosition;

		float mVolume;

		const char* mySoundRate;

		void SetCameraShakeTimer(float timer);

	private:
		static GameManager* instance;
		SceneManager* m_sceneManager;
		CScene* m_curScene;
		
		HWND m_hWnd = nullptr;
		HDC m_hdc = nullptr;
		int m_UpdateCount = { 0 };
		int m_FixedUpdateCount = { 0 };

		int g_root;

		float cameraShakeTimer = 0.f;
	};
}

