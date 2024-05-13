#include "CScene.h"

void CScene::Render() {
	for (int i = 0; i < m_arrObj.size(); i++) {
		m_arrObj[i]->Render();

	}
}