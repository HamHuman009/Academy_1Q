#pragma once
#include "Vector2.h"
#include "Bounds.h"
//#include "Collider.h"

class Collider;

enum ObjectStatus {
	OBJECT_STATUS_IDLE,
	OBJECT_STATUS_MOVE,
	OBJECT_STATUS_ATTACK
};

struct AnimationResource;
struct Object
{
	bool m_isActive = true;							// isDead ��� Ȱ�����¸� ��Ÿ��.

	//bool m_player = true;							�ּ�ó�� �ص� ������ Object�� ��ӹ��� ����.
	//bool m_isDead = false;
	Vector2 m_pos;									// ���� ��ġ	

	Collider* m_collider;							// �浹ó��
	Bounds m_renderBounds;							// ������ �̹��� ��ǥ
	//float m_speed = 500.0f;						// �̵� ������ �ӷ�

	//Vector2 m_moveDir = { 0.0f,0.0f };			// ������ ���� ����
	//Vector2 m_moveDirPrev = { 0.0f,0.0f };		// ������ ���� ����
	//Vector2 m_inputDir;							// �Է� ����


	//SIZE  m_colliderSize ={ 50,50 };
	//COLORREF m_color = RGB(255,255,255);
	ObjectStatus m_status = OBJECT_STATUS_IDLE;	// �÷��̾��� ���� ��Ÿ�� �� ���

	AnimationResource* m_pAnimationResource = nullptr;	
	int m_AnimationMotionIndex = -1;
	int m_AnimationFrameIndex = 0;
	float m_AnimationAccTime = 0.0f;
	bool m_AnimationFlip = false;

	void Init();
	void Update(float delta);
	void Render();
	void SetMotion(int index);
	void UpdateAnimation(float delta);	
	void ChangeStatus(ObjectStatus status);

	Vector2 GetPosition();
	virtual void OnTrigger() = 0;;

	friend class Collider;
	friend class CircleCollider;
	friend class RectangleCollider;
};

