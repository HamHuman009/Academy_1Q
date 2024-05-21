#include "StartScene.h"
#include "../System/InputSystem.h"

#include "../GameLogic/Event.h"


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

	//��ũ �ҷ�����
	myRang->sortRank();
	myRang->rankToStr();

	//���
	myBitmap = CR->LoadBitmapResouce(L"image1",L"startback.png");
	UIImage* myBack = new UIImage(); // ��ü �׽�Ʈ 
	myBack->Init(myBitmap, { 640.f,360.f });
	
	//Ÿ��Ʋ //70 , 48 //544,144
	Gdiplus::Bitmap* titleBitmap = CR->LoadBitmapResouce(L"title", L"titled_sample.bmp");
	UIImage* titleImg = new UIImage(); // ��ü �׽�Ʈ 
	titleImg->Init(titleBitmap, { 70 + (544 / 2),48 + (144 / 2) });

	//�̺�Ʈ
	SelectScnEvent* e_nextScn = new SelectScnEvent((UINT)SceneType::INTRO, mySound::eSoundList::Button); // ����ȯ �̺�Ʈ �׽�Ʈ ��ư
	ExitEvent* e_exit = new ExitEvent(mySound::eSoundList::Button);

	//���۹�ư 
	//SelectScnEvent* e_nextScn = new SelectScnEvent((UINT)SceneType::Dialog1,mySound::eSoundList::Button); // ����ȯ �̺�Ʈ �׽�Ʈ ��ư

	UIButton* gameStartButton = new UIButton(Vector2{ 70 + (200 / 2),254 + (50 / 2) }, e_nextScn, L"UI_Button_Title_StartGame",L".png"); // ��ü �׽�Ʈ
	//�����ư
	UIButton* exit = new UIButton(Vector2{ 70 + (200 / 2),472 + (50 / 2) }, e_exit, L"UI_Button_Title_GameOver", L".png");
	//����
	UIButton* controll = new UIButton(Vector2{ 70 + (200 / 2),363 + (50 / 2) }, nullptr, L"UI_Button_Title_ToMove", L".png"); 

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
	AddObject(myBack);
	AddObject(titleImg);
	AddObject(gameStartButton);
	AddObject(controll);
	AddObject(exit);
	AddObject(rankDialog);
	AddObject(backEffect);

	//�̺�Ʈ ���
	AddEvent(e_nextScn);
	AddEvent(e_exit);

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