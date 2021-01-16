#include <Siv3D.hpp>
#include "Player.h"

Player::Player()
	: posX(35), 
	  posY(35), 
	  playerPos(posX, posY), 
	  playerWidth(30), 
	  playerHeight(30), 
	  delta(100 * Scene::DeltaTime()), 
	  playerEntity(new Rect(playerPos.x, playerPos.y, playerWidth, playerHeight)) 
{

}

void Player::DrawPlayer() const {
	playerEntity->draw(Palette::Lightgrey).drawFrame(4, 0, Color(47));
}

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