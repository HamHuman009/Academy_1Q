#pragma once
#include "../Manager/SceneManager.h"
#include "../Manager/GameManager.h"
#include "../Scene/CScene.h"
#include "../System/TimeSystem.h"
#include "../System/SoundSystem.h"

class Event {
protected:
	mySound::SoundManager* m_SoundManager = nullptr;
	mySound::eSoundList m_Sound = mySound::eSoundList::Void;

public:
	virtual void Init() {};
	virtual void OnTrigger() = 0;
	Event() { 
		m_SoundManager = mySound::SoundManager::GetInstance();
		m_Sound = mySound::eSoundList::Void;
	}
	Event(mySound::eSoundList mSound) { 
		m_SoundManager = mySound::SoundManager::GetInstance();
		m_Sound = mSound;
	}
	virtual ~Event() { 
		std::cout << "d�̺�Ʈ �Ҹ�" << std::endl; 
	}

};

class SelectScnEvent : public Event {
private:
	SceneManager* scnManager;
	Game::GameManager* gameManager;
	int nextSceneNum;

public:
	/*SelectScnEvent() {
		Init();
	}*/

	SelectScnEvent(int sceneNum) {
		scnManager = SceneManager::GetInstance();
		gameManager = Game::GameManager::GetInstance();
		m_SoundManager = mySound::SoundManager::GetInstance();
		nextSceneNum = sceneNum;
		m_Sound = mySound::eSoundList::Void;
	}

	SelectScnEvent(int sceneNum, mySound::eSoundList mSound) {
		scnManager = SceneManager::GetInstance();
		gameManager = Game::GameManager::GetInstance();
		m_SoundManager = mySound::SoundManager::GetInstance();
		nextSceneNum = sceneNum;
		m_Sound = mSound;
	}

	/*void Init() override {
		scnManager = SceneManager::GetInstance();
		
		
	}*/

	void OnTrigger() override {
		
		if (m_Sound != mySound::eSoundList::Void) {
			mySound::SoundManager::GetInstance()->PlayMusic(m_Sound,mySound::eSoundChannel::Effect);
		}
		SelectScene(nextSceneNum);
	}

	void SelectScene(int i) {
		scnManager->SetCurScene(i);
	}
	~SelectScnEvent() {
		std::cout << "d�̺�Ʈ �Ҹ�dwadawdawd" << std::endl;
		//m_Sound = mySound::eSoundList::Void;
	}
};

class PauseEvent : public Event
{
public:

	UIImage* PauseBack;
	UIButton* Resume;
	UIButton* Retry;
	UIButton* Exit;
	
	void OnTrigger() override
	{
		PauseBack->m_isActive = true;
		Resume->m_isActive = true;
		Retry->m_isActive = true;
		Exit->m_isActive = true;
		High_Resolution_Time::SetTimeScale(0.f);
	}

};

class ResumeEvent : public Event
{	
public:
	UIImage* PauseBack;
	UIButton* Resume;
	UIButton* Retry;
	UIButton* Exit;

	void OnTrigger() override
	{
		PauseBack->m_isActive = false;
		Resume->m_isActive = false;
		Retry->m_isActive = false;
		Exit->m_isActive = false;
		High_Resolution_Time::SetTimeScale(1.f);
	}
};

class RetryEvent : public Event
{
	// retry ��ư�� �������� �׳� ��ó�� �ʱ�ȭ������ ���ư��Բ�
	// + �ð��ʰ� �ٵǸ� retry �̺�Ʈ�� �ڵ����� ����ǰԲ�

private:
	SceneManager* scnManager = SceneManager::GetInstance();
	Game::GameManager* gameManager = Game::GameManager::GetInstance();

public:

	void OnTrigger() override
	{	
		scnManager->SetCurScene(1);
		High_Resolution_Time::SetTimeScale(1.f);
	}
};

class ExitEvent : public Event
{
	void OnTrigger() override
	{	
		Game::GameManager::GetInstance()->Finalize();
		Game::GameManager::GetInstance()->ReleaseResource();
		Game::GameManager::GetInstance()->DestroyInstance();
		_CrtDumpMemoryLeaks();
		PostQuitMessage(1);
	}
};

class Discription : public Event
{
public:
	UIButton* Close;
	UIButton* Resume;

	void OnTrigger() override
	{	
		Close->m_isActive = true;
		Resume->m_isActive = true;
		High_Resolution_Time::SetTimeScale(0.f);
	}
};