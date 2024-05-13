#pragma once
#include "../stdafx.h"
//#include "../Animation.h"
struct Frame
{
	RECT Source = { 0, };			// 부분출력할 이미지 영역
	SIZE Size = { 0, };			// 출력 크기
	int CenterX = 0, CenterY = 0;	// 중심이 되는 이동 위치 
};

struct Motion
{
	Frame Frames[20];		// 프레임 컨테이너
	int FrameCount = 0;			// 전체 프레임 수
	bool IsLoop = false;	// 반복 여부
};

struct AnimationResource
{
	std::wstring m_fileName;

	Gdiplus::Bitmap* m_bitmap = nullptr;		// Origin Image
	Gdiplus::Bitmap* m_bitmapFlip = nullptr;	// Flip Image
	Motion m_motions[10];	// 최대 10개의 동작을 가질 수 있음
	int m_motionCount = 0;	// 현재 동작의 개수

	~AnimationResource();	// GDI+가 파괴되기전에 비트맵 메모리 해제해야한다.

	void LoadAnimImage(const WCHAR* fileName);
	void LoadAnimMotion(const WCHAR* fileName, bool IsLoop = true);
};



class CResourceManager
{
	//Todo:
	//현제 Gdiplus::Bitmap* 에 대한 map 만 만들어놓았음 animation과 sound 그외 필요시 추가 구현 필요
private:
	static CResourceManager* instance;
	//bitmap* 담을 맵 <key 값, 내용물> 을 담아서 쓸수 있음 
	std::map<std::wstring, Gdiplus::Bitmap*> m_mapBitmap;
	std::map<std::wstring, AnimationResource*> m_mapAnimation;

public:
	CResourceManager();
	~CResourceManager();
	static CResourceManager* GetInstance();
	static void DestroyInstance();
	//찾기 불러오기 Load시 위 map에 담겨있는지도 판단 하여 있으면 있는 내용물을 없으면 bitmap*로 파일을 불러오라 사용
	Gdiplus::Bitmap* LoadBitmapResouce(const std::wstring& _strkey, const std::wstring& _path);
	Gdiplus::Bitmap* FindBitmapResouce(const std::wstring& _strkey);
	AnimationResource* LoadAnimationResouce(const std::wstring& _strkey, const std::wstring& _path);
	AnimationResource* FindAnimationResouce(const std::wstring& _strkey);
	void setAnimationMotion(const std::wstring& _strkey, const std::wstring& _path, bool IsLoop = true);
};

