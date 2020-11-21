#ifndef ___GAMEOVERSCENE
#define ___GAMEOVERSCENE

#include <Siv3D.hpp>
#include "Debug.h"

class GameOverScene : public SceneManager<String>::Scene {
private:
	Debug debug;

public:
	GameOverScene(const InitData& init);

	void draw() const override;

	void update() override;
};

#endif