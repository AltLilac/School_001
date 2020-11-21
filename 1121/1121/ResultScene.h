#ifndef ___RESULTSCENE
#define ___RESULTSCENE

#include <Siv3D.hpp>
#include "Debug.h"
#include "MainGameScene.h"

class ResultScene : public SceneManager<String>::Scene {
private:
	Debug debug;

public:
	ResultScene(const InitData& init);

	void draw() const override;
	
	void update() override;
};

#endif