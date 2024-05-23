#include "ScoreScene.h"
#include "../GameLogic/Objects/UIObject.h"
#include "../GameLogic/Event.h"





void ScoreScene::Init()
{	
	//----------Test-----------

	//Ranking* myRang = Game::GameManager::GetInstance()->m_Ranking;
	////랭크 불러오기
	//myRang->sortRank();
	//myRang->rankToStr();

	////랭크보드
	//RECT scoreRect = { 400,200,800,800 };
	//UIImage* rankBoard = new UIImage();
	//Gdiplus::Bitmap* rankImage = CResourceManager::GetInstance()->LoadBitmapResouce(L"RankBoard", L"UI_Title_Ranking.png");
	//rankBoard->Init(rankImage, { 1450.f, 340.f });

	////랭킹보드 움직이는 오브젝트
	//MoveObject* moveAbleObject = new MoveObject(rankBoard, { 950, 340 }, 1.f);
	//AddObject(moveAbleObject);


	//-------------------------




	WCHAR _str[255];
	WCHAR _scoreStr[255];
	WCHAR _father_str[255];

	WCHAR _rankStr[255];

	// _str = 점수;
	std::wstring _wstr = L"우리 아빠 점수는 : ";
	std::wstring _wScore = L"";
	
	std::wstring _wRank = L"";

	_wScore.append(std::to_wstring(Game::GameManager::GetInstance()->FinalScore));
	CResourceManager* CRM = CResourceManager::GetInstance();
	myBitmap = CRM->LoadBitmapResouce(L"UI_Rank", L"UI_Window_scorecount_Rank_Window_01.png");
	UIImage* myBack = new UIImage(); // 객체 테스트 
	myBack->Init(myBitmap, { 640.f,360.f });
	AddObject(myBack);

	int playerRank = Game::GameManager::GetInstance()->m_Ranking->InRankPlayer(Game::GameManager::GetInstance()->FinalScore);

	
	switch (playerRank)
	{
	case 1:
		_wRank.append(std::to_wstring(playerRank));
		_wRank.append(L"등\n");
		_wRank.append(L"아빠 진짜 최고야!");
		break;
	case 2:
	case 3:
		_wRank.append(std::to_wstring(playerRank));
		_wRank.append(L"등\n");
		_wRank.append(L"다정한 아빠 고마워요");
		break;
	case 4:
	case 5:
	case 6:
	case 7:
		_wRank.append(std::to_wstring(playerRank));
		_wRank.append(L"등\n");
		_wRank.append(L"항상 최선을 다하는 아빠");
		break;
	case 8:
	case 9:
	case 10:
		_wRank.append(std::to_wstring(playerRank));
		_wRank.append(L"등\n");
		_wRank.append(L"사랑하는 아빠");
		break;
	default:
		_wRank.append(std::to_wstring(playerRank));
		_wRank.append(L"등\n");
		_wRank.append(L"아빠 정말 좋아");
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
	//// _str = 점수;
	//wcscpy_s(_str2, 255, L"점수 입력");

	/*UIDialog* inputScore= new UIDialog();
	inputScore->Init(Vector2{ 100.f, 250.f }, Vector2{ 1000.f, 350.f }, _str2);
	AddObject(inputScore);*/
	

	//랭크 등록->다시하기로
	UIButton* inRank = new UIButton(Vector2{ 250,600 }, nullptr/*랭크 등록 이벤트 넣을 것*/, L"UI_Button_scorecount_InRank", L".png");
	AddObject(inRank);
	
	

	UIImage* myNoTitle = new UIImage(); // 객체 테스트 
	Gdiplus::Bitmap* myNoTitleBitmap = CRM->LoadBitmapResouce(L"UI_NoTitle", L"notitle_resize.jpg");
	myNoTitle->Init(myNoTitleBitmap, { 850.f,280.f });
	AddObject(myNoTitle);

	if (playerRank < 11)
	{
		wcscpy_s(_father_str, 255, L"우리 아빠 이름은");
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
	//게임 다시 시작하는 버튼과 이벤트
	GameRetryEvent* e_gameRetry = new GameRetryEvent(mySound::eSoundList::Button_Use); //게임 다시 시작하는 이벤트
	UIButton* gameRetry = new UIButton(Vector2{ 650, 600 }, e_gameRetry/*랭크 확인 이벤트 넣을 것*/, L"UI_Button_Retry", L".png");
	AddEvent(e_gameRetry);
	AddObject(gameRetry);
	

	//랭크 확인 제거
	
	//메인 메뉴로 가는 버튼과 이벤트
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
