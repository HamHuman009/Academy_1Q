#include "StartScene.h"
#include "../System/InputSystem.h"

#include "../GameLogic/Event.h"


void StartScene::Start() 
{

}

void StartScene::Init()
{	
	Ranking* myRang = Game::GameManager::GetInstance()->m_Ranking;
	myRang->sortRank();
	myRang->rankToStr();
	CResourceManager* CR = CResourceManager::GetInstance();
	myBitmap = CR->LoadBitmapResouce(L"image1",L"startback.png");
	UIImage* myBack = new UIImage(); // ��ü �׽�Ʈ 
	myBack->Init(myBitmap, { 640.f,360.f });
	
	/*SelectScnEvent* a = new SelectScnEvent(3);
	delete a;*/
	/*Gdiplus::Bitmap* startBtn = CR->LoadBitmapResouce(L"startBtn", L"startbtn_sample.bmp");
	Gdiplus::Bitmap* exitBtn = CR->LoadBitmapResouce(L"exitBtn", L"exitbtn_sample.bmp");*/

	//Ÿ��Ʋ
	Gdiplus::Bitmap* titleBitmap = CR->LoadBitmapResouce(L"title", L"titled_sample.bmp");
	UIImage* titleImg = new UIImage(); // ��ü �׽�Ʈ 
	////70 , 48
	////544,144
	titleImg->Init(titleBitmap, { 70 + (544 / 2),48 + (144 / 2) });

	SelectScnEvent* e_nextScn = new SelectScnEvent((UINT)SceneType::INTRO,mySound::eSoundList::Button); // ����ȯ �̺�Ʈ �׽�Ʈ
	UIButton* gameStartButton = new UIButton(Vector2{ 70 + (200 / 2),254 + (50 / 2) }, e_nextScn, L"UI_Button_Title_StartGame",L".png"); // ��ü �׽�Ʈ
	
	scoreRect = { 400,200,800,800 };
	
	WCHAR _str[500];
	memset(_str, L'\0', 500);
	//WCHAR t_str[] = L"��ŷ ���� ������ ���\n �ҷ����°� ������ ���� �����Ұ�";
	std::string myRank;
	int fromRank = strlen(Game::GameManager::GetInstance()->m_Ranking->str_rank.c_str());
	myRank.assign(Game::GameManager::GetInstance()->m_Ranking->str_rank);
	
	int sizeNeeded = MultiByteToWideChar(CP_UTF8, 0, &myRank[0], (int)myRank.size(), NULL, 0);
	MultiByteToWideChar(CP_UTF8, 0, &myRank[0], fromRank, &_str[0], sizeNeeded);
	UIDialog* rankDialog = new UIDialog();
	rankDialog->Init({ 752,48 }, { 432,624 }, _str);

	ExitEvent* e_exit = new ExitEvent;
	//UIButton* exit = new UIButton(Vector2{ 200.0f,600.0f }, e_exit, exitBtn);
	UIButton* exit = new UIButton(Vector2{ 70 + (200 / 2),472 + (50 / 2) }, e_exit, L"UI_Button_Title_GameOver", L".png");
	UIInputField* inputField = new UIInputField({500.f, 500.f}, 200.f, 150.f);

	//����
	//UIButton* exit = new UIButton(Vector2{ 70 + (200 / 2),472 + (50 / 2) }, e_exit, exitBtn);
	UIButton* controll = new UIButton(Vector2{ 70 + (200 / 2),363 + (50 / 2) },nullptr,L"UI_Button_Title_ToMove",L".png");\
	
	AddObject(myBack);
	AddObject(titleImg);
	AddObject(gameStartButton);
	AddObject(controll);
	AddObject(exit);
	AddEvent(e_nextScn);
	
	AddEvent(e_exit);

	AddObject(inputField);
	
	UICrossDissolve* backEffect = new UICrossDissolve({ 640.f, 360.f }, Game::GameManager::GetInstance()->sceneBitmap);
	AddObject(backEffect);
	
	alpha = 1.0f;

	AddObject(rankDialog);
	//Test-------------end

}

StartScene::~StartScene() {
	//delete[] _str;
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