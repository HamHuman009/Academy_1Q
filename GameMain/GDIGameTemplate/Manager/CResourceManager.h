#pragma once
#include "../stdafx.h"
//#include "../Animation.h"
struct Frame
{
	RECT Source = { 0, };			// �κ������ �̹��� ����
	SIZE Size = { 0, };			// ��� ũ��
	int CenterX = 0, CenterY = 0;	// �߽��� �Ǵ� �̵� ��ġ 
};

struct Motion
{
	Frame Frames[20];		// ������ �����̳�
	int FrameCount = 0;			// ��ü ������ ��
	bool IsLoop = false;	// �ݺ� ����
};

struct AnimationResource
{
	std::wstring m_fileName;

	Gdiplus::Bitmap* m_bitmap = nullptr;		// Origin Image
	Gdiplus::Bitmap* m_bitmapFlip = nullptr;	// Flip Image
	Motion m_motions[10];	// �ִ� 10���� ������ ���� �� ����
	int m_motionCount = 0;	// ���� ������ ����

	~AnimationResource();	// GDI+�� �ı��Ǳ����� ��Ʈ�� �޸� �����ؾ��Ѵ�.

	void LoadAnimImage(const WCHAR* fileName);
	void LoadAnimMotion(const WCHAR* fileName, bool IsLoop = true);
};



class CResourceManager
{
	//Todo:
	//���� Gdiplus::Bitmap* �� ���� map �� ���������� animation�� sound �׿� �ʿ�� �߰� ���� �ʿ�
private:
	static CResourceManager* instance;
	//bitmap* ���� �� <key ��, ���빰> �� ��Ƽ� ���� ���� 
	std::map<std::wstring, Gdiplus::Bitmap*> m_mapBitmap;
	std::map<std::wstring, AnimationResource*> m_mapAnimation;

public:
	CResourceManager();
	~CResourceManager();
	static CResourceManager* GetInstance();
	static void DestroyInstance();
	//ã�� �ҷ����� Load�� �� map�� ����ִ����� �Ǵ� �Ͽ� ������ �ִ� ���빰�� ������ bitmap*�� ������ �ҷ����� ���
	Gdiplus::Bitmap* LoadBitmapResouce(const std::wstring& _strkey, const std::wstring& _path);
	Gdiplus::Bitmap* FindBitmapResouce(const std::wstring& _strkey);
	AnimationResource* LoadAnimationResouce(const std::wstring& _strkey, const std::wstring& _path);
	AnimationResource* FindAnimationResouce(const std::wstring& _strkey);
	void setAnimationMotion(const std::wstring& _strkey, const std::wstring& _path, bool IsLoop = true);
};

