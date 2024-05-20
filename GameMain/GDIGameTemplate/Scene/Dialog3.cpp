#include "IntroScene.h"
#include "../GameLogic/Objects/UIObject.h"
#include "../GameLogic/Event.h"
#include "../System/InputSystem.h"
#include "../GameLogic/Objects/KeyInput.h"
#include "../GameLogic/Objects/Fish.h"

Dialog3::Dialog3()
{

}

Dialog3::~Dialog3()
{

}

void Dialog3::Init()
{
	WCHAR* _str = new WCHAR[255];
	WCHAR t_str[] = L"꼬리가 밤하늘같아... 아빠, 저 애 잡아줄 수 있어?";
	wcscpy_s(_str, 255, t_str);
	UIDialog* dialog = new UIDialog();
	dialog->Init({ 100.f, 500.f }, { 1000.f, 700.f }, _str);

	CResourceManager* CRM = CResourceManager::GetInstance();
	myBitmap = CRM->LoadBitmapResouce(L"image1", L"startback.png");
	UIImage* myBack = new UIImage(); // 객체 테스트 
	myBack->Init(myBitmap, { 640.f,360.f });



	SelectScnEvent* e_NextScn = new SelectScnEvent((UINT)SceneType::STAGE_04);

	Gdiplus::Bitmap* daughterFace = CRM->LoadBitmapResouce(L"Face", L"FaceTest.png");
	UIFace* myFace = new UIFace(Vector2{ 400.f , 600.f }, daughterFace);

	KeyInput* myKey = new KeyInput();

	myKey->m_Event = e_NextScn;

	AddEvent(e_NextScn);

	AddObject(myBack);
	AddObject(myFace);
	AddObject(dialog);


	AddObject(myKey);

	Fish* myFish;
	myFish = new Fish(L"BossFish", 0, 0, L"BossFish_04_Anim_00.png", CRM, L".png", 0, 0, 0, 0, true);
	myFish->m_pos = Vector2{ 400 , 200 };
	myFish->setAngleDirection(Vector2{ 1,0 });
	myFish->ScaleX = 1.5f;
	myFish->ScaleY = 1.5f;
	AddObject(myFish);
}


void Dialog3::Start()
{
}


void Dialog3::Exit() {
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

