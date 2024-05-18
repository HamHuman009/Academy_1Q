#include "Ending.h"
#include "../GameLogic/Objects/UIObject.h"
#include "../GameLogic/Event.h"

void Ending::Init()
{
	WCHAR* _str = new WCHAR[255];
	WCHAR t_str[] = { 0 };

	switch (num)
	{
    case 1:
        wcscpy_s(_str, 255, L"첫 번째 문자열"); // num이 1일 때 문자열 할당
        break;
    case 2:
        wcscpy_s(_str, 255, L"두 번째 문자열"); // num이 2일 때 문자열 할당
        break;
    case 3:
        wcscpy_s(_str, 255, L"세 번째 문자열"); // num이 3일 때 문자열 할당
        break;
    default:
        wcscpy_s(_str, 255, L"기본 문자열"); // num이 1, 2, 3이 아닐 때 기본 문자열 할당
        break;
	}
	
    CResourceManager* CRM = CResourceManager::GetInstance();
    myBitmap = CRM->LoadBitmapResouce(L"image1", L"startback.bmp");
    UIImage* myBack = new UIImage(); // 객체 테스트 
    myBack->Init(myBitmap, { 640.f,360.f });

	UIDialog* dialog = new UIDialog();
	dialog->Init({ 100.f, 500.f }, { 1000.f, 700.f }, _str);
	AddObject(myBack);
    AddObject(dialog);
}

void Ending::Start()
{

}

void Ending::Exit()
{
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

Ending::Ending()
{
}

Ending::~Ending()
{
}


