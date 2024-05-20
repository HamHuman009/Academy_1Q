#include "ScoreScene.h"
#include "../GameLogic/Objects/UIObject.h"
#include "../GameLogic/Event.h"





void ScoreScene::Init()
{	
	WCHAR _str[255];
	WCHAR _father_str[255];
	// _str = 점수;
	std::wstring _wstr = L"점수 창 : ";
	_wstr.append(std::to_wstring(Game::GameManager::GetInstance()->FinalScore));
	CResourceManager* CRM = CResourceManager::GetInstance();
	myBitmap = CRM->LoadBitmapResouce(L"image1", L"startback.png");
	UIImage* myBack = new UIImage(); // 객체 테스트 
	myBack->Init(myBitmap, { 640.f,360.f });
	AddObject(myBack);

	UIDialog* myScore = new UIDialog();
	wcscpy_s(_str,255,_wstr.c_str());
	myScore->Init(Vector2{ 100.f, 100.f }, Vector2{ 1000.f, 150.f }, _str);
	AddObject(myScore);

	//WCHAR* _str2 = new WCHAR[255];
	//// _str = 점수;
	//wcscpy_s(_str2, 255, L"점수 입력");

	/*UIDialog* inputScore= new UIDialog();
	inputScore->Init(Vector2{ 100.f, 250.f }, Vector2{ 1000.f, 350.f }, _str2);
	AddObject(inputScore);*/
	
	wcscpy_s(_father_str, 255, L"우리 아빠 이름은");
	UIDialog* myFatherName = new UIDialog();
	myFatherName->Init(Vector2{ 100.f,250.f }, Vector2{ 500.f, 50.f }, _father_str);
	AddObject(myFatherName);

	UIInputField* myInputField = new UIInputField(Vector2{ 350.f,350.f }, 500.f, 100.f);
	myInputField->Init();
	AddObject(myInputField);

	RetryEvent* e_retry = new RetryEvent;
	//Gdiplus::Bitmap* exitBtn = CRM->LoadBitmapResouce(L"exitBtn", L"exitbtn_sample.bmp");
	UIButton* retry = new UIButton(Vector2{ 710,400 }, e_retry, L"UI_Button_MainMenu", L".png");
	AddEvent(e_retry);
	AddObject(retry);
	
	int root = Game::GameManager::GetInstance()->GetRoot();

	switch (root)
	{
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	}

}

void ScoreScene::Start()
{
}

void ScoreScene::Exit()
{	
	Game::GameManager* myGame = Game::GameManager::GetInstance();
	myGame->m_Ranking->saveRankings();
	/*myGame->m_Ranking->sortRank();
	
	myGame->m_Ranking->loadRankings();
	myGame->m_Ranking->rankToStr();*/
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
	//delete[] _str;
	//delete[] _father_str;
}
