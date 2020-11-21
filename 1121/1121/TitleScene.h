#ifndef ___TITLESCENE
#define ___TITLESCENE

#include <Siv3D.hpp>
#include "Debug.h"

class TitleScene : public SceneManager<String>::Scene {
private:
	Debug debug;

public:
	TitleScene(const InitData& init) : IScene(init) {

	}

	void draw() const override;

	void update() override;
};

#endif