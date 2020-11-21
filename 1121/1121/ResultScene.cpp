#include <Siv3D.hpp>
#include "ResultScene.h"

ResultScene::ResultScene(const InitData& init) : IScene(init) {

}

void ResultScene::draw() const {
	debug.DrawCoordinate();

	Scene::SetBackground(Palette::Darkcyan);

	FontAsset(U"ResultFont")(U"ResultScene").drawAt(400, 150);
	FontAsset(U"ResultFont")(U"Press Enter Key to Continue...").drawAt(400, 500);
	// FontAsset(U"ResultFont")(U"{}{}{}"_fmt(U"Your Score", U" : ", mGameScene.GetCurrentTime() * 10)).drawAt(400, 200);
}

void ResultScene::update() {
	if (KeyEnter.pressed()) {
		changeScene(U"Title");
	}
}
