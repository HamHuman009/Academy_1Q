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
		m_Ranking = new Ranking();
		Input::InitInput();
		High_Resolution_Time::InitTime();
		m_hWnd = global::GetWinApp().GetWindow();
		m_hdc = GetDC(m_hWnd);
		/*mySound::SoundManager::Init();
		mySound::SoundManager::GetInstance()->LoadSounds(mySound::SoundList::Singing, false, "singing.wav");*/
		SMInstance = mySound::SoundManager::GetInstance();
		SMInstance->LoadMusic(mySound::eSoundList::BGM, true, "BGM.mp3");
		SMInstance->LoadMusic(mySound::eSoundList::BGM2, true, "BGM2.mp3");
		SMInstance->LoadMusic(mySound::eSoundList::BGM3, true, "BGM3.mp3");
		SMInstance->LoadMusic(mySound::eSoundList::Button, false, "button.wav");
		SMInstance->LoadMusic(mySound::eSoundList::Water, false, "water.wav");

		/*SMInstance->LoadMusic(mySound::eSoundList::s_title,true,"Sound_Title_MainTheme_01.wav");
		SMInstance->LoadMusic(mySound::eSoundList::s_intro,true,"Sound_Intro_Intro Theme_01.wav");
		SMInstance->LoadMusic(mySound::eSoundList::s_talk,true,"Sound_Talk_Talk Theme_01.wav");
		SMInstance->LoadMusic(mySound::eSoundList::s_ingame,true,"Sound_Stage_Ingame Theme_01.wav");
		SMInstance->LoadMusic(mySound::eSoundList::s_ending,true,"Sound_Ending_Ending Theme_01.wav");

		SMInstance->LoadMusic(mySound::eSoundList::s_button,false,"Sound_Button Use_01.wav");
		SMInstance->LoadMusic(mySound::eSoundList::s_dialogue,false,"Sound_Talk Output_01.wav");
		SMInstance->LoadMusic(mySound::eSoundList::s_talkbubble,false,"Sound_Comic Talk_01.wav");
		SMInstance->LoadMusic(mySound::eSoundList::s_scooperDown,false,"Sound_Stage_Scooper Down_01.wav");
		SMInstance->LoadMusic(mySound::eSoundList::s_scooperUp,false,"Sound_Stage_Scooper Up_01.wav");
		SMInstance->LoadMusic(mySound::eSoundList::s_fishMove,false,"Sound_Stage_Fish Move_01.wav");
		SMInstance->LoadMusic(mySound::eSoundList::s_fishCaught,false,"Sound_Stage_Fish Catch_01.wav");
		SMInstance->LoadMusic(mySound::eSoundList::s_bossCaught,false,"Sound_Stage_Boss Fish Catch_01.wav");
		SMInstance->LoadMusic(mySound::eSoundList::s_sceneTrans,false,"Sound_Move Scene Theme_01.wav");
		SMInstance->LoadMusic(mySound::eSoundList::s_angerStart,false,"Sound_Anger Sound_01.wav");
		SMInstance->LoadMusic(mySound::eSoundList::s_angerTerm,false,"Sound_Anger Sound_02.wav");
		SMInstance->LoadMusic(mySound::eSoundList::s_bubble,false,"Sound_Fish breathing _01.wav");
		SMInstance->LoadMusic(mySound::eSoundList::s_finalscoreShownup,false,"Sound_Final Score Sound_01.wav");
		
		SMInstance->LoadMusic(mySound::eSoundList::Water, false, "Sound_Dad Voice_01.wav");
		SMInstance->LoadMusic(mySound::eSoundList::Water, false, "Sound_Kid Voice_01.wav");
		*/

		

		m_sceneManager = SceneManager::GetInstance();
		m_sceneManager->Init();
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

		std::string FrameRate = std::to_string(High_Resolution_Time::GetFrameRate());
		const char* myFrameRate = FrameRate.c_str();
		Render::DrawTextW(10, 50, myFrameRate, RGB(255, 0, 0));

		

		Render::EndDraw();

		
	}
	void GameManager::Finalize()
	{	
		//m_Ranking->saveRankings();
		delete m_Ranking;
		SceneManager::GetInstance()->DestroyInstance();
		CResourceManager::GetInstance()->DestroyInstance();
		
		Render::ReleaseRender();
		//mySound::SoundManager::GetInstance()->RelaseSounds();
		SMInstance->RelaseSounds();
		mySound::SoundManager::DestroyInstance();
		

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

	int GameManager::GetRoot()
	{
		return g_root;
	}

	void GameManager::SetRoot(int root)
	{
		g_root = root;
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
