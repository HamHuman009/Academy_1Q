#pragma once
#include "../stdafx.h"
#include "../GameLogic/Vector2.h"
#include "../GameLogic/Objects/Object.h"

class ColliderManager;
enum class TYPE
{
	DEFAULT,

	PLAYER,
	FISH,
	UI,

	END = 5
};

//class ColliderManager;
class CScene
{
private:
	

public:
	void SetName(const std::wstring& _strName) { m_strName = _strName; }
	const std::wstring& GetName() { return m_strName; }
	virtual void Init() = 0; 
	void Update();
	void Render();
	void PostProcessing();
	virtual void FixedUpdate();

	virtual void Start() = 0;
	virtual void Exit() = 0;
	
	ColliderManager* colliderManager; // �� ��ü �ݶ��̴��� �����ϱ� ����.

	float alpha;					  // ����
	bool isCapture = false;

	//static Gdiplus::Bitmap* prevBitmap;
	//Gdiplus::Bitmap* Getbitmap() {
	//	return prevBitmap;
	//}
protected:
	//void AddObject(Object* obj, TYPE _type) {
	//	m_arrObj[(UINT)_type].push_back(obj); //�� �ڵ� ��ö������ ��� ��.
	//}
	std::vector<Object*> m_arrObj;
	std::vector<Event*> m_eventArr;
	std::wstring m_strName;
	void AddObject(Object* obj);
	void AddEvent(Event* evt);

public:
	CScene() {};
	~CScene() {
		for (int i = 0; i < m_arrObj.size(); i++) {

			if (m_arrObj[i] != nullptr) {
				delete m_arrObj[i];
			}
		}
		for (int i = 0; i < m_eventArr.size(); i++) {

			if (m_eventArr[i] != nullptr) {
				delete m_eventArr[i];
			}
		}
		m_arrObj.clear();
		if (colliderManager != nullptr)
			delete colliderManager;
	};
};