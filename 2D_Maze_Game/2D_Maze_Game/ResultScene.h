#ifndef ___RESULTSCENE
#define ___RESULTSCENE

#include <Siv3D.hpp>
#include "MainGameScene.h"

class ResultScene : public SceneManager<String>::Scene {
private:
	Point		   pressKeyUIPos;
	Point		   mainUIPos;

	MainGameScene* mGameScene;

public:
	ResultScene(const InitData& init);

	void draw() const override;
	void update() override;
};

#endif