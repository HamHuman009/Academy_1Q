#include "Player.h"
#include "Fish.h"
#include "../../System/InputSystem.h"
#include "../Event.h"
#include "../../System/SoundSystem.h"

Player::Player()
{
	moveSpeed = 70.0f;
	radius = 50.0f;
	pauseEvent = nullptr;
	moveDirection = { 0.f, 0.f };
	m_AnimationMotionIndex = 0;
	cnt = 0;
	Init();
	BossCnt = 0;
}

//Player::~Player()
//{
//	/*if (pauseEvent != nullptr) {
//		delete pauseEvent;
//	}*/
//}

void Player::Init()
{
	playerBitmap = Gdiplus::Bitmap::FromFile(L"Player.png");
	m_collider = new CircleCollider({ 0,0 }, radius);
	m_collider->parent = this;

	m_renderBounds = { { 0,0 }, {playerBitmap->GetWidth() / 2.f, playerBitmap->GetHeight() / 2.f}};

	isAwake = false;
}

void Player::Update(float delta)
{
	movePlayer(delta);

	ScoopUp(delta);
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
	Render::DrawTextW(10, 30, std::to_string(cnt).c_str(), RGB(255, 0, 0));
	Render::DrawTextW(10, 70, std::to_string(BossCnt).c_str(), RGB(0, 0, 255));
	Render::DrawImage(m_pos.x - m_renderBounds.extents.x, m_pos.y - m_renderBounds.extents.y, playerBitmap, 0, 0, playerBitmap->GetWidth(), playerBitmap->GetHeight(), alpha, scale);
}

void Player::OnTrigger()
{
	
}
void Player::movePlayer(float delta)
{
	moveDirection = { 0.f, 0.f };
	if (Input::IsKey('W')) {
		moveDirection += isAwake ? Vector2(0.f, -1.f) : up;
	}
	else if (Input::IsKey('S')) {
		moveDirection += isAwake ? Vector2(0.f, 1.f) : down;
	}
	if (Input::IsKey('A')) {
		moveDirection += isAwake ? Vector2(-1.f, 0.f) : left;
	}
	else if (Input::IsKey('D')) {
		moveDirection += isAwake ? Vector2(1.f, 0.f) : right;
	}
	if(moveDirection != Vector2(0.f, 0.f))
		moveDirection.Normalize();
	m_pos += moveDirection * moveSpeed * delta;
	if (Input::IsKey(VK_ESCAPE))
	{
		//pauseEvent
		pauseEvent->OnTrigger();
	}
}

void Player::ScoopUp(float delta)
{
	event4timer -= delta;
	event5timer -= delta;
	//cheat key
	if (Input::IsKeyDown('I')) {
		SoberUp();
	}
	if (Input::IsKeyDown('U')) {
		CancelSoberUp();
	}
	//---------

	if (isAwake == true) {
		awakeTime -= delta;
		if (awakeTime <= 0.f) {
			CancelSoberUp();
		}
	}

	if (Input::IsKeyDown(' ') && isScoopUp == false) {
		isScoopUp = true;
		moveSpeed = 45.f;
		isOnScoopUpSound = true;
		
	}

	if (isScoopUp == true) {
		scoopUpTime += delta;
		if (scoopUpTime >= 0.f && scoopUpTime < 1.5f) {
			scale -= delta * 0.25f / 1.5f; 
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
			//r = true;
			if (isOnScoopUpSound == true) {
				// Sound Play
				if (mySound::SoundManager::GetInstance()->isChannelPlaying(mySound::eSoundChannel::Effect) == false) {
					mySound::SoundManager::GetInstance()->PlayMusic(mySound::eSoundList::Water, mySound::eSoundChannel::Effect);
				}
				isOnScoopUpSound = false; 
			}
		}
		else if (scoopUpTime >= 1.5f && scoopUpTime < 4.5f) {
			SceneManager* s = SceneManager::GetInstance();
			auto c = s->GetCurScene();

			Collider* fishs[24];
			int count = c->colliderManager->GetCountCollidersAtType(m_collider, fishs, 20, TYPE::FISH);
			for (int i = 0; i < count; i++) {
				if (std::wcsstr(fishs[i]->parent->m_name, L"Craw") != nullptr) {
					if (!isAwake) {
						if (cnt == 0) {
							if (feedbackEvent1_ifCrawCaptureScoreZero != nullptr)
								feedbackEvent1_ifCrawCaptureScoreZero->OnTrigger();
						}
						else if (cnt >= 1) {
							if (feedbackEvent2_ifCrawCaptureScoreOne != nullptr)
								feedbackEvent2_ifCrawCaptureScoreOne->OnTrigger();
						}
						fishs[i]->parent->OnTrigger();
						cnt--;
						SoberUp();
					}
				}
				else if (std::wcsstr(fishs[i]->parent->m_name, L"Boss") != nullptr) {
					if (feedbackEvent3_CaptureBossFish != nullptr)
						feedbackEvent3_CaptureBossFish->OnTrigger();
					cnt += 3;
					BossCnt++;
					fishs[i]->parent->OnTrigger();
				}
				else {
					if (event4timer <= 0.f) {
						event4timer = event4timerMax;
						if (feedbackEvent4_CaptureFish != nullptr)
							feedbackEvent4_CaptureFish->OnTrigger();
					}
					if (event5timer <= 0.f) {
						event5timer = event5timerMax;
						event5count = 0;
					}
					else {
						event5count++;
						if (event5count >= 2) {
							event5count = 0;
							event5timer = 0.f;
							if (feedbackEvent5_OneCaptureTwoKill != nullptr)
								feedbackEvent5_OneCaptureTwoKill->OnTrigger();
						}
					}
					cnt++;

					fishs[i]->parent->OnTrigger();
				}

				std::cout << cnt << '\n';
				std::cout << (std::wcsstr(fishs[i]->parent->m_name, L"Craw") != nullptr) << '\n';
				std::wcout << fishs[i]->parent->m_name << std::endl;
			}
			if (isSevenScore == false && cnt >= 7) {
				isSevenScore = true;
				if (feedbackEvent6_SevenScore != nullptr)
					feedbackEvent6_SevenScore->OnTrigger();
			}

			if (prevCnt != cnt) {
				event9timer = event9timerMax;
			}
			else {
				event9timer -= delta;
				if (event9timer <= 0.f) {
					if (feedbackEvent9_10secNothingAnd14sec != nullptr)
						feedbackEvent9_10secNothingAnd14sec->OnTrigger();
				}
			}
			prevCnt = cnt;
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

void Player::SetMoveDirection(Vector2 _up, Vector2 _down, Vector2 _left, Vector2 _right)
{
	up = _up;
	down = _down;
	left = _left;
	right = _right;
}

void Player::SoberUp()
{
	isAwake = true;
	awakeTime = 15.f;
}

void Player::CancelSoberUp()
{
	isAwake = false;
	awakeTime = 0.f;
}



