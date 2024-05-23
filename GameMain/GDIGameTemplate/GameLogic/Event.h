#pragma once
#include <cstdio>
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
	PauseEvent(mySound::eSoundList mSound) : Event(mSound) {

	} //생성자 상속 예시
	UIImage* PauseBack;
	UIButton* Resume;
	UIButton* Retry;
	UIButton* Exit;
	UIButton* B_Inc;
	UIButton* B_Dec;
	UIButton* E_Inc;
	UIButton* E_Dec;
	UIVolume* E_Volume;

	void OnTrigger() override
	{	
		if (m_Sound != mySound::eSoundList::Void) {
			mySound::SoundManager::GetInstance()->PlayMusic(m_Sound, mySound::eSoundChannel::Effect);
		}
		PauseBack->m_isActive = true;
		Resume->m_isActive = true;
		Retry->m_isActive = true;
		Exit->m_isActive = true;
		B_Inc->m_isActive = true;
		B_Dec->m_isActive = true;
		E_Inc->m_isActive = true;
		E_Dec->m_isActive = true;
		E_Volume->m_isActive = true;
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
	UIButton* B_Inc;
	UIButton* B_Dec;
	UIButton* E_Inc;
	UIButton* E_Dec;
	UIVolume* E_Volume;

	void OnTrigger() override
	{	
		if (m_Sound != mySound::eSoundList::Void) {
			mySound::SoundManager::GetInstance()->PlayMusic(m_Sound, mySound::eSoundChannel::Effect);
		}
		PauseBack->m_isActive = false;
		Resume->m_isActive = false;
		Retry->m_isActive = false;
		Exit->m_isActive = false;
		B_Inc->m_isActive = false;
		B_Dec->m_isActive = false;
		E_Inc->m_isActive = false;
		E_Dec->m_isActive = false;
		E_Volume->m_isActive = false;
		High_Resolution_Time::SetTimeScale(1.f);
		High_Resolution_Time::SetTimeScale2(1.f);
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
		High_Resolution_Time::SetTimeScale2(1.f);
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
	Speechenum feedbackNumber;

	FeedbackEvent(UISpeech* speech, Speechenum number) {
		feedbackObject = speech;
		feedbackNumber = number;
	}
	void OnTrigger() override {
		if (feedbackObject != nullptr)
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

	HowToEvent(mySound::eSoundList mySound) {
		m_Sound = mySound;
	}

	void OnTrigger() override
	{	
		if (m_Sound != mySound::eSoundList::Void) {
			mySound::SoundManager::GetInstance()->PlayMusic(m_Sound, mySound::eSoundChannel::Effect);
		}
		if (howToImg->m_isActive == true) howToImg->m_isActive = false;
		else howToImg->m_isActive = true;

	}
};

class EndgameEvent : public Event {
public:
	Player* player;

	EndgameEvent(Player* _player) {
		player = _player;
	}
	void OnTrigger() override {
		player->gameOver = true;
	}
};

class CatchBossEvent : public Event {
public:
	In_ScoreBoard* scoreBoard;
	CatchBossEvent(In_ScoreBoard* _scoreBoard) {
		scoreBoard = _scoreBoard;
	}
	void OnTrigger() override {
		scoreBoard->SwapBitmap();
		m_SoundManager->PlayMusic(mySound::eSoundList::Boss_Fish_Catch, mySound::eSoundChannel::Effect2);
	}
};


class BGSound_Plus : public Event
{
public:	
	void OnTrigger() override
	{
		if (Game::GameManager::GetInstance()->mVolume <= 1.f)
		{
			m_SoundManager->SetVolume(Game::GameManager::GetInstance()->mVolume += 0.1f, (int)mySound::eSoundChannel::BGM);
		}
	}
};

class BGSound_Minus : public Event
{
public:
	void OnTrigger() override
	{
		if (Game::GameManager::GetInstance()->mVolume > 0.1f)
		{
			m_SoundManager->SetVolume(Game::GameManager::GetInstance()->mVolume -= 0.1f, (int)mySound::eSoundChannel::BGM);
		}
	}
};

class EffectSound_Plus : public Event
{
public:
	void OnTrigger() override
	{	
		if (Game::GameManager::GetInstance()->effectVolume <= 1.f)
		{
			m_SoundManager->SetVolume(Game::GameManager::GetInstance()->effectVolume += 0.1f, (int)mySound::eSoundChannel::Effect);
			m_SoundManager->SetVolume(Game::GameManager::GetInstance()->effectVolume += 0.1f, (int)mySound::eSoundChannel::Effect2);
			m_SoundManager->SetVolume(Game::GameManager::GetInstance()->effectVolume += 0.1f, (int)mySound::eSoundChannel::Effect3);
			m_SoundManager->SetVolume(Game::GameManager::GetInstance()->effectVolume += 0.1f, (int)mySound::eSoundChannel::Voice);
		}
	}
};

class EffectSound_Minus : public Event
{
public:

	void OnTrigger() override
	{
		if (Game::GameManager::GetInstance()->effectVolume > 0.1f)
		{
			m_SoundManager->SetVolume(Game::GameManager::GetInstance()->effectVolume -= 0.1f, (int)mySound::eSoundChannel::Effect);
			m_SoundManager->SetVolume(Game::GameManager::GetInstance()->effectVolume -= 0.1f, (int)mySound::eSoundChannel::Effect2);
			m_SoundManager->SetVolume(Game::GameManager::GetInstance()->effectVolume -= 0.1f, (int)mySound::eSoundChannel::Effect3);
			m_SoundManager->SetVolume(Game::GameManager::GetInstance()->effectVolume -= 0.1f, (int)mySound::eSoundChannel::Voice);
		}
	}
};

class ButtonOnTriggerAndActiveFalseEvent : public Event {
public:
	UIButton* button;
	UIInputField* objectTrigger;
	ButtonOnTriggerAndActiveFalseEvent(UIButton* _button, UIInputField* _objectTrigger) {
		button = _button;
		objectTrigger = _objectTrigger;
	}
	void OnTrigger() override {
		if (objectTrigger->strCount != 0)
			button->unableButton = true;
		objectTrigger->OnTrigger();
	}
};

