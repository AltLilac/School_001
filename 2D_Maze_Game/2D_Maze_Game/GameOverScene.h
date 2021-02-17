#ifndef ___GAMEOVERSCENE
#define ___GAMEOVERSCENE

#include <Siv3D.hpp>

class GameOverScene : public SceneManager<String>::Scene {
private:
	Point pressKeyUIPos;
	Point mainUIPos;

public:
	GameOverScene(const InitData& init);

	void draw() const override;
	void update() override;
};

#endif