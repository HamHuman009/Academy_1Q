#include "StartScene.h"
#include "../System/InputSystem.h"

#include "../GameLogic/Event.h"
#include "../GameLogic/Objects/KeyInput.h"
#include "../GameLogic/Objects/Fish.h"


void StartScene::Start()
{
	mySound::SoundManager* meSound = mySound::SoundManager::GetInstance();
	meSound->StopMusic(mySound::eSoundChannel::BGM);
	meSound->PlayMusic(mySound::eSoundList::Main_Theme/*s_ending*/, mySound::eSoundChannel::BGM);
}

void StartScene::Init()
{
	//필요 인스턴스 로드
	CResourceManager* CR = CResourceManager::GetInstance();
	Ranking* myRang = Game::GameManager::GetInstance()->m_Ranking;

	//스코어 초기화
	Game::GameManager::GetInstance()->BossCount = 0;
	Game::GameManager::GetInstance()->FinalScore = 0;
	Game::GameManager::GetInstance()->SetRoot(0);

	//랭크 불러오기
	myRang->sortRank();
	myRang->rankToStr();

	//배경
	UIImage* myBackGround = new UIImage();
	Gdiplus::Bitmap* waterBack = CR->LoadBitmapResouce(L"waterImage", L"Water.png");
	myBackGround->Init(waterBack, { 640.f, 360.f });
	UIBackGround* myUPBackGround = new UIBackGround();
	myUPBackGround->Init(L"물결+그림자_00.png", CR);

	////랭킹보드
	/*UIImage* rankingBoard = new UIImage();
	Gdiplus::Bitmap* rankingBack = CR->LoadBitmapResouce(L"ranking", L"UI_Button_Title_Ranking.png");
	rankingBoard->Init(rankingBack, { 1450.f, 340.f });

	MoveObject* moveAbleObject = new MoveObject(rankingBoard, {950, 340}, 1.f);
	AddObject(moveAbleObject);*/


	//타이틀 //70 , 48 //544,144
	Gdiplus::Bitmap* titleBitmap = CR->LoadBitmapResouce(L"logo", L"Logo_final.png");
	UIImage* titleImg = new UIImage(); // 객체 테스트 
	titleImg->Init(titleBitmap, { 370, 250 });
	//titleImg->Init(titleBitmap, { 70 + (328 / 2),48 + (223 / 2) });

	//이벤트
	SelectScnEvent* e_nextScn = new SelectScnEvent((UINT)SceneType::INTRO, mySound::eSoundList::Button_Use); // 씬전환 이벤트 테스트 버튼
	ExitEvent* e_exit = new ExitEvent(mySound::eSoundList::Button_Use);

	//게임 방법
	Gdiplus::Bitmap* howToPlayImage = CR->LoadBitmapResouce(L"HowToPlay", L"UI_Image_ToMoveImage.png");
	UIImage* howToPlay = new UIImage();
	howToPlay->Init(howToPlayImage, { 640.f, 360.f });
	howToPlay->m_isActive = false;
	HowToEvent* myHow = new HowToEvent();
	myHow->howToImg = howToPlay;


	/*UIButton* gameStartButton = new UIButton(Vector2{70 + (200 / 2),330 + (50 / 2)}, e_nextScn, L"UI_Button_Title_StartGame", L".png"); // 객체 테스트
	//게임 방법 버튼
	UIButton* controll = new UIButton(Vector2{ 70 + (200 / 2),450 + (50 / 2) }, myHow, L"UI_Button_Title_ToMove", L".png");

	//종료버튼
	UIButton* exit = new UIButton(Vector2{ 70 + (200 / 2),570 + (50 / 2) }, e_exit, L"UI_Button_Title_GameOver", L".png");*/

	//시작버튼 
	//SelectScnEvent* e_nextScn = new SelectScnEvent((UINT)SceneType::Dialog1,mySound::eSoundList::Button); // 씬전환 이벤트 테스트 버튼

	UIButton* gameStartButton = new UIButton(Vector2{ 80 + (200 / 2),520 + (50 / 2) }, e_nextScn, L"UI_Button_Title_StartGame", L".png"); // 객체 테스트
	//게임 방법 버튼
	UIButton* controll = new UIButton(Vector2{ 270 + (200 / 2),520 + (50 / 2) }, myHow, L"UI_Button_Title_ToMove", L".png");

	//종료버튼
	UIButton* exit = new UIButton(Vector2{ 460 + (200 / 2),520 + (50 / 2) }, e_exit, L"UI_Button_Title_GameOver", L".png");
	

	//게임 방법 돌아오기


	//랭크보드
	scoreRect = { 400,200,800,800 };
	UIImage* rankBoard = new UIImage();
	Gdiplus::Bitmap* rankImage = CR->LoadBitmapResouce(L"RankBoard",L"UI_Title_Ranking.png");
	rankBoard->Init(rankImage,{ 1450.f, 340.f });

	//랭킹보드 움직이는 오브젝트
	MoveObject* moveAbleObject = new MoveObject(rankBoard, { 950, 340 }, 1.f);
	AddObject(moveAbleObject);

	/*WCHAR _str[500];
	memset(_str, L'\0', 500);

	std::string myRank;
	int fromRank = strlen(Game::GameManager::GetInstance()->m_Ranking->str_rank.c_str());
	myRank.assign(Game::GameManager::GetInstance()->m_Ranking->str_rank);
	int sizeNeeded = MultiByteToWideChar(CP_UTF8, 0, &myRank[0], (int)myRank.size(), NULL, 0);
	MultiByteToWideChar(CP_UTF8, 0, &myRank[0], fromRank, &_str[0], sizeNeeded);*/

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
		rankDialog[i]->Init({1350.f, 173.f + 45.f * i}, {200.f,100.f}, top10[i], 16, COLORREF(0x271a14));

		moveRank[i] = new MoveObject(rankDialog[i], { 850.f + 100, 173.f + 45.f * i  + 50.f}, 1.f);
		
		_itow_s(temp.score, top10score[i], 10);
		scoreDialog[i] = new UIDialog();
		scoreDialog[i]->Init({ 1565.f - (wcslen(top10score[i]) * 13 ),173.f + 45 * i}, {200.f,100.f}, top10score[i], 16, COLORREF(0x271a14));

		moveScore[i] = new MoveObject(scoreDialog[i], { 1065.f - (wcslen(top10score[i]) * 13) + 100,173.f + 45 * i + 50}, 1.f);

		//MoveObject* moveAbleObject = new MoveObject(rankBoard, { 950, 340 }, 1.f);
		//AddObject(moveAbleObject);
	}
	
	
	/*UIDialog* rankDialog = new UIDialog();
	rankDialog->Init({ 752,48 }, { 432,624 }, _str);*/

	//조작
	//UIButton* exit = new UIButton(Vector2{ 70 + (200 / 2),472 + (50 / 2) }, e_exit, exitBtn);

	//화면전환
	UICrossDissolve* backEffect = new UICrossDissolve({ 640.f, 360.f }, Game::GameManager::GetInstance()->sceneBitmap);
	

	KeyInput* myKey = new KeyInput();
	myKey->Init();
	myKey->m_Event = myHow;

	AddObject(myKey);

	//오브젝트 등록
	AddObject(myBackGround);

	Fish* myFish;
	myFish = new Fish(L"Fish1", 50.f, 4.36f, L"Fish_01_Anim_00.png", CR, L".png", 3.f, 4.f, 23.f, 23.f);
	AddObject(myFish);
	myFish = new Fish(L"Fish2", 50.f, 4.36f, L"Fish_02_Anim_00.png", CR, L".png", 3.f, 4.f, 23.f, 23.f);
	AddObject(myFish);
	myFish = new Fish(L"Fish3", 50.f, 4.36f, L"Fish_03_Anim_00.png", CR, L".png", 3.f, 4.f, 23.f, 23.f);
	AddObject(myFish);
	myFish = new Fish(L"Fish4", 50.f, 4.36f, L"Fish_04_Anim_00.png", CR, L".png", 3.f, 4.f, 23.f, 23.f);
	AddObject(myFish);

	AddObject(myUPBackGround);

	
	AddObject(gameStartButton);
	AddObject(controll);
	AddObject(exit);
	AddObject(rankBoard);
	for (int i = 0; i < Game::GameManager::GetInstance()->m_Ranking->players.size(); i++) {
		AddObject(rankDialog[i]);
		AddObject(moveRank[i]);
	}
	for (int i = 0; i < Game::GameManager::GetInstance()->m_Ranking->players.size(); i++) {
		AddObject(scoreDialog[i]);
		AddObject(moveScore[i]);
	}

	
	
	//이벤트 등록
	AddEvent(e_nextScn);
	AddEvent(e_exit);
	AddEvent(myHow);
	AddObject(titleImg);

	AddObject(howToPlay);
	AddObject(backEffect);
	//화면 알파 값 초기화
	alpha = 1.0f;

	/*BGSound_Plus* bg_Plus = new BGSound_Plus();
	BGSound_Minus* bg_Minus = new BGSound_Minus();
	EffectSound_Plus* eft_Plus = new EffectSound_Plus();
	EffectSound_Minus* eft_Minus = new EffectSound_Minus();
	AddEvent(bg_Plus);
	AddEvent(bg_Minus);
	AddEvent(eft_Plus);
	AddEvent(eft_Minus);

	UIButton* b_Plus = new UIButton({ 600, 500 }, bg_Plus, L"Plus", L".png");
	UIButton* b_Minus = new UIButton({ 700, 500 }, bg_Minus, L"Minus", L".png");
	UIButton* e_Plus = new UIButton({ 600, 600 }, eft_Plus, L"Plus", L".png");
	UIButton* e_Minus = new UIButton({ 700, 600 }, eft_Minus, L"Minus", L".png");
	AddObject(b_Plus);
	AddObject(b_Minus);
	AddObject(e_Plus);
	AddObject(e_Minus);*/
}

StartScene::~StartScene() {
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