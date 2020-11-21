#include <Siv3D.hpp>
#include "GameOverScene.h"

GameOverScene::GameOverScene(const InitData& init) : IScene(init) {
	
}

void GameOverScene::draw() const {
	Scene::SetBackground(Palette::Darkcyan);

	debug.DrawCoordinate();
}

void GameOverScene::update() {

}