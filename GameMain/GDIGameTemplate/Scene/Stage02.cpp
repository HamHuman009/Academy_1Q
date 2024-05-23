#include "Stage02.h"
#include "../GameLogic/Objects/UIObject.h"
#include "../GameLogic/Objects/Fish.h"
#include "../GameLogic/Objects/KeyInput.h"
#include "../System/TimeSystem.h"
#include "../GameLogic/Event.h"
void Stage02::Init()
{
	// 작성요령
	// 1. object를 생성자로 생성 ex) (원하는 클래스) obj = new (원하는 클래스)();
	// 2. AddObject(obj); 를 통해 생성된 오브젝트 씬에 넣기.
	// 3. 콜라이더가 필요한 object의 경우 object가 내부적으로 콜라이더를 생성하지 않는다면 직접 넣기.
	// 3-1. 콜라이더를 넣을 때 콜라이더안에 object도 넣어주기.
	// 3-2. 해당 콜라이더를 ColliderManager에 넣기.
	// 4. 이벤트도 필요하다면 붙이기.

	// 따로 존재하는 객체 ex)Button은 Update에서 마우스 클릭시 마우스가 해당 콜라이더 안인지 판단하는 용도로 사용 가능.
	// 또는 오브젝트 자체가 Update에서 마우스 클릭을 받아서 사용도 가능.
	// 하나하나 event나 객체 생성을 해야하므로 init함수 내부가 꽉찰 예정.

	//UIBackGround* myBack = new UIBackGround();
	//AddObject(myBack);

	colliderManager = new ColliderManager();

	UISpeech* speech = new UISpeech({ 766, 103 }, nullptr);
	FeedbackEvent* e_feedBack1 = new FeedbackEvent(speech, IfCrawCaptureScoreZero);
	FeedbackEvent* e_feedBack2 = new FeedbackEvent(speech, IfCrawCaptureScoreOne);
	FeedbackEvent* e_feedBack3 = new FeedbackEvent(speech, CaptureBossFish);
	FeedbackEvent* e_feedBack4 = new FeedbackEvent(speech, CaptureFish);
	FeedbackEvent* e_feedBack5 = new FeedbackEvent(speech, OneCaptureTwoKill);
	FeedbackEvent* e_feedBack6 = new FeedbackEvent(speech, SevenScore);
	FeedbackEvent* e_feedBack7 = new FeedbackEvent(speech, RemainningTime);
	FeedbackEvent* e_feedBack8 = new FeedbackEvent(speech, CrawAppear);
	FeedbackEvent* e_feedBack9 = new FeedbackEvent(speech, TenSecNothingAnd14sec);
	AddEvent(e_feedBack1);
	AddEvent(e_feedBack2);
	AddEvent(e_feedBack3);
	AddEvent(e_feedBack4);
	AddEvent(e_feedBack5);
	AddEvent(e_feedBack6);
	AddEvent(e_feedBack7);
	AddEvent(e_feedBack8);
	AddEvent(e_feedBack9);

	BGSound_Plus* bg_Plus = new BGSound_Plus();
	BGSound_Minus* bg_Minus = new BGSound_Minus();
	EffectSound_Plus* eft_Plus = new EffectSound_Plus();
	EffectSound_Minus* eft_Minus = new EffectSound_Minus();

	AddEvent(bg_Plus);
	AddEvent(bg_Minus);
	AddEvent(eft_Plus);
	AddEvent(eft_Minus);

	Player* m_Player;
	m_Player = new Player();
	m_Player->feedbackEvent1_ifCrawCaptureScoreZero = e_feedBack1;
	m_Player->feedbackEvent2_ifCrawCaptureScoreOne = e_feedBack2;
	m_Player->feedbackEvent3_CaptureBossFish = e_feedBack3;
	m_Player->feedbackEvent4_CaptureFish = e_feedBack4;
	m_Player->feedbackEvent5_OneCaptureTwoKill = e_feedBack5;
	m_Player->feedbackEvent6_SevenScore = e_feedBack6;
	m_Player->feedbackEvent9_10secNothingAnd14sec = e_feedBack9;

	g_player = m_Player;
	UIImage* pauseBack = new UIImage();
	m_Player->Init();

	PauseEvent* e_pause = new PauseEvent(mySound::eSoundList::Button_Use);
	ResumeEvent* e_resume = new ResumeEvent(mySound::eSoundList::Button_Use);
	RetryEvent* e_retry = new RetryEvent(mySound::eSoundList::Button_Use);
	ExitEvent* e_exit = new ExitEvent(mySound::eSoundList::Button_Use);
	AddEvent(e_pause);
	AddEvent(e_resume);
	AddEvent(e_retry);
	AddEvent(e_exit);

	CResourceManager* CRM = CResourceManager::GetInstance();
	//Gdiplus::Bitmap* exitBtn = CRM->LoadBitmapResouce(L"exitBtn", L"exitbtn_sample.bmp");


	Gdiplus::Bitmap* speechBack = CRM->LoadBitmapResouce(L"speechBack", L"UI_Image_Stage_TalkBar_01.png");
	speech->Init({ 620, 73 }, speechBack);

	Gdiplus::Bitmap* pauseBackImage = CRM->LoadBitmapResouce(L"pauseBackImage", L"PauseBackGround.png");
	UIButton* resume = new UIButton(Vector2{ 640.f,300 }, e_resume, L"UI_Button_wailManu_GoToStage", L".png");
	UIButton* retry = new UIButton(Vector2{ 640.f,400 }, e_retry, L"UI_Button_wailManu_GoToTitle", L".png");
	UIButton* exit = new UIButton(Vector2{ 640.f,500 }, e_exit, L"UI_Button_Title_GameOver", L".png");

	UIButton* b_Plus = new UIButton({ 250, 300 }, bg_Plus, L"UI_Button_Pause_VolumeUp", L".png");
	UIButton* b_Minus = new UIButton({ 400, 300 }, bg_Minus, L"UI_Button_Pause_VolumeDown", L".png");
	UIButton* e_Plus = new UIButton({ 250, 500 }, eft_Plus, L"UI_Button_Pause_VolumeUp", L".png");
	UIButton* e_Minus = new UIButton({ 400, 500 }, eft_Minus, L"UI_Button_Pause_VolumeDown", L".png");

	UIVolume* myVoL = new UIVolume();

	myVoL->Init({ 315,280 }, { 350,280 });

	e_resume->Resume = resume;
	e_resume->Retry = retry;
	e_resume->PauseBack = pauseBack;
	e_resume->Exit = exit;
	e_resume->B_Inc = b_Plus;
	e_resume->B_Dec = b_Minus;
	e_resume->E_Inc = e_Plus;
	e_resume->E_Dec = e_Minus;
	e_resume->E_Volume = myVoL;

	e_pause->Resume = resume;
	e_pause->Retry = retry;
	e_pause->PauseBack = pauseBack;
	e_pause->Exit = exit;
	e_pause->B_Inc = b_Plus;
	e_pause->B_Dec = b_Minus;
	e_pause->E_Inc = e_Plus;
	e_pause->E_Dec = e_Minus;
	e_pause->E_Volume = myVoL;
	e_resume->OnTrigger();
	m_Player->pauseEvent = e_pause;

	pauseBack->Init(pauseBackImage, Vector2{ 500.f,400.f });
	pauseBack->alpha = 0.5f;

	pauseBack->m_isActive = false;
	resume->m_isActive = false;
	retry->m_isActive = false;
	exit->m_isActive = false;

	b_Plus->m_isActive = false;
	b_Minus->m_isActive = false;
	e_Plus->m_isActive = false;
	e_Minus->m_isActive = false;

	myVoL->m_isActive = false;

	SelectScnEvent* e_nextScn = new SelectScnEvent((UINT)SceneType::Dialog3);
	AddEvent(e_nextScn);

	UITimer* myTimer = new UITimer(CRM, Vector2{ 353, 14 }, e_nextScn, 40.f/*40.f*/);
	myTimer->remainningTimeEvent = e_feedBack7;
	EndgameEvent* e_endGame = new EndgameEvent(m_Player);
	myTimer->gameOverTimerEvent = e_endGame;
	AddEvent(e_endGame);

	UIImage* myBackGround = new UIImage();
	Gdiplus::Bitmap* waterBack = CRM->LoadBitmapResouce(L"waterImage", L"Water.png");
	myBackGround->Init(waterBack, { 640.f, 360.f });
	//UIBackGround* myBackGround = new UIBackGround();
	//myBackGround->Init(L"Water_Down_00.bmp",CRM);

	
	m_Player->m_pos = { 600.f, 350.f };
	m_Player->SetMoveDirection({0.f, 1.f}, {0.f, -1.f}, {1.f, 0.f}, {-1.f, 0.f});
	UIBackGround* myUPBackGround = new UIBackGround();
	myUPBackGround->Init(L"물결+그림자_00.png", CRM);


	UICrossDissolve* backEffect = new UICrossDissolve({ 640.f, 360.f }, Game::GameManager::GetInstance()->sceneBitmap);
	

	Gdiplus::Bitmap* daughterFace1 = CRM->LoadBitmapResouce(L"Face1", L"UI_Image_Talk_CharaFace_Normal_01.png");
	Gdiplus::Bitmap* daughterFace2 = CRM->LoadBitmapResouce(L"Face2", L"UI_Image_Talk_CharaFace_Sad_01.png");
	Gdiplus::Bitmap* daughterFace3 = CRM->LoadBitmapResouce(L"Face3", L"UI_Image_Talk_CharaFace_Smile_01.png");
	Gdiplus::Bitmap* daughterFace4 = CRM->LoadBitmapResouce(L"Face4", L"UI_Image_Talk_CharaFace_Happy_01.png");
	UIFace* myFace = new UIFace(Vector2{  1115+(250/2),120+(250/2)}, daughterFace1, daughterFace2, daughterFace3, daughterFace4);
	

	alpha = 1.0f;

	/*WCHAR* _str = new WCHAR[255];
	WCHAR t_str[] = L"점수창";
	wcscpy_s(_str, 255, t_str);
	UIDialog* ScoreBox = new UIDialog();
	ScoreBox->Init({ 300.f, 100.f }, { 700.f, 150.f }, _str);
	AddObject(ScoreBox);*/

	std::wstring _wstr = L"점수 창 : ";
	_wstr.append(std::to_wstring(g_Score));
	In_ScoreBoard* myBoard = new In_ScoreBoard();
	CatchBossEvent* e_CatchBoss = new CatchBossEvent(myBoard);
	AddEvent(e_CatchBoss);
	m_Player->CatchBossFish = e_CatchBoss;
	Gdiplus::Bitmap* bossFishTarget = CRM->LoadBitmapResouce(L"BossFish2_Objective", L"ScoreBoard_Objective_02.png");
	Gdiplus::Bitmap* bossFishTargetGray = CRM->LoadBitmapResouce(L"BossFish2_ObjectiveBW", L"ScoreBoard_ObjectiveBW_02.png");
	myBoard->Init(CRM, { 1040, 286 }, { 200, 100 }, bossFishTarget, bossFishTargetGray, _wstr);
	
	speech->face = myFace;

	KeyInput* swapObject = new KeyInput(); // 스왑용 빈 오브젝트 삭제금지
	swapObject->m_isActive = false;
	SwapObjectEvent* e_swapEvent = new SwapObjectEvent(dynamic_cast<Object*>(m_Player), dynamic_cast<Object*>(swapObject), m_arrObj);
	m_Player->temp = e_swapEvent;
	AddEvent(e_swapEvent);
	//---------------------------------------- 렌더 순서------------------------------------------
	//***************배경뒤******************
	AddObject(myBackGround);
	AddObject(swapObject);
	//*************물고기 생성****************
	srand(std::time(NULL));
	Fish* myFish;
	myFish = new Fish(L"CrawFish", 40.f, 3.5f, L"CrawFish_01_Anim_00.png", CRM, L".png", 4.f, 5.f, 23.f, 23.f, true);
	myFish->CrawAppearEvent = e_feedBack8;
	myFish->m_pos = { -400.f, float(rand() % 720) };
	AddObject(myFish);
	colliderManager->PushCollider(myFish->m_collider, TYPE::FISH);
	for (int i = 0; i < 4; i++) {
		myFish = new Fish(L"Fish1", 50.f, 4.36f, L"Fish_01_Anim_00.png", CRM, L".png", 3.f, 4.f, 23.f, 23.f);
		AddObject(myFish);
		colliderManager->PushCollider(myFish->m_collider, TYPE::FISH);
	}for (int i = 0; i < 4; i++) {
		myFish = new Fish(L"Fish2", 50.f, 4.36f, L"Fish_02_Anim_00.png", CRM, L".png", 3.f, 4.f, 23.f, 23.f);
		AddObject(myFish);
		colliderManager->PushCollider(myFish->m_collider, TYPE::FISH);
	}for (int i = 0; i < 4; i++) {
		myFish = new Fish(L"Fish3", 50.f, 4.36f, L"Fish_03_Anim_00.png", CRM, L".png", 3.f, 4.f, 23.f, 23.f);
		AddObject(myFish);
		colliderManager->PushCollider(myFish->m_collider, TYPE::FISH);
	}for (int i = 0; i < 4; i++) {
		myFish = new Fish(L"Fish4", 50.f, 4.36f, L"Fish_04_Anim_00.png", CRM, L".png", 3.f, 4.f, 23.f, 23.f);
		AddObject(myFish);
		colliderManager->PushCollider(myFish->m_collider, TYPE::FISH);
	}
	myFish = new Fish(L"BossFish", 75.f, 8.7f, L"BossFish_02_Anim_00.png", CRM, L".png", 2.f, 4.f, 30.f, 30.f);
	AddObject(myFish);
	colliderManager->PushCollider(myFish->m_collider, TYPE::FISH);
	//****************배경앞*******************
	AddObject(myUPBackGround);
	//*************플레이어(뜰채)**************
	AddObject(m_Player);
	//******************UI********************
	AddObject(myTimer);
	//****************딸 이미지****************
	AddObject(myBoard);
	AddObject(speech);
	AddObject(myFace);
	//****************씬전환효과***************
	AddObject(backEffect);

	//-----------------------------------
	AddObject(pauseBack);
	AddObject(resume);
	AddObject(retry);
	AddObject(exit);

	AddObject(b_Plus);
	AddObject(b_Minus);
	AddObject(e_Plus);
	AddObject(e_Minus);
	AddObject(myVoL);
}

Stage02::~Stage02() {
	/*for (int i = 0; i < m_arrObj.size(); i++) {

		if (m_arrObj[i] != nullptr) {
			delete m_arrObj[i];
		}

	}
	m_arrObj.clear();
	if (colliderManager != nullptr)
		delete colliderManager;*/
}

void Stage02::Start()
{
	mySound::SoundManager* meSound = mySound::SoundManager::GetInstance();
	meSound->StopMusic(mySound::eSoundChannel::BGM);
	meSound->PlayMusic(mySound::eSoundList::Ingame_Theme/*s_ingame*/, mySound::eSoundChannel::BGM);
}

void Stage02::FixedUpdate() {
	//myBackGround->FixedUpdate();
	//myUPBackGround->FixedUpdate();
}

void Stage02::Exit() {
	Game::GameManager::GetInstance()->FinalScore += g_Score;
	Game::GameManager::GetInstance()->BossCount += g_BossCnt;

	if (Game::GameManager::GetInstance()->sceneBitmap != nullptr)
		delete Game::GameManager::GetInstance()->sceneBitmap;
	Game::GameManager::GetInstance()->sceneBitmap = Render::GetFrontHDC();
	//CScene::~CScene();
	if (colliderManager != nullptr)
		delete colliderManager;

	for (int i = 0; i < m_eventArr.size(); i++) {
		if (m_eventArr[i] != nullptr) {
			delete (m_eventArr[i]);
		}
	}
	for (int i = 0; i < m_arrObj.size(); i++) {

		if (m_arrObj[i] != nullptr) {
			delete m_arrObj[i];
		}
	}
	m_arrObj.clear();
	m_eventArr.clear();
}