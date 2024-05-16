#include "Player.h"
#include "Fish.h"
#include "../../System/InputSystem.h"
#include "../Event.h"

Player::Player()
{
	moveSpeed = 70.0f;
	radius = 50.0f;
	pauseEvent = nullptr;
	moveDirection = { 0.f, 0.f };
	m_AnimationMotionIndex = 0;
	Init();
	flag = false;
}

Player::~Player()
{
	if (pauseEvent != nullptr) {
		delete pauseEvent;
	}
}

void Player::Init()
{
	playerBitmap = Gdiplus::Bitmap::FromFile(L"Player.png");
	m_collider = new CircleCollider({ 0,0 }, radius);
	m_collider->parent = this;

	m_renderBounds = { { 0,0 }, {playerBitmap->GetWidth() / 2.f, playerBitmap->GetHeight() / 2.f}};

}

void Player::Update(float delta)
{
	/*sScale -= delta;
	if (sScale <= 0.7f)
	{
		sScale = 0.7f;
	}*/
	movePlayer(delta);

	ScoopUp(delta);

	if (flag == true)
	{
		ChangeStatus(ObjectStatus::OBJECT_STATUS_MOVE);
	}
	else
	{
		ChangeStatus(ObjectStatus::OBJECT_STATUS_IDLE);
	}
	
	//if(Input::IsKeyDown('F'))
	if (m_pAnimationResource && m_AnimationMotionIndex != -1)
	{
		UpdateAnimation(delta);
	}

}

void Player::Render(float alpha)
{
	/*Render::DrawCircle(m_pos.x, m_pos.y, radius, RGB(0, 255, 0));
	Render::*/

	if (m_pAnimationResource && m_AnimationMotionIndex != -1)
	{
		Frame& frame = m_pAnimationResource->m_motions[m_AnimationMotionIndex].Frames[m_AnimationFrameIndex];
		Gdiplus::Bitmap* bitmap = m_AnimationFlip ? m_pAnimationResource->m_bitmapFlip : m_pAnimationResource->m_bitmap;
		SIZE size = Render::GetScreenSize();

		int x = m_AnimationFlip ? (int)m_pos.x - (frame.Size.cx - frame.CenterX) : (int)m_pos.x - frame.CenterX;
		int y = (int)m_pos.y - frame.CenterY;
		int srcX = m_AnimationFlip ? m_pAnimationResource->m_bitmapFlip->GetWidth() - frame.Size.cx - frame.Source.left : frame.Source.left;
		int srcY = frame.Source.top;

		Render::DrawImage(x, y, bitmap, srcX, srcY, frame.Size.cx, frame.Size.cy , alpha);
	}
	//Render::DrawCircle(m_pos.x, m_pos.y, radius, RGB(0, 255, 0));
	//Render::DrawRect(m_pos.x, m_pos.y, m_renderBounds.extents.x * 2, m_renderBounds.extents.y * 2, RGB(255, 0, 0));
	//Render::DrawImage(m_pos.x - m_renderBounds.extents.x, m_pos.y - m_renderBounds.extents.y, playerBitmap, 0, 0, playerBitmap->GetWidth(), playerBitmap->GetHeight());
	//if(r) Render::DrawCircle(m_pos.x, m_pos.y, radius, RGB(0, 255, 0));
	Render::DrawImage(m_pos.x - m_renderBounds.extents.x, m_pos.y - m_renderBounds.extents.y, playerBitmap, 0, 0, playerBitmap->GetWidth(), playerBitmap->GetHeight(), alpha, scale);
}

void Player::OnTrigger()
{
	// 물고기 잡을때 트리거
}
void Player::movePlayer(float delta)
{
	// 키설정 버튼이 바뀔 수 있음
	if (Input::IsKey('W') && !Input::IsKey('A') && !Input::IsKey('S') && !Input::IsKey('D'))
	{
		Up(delta);
	}
	else if (Input::IsKey('S') && !Input::IsKey('A') && !Input::IsKey('W') && !Input::IsKey('D'))
	{
		Down(delta);
	}
	else if  (Input::IsKey('A') && !Input::IsKey('W') && !Input::IsKey('S') && !Input::IsKey('D'))
	{
		Left(delta);
	}
	else if (Input::IsKey('D') && !Input::IsKey('A') && !Input::IsKey('S') && !Input::IsKey('W'))
	{
		Right(delta);
	}
	else if (Input::IsKey('W') && Input::IsKey('A') && !Input::IsKey('S') && !Input::IsKey('D')) // 좌상단
	{
		Left(delta);
		Up(delta);
	}
	else if (!Input::IsKey('W') && Input::IsKey('A') && Input::IsKey('S') && !Input::IsKey('D')) // 좌하단
	{ 
		Left(delta);
		Down(delta);
	}
	else if (Input::IsKey('W') && !Input::IsKey('A') && !Input::IsKey('S') && Input::IsKey('D')) // 우상단
	{ 
		Right(delta);
		Up(delta);
	}
	else if (!Input::IsKey('W') && !Input::IsKey('A') && Input::IsKey('S') && Input::IsKey('D')) // 우하단
	{ 
		Right(delta);
		Down(delta);
	}
	else
	{
		flag = false;
		// flag 설정할것
	}

	if (Input::IsKey(VK_ESCAPE))
	{
		//pauseEvent
		pauseEvent->OnTrigger();
	}
}

void Player::ScoopUp(float delta)
{
	if (Input::IsKeyDown(' ') && isScoopUp == false) {
		isScoopUp = true;
		moveSpeed = 45.f;
	}

	if (isScoopUp == true) {
		std::cout << scoopUpTime << ", " << scale << std::endl;
		scoopUpTime += delta;
		if (scoopUpTime >= 0.f && scoopUpTime < 1.5f) {
			scale -= delta * 0.25f / 1.5f; // 1.5초에 걸쳐서 0.75 scale까지 줄어듦.
			if (scale < 0.75f)
				scale = 0.75f;
		}
		else if (scoopUpTime >= 1.5f && scoopUpTime < 4.5f) {
			// nothing
		}
		else if (scoopUpTime >= 4.5f && scoopUpTime < 6.f) {
			scale += delta * 0.25f / 1.5f;
			if (scale > 1.f)
				scale = 1.f;
		}

		if (scoopUpTime >= 1.3f && scoopUpTime < 1.5f) {
			// 사운드, 시각효과
			//r = true;
		}
		else if (scoopUpTime >= 1.5f && scoopUpTime < 4.5f) {
			SceneManager* s = SceneManager::GetInstance();
			auto c = s->GetCurScene();

			Collider* fishs[20];
			int count = c->colliderManager->GetCountCollidersAtType(m_collider, fishs, 20, TYPE::FISH);
			for (int i = 0; i < count; i++) {
				fishs[i]->parent->OnTrigger();
			}
		}
		else if (scoopUpTime >= 4.5f && scoopUpTime < 6.f) {
			
		}
		else if (scoopUpTime >= 6.f){
			isScoopUp = false;
			scoopUpTime = 0.f;
			moveSpeed = 70.f;
			//r = false;
		}
	}
}

void Player::Up(float delta)
{
	moveDirection.y = -1;
	Vector2 normal = Vector2(0, -1);
	normal.Normalize();
	m_pos += normal * moveSpeed * delta;
}

void Player::Down(float delta)
{
	moveDirection.y = 1;
	Vector2 normal = Vector2(0, 1);
	normal.Normalize();
	m_pos += normal * moveSpeed * delta;
}

void Player::Left(float delta)
{
	moveDirection.x = -1;
	Vector2 normal = Vector2(-1, 0);
	normal.Normalize();
	m_pos += normal * moveSpeed * delta;
}

void Player::Right(float delta)
{
	moveDirection.x = -1;
	Vector2 normal = Vector2(1, 0);
	normal.Normalize();
	m_pos += normal * moveSpeed * delta;
}

void Player::SetStatus()
{
	if (m_status != ObjectStatus::OBJECT_STATUS_ATTACK)
	{
		if (m_moveDirPrev == Vector2(0.0f,0.0f))
		{
			if (m_moveDir != Vector2(0.0f, 0.0f))
				ChangeStatus(ObjectStatus::OBJECT_STATUS_MOVE);
		}
		else if (m_moveDirPrev != Vector2(0.0f, 0.0f))
		{
			if (m_moveDir == Vector2(0.0f, 0.0f))
				ChangeStatus(ObjectStatus::OBJECT_STATUS_IDLE);
		}
	}
}

