#ifndef ___TITLESCENE
#define ___TITLESCENE

#include <Siv3D.hpp>

class TitleScene : public SceneManager<String>::Scene {
private:
	Point titleUIPos, pressKeyUIPos;

public:
	TitleScene(const InitData& init);

	void draw() const override;

	void update() override;
};

#endif