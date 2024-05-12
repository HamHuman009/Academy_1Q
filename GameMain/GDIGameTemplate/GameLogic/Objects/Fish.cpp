#include "Fish.h"

void Fish::Move(float delta) {
	m_pos += m_moveDirection * speed * delta;
}
void Fish::AngularVelocity(float delta) {
	float deg = (m_AngulerDirection.x * m_moveDirection.y - m_AngulerDirection.y * m_moveDirection.x) /
		(sqrtf(powf(m_AngulerDirection.x, 2) + powf(m_AngulerDirection.y, 2)) * 
			sqrtf(powf(m_moveDirection.x,2) + powf(m_moveDirection.y, 2)));
	deg = asinf(deg) * 180.f / 3.14159f;
}

void Fish::Init() {

}

void Fish::Update(float delta) {

}

void Fish::Render() {

}

void Fish::OnTrigger() {

}