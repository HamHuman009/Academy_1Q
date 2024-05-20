#include "Stage01.h"
#include "../GameLogic/Objects/UIObject.h"
#include "../GameLogic/Objects/Fish.h"
#include "../System/TimeSystem.h"
#include "../GameLogic/Event.h"

//#define TEST
void Stage01::Init()
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

	UISpeech* speech = new UISpeech({ 900.f, 300.f }, nullptr);
	FeedbackEvent* e_feedBack1 = new FeedbackEvent(speech, 1);
	FeedbackEvent* e_feedBack2 = new FeedbackEvent(speech, 2);
	FeedbackEvent* e_feedBack3 = new FeedbackEvent(speech, 3);
	FeedbackEvent* e_feedBack4 = new FeedbackEvent(speech, 4);
	FeedbackEvent* e_feedBack5 = new FeedbackEvent(speech, 5);
	FeedbackEvent* e_feedBack6 = new FeedbackEvent(speech, 6);
	FeedbackEvent* e_feedBack7 = new FeedbackEvent(speech, 7);
	FeedbackEvent* e_feedBack8 = new FeedbackEvent(speech, 8);
	FeedbackEvent* e_feedBack9 = new FeedbackEvent(speech, 9);
	AddEvent(e_feedBack1);
	AddEvent(e_feedBack2);
	AddEvent(e_feedBack3);
	AddEvent(e_feedBack4);
	AddEvent(e_feedBack5);
	AddEvent(e_feedBack6);
	AddEvent(e_feedBack7);
	AddEvent(e_feedBack8);
	AddEvent(e_feedBack9);

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

	PauseEvent* e_pause = new PauseEvent;
	ResumeEvent* e_resume = new ResumeEvent;
	RetryEvent* e_retry = new RetryEvent;
	ExitEvent* e_exit = new ExitEvent;
	AddEvent(e_pause);
	AddEvent(e_resume);
	AddEvent(e_retry);
	AddEvent(e_exit);

	CResourceManager* CRM = CResourceManager::GetInstance();
	
	//Gdiplus::Bitmap* exitBtn = CRM->LoadBitmapResouce(L"exitBtn", L"exitbtn_sample.bmp");

	Gdiplus::Bitmap* pauseBackImage = CRM->LoadBitmapResouce(L"pauseBackImage", L"image1.png");

	UIButton* resume = new UIButton(Vector2{ 710,200 }, e_resume, L"UI_Button_Resume", L".png");
	UIButton* retry = new UIButton(Vector2{ 710,400 }, e_retry, L"UI_Button_MainMenu",L".png");
	UIButton* exit = new UIButton(Vector2{ 710,600 }, e_exit, L"UI_Button_Title_GameOver", L".png");

	e_resume->Resume = resume;
	e_resume->Retry = retry;
	e_resume->PauseBack = pauseBack;
	e_resume->Exit = exit;
	e_pause->Resume = resume;
	e_pause->Retry = retry;
	e_pause->PauseBack = pauseBack;
	e_pause->Exit = exit;
	
	e_resume->OnTrigger();
	m_Player->pauseEvent = e_pause;
	
	pauseBack->Init(pauseBackImage,Vector2{500.f,400.f});

	

	pauseBack->m_isActive = false;
	resume->m_isActive = false;
	retry->m_isActive = false;
	exit->m_isActive = false;


	SelectScnEvent* e_nextScn = new SelectScnEvent((UINT)SceneType::Dialog1);
	AddEvent(e_nextScn);

	UITimer* myTimer = new UITimer(CRM, Vector2{ 310,100 }, e_nextScn, 20.f);
	myTimer->remainningTimeEvent = e_feedBack7;

	UIImage* myBackGround = new UIImage();
	Gdiplus::Bitmap* waterBack = CRM->LoadBitmapResouce(L"waterImage", L"Water.png");
	myBackGround->Init(waterBack, { 640.f, 360.f });

	
	m_Player->m_pos = { 600.f, 350.f };

	UIBackGround* myUPBackGround = new UIBackGround();
	myUPBackGround->Init(L"물결+그림자_00.png", CRM);
	
#ifndef TEST

	/*SelectScnEvent* e_TEST[(int)SceneType::END];
	for (int i = 0; i < (int)SceneType::END; i++) {
		e_TEST[i] = new SelectScnEvent(i+1);
		AddEvent(e_TEST[i]);
	}

	UIButton* ub_S1 = new UIButton(Vector2{ 100,000 }, e_TEST[0], exitBtn);
	UIButton* ub_S2 = new UIButton(Vector2{ 100,200 }, e_TEST[1], exitBtn);
	UIButton* ub_S3 = new UIButton(Vector2{ 100,400 }, e_TEST[2], exitBtn);
	UIButton* ub_S4 = new UIButton(Vector2{ 100,600 }, e_TEST[3], exitBtn);
	AddObject(ub_S1);
	AddObject(ub_S2);
	AddObject(ub_S3);
	AddObject(ub_S4);

	UIButton* ub_S5 = new UIButton(Vector2{ 400,000 }, e_TEST[4], exitBtn);
	UIButton* ub_S6 = new UIButton(Vector2{ 400,200 }, e_TEST[5], exitBtn);
	UIButton* ub_S7 = new UIButton(Vector2{ 400,400 }, e_TEST[6], exitBtn);
	UIButton* ub_S8 = new UIButton(Vector2{ 400,600 }, e_TEST[7], exitBtn);

	AddObject(ub_S5);
	AddObject(ub_S6);
	AddObject(ub_S7);
	AddObject(ub_S8);*/
	
#endif // !TEST
	UICrossDissolve* backEffect = new UICrossDissolve({640.f, 360.f}, Game::GameManager::GetInstance()->sceneBitmap);
	
	Gdiplus::Bitmap* daughterFace1 = CRM->LoadBitmapResouce(L"Face1", L"UI_Image_Talk_CharaFace_Normal_01.png");
	Gdiplus::Bitmap* daughterFace2 = CRM->LoadBitmapResouce(L"Face2", L"UI_Image_Talk_CharaFace_Sad_01.png");
	Gdiplus::Bitmap* daughterFace3 = CRM->LoadBitmapResouce(L"Face3", L"UI_Image_Talk_CharaFace_Smile_01.png");
	Gdiplus::Bitmap* daughterFace4 = CRM->LoadBitmapResouce(L"Face4", L"UI_Image_Talk_CharaFace_Happy_01.png");
	UIFace* myFace = new UIFace(Vector2{1200,300}, daughterFace1, daughterFace2, daughterFace3, daughterFace4);
	
	alpha = 1.0f;
	//WCHAR* _str = new WCHAR[255];
	//WCHAR t_str[] = L"점수창 : ";  // 점수 받아오는 함수 만들거나 넣어서 출력시키기
	/*wcscpy_s(_str, 255, t_str);*/
	/*UIDialog* ScoreBox = new UIDialog();
	ScoreBox->Init({ 300.f, 100.f }, { 700.f, 150.f }, _str);
	AddObject(ScoreBox);*/

	std::wstring _wstr = L"점수 창 : ";
	_wstr.append(std::to_wstring(g_Score));
	In_ScoreBoard* myBoard = new In_ScoreBoard();
	myBoard->Init({ 300.f, 100.f }, { 700.f, 150.f }, _wstr);

	speech->face = myFace;

	//---------------------------------------- 렌더 순서------------------------------------------
	//***************배경뒤******************
	AddObject(myBackGround);
	//*************물고기 생성****************
	srand(std::time(NULL));
	Fish* myFish;
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
	myFish = new Fish(L"BossFish", 60.f, 8.7f, L"BossFish_00.png", CRM, L".png", 2.f, 4.f, 30.f, 30.f);
	AddObject(myFish);
	colliderManager->PushCollider(myFish->m_collider, TYPE::FISH);
	//****************배경앞*******************
	AddObject(myUPBackGround);
	//*************플레이어(뜰채)**************
	AddObject(m_Player);
	//******************UI********************
	AddObject(myTimer);

	AddObject(pauseBack);
	AddObject(resume);
	AddObject(retry);
	AddObject(exit);
	//****************딸 이미지****************
	AddObject(myBoard);
	AddObject(speech);
	AddObject(myFace);
	//****************씬전환효과***************
	AddObject(backEffect);
}

Stage01::~Stage01() {
	/*for (int i = 0; i < m_arrObj.size(); i++) {

		if (m_arrObj[i] != nullptr) {
			delete m_arrObj[i];
		}

	}
	m_arrObj.clear();
	if (colliderManager != nullptr)
		delete colliderManager;*/
}

void Stage01::Start()
{
}

void Stage01::FixedUpdate() {
	//myBackGround->FixedUpdate();
	//myUPBackGround->FixedUpdate();
}

void Stage01::Exit() {

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
