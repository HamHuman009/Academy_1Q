#include "Player.h"
#include "Fish.h"
#include "../../System/InputSystem.h"
#include "../Event.h"
#include "../../System/SoundSystem.h"

Player::Player()
{
	moveSpeed = 70.0f;
	radius = 25.0f;
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

float randomSoundTimer;

void Player::Init()
{
	//playerBitmap = Gdiplus::Bitmap::FromFile(L"Player.png");
	Default_playerBitmap		 =	Gdiplus::Bitmap::FromFile(L"Scooper_Defalt_Body.png");
	Default_playerBitmap_Paper	 = 	Gdiplus::Bitmap::FromFile(L"Scooper_Defalt_Paper.png");
	Target_playerBitmap			 = 	Gdiplus::Bitmap::FromFile(L"Scooper_Target_Body.png");
	Target_playerBitmap_Paper	 = 	Gdiplus::Bitmap::FromFile(L"Scooper_Target_Paper.png");
	TimeOver_playerBitmap		 = 	Gdiplus::Bitmap::FromFile(L"Scooper_Ripped_Paper.png");

	m_collider = new CircleCollider({ 0,0 }, radius);
	m_collider->parent = this;

	m_renderBounds = { { -10, -71 }, {Default_playerBitmap->GetWidth() / 2.f, Default_playerBitmap->GetHeight() / 2.f}};
	randomSoundTimer = (rand() % 300 + 400)/100.f;
	//timeOverMoment = 1.3f; 
	//스쿱 찢어지는 순간으로 생각하고 넣어둠
	isAwake = false;
}

void Player::Update(float delta)
{
	movePlayer(delta);
	randomSoundTimer = randomSoundTimer - delta;
	if (randomSoundTimer < 0.f) {
		int i = (rand() % 3);
		switch (i)
		{
		case 0:
			mySound::SoundManager::GetInstance()->PlayMusic(mySound::eSoundList::Fish_breathing1, mySound::eSoundChannel::Effect);
			break;
		case 1:
			mySound::SoundManager::GetInstance()->PlayMusic(mySound::eSoundList::Fish_breathing2, mySound::eSoundChannel::Effect);
			break;
		case 2:
			mySound::SoundManager::GetInstance()->PlayMusic(mySound::eSoundList::Fish_breathing3, mySound::eSoundChannel::Effect);
			break;
		}
		
		randomSoundTimer = (rand() % 300 + 400) / 100.f;
	}
	//if (timeOverMoment) {

	//} 스쿱 찢어질때 소리 넣을 곳 용우씨에게 문의
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
	//Render::DrawRect(m_pos.x, m_pos.y, m_renderBounds.extents.x * 2, m_renderBounds.extents.y * 2, RGB(255, 0, 0));
	//Render::DrawImage(m_pos.x - m_renderBounds.extents.x, m_pos.y - m_renderBounds.extents.y, playerBitmap, 0, 0, playerBitmap->GetWidth(), playerBitmap->GetHeight());
	//if(r) Render::DrawCircle(m_pos.x, m_pos.y, radius, RGB(0, 255, 0));

	if (Input::IsKey('Q')) {
		Render::DrawTextW(10, 30, std::to_string(cnt).c_str(), RGB(255, 0, 0));
		Render::DrawTextW(10, 70, std::to_string(BossCnt).c_str(), RGB(0, 0, 255));
	}
	Render::DrawImage(m_pos.x - m_renderBounds.extents.x + 10, m_pos.y - m_renderBounds.extents.y + 51, 
		gameOver ? TimeOver_playerBitmap : (scoopUpTime > 1.3f && scoopUpTime < 4.5f) ? Target_playerBitmap_Paper : Default_playerBitmap_Paper,
		0, 0, Default_playerBitmap_Paper->GetWidth(), Default_playerBitmap_Paper->GetHeight(), (scoopUpTime > 1.3f && scoopUpTime < 4.5f) ? 0.2f : 0.5f, scale);
	Render::DrawImage(m_pos.x - m_renderBounds.extents.x + 10, m_pos.y - m_renderBounds.extents.y + 51, 
		(scoopUpTime > 1.3f && scoopUpTime < 4.5f) ? Target_playerBitmap : Default_playerBitmap,
		0, 0, Default_playerBitmap->GetWidth(), Default_playerBitmap->GetHeight(), alpha, scale);
	//Render::DrawCircle(m_pos.x, m_pos.y, radius, RGB(0, 255, 0));
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
	if (Input::IsKey('S')) {
		moveDirection += isAwake ? Vector2(0.f, 1.f) : down;
	}
	if (Input::IsKey('A')) {
		moveDirection += isAwake ? Vector2(-1.f, 0.f) : left;
	}
	if (Input::IsKey('D')) {
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

	if (Input::IsKeyDown(' ') && isScoopUp == false && High_Resolution_Time::GetDeltaTime() != 0.f) {
		isScoopUp = true;
		moveSpeed = 45.f;
		isOnScoopUpSound = true;
		
	}

	if (isScoopUp == true) {
		scoopUpTime += delta;
		if (scoopUpTime >= 0.f && scoopUpTime < 1.5f) {
			scale -= delta * 0.25f / 1.5f; 
			if (scale < 0.75f) {
				scale = 0.75f;
			}
		}
		else if (scoopUpTime >= 1.5f && scoopUpTime < 4.5f) {
			// nothing
		}
		else if (scoopUpTime >= 4.5f && scoopUpTime < 6.f) {
			scale += delta * 0.25f / 1.5f;
			if (scale > 1.f) {
				scale = 1.f;
			}
		}

		if (scoopUpTime >= 1.3f && scoopUpTime < 1.5f) {
			//r = true;
			if (isOnScoopUpSound == true) {
				// Sound Play
				if (mySound::SoundManager::GetInstance()->isChannelPlaying(mySound::eSoundChannel::Scoop) == false) {
					mySound::SoundManager::GetInstance()->PlayMusic(mySound::eSoundList::Scooper_Down, mySound::eSoundChannel::Scoop);
				}
				if(temp != nullptr)
					temp->OnTrigger();
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
								feedbackEvent1_ifCrawCaptureScoreZero->OnTrigger(); //가재 잡은 순간 분노 넣어야 하는디 언제 넣는지 용우씨에게 문의
						}
						else if (cnt >= 1) {
							if (feedbackEvent2_ifCrawCaptureScoreOne != nullptr)
								feedbackEvent2_ifCrawCaptureScoreOne->OnTrigger();
						}
						mySound::SoundManager::GetInstance()->PlayMusic(mySound::eSoundList::Anger_Sound_Start,mySound::eSoundChannel::Voice);
						fishs[i]->parent->OnTrigger();
						cnt--;
						SoberUp();
					}
				}
				else if (std::wcsstr(fishs[i]->parent->m_name, L"Boss") != nullptr) {
					if (feedbackEvent3_CaptureBossFish != nullptr)
						feedbackEvent3_CaptureBossFish->OnTrigger();
					if (CatchBossFish != nullptr)
						CatchBossFish->OnTrigger();
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
					mySound::SoundManager::GetInstance()->PlayMusic(mySound::eSoundList::Fish_Catch, mySound::eSoundChannel::Effect);
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
			if (isOnScoopUpSound == false) {
				isOnScoopUpSound = true;
				if (mySound::SoundManager::GetInstance()->isChannelPlaying(mySound::eSoundChannel::Scoop) == false) {
					mySound::SoundManager::GetInstance()->PlayMusic(mySound::eSoundList::Scooper_Up, mySound::eSoundChannel::Scoop);
				}
				if (temp != nullptr)
					temp->OnTrigger();
			}
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
	//Game::GameManager::GetInstance()->SetCameraShakeTimer(awakeTime);
	Game::GameManager::GetInstance()->SetHardCameraShake(1.f);
	Game::GameManager::GetInstance()->OffCameraShaker();

}

void Player::CancelSoberUp()
{	
	mySound::SoundManager::GetInstance()->PlayMusic(mySound::eSoundList::Anger_Sound_End, mySound::eSoundChannel::Voice);
	isAwake = false;
	awakeTime = 0.f;
	//Game::GameManager::GetInstance()->OffCameraShaker();
	Game::GameManager::GetInstance()->SetCameraShakeTimer(6000.f);
}



