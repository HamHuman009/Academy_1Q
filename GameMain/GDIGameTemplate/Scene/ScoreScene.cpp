#include "ScoreScene.h"
#include "../GameLogic/Objects/UIObject.h"
#include "../GameLogic/Event.h"
WCHAR* _str;
WCHAR* _father_str;
void ScoreScene::Init()
{
	// _str = 점수;
	std::wstring _wstr = L"점수 창 : ";
	_wstr.append(std::to_wstring(Game::GameManager::GetInstance()->FinalScore));
	CResourceManager* CRM = CResourceManager::GetInstance();
	myBitmap = CRM->LoadBitmapResouce(L"image1", L"startback.bmp");
	UIImage* myBack = new UIImage(); // 객체 테스트 
	myBack->Init(myBitmap, { 640.f,360.f });

	AddObject(myBack);

	UIDialog* myScore = new UIDialog();
	_str = new WCHAR[255];
	wcscpy_s(_str,255,_wstr.c_str());
	myScore->Init(Vector2{ 100.f, 100.f }, Vector2{ 1000.f, 150.f }, _str);
	AddObject(myScore);

	//WCHAR* _str2 = new WCHAR[255];
	//// _str = 점수;
	//wcscpy_s(_str2, 255, L"점수 입력");

	/*UIDialog* inputScore= new UIDialog();
	inputScore->Init(Vector2{ 100.f, 250.f }, Vector2{ 1000.f, 350.f }, _str2);
	AddObject(inputScore);*/
	_father_str = new WCHAR[255];
	wcscpy_s(_father_str, 255, L"우리 아빠 이름은");
	UIDialog* myFatherName = new UIDialog();
	myFatherName->Init(Vector2{ 100.f,250.f }, Vector2{ 500.f, 50.f }, _father_str);
	AddObject(myFatherName);

	UIInputField* myInputField = new UIInputField(Vector2{ 350.f,350.f }, 500.f, 100.f);
	myInputField->Init();
	AddObject(myInputField);

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
	delete[] _str;
	delete[] _father_str;
}
