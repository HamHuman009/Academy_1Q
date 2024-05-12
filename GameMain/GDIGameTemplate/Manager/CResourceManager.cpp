#include "CResourceManager.h"
#include "CPathManager.h"

CPathManager path;

CResourceManager::CResourceManager() {

}

CResourceManager::~CResourceManager() {
}

Gdiplus::Bitmap* CResourceManager::LoadBitmapResouce(const std::wstring& _strkey, const std::wstring& _path)
{
	//키값으로 map에서 찾기
	Gdiplus::Bitmap* pBitmap = FindBitmapResouce(_strkey);
	//있으면 반환
	if (pBitmap!=nullptr)
	{
		return pBitmap;
	}
	//pathmanager로 상대경로 붙이기
	std::wstring strFilePath = path.GetContentPath(); //요 언저리 고치기!!
	strFilePath += _path;
	//bitmap 로드
	pBitmap = Gdiplus::Bitmap::FromFile(strFilePath.c_str());
	//map에 저장 하고
	m_mapBitmap.insert(make_pair(_strkey, pBitmap));
	//bitmap* 전달
	return pBitmap;
}

Gdiplus::Bitmap* CResourceManager::FindBitmapResouce(const std::wstring& _strkey)
{
	//map의 이터레이터를 사용 key값으로 찾음
	std::map<std::wstring, Gdiplus::Bitmap*>::iterator iter = m_mapBitmap.find(_strkey);
	//iterator 종료시 까지 없는 경우 --> map에 내용물이 없는경우 nullptr 반환
	if (iter == m_mapBitmap.end())
	{
		return nullptr;
	}
		//있는 경우 <first,second> -> <key,내용물>이므로 내용물을 반환
	return iter->second;
}
