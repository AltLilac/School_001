#ifndef ___PLAYER
#define ___PLAYER

class Player {
private:
	const int    posX;			// 初期スポーンX座標
	const int    posY;			// 初期スポーンY座標

	const int    playerWidth;   // プレイヤーの横幅
	const int    playerHeight;  // プレイヤーの縦幅

	const double delta;			// プレイヤーの座標更新用

	Vec2         playerPos;		// プレイヤーの位置

	Rect*        playerEntity;  // プレイヤー本体

public:
	Player();

	void DrawPlayer() const;

	void InputPlayer();

	Rect GetPlayer() const { return *playerEntity; }
};

#endif