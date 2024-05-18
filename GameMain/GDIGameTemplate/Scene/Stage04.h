#pragma once
#include "CScene.h"
//#include "../GameLogic/Objects/Object.h"
#include "../GameLogic/Objects/Player.h"

class UIImage;
//class Player;
class UIBackGround;
class Stage04 : public CScene
{
private:
	/*UIBackGround* myBack; // ÀÌ·± º¯¼ö´Â m_arrObj¿¡¼­ °ü¸®.
	Player* m_Player; */
	//UIBackGround* myBackGround; //fixedUpdate Ã³¸®ÇØ¾ßÇØ¼­ ºÎµæÀÌÇÏ°Ô ¼±¾ð.
	//UIBackGround* myUPBackGround;
public:
	// CSceneÀ»(¸¦) ÅëÇØ »ó¼ÓµÊ
	void Init() override;
	void Start() override;
	void Exit() override;
	void FixedUpdate() override;

	Stage04() {};
	~Stage04();
};

class UIImage;
//class Player;
class UIBackGround;
class Stage04 : public CScene
{
private:
	/*UIBackGround* myBack; // ï¿½Ì·ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ m_arrObjï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½.
	Player* m_Player; */
	//UIBackGround* myBackGround; //fixedUpdate Ã³ï¿½ï¿½ï¿½Ø¾ï¿½ï¿½Ø¼ï¿½ ï¿½Îµï¿½ï¿½ï¿½ï¿½Ï°ï¿½ ï¿½ï¿½ï¿½ï¿½.
	//UIBackGround* myUPBackGround;
public:
	// CSceneï¿½ï¿½(ï¿½ï¿½) ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½Óµï¿?
	void Init() override;
	void Start() override;
	void Exit() override;
	void FixedUpdate() override;

	Stage04() {};
	~Stage04();
};