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
	_wScore.append(L"��");

	int playerRank = Game::GameManager::GetInstance()->m_Ranking->InRankPlayer(Game::GameManager::GetInstance()->FinalScore);
	_wRank.append(std::to_wstring(playerRank));

	CResourceManager* CRM = CResourceManager::GetInstance();

	UIImage* myBackGround = new UIImage();
	Gdiplus::Bitmap* waterBack = CRM->LoadBitmapResouce(L"waterImage", L"Water.png");
	myBackGround->Init(waterBack, { 640.f, 360.f });
	UIBackGround* myUPBackGround = new UIBackGround();
	myUPBackGround->Init(L"����+�׸���_00.png", CRM);
	AddObject(myBackGround);
	AddObject(myUPBackGround);

	Gdiplus::Bitmap* myBitmap = CRM->LoadBitmapResouce(L"UI_Rank", L"UI_Window_scorecount_Rank_Window_01.png");
	UIImage* myBack = new UIImage(); // ��ü �׽�Ʈ 
	myBack->Init(myBitmap, { 640.f,360.f });
	AddObject(myBack);
	
	Gdiplus::Bitmap* scoreBoxBackImg = CRM->LoadBitmapResouce(L"scoreBoxBack", L"�츮�ƺ�������_Box.png");
	Gdiplus::Bitmap* scoreBoxTextImg = CRM->LoadBitmapResouce(L"scoreBoxText", L"�츮 �ƺ� ������_.png");
	Gdiplus::Bitmap* rankTextImg = CRM->LoadBitmapResouce(L"rankText", L"�� �ƺ���!.png");
	Gdiplus::Bitmap* rankSet1Img = CRM->LoadBitmapResouce(L"rankSet1", L"Īȣ_�ƺ���¥�ְ��.png");
	Gdiplus::Bitmap* rankSet2Img = CRM->LoadBitmapResouce(L"rankSet2", L"Īȣ_�����Ѿƺ�.png");
	Gdiplus::Bitmap* rankSet3Img = CRM->LoadBitmapResouce(L"rankSet3", L"Īȣ_����ϴ¾ƺ�.png");
	Gdiplus::Bitmap* rankSet4Img = CRM->LoadBitmapResouce(L"rankSet4", L"�׻��ּ������ϴ¾ƺ�_Īȣ.png");
	Gdiplus::Bitmap* rankSet5Img = CRM->LoadBitmapResouce(L"rankSet5", L"�ƺ���������.png");
	Gdiplus::Bitmap* nameBoxBackImg = CRM->LoadBitmapResouce(L"nameBoxBack", L"�̸�������_box.png");
	Gdiplus::Bitmap* nonNameTextImg = CRM->LoadBitmapResouce(L"nonNameText", L"�����������������.png");
	Gdiplus::Bitmap* nameBoxTextImg = CRM->LoadBitmapResouce(L"nameBoxText", L"�ƺ� �̸��� ������__.png");

	//�츮�ƺ� ������ + ���� �ؽ�Ʈ
	UIImage* scoreBoxBack = new UIImage();
	scoreBoxBack->Init(scoreBoxBackImg, { 640.f,180.f });
	UIImage* scoreBoxText = new UIImage(); 
	scoreBoxText->Init(scoreBoxTextImg, { 640.f,160.f });

	//~�� �ƺ���
	UIImage* rankText = new UIImage();
	rankText->Init(rankTextImg, { 550.f, 287.f });
	
	//�������� �ٲ�� â
	UIImage* rankSetText = new UIImage();
	UIImage* nonRankSetText = new UIImage();

	//�ƺ��̸��� ������
	UIImage* nameBoxBack = new UIImage();
	nameBoxBack->Init(nameBoxBackImg, { 640.f,370.f });
	UIImage* nameBoxText = new UIImage();
	nameBoxText->Init(nameBoxTextImg, { 640.f,370.f });


	UIDialog* myScore = new UIDialog();
	wcscpy_s(_scoreStr, 255, _wScore.c_str());


	UIDialog* myRank = new UIDialog();
	wcscpy_s(_rankStr, 255, _wRank.c_str());

	// ����
	myScore->Init(Vector2{ 600.f,175.f }, Vector2{ 120.f, 70.f }, _scoreStr, 40);

	// ���
	myRank->Init(Vector2{ 410.f,255.f }, Vector2{ 120.f, 60.f }, _rankStr, 40);

	// �̸� ��ǲ
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
	

	

	//��ũ ���->�ٽ��ϱ��
	UIButton* inRank = new UIButton(Vector2{ 340 ,565 }, nullptr/*��ũ ��� �̺�Ʈ ���� ��*/, L"UI_Button_scorecount_InRank", L".png");
	AddObject(inRank);

	ButtonOnTriggerAndActiveFalseEvent* e_inRank = new ButtonOnTriggerAndActiveFalseEvent(inRank, myInputField);
	AddEvent(e_inRank);
	inRank->m_Event = e_inRank;
	

	//���� �ٽ� �����ϴ� ��ư�� �̺�Ʈ
	GameRetryEvent* e_gameRetry = new GameRetryEvent(mySound::eSoundList::Button_Use); //���� �ٽ� �����ϴ� �̺�Ʈ
	UIButton* gameRetry = new UIButton(Vector2{ 640, 565 }, e_gameRetry/*��ũ Ȯ�� �̺�Ʈ ���� ��*/, L"UI_Button_Retry", L".png");
	AddEvent(e_gameRetry);
	AddObject(gameRetry);
	

	//��ũ Ȯ�� ����
	
	//���� �޴��� ���� ��ư�� �̺�Ʈ
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
