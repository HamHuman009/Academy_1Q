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
		std::cout << "d이벤트 소멸" << std::endl;
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
			mySound::SoundManager::GetInstance()->PlayMusic(m_Sound, mySound::eSoundChannel::Effect);
		}
		SelectScene(nextSceneNum);
	}

	void SelectScene(int i) {
		scnManager->SetCurScene(i);
	}
	~SelectScnEvent() {
		std::cout << "d이벤트 소멸dwadawdawd" << std::endl;
		m_Sound = mySound::eSoundList::Void;
	}
};

class PauseEvent : public Event
{
public:
	/*PauseEvent(mySound::eSoundList mSound) : Event(mSound) {

	}*/ //생성자 상속 예시
	UIImage* PauseBack;
	UIButton* Resume;
	UIButton* Retry;
	UIButton* Exit;

	void OnTrigger() override
	{	
		if (m_Sound != mySound::eSoundList::Void) {
			mySound::SoundManager::GetInstance()->PlayMusic(m_Sound, mySound::eSoundChannel::Effect);
		}
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
	ResumeEvent() : Event() {};

	ResumeEvent(mySound::eSoundList mSound) : Event(mSound) {

	}

	UIImage* PauseBack;
	UIButton* Resume;
	UIButton* Retry;
	UIButton* Exit;

	void OnTrigger() override
	{	
		if (m_Sound != mySound::eSoundList::Void) {
			mySound::SoundManager::GetInstance()->PlayMusic(m_Sound, mySound::eSoundChannel::Effect);
		}
		PauseBack->m_isActive = false;
		Resume->m_isActive = false;
		Retry->m_isActive = false;
		Exit->m_isActive = false;
		High_Resolution_Time::SetTimeScale(1.f);
	}
};

class RetryEvent : public Event
{

private:
	SceneManager* scnManager = SceneManager::GetInstance();
	Game::GameManager* gameManager = Game::GameManager::GetInstance();

public:
	RetryEvent() : Event() {};

	RetryEvent(mySound::eSoundList mSound) : Event(mSound) {

	}

	void OnTrigger() override
	{	
		if (m_Sound != mySound::eSoundList::Void) {
			mySound::SoundManager::GetInstance()->PlayMusic(m_Sound, mySound::eSoundChannel::Effect);
		}
		scnManager->SetCurScene(1);
		High_Resolution_Time::SetTimeScale(1.f);
	}
};

class ExitEvent : public Event
{	
public:
	ExitEvent() : Event() {};

	ExitEvent(mySound::eSoundList mSound) : Event(mSound) {

	}

	void OnTrigger() override
	{	
		if (m_Sound != mySound::eSoundList::Void) {
			mySound::SoundManager::GetInstance()->PlayMusic(m_Sound, mySound::eSoundChannel::Effect);
		}
		/*Game::GameManager::GetInstance()->Finalize();
		Game::GameManager::GetInstance()->ReleaseResource();
		Game::GameManager::GetInstance()->DestroyInstance();*/
		//_CrtDumpMemoryLeaks();*/
		PostQuitMessage(0);
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

class FeedbackEvent : public Event {
public:
	UISpeech* feedbackObject;
	int feedbackNumber;

	FeedbackEvent(UISpeech* speech, int number) {
		feedbackObject = speech;
		feedbackNumber = number;
	}
	void OnTrigger() override {
		if(feedbackObject != nullptr)
			feedbackObject->AddFeedback(feedbackNumber);
	}
};


class SwapObjectEvent : public Event {
public:
	std::vector<Object*>* swapObject;
	Object* swap1;
	Object* swap2;

	SwapObjectEvent(Object* _swap1, Object* _swap2, std::vector<Object*>& swap) {
		swap1 = _swap1;
		swap2 = _swap2;
		swapObject = &swap;
	}
	void OnTrigger() override {
		auto it_a = std::find(swapObject->begin(), swapObject->end(), swap1);
		auto it_b = std::find(swapObject->begin(), swapObject->end(), swap2);
		std::swap(*it_a, *it_b);
	}
};

class HowToEvent : public Event {
public:
	UIImage* howToImg;

	void OnTrigger() override
	{
		howToImg->m_isActive = true;
	}
};