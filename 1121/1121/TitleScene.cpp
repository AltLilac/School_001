#include <Siv3D.hpp>
#include "TitleScene.h"

void TitleScene::draw() const {
	Scene::SetBackground(Palette::Lightblue);

	debug.DrawCoordinate();

	FontAsset(U"TitleFont")(U"My Game").drawAt(400, 150);
	FontAsset(U"TitleFont")(U"Press Enter Key").drawAt(400, 460);
}

void TitleScene::update() {
	if (KeyEnter.down()) {
		changeScene(U"MainGame");
	}
}