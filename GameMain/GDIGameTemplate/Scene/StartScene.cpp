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
	//필요 인스턴스 로드
	CResourceManager* CR = CResourceManager::GetInstance();
	Ranking* myRang = Game::GameManager::GetInstance()->m_Ranking;

	//랭크 불러오기
	myRang->sortRank();
	myRang->rankToStr();

	//배경
	myBitmap = CR->LoadBitmapResouce(L"image1",L"startback.png");
	UIImage* myBack = new UIImage(); // 객체 테스트 
	myBack->Init(myBitmap, { 640.f,360.f });
	
	//타이틀 //70 , 48 //544,144
	Gdiplus::Bitmap* titleBitmap = CR->LoadBitmapResouce(L"title", L"titled_sample.bmp");
	UIImage* titleImg = new UIImage(); // 객체 테스트 
	titleImg->Init(titleBitmap, { 70 + (544 / 2),48 + (144 / 2) });

	//이벤트
	SelectScnEvent* e_nextScn = new SelectScnEvent((UINT)SceneType::INTRO, mySound::eSoundList::Button); // 씬전환 이벤트 테스트 버튼
	ExitEvent* e_exit = new ExitEvent(mySound::eSoundList::Button);

	//시작버튼 
	//SelectScnEvent* e_nextScn = new SelectScnEvent((UINT)SceneType::Dialog1,mySound::eSoundList::Button); // 씬전환 이벤트 테스트 버튼

	UIButton* gameStartButton = new UIButton(Vector2{ 70 + (200 / 2),254 + (50 / 2) }, e_nextScn, L"UI_Button_Title_StartGame",L".png"); // 객체 테스트
	//종료버튼
	UIButton* exit = new UIButton(Vector2{ 70 + (200 / 2),472 + (50 / 2) }, e_exit, L"UI_Button_Title_GameOver", L".png");
	//조작
	UIButton* controll = new UIButton(Vector2{ 70 + (200 / 2),363 + (50 / 2) }, nullptr, L"UI_Button_Title_ToMove", L".png"); 

	//랭크보드
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

	//조작
	//UIButton* exit = new UIButton(Vector2{ 70 + (200 / 2),472 + (50 / 2) }, e_exit, exitBtn);

	//화면전환
	UICrossDissolve* backEffect = new UICrossDissolve({ 640.f, 360.f }, Game::GameManager::GetInstance()->sceneBitmap);

	//오브젝트 등록
	AddObject(myBack);
	AddObject(titleImg);
	AddObject(gameStartButton);
	AddObject(controll);
	AddObject(exit);
	AddObject(rankDialog);
	AddObject(backEffect);

	//이벤트 등록
	AddEvent(e_nextScn);
	AddEvent(e_exit);

	//화면 알파 값 초기화
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