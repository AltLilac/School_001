#include <Siv3D.hpp>
#include "GameOverScene.h"

GameOverScene::GameOverScene(const InitData& init)
	: IScene(init),
	  pressKeyPos(400, 460)
{
	
}

void GameOverScene::draw() const {
	Scene::SetBackground(Palette::Darkcyan);

	debug.DrawCoordinate();

	FontAsset(U"ResultFont")(U"GameOverScene").drawAt(400, 150);
	FontAsset(U"ResultFont")(U"Press Enter Key to Continue...").drawAt(pressKeyPos.movedBy(2, 2), ColorF(0.0, 0.7));
	FontAsset(U"ResultFont")(U"Press Enter Key to Continue...").drawAt(pressKeyPos);
}

void GameOverScene::update() {
	if (KeyEnter.pressed()) {
		changeScene(U"Title");
	}
}