#include "Player.h"
#include "Fish.h"
#include "../../System/InputSystem.h"

Player::Player()
{
	moveSpeed = 100.0f;
	radius = 50.0f;
	pauseEvent = nullptr;
	moveDirection = { 0.f, 0.f };
}

Player::~Player()
{

}

void Player::Init()
{
	//m_collider = new RectangleCollider(center, width, height);
	m_collider = new CircleCollider({ 0,0 }, radius);
	m_collider->parent = this;
	//m_renderBounds = { center, {width / 2, height / 2} };
}

void Player::Update(float delta)
{
	movePlayer(delta);
	//if(Input::IsKeyDown('F'))
}

void Player::Render()
{
	Render::DrawCircle(m_pos.x, m_pos.y, radius, RGB(0, 255, 0));
	//Render::DrawRect(m_pos.x, m_pos.y, m_renderBounds.extents.x * 2, m_renderBounds.extents.y * 2, RGB(255, 0, 0));
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

	if (Input::IsKeyDown(' ')) {
		SceneManager* s = SceneManager::GetInstance();
		auto c = s->GetCurScene();
		Collider* fish = c->colliderManager->GetCurrentPointCollider(m_pos, TYPE::FISH);
		if (fish != nullptr)
		{
			fish->parent->OnTrigger();
		}
	}

	if (Input::IsKey(VK_ESCAPE))
	{
		//pauseEvent
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

