#include "UIObject.h"
#include "../Event.h"


void UIObject::Init() {

}

void UIObject::Render(float alpha)
{

}


void UIObject::OnTrigger()
{

}

void UIImage::Init(Gdiplus::Bitmap* myBitMap, Vector2 myVector) {
	//CResourceManager* CR = CResourceManager::GetInstance();
	//m_BackGround = CR->LoadBitmapResouce(L"image1",L"image1.png");
	//m_BackGround = Gdiplus::Bitmap::FromFile(L"image1.png");
	m_BackGround = myBitMap;
	if (m_BackGround == nullptr) return;
	m_renderBounds = { {0.f, 0.f}, {myBitMap->GetWidth() / 2.f, myBitMap->GetHeight() / 2.f} };
	m_pos = myVector;
}

void UIImage::Render(float _alpha) {
	if (m_isActive == false) return;
	//0x00000147f3f723d0
	if (m_BackGround == nullptr) return;
	Render::DrawImage(m_pos.x - m_renderBounds.extents.x, m_pos.y - m_renderBounds.extents.y, m_BackGround, 0, 0, m_renderBounds.extents.x * 2, m_renderBounds.extents.y * 2, alpha);
}
//���� - ���� - ��ư - �⺻ - 1	200 * 100
void UIButton::Init(Vector2 myPos, Event* myEvent, const std::wstring& _strkey, const std::wstring& _extention) {
	CRM = CResourceManager::GetInstance();
	std::wstring fullPath_On = _strkey;
	std::wstring fullPath_Off = _strkey;
	fullPath_On.append(L"_On");
	fullPath_Off.append(L"_Off");
	m_Bitmap_On = CRM->LoadBitmapResouce(fullPath_On, fullPath_On.append(_extention));
	m_Bitmap_Off = CRM->LoadBitmapResouce(fullPath_Off, fullPath_Off.append(_extention));

	std::wstring off;
	m_pos = myPos;
	m_Event = myEvent;
	if (m_Bitmap_On == nullptr) return;
	cx = m_Bitmap_On->GetWidth();
	cy = m_Bitmap_On->GetHeight();
	m_collider = new RectangleCollider({ 0.f,0.f }, { (float)cx, (float)cy });
	m_collider->parent = this;
	m_CurBitMap = m_Bitmap_On;
}

void UIButton::Render(float alpha) {
	if (m_isActive == false) return;
	Render::DrawImage(m_pos.x - (cx / 2), m_pos.y - (cy / 2), m_CurBitMap, 0, 0, cx, cy, 1.0f);
}

void UIButton::OnTrigger() {
	if (m_Event != nullptr) m_Event->OnTrigger();
}

void UIButton::Update(float delta) {
	if (m_isActive == false) return;


	Vector2 temp = Vector2(Input::GetMouseState().x, Input::GetMouseState().y);
	if (m_collider->isPointColliding(temp)) {
		if (Input::GetPrevMouseState().left && Input::GetMouseState().left) {
			m_CurBitMap = m_Bitmap_Off;
		}
		else if (Input::GetPrevMouseState().left && !Input::GetMouseState().left) {
			m_CurBitMap = m_Bitmap_On;
			OnTrigger();
		}
	}
	else {
		m_CurBitMap = m_Bitmap_On;
	}
}

//����-�ð�-������-��-������-1	600*50
//���� - �ð� - ������ - �� - ��� - 1	600 * 50
void UITimer::Init(CResourceManager* CRM, Vector2 myPos, Event* myEvent, float _setTime) {
	m_BitmapBack = CRM->LoadBitmapResouce(L"timerBack", L"UI_Image_Stage_TimeBar_Off_01.png");
	m_BitmapBar = CRM->LoadBitmapResouce(L"timerbar", L"UI_Image_Stage_TimeBar_On_01.png");
	m_BitmapClock = CRM->LoadBitmapResouce(L"timerClock", L"UI_Image_Stage_TimeBar_Off_02.png");
	m_BitmapLeft = CRM->LoadBitmapResouce(L"timerLeft", L"UI_Image_Stage_TimeBar_On_Left_01.png");
	m_BitmapRight = CRM->LoadBitmapResouce(L"timerRight", L"UI_Image_Stage_TimeBar_On_Right_01.png");

	m_pos = myPos;
	m_Event = myEvent;

	cx = 551;
	cy = 50;

	deltaCx = 551;
	setTime = _setTime;
	deltaTime = _setTime;
}
void UITimer::Update(float delta) {
	if (m_isActive == false) return;
	deltaTime -= delta;
	/*std::cout << "delta : " << delta << endl;
	std::cout << "setTime : " << setTime << endl;*/
	//�پ�� ���� ����  = (���ѽð����� delta��ũ �پ�� �ñ⳪ / ���� �ð� ) * ���� ���� ��
	if (deltaTime > 0) {

		deltaCx = (deltaTime / setTime) * cx;

		if (deltaTime < 18.f && istutorial2 == false) {
			if (tutorialEvent2 != nullptr) tutorialEvent2->OnTrigger();
			istutorial2 = true;
		}if (deltaTime < 14.f && istutorial3 == false) {
			if (tutorialEvent3 != nullptr) tutorialEvent3->OnTrigger();
			istutorial3 = true;
		}if (deltaTime < 10.f && istutorial4 == false) {
			if (tutorialEvent4 != nullptr) tutorialEvent4->OnTrigger();
			istutorial4 = true;
		}if (deltaTime < 1.5f && istutorial5 == false) {
			if (tutorialEvent5 != nullptr) tutorialEvent5->OnTrigger();
			istutorial5 = true;
		}

		if (deltaTime < 7.f && isOn == false) {
			isOn = true;
			if (remainningTimeEvent != nullptr)
				remainningTimeEvent->OnTrigger();
		}

		if (deltaTime < .5f && isGameOverOn == false) {
			mySound::SoundManager::GetInstance()->PlayMusic(mySound::eSoundList::Scooper_Broken,mySound::eSoundChannel::Effect);
			isGameOverOn = true;
			if (gameOverTimerEvent != nullptr) {
				gameOverTimerEvent->OnTrigger();
			}
		}
	}
	else {
		OnTrigger();
	}
}

void UITimer::Render(float alpha) {
	if (m_isActive == false) return;
	Render::DrawBitmap(m_pos.x, m_pos.y, m_BitmapBack, 0, 0, cx + 75, cy);
	Render::DrawBitmap(m_pos.x + 12, m_pos.y, m_BitmapBar, 0, 0, (UINT)deltaCx, cy);

	Render::DrawBitmap(m_pos.x, m_pos.y, m_BitmapLeft, 0, 0, 12, cy);
	Render::DrawBitmap(m_pos.x + deltaCx + 12, m_pos.y, m_BitmapRight, 0, 0, 12, cy);

	Render::DrawBitmap(m_pos.x - 70, m_pos.y - 25, m_BitmapClock, 0, 0, 100, 100);
	/*Render::DrawRect(m_pos.x, m_pos.y, cx, cy, RGB(255, 255, 255));
	Render::DrawRect(m_pos.x, m_pos.y, (UINT)deltaCx, cy, RGB(255, 255, 0));*/
}

void UITimer::OnTrigger() {
	if (m_Event != nullptr) m_Event->OnTrigger();
}

void UIBackGround::Init(const WCHAR* fileName, CResourceManager* CRM) {
	LoadAnimImage(fileName, CRM);
	m_pos = { 960.f, 540.f };
	m_renderBounds = { {0,0},{m_bitmap[0]->GetWidth() / 2.f,m_bitmap[0]->GetHeight() / 2.f} };
	backGroundFrame = 0;
	backGroundFrameFlag = 0;
}

void UIBackGround::LoadAnimImage(const WCHAR* fileName, CResourceManager* CRM)
{
	int fileNameLength = wcslen(fileName);

	m_fileName[0] = fileName;
	m_bitmap[0] = CRM->LoadBitmapResouce(fileName, fileName);
	std::wstring noNumFileName = m_fileName[0].substr(0, fileNameLength - 6);

	for (int i = 1; i < BACK_GROUND_ANIM_FRAME; i++) {
		std::wstring wZero = std::to_wstring(0);

		std::wstring wNum = std::to_wstring(i);
		if (i < 10) {
			m_fileName[i] = noNumFileName.append(wZero).append(wNum);
		}
		else {
			m_fileName[i] = noNumFileName.append(wNum);
		}

		m_bitmap[i] = CRM->LoadBitmapResouce(m_fileName[i].c_str(), m_fileName[i].append(L".png").c_str());
		noNumFileName = noNumFileName.substr(0, fileNameLength - 6);
	}


}

void UIBackGround::Update(float delta) {
	time += delta;
	if (time >= maxTime) {
		time -= maxTime;
		backGroundFrame = (backGroundFrame + 1) % BACK_GROUND_ANIM_FRAME;
	}

	/*backGroundFrameFlag = ++backGroundFrameFlag % backGroundFrameInterval;
	if (backGroundFrameFlag == 9) {
		backGroundFrame = ++backGroundFrame % BACK_GROUND_ANIM_FRAME;
	}*/
}

void UIBackGround::Render(float alpha) {

	/*Render::DrawImage(m_pos.x - m_renderBounds.extents.x,
		m_pos.y - m_renderBounds.extents.y, m_bitmap[backGroundFrame],
		0, 0, m_renderBounds.extents.x * 2, m_renderBounds.extents.y * 2);*/

		//Render::DrawImage(50, 200, m_bitmap[backGroundFrame], 0, 0, 1250, 800);
	Render::DrawBitmap(0, 0, m_bitmap[backGroundFrame], 0, 0, 1280, 720);

}

void UIBackGround::FixedUpdate() {


}


//UIBackGround::~UIBackGround() {
//	for (int i = 0; i < BACK_GROUND_ANIM_FRAME; i++) {
//		if (m_bitmap[i]!=nullptr)
//			delete m_bitmap[i];
//	}
//}


void UIDialog::Init(Vector2 myPos, Vector2 endPos, WCHAR* _string, int _fontSize, COLORREF myColor) {
	x = myPos.x;
	y = myPos.y;
	cx = endPos.x;
	cy = endPos.y;
	//string = _string;
	wcscpy_s(string, 255, _string);
	strCount = 0;
	memset(t_str, '\0', 255);
	timer = maxTime;
	m_Color = myColor;
	fontSize = _fontSize;

	m_pos.x = float(x + cx / 2);
	m_pos.y = float(y + cy / 2);
	m_renderBounds = { {0.f, 0.f}, {cx / 2.f, cy / 2.f} };
}

void UIDialog::Render(float alpha) {
	//Render::DrawFont(x, y, cx, cx, string, RGB(0, 255, 0), 12, L"Arial", 1);
	//Render::DrawFont(x, y, cx, cy, t_str, RGB(0, 255, 0), 12, L"Arial", 1);
	Render::DrawFontS(m_pos.x - m_renderBounds.extents.x, m_pos.y - m_renderBounds.extents.y, 
		cx, cy, t_str, m_Color, fontSize, L"KOTRAHOPE.ttf", 1);
}

void UIDialog::Update(float delta) {
	timer -= delta;
	if (timer <= 0.f) {
		timer += maxTime;
		if (string[strCount] != '\0') {
			/*if (mySound::SoundManager::GetInstance()->isChannelPlaying(mySound::eSoundChannel::Effect))
			{
				mySound::SoundManager::GetInstance()->PlayMusic(mySound::eSoundList::Talk_Output, mySound::eSoundChannel::Effect);
			}*/
			t_str[strCount] = string[strCount];
			strCount++;
		}
	}
	if (strCount < 255 && string[strCount] != '\0' && Input::GetMouseState().left && !Input::GetPrevMouseState().left) {
		// ���� ��ȭ�� �����ִٸ� ��ȭ�� ��� ���.
		/*if (mySound::SoundManager::GetInstance()->isChannelPlaying(mySound::eSoundChannel::Effect))
		{
			mySound::SoundManager::GetInstance()->PlayMusic(mySound::eSoundList::Talk_Output, mySound::eSoundChannel::Effect);
		}*/
		wcscpy_s(t_str, 255, string);
	}
}

void UIDialog::OnTrigger() {
	if (m_Event != nullptr) m_Event->OnTrigger();
}

UICrossDissolve::UICrossDissolve(Vector2 position, Gdiplus::Bitmap* bitmap, float alphatime, bool _isClickable)
{
	m_pos = position;
	m_BackGround = bitmap;
	alphaValue = alphatime;
	isClickable = _isClickable;
	Init();
}

void UICrossDissolve::Init()
{
	if (m_BackGround == nullptr) return;
	m_renderBounds = { {0.f, 0.f}, {m_BackGround->GetWidth() / 2.f, m_BackGround->GetHeight() / 2.f} };
}

void UICrossDissolve::Update(float delta)
{
	if (m_isActive == false) return;

	alphaValue -= High_Resolution_Time::GetUnScaleDeltaTime() / 1000.f;
	if (alphaValue < 0.f) {
		alphaValue = 0;
		m_isActive = false;
	}
	if (isClickable == true)
	{

		if (Input::GetMouseState().left && !Input::GetPrevMouseState().left)
		{
			alphaValue = 0.f;
		}
	}
}

void UICrossDissolve::Render(float alpha)
{
	if (m_isActive == false) return;
	if (m_BackGround == nullptr) return;
	Render::DrawImage(m_pos.x - m_renderBounds.extents.x, m_pos.y - m_renderBounds.extents.y, m_BackGround, 0, 0, m_renderBounds.extents.x * 2, m_renderBounds.extents.y * 2, alphaValue);
}

void UIFace::Init(Vector2 myPos, Gdiplus::Bitmap* myBitMap)
{
	m_pos = myPos;
	m_Bitmap = myBitMap;
	if (m_Bitmap == nullptr) return;
	cx = m_Bitmap->GetWidth();
	cy = m_Bitmap->GetHeight();

	m_renderBounds = { {0.f, 0.f }, { (float)cx, (float)cy } };
}

void UIFace::Render(float alpha) {
	if (m_isActive == false) return;
	Render::DrawImage(m_pos.x - m_renderBounds.extents.x, m_pos.y - m_renderBounds.extents.y, m_Bitmap, 0, 0, cx, cy, 1.0f);
}

void UIFace::OnTrigger()
{

}

void UIFace::SetFace(int faceNumber, float duration)
{
	m_Bitmap = m_faceImage[faceNumber];
	timer = duration;
}

void UIFace::Update(float delta) {
	if (m_isActive == false) return;
	// ���º�ȭ �̺�Ʈ? �ƹ�ư �󱼺�ȭ ���⼭ �ֱ�
	if (timer > 0.f) {
		timer -= delta;
		if (timer <= 0.f) {
			m_Bitmap = m_faceImage[0];
		}
	}
}

void In_ScoreBoard::Init(CResourceManager* CRM,Vector2 myPos, Vector2 endPos,Gdiplus::Bitmap* _bitmap, Gdiplus::Bitmap* _backBitmap, std::wstring _string)
{
	x = myPos.x;
	y = myPos.y;
	cx = endPos.x;
	cy = endPos.y;
	m_bitmapBack = CRM->LoadBitmapResouce(L"boaodBack", L"UI_Text_Stage_NowScore_01.png");
	m_bitmapTarget = _bitmap;
	m_bitmapTargetGray = _backBitmap;
	string = _string;
	/*memset(t_str, '\0', 255);*/
}

void In_ScoreBoard::Update(float delta)
{
	//Score : 0000
	string = L"";
	string.append(std::to_wstring(SceneManager::GetInstance()->GetCurScene()->g_Score));
	//Render(1.0f);
}

void In_ScoreBoard::Render(float alpha)
{
	Render::DrawImage(x, y, m_bitmapBack, 0, 0, cx, cy, 1.0f);
	Render::DrawFontS(x+120, y + 15, cx, cy-70, string.c_str(), RGB(255, 255, 255), 20, L"KOTRAHOPE.ttf", 1);
	//Render::DrawImage(x, y, m_bitmapTarget, 0, 0, cx, cy, 1.0f);
	if(m_bitmapTargetGray != nullptr)
		Render::DrawRotateImage(x+15, y-60, m_bitmapTargetGray, 270,1.0f,0.5f,0.5f);
}

void In_ScoreBoard::OnTrigger()
{
}

void In_ScoreBoard::SwapBitmap()
{
	m_bitmapTargetGray = m_bitmapTarget;
}

UIInputField::UIInputField(Vector2 position, float width, float height)
{
	wmemset(inputStr, L'\0', 9);
	isInput = false;
	strCount = 0;

	m_collider = new RectangleCollider({ 0.f,0.f }, width, height);
	m_collider->parent = this;
	m_pos = position;
	m_renderBounds = { {0.f, 0.f}, {width / 2.f, height / 2.f} };
	timer = 0.f;
}

void UIInputField::Init()
{

}



void UIInputField::Update(float delta)
{
	if (m_isActive == false) return;
	if (isInput == true) {
		strCount = Input::GetInputBuffer(inputStr, strCount, 9);
		if (Input::IsKeyDown('\b')) {
			if (strCount > 0)
				inputStr[strCount--] = L'\0';
		}
		timer -= delta;
		if (strCount < 8)
			inputStr[strCount] = timer >= 1.f ? L'_' : L' ';
		if (timer < 0.f) {
			timer = 2.f;
		}

		if (Input::IsKeyDown('\r')) {
			EnterInput();
		}
	}
	if (Input::GetMouseState().left && !Input::GetPrevMouseState().left) {
		Vector2 temp = Vector2(Input::GetMouseState().x, Input::GetMouseState().y);
		if (m_collider->isPointColliding(temp)) {
			isInput = true;
			Input::SetInputState(true);
		}
		else {
			isInput = false;
			Input::SetInputState(false);
			inputStr[strCount] = L'\0';
		}
	}
}

void UIInputField::Render(float alpha)
{
	//Render::DrawRect(m_pos.x - m_renderBounds.extents.x, m_pos.y - m_renderBounds.extents.y,
	//	m_renderBounds.extents.x * 2, m_renderBounds.extents.y * 2, RGB(0, 0, 0));
	Render::DrawFontS(m_pos.x - m_renderBounds.extents.x, m_pos.y - m_renderBounds.extents.y,
		m_renderBounds.extents.x * 2, m_renderBounds.extents.y * 2, inputStr, RGB(0, 0, 0), 40, L"KOTRAHOPE.ttf", 1);
}

void UIInputField::OnTrigger()
{

}

void UIInputField::EnterInput()
{
	inputStr[strCount] = L'\0';
	std::wcout << inputStr << std::endl;

	int strSize = WideCharToMultiByte(CP_UTF8, 0, inputStr, -1, NULL, 0, NULL, NULL);
	char* myName = new char[strSize];
	WideCharToMultiByte(CP_UTF8, 0, inputStr, -1, myName, strSize, 0, 0);

	Game::GameManager::GetInstance()->m_Ranking->players.push_back(Ranking::r_Player{ myName , (int)Game::GameManager::GetInstance()->FinalScore });
	//���� ���ɼ� ���� ����
}

void UISpeech::Init(Vector2 myPos, Gdiplus::Bitmap* myBitMap, Event* myEvent) {
	m_pos = myPos;
	m_Bitmap = myBitMap;
	m_Event = myEvent;
	if (m_Bitmap == nullptr) return;
	cx = m_Bitmap->GetWidth();
	cy = m_Bitmap->GetHeight();
	elepsedTime = 0.0f;
	wmemset(string, L'\0', 255);
	strCount = 0;
	memset(t_str, '\0', 255);
	timer = maxTime;

}


void UISpeech::Render(float alpha) {
	if (m_isActive == false) return;
	Render::DrawImage(m_pos.x, m_pos.y , m_Bitmap, 0, 0, cx, cy, 1.0f);
	Render::DrawFontS(m_pos.x+25 , m_pos.y+25, cx-100, cy-60, t_str, COLORREF(0x091f29), 12, L"KOTRAHOPE.ttf", 1);

}

void UISpeech::OnTrigger() {
	if (m_Event != nullptr) m_Event->OnTrigger();
}

void UISpeech::GetFeedBack(Speechenum feedbackNumber, WCHAR* out)
{
	switch (feedbackNumber) {
	case TUTORIALONE_Explanation_Control:
		wcscpy_s(out, 29, L"�ƺ�! ��ä�� WASDŰ�� ����� �̵��� �� �־�!");
		isTutorial = true;
		High_Resolution_Time::SetTimeScale2(0.f);
		break;
	case TUTORIALTWO_Explanation_Scoop:
		wcscpy_s(out, 49, L"SpaceŰ�� ������ 3�ʵ��� ��ä�� �������� ���µ� �׶� ����⸦ ���� �� �־�!");
		isTutorial = true;
		High_Resolution_Time::SetTimeScale2(0.f);
		break;
	case TUTORIALTHREE_Explanation_Boss:
		wcscpy_s(out, 57, L"�ƺ�! ��ǥ ������ �ٸ� ����⺸�� �� ���ڰ� ���� ������ε�...��.. ������ ���� �� �ູ����!");
		isTutorial = true;
		High_Resolution_Time::SetTimeScale2(0.f);
		break;
	case TUTORIALFOUR_Explanation_REMAINNINGTIME:
		wcscpy_s(out, 60, L"�ƺ�! ��� ������������ ���ѽð��� �־�! �׷��ϱ� ���ѽð� �ȿ� �ִ��� �̻� ����⸦ ���� ��ƾ� ��! ");
		isTutorial = true;
		High_Resolution_Time::SetTimeScale2(0.f);
		break;
	case TUTORIALFIVE_Explanation_CRAW:
		wcscpy_s(out, 51, L"�ƺ�! ����� �ƺ��� ��! �� �ƺ��� ������༭ ����⸦ �� �� ���� �� �ְ� ����! ");
		isTutorial = true;
		High_Resolution_Time::SetTimeScale2(0.f);
		break;
	case IfCrawCaptureScoreZero:
		wcscpy_s(out, 13, L"���Ⱦ�? �ƺ� ������?"); // ������ 0�� ���¿��� ���縦 ������ ���
		face->SetFace(1, 3.f);
		break;
	case IfCrawCaptureScoreOne:
		wcscpy_s(out, 19, L"���簡 ����⸦ ��ġ�� �߾�..."); // ������ 1 �̻��� ���¿��� ���縦 ������ ���
		face->SetFace(1, 3.f);
		break;
	case CaptureBossFish:
		wcscpy_s(out, 25, L"��¥ ���� �� ��Ҵ�! �ƺ�, ���� �����!"); // ��ǥ ����⸦ ������ ���
		face->SetFace(3, 4.f);
		break;
	case CaptureFish:
		wcscpy_s(out, 3, L"��~"); // ���� FB_06 ��¿Ϸ� �� 4�ʰ� ������, ����⸦ ������ ���
		face->SetFace(2, 2.f);
		break;
	case OneCaptureTwoKill:
		wcscpy_s(out, 5, L"���~!"); // ����� ��ȹ �� 1�� ���� �� ���� �� ��ȹ
		face->SetFace(3, 2.f);
		break;
	case SevenScore:
		wcscpy_s(out, 24, L"��û ����~! �ƺ� ����� ��û �� ���!"); // �� ������������ ���� 7�� �̻� �޼�
		face->SetFace(3, 4.f);
		break;
	case RemainningTime:
		wcscpy_s(out, 20, L"��ä�� �̻���... ������ �� ����"); // �������� ���� �ð��� 7�� ���� ���
		face->SetFace(1, 3.f);
		break;
	case CrawAppear:
		wcscpy_s(out, 28, L"������ �ƺ�! ���� ������ �ƺ��� ����⵵ �ƾ���"); // ���� ���� ��, ������ �ݶ��̴��� ���ʷ� ȭ�� �ȿ� ������ ���
		face->SetFace(1, 4.f);
		break;
	case TenSecNothingAnd14sec:
		wcscpy_s(out, 22, L"�ƺ��� �� �� �־�! ���� �ƺ� ����!"); // ���� ���� ���� 10�� ���/���� FB_09 ��� �� 14�� ���
		face->SetFace(2, 3.f);
		break;
	case Encouragement:
		wcscpy_s(out, 8, L"��~ �ܢ�~ "); // FB_01�� 10�� �̻� ���ӵǾ���, ���� �ð��� 10�� �̻� ���� ���
		face->SetFace(2, 2.f);
		break;
	case StageStart:
		wcscpy_s(out, 16, L"����! �� �� �� ��������!"); // �������� ���� ��
		face->SetFace(0, 2.f);
		break;
	default:
		std::cout << "Error: ������ ���� ���� ���Խ��ϴ�." << std::endl;
		break;
	}
}

bool SortEnumFeedback(Speechenum a, Speechenum b) {
	return a < b;
}

void UISpeech::Update(float delta) {
	if (isTutorial) {
		if (string[strCount] == L'\0') {
			isTutorial = false;
			High_Resolution_Time::SetTimeScale2(1.f);
			/*memset(t_str, '\0', 255);
			memset(string, '\0', 255);
			strCount = 0;*/
			textEnd = true;
		}
	}

	//if (m_isActive == false) return;
	nothingTimer -= delta;
	if (nothingTimer < 0.f) {
		AddFeedback(Speechenum::Encouragement); // �ݷ�
	}

	if (ignoreTimer > 0.f) {
		ignoreTimer -= delta;
		if (ignoreTimer <= 0.f) {
			std::sort(feedbackSort.begin(), feedbackSort.end(), SortEnumFeedback);
			Speechenum feedbackNum = feedbackSort.front();
			feedbackSort.clear();
			memset(t_str, '\0', 255);
			WCHAR in[255];
			GetFeedBack(feedbackNum, in);
			wcscpy_s(string, 255, in);
			strCount = 0;
			timer = maxTime;
			m_isActive = true;
			elepsedTime = 0.0f;
		}
	}

	if (textEnd == true)
	{
		elepsedTime += delta;
	}
	timer -= isTutorial ? High_Resolution_Time::GetUnScaleDeltaTime() / 1000.f : delta;
	if (timer <= 0.f) {
		timer += maxTime;
		if (string[strCount] != '\0') {
			t_str[strCount] = string[strCount];
			strCount++;
		}
		else {
			textEnd = true;
		}
	}
	//if (strCount < 255 && this->string[strCount] != '\0' && Input::GetMouseState().left && !Input::GetPrevMouseState().left) {
	//	// ���� ��ȭ�� �����ִٸ� ��ȭ�� ��� ���.
	//	wcscpy_s(t_str, 255, string);
	//	textEnd = true;
	//}

	if (elepsedTime > 1.5f)
	{
		memset(t_str, '\0', 255);
		m_isActive = false;
		textEnd = false;
	}
	if (ignoreTimer <= 0.f) {
		if (!feedbackSort.empty()) {
			ignoreTimer = 0.3f;
		}
	}

	// ��ȹ���� 
	// ó�� ��ȹ ���� �����ϸ� �� 0.3�� �ּ� �� �ȿ� �߰� ���� 
	// ������ �켱������ ���� �ֻ����� ����ϰ� ����ϴ� ���� ������ ��ȹ ������ �� ����
	// �׸��� �г������ �� ���� Ʈ���� ��Ȱ��ȭ
	// ��ǥ����� Ʈ���� ���̰� �ӵ� ���̱�

	
}


void UIIntroBack::Init(const WCHAR* fileName, CResourceManager* CRM) {
	LoadAnimImage(fileName, CRM);
	m_pos = { 960.f, 540.f };
	m_renderBounds = { {0,0},{m_bitmap[0]->GetWidth() / 2.f,m_bitmap[0]->GetHeight() / 2.f} };
	backGroundFrame = 0;
	backGroundFrameFlag = 0;
}

void UIIntroBack::LoadAnimImage(const WCHAR* fileName, CResourceManager* CRM)
{
	int fileNameLength = wcslen(fileName);

	m_fileName[0] = fileName;
	m_bitmap[0] = CRM->LoadBitmapResouce(fileName, fileName);
	std::wstring noNumFileName = m_fileName[0].substr(0, fileNameLength - 6);

	for (int i = 1; i < INTRO_ANIM_FRAME; i++) {
		std::wstring wZero = std::to_wstring(0);

		std::wstring wNum = std::to_wstring(i);
		if (i < 10) {
			m_fileName[i] = noNumFileName.append(wZero).append(wNum);
		}
		else {
			m_fileName[i] = noNumFileName.append(wNum);
		}

		m_bitmap[i] = CRM->LoadBitmapResouce(m_fileName[i].c_str(), m_fileName[i].append(L".png").c_str());
		noNumFileName = noNumFileName.substr(0, fileNameLength - 6);
	}


}

void UIIntroBack::OnTrigger() {
	if (m_Event != nullptr) m_Event->OnTrigger();
}

void UIIntroBack::Update(float delta) {
	bool temp = false;
	if (Input::IsKeyDown(' ')) temp = true;
	if (Input::GetMouseState().left && !Input::GetPrevMouseState().left) temp = true;
	if (temp) {
		backGroundFrame = (backGroundFrame + 1) % INTRO_ANIM_FRAME + 1;
		if (backGroundFrame == INTRO_ANIM_FRAME) m_Event->OnTrigger();
	}


}

void UIIntroBack::Render(float alpha) {

	/*Render::DrawImage(m_pos.x - m_renderBounds.extents.x,
		m_pos.y - m_renderBounds.extents.y, m_bitmap[backGroundFrame],
		0, 0, m_renderBounds.extents.x * 2, m_renderBounds.extents.y * 2);*/

		//Render::DrawImage(50, 200, m_bitmap[backGroundFrame], 0, 0, 1250, 800);
	Render::DrawBitmap(0, 0, m_bitmap[backGroundFrame], 0, 0, 1280, 720);

}

void UIVolume::Init(Vector2 startPos, Vector2 endPos, WCHAR* _string, int _fontSize, COLORREF myColor)
{
	mPos = startPos;
	fPos = endPos;
	mFontsize = _fontSize;
	m_Color = myColor;
}

void UIVolume::Update(float delta)
{
	float backv = Game::GameManager::GetInstance()->mVolume * 10.f;
	float effectv = Game::GameManager::GetInstance()->effectVolume * 10.f;
	if (backv > 10.f && effectv > 10.f)
	{
		backv = 10.f;
		effectv = 10.f;
	}
	swprintf(b_str, 20, L"%.f", backv);
	swprintf(e_str, 20, L"%.f", effectv);
}

void UIVolume::Render(float alpha)
{
	if (m_isActive == false) return;
	Render::DrawFontS(mPos.x, mPos.y, fPos.x, fPos.y, b_str, m_Color, mFontsize, L"KOTRAHOPE.ttf", 1);
	Render::DrawFontS(mPos.x, mPos.y + 200.f, fPos.x, fPos.y + 200.f, e_str, m_Color, mFontsize, L"KOTRAHOPE.ttf", 1);
}
