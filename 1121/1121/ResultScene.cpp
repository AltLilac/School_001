#include <Siv3D.hpp>
#include "ResultScene.h"

ResultScene::ResultScene(const InitData& init)
	: IScene(init), 
	  mGameScene(new MainGameScene(init)),
	  pressKeyPos(400, 460) 
{

}

void ResultScene::draw() const {
	debug.DrawCoordinate();

	Scene::SetBackground(Palette::Darkcyan);

	FontAsset(U"ResultFont")(U"ResultScene").drawAt(400, 150);
	FontAsset(U"ResultFont")(U"Press Enter Key to Continue...").drawAt(pressKeyPos.movedBy(2, 2), ColorF(0.0, 0.7));
	FontAsset(U"ResultFont")(U"Press Enter Key to Continue...").drawAt(pressKeyPos);
	// FontAsset(U"ResultFont")(U"{}{}{}"_fmt(U"Your Score", U" : ", mGameScene.GetCurrentTime() * 10)).drawAt(400, 200);
}

void ResultScene::update() {
	if (KeyEnter.pressed()) {
		changeScene(U"Title");
	}
}
