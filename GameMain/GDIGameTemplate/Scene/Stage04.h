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
	//UIBackGround* myBackGround;  //fixedUpdate Ã³¸®ÇØ¾ßÇØ¼­ ºÎµæÀÌÇÏ°Ô ¼±¾ð.
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