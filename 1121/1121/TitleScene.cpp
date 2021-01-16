#include <Siv3D.hpp>
#include "TitleScene.h"

TitleScene::TitleScene(const InitData& init) : IScene(init), titleUIPos(400, 150), pressKeyUIPos(400, 460) {

}

void TitleScene::draw() const {
	Scene::SetBackground(Color(220));

	debug.DrawCoordinate();

	FontAsset(U"TitleFont")(U"2D Maze Game").drawAt(titleUIPos.movedBy(2, 2), ColorF(0.0, 0.7));
	FontAsset(U"TitleFont")(U"2D Maze Game").drawAt(titleUIPos);
	FontAsset(U"TitleFont")(U"Press Enter Key").drawAt(pressKeyUIPos.movedBy(2, 2), ColorF(0.0, 0.7));
	FontAsset(U"TitleFont")(U"Press Enter Key").drawAt(pressKeyUIPos);
}

void TitleScene::update() {
	if (KeyEnter.down()) {
		changeScene(U"MainGame");
	}
}