#include "IntroScene.h"
#include "../GameLogic/Objects/UIObject.h"
#include "../GameLogic/Event.h"
#include "../System/InputSystem.h"
#include "../GameLogic/Objects/KeyInput.h"
#include "../GameLogic/Objects/Fish.h"

Dialog1::Dialog1()
{

}

Dialog1::~Dialog1()
{

}

void Dialog1::Init()
{
	CResourceManager* CRM = CResourceManager::GetInstance();

	Gdiplus::Bitmap* b_talkBarBox = CRM->LoadBitmapResouce(L"TalkBar_Box", L"UI_Image_Talk_TalkBar_01_Box.png");
	UIImage* talkBarBox = new UIImage(); // ��ü �׽�Ʈ 
	talkBarBox->Init(b_talkBarBox, { 32 + (1216 / 2),512 + (176 / 2) });

	Gdiplus::Bitmap* b_talkBarSpace = CRM->LoadBitmapResouce(L"TalkBar_Space", L"UI_Image_Talk_TalkBar_01_SpaceBar.png");
	UIImage* talkBarSpace = new UIImage(); // ��ü �׽�Ʈ 
	talkBarSpace->Init(b_talkBarSpace, { 1100 + (99 / 2), 635 + (30 / 2) });

	//WCHAR* _str = new WCHAR[255]; 메모리 릭 발생!!
	WCHAR _str[255];
	WCHAR t_str[] = L"이 애, 솜사탕같지 않아? 같이 많이 먹었잖아!";
	wcscpy_s(_str, 255, t_str);
	UIDialog* dialog = new UIDialog();
	dialog->Init({ 230.f, 590.f }, { 600.f, 200.f }, _str);

	 
	myBitmap = CRM->LoadBitmapResouce(L"Dialog3", L"White_Dim.png");
	UIImage* myBack = new UIImage(); // 객체 테스트 
	myBack->Init(myBitmap, { 600.f, 300.f });

	SelectScnEvent* e_NextScn = new SelectScnEvent((UINT)SceneType::STAGE_01);

	Gdiplus::Bitmap* daughterFace1 = CRM->LoadBitmapResouce(L"TalkBarFace1", L"UI_Image_Talk_TalkBar_01_Portrait.png");
	/*Gdiplus::Bitmap* daughterFace2 = CRM->LoadBitmapResouce(L"TalkBarFace2", L"UI_Image_Talk_CharaFace_Sad_01.png");
	Gdiplus::Bitmap* daughterFace3 = CRM->LoadBitmapResouce(L"TalkBarFace3", L"UI_Image_Talk_CharaFace_Smile_01.png");
	Gdiplus::Bitmap* daughterFace4 = CRM->LoadBitmapResouce(L"TalkBarFace4", L"UI_Image_Talk_CharaFace_Happy_01.png");*/
	UIFace* myFace = new UIFace(Vector2{ 130 + (150 / 2),550 + (144 / 2) }, daughterFace1, daughterFace1, daughterFace1, daughterFace1);

	bool keys[256];
	for (int i = 0; i < 256; i++) {
		keys[i] = false;
	}
	keys[unsigned int(' ')] = true;
	KeyInput* myKey = new KeyInput(keys);
	myKey->Init(2.0f);
	myKey->m_Event = e_NextScn;

	DialogMessageEvent* e_dialogEvent = new DialogMessageEvent(L"그래서... 물고기를 잡고 싶다고?",
		nullptr,
		myFace,
		myKey,
		dialog,
		-1,
		1000.f
	);
	/*
	DialogMessageEvent* e_dialogEvent = new DialogMessageEvent(L"응! 응!",
		nullptr,
		myFace,
		myKey,
		dialog,
		-1,
		1000.f
	);
	DialogMessageEvent* e_dialogEvent = new DialogMessageEvent(L"그래서... 물고기를 잡고 싶다고?",
		nullptr,
		myFace,
		myKey,
		dialog,
		-1,
		1000.f
	);
	DialogMessageEvent* e_dialogEvent = new DialogMessageEvent(L"그래서... 물고기를 잡고 싶다고?",
		nullptr,
		myFace,
		myKey,
		dialog,
		-1,
		1000.f
	);
	DialogMessageEvent* e_dialogEvent = new DialogMessageEvent(L"그래서... 물고기를 잡고 싶다고?",
		nullptr,
		myFace,
		myKey,
		dialog,
		-1,
		1000.f
	);*/


	AddEvent(e_NextScn);

	AddObject(myBack);
	AddObject(talkBarBox);
	AddObject(dialog);
	AddObject(talkBarSpace);

	AddObject(myFace);

	AddObject(myKey);

	Fish* myFish;
	myFish = new Fish(L"DialogBossFish", 0, 10, L"BossFish_Only00.png", CRM, L".png", 0, 0, 0, 0, true);
	//myFish->m_pos = Vector2{ 480 , 420 };
	myFish->m_pos = Vector2{ 600.f,300.f };
	myFish->setAngleDirection(Vector2{ 1,0 });
	myFish->SetMoveDirection(Vector2{ -1,0 });
	/*myFish->ScaleX = 3.f;
	myFish->ScaleY = 3.f;*/
	AddObject(myFish);
}


void Dialog1::Start()
{
	mySound::SoundManager* meSound = mySound::SoundManager::GetInstance();
	meSound->StopMusic(mySound::eSoundChannel::BGM);
	meSound->PlayMusic(mySound::eSoundList::Talk_Theme/*s_ending*/, mySound::eSoundChannel::BGM);
}


void Dialog1::Exit() {
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

