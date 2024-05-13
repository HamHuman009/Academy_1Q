#include "CResourceManager.h"
#include "CPathManager.h"


CPathManager path;

CResourceManager* CResourceManager::instance = nullptr;

AnimationResource::~AnimationResource()
{
	if (m_bitmap)
		delete m_bitmap;

	if (m_bitmapFlip)
		delete m_bitmapFlip;
}
void AnimationResource::LoadAnimImage(const WCHAR* fileName)
{
	m_fileName = fileName;
	m_bitmap = Gdiplus::Bitmap::FromFile(fileName);
	m_bitmapFlip = Gdiplus::Bitmap::FromFile(fileName);
	m_bitmapFlip->RotateFlip(Gdiplus::Rotate180FlipY); // 하나는 좌우 반전 이미지.
}

void AnimationResource::LoadAnimMotion(const WCHAR* fileName, bool IsLoop)
{
	std::wifstream file(fileName);
	if (!file.is_open()) {
		std::cout << "파일을 열 수 없습니다." << std::endl;
	}
	std::wstring line;			// 한줄의 문자열	
	Motion motion;
	{
		getline(file, line);		// 첫번째 줄 읽기
		std::wstringstream wss(line);
		wss >> motion.FrameCount;
	}

	for (int j = 0; j < motion.FrameCount; j++)
	{
		getline(file, line);		// 한줄 읽기
		std::wstringstream wss(line);    // 한줄을 읽어서 wstringstream에 저장
		std::wstring token;
		{
			getline(wss, token, L',');	// wss의 내용을 ,를 기준으로 문자열을 분리
			motion.Frames[j].Source.left = _wtoi(token.c_str());
			getline(wss, token, L',');
			motion.Frames[j].Source.top = _wtoi(token.c_str());
			getline(wss, token, L',');
			motion.Frames[j].Source.right = _wtoi(token.c_str());
			getline(wss, token, L',');
			motion.Frames[j].Source.bottom = _wtoi(token.c_str());
			getline(wss, token, L',');
			motion.Frames[j].CenterX = _wtoi(token.c_str());
			getline(wss, token, L',');
			motion.Frames[j].CenterY = _wtoi(token.c_str());

			motion.Frames[j].Size.cx = motion.Frames[j].Source.right - motion.Frames[j].Source.left + 1;
			motion.Frames[j].Size.cy = motion.Frames[j].Source.bottom - motion.Frames[j].Source.top + 1;
		}
	}
	motion.IsLoop = IsLoop;

	m_motions[m_motionCount] = motion;
	m_motionCount++;
}

CResourceManager::CResourceManager() {
	//path 경로 초기화 
	path.Init();
}

CResourceManager::~CResourceManager() {
	//소멸자에서 map 순회하며 전체 리소스 해제
	std::map<std::wstring, Gdiplus::Bitmap*>::iterator iter = m_mapBitmap.begin();
	for (; iter != m_mapBitmap.end(); ++iter) {
		delete iter->second;
	}

	/*std::map<std::wstring, AnimationResource*>::iterator iterAnimation = m_mapAnimation.begin();
	for (; iter != m_mapBitmap.end(); ++iter) {
		delete iter->second;
	}*/
}

Gdiplus::Bitmap* CResourceManager::LoadBitmapResouce(const std::wstring& _strkey, const std::wstring& _path)
{
	//키값으로 map에서 찾기
	Gdiplus::Bitmap* pBitmap = FindBitmapResouce(_strkey);
	//있으면 반환
	if (pBitmap != nullptr)
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

AnimationResource* CResourceManager::LoadAnimationResouce(const std::wstring& _strkey, const std::wstring& _path)
{
	//키값으로 map에서 찾기
	AnimationResource* pAnimation = FindAnimationResouce(_strkey);
	//있으면 반환
	if (pAnimation != nullptr)
	{
		return pAnimation;
	}
	//pathmanager로 상대경로 붙이기
	std::wstring strFilePath = path.GetContentPath(); 
	strFilePath += _path;
	//bitmap 로드
	pAnimation->LoadAnimImage(strFilePath.c_str());
	//map에 저장 하고
	m_mapAnimation.insert(make_pair(_strkey, pAnimation));
	//bitmap* 전달
	return pAnimation;
}

AnimationResource* CResourceManager::FindAnimationResouce(const std::wstring& _strkey)
{
	//map의 이터레이터를 사용 key값으로 찾음
	std::map<std::wstring, AnimationResource*>::iterator iter = m_mapAnimation.find(_strkey);
	//iterator 종료시 까지 없는 경우 --> map에 내용물이 없는경우 nullptr 반환
	if (iter == m_mapAnimation.end())
	{
		return nullptr;
	}
	//있는 경우 <first,second> -> <key,내용물>이므로 내용물을 반환
	return iter->second;
}

void CResourceManager::setAnimationMotion(const std::wstring& _strkey, const std::wstring& _path, bool IsLoop)
{
	AnimationResource* pAnimation = FindAnimationResouce(_strkey);
	if (pAnimation==nullptr)
	{
		return;
	}

	std::wstring strFilePath = path.GetContentPath();
	strFilePath += _path;
	pAnimation->LoadAnimMotion(strFilePath.c_str(), IsLoop);
}


CResourceManager* CResourceManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new CResourceManager();
	}
	return instance;
}

void CResourceManager::DestroyInstance()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}
