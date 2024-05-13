#include "Player.h"
#include "../System/InputSystem.h"

Player::Player()
{
	moveSpeed = 100.0f;
	center = { 1,1 };
	width = 50.0f;
	height = 50.0f;
	radius = 50.0f;
}

Player::~Player()
{

}

void Player::Init()
{
	//m_collider = new RectangleCollider(center, width, height);
	m_collider = new CircleCollider(center, radius);
	m_collider->parent = this;
	//m_renderBounds = { center, {width / 2, height / 2} };
}

void Player::Update(float delta)
{
	movePlayer(delta);
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
	if (Input::IsKey('W'))
	{
		m_pos.y -= moveSpeed * delta;
	}
	if (Input::IsKey('S'))
	{
		m_pos.y += moveSpeed * delta;
	}
	if  (Input::IsKey('A'))
	{
		m_pos.x -= moveSpeed * delta;
	}
	if (Input::IsKey('D'))
	{
		m_pos.x += moveSpeed * delta;
	}


}
