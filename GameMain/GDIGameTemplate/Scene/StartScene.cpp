#include "StartScene.h"
#include "../System/InputSystem.h"

#include "../GameLogic/Event.h"


void StartScene::Start() 
{

}

void StartScene::Init()
{	

	CResourceManager* CR = CResourceManager::GetInstance();
	myBitmap = CR->LoadBitmapResouce(L"image1",L"startback.png");
	UIImage* myBack = new UIImage(); // 객체 테스트 
	myBack->Init(myBitmap, { 640.f,360.f });
	
	/*SelectScnEvent* a = new SelectScnEvent(3);
	delete a;*/
	Gdiplus::Bitmap* startBtn = CR->LoadBitmapResouce(L"startBtn", L"startbtn_sample.bmp");
	Gdiplus::Bitmap* exitBtn = CR->LoadBitmapResouce(L"exitBtn", L"exitbtn_sample.bmp");

	SelectScnEvent* e_nextScn = new SelectScnEvent((UINT)SceneType::INTRO,mySound::eSoundList::Button); // 씬전환 이벤트 테스트
	UIButton* gameStartButton = new UIButton(Vector2{200.0f,300.0f}, e_nextScn, startBtn); // 객체 테스트
	
	scoreRect = { 400,200,800,800 };
	
	_str = new WCHAR[255];
	memset(_str, L'\0', 255);
	//WCHAR t_str[] = L"랭킹 보드 구현할 장소\n 불러오는건 사이즈 보고 구현할것";
	std::string myRank;
	int fromRank = strlen(Game::GameManager::GetInstance()->m_Ranking->str_rank.c_str());
	myRank.assign(Game::GameManager::GetInstance()->m_Ranking->str_rank);
	
	int sizeNeeded = MultiByteToWideChar(CP_UTF8, 0, &myRank[0], (int)myRank.size(), NULL, 0);
	MultiByteToWideChar(CP_UTF8, 0, &myRank[0], fromRank, &_str[0], sizeNeeded);
	UIDialog* rankDialog = new UIDialog();
	rankDialog->Init({ 400.f,200.f }, { 800.f,800.f}, _str);

	ExitEvent* e_exit = new ExitEvent;
	UIButton* exit = new UIButton(Vector2{ 200.0f,600.0f }, e_exit, exitBtn);

	UIInputField* inputField = new UIInputField({500.f, 500.f}, 200.f, 150.f);

	AddObject(myBack);
	
	AddObject(gameStartButton);
	AddObject(exit);
	AddEvent(e_nextScn);
	AddEvent(e_exit);

	AddObject(inputField);
	
	UICrossDissolve* backEffect = new UICrossDissolve({ 640.f, 360.f }, Game::GameManager::GetInstance()->sceneBitmap);
	AddObject(backEffect);
	//Test-------------start
	FeedbackEvent* e_feedBack = new FeedbackEvent;
	FeedbackEvent* e_feedBack2 = new FeedbackEvent;
	UIButton* TestButton = new UIButton(Vector2{ 500.0f, 300.0f }, e_feedBack, startBtn);
	UIButton* TestButton2 = new UIButton(Vector2{ 700.0f, 300.0f }, e_feedBack2, startBtn);
	UISpeech* speech = new UISpeech({ 500.f, 500.f }, startBtn);
	e_feedBack->feedbackObject = speech;
	e_feedBack->feedbackNumber = 2;
	e_feedBack2->feedbackObject = speech;
	e_feedBack2->feedbackNumber = 5;
	AddObject(speech);
	AddObject(TestButton);
	AddObject(TestButton2);
	AddEvent(e_feedBack);
	AddEvent(e_feedBack2);
	alpha = 1.0f;
	AddObject(rankDialog);
	//Test-------------end
}

StartScene::~StartScene() {
	delete[] _str;
}

void StartScene::Exit() {
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