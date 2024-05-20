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

	Player* m_Player;
	m_Player = new Player();
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
	Gdiplus::Bitmap* exitBtn = CRM->LoadBitmapResouce(L"exitBtn", L"exitbtn_sample.bmp");

	Gdiplus::Bitmap* pauseBackImage = CRM->LoadBitmapResouce(L"pauseBackImage", L"image1.png");

	UIButton* resume = new UIButton(Vector2{ 710,200 }, e_resume, exitBtn);
	UIButton* retry = new UIButton(Vector2{ 710,400 }, e_retry, exitBtn);
	UIButton* exit = new UIButton(Vector2{ 710,600 }, e_exit, exitBtn);

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


	SelectScnEvent* e_nextScn = new SelectScnEvent((UINT)SceneType::STAGE_02);
	AddEvent(e_nextScn);

	UITimer* myTimer = new UITimer(CRM,Vector2{ 310,100 }, e_nextScn, 1.0f/*20.f*/);


	UIImage* myBackGround = new UIImage();
	Gdiplus::Bitmap* waterBack = CRM->LoadBitmapResouce(L"waterImage", L"Water.png");
	myBackGround->Init(waterBack, { 640.f, 360.f });

	//UIBackGround* myBackGround = new UIBackGround();
	//myBackGround->Init(L"Water_Down_00.bmp",CRM);

	AddObject(myBackGround);
	AddObject(myTimer);

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
	//***************************************
	AddObject(m_Player);
	m_Player->m_pos = { 600.f, 350.f };

	UIBackGround* myUPBackGround = new UIBackGround();
	myUPBackGround->Init(L"물결+그림자_00.png", CRM);
	AddObject(myUPBackGround);
	AddObject(pauseBack);
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

	AddObject(resume);
	AddObject(retry);
	AddObject(exit);
	

	UICrossDissolve* backEffect = new UICrossDissolve({640.f, 360.f}, Game::GameManager::GetInstance()->sceneBitmap);
	AddObject(backEffect);

	Gdiplus::Bitmap* daughterFace = CRM->LoadBitmapResouce(L"Face", L"FaceTest.png");
	UIFace* myFace = new UIFace(Vector2{1200,300}, daughterFace);
	AddObject(myFace);

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
	AddObject(myBoard);
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
