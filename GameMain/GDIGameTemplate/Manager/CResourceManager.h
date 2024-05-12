#pragma once
#include "../stdafx.h"
class CResourceManager
{
	//Todo:
	//���� Gdiplus::Bitmap* �� ���� map �� ���������� animation�� sound �׿� �ʿ�� �߰� ���� �ʿ�
private:
	//bitmap* ���� �� <key ��, ���빰> �� ��Ƽ� ���� ���� 
	std::map<std::wstring, Gdiplus::Bitmap*> m_mapBitmap;
public:
	CResourceManager();
	~CResourceManager();
	//ã�� �ҷ����� Load�� �� map�� ����ִ����� �Ǵ� �Ͽ� ������ �ִ� ���빰�� ������ bitmap*�� ������ �ҷ����� ���
	Gdiplus::Bitmap* LoadBitmapResouce(const std::wstring& _strkey, const std::wstring& _path);
	Gdiplus::Bitmap* FindBitmapResouce(const std::wstring& _strkey);
};

