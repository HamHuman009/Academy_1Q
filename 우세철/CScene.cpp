#include "CScene.h"

void CScene::Update() {
	for (UINT i = 0; i < (UINT)TYPE::END; ++i) {
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			m_arrObj[i][j]->update();
		}
	}
}