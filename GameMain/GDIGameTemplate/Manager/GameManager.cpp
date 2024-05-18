#include "GameManager.h"



namespace Game
{
	
	//Gdiplus::Bitmap* hTestBitmap = nullptr; // ���� ����
	GameManager* GameManager::instance = nullptr;
	mySound::SoundManager* SMInstance = nullptr;
	GameManager::GameManager()
	{
	}
	GameManager::~GameManager()
	{
	}
	void GameManager::Initialize()
	{
		Input::InitInput();
		High_Resolution_Time::InitTime();
		m_hWnd = global::GetWinApp().GetWindow();
		m_hdc = GetDC(m_hWnd);
		/*mySound::SoundManager::Init();
		mySound::SoundManager::GetInstance()->LoadSounds(mySound::SoundList::Singing, false, "singing.wav");*/
		SMInstance = mySound::SoundManager::GetInstance();
		SMInstance->LoadMusic(mySound::eSoundList::Singing, false, "singing.wav");
		m_sceneManager = SceneManager::GetInstance();
		m_curScene = m_sceneManager->GetCurScene();
	}

	void GameManager::Update()
	{
		++m_UpdateCount;

		Input::UpdateMouse();
		if (m_curScene != m_sceneManager->GetCurScene()) {
			m_curScene = m_sceneManager->GetCurScene();
		}
		m_curScene->Update();
		Input::ResetInput();

		
	}
	
	void GameManager::FixeUpdate()
	{
		static ULONGLONG elapsedTime;

		elapsedTime += High_Resolution_Time::GetDeltaTime();
		
		while (elapsedTime >= 20) //0.02��
		{
			++m_FixedUpdateCount;
			
			m_curScene->FixedUpdate();

			elapsedTime -= 20;
		}
	}

	void GameManager::Render()
	{
		Render::BeginDraw();
		


		m_curScene->Render();

		//string FrameRate = std::to_string(High_Resolution_Time::GetFrameRate());

		//Render::DrawTextW(10, 50, FrameRate.c_str(), RGB(255, 0, 0));

		

		Render::EndDraw();

		
	}
	void GameManager::Finalize()
	{
		SceneManager::GetInstance()->DestroyInstance();
		CResourceManager::GetInstance()->DestroyInstance();
		
		Render::ReleaseRender();
		mySound::SoundManager::GetInstance()->RelaseSounds();
		mySound::SoundManager::DestroyInstance();
		//SMInstance->RelaseSounds();
		//SMInstance->DestroyInstance(); //153���� �޸� ���� ��ü..

	}
	void GameManager::Run()
	{
		High_Resolution_Time::UpdateTime();

		FixeUpdate();

		Update();

		Render();
	}

	GameManager* GameManager::GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new GameManager();
		}
		return instance;
	}
	void GameManager::DestroyInstance()
	{
		if (instance != nullptr)
		{
			delete instance;
			instance = nullptr;
		}
	}


	
	//AnimationResource* g_PlayerAnim = nullptr;
	//void LoadResource()
	//{
	//	g_PlayerAnim = new AnimationResource;

	//	g_PlayerAnim->LoadAnimImage(L"../Resource/Ken.png");
	//	g_PlayerAnim->LoadAnimMotion(L"../Resource/KenIdle.txt");				 //	OBJECT_STATUS_IDLE,
	//	g_PlayerAnim->LoadAnimMotion(L"../Resource/KenMove.txt");				 //	OBJECT_STATUS_MOVE,
	//	g_PlayerAnim->LoadAnimMotion(L"../Resource/KenAttack.txt", false);		 //	OBJECT_STATUS_ATTACK

	//}

	//void ReleaseResource()
	//{
	//	delete g_PlayerAnim;
	//}

	void GameManager::LoadResource() {
		//hTestBitmap = Gdiplus::Bitmap::FromFile(L"image1.png");
	}

	void GameManager::ReleaseResource() {
		//delete hTestBitmap;
	}
	
}
