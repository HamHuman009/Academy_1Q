#include "SceneManager.h"
SceneManager* SceneManager::m_Instance = nullptr;

void SceneManager::Init() {
	m_sceneArr[(UINT)SceneType::START] = new StartScene();
	SetCurScene((UINT)SceneType::START);
}

void SceneManager::SetCurScene(int i) {
	m_curScene =  m_sceneArr[i];
}

CScene* SceneManager::GetCurScene() {
	return m_curScene;
}

SceneManager* SceneManager::GetInstance() {
	if (m_Instance == nullptr) {
		m_Instance = new SceneManager();
		m_Instance->Init();
	}
	return m_Instance;
}