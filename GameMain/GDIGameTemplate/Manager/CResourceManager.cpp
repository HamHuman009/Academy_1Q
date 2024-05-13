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
	m_bitmapFlip->RotateFlip(Gdiplus::Rotate180FlipY); // �ϳ��� �¿� ���� �̹���.
}

void AnimationResource::LoadAnimMotion(const WCHAR* fileName, bool IsLoop)
{
	std::wifstream file(fileName);
	if (!file.is_open()) {
		std::cout << "������ �� �� �����ϴ�." << std::endl;
	}
	std::wstring line;			// ������ ���ڿ�	
	Motion motion;
	{
		getline(file, line);		// ù��° �� �б�
		std::wstringstream wss(line);
		wss >> motion.FrameCount;
	}

	for (int j = 0; j < motion.FrameCount; j++)
	{
		getline(file, line);		// ���� �б�
		std::wstringstream wss(line);    // ������ �о wstringstream�� ����
		std::wstring token;
		{
			getline(wss, token, L',');	// wss�� ������ ,�� �������� ���ڿ��� �и�
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
	//path ��� �ʱ�ȭ 
	path.Init();
}

CResourceManager::~CResourceManager() {
	//�Ҹ��ڿ��� map ��ȸ�ϸ� ��ü ���ҽ� ����
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
	//Ű������ map���� ã��
	Gdiplus::Bitmap* pBitmap = FindBitmapResouce(_strkey);
	//������ ��ȯ
	if (pBitmap != nullptr)
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

AnimationResource* CResourceManager::LoadAnimationResouce(const std::wstring& _strkey, const std::wstring& _path)
{
	//Ű������ map���� ã��
	AnimationResource* pAnimation = FindAnimationResouce(_strkey);
	//������ ��ȯ
	if (pAnimation != nullptr)
	{
		return pAnimation;
	}
	//pathmanager�� ����� ���̱�
	std::wstring strFilePath = path.GetContentPath(); 
	strFilePath += _path;
	//bitmap �ε�
	pAnimation->LoadAnimImage(strFilePath.c_str());
	//map�� ���� �ϰ�
	m_mapAnimation.insert(make_pair(_strkey, pAnimation));
	//bitmap* ����
	return pAnimation;
}

AnimationResource* CResourceManager::FindAnimationResouce(const std::wstring& _strkey)
{
	//map�� ���ͷ����͸� ��� key������ ã��
	std::map<std::wstring, AnimationResource*>::iterator iter = m_mapAnimation.find(_strkey);
	//iterator ����� ���� ���� ��� --> map�� ���빰�� ���°�� nullptr ��ȯ
	if (iter == m_mapAnimation.end())
	{
		return nullptr;
	}
	//�ִ� ��� <first,second> -> <key,���빰>�̹Ƿ� ���빰�� ��ȯ
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
