#include "Ending.h"
#include "../GameLogic/Objects/UIObject.h"
#include "../GameLogic/Event.h"
#include "../GameLogic/Objects/KeyInput.h"

void Ending::Init()
{
	WCHAR* _str = new WCHAR[255];
	WCHAR t_str[] = { 0 };

	SelectScnEvent* e_NextScn1 = new SelectScnEvent((UINT)SceneType::Score);
	AddEvent(e_NextScn1);

	CResourceManager* CRM = CResourceManager::GetInstance();
	g_Score = 50;
	g_BossCnt = 5;
	if (g_Score <= 1 && g_BossCnt <= 0)
	{
		root = static_cast<int>(EndRoot::Poor);
	}
	else if (g_Score <= 12 && g_BossCnt <= 4)
	{
		root = static_cast<int>(EndRoot::Normal);
	}
	else if (g_Score <= 12 && g_BossCnt >= 5)
	{
		root = static_cast<int>(EndRoot::Maniac);
	}
	else if (g_Score <= 28 && g_BossCnt <= 4)
	{
		root = static_cast<int>(EndRoot::Great);
	}
	else if (g_Score <= 28 && g_BossCnt >= 5)
	{
		root = static_cast<int>(EndRoot::Professional);
	}
	else if (g_Score >= 50 && g_BossCnt >= 5)
	{
		root = static_cast<int>(EndRoot::Best);
	}

	// 최고엔딩은 따로 뺄것 (비트맵 2개)
	switch (root)
	{
	case 1:
		
		e_NextScn1->OnTrigger();
		break;
	case 2:
		//wcscpy_s(_str, 255, L"노말"); // num이 2일 때 문자열 할당
		myBitmap = CRM->LoadBitmapResouce(L"image2", L"startback2.png");
		break;
	case 3:
		//wcscpy_s(_str, 255, L"매니악"); // num이 3일 때 문자열 할당
		myBitmap = CRM->LoadBitmapResouce(L"image3", L"startback3.png");
		break;
	case 4:
		//wcscpy_s(_str, 255, L"우수"); // num이 4일 때 문자열 할당
		myBitmap = CRM->LoadBitmapResouce(L"image4", L"startback4.png");
		break;
	case 5:
		//wcscpy_s(_str, 255, L"프로"); // num이 5일 때 문자열 할당
		myBitmap = CRM->LoadBitmapResouce(L"image5", L"startback5.png");
		break;
	case 6:
		//wcscpy_s(_str, 255, L"최고");
		backBitmap = CRM->LoadBitmapResouce(L"image6", L"startback6.png");
		myBitmap = CRM->LoadBitmapResouce(L"image7", L"startback7.png");
		break;
	}

	UIImage* myBack = new UIImage(); // 객체 테스트 
	myBack->Init(myBitmap, { 640.f,360.f });
	UIDialog* dialog = new UIDialog();
	dialog->Init({ 100.f, 500.f }, { 1000.f, 700.f }, _str);
	AddObject(myBack);
	AddObject(dialog);

	SelectScnEvent* e_NextScn = new SelectScnEvent((UINT)SceneType::Score);
	AddEvent(e_NextScn);

	KeyInput* mykey = new KeyInput();
	mykey->m_Event = e_NextScn;
	AddObject(mykey);

	UICrossDissolve* backEffect = new UICrossDissolve({ 640.f, 360.f }, backBitmap , 1.f, true);
	AddObject(backEffect);
}

void Ending::Start()
{

}

void Ending::Exit()
{
	Game::GameManager::GetInstance()->SetRoot(root);

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

int Ending::getRoot()
{
	return root;
}

Ending::Ending()
{
}

Ending::~Ending()
{
}


