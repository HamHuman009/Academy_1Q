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
	// _str = 점수;
	std::wstring _wstr = L"우리 아빠 점수는 : ";
	std::wstring _wScore = L"";
	_wScore.append(std::to_wstring(Game::GameManager::GetInstance()->FinalScore));
	CResourceManager* CRM = CResourceManager::GetInstance();
	myBitmap = CRM->LoadBitmapResouce(L"UI_Rank", L"UI_Window_scorecount_Rank_Window_01.png");
	UIImage* myBack = new UIImage(); // 객체 테스트 
	myBack->Init(myBitmap, { 640.f,360.f });
	AddObject(myBack);

	/*int playerRank = Game::GameManager::GetInstance()->m_Ranking->InRankPlayer(Game::GameManager::GetInstance()->FinalScore);
	_wstr.append(std::to_wstring(playerRank));
	_wstr.append(L"등");*/

	UIDialog* myScoreDial = new UIDialog();
	wcscpy_s(_str,255,_wstr.c_str());
	UIDialog* myScore = new UIDialog();
	wcscpy_s(_scoreStr, 255, _wScore.c_str());
	myScoreDial->Init(Vector2{ 100.f, 100.f }, Vector2{ 1000.f, 150.f }, _str);
	AddObject(myScoreDial);
	myScore->Init(Vector2{ 310.f, 93.f }, Vector2{ 1000.f, 150.f }, _scoreStr,40);
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

	UIImage* myNoTitle = new UIImage(); // 객체 테스트 
	Gdiplus::Bitmap* myNoTitleBitmap = CRM->LoadBitmapResouce(L"UI_NoTitle", L"notitle_resize.jpg");
	myNoTitle->Init(myNoTitleBitmap, { 850.f,280.f });
	AddObject(myNoTitle);

	UIInputField* myInputField = new UIInputField(Vector2{ 350.f,350.f }, 500.f, 100.f);
	myInputField->Init();
	AddObject(myInputField);

	UIButton* inRank = new UIButton(Vector2{ 250,600 }, nullptr/*랭크 등록 이벤트 넣을 것*/, L"UI_Button_scorecount_InRank", L".png");
	AddObject(inRank);

	ButtonOnTriggerAndActiveFalseEvent* e_inRank = new ButtonOnTriggerAndActiveFalseEvent(inRank, myInputField);
	AddEvent(e_inRank);
	inRank->m_Event = e_inRank;
		
	UIButton* toRank = new UIButton(Vector2{650, 600}, nullptr/*랭크 확인 이벤트 넣을 것*/, L"UI_Button_scorecount_ToRank", L".png");
	AddObject(toRank);
	RetryEvent* e_retry = new RetryEvent(mySound::eSoundList::Button_Use);
	//Gdiplus::Bitmap* exitBtn = CRM->LoadBitmapResouce(L"exitBtn", L"exitbtn_sample.bmp");
	UIButton* retry = new UIButton(Vector2{ 1050,600 }, e_retry, L"UI_Button_MainMenu", L".png");
	AddEvent(e_retry);
	AddObject(retry);
	
	UIImage* rankBoard = new UIImage();
	Gdiplus::Bitmap* rankImage = CRM->LoadBitmapResouce(L"RankBoard", L"UI_Title_Ranking.png");
	rankBoard->Init(rankImage, { 1450.f, 340.f });
	
	MoveObject* moveAbleObject = new MoveObject(rankBoard, { 950, 340 }, 1.f);
	AddObject(moveAbleObject);

	WCHAR top10[10][50];
	WCHAR top10score[10][10];
	for (int i = 0; i < 10; i++) {
		for (int k = 0; k < 50; k++) {
			top10[i][k] = L'\0';
		}
		for (int k = 0; k < 10; k++) {
			top10score[i][k] = L'\0';
		}
	}
	UIDialog* rankDialog[10];
	UIDialog* scoreDialog[10];
	MoveObject* moveRank[10];
	MoveObject* moveScore[10];
	for (int i = 0; i < Game::GameManager::GetInstance()->m_Ranking->players.size(); i++) {

		Ranking::r_Player temp = Game::GameManager::GetInstance()->m_Ranking->players[i];
		int plen = strlen(temp.name.c_str());
		std::string tempStr;
		tempStr.assign(temp.name.c_str());
		int sizeNeeded = MultiByteToWideChar(CP_UTF8, 0, &tempStr[0], (int)tempStr.size(), NULL, 0);
		MultiByteToWideChar(CP_UTF8, 0, &tempStr[0], plen, top10[i], sizeNeeded);
		rankDialog[i] = new UIDialog();
		//rankDialog[i]->Init({850.f,173.f+45*i}, {200.f,100.f}, top10[i], 16, COLORREF(0x271a14));
		rankDialog[i]->Init({ 1350.f, 173.f + 45.f * i }, { 200.f,100.f }, top10[i], 16, COLORREF(0x271a14));

		moveRank[i] = new MoveObject(rankDialog[i], { 850.f + 100, 173.f + 45.f * i + 50.f }, 1.f);

		_itow_s(temp.score, top10score[i], 10);
		scoreDialog[i] = new UIDialog();
		scoreDialog[i]->Init({ 1565.f - (wcslen(top10score[i]) * 13),173.f + 45 * i }, { 200.f,100.f }, top10score[i], 16, COLORREF(0x271a14));

		moveScore[i] = new MoveObject(scoreDialog[i], { 1065.f - (wcslen(top10score[i]) * 13) + 100,173.f + 45 * i + 50 }, 1.f);
	}

	AddObject(rankBoard);
	for (int i = 0; i < Game::GameManager::GetInstance()->m_Ranking->players.size(); i++) {
		AddObject(rankDialog[i]);
		AddObject(moveRank[i]);
	}
	for (int i = 0; i < Game::GameManager::GetInstance()->m_Ranking->players.size(); i++) {
		AddObject(scoreDialog[i]);
		AddObject(moveScore[i]);
	}
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
