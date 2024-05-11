#pragma once
#include "../Scene/CScene.h"
#include "../Scene/StartScene.h"
enum class SceneType
{
	NONE,
	START,
	STAGE_01,
	END
};

class SceneManager
{
public:


	void Init();

	void SetCurScene(int i);

	CScene* GetCurScene();

	static SceneManager* GetInstance();


private:
	SceneManager() {};
	~SceneManager();
	CScene* m_sceneArr[(UINT)SceneType::END];
	CScene* m_curScene;
	SceneType curSceneType;
	static SceneManager* m_Instance;
};

