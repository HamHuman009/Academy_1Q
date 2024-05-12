#include "Fish.h"

void Fish::Move(float delta) {
	m_pos += m_moveDirection * speed * delta;
}
void Fish::AngularVelocity(float delta) {
	// 시계방향으로 가야하면+, 반시계방향으로 가야하면-
	float angulerdirScale = sqrtf(powf(m_AngulerDirection.x, 2) + powf(m_AngulerDirection.y, 2));
	float movedirScale = sqrtf(powf(m_moveDirection.x, 2) + powf(m_moveDirection.y, 2));

	float deg = (m_AngulerDirection.x * m_moveDirection.y - m_AngulerDirection.y * m_moveDirection.x) /
		(angulerdirScale * movedirScale);
	deg = asinf(deg) * 180.f / 3.14159f;
	float rad = asinf(deg);
	
	float inner = m_AngulerDirection.x * m_moveDirection.x + m_AngulerDirection.y * m_moveDirection.y;
	float deg2 = acosf(inner / (angulerdirScale * movedirScale));

	float dirScale = deg > 0 ? deg2 : -deg2;

	// m_moveDirection을 회전한 벡터로 초기화. (남은 각도 < 변경할 각도의 크기) 라면 m_moveDirection = m_AngulerDirection; 해야하고 회전중지.
}

void Fish::Init() {
	// 테스트용
	m_collider = new RectangleCollider({ 0.f,0.f }, 100.f, 100.f);
	m_collider->parent = this;
	m_renderBounds = { {0.f, 0.f}, {50.f, 50.f} };
}

void Fish::Update(float delta) {

}

void Fish::Render() {
	// 테스트용
	Render::DrawRect(m_pos.x, m_pos.y, m_renderBounds.extents.x * 2, m_renderBounds.extents.y * 2, RGB(0, 0, 255));
}

void Fish::OnTrigger() {

}