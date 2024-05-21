#include "IntroScene.h"
#include "../GameLogic/Objects/UIObject.h"
#include "../GameLogic/Event.h"
#include "../System/InputSystem.h"
#include "../GameLogic/Objects/KeyInput.h"
#include "../GameLogic/Objects/Fish.h"

IntroScene::IntroScene()
{

}

IntroScene::~IntroScene()
{

}

void IntroScene::Init()
{
	CResourceManager* CRM = CResourceManager::GetInstance();

	//배경
	myBitmap = CRM->LoadBitmapResouce(L"image1", L"startback.png");
	UIImage* myBack = new UIImage(); // 객체 테스트 
	myBack->Init(myBitmap, { 640.f,360.f });

	SelectScnEvent* e_NextScn = new SelectScnEvent((UINT)SceneType::STAGE_01);

	KeyInput* myKey = new KeyInput();
	myKey->Init(2.0f);
	myKey->m_Event = e_NextScn;

	//다이얼로그 배경 //1216*176
	Gdiplus::Bitmap* b_talkBarBox = CRM->LoadBitmapResouce(L"TalkBar_Box", L"UI_Image_Talk_TalkBar_01_Box.png");
	UIImage* talkBarBox = new UIImage(); // 객체 테스트 
	talkBarBox->Init(b_talkBarBox, { 32+(1216/2),512+(176/2)});

	//다이얼로그
	WCHAR _str[255];
	WCHAR t_str[] = L"이 애, 솜사탕같지 않아? 같이 많이 먹었잖아!";
	wcscpy_s(_str, 255, t_str);
	UIDialog* dialog = new UIDialog();
	dialog->Init({ 300, 560 }, { 600 , 200 }, _str);

	//스페이스바이미지 //99*30
	Gdiplus::Bitmap* b_talkBarSpace = CRM->LoadBitmapResouce(L"TalkBar_Space", L"UI_Image_Talk_TalkBar_01_SpaceBar.png");
	UIImage* talkBarSpace = new UIImage(); // 객체 테스트 
	talkBarSpace->Init(b_talkBarSpace, { 1100 + (99 / 2), 635 + (30 / 2) });

	//face //150/144
	Gdiplus::Bitmap* daughterFace1 = CRM->LoadBitmapResouce(L"TalkBarFace1", L"UI_Image_Talk_TalkBar_01_Portrait.png");
	/*Gdiplus::Bitmap* daughterFace2 = CRM->LoadBitmapResouce(L"Face2", L"UI_Image_Talk_CharaFace_Sad_01.png");
	Gdiplus::Bitmap* daughterFace3 = CRM->LoadBitmapResouce(L"Face3", L"UI_Image_Talk_CharaFace_Smile_01.png");
	Gdiplus::Bitmap* daughterFace4 = CRM->LoadBitmapResouce(L"Face4", L"UI_Image_Talk_CharaFace_Happy_01.png");*/
	UIFace* myFace = new UIFace(Vector2{ 130+(150/2),550+(144/2)}, daughterFace1, daughterFace1, daughterFace1, daughterFace1);

	//BossFish
	Fish* myFish;
	myFish = new Fish(L"BossFish", 0, 10, L"BossFish_00.png", CRM, L".png", 0, 0, 0, 0, true);
	myFish->m_pos = Vector2{ 400 , 200 };
	myFish->setAngleDirection(Vector2{ 1,0 });
	myFish->SetMoveDirection(Vector2{ -1,0 });
	myFish->ScaleX = 1.5f;
	myFish->ScaleY = 1.5f;


	AddEvent(e_NextScn);

	AddObject(myBack);
	AddObject(talkBarBox);
	AddObject(dialog);
	AddObject(talkBarSpace);
	AddObject(myFace);
	AddObject(myKey);
	AddObject(myFish);
}


void IntroScene::Start()
{
}


void IntroScene::Exit() {
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

