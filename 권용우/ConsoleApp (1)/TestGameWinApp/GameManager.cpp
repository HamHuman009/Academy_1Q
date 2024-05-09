#include "WinApp.h"
#include "InputSystem.h"
#include "TimeSystem.h"
#include "RenderSystem.h"

#include "GameManager.h"
#include "Object.h"
#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include "Collider.h"
#include "GameStruct.h"
#include "resource.h"
#include "Scene.h"

#include <typeinfo>
#include <string>
#define APSTUDIO_INVOKED
namespace game
{
#pragma region Test
	struct Object
	{
		float x;
		float y;
		float size;
		float speed;

		COLORREF color;

		void SetPos(float x, float y)
		{
			this->x = x;
			this->y = y;
		}

		void Move(float x, float y)
		{
			this->x += x;
			this->y += y;
		}
	};

	Engine::GameObject* player1 = new Engine::GameObject();
	//Object player = { global::GetWinApp().GetWidth() / 2.f ,global::GetWinApp().GetHeight() / 2.f, 10, 1, RGB(255, 255, 0) };
	Engine::GameObject* ColliderTest = new Engine::GameObject();

	

	const int bludeCircleMax = 100;
	int blueCircleCount = 0;
	Object blueCircles[bludeCircleMax];

	Engine::Vector2 temp1;

	int debugvalue = 0;
#pragma endregion
	Engine::Transform* playerTr;
	Engine::Collider* playerColl;

	void UpdatePlayer()
	{
		debugvalue = 0;
		float speed = 0.1f; // 임시
		 //게임 로직은 여기에 추가
		temp1 = Engine::Vector2(
			input::IsKey('A') ? -1 : input::IsKey('D') ? 1 : 0,
			input::IsKey('W') ? -1 : input::IsKey('S') ? 1 : 0
			);

		temp1.Normalize();
		temp1 *= speed * High_Time::GetDeltaTime();
		playerTr->position += temp1;

		/*if (player1->collider->isCollision(*ColliderTest->collider)) {
			debugvalue = 1;
		}*/
	}
	bool right = false;
	void UpdateBlueCircle()
	{
		const input::MouseState& mouse = input::GetMouseState();
		const input::MouseState& prevmouse = input::GetPrevMouseState();

		if (input::IsSame(mouse, prevmouse))
		{
			return;
		}

		if (blueCircleCount < bludeCircleMax && mouse.left)
		{
			blueCircles[blueCircleCount].SetPos(mouse.x, mouse.y);
			blueCircles[blueCircleCount].color = RGB(0, 0, 255);
			blueCircles[blueCircleCount].size = 10;
			blueCircles[blueCircleCount].speed = 0;
			blueCircleCount++;
		}

		if (mouse.right) {
			right = true;
		}
		else {
			right = false;
		}
	}
	Engine::Scene scene;

	GameManager* GameManager::instance = nullptr;
	GameManager::GameManager()
	{
	}
	GameManager::~GameManager()
	{
	}

	HBITMAP temp;
	

	void GameManager::Initialize()
	{
		input::InitInput();
		High_Time::InitTime();
		render::InitRender();

		Load();

		player1->components.PushBack(new Engine::Transform());
		player1->components.PushBack(new Engine::Collider());
		ColliderTest->components.PushBack(new Engine::Transform());
		ColliderTest->components.PushBack(new Engine::Collider());
		scene.hierarchy.PushBack(player1);
		scene.hierarchy.PushBack(ColliderTest);

		playerTr = player1->GetTransform();

		playerTr->position = { global::GetWinApp().GetWidth() / 2.f ,global::GetWinApp().GetHeight() / 2.f };
		//player1->collider->bounds = { {0,0} , {10,10} };
		//ColliderTest->transform->position = { global::GetWinApp().GetWidth() / 2.f ,global::GetWinApp().GetHeight() / 2.f + 100 };
		//ColliderTest->collider->bounds = { {0,0} , {50,50} };
	}

	void GameManager::Update()
	{
		++m_UpdateCount;

		input::UpdateMouse();
		
		High_Time::UpdateTime();

		UpdatePlayer();
		UpdateBlueCircle();

		input::ResetInput();

	}

	void GameManager::FixeUpdate()
	{
		static float elapsedTime;

		elapsedTime += High_Time::GetDeltaTime();

		while (elapsedTime >= 20.0f) //0.02초
		{
			++m_FixedUpdateCount;

			elapsedTime -= 20;
		}
	}

	void GameManager::Render()
	{
		render::BeginDraw();

		DrawSomething();
		DrawPlayer();
		DrawFPS();

		//DrawDebugLog();

		render::EndDraw();
	}
	void GameManager::Finalize()
	{
		Unload();
		render::ReleaseRender();
	}
	void GameManager::Run()
	{
		MSG msg;

		while (true)
		{
			// GetMessage 가 아니라 PeekMessage 를 사용합니다!!
			if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT) break;

				if (msg.message == WM_KEYDOWN)
				{
					input::KeyDown(msg.wParam);
				}
				else if (msg.message == WM_KEYUP)
				{
					input::KeyUp(msg.wParam);
				}
				else
				{
					DispatchMessage(&msg);
				}
			}
			else
			{
				FixeUpdate();

				Update();

				Render();
			}
		}
	}

	GameManager* GameManager::GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new GameManager();
		}
		return instance;
	}
	void GameManager::DestroyInstance()
	{
		if (instance != nullptr)
		{
			delete instance;
			instance = nullptr;
		}
	}

	void GameManager::DrawFPS()
	{
		static float elapsedTime;
		static int UpdateCount;
		static int FixedUpdateCount;
		static float time;
		time += High_Time::GetDeltaTime();

		elapsedTime += High_Time::GetDeltaTime();
		if (elapsedTime >= 1000)
		{
			elapsedTime = 0;

			UpdateCount = m_UpdateCount;
			FixedUpdateCount = m_FixedUpdateCount;

			m_UpdateCount = 0;
			m_FixedUpdateCount = 0;
		}
		std::string str = "FPS: " + std::to_string(High_Time::GetFrameRate());
		std::string str1 = "Update " + std::to_string(UpdateCount);
		std::string str2 = "FixedUpdate " + std::to_string(FixedUpdateCount);

		render::DrawText(10, 10, str.c_str(), RGB(255, 0, 0));
		render::DrawText(10, 30, str1.c_str(), RGB(255, 0, 0));
		render::DrawText(10, 50, str2.c_str(), RGB(255, 0, 0));

		std::string str3 = "time " + std::to_string(time / 1000.0f);
		render::DrawText(10, 70, str3.c_str(), RGB(255, 0, 0));
		std::string str4 = "deltaTime " + std::to_string(High_Time::GetDeltaTime());
		render::DrawText(10, 90, str4.c_str(), RGB(255, 0, 0));
		std::string str5 = "Vector2: " + std::to_string(input::GetMouseState().x) + ", " + std::to_string(input::GetMouseState().y) + ", debug : " + std::to_string(debugvalue);
		render::DrawText(10, 110, str5.c_str(), RGB(255, 0, 0));

		//std::string str6 = "Vector2: " + std::to_string(GetBitmapWidth(temp1)) + ", " + std::to_string(input::GetMouseState().y);
		//render::DrawText(10, 130, str6.c_str(), RGB(255, 0, 0));

	}

	void GameManager::DrawPlayer()
	{
		//render::DrawCircle(player1->transform->position.x, player1->transform->position.y, 10/*player.size*/, RGB(255, 255, 0)/*player.color*/);
		render::DrawRect(player1->transform->position.x - player1->collider->bounds.extents.x, player1->transform->position.y - player1->collider->bounds.extents.y, 20, 20/*player.size*/, RGB(255, 255, 0)/*player.color*/);

		render::DrawRect(ColliderTest->transform->position.x - 50, ColliderTest->transform->position.y - 50, 100, 100, RGB(128, 0, 255));
	}

	void GameManager::DrawSomething()
	{
		for (int i = 0; i < blueCircleCount; i++)
		{
			render::DrawCircle(blueCircles[i].x, blueCircles[i].y, blueCircles[i].size, blueCircles[i].color);
		}

		//render::DrawLine(player1->transform->position.x - 50, player1->transform->position.y + 50, player1->transform->position.x + 50, player1->transform->position.y + 50, RGB(255, 0, 0));
		//render::DrawRect(player1->transform->position.x - 25, player1->transform->position.y - 25, 50, 50, RGB(255, 0, 255));
		if (right) {
			render::DrawBitmap(player1->transform->position.x - 24, player1->transform->position.y - 24, temp);
		}
	}

	void GameManager::DrawDebugLog() {
		int screenWidth = GetSystemMetrics(SM_CXSCREEN);
		int screenHeight = GetSystemMetrics(SM_CYSCREEN);
		std::string str = "width: " + std::to_string(screenWidth);
		str += "           height: " + std::to_string(screenHeight);
		render::DrawText(10, 30, str.c_str(), RGB(255, 0, 0));
	}

	void GameManager::Load() {
		temp = render::LoadImdage("bitmap1.bmp");
	}

	void GameManager::Unload() {
		render::ReleaseImage(temp);
	}
}
