#include "ScoreScene.h"
#include "../GameLogic/Objects/UIObject.h"
#include "../GameLogic/Event.h"

void ScoreScene::Init()
{
	WCHAR* _str = new WCHAR[255];
	// _str = 점수;
	wcscpy_s(_str, 255, L"1등 : 100점");
	CResourceManager* CRM = CResourceManager::GetInstance();
	myBitmap = CRM->LoadBitmapResouce(L"image1", L"startback.bmp");
	UIImage* myBack = new UIImage(); // 객체 테스트 
	myBack->Init(myBitmap, { 640.f,360.f });

	AddObject(myBack);

	UIDialog* myScore = new UIDialog();
	myScore->Init(Vector2{ 100.f, 100.f }, Vector2{ 1000.f, 150.f }, _str);
	AddObject(myScore);

	WCHAR* _str2 = new WCHAR[255];
	// _str = 점수;
	wcscpy_s(_str2, 255, L"점수 입력");

	UIDialog* inputScore= new UIDialog();
	inputScore->Init(Vector2{ 100.f, 250.f }, Vector2{ 1000.f, 350.f }, _str2);
	AddObject(inputScore);

	RetryEvent* e_retry = new RetryEvent;
	Gdiplus::Bitmap* exitBtn = CRM->LoadBitmapResouce(L"exitBtn", L"exitbtn_sample.bmp");
	UIButton* retry = new UIButton(Vector2{ 910, 600 }, e_retry, exitBtn);
	AddEvent(e_retry);
	AddObject(retry);

}

void ScoreScene::Start()
{
}

void ScoreScene::Exit()
{
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

ScoreScene::ScoreScene()
{
}

ScoreScene::~ScoreScene()
{
}
