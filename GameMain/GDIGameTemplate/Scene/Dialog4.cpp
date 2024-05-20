#include "IntroScene.h"
#include "../GameLogic/Objects/UIObject.h"
#include "../GameLogic/Event.h"
#include "../System/InputSystem.h"
#include "../GameLogic/Objects/KeyInput.h"
#include "../GameLogic/Objects/Fish.h"

Dialog4::Dialog4()
{

}

Dialog4::~Dialog4()
{

}

void Dialog4::Init()
{
	WCHAR* _str = new WCHAR[255];
	WCHAR t_str[] = L"아빠! 저 애는 진짜 정말 꼭! 잡아줘. 꼭이야!";
	wcscpy_s(_str, 255, t_str);
	UIDialog* dialog = new UIDialog();
	dialog->Init({ 100.f, 500.f }, { 1000.f, 700.f }, _str);

	CResourceManager* CRM = CResourceManager::GetInstance();
	myBitmap = CRM->LoadBitmapResouce(L"image1", L"startback.png");
	UIImage* myBack = new UIImage(); // 객체 테스트 
	myBack->Init(myBitmap, { 640.f,360.f });



	SelectScnEvent* e_NextScn = new SelectScnEvent((UINT)SceneType::STAGE_05);

	Gdiplus::Bitmap* daughterFace1 = CRM->LoadBitmapResouce(L"Face1", L"UI_Image_Talk_CharaFace_Normal_01.png");
	Gdiplus::Bitmap* daughterFace2 = CRM->LoadBitmapResouce(L"Face2", L"UI_Image_Talk_CharaFace_Sad_01.png");
	Gdiplus::Bitmap* daughterFace3 = CRM->LoadBitmapResouce(L"Face3", L"UI_Image_Talk_CharaFace_Smile_01.png");
	Gdiplus::Bitmap* daughterFace4 = CRM->LoadBitmapResouce(L"Face4", L"UI_Image_Talk_CharaFace_Happy_01.png");
	UIFace* myFace = new UIFace(Vector2{ 1200,300 }, daughterFace1, daughterFace2, daughterFace3, daughterFace4);

	KeyInput* myKey = new KeyInput();

	myKey->m_Event = e_NextScn;

	AddEvent(e_NextScn);

	AddObject(myBack);
	AddObject(myFace);
	AddObject(dialog);


	AddObject(myKey);

	Fish* myFish;
	myFish = new Fish(L"BossFish", 0, 0, L"BossFish_05_Anim_00.png", CRM, L".png", 0, 0, 0, 0, true);
	myFish->m_pos = Vector2{ 400 , 200 };
	myFish->setAngleDirection(Vector2{ 1,0 });
	myFish->ScaleX = 1.5f;
	myFish->ScaleY = 1.5f;
	AddObject(myFish);
}


void Dialog4::Start()
{
}


void Dialog4::Exit() {
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

