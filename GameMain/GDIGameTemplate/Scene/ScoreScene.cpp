#include "ScoreScene.h"
#include "../GameLogic/Objects/UIObject.h"
#include "../GameLogic/Event.h"





void ScoreScene::Init()
{	
	//----------Test-----------

	//Ranking* myRang = Game::GameManager::GetInstance()->m_Ranking;
	////��ũ �ҷ�����
	//myRang->sortRank();
	//myRang->rankToStr();

	////��ũ����
	//RECT scoreRect = { 400,200,800,800 };
	//UIImage* rankBoard = new UIImage();
	//Gdiplus::Bitmap* rankImage = CResourceManager::GetInstance()->LoadBitmapResouce(L"RankBoard", L"UI_Title_Ranking.png");
	//rankBoard->Init(rankImage, { 1450.f, 340.f });

	////��ŷ���� �����̴� ������Ʈ
	//MoveObject* moveAbleObject = new MoveObject(rankBoard, { 950, 340 }, 1.f);
	//AddObject(moveAbleObject);


	//-------------------------




	WCHAR _str[255];
	WCHAR _scoreStr[255];
	WCHAR _father_str[255];

	WCHAR _rankStr[255];

	// _str = ����;
	std::wstring _wstr = L"�츮 �ƺ� ������ : ";
	std::wstring _wScore = L"";
	
	std::wstring _wRank = L"";

	_wScore.append(std::to_wstring(Game::GameManager::GetInstance()->FinalScore));
	CResourceManager* CRM = CResourceManager::GetInstance();
	myBitmap = CRM->LoadBitmapResouce(L"UI_Rank", L"UI_Window_scorecount_Rank_Window_01.png");
	UIImage* myBack = new UIImage(); // ��ü �׽�Ʈ 
	myBack->Init(myBitmap, { 640.f,360.f });
	AddObject(myBack);

	int playerRank = Game::GameManager::GetInstance()->m_Ranking->InRankPlayer(Game::GameManager::GetInstance()->FinalScore);

	
	switch (playerRank)
	{
	case 1:
		_wRank.append(std::to_wstring(playerRank));
		_wRank.append(L"��\n");
		_wRank.append(L"�ƺ� ��¥ �ְ��!");
		break;
	case 2:
	case 3:
		_wRank.append(std::to_wstring(playerRank));
		_wRank.append(L"��\n");
		_wRank.append(L"������ �ƺ� ������");
		break;
	case 4:
	case 5:
	case 6:
	case 7:
		_wRank.append(std::to_wstring(playerRank));
		_wRank.append(L"��\n");
		_wRank.append(L"�׻� �ּ��� ���ϴ� �ƺ�");
		break;
	case 8:
	case 9:
	case 10:
		_wRank.append(std::to_wstring(playerRank));
		_wRank.append(L"��\n");
		_wRank.append(L"����ϴ� �ƺ�");
		break;
	default:
		_wRank.append(std::to_wstring(playerRank));
		_wRank.append(L"��\n");
		_wRank.append(L"�ƺ� ���� ����");
		break;
	}


	UIDialog* myScoreDial = new UIDialog();
	wcscpy_s(_str,255,_wstr.c_str());
	UIDialog* myScore = new UIDialog();
	wcscpy_s(_scoreStr, 255, _wScore.c_str());

	UIDialog* myRank = new UIDialog();
	wcscpy_s(_rankStr, 255, _wRank.c_str());

	myScoreDial->Init(Vector2{ 100.f, 100.f }, Vector2{ 1000.f, 150.f }, _str);
	AddObject(myScoreDial);
	myScore->Init(Vector2{ 310.f, 93.f }, Vector2{ 1000.f, 150.f }, _scoreStr,40);
	AddObject(myScore);

	myRank->Init(Vector2{ 100.f, 200.f }, Vector2{ 1000.f, 150.f }, _rankStr);
	AddObject(myRank);


	//WCHAR* _str2 = new WCHAR[255];
	//// _str = ����;
	//wcscpy_s(_str2, 255, L"���� �Է�");

	/*UIDialog* inputScore= new UIDialog();
	inputScore->Init(Vector2{ 100.f, 250.f }, Vector2{ 1000.f, 350.f }, _str2);
	AddObject(inputScore);*/
	

	//��ũ ���->�ٽ��ϱ��
	UIButton* inRank = new UIButton(Vector2{ 250,600 }, nullptr/*��ũ ��� �̺�Ʈ ���� ��*/, L"UI_Button_scorecount_InRank", L".png");
	AddObject(inRank);
	
	

	UIImage* myNoTitle = new UIImage(); // ��ü �׽�Ʈ 
	Gdiplus::Bitmap* myNoTitleBitmap = CRM->LoadBitmapResouce(L"UI_NoTitle", L"notitle_resize.jpg");
	myNoTitle->Init(myNoTitleBitmap, { 850.f,280.f });
	AddObject(myNoTitle);

	if (playerRank < 11)
	{
		wcscpy_s(_father_str, 255, L"�츮 �ƺ� �̸���");
		UIDialog* myFatherName = new UIDialog();
		myFatherName->Init(Vector2{ 100.f,300.f }, Vector2{ 500.f, 50.f }, _father_str);
		AddObject(myFatherName);

		UIInputField* myInputField = new UIInputField(Vector2{ 350.f,400.f }, 500.f, 100.f);
		myInputField->Init();
		AddObject(myInputField);

		ButtonOnTriggerAndActiveFalseEvent* e_inRank = new ButtonOnTriggerAndActiveFalseEvent(inRank, myInputField);
		AddEvent(e_inRank);
		inRank->m_Event = e_inRank;
	}
	//���� �ٽ� �����ϴ� ��ư�� �̺�Ʈ
	GameRetryEvent* e_gameRetry = new GameRetryEvent(mySound::eSoundList::Button_Use); //���� �ٽ� �����ϴ� �̺�Ʈ
	UIButton* gameRetry = new UIButton(Vector2{ 650, 600 }, e_gameRetry/*��ũ Ȯ�� �̺�Ʈ ���� ��*/, L"UI_Button_Retry", L".png");
	AddEvent(e_gameRetry);
	AddObject(gameRetry);
	

	//��ũ Ȯ�� ����
	
	//���� �޴��� ���� ��ư�� �̺�Ʈ
	RetryEvent* e_mainMenu = new RetryEvent(mySound::eSoundList::Button_Use);
	//Gdiplus::Bitmap* exitBtn = CRM->LoadBitmapResouce(L"exitBtn", L"exitbtn_sample.bmp");
	UIButton* mainMenuBtn = new UIButton(Vector2{ 1050,600 }, e_mainMenu, L"UI_Button_MainMenu", L".png");
	AddEvent(e_mainMenu);
	AddObject(mainMenuBtn);

	/*int root = Game::GameManager::GetInstance()->GetRoot();*/

	/*switch (root)
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
	}*/

}

void ScoreScene::Start()
{
}

void ScoreScene::Exit()
{	
	Game::GameManager* myGame = Game::GameManager::GetInstance();
	//myGame->m_Ranking->saveRankings();
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
