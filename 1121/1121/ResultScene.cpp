#include <Siv3D.hpp>
#include "ResultScene.h"

ResultScene::ResultScene(const InitData& init)
	: IScene(init), 
	  mGameScene(new MainGameScene(init)),
	  pressKeyUIPos(400, 460),
	  mainUIPos(400, 150)
{

}

void ResultScene::draw() const {
	debug.DrawCoordinate();

	Scene::SetBackground(Color(220));

	FontAsset(U"ResultFont")(U"You Win").drawAt(mainUIPos.movedBy(2, 2), ColorF(0.0, 0.7));
	FontAsset(U"ResultFont")(U"You Win").drawAt(mainUIPos);
	FontAsset(U"ResultFont")(U"Press Enter Key to Continue...").drawAt(pressKeyUIPos.movedBy(2, 2), ColorF(0.0, 0.7));
	FontAsset(U"ResultFont")(U"Press Enter Key to Continue...").drawAt(pressKeyUIPos);
}

void ResultScene::update() {
	if (KeyEnter.pressed()) {
		changeScene(U"Title");
	}
}
