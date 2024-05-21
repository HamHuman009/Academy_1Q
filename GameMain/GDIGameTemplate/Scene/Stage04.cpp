#include "Stage04.h"
#include "../GameLogic/Objects/UIObject.h"
#include "../GameLogic/Objects/Fish.h"
#include "../GameLogic/Objects/KeyInput.h"
#include "../System/TimeSystem.h"
#include "../GameLogic/Event.h"
void Stage04::Init()
{
	// �ۼ����
	// 1. object�� �����ڷ� ���� ex) (���ϴ� Ŭ����) obj = new (���ϴ� Ŭ����)();
	// 2. AddObject(obj); �� ���� ������ ������Ʈ ���� �ֱ�.
	// 3. �ݶ��̴��� �ʿ��� object�� ��� object�� ���������� �ݶ��̴��� �������� �ʴ´ٸ� ���� �ֱ�.
	// 3-1. �ݶ��̴��� ���� �� �ݶ��̴��ȿ� object�� �־��ֱ�.
	// 3-2. �ش� �ݶ��̴��� ColliderManager�� �ֱ�.
	// 4. �̺�Ʈ�� �ʿ��ϴٸ� ���̱�.

	// ���� �����ϴ� ��ü ex)Button�� Update���� ���콺 Ŭ���� ���콺�� �ش� �ݶ��̴� ������ �Ǵ��ϴ� �뵵�� ��� ����.
	// �Ǵ� ������Ʈ ��ü�� Update���� ���콺 Ŭ���� �޾Ƽ� ��뵵 ����.
	// �ϳ��ϳ� event�� ��ü ������ �ؾ��ϹǷ� init�Լ� ���ΰ� ���� ����.

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

	PauseEvent* e_pause = new PauseEvent(/*mySound::eSoundList::s_button*/);
	ResumeEvent* e_resume = new ResumeEvent(/*mySound::eSoundList::s_button*/);
	RetryEvent* e_retry = new RetryEvent(/*mySound::eSoundList::s_button*/);
	ExitEvent* e_exit = new ExitEvent(/*mySound::eSoundList::s_button*/);
	AddEvent(e_pause);
	AddEvent(e_resume);
	AddEvent(e_retry);
	AddEvent(e_exit);

	CResourceManager* CRM = CResourceManager::GetInstance();
	Gdiplus::Bitmap* exitBtn = CRM->LoadBitmapResouce(L"exitBtn", L"exitbtn_sample.bmp");

	Gdiplus::Bitmap* pauseBackImage = CRM->LoadBitmapResouce(L"pauseBackImage", L"image1.png");

	UIButton* resume = new UIButton(Vector2{ 710,200 }, e_resume, L"UI_Button_Resume", L".png");
	UIButton* retry = new UIButton(Vector2{ 710,400 }, e_retry, L"UI_Button_MainMenu", L".png");
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

	pauseBack->Init(pauseBackImage, Vector2{ 500.f,400.f });


	pauseBack->m_isActive = false;
	resume->m_isActive = false;
	retry->m_isActive = false;
	exit->m_isActive = false;


	SelectScnEvent* e_nextScn = new SelectScnEvent((UINT)SceneType::Dialog5);
	AddEvent(e_nextScn);

	UITimer* myTimer = new UITimer(CRM, Vector2{ 310,100 }, e_nextScn, 2.0f/*40.f*/);
	myTimer->remainningTimeEvent = e_feedBack7;

	UIImage* myBackGround = new UIImage();
	Gdiplus::Bitmap* waterBack = CRM->LoadBitmapResouce(L"waterImage", L"Water.png");
	myBackGround->Init(waterBack, { 640.f, 360.f });
	//UIBackGround* myBackGround = new UIBackGround();
	//myBackGround->Init(L"Water_Down_00.bmp",CRM);
	
	
	m_Player->m_pos = { 600.f, 350.f };
	m_Player->SetMoveDirection({ 0.f, -1.f }, { 1.f, 0.f }, { -1.f, 0.f }, { 0.f, 1.f });
	UIBackGround* myUPBackGround = new UIBackGround();
	myUPBackGround->Init(L"����+�׸���_00.png", CRM);
	
	
	Gdiplus::Bitmap* daughterFace1 = CRM->LoadBitmapResouce(L"Face1", L"UI_Image_Talk_CharaFace_Normal_01.png");
	Gdiplus::Bitmap* daughterFace2 = CRM->LoadBitmapResouce(L"Face2", L"UI_Image_Talk_CharaFace_Sad_01.png");
	Gdiplus::Bitmap* daughterFace3 = CRM->LoadBitmapResouce(L"Face3", L"UI_Image_Talk_CharaFace_Smile_01.png");
	Gdiplus::Bitmap* daughterFace4 = CRM->LoadBitmapResouce(L"Face4", L"UI_Image_Talk_CharaFace_Happy_01.png");
	UIFace* myFace = new UIFace(Vector2{1200,300}, daughterFace1, daughterFace2, daughterFace3, daughterFace4);


	UICrossDissolve* backEffect = new UICrossDissolve({ 640.f, 360.f }, Game::GameManager::GetInstance()->sceneBitmap);
	

	alpha = 1.0f;

	/*WCHAR* _str = new WCHAR[255];
	WCHAR t_str[] = L"����â";
	wcscpy_s(_str, 255, t_str);
	UIDialog* ScoreBox = new UIDialog();
	ScoreBox->Init({ 300.f, 100.f }, { 700.f, 150.f }, _str);
	AddObject(ScoreBox);*/

	std::wstring _wstr = L"���� â : ";
	_wstr.append(std::to_wstring(g_Score));
	In_ScoreBoard* myBoard = new In_ScoreBoard();
	myBoard->Init({ 300.f, 100.f }, { 700.f, 150.f }, _wstr);
	
	speech->face = myFace;

	KeyInput* swapObject = new KeyInput(); // ���ҿ� �� ������Ʈ ��������
	swapObject->m_isActive = false;
	SwapObjectEvent* swapTest = new SwapObjectEvent(dynamic_cast<Object*>(m_Player), dynamic_cast<Object*>(swapObject), m_arrObj);
	m_Player->temp = swapTest;
	//---------------------------------------- ���� ����------------------------------------------
	//***************����******************
	AddObject(myBackGround);
	AddObject(swapObject);
	//*************����� ����****************
	srand(std::time(NULL));
	Fish* myFish;
	myFish = new Fish(L"CrawFish", 40.f, 3.5f, L"CrawFish_01_Anim_00.png", CRM, L".png", 4.f, 5.f, 23.f, 23.f, true);
	myFish->CrawAppearEvent = e_feedBack8;
	myFish->m_pos = { 1480.f, float(rand() % 720) };
	AddObject(myFish);
	colliderManager->PushCollider(myFish->m_collider, TYPE::FISH);
	myFish = new Fish(L"CrawFish", 40.f, 3.5f, L"CrawFish_01_Anim_00.png", CRM, L".png", 4.f, 5.f, 23.f, 23.f, true);
	myFish->m_pos = { -400.f, float(rand() % 720) };
	AddObject(myFish);
	colliderManager->PushCollider(myFish->m_collider, TYPE::FISH);
	myFish = new Fish(L"CrawFish", 40.f, 3.5f, L"CrawFish_01_Anim_00.png", CRM, L".png", 4.f, 5.f, 23.f, 23.f, true);
	myFish->m_pos = { float(rand() % 1280), -800.f };
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
	myFish = new Fish(L"BossFish", 60.f, 8.7f, L"BossFish_04_Anim_00.png", CRM, L".png", 2.f, 4.f, 30.f, 30.f);
	AddObject(myFish);
	colliderManager->PushCollider(myFish->m_collider, TYPE::FISH);
	//****************����*******************
	AddObject(myUPBackGround);
	//*************�÷��̾�(��ä)**************
	AddObject(m_Player);
	//******************UI********************
	AddObject(myTimer);

	AddObject(pauseBack);
	AddObject(resume);
	AddObject(retry);
	AddObject(exit);
	//****************�� �̹���****************
	AddObject(myBoard);
	AddObject(speech);
	AddObject(myFace);
	//****************����ȯȿ��***************
	AddObject(backEffect);
}

Stage04::~Stage04() {
	/*for (int i = 0; i < m_arrObj.size(); i++) {

		if (m_arrObj[i] != nullptr) {
			delete m_arrObj[i];
		}

	}
	m_arrObj.clear();
	if (colliderManager != nullptr)
		delete colliderManager;*/
}

void Stage04::Start()
{
}

void Stage04::FixedUpdate() {
	//myBackGround->FixedUpdate();
	//myUPBackGround->FixedUpdate();
}

void Stage04::Exit() {
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