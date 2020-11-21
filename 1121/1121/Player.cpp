#include <Siv3D.hpp>
#include "Player.h"

Player::Player() : posX(35), posY(35), playerPos(posX, posY), playerWidth(25), playerHeight(25), delta(100 * Scene::DeltaTime()) {

}

Rect Player::DrawPlayer() const {
	Rect playerEntity(playerPos.x, playerPos.y, playerWidth, playerHeight);

	playerEntity.draw(Palette::Lightgrey).drawFrame(0, 4, Color(47));

	return playerEntity;
}

void Player::InputPlayer() {

	if (KeyW.pressed()) {
		playerPos.y -= delta;
	}
	if (KeyS.pressed()) {
		playerPos.y += delta;
	}
	if (KeyA.pressed()) {
		playerPos.x -= delta;
	}
	if (KeyD.pressed()) {
		playerPos.x += delta;
	}
}