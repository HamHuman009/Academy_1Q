#include "Ending.h"
#include "../GameLogic/Objects/UIObject.h"
#include "../GameLogic/Event.h"
#include "../GameLogic/Objects/KeyInput.h"

void Ending::Init()
{
	
	WCHAR t_str[] = { 0 };

	SelectScnEvent* e_NextScn1 = new SelectScnEvent((UINT)SceneType::Score);
	AddEvent(e_NextScn1);

	CResourceManager* CRM = CResourceManager::GetInstance();
	
	Score = Game::GameManager::GetInstance()->FinalScore;
	bossCount = Game::GameManager::GetInstance()->BossCount;
	/*Score = 29;
	bossCount = 5;*/
	if (Score <= 1 && bossCount <= 0)
	{
		root = static_cast<int>(EndRoot::Poor);
	}
	else if (Score <= 12 && bossCount <= 4)
	{
		root = static_cast<int>(EndRoot::Normal);
	}
	else if (Score <= 12 && bossCount >= 5)
	{
		root = static_cast<int>(EndRoot::Maniac);
	}
	else if (Score <= 28 && bossCount <= 2)
	{
		root = static_cast<int>(EndRoot::Great);
	}
	else if (Score <= 28 && bossCount >= 5)
	{
		root = static_cast<int>(EndRoot::Professional);
	}
	else if (Score >= 29 && bossCount >= 5)
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
		myBitmap = CRM->LoadBitmapResouce(L"Ending_Normal", L"ending_scene_normal.png");
		break;
	case 3:
		//wcscpy_s(_str, 255, L"매니악"); // num이 3일 때 문자열 할당
		myBitmap = CRM->LoadBitmapResouce(L"Ending_Manic", L"ending_scene_maniac.png");
		break;
	case 4:
		//wcscpy_s(_str, 255, L"우수"); // num이 4일 때 문자열 할당
		myBitmap = CRM->LoadBitmapResouce(L"Ending_Great", L"ending_scene_excellent.png");
		break;
	case 5:
		//wcscpy_s(_str, 255, L"프로"); // num이 5일 때 문자열 할당
		myBitmap = CRM->LoadBitmapResouce(L"Ending_Professional", L"ending_scene_pro_best1.png");
		break;
	case 6:
		//wcscpy_s(_str, 255, L"최고");
		backBitmap = CRM->LoadBitmapResouce(L"Ending_Professional", L"ending_scene_pro_best1.png");
		myBitmap = CRM->LoadBitmapResouce(L"Ending_Best_2", L"ending_scene_best2.png");
		break;
	}

	UIImage* myBack = new UIImage(); // 객체 테스트 
	myBack->Init(myBitmap, { 640.f,360.f });
	/*UIDialog* dialog = new UIDialog();
	dialog->Init({ 100.f, 500.f }, { 1000.f, 700.f }, _str);*/
	AddObject(myBack);
	//AddObject(dialog);

	SelectScnEvent* e_NextScn = new SelectScnEvent((UINT)SceneType::Score);
	AddEvent(e_NextScn);

	KeyInput* mykey = new KeyInput();
	mykey->Init(4.0f); //이거 없으면 키 연타하다가 바로 엔딩 씬으로 감..
	mykey->m_Event = e_NextScn;
	AddObject(mykey);

	UICrossDissolve* backEffect = new UICrossDissolve({ 640.f, 360.f }, backBitmap , 4.f, true);
	AddObject(backEffect);
}

void Ending::Start()
{
	mySound::SoundManager* meSound = mySound::SoundManager::GetInstance();
	meSound->StopMusic(mySound::eSoundChannel::BGM);
	meSound->PlayMusic(mySound::eSoundList::Ending_Theme/*s_ending*/, mySound::eSoundChannel::BGM);
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


