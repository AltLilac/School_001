#include <Siv3D.hpp>
#include "Player.h"

Player::Player()
	: posX(35), posY(35), playerPos(posX, posY), playerWidth(25), playerHeight(25), 
	  delta(100 * Scene::DeltaTime()), 
	  playerEntity(new Rect(playerPos.x, playerPos.y, playerWidth, playerHeight)) {

}

void Player::DrawPlayer_Test() const {
	playerEntity->draw(Palette::Lightgrey).drawFrame(0, 4, Color(47));
}

/*
Rect Player::DrawPlayer() const {
	Rect playerEntity(playerPos.x, playerPos.y, playerWidth, playerHeight);

	playerEntity.draw(Palette::Lightgrey).drawFrame(0, 4, Color(47));

	return playerEntity;
}
*/

void Player::InputPlayer() {

	if (KeyW.pressed()) {
		playerEntity->y -= delta;
	}
	if (KeyS.pressed()) {
		playerEntity->y += delta;
	}
	if (KeyA.pressed()) {
		playerEntity->x -= delta;
	}
	if (KeyD.pressed()) {
		playerEntity->x += delta;
	}
}