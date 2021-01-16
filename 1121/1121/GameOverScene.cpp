#include <Siv3D.hpp>
#include "GameOverScene.h"

GameOverScene::GameOverScene(const InitData& init)
	: IScene(init),
	  pressKeyUIPos(400, 460),
	  mainUIPos(400, 150)
{
	
}

void GameOverScene::draw() const {
	Scene::SetBackground(Color(220));

	debug.DrawCoordinate();

	FontAsset(U"ResultFont")(U"Game Over").drawAt(mainUIPos.movedBy(2, 2), ColorF(0.0, 0.7));
	FontAsset(U"ResultFont")(U"Game Over").drawAt(mainUIPos);
	FontAsset(U"ResultFont")(U"Press Enter Key to Continue...").drawAt(pressKeyUIPos.movedBy(2, 2), ColorF(0.0, 0.7));
	FontAsset(U"ResultFont")(U"Press Enter Key to Continue...").drawAt(pressKeyUIPos);
}

void GameOverScene::update() {
	if (KeyEnter.pressed()) {
		changeScene(U"Title");
	}
}