#include "Fish.h"


void Fish::Move(float delta) {
	m_pos += m_moveDirection * m_speed * delta;
}
void Fish::AngularVelocity(float delta) {
	// 시계방향으로 가야하면-, 반시계방향으로 가야하면+
	float angulerdirScale = sqrtf(powf(m_AngulerDirection.x, 2) + powf(m_AngulerDirection.y, 2));
	float movedirScale = sqrtf(powf(m_moveDirection.x, 2) + powf(m_moveDirection.y, 2));

	float deg = (m_AngulerDirection.x * m_moveDirection.y - m_AngulerDirection.y * m_moveDirection.x) /
		(angulerdirScale * movedirScale); // 회전방향 구하기
	//deg = asinf(deg) * 180.f / 3.14159f;
	//float rad = asinf(deg);
	
	float inner = m_AngulerDirection.x * m_moveDirection.x + m_AngulerDirection.y * m_moveDirection.y;
	float deg2 = acosf(inner / (angulerdirScale * movedirScale)) * 180.f / 3.14159f;

	float dirScale = deg > 0 ? deg2 : -deg2;
	float dir = deg > 0 ? m_AngulerSpeed * delta : -m_AngulerSpeed * delta;
	//std::cout << "abs(dirScale): " << abs(deg) * 180.f / 3.14159f << std::endl;
	if (abs(deg) * 180.f / 3.14159f <= abs(dir)) { // 남은 각도보다 회전할 각도가 클 때 방향을 m_moveDirection = m_AngulerDirection;
		m_moveDirection = { -m_AngulerDirection.x,  -m_AngulerDirection.y};
		// 회전이 완료되면 회전을 종료하는 무언가를 추가하면 될듯.
		m_AngulerDirection = { 0.f, 0.f };
	}
	else {
		dir = dir  / 180.f * 3.14159f;
		float thetaX = m_moveDirection.x * cosf(dir) - m_moveDirection.y * sinf(dir);
		float thetaY = m_moveDirection.x * sinf(dir) + m_moveDirection.y * cosf(dir);

		m_moveDirection = { thetaX, thetaY };
	}

	// m_moveDirection을 회전한 벡터로 초기화. (남은 각도 < 변경할 각도의 크기) 라면 m_moveDirection = m_AngulerDirection; 해야하고 회전중지.
}

Vector2 Fish::GetRandomDirection() {
	float theta = rand() % 360;
	theta -= 180;
	theta = theta / 180.f * 3.14159f;
	float a = cosf(theta);
	float b = sinf(theta);
	return { cosf(theta), sinf(theta) };
}

void Fish::Init() {
	// 테스트용
	m_collider = new RectangleCollider({ 0.f,0.f }, 100.f, 100.f);
	m_collider->parent = this;
	m_moveDirection = GetRandomDirection();

	//CResourceManager CR = CResourceManager::CResourceManager();
	//m_FishImage = CR.LoadBitmapResouce(L"FishTest", L"FishTest.png");
	m_FishImage = Gdiplus::Bitmap::FromFile(L"FishTest.png");
	m_renderBounds = { {0.f, 0.f}, {m_FishImage->GetWidth() / 2.f, m_FishImage->GetHeight() / 2.f}};
}

void Fish::Update(float delta) {
	time += delta;
	if (time > maxTime) {
		m_AngulerDirection = GetRandomDirection();
		time -= maxTime;
	}

	Move(delta);
	if (m_AngulerDirection != Vector2(0.f, 0.f))
		AngularVelocity(delta);
}

void Fish::Render() {
	float angulerdirScale = 1.f;
	float movedirScale = 1.f;

	float deg = (0.f * m_moveDirection.y - 1.f * m_moveDirection.x) /
		(angulerdirScale * movedirScale); // 회전방향 구하기
	//deg = asinf(deg) * 180.f / 3.14159f;
	//float rad = asinf(deg);

	float inner = 0.f * m_moveDirection.x + 1.f * m_moveDirection.y;
	float deg2 = acosf(inner / (angulerdirScale * movedirScale)) * 180.f / 3.14159f;

	float dirScale = deg > 0 ? deg2 : -deg2;
	//float dir = deg > 0 ? m_AngulerSpeed * delta : -m_AngulerSpeed * delta;


	// 테스트용
	//Render::DrawRect(m_pos.x, m_pos.y, m_renderBounds.extents.x * 2, m_renderBounds.extents.y * 2, RGB(0, 0, 255));
	Render::DrawRotateImage((int)m_pos.x, (int)m_pos.y, m_FishImage, dirScale);
	//Render::DrawImage(m_pos.x - m_renderBounds.extents.x, m_pos.y - m_renderBounds.extents.y, m_FishImage, 0, 0, (int)m_renderBounds.extents.x * 2, (int)m_renderBounds.extents.y * 2);

	Render::DrawText(10, 10, std::to_string(dirScale).c_str(), RGB(255, 0, 0));
}

void Fish::OnTrigger() {

}