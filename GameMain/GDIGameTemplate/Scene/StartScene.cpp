#include "StartScene.h"
#include "../System/InputSystem.h"

#include "../GameLogic/Event.h"
#include "../GameLogic/Objects/Fish.h"


void StartScene::Start()
{
	mySound::SoundManager* meSound = mySound::SoundManager::GetInstance();
	meSound->StopMusic(mySound::eSoundChannel::BGM);
	meSound->PlayMusic(mySound::eSoundList::BGM/*s_ending*/, mySound::eSoundChannel::BGM);
}

void StartScene::Init()
{
	//�ʿ� �ν��Ͻ� �ε�
	CResourceManager* CR = CResourceManager::GetInstance();
	Ranking* myRang = Game::GameManager::GetInstance()->m_Ranking;

	//���ھ� �ʱ�ȭ
	Game::GameManager::GetInstance().g_sc

	//��ũ �ҷ�����
	myRang->sortRank();
	myRang->rankToStr();

	//���
	//myBitmap = CR->LoadBitmapResouce(L"image1",L"startback.png");
	//UIImage* myBack = new UIImage(); // ��ü �׽�Ʈ 
	//myBack->Init(myBitmap, { 640.f,360.f });
	UIImage* myBackGround = new UIImage();
	Gdiplus::Bitmap* waterBack = CR->LoadBitmapResouce(L"waterImage", L"Water.png");
	myBackGround->Init(waterBack, { 640.f, 360.f });
	UIBackGround* myUPBackGround = new UIBackGround();
	myUPBackGround->Init(L"����+�׸���_00.png", CR);

	//��ŷ����
	UIImage* rankingBoard = new UIImage();
	Gdiplus::Bitmap* rankingBack = CR->LoadBitmapResouce(L"ranking", L"UI_Button_Title_Ranking.png");
	rankingBoard->Init(rankingBack, { 1450.f, 340.f });

	MoveObject* moveAbleObject = new MoveObject(rankingBoard, {950, 340}, 1.f);
	AddObject(moveAbleObject);

	//Ÿ��Ʋ //70 , 48 //544,144
	Gdiplus::Bitmap* titleBitmap = CR->LoadBitmapResouce(L"logo", L"Logo_final.png");
	UIImage* titleImg = new UIImage(); // ��ü �׽�Ʈ 
	titleImg->Init(titleBitmap, { 370, 250 });
	//titleImg->Init(titleBitmap, { 70 + (328 / 2),48 + (223 / 2) });

	//�̺�Ʈ
	SelectScnEvent* e_nextScn = new SelectScnEvent((UINT)SceneType::INTRO, mySound::eSoundList::Button); // ����ȯ �̺�Ʈ �׽�Ʈ ��ư
	ExitEvent* e_exit = new ExitEvent(mySound::eSoundList::Button);

	//���� ���
	Gdiplus::Bitmap* howToPlayImage = CR->LoadBitmapResouce(L"HowToPlay", L"image1.png");
	UIImage* howToPlay = new UIImage();
	howToPlay->Init(howToPlayImage, { 500.f,400.f });
	howToPlay->m_isActive = false;
	HowToEvent* myHow = new HowToEvent();
	myHow->howToImg = howToPlay;


	/*UIButton* gameStartButton = new UIButton(Vector2{70 + (200 / 2),330 + (50 / 2)}, e_nextScn, L"UI_Button_Title_StartGame", L".png"); // ��ü �׽�Ʈ
	//���� ��� ��ư
	UIButton* controll = new UIButton(Vector2{ 70 + (200 / 2),450 + (50 / 2) }, myHow, L"UI_Button_Title_ToMove", L".png");

	//�����ư
	UIButton* exit = new UIButton(Vector2{ 70 + (200 / 2),570 + (50 / 2) }, e_exit, L"UI_Button_Title_GameOver", L".png");*/

	//���۹�ư 
	//SelectScnEvent* e_nextScn = new SelectScnEvent((UINT)SceneType::Dialog1,mySound::eSoundList::Button); // ����ȯ �̺�Ʈ �׽�Ʈ ��ư

	UIButton* gameStartButton = new UIButton(Vector2{ 80 + (200 / 2),520 + (50 / 2) }, e_nextScn, L"UI_Button_Title_StartGame", L".png"); // ��ü �׽�Ʈ
	//���� ��� ��ư
	UIButton* controll = new UIButton(Vector2{ 270 + (200 / 2),520 + (50 / 2) }, myHow, L"UI_Button_Title_ToMove", L".png");

	//�����ư
	UIButton* exit = new UIButton(Vector2{ 460 + (200 / 2),520 + (50 / 2) }, e_exit, L"UI_Button_Title_GameOver", L".png");
	

	//���� ��� ���ƿ���


	//��ũ����
	scoreRect = { 400,200,800,800 };
	WCHAR _str[500];
	memset(_str, L'\0', 500);

	std::string myRank;
	int fromRank = strlen(Game::GameManager::GetInstance()->m_Ranking->str_rank.c_str());
	myRank.assign(Game::GameManager::GetInstance()->m_Ranking->str_rank);
	int sizeNeeded = MultiByteToWideChar(CP_UTF8, 0, &myRank[0], (int)myRank.size(), NULL, 0);
	MultiByteToWideChar(CP_UTF8, 0, &myRank[0], fromRank, &_str[0], sizeNeeded);
	UIDialog* rankDialog = new UIDialog();
	rankDialog->Init({ 752,48 }, { 432,624 }, _str);

	//����
	//UIButton* exit = new UIButton(Vector2{ 70 + (200 / 2),472 + (50 / 2) }, e_exit, exitBtn);

	//ȭ����ȯ
	UICrossDissolve* backEffect = new UICrossDissolve({ 640.f, 360.f }, Game::GameManager::GetInstance()->sceneBitmap);




	//������Ʈ ���
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
	AddObject(rankingBoard);
	AddObject(rankDialog);
	AddObject(backEffect);
	AddObject(howToPlay);
	//�̺�Ʈ ���
	AddEvent(e_nextScn);
	AddEvent(e_exit);
	AddEvent(myHow);
	AddObject(titleImg);
	//ȭ�� ���� �� �ʱ�ȭ
	alpha = 1.0f;
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