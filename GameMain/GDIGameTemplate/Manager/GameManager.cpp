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
		mVolume = 0.5f;
		effectVolume = 0.5f;
		m_Ranking = new Ranking();
		Input::InitInput();
		High_Resolution_Time::InitTime();
		m_hWnd = global::GetWinApp().GetWindow();
		m_hdc = GetDC(m_hWnd);
		/*mySound::SoundManager::Init();
		mySound::SoundManager::GetInstance()->LoadSounds(mySound::SoundList::Singing, false, "singing.wav");*/
		SMInstance = mySound::SoundManager::GetInstance();
		SMInstance->LoadMusic(mySound::eSoundList::Main_Theme, true, "Sound_Title_MainTheme_01-0.wav");
		SMInstance->LoadMusic(mySound::eSoundList::Intro_Theme, true, "Sound_Intro_Intro_Theme_01.wav");
		SMInstance->LoadMusic(mySound::eSoundList::Ingame_Theme, true, "Sound_Stage_Ingame_Theme_01-1_2.wav");
		SMInstance->LoadMusic(mySound::eSoundList::Talk_Theme, true, "Sound_Talk_Talk_Theme_01.wav");
		SMInstance->LoadMusic(mySound::eSoundList::Ending_Theme, true, "Sound_Ending_Ending_Theme_01_2-2.wav");
		SMInstance->LoadMusic(mySound::eSoundList::Button_Use, false, "Sound_Button_Use_01-1.wav");
		SMInstance->LoadMusic(mySound::eSoundList::Scooper_Down, false, "Sound_Stage_Scooper_Down_01.wav");
		SMInstance->LoadMusic(mySound::eSoundList::Scooper_Up, false, "Sound_Stage_Scooper_Up_01.wav");
		SMInstance->LoadMusic(mySound::eSoundList::Fish_Catch, false, "Sound_Stage_Fish_Catch_01_003.wav");
		SMInstance->LoadMusic(mySound::eSoundList::Boss_Fish_Catch, false, "Sound_Stage_Boss_Fish_Catch_01-1.wav");
		SMInstance->LoadMusic(mySound::eSoundList::Fish_breathing1, false, "Sound_Fish_breathing_01-1.wav");
		SMInstance->LoadMusic(mySound::eSoundList::Fish_breathing2, false, "Sound_Fish_breathing_01-2.wav");
		SMInstance->LoadMusic(mySound::eSoundList::Fish_breathing3, false, "Sound_Fish_breathing_01-3.wav");
		SMInstance->LoadMusic(mySound::eSoundList::Anger_Sound_Start,false,"Sound_Anger_Sound_01-3.wav");
		SMInstance->LoadMusic(mySound::eSoundList::Anger_Sound_End, false, "Sound_Anger_Sound_02-3.wav");
		SMInstance->LoadMusic(mySound::eSoundList::Scooper_Broken, false, "Sound_Scooper_Broken_01-1.wav"); 
		SMInstance->LoadMusic(mySound::eSoundList::Stage_End_Counting, false, "Sound_Stage_End_Counting_01.wav");
		SMInstance->LoadMusic(mySound::eSoundList::Move_Scene_Theme1, false, "Sound_Move_Scene_Theme_01_001.wav");
		SMInstance->LoadMusic(mySound::eSoundList::Move_Scene_Theme2, false, "Sound_Move_Scene_Theme_01_002.wav");
		SMInstance->LoadMusic(mySound::eSoundList::Move_Scene_Theme3, false, "Sound_Move_Scene_Theme_01_003.wav");
		SMInstance->LoadMusic(mySound::eSoundList::CrabDance, true, "CrabDance.mp3");
		SMInstance->SetVolumeAll(mVolume);
		
		

		m_cameraPosition = { 0.f, 0.f };

		m_sceneManager = SceneManager::GetInstance();
		m_sceneManager->Init();
		m_curScene = m_sceneManager->GetCurScene();
		
	}
	float timer = 0.f;
	void GameManager::Update()
	{
		++m_UpdateCount;

		Input::UpdateMouse();
		//std::cout << SMInstance->isChannelPlaying(mySound::eSoundChannel::BGM) << std::endl;

		if (cameraShakeTimer > 0.f) {
			cameraShakeTimer -= High_Resolution_Time::GetDeltaTime() / 1000.f;
			timer += High_Resolution_Time::GetDeltaTime() / 90.f;

			std::cout << cameraShakeTimer << std::endl;
			m_cameraPosition = { sinf(timer) * 6 - 3, sinf(timer * 1.3f) * -3 };
			if (cameraShakeTimer < 0.f) {
				m_cameraPosition = { 0.f, 0.f };
			}
		}

		if (hardCameraShakeTimer > 0.f) {
			hardCameraShakeTimer -= High_Resolution_Time::GetDeltaTime() / 1000.f;
			timer += High_Resolution_Time::GetDeltaTime() / 50.f;
			m_cameraPosition = { sinf(timer) * 8 - 4, sinf(timer * 1.3f) * -6 + 3  };
			if (hardCameraShakeTimer < 0.f) {
				m_cameraPosition = { 0.f, 0.f };
			}
		}

		if (Input::IsKey('L') && Input::IsKeyDown('1')) {
			m_sceneManager->SetCurScene((UINT)SceneType::START);
			High_Resolution_Time::SetTimeScale(1.f);
			High_Resolution_Time::SetTimeScale2(1.f);
		}if (Input::IsKey('L') && Input::IsKeyDown('2')) {
			m_sceneManager->SetCurScene((UINT)SceneType::INTRO);
			High_Resolution_Time::SetTimeScale(1.f);
			High_Resolution_Time::SetTimeScale2(1.f);
		}if (Input::IsKey('L') && Input::IsKeyDown('3')) {
			m_sceneManager->SetCurScene((UINT)SceneType::STAGE_01);
			High_Resolution_Time::SetTimeScale(1.f);
			High_Resolution_Time::SetTimeScale2(1.f);
		}if (Input::IsKey('L') && Input::IsKeyDown('4')) {
			m_sceneManager->SetCurScene((UINT)SceneType::STAGE_02);
			High_Resolution_Time::SetTimeScale(1.f);
			High_Resolution_Time::SetTimeScale2(1.f);
		}if (Input::IsKey('L') && Input::IsKeyDown('5')) {
			m_sceneManager->SetCurScene((UINT)SceneType::STAGE_03);
			High_Resolution_Time::SetTimeScale(1.f);
			High_Resolution_Time::SetTimeScale2(1.f);
		}if (Input::IsKey('L') && Input::IsKeyDown('6')) {
			m_sceneManager->SetCurScene((UINT)SceneType::STAGE_04);
			High_Resolution_Time::SetTimeScale(1.f);
			High_Resolution_Time::SetTimeScale2(1.f);
		}if (Input::IsKey('L') && Input::IsKeyDown('7')) {
			m_sceneManager->SetCurScene((UINT)SceneType::STAGE_05);
			High_Resolution_Time::SetTimeScale(1.f);
			High_Resolution_Time::SetTimeScale2(1.f);
		}if (Input::IsKey('L') && Input::IsKeyDown('8')) {
			m_sceneManager->SetCurScene((UINT)SceneType::Ending);
			High_Resolution_Time::SetTimeScale(1.f);
			High_Resolution_Time::SetTimeScale2(1.f);
		}if (Input::IsKey('L') && Input::IsKeyDown('9')) {
			m_sceneManager->SetCurScene((UINT)SceneType::Score);
			High_Resolution_Time::SetTimeScale(1.f);
			High_Resolution_Time::SetTimeScale2(1.f);
		}

		if (m_curScene != m_sceneManager->GetCurScene()) {
			m_curScene = m_sceneManager->GetCurScene();
		}
		m_curScene->Update();
		Input::ResetInput();

		/*std::string SoundRate = std::to_string(mVolume);
		mySoundRate = SoundRate.c_str();*/
		//std::cout << mVolume << '\n';
	}
	
	void GameManager::FixeUpdate()
	{
		static ULONGLONG elapsedTime;

		elapsedTime += High_Resolution_Time::GetDeltaTime();
		
		while (elapsedTime >= 20) //0.02초
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

		if (Input::IsKey('Q')) {
			std::string FrameRate = std::to_string(High_Resolution_Time::GetFrameRate());
			const char* myFrameRate = FrameRate.c_str();
			Render::DrawTextW(10, 50, myFrameRate, RGB(255, 0, 0));
		}
		//Render::DrawTextW(10, 70, mySoundRate, RGB(0, 255, 255));
		

		Render::EndDraw();

		
	}
	void GameManager::Finalize()
	{	
		m_Ranking->saveRankings();

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

	void GameManager::SetCameraShakeTimer(float timer)
	{
		if (cameraShakeTimer < timer)
			cameraShakeTimer = timer;
	}

	void GameManager::OffCameraShaker()
	{
		cameraShakeTimer = 0.f;
		m_cameraPosition = { 0.f, 0.f };
	}

	void GameManager::SetHardCameraShake(float time)
	{
		cameraShakeTimer = 0.f;
		m_cameraPosition = { 0.f, 0.f };
		hardCameraShakeTimer = time;
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
