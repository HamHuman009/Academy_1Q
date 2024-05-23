#include "ScoreScene.h"
#include "../GameLogic/Objects/UIObject.h"
#include "../GameLogic/Event.h"





void ScoreScene::Init()
{	
	
	
	WCHAR _scoreStr[255];
	WCHAR _rankStr[255];
	std::wstring _wScore = L"";
	std::wstring _wRank = L"";

	_wScore.append(std::to_wstring(Game::GameManager::GetInstance()->FinalScore));
	_wScore.append(L"점");

	int playerRank = Game::GameManager::GetInstance()->m_Ranking->InRankPlayer(Game::GameManager::GetInstance()->FinalScore);
	_wRank.append(std::to_wstring(playerRank));

	CResourceManager* CRM = CResourceManager::GetInstance();

	UIImage* myBackGround = new UIImage();
	Gdiplus::Bitmap* waterBack = CRM->LoadBitmapResouce(L"waterImage", L"Water.png");
	myBackGround->Init(waterBack, { 640.f, 360.f });
	UIBackGround* myUPBackGround = new UIBackGround();
	myUPBackGround->Init(L"물결+그림자_00.png", CRM);
	AddObject(myBackGround);
	AddObject(myUPBackGround);

	Gdiplus::Bitmap* myBitmap = CRM->LoadBitmapResouce(L"UI_Rank", L"UI_Window_scorecount_Rank_Window_01.png");
	UIImage* myBack = new UIImage(); // 객체 테스트 
	myBack->Init(myBitmap, { 640.f,360.f });
	AddObject(myBack);
	
	Gdiplus::Bitmap* scoreBoxBackImg = CRM->LoadBitmapResouce(L"scoreBoxBack", L"우리아빠점수는_Box.png");
	Gdiplus::Bitmap* scoreBoxTextImg = CRM->LoadBitmapResouce(L"scoreBoxText", L"우리 아빠 점수는_.png");
	Gdiplus::Bitmap* rankTextImg = CRM->LoadBitmapResouce(L"rankText", L"등 아빠야!.png");
	Gdiplus::Bitmap* rankSet1Img = CRM->LoadBitmapResouce(L"rankSet1", L"칭호_아빠진짜최고야.png");
	Gdiplus::Bitmap* rankSet2Img = CRM->LoadBitmapResouce(L"rankSet2", L"칭호_다정한아빠.png");
	Gdiplus::Bitmap* rankSet3Img = CRM->LoadBitmapResouce(L"rankSet3", L"칭호_사랑하는아빠.png");
	Gdiplus::Bitmap* rankSet4Img = CRM->LoadBitmapResouce(L"rankSet4", L"항상최선을다하는아빠_칭호.png");
	Gdiplus::Bitmap* rankSet5Img = CRM->LoadBitmapResouce(L"rankSet5", L"아빠정말좋아.png");
	Gdiplus::Bitmap* nameBoxBackImg = CRM->LoadBitmapResouce(L"nameBoxBack", L"이름뭐였지_box.png");
	Gdiplus::Bitmap* nonNameTextImg = CRM->LoadBitmapResouce(L"nonNameText", L"다음엔더많이잡아줘.png");
	Gdiplus::Bitmap* nameBoxTextImg = CRM->LoadBitmapResouce(L"nameBoxText", L"아빠 이름이 뭐였지__.png");

	//우리아빠 점수는 + 점수 텍스트
	UIImage* scoreBoxBack = new UIImage();
	scoreBoxBack->Init(scoreBoxBackImg, { 640.f,180.f });
	UIImage* scoreBoxText = new UIImage(); 
	scoreBoxText->Init(scoreBoxTextImg, { 640.f,160.f });

	//~등 아빠야
	UIImage* rankText = new UIImage();
	rankText->Init(rankTextImg, { 550.f, 287.f });
	
	//순위따라 바뀌는 창
	UIImage* rankSetText = new UIImage();
	UIImage* nonRankSetText = new UIImage();

	//아빠이름이 뭐였지
	UIImage* nameBoxBack = new UIImage();
	nameBoxBack->Init(nameBoxBackImg, { 640.f,370.f });
	UIImage* nameBoxText = new UIImage();
	nameBoxText->Init(nameBoxTextImg, { 640.f,370.f });


	UIDialog* myScore = new UIDialog();
	wcscpy_s(_scoreStr, 255, _wScore.c_str());


	UIDialog* myRank = new UIDialog();
	wcscpy_s(_rankStr, 255, _wRank.c_str());

	// 점수
	myScore->Init(Vector2{ 600.f,175.f }, Vector2{ 120.f, 70.f }, _scoreStr, 40);

	// 등수
	myRank->Init(Vector2{ 410.f,255.f }, Vector2{ 120.f, 60.f }, _rankStr, 40);

	// 이름 인풋
	UIInputField* myInputField = new UIInputField(Vector2{ 820.f, 470.f }, 500.f, 100.f);
	myInputField->Init();
	

	AddObject(scoreBoxBack);
	AddObject(scoreBoxText);
	AddObject(myScore);
	switch (playerRank)
	{
	case 1:
		_wRank.append(std::to_wstring(playerRank));
		rankSetText->Init(rankSet1Img, { 780.f,257.f });
		AddObject(rankText);
		AddObject(rankSetText);
		AddObject(nameBoxBack);
		AddObject(nameBoxText);
		AddObject(myRank);
		AddObject(myInputField);
		break;
	case 2:
	case 3:
		_wRank.append(std::to_wstring(playerRank));
		rankSetText->Init(rankSet2Img, { 780.f,256.f });
		AddObject(rankText);
		AddObject(rankSetText);
		AddObject(nameBoxBack);
		AddObject(nameBoxText);
		AddObject(myRank);
		AddObject(myInputField);
		break;
	case 4:
	case 5:
	case 6:
	case 7:
		_wRank.append(std::to_wstring(playerRank));
		rankSetText->Init(rankSet3Img, { 765.f,257.f });
		AddObject(rankText);
		AddObject(rankSetText);
		AddObject(nameBoxBack);
		AddObject(nameBoxText);
		AddObject(myRank);
		AddObject(myInputField);
		break;
	case 8:
	case 9:
	case 10:
		_wRank.append(std::to_wstring(playerRank));
		rankSetText->Init(rankSet4Img, { 800.f,254.f });
		AddObject(rankText);
		AddObject(rankSetText);
		AddObject(nameBoxBack);
		AddObject(nameBoxText);
		AddObject(myRank);
		AddObject(myInputField);
		break;
	default:
		rankSetText->Init(rankSet5Img, { 650.f,350.f });
		nonRankSetText->Init(nonNameTextImg, { 630.f,350.f });
		AddObject(rankSetText);
		AddObject(nonRankSetText);
		break;
	}
	

	

	//랭크 등록->다시하기로
	UIButton* inRank = new UIButton(Vector2{ 340 ,565 }, nullptr/*랭크 등록 이벤트 넣을 것*/, L"UI_Button_scorecount_InRank", L".png");
	AddObject(inRank);

	ButtonOnTriggerAndActiveFalseEvent* e_inRank = new ButtonOnTriggerAndActiveFalseEvent(inRank, myInputField);
	AddEvent(e_inRank);
	inRank->m_Event = e_inRank;
	

	//게임 다시 시작하는 버튼과 이벤트
	GameRetryEvent* e_gameRetry = new GameRetryEvent(mySound::eSoundList::Button_Use); //게임 다시 시작하는 이벤트
	UIButton* gameRetry = new UIButton(Vector2{ 640, 565 }, e_gameRetry/*랭크 확인 이벤트 넣을 것*/, L"UI_Button_Retry", L".png");
	AddEvent(e_gameRetry);
	AddObject(gameRetry);
	

	//랭크 확인 제거
	
	//메인 메뉴로 가는 버튼과 이벤트
	RetryEvent* e_mainMenu = new RetryEvent(mySound::eSoundList::Button_Use);
	UIButton* mainMenuBtn = new UIButton(Vector2{ 940 ,565 }, e_mainMenu, L"UI_Button_MainMenu", L".png");
	AddEvent(e_mainMenu);
	AddObject(mainMenuBtn);
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
