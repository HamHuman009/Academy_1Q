#pragma once
#include "../Manager/SceneManager.h"
#include "../Manager/GameManager.h"
#include "../Scene/CScene.h"
#include "../System/TimeSystem.h"

class Event {
public:
	virtual void Init() {};
	virtual void OnTrigger() = 0;
	Event() {};
	~Event() {};
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
		nextSceneNum = sceneNum;
	}

	/*void Init() override {
		scnManager = SceneManager::GetInstance();
		
		
	}*/

	void OnTrigger() override {
		SelectScene(nextSceneNum);
	}

	void SelectScene(int i) {
		scnManager->SetCurScene(i);
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
		
	}

};

class ResumeEvent : public Event
{
	void OnTrigger() override
	{

	}
};

class RetryEvent : public Event
{
	void OnTrigger() override
	{

	}
};

class ExitEvent : public Event
{
	void OnTrigger() override
	{

	}
};