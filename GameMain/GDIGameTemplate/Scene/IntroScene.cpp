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
	Game::GameManager::GetInstance()->OffCameraShaker();

	// dialog1로 옮겨져서 사용 X
	UIIntroBack* myBack = new UIIntroBack();
	CResourceManager* CRM = CResourceManager::GetInstance();
	myBack->Init(L"opening_scene_00.png", CRM);
	SelectScnEvent* e_nextScn = new SelectScnEvent((int)SceneType::Dialog1);
	myBack->m_Event = e_nextScn;

	//게임 방법 돌아오기 이미지
	Gdiplus::Bitmap* b_talkBarSpace = CRM->LoadBitmapResouce(L"TalkBar_Space", L"UI_Image_Talk_TalkBar_01_SpaceBar.png");
	UIImage* talkBarSpace = new UIImage();
	talkBarSpace->Init(b_talkBarSpace, { 1100 + (99 / 2), 635 + (30 / 2) });

	AddObject(myBack);
	AddEvent(e_nextScn);
	AddObject(talkBarSpace);
	
	
}


void IntroScene::Start()
{
	mySound::SoundManager* meSound = mySound::SoundManager::GetInstance();
	meSound->StopMusic(mySound::eSoundChannel::BGM);
	meSound->PlayMusic(mySound::eSoundList::Intro_Theme/*s_ending*/, mySound::eSoundChannel::BGM);

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

