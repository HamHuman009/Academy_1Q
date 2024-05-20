#include "Ending.h"
#include "../GameLogic/Objects/UIObject.h"
#include "../GameLogic/Event.h"
#include "../GameLogic/Objects/KeyInput.h"

void Ending::Init()
{
	WCHAR* _str = new WCHAR[255];
	WCHAR t_str[] = { 0 };
	g_Score = 41;
	g_BossCnt = 5;
	CResourceManager* CRM = CResourceManager::GetInstance();

	if (g_Score <= -1 && g_BossCnt <= 0)
	{
		num = static_cast<int>(EndRoot::Poor);
	}
	else if (g_Score < 40 && g_BossCnt < 3)
	{
		num = static_cast<int>(EndRoot::Normal);
	}
	else if (g_Score < 40 && g_BossCnt >= 5)
	{
		num = static_cast<int>(EndRoot::Maniac);
	}
	else if (g_Score >= 40 && g_BossCnt < 3)
	{
		num = static_cast<int>(EndRoot::Great);
	}
	else if (g_Score >= 40 && g_BossCnt >= 5)
	{
		num = static_cast<int>(EndRoot::Professional);
	}

	// �ְ����� ���� ���� (��Ʈ�� 2��)
	switch (num)
	{
    case 1:
        wcscpy_s(_str, 255, L"����"); // num�� 1�� �� ���ڿ� �Ҵ�
		myBitmap = CRM->LoadBitmapResouce(L"image1", L"startback.png");
        break;
    case 2:
        wcscpy_s(_str, 255, L"�븻"); // num�� 2�� �� ���ڿ� �Ҵ�
		myBitmap = CRM->LoadBitmapResouce(L"image2", L"startback2.png");
        break;
    case 3:
        wcscpy_s(_str, 255, L"�ŴϾ�"); // num�� 3�� �� ���ڿ� �Ҵ�
		myBitmap = CRM->LoadBitmapResouce(L"image3", L"startback3.png");
        break;
	case 4:
		wcscpy_s(_str, 255, L"���"); // num�� 4�� �� ���ڿ� �Ҵ�
		myBitmap = CRM->LoadBitmapResouce(L"image4", L"startback4.png");
		break;
	case 5:
		wcscpy_s(_str, 255, L"����"); // num�� 5�� �� ���ڿ� �Ҵ�
		myBitmap = CRM->LoadBitmapResouce(L"image5", L"startback5.png");
		break;
	}
	
   
	UIImage* myBack = new UIImage(); // ��ü �׽�Ʈ 
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


