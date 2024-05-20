#include "IntroScene.h"
#include "../GameLogic/Objects/UIObject.h"
#include "../GameLogic/Event.h"
#include "../System/InputSystem.h"
#include "../GameLogic/Objects/KeyInput.h"

Dialog1::Dialog1()
{

}

Dialog1::~Dialog1()
{

}

void Dialog1::Init()
{
	WCHAR* _str = new WCHAR[255];
	WCHAR t_str[] = L"물고기에 대한 설명 + 스토리 가나다라마다사아자차카타파하 물고기에 대한 설명 + 스토리 가나다라마다사아자차카타파하 물고기에 대한 설명 + 스토리 가나다라마다사아자차카타파하 물고기에 대한 설명 + 스토리 가나다라마다사아자차카타파하 물고기에 대한 설명 + 스토리 가나다라마다사아자차카타파하 물고기에 대한 설명 + 스토리 가나다라마다사아자차카타파하 물고기에 대한 설명 + 스토리 가나다라마다사아자차카타파하";
	wcscpy_s(_str, 255, t_str);
	UIDialog* dialog = new UIDialog();
	dialog->Init({ 100.f, 500.f }, { 1000.f, 700.f }, _str);

	CResourceManager* CRM = CResourceManager::GetInstance();
	myBitmap = CRM->LoadBitmapResouce(L"image1", L"startback.png");
	UIImage* myBack = new UIImage(); // 객체 테스트 
	myBack->Init(myBitmap, { 640.f,360.f });



	SelectScnEvent* e_NextScn = new SelectScnEvent((UINT)SceneType::STAGE_02);

	Gdiplus::Bitmap* daughterFace = CRM->LoadBitmapResouce(L"Face", L"FaceTest.png");
	UIFace* myFace = new UIFace(Vector2{ 400.f , 600.f }, daughterFace);

	KeyInput* myKey = new KeyInput();

	myKey->m_Event = e_NextScn;

	AddEvent(e_NextScn);

	AddObject(myBack);
	AddObject(myFace);
	AddObject(dialog);


	AddObject(myKey);
}


void Dialog1::Start()
{
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

