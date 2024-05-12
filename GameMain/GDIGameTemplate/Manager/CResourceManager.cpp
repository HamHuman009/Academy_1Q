#include "CResourceManager.h"
#include "CPathManager.h"

CPathManager path;

CResourceManager::CResourceManager() {

}

CResourceManager::~CResourceManager() {
}

Gdiplus::Bitmap* CResourceManager::LoadBitmapResouce(const std::wstring& _strkey, const std::wstring& _path)
{
	//Ű������ map���� ã��
	Gdiplus::Bitmap* pBitmap = FindBitmapResouce(_strkey);
	//������ ��ȯ
	if (pBitmap!=nullptr)
	{
		return pBitmap;
	}
	//pathmanager�� ����� ���̱�
	std::wstring strFilePath = path.GetContentPath(); //�� ������ ��ġ��!!
	strFilePath += _path;
	//bitmap �ε�
	pBitmap = Gdiplus::Bitmap::FromFile(strFilePath.c_str());
	//map�� ���� �ϰ�
	m_mapBitmap.insert(make_pair(_strkey, pBitmap));
	//bitmap* ����
	return pBitmap;
}

Gdiplus::Bitmap* CResourceManager::FindBitmapResouce(const std::wstring& _strkey)
{
	//map�� ���ͷ����͸� ��� key������ ã��
	std::map<std::wstring, Gdiplus::Bitmap*>::iterator iter = m_mapBitmap.find(_strkey);
	//iterator ����� ���� ���� ��� --> map�� ���빰�� ���°�� nullptr ��ȯ
	if (iter == m_mapBitmap.end())
	{
		return nullptr;
	}
		//�ִ� ��� <first,second> -> <key,���빰>�̹Ƿ� ���빰�� ��ȯ
	return iter->second;
}
