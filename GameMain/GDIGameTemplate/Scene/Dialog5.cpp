#include "Dialog5.h"
#include "../GameLogic/Objects/UIObject.h"
#include "../GameLogic/Event.h"
#include "../System/InputSystem.h"
#include "../GameLogic/Objects/KeyInput.h"
#include "../GameLogic/Objects/Fish.h"

Dialog5::Dialog5()
{

}

Dialog5::~Dialog5()
{

}

void Dialog5::Init()
{
	CResourceManager* CRM = CResourceManager::GetInstance();

	Gdiplus::Bitmap* b_talkBarBox = CRM->LoadBitmapResouce(L"TalkBar_Box", L"UI_Image_Talk_TalkBar_01_Box.png");
	UIImage* talkBarBox = new UIImage(); // ��ü �׽�Ʈ 
	talkBarBox->Init(b_talkBarBox, { 32 + (1216 / 2),512 + (176 / 2) });

	Gdiplus::Bitmap* b_talkBarSpace = CRM->LoadBitmapResouce(L"TalkBar_Space", L"UI_Image_Talk_TalkBar_01_SpaceBar.png");
	UIImage* talkBarSpace = new UIImage(); // ��ü �׽�Ʈ 
	talkBarSpace->Init(b_talkBarSpace, { 1100 + (99 / 2), 635 + (30 / 2) });

	//WCHAR* _str = new WCHAR[255]; 메모리 발생!!
	WCHAR _str[255];
	WCHAR t_str[] = L"아빠! 저 애는 진짜 정말 꼭! 잡아줘. 꼭이야!";
	wcscpy_s(_str, 255, t_str);
	UIDialog* dialog = new UIDialog();
	dialog->Init({ 230.f, 590.f }, { 800.f, 200.f }, _str);

	myBitmap = CRM->LoadBitmapResouce(L"Dialog3", L"White_Dim.png");
	UIImage* myBack = new UIImage(); // 객체 테스트 
	myBack->Init(myBitmap, { 600.f, 300.f });

	SelectScnEvent* e_NextScn = new SelectScnEvent((UINT)SceneType::STAGE_05);

	Gdiplus::Bitmap* daughterFace1 = CRM->LoadBitmapResouce(L"TalkBarFace1", L"UI_Image_Talk_TalkBar_01_Portrait_Default.png");
	Gdiplus::Bitmap* daughterFace2 = CRM->LoadBitmapResouce(L"TalkBarFace2", L"UI_Image_Talk_TalkBar_01_Portrait_Sad.png");
	Gdiplus::Bitmap* daughterFace3 = CRM->LoadBitmapResouce(L"TalkBarFace3", L"UI_Image_Talk_TalkBar_01_Portrait_Smile.png");
	Gdiplus::Bitmap* daughterFace4 = CRM->LoadBitmapResouce(L"TalkBarFace4", L"UI_Image_Talk_TalkBar_01_Portrait_Happy.png");
	UIFace* myFace = new UIFace(Vector2{ 130 + (150 / 2),550 + (144 / 2) }, daughterFace1, daughterFace2, daughterFace3, daughterFace4);

	bool keys[256];
	for (int i = 0; i < 256; i++) {
		keys[i] = false;
	}
	keys[unsigned int(' ')] = true;
	KeyInput* myKey = new KeyInput(keys);
	myKey->Init(.5f);

	DialogMessageEvent* e_dialogEvent1 = new DialogMessageEvent(L"아빠! 저 물고기 엄마 처럼 예쁘지 않아요?",
		myFace, myKey, dialog, 3, 1000.f);
	myKey->m_Event = e_dialogEvent1;
	DialogMessageEvent* e_dialogEvent2 = new DialogMessageEvent(L"그래 이쁜 물고기네.",
		myFace, myKey, dialog, -1, 1000.f);
	DialogMessageEvent* e_dialogEvent3 = new DialogMessageEvent(L"마지막으로 저 애만 잡으면 안돼요?",
		myFace, myKey, dialog, 1, 1000.f);
	DialogMessageEvent* e_dialogEvent4 = new DialogMessageEvent(L"그래, 아빠가 마지막으로 힘을 내볼게.",
		myFace, myKey, dialog, -1, 1000.f);

	e_dialogEvent1->nextEvent = e_dialogEvent2;
	e_dialogEvent2->nextEvent = e_dialogEvent3;
	e_dialogEvent3->nextEvent = e_dialogEvent4;
	e_dialogEvent4->nextEvent = e_NextScn;
	e_dialogEvent1->OnTrigger();

	AddEvent(e_dialogEvent1);
	AddEvent(e_dialogEvent2);
	AddEvent(e_dialogEvent3);
	AddEvent(e_dialogEvent4);

	AddEvent(e_NextScn);

	AddObject(myBack);
	AddObject(talkBarBox);
	AddObject(dialog);
	AddObject(talkBarSpace);

	AddObject(myFace);

	AddObject(myKey);

	Fish* myFish;
	myFish = new Fish(L"DialogBossFish5", 0, 10, L"BossFish_05_Upscale_00.png", CRM, L".png", 0, 0, 0, 0, true);
	myFish->m_pos = Vector2{ 600.f,300.f };
	myFish->setAngleDirection(Vector2{ 1,0 });
	myFish->SetMoveDirection(Vector2{ -1,0 });
	/*myFish->ScaleX = 3.f;
	myFish->ScaleY = 3.f;*/
	AddObject(myFish);
}


void Dialog5::Start()
{
	mySound::SoundManager* meSound = mySound::SoundManager::GetInstance();
	meSound->StopMusic(mySound::eSoundChannel::BGM);
	meSound->PlayMusic(mySound::eSoundList::Talk_Theme/*s_ending*/, mySound::eSoundChannel::BGM);
}


void Dialog5::Exit() {
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

