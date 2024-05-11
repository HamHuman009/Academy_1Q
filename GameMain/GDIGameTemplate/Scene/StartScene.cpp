#include "StartScene.h"
UIBackGround* myBack;
void StartScene::Start() 
{

}

void StartScene::Init()
{	
	myBack = new UIBackGround();
	AddObject(myBack);
	
}

void StartScene::Render() //이 부분 고칠 것.
{	
	for (int i = 0; i < m_arrObj->size(); i++) {
		m_arrObj[i];
	}
}

void StartScene::Update() {

}

void StartScene::FixedUpdate() {

}

void StartScene::Exit() 
{
	
}
